#pragma once

#include "global.h"
#include "sf64audio_provisional.h"

// ────────────────────────────────────────────────────────────────────────────
// Display events — game thread
// ────────────────────────────────────────────────────────────────────────────

// Fires at the very start of the display update, before any game logic runs.
DEFINE_EVENT(DisplayPreUpdateEvent);

// Fires at the very end of the display update, after all game logic has run.
DEFINE_EVENT(DisplayPostUpdateEvent);

// ────────────────────────────────────────────────────────────────────────────
// Game loop events — game thread
// ────────────────────────────────────────────────────────────────────────────

// Fires at the start of the main game update tick.
DEFINE_EVENT(GamePreUpdateEvent);

// Fires at the end of the main game update tick.
DEFINE_EVENT(GamePostUpdateEvent);

// Fires during the play-state update (active gameplay, not menus).
DEFINE_EVENT(PlayUpdateEvent);

// ────────────────────────────────────────────────────────────────────────────
// Player events — game thread
// ────────────────────────────────────────────────────────────────────────────

// Fires before the player entity is updated.
//   player — the player being updated
DEFINE_EVENT(PlayerPreUpdateEvent,
    Player* player;
);

// Fires after the player entity is updated.
//   player — the player that was updated
DEFINE_EVENT(PlayerPostUpdateEvent,
    Player* player;
);

// ────────────────────────────────────────────────────────────────────────────
// HUD / radar draw events — game thread
// ────────────────────────────────────────────────────────────────────────────

// Fires before the radar HUD element is drawn. Cancel to suppress default drawing.
DEFINE_EVENT(DrawRadarHUDEvent);

// Fires before an Arwing blip is drawn on the radar.
//   colorIdx — palette index used for this blip
DEFINE_EVENT(DrawRadarMarkArwingEvent,
    s32 colorIdx;
);

// Fires before a Wolfen blip is drawn on the radar. Cancel to suppress.
DEFINE_EVENT(DrawRadarMarkWolfenEvent);

// Fires before the boost gauge is drawn. Cancel to suppress default drawing.
DEFINE_EVENT(DrawBoostGaugeHUDEvent);

// Fires before the bomb counter is drawn. Cancel to suppress default drawing.
DEFINE_EVENT(DrawBombCounterHUDEvent);

// Fires before the incoming-message indicator is drawn. Cancel to suppress.
DEFINE_EVENT(DrawIncomingMsgHUDEvent);

// Fires before the radio message box is set up.
//   radioRedBox — pointer to the red-box flag; write to force a specific style
DEFINE_EVENT(PreSetupRadioMsgEvent,
    s32* radioRedBox;
);

// Fires before the gold rings counter is drawn. Cancel to suppress.
DEFINE_EVENT(DrawGoldRingsHUDEvent);

// Fires before the lives counter is drawn. Cancel to suppress.
DEFINE_EVENT(DrawLivesCounterHUDEvent);

// Fires before the training ring pass counter is drawn. Cancel to suppress.
DEFINE_EVENT(DrawTrainingRingPassCountHUDEvent);

// Fires before the edge-direction arrows are drawn. Cancel to suppress.
DEFINE_EVENT(DrawEdgeArrowsHUDEvent);

// Fires before the boss health bar is drawn. Cancel to suppress.
DEFINE_EVENT(DrawBossHealthHUDEvent);

// Fires before the global HUD layer is drawn (outermost pre-draw hook).
DEFINE_EVENT(DrawGlobalHUDPreEvent);

// Fires after the global HUD layer has been drawn (outermost post-draw hook).
DEFINE_EVENT(DrawGlobalHUDPostEvent);

// ────────────────────────────────────────────────────────────────────────────
// Engine UI events — render thread
// ────────────────────────────────────────────────────────────────────────────

// Fires when the engine renders its ImGui menubar. Add custom menu items here.
DEFINE_EVENT(EngineRenderMenubarEvent);

// Fires when the engine renders the mods panel. Add custom ImGui widgets here.
DEFINE_EVENT(EngineRenderModsEvent);

// ────────────────────────────────────────────────────────────────────────────
// Audio — voice events
// These fire on the GAME THREAD (PlayVoiceEvent, ClearVoiceEvent) or the
// AUDIO THREAD (UpdateVoiceEvent, GetCurrentVoiceEvent, GetVoiceStatusEvent).
// Do not access non-thread-safe state from the wrong thread.
// ────────────────────────────────────────────────────────────────────────────

// Fires when a voice line is requested. GAME THREAD.
// The VoiceEnhancements mod listens here to load a replacement PCM sample.
//   msgId — the voice message ID (matches ast_radio/gMsg_ID_XXXX resource names)
DEFINE_EVENT(PlayVoiceEvent,
    s32 msgId;
);

// Fires once per audio frame while a voice line is active. AUDIO THREAD.
// Set *finished = true to signal that custom playback has completed so the
// engine restores BGM volume and clears the voice state.
//   finished — write true to mark the override as done
DEFINE_EVENT(UpdateVoiceEvent,
    bool* finished;
);

// Fires when the engine queries the currently playing voice ID. AUDIO THREAD.
// Write the current msgId into *result to override the default channel-scan
// logic (used for mouth animation and BGM-restore gating).
//   result — write the active msgId here, or leave at -1 for default behaviour
DEFINE_EVENT(GetCurrentVoiceEvent,
    s32* result;
);

// Fires when the engine queries the voice playback status for mouth animation.
// AUDIO THREAD. Write one of: 0 = silent, 1 = speaking, 2 = finished.
//   result — write the desired mouth-animation state, or leave at -1 for default
DEFINE_EVENT(GetVoiceStatusEvent,
    s32* result;
);

// Fires when voice playback is cleared (e.g. on scene transition). GAME THREAD.
// Use to reset any per-voice override state.
DEFINE_EVENT(ClearVoiceEvent);

// ────────────────────────────────────────────────────────────────────────────
// Audio — sequence / BGM events — GAME THREAD
// Cancellable: set event->Event.Cancelled = true to block the operation.
// Mutable fields (pointers): write through them to change the value that the
// engine will use before the SEQCMD is dispatched.
// ────────────────────────────────────────────────────────────────────────────

// Fires inside Audio_PlaySequence before the SEQCMD is queued. Cancellable.
// Write *seqId to redirect playback to a different sequence.
// Cancel to suppress playback entirely (e.g. when substituting custom audio).
//   seqPlayId  — which sequence player (SEQ_PLAYER_BGM, SEQ_PLAYER_FANFARE, …)
//   seqId      — mutable pointer to the sequence ID; write to remap
//   fadeinTime — fade-in duration in audio frames
//   bgmParam   — extra BGM parameter passed via SEQCMD_SET_SEQPLAYER_IO
DEFINE_EVENT(PlaySequenceEvent,
    u8   seqPlayId;
    u16* seqId;
    u8   fadeinTime;
    u8   bgmParam;
);

// Fires inside Audio_PlayFanfare before the SEQCMD is queued. Cancellable.
// Write *seqId to redirect playback to a different fanfare sequence.
//   seqId          — mutable pointer to the fanfare sequence ID; write to remap
//   bgmVolume      — BGM volume level during fanfare playback
//   bgmFadeoutTime — frames to fade the BGM out before the fanfare starts
//   bgmFadeinTime  — frames to restore BGM volume after the fanfare ends
DEFINE_EVENT(PlayFanfareEvent,
    u16* seqId;
    u8   bgmVolume;
    u8   bgmFadeoutTime;
    u8   bgmFadeinTime;
);

// Fires inside Audio_StopSequence before the player is disabled. Cancellable.
// Cancel to keep the sequence running (e.g. when a custom music system owns
// the player and handles stopping itself).
//   seqPlayId   — which sequence player is being stopped
//   fadeOutTime — fade-out duration in audio frames
DEFINE_EVENT(StopSequenceEvent,
    u8  seqPlayId;
    u16 fadeOutTime;
);

// Fires inside Audio_SetSequenceFade before the fade values are committed.
// Cancellable. Modify *fadeMod or *fadeTime to alter the fade curve.
//   seqPlayId  — which sequence player is being faded
//   fadeModId  — which fade-mod slot is being written (0 = primary volume)
//   fadeMod    — mutable target volume level [0, 127]
//   fadeTime   — mutable fade duration in audio frames
DEFINE_EVENT(SetSequenceFadeEvent,
    u8  seqPlayId;
    u8  fadeModId;
    u8* fadeMod;
    u8* fadeTime;
);

// ────────────────────────────────────────────────────────────────────────────
// Audio — SFX event — GAME THREAD — Cancellable
// ────────────────────────────────────────────────────────────────────────────

// Fires inside Audio_PlaySfx before the request is enqueued. Cancellable.
// Write *sfxId to remap to a different sound effect.
// freqMod / volMod / reverbAdd are double-pointers: you may point them at your
// own variables to fully replace the modulator without copying values.
// Cancel to suppress the sound entirely.
//   sfxId     — mutable sound effect ID; write to remap
//   sfxSource — 3-float world-space position of the sound source
//   token     — bank slot / token used for kill-by-source operations
//   freqMod   — pointer-to-pointer to the pitch multiplier (1.0 = normal)
//   volMod    — pointer-to-pointer to the volume multiplier (1.0 = full)
//   reverbAdd — pointer-to-pointer to the reverb addend (signed byte)
DEFINE_EVENT(PlaySfxEvent,
    u32*  sfxId;
    f32*  sfxSource;
    u8    token;
    f32** freqMod;
    f32** volMod;
    s8**  reverbAdd;
);

// ────────────────────────────────────────────────────────────────────────────
// Audio — volume / spec events — GAME THREAD
// ────────────────────────────────────────────────────────────────────────────

// Fires inside Audio_SetVolume after the [0, 99] clamp, before the value is
// stored. Cancellable. Write *volume to apply a different final value.
//   audioType — AUDIO_TYPE_MUSIC, AUDIO_TYPE_SFX, or AUDIO_TYPE_VOICE
//   volume    — mutable volume in [0, 99]
DEFINE_EVENT(SetVolumeEvent,
    u8  audioType;
    u8* volume;
);

// Fires inside Audio_SetAudioSpec before SEQCMD_RESET_AUDIO_HEAP is issued.
// Not cancellable — the spec change must proceed to keep audio in sync.
// Write *specId or *sfxChannelLayout to redirect the engine to a different
// audio spec (e.g. to load a custom instrument bank for a modded level).
//   sfxChannelLayout — mutable SFX channel layout byte (high byte of specParam)
//   specId           — mutable audio spec ID (low byte of specParam)
DEFINE_EVENT(SetAudioSpecEvent,
    u8* sfxChannelLayout;
    u8* specId;
);

// ────────────────────────────────────────────────────────────────────────────
// Audio — per-frame tick — GAME THREAD
// ────────────────────────────────────────────────────────────────────────────

// Fires at the end of Audio_Update every frame, after SFX, sequences, voice,
// and the audio thread command queue have all been processed.
// Use for per-frame audio mod work that must run in lockstep with the game.
// Not cancellable.
DEFINE_EVENT(AudioUpdateEvent);

// ────────────────────────────────────────────────────────────────────────────
// Audio — note-level hooks — AUDIO THREAD
// These fire deep inside the sequence player on the audio thread.
// Do not call any game-thread APIs or take game-thread locks here.
// ────────────────────────────────────────────────────────────────────────────

// Fires just before a note is allocated for a sequence layer.
// Used by VoiceEnhancements to swap layer->tunedSample for a custom PCM buffer
// and to adjust layer->freqMod for sample-rate matching.
//   layer   — the sequence layer that is about to trigger a note
//   channel — the channel that owns this layer
DEFINE_EVENT(SeqLayerPreNoteEvent,
    SequenceLayer*  layer;
    SequenceChannel* channel;
);

// Fires immediately after a note has been allocated for a sequence layer.
// Used by VoiceEnhancements to pin delay/gateDelay so the engine does not
// cut the custom sample short.
//   layer — the layer whose note was just allocated
DEFINE_EVENT(SeqLayerPostNoteEvent,
    SequenceLayer* layer;
);
