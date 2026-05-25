#!/usr/bin/env python3
"""
Generates an XML descriptor for a custom audio sample (WAV/OGG/MP3) compatible
with Starship's ResourceFactoryXMLSampleV0.

The XML and the audio file must both be packed into the same OTR/o2r archive so
that the engine can load them at runtime. This tool only generates the XML; use
your archive-packing workflow (e.g. o2r_builder) to bundle both files.

Usage examples:
    python3 tools/import_audio_sample.py mysound.wav --asset audio/custom/mysound
    python3 tools/import_audio_sample.py bgm.ogg --asset audio/custom/bgm --sample-rate 44100 --channels 1
    python3 tools/import_audio_sample.py voice.mp3 --asset audio/custom/voice --out-dir mods/my_mod/assets
"""

import argparse
import json
import os
import shutil
import struct
import subprocess
import sys
import wave
import xml.dom.minidom
import xml.etree.ElementTree as ET


# Starship runs its audio mixer at 32 kHz.  Tuning is the ratio of the
# sample's playback rate to that reference frequency.
_AUDIO_REFERENCE_HZ = 32000.0


def _probe_wav(path):
    """Return (sample_rate, channels) from a WAV file using stdlib only."""
    with wave.open(path, "rb") as w:
        return w.getframerate(), w.getnchannels()


def _probe_via_ffprobe(path):
    """
    Return (sample_rate, channels) by calling ffprobe.
    Raises FileNotFoundError if ffprobe is not on PATH.
    """
    result = subprocess.run(
        [
            "ffprobe", "-v", "quiet",
            "-print_format", "json",
            "-show_streams",
            "-select_streams", "a:0",
            path,
        ],
        capture_output=True,
        text=True,
        check=True,
    )
    info = json.loads(result.stdout)
    stream = info["streams"][0]
    return int(stream["sample_rate"]), int(stream["channels"])


def probe_audio(path, sample_rate=None, channels=None):
    """
    Determine sample_rate and channels.  Explicit arguments take precedence.
    Falls back to WAV stdlib, then ffprobe, then asks the user.
    """
    ext = os.path.splitext(path)[1].lower()

    if sample_rate is None or channels is None:
        detected_rate, detected_ch = None, None

        if ext == ".wav":
            try:
                detected_rate, detected_ch = _probe_wav(path)
            except Exception as e:
                print(f"[warn] Could not read WAV header: {e}", file=sys.stderr)

        if detected_rate is None:
            try:
                detected_rate, detected_ch = _probe_via_ffprobe(path)
            except (FileNotFoundError, subprocess.CalledProcessError, KeyError) as e:
                pass

        if detected_rate is None:
            print(
                "[info] Could not detect audio metadata automatically.\n"
                "       Install ffprobe (part of ffmpeg) for automatic detection.",
                file=sys.stderr,
            )
            if sample_rate is None:
                sample_rate = int(input("  Enter sample rate (e.g. 44100): "))
            if channels is None:
                channels = int(input("  Enter channel count (1=mono, 2=stereo): "))
        else:
            if sample_rate is None:
                sample_rate = detected_rate
            if channels is None:
                channels = detected_ch

    return sample_rate, channels


def make_xml(asset_path, audio_filename, fmt, tuning):
    """
    Build the tinyxml2-compatible XML used by ResourceFactoryXMLSampleV0.

    asset_path    – the in-archive path for the audio file (e.g. audio/custom/mysound.wav)
    audio_filename – basename of the audio file as stored in the archive
    fmt           – "wav", "ogg", or "mp3"
    tuning        – (sample_rate * channels) / 32000.0
    """
    root = ET.Element("Sample")
    root.set("Version", "0")
    root.set("Codec", "S16")
    root.set("Medium", "Ram")
    root.set("bit26", "0")
    root.set("Tuning", f"{tuning:.6f}")
    # Size will be determined at decode time; 0 is a safe placeholder.
    root.set("Size", "0")
    root.set("Relocated", "0")
    root.set("Path", asset_path)
    root.set("CustomFormat", fmt)

    raw = ET.tostring(root, encoding="unicode")
    dom = xml.dom.minidom.parseString(raw)
    return dom.toprettyxml(indent="  ", encoding=None).replace('<?xml version="1.0" ?>\n', "")


def main():
    parser = argparse.ArgumentParser(
        description="Generate a Starship sample XML for a custom audio file."
    )
    parser.add_argument("audio", help="Input audio file (.wav, .ogg, or .mp3)")
    parser.add_argument(
        "--asset",
        required=True,
        help="Asset path inside the archive, without extension (e.g. audio/custom/mysound). "
             "The audio file will be stored at <asset>.<ext>.",
    )
    parser.add_argument(
        "--out-dir",
        default=None,
        help="Directory to write the XML and copy the audio file into. "
             "Mirrors the asset path hierarchy. Defaults to the directory of the input file.",
    )
    parser.add_argument(
        "--sample-rate",
        type=int,
        default=None,
        help="Override detected sample rate (Hz).",
    )
    parser.add_argument(
        "--channels",
        type=int,
        default=None,
        help="Override detected channel count.",
    )
    args = parser.parse_args()

    audio_path = os.path.abspath(args.audio)
    if not os.path.isfile(audio_path):
        print(f"error: file not found: {audio_path}", file=sys.stderr)
        sys.exit(1)

    ext = os.path.splitext(audio_path)[1].lower().lstrip(".")
    if ext not in ("wav", "ogg", "mp3"):
        print(f"error: unsupported format '.{ext}'. Only wav, ogg, mp3 are supported.", file=sys.stderr)
        sys.exit(1)

    sample_rate, channels = probe_audio(audio_path, args.sample_rate, args.channels)
    tuning = (sample_rate * channels) / _AUDIO_REFERENCE_HZ

    asset_path_with_ext = f"{args.asset}.{ext}"

    xml_content = make_xml(asset_path_with_ext, os.path.basename(audio_path), ext, tuning)

    if args.out_dir is not None:
        out_dir = os.path.abspath(args.out_dir)
    else:
        out_dir = os.path.dirname(audio_path)

    # Mirror the asset hierarchy inside out_dir.
    asset_rel_dir = os.path.dirname(args.asset)
    dest_dir = os.path.join(out_dir, asset_rel_dir)
    os.makedirs(dest_dir, exist_ok=True)

    asset_basename = os.path.basename(args.asset)
    xml_out = os.path.join(dest_dir, f"{asset_basename}.xml")
    audio_out = os.path.join(dest_dir, f"{asset_basename}.{ext}")

    with open(xml_out, "w", encoding="utf-8") as f:
        f.write(xml_content)

    if os.path.abspath(audio_path) != os.path.abspath(audio_out):
        shutil.copy2(audio_path, audio_out)

    print(f"Sample rate : {sample_rate} Hz")
    print(f"Channels    : {channels}")
    print(f"Tuning      : {tuning:.6f}")
    print(f"XML written : {xml_out}")
    print(f"Audio file  : {audio_out}")
    print()
    print("Next steps:")
    print(f"  1. Add both files to your OTR/o2r archive under the paths:")
    print(f"       {args.asset}.xml")
    print(f"       {asset_path_with_ext}")
    print(f"  2. In your mod/game code, load the sample via:")
    print(f'       ResourceManager::LoadResource("{args.asset}")')


if __name__ == "__main__":
    main()
