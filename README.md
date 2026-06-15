[comment]: <> (Todo: Make Light Mode Image)
[comment]: <> (Todo: Make Dark Mode Image)

# Starship

Lead Developers: 
* [SonicDcer](https://www.github.com/sonicdcer)
* [Lywx](https://www.github.com/kiritodv)

## Discord

Official Discord: https://discord.com/invite/shipofharkinian

If you're having any trouble after reading through this `README`, feel free ask for help in the Starship Support text channels. Please keep in mind that we do not condone piracy.

# Quick Start

Starship does not include any copyrighted assets.  You are required to provide a supported copy of the game.

### 1. Verify your ROM dump
The supported ROMs are US 1.0 and US 1.1 Rev A versions. You can verify you have dumped a supported copy of the game by using the SHA-1 File Checksum Online at https://www.romhacking.net/hash/. 

* The SHA-1 hash for a US 1.0 ROM is D8B1088520F7C5F81433292A9258C1184AFA1457.
* The SHA-1 hash for a US 1.1 ROM is 09F0D105F476B00EFA5303A3EBC42E60A7753B7A.

Starship also supports voice language replacement use from both EU (Lylat) and JP (Japanese) when used in conjunction with an US ROM.

Note: JP and EU versions of the game are not supported for the base asset O2R creation, a US ROM must be used for it, and you can only use one voice language replacement at a time (Either EU or JP).

### 2. Verify your ROM is in .z64 format
Your ROM needs to be in .z64 format. If it's in .n64 format, use the following to convert it to a .z64: https://hack64.net/tools/swapper.php

### 2. Download Starship from [Releases](https://github.com/HarbourMasters/Starship/releases)

### 3. Generating the OTR from the ROM and Play!
#### Windows
* Extract every file from the zip into a folder of your choosing.
* Run starship.exe and select your US 1.0 or US 1.1 ROM.

#### Linux
* Extract every file from the zip into a folder of your choosing.
* Execute starship.appimage. You may have to chmod +x the appimage via terminal.

#### MacOS
* Extract every file from the zip into a folder of your choosing.
* Run starship and select your US 1.0 or US 1.1 ROM.

#### Nintendo Switch
* Run one of the PC releases to generate an `sf64.o2r` file. After launching the game on PC, you will be able to find these files in the same directory as `starship.exe` or `starship.appimage`.
* Copy the files to your sd card

# Configuration

### Default keyboard configuration
| N64 | A | B | Z | Start | Analog stick | C buttons | D-Pad |
| - | - | - | - | - | - | - | - |
| Keyboard | X | C | Z | Space | WASD | Arrow keys | TFGH |

### Other shortcuts
| Keys | Action |
| - | - |
| F1 | Toggle menubar |
| F4 | Reset |
| F11 | Fullscreen |
| Tab | Toggle Alternate assets |

### Graphics Backends
Currently, there are three rendering APIs supported: DirectX11 (Windows), OpenGL (all platforms), and Metal (macOS). You can change which API to use in the `Settings` menu of the menubar, which requires a restart.  If you're having an issue with crashing, you can change the API in the `starship.cfg.json` file by finding the line `"Backend":{`... and changing the `id` value to `3` and set the `Name` to `OpenGL`. `DirectX 11` with id `2` is the default on Windows. `Metal` with id `4` is the default on macOS.

# Custom Assets
Custom assets are packed in `.o2r` or `.otr` files. To use custom assets, place them in the `mods` folder.

If you're interested in creating and/or packing your own custom asset `.o2r`/`.otr` files, check out the following tools:
* [**retro - OTR and O2R generator**](https://github.com/HarbourMasters64/retro)
* [**fast64 - Blender plugin (Note that SF64 is not supported at this time)**](https://github.com/HarbourMasters/fast64)

# Development
### Building

If you want to manually compile Starship, please consult the [building instructions](https://github.com/HarbourMasters/Starship/blob/main/docs/BUILDING.md).

### Playtesting
If you want to playtest a continuous integration build, you can find them at the links below. Keep in mind that these are for playtesting only, and you will likely encounter bugs and possibly crashes. 

* [Windows](https://nightly.link/HarbourMasters/Starship/workflows/main/main/starship-windows.zip)
* [macOS](https://nightly.link/HarbourMasters/Starship/workflows/main/main/Starship-mac.zip)
* [Linux](https://nightly.link/HarbourMasters/Starship/workflows/main/main/Starship-linux.zip)
* [Switch](https://nightly.link/HarbourMasters/Starship/workflows/main/main/Starship-switch.zip)

<a href="https://github.com/Kenix3/libultraship/">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./docs/poweredbylus.darkmode.png">
    <img alt="Powered by libultraship" src="./docs/poweredbylus.lightmode.png">
  </picture>
</a>

# Special Thanks:

* [ZeldaRET](https://github.com/zeldaret) : for teaching me the fundamental knowledge of N64 decompilation.
* [Decompals](https://github.com/decompals) : for helping in the initial disassembly and decompilation of the game.
* [HM64 Team](https://github.com/harbourMasters) : for creating Libultraship and helping with various issues.

* [DarioSamo](https://github.com/DarioSamo) : for providing important fixes to the renderer and information about the inner workings of the game graphics system.
* [garrettjoecox](https://github.com/garrettjoecox) : for contributing with interpolation fixes to this port.
* [inspectredc](https://github.com/inspectredc) : for contributing to the [SF64 decompilation project](https://github.com/sonicdcer/sf64).
* [Lywx](https://github.com/KiritoDv) : for co-developing this port as a lead and creating [Torch](https://github.com/HarbourMasters/Torch) asset extraction system.
* [m4xw](https://github.com/m4xw) : for helping with audio issues in this port.
* [Malkierian](https://github.com/Malkierian) : for contributing with important fixes to this port.
* [petrie911](https://github.com/petrie911) : for contributing to the [SF64 decompilation project](https://github.com/sonicdcer/sf64) as a lead.
* [Ryan-Myers](https://github.com/Ryan-Myers) : for contributing to the [SF64 decompilation project](https://github.com/sonicdcer/sf64).
* [Thar0](https://github.com/Thar0) : for contributing with an improved Starfield that can be interpolated to any framerate.
* [TheBoy181](https://github.com/TheBoy181) : for contributing to this project with various widescreen enhancements such as level floors, an extended Starfield among other things.
* [Wiseguy](https://github.com/Mr-Wiseguy) : for providing important information about the inner workings of the N64 platform, as well as helping with the decompilation process.
