#include "sys.h"
#include "sf64audio_provisional.h"
#include "audiothread_cmd.h"

void AudioThread_ProcessCmds(u32 msg);
void AudioThread_SetFadeOutTimer(s32 seqPlayId, s32 fadeTime);
void AudioThread_SetFadeInTimer(s32 seqPlayId, s32 fadeTime);

OSMesgQueue sAudioTaskStartQueue;
OSMesgQueue sThreadCmdProcQueue;
OSMesgQueue sAudioSpecQueue;
OSMesgQueue sAudioResetQueue;
AudioCmd gThreadCmdBuffer[256];
OSMesg sAudioTaskStartMsg[1];
OSMesg sThreadCmdProcMsg[4];
OSMesg sAudioSpecMsg[1];
OSMesg sAudioResetMsg[1];

u8 gThreadCmdWritePos = 0;
u8 gThreadCmdReadPos = 0;
OSMesgQueue* gAudioTaskStartQueue = &sAudioTaskStartQueue;
OSMesgQueue* gThreadCmdProcQueue = &sThreadCmdProcQueue;
OSMesgQueue* gAudioSpecQueue = &sAudioSpecQueue;
OSMesgQueue* gAudioResetQueue = &sAudioResetQueue;

static const char devstr0[] = "DAC:Lost 1 Frame.\n";
static const char devstr1[] = "DMA: Request queue over.( %d )\n";
static const char devstr2[] = "Spec Change Override. %d -> %d\n";
static const char devstr3[] = "Audio:now-max tasklen is %d / %d\n";
static const char devstr4[] = "Audio:Warning:ABI Tasklist length over (%d)\n";
static const char devstr5[] = "BGLOAD Start %d\n";
static const char devstr6[] = "Error: OverFlow Your Request\n";
static const char devstr7[] = "---AudioSending (%d->%d) \n";
static const char devstr8[] = "AudioSend: %d -> %d (%d)\n";
static const char devstr9[] = "Continue Port\n";
static const char devstr10[] = "%d -> %d\n";
static const char devstr11[] = "Sync-Frame  Break. (Remain %d)\n";
static const char devstr12[] = "Undefined Port Command %d\n";
static const char devstr13[] = "specchg conjunction error (Msg:%d Cur:%d)\n";
static const char devstr14[] = "Error : Queue is not empty ( %x ) \n";

void AudioThread_CreateNextAudioBuffer(s16* samples, u32 num_samples) {
    static s32 gMaxAbiCmdCnt = 128;
    static SPTask* gWaitingAudioTask = NULL;
    s32 abiCmdCount;
    OSMesg specId;
    OSMesg msg;

    gCurAiBuffIndex++;
    gCurAiBuffIndex %= 3;

    gCurAudioFrameDmaCount = 0;
    AudioLoad_DecreaseSampleDmaTtls();
    AudioLoad_ProcessLoads(gAudioResetStep);

    if (osRecvMesg(gAudioSpecQueue, &specId, 0) != -1) {
        if (gAudioResetStep == 0) {
            gAudioResetStep = 5;
        }
        gAudioSpecId = specId.data8;
    }

    if ((gAudioResetStep != 0) && (AudioHeap_ResetStep() == 0)) {
        if (gAudioResetStep == 0) {
            osSendMesg8(gAudioResetQueue, gAudioSpecId, OS_MESG_NOBLOCK);
        }
        gWaitingAudioTask = NULL;
        return;
    }

    if (gAudioResetTimer > 16) {
        return;
    }
    if (gAudioResetTimer != 0) {
        gAudioResetTimer++;
    }

    while (MQ_GET_MESG(gThreadCmdProcQueue, &msg)) {
        AudioThread_ProcessCmds(msg.data32);
    }

    AudioSynth_Update(gCurAbiCmdBuffer, &abiCmdCount, samples, num_samples);

    // Spectrum Analyzer fix
    memcpy(gAiBuffers[gCurAiBuffIndex], samples, num_samples);

    gAudioRandom = osGetCount() * (gAudioRandom + gAudioTaskCountQ);
}

// Original function, unused in the port.
SPTask* AudioThread_CreateTask() {
    static s32 gMaxAbiCmdCnt = 128;
    static SPTask* gWaitingAudioTask = NULL;
    u32 aiSamplesLeft;
    s32 abiCmdCount;
    s32 aiBuffIndex;
    s32 pad48;
    OSTask_t* task;
    u16* aiBuffer;
    s32 pad3C;
    u32 specId;
    u32 msg;
    s32 pad30;

    gAudioTaskCountQ++;
    if ((gAudioTaskCountQ % gAudioBufferParams.numBuffers) != 0) {
        return gWaitingAudioTask;
    }
    osSendMesg(gAudioTaskStartQueue, OS_MESG_32(gAudioTaskCountQ), OS_MESG_NOBLOCK);
    gAudioTaskIndexQ ^= 1;
    gCurAiBuffIndex++;
    gCurAiBuffIndex %= 3;

    aiBuffIndex = (gCurAiBuffIndex + 1) % 3;
    aiSamplesLeft = osAiGetLength() / 4;

    if ((gAudioResetTimer < 16) && (gAiBuffLengths[aiBuffIndex] != 0)) {
        osAiSetNextBuffer(gAiBuffers[aiBuffIndex], gAiBuffLengths[aiBuffIndex] * 4);
    }

    if (gCurAudioFrameDmaCount && gCurAudioFrameDmaCount) {} //! FAKE ?

    gCurAudioFrameDmaCount = 0;
    AudioLoad_DecreaseSampleDmaTtls();
    AudioLoad_ProcessLoads(gAudioResetStep);

    if (MQ_GET_MESG(gAudioSpecQueue, &specId)) {
        if (gAudioResetStep == 0) {
            gAudioResetStep = 5;
        }
        gAudioSpecId = specId;
    }

    if ((gAudioResetStep != 0) && (AudioHeap_ResetStep() == 0)) {
        if (gAudioResetStep == 0) {
            osSendMesg(gAudioResetQueue, OS_MESG_32((s32) gAudioSpecId), OS_MESG_NOBLOCK);
        }
        gWaitingAudioTask = NULL;
        return NULL;
    }

    if (gAudioResetTimer > 16) {
        return NULL;
    }
    if (gAudioResetTimer != 0) {
        gAudioResetTimer++;
    }

    gAudioCurTask = &gAudioRspTasks[gAudioTaskIndexQ];
    gCurAbiCmdBuffer = gAbiCmdBuffs[gAudioTaskIndexQ];
    aiBuffIndex = gCurAiBuffIndex;
    aiBuffer = gAiBuffers[aiBuffIndex];
    gAiBuffLengths[aiBuffIndex] = ALIGN16_ALT(gAudioBufferParams.samplesPerFrameTarget - aiSamplesLeft + 0x80);

    if (gAiBuffLengths[aiBuffIndex] < gAudioBufferParams.minAiBufferLength) {
        gAiBuffLengths[aiBuffIndex] = gAudioBufferParams.minAiBufferLength;
    }
    if (gAiBuffLengths[aiBuffIndex] > gAudioBufferParams.maxAiBufferLength) {
        gAiBuffLengths[aiBuffIndex] = gAudioBufferParams.maxAiBufferLength;
    }
    while (MQ_GET_MESG(gThreadCmdProcQueue, &msg)) {
        AudioThread_ProcessCmds(msg);
    }
    gCurAbiCmdBuffer = AudioSynth_Update(gCurAbiCmdBuffer, &abiCmdCount, aiBuffer, gAiBuffLengths[aiBuffIndex]);
    gAudioRandom = osGetCount() * (gAudioRandom + gAudioTaskCountQ);
    gAudioRandom = gAiBuffers[aiBuffIndex][gAudioTaskCountQ & 0xFF] + gAudioRandom;

    aiBuffIndex = gAudioTaskIndexQ;

    gAudioCurTask->msg = OS_MESG_PTR(NULL);

    task = &gAudioCurTask->task.t;

    task->type = 2;
    task->flags = 0;
    // task->ucode_boot = rspbootTextStart;
    // task->ucode_boot_size = (uintptr_t) rspbootTextEnd - (uintptr_t) rspbootTextStart;
    //
    // task->ucode = aspMainTextStart;
    // task->ucode_data = aspMainDataStart;
    // task->ucode_size = SP_UCODE_SIZE;
    // task->ucode_data_size = (aspMainDataEnd - aspMainDataStart) * 8;

    task->dram_stack = NULL;
    task->dram_stack_size = 0;

    task->output_buff = NULL;
    task->output_buff_size = NULL;
    if (1) {}
    task->data_ptr = (u64*) gAbiCmdBuffs[aiBuffIndex];
    task->data_size = abiCmdCount * sizeof(Acmd);

    task->yield_data_ptr = NULL;
    task->yield_data_size = 0;

    if (gMaxAbiCmdCnt < abiCmdCount) {
        gMaxAbiCmdCnt = abiCmdCount;
    }

    if (gAudioBufferParams.numBuffers == 1) {
        return gAudioCurTask;
    } else {
        gWaitingAudioTask = gAudioCurTask;
        return NULL;
    }
}

void AudioThread_ProcessGlobalCmd(AudioCmd* cmd) {
    s32 i;

    switch (cmd->op) {
        case AUDIOCMD_OP_GLOBAL_SYNC_LOAD_SEQ_PARTS:
            AudioLoad_SyncLoadSeqParts(cmd->arg1, 3);
            break;
        case AUDIOCMD_OP_GLOBAL_INIT_SEQPLAYER:
        case AUDIOCMD_OP_GLOBAL_INIT_SEQPLAYER_ALT:
            AudioLoad_SyncInitSeqPlayer(cmd->arg0, cmd->arg1, cmd->arg2);
            AudioThread_SetFadeInTimer(cmd->arg0, (uintptr_t) cmd->data);
            break;
        case AUDIOCMD_OP_GLOBAL_DISABLE_SEQPLAYER:
            if (gSeqPlayers[cmd->arg0].enabled) {
                if (cmd->asInt == 0) {
                    AudioSeq_SequencePlayerDisable(&gSeqPlayers[cmd->arg0]);
                } else {
                    AudioThread_SetFadeOutTimer(cmd->arg0, cmd->asInt);
                }
            }
            break;
        case AUDIOCMD_OP_GLOBAL_UNK_84:
            break;
        case AUDIOCMD_OP_GLOBAL_SET_SOUND_MODE:
            gAudioSoundMode = cmd->asUInt;
            break;
        case AUDIOCMD_OP_GLOBAL_MUTE:
            for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
                SequencePlayer* seqplayer = &gSeqPlayers[i];

                seqplayer->muted = true;
                seqplayer->recalculateVolume = true;
            }
            break;
        case AUDIOCMD_OP_GLOBAL_UNMUTE:
            if (cmd->asUInt == 1) {
                for (i = 0; i < gNumNotes; i++) {
                    Note* note = &gNotes[i];
                    NoteSubEu* noteSub = &note->noteSubEu;

                    if ((noteSub->bitField0.enabled) && (note->playbackState.unk_04 == 0) &&
                        (note->playbackState.parentLayer != NO_LAYER) &&
                        (note->playbackState.parentLayer->channel->muteBehavior & 8)) {
                        noteSub->bitField0.finished = true;
                    }
                }
            }
            for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
                SequencePlayer* seqplayer = &gSeqPlayers[i];

                seqplayer->muted = false;
                seqplayer->recalculateVolume = true;
            }
            break;
        case AUDIOCMD_OP_GLOBAL_SYNC_LOAD_INSTRUMENT:
            AudioLoad_SyncLoadInstrument(cmd->arg0, cmd->arg1, cmd->arg2);
            break;
        case AUDIOCMD_OP_GLOBAL_ASYNC_LOAD_SAMPLE_BANK:
            AudioLoad_AsyncLoadSampleBank(cmd->arg0, cmd->arg1, cmd->arg2, &gExternalLoadQueue);
            break;
        case AUDIOCMD_OP_GLOBAL_ASYNC_LOAD_FONT:
            AudioLoad_AsyncLoadSeq(cmd->arg0, cmd->arg1, cmd->arg2, &gExternalLoadQueue);
            break;
        case AUDIOCMD_OP_GLOBAL_DISCARD_SEQ_FONTS:
            AudioLoad_DiscardSeqFonts(cmd->arg1);
            break;
    }
}

void AudioThread_SetFadeOutTimer(s32 seqPlayId, s32 fadeTime) {
    if (fadeTime == 0) {
        fadeTime = 1;
    }

    gSeqPlayers[seqPlayId].state = 2;
    gSeqPlayers[seqPlayId].fadeTimer = fadeTime;
    gSeqPlayers[seqPlayId].fadeVelocity = -(gSeqPlayers[seqPlayId].fadeVolume / fadeTime);
}

void AudioThread_SetFadeInTimer(s32 seqPlayId, s32 fadeTime) {
    if (fadeTime != 0) {
        gSeqPlayers[seqPlayId].state = 1;
        gSeqPlayers[seqPlayId].fadeTimerUnkEu = fadeTime;
        gSeqPlayers[seqPlayId].fadeTimer = fadeTime;
        gSeqPlayers[seqPlayId].fadeVolume = 0.0f;
        gSeqPlayers[seqPlayId].fadeVelocity = 0.0f;
    }
}

void AudioThread_InitQueues(void) {
    gThreadCmdWritePos = 0;
    gThreadCmdReadPos = 0;
    osCreateMesgQueue(gAudioTaskStartQueue, sAudioTaskStartMsg, 1);
    osCreateMesgQueue(gThreadCmdProcQueue, sThreadCmdProcMsg, 4);
    osCreateMesgQueue(gAudioSpecQueue, sAudioSpecMsg, 1);
    osCreateMesgQueue(gAudioResetQueue, sAudioResetMsg, 1);
}

void AudioThread_QueueCmd(AudioCmd cmd) {
    AudioCmd* audioCmd = &gThreadCmdBuffer[gThreadCmdWritePos & 0xFF];

    *audioCmd = cmd;

    gThreadCmdWritePos++;
    if (gThreadCmdWritePos == gThreadCmdReadPos) {
        gThreadCmdWritePos--;
    }
}

void AudioThread_QueueCmdPtr(u32 opArgs, void* data) {
    AudioCmd cmd = {
        .opArgs = opArgs,
        .asPtr = data,
    };
    AudioThread_QueueCmd(cmd);
}

void AudioThread_QueueCmdF32(u32 opArgs, f32 val) {
    AudioCmd cmd = { .opArgs = opArgs, .asFloat = val };
    AudioThread_QueueCmd(cmd);
}

void AudioThread_QueueCmdS32(u32 opArgs, u32 val) {
    AudioCmd cmd = { .opArgs = opArgs, .asInt = val };
    AudioThread_QueueCmd(cmd);
}

void AudioThread_QueueCmdS8(u32 opArgs, s8 val) {
    AudioCmd cmd = { .opArgs = opArgs, .asSbyte = val };
    AudioThread_QueueCmd(cmd);
}

void AudioThread_ScheduleProcessCmds(void) {
    static s32 D_800C7C70 = 0;
    s32 msg;

    if (D_800C7C70 < (u8) (gThreadCmdWritePos - gThreadCmdReadPos + 0x100)) {
        D_800C7C70 = (u8) (gThreadCmdWritePos - gThreadCmdReadPos + 0x100);
    }
    msg = (((gThreadCmdReadPos & 0xFF) << 8) | (gThreadCmdWritePos & 0xFF));
    osSendMesg(gThreadCmdProcQueue, OS_MESG_32(msg), OS_MESG_NOBLOCK);
    gThreadCmdReadPos = gThreadCmdWritePos;
}

void AudioThread_ResetCmdQueue(void) {
    gThreadCmdReadPos = gThreadCmdWritePos;
}

void AudioThread_ProcessCmds(u32 msg) {
    static u8 gCurCmdReadPos = 0;
    static u8 gThreadCmdQueueFinished = false;
    AudioCmd* cmd;
    SequenceChannel* channel;
    SequencePlayer* player;
    u8 writePos;

    if (!gThreadCmdQueueFinished) {
        gCurCmdReadPos = (msg >> 8) & 0xFF;
    }
    writePos = msg & 0xFF;
    while (true) {

        if (gCurCmdReadPos == writePos) {
            gThreadCmdQueueFinished = 0;
            break;
        }

        cmd = &gThreadCmdBuffer[gCurCmdReadPos & 0xFF];
        gCurCmdReadPos++;
        if (cmd->op == AUDIOCMD_OP_GLOBAL_STOP_AUDIOCMDS) {
            gThreadCmdQueueFinished = true;
            break;
        }
        if ((cmd->op & 0xF0) == 0xF0) {
            AudioThread_ProcessGlobalCmd(cmd);
        } else if (cmd->arg0 < ARRAY_COUNT(gSeqPlayers)) {
            player = &gSeqPlayers[cmd->arg0];
            if (cmd->op & 0x80) {
                AudioThread_ProcessGlobalCmd(cmd);
            } else if (cmd->op & 0x40) {
                switch (cmd->op) {
                    case AUDIOCMD_OP_SEQPLAYER_FADE_VOLUME_SCALE:
                        if (player->fadeVolumeMod != cmd->asFloat) {
                            player->fadeVolumeMod = cmd->asFloat;
                            player->recalculateVolume = true;
                        }
                        break;
                    case AUDIOCMD_OP_SEQPLAYER_SET_TEMPO:
                        player->tempo = cmd->asInt * 48;
                        break;
                    case AUDIOCMD_OP_SEQPLAYER_SET_TRANSPOSITION:
                        player->transposition = cmd->asSbyte;
                        break;
                    case AUDIOCMD_OP_SEQPLAYER_SET_IO:
                        player->unk_07[cmd->arg2] = cmd->asSbyte;
                        break;
                }
            } else if ((player->enabled) && (cmd->arg1 < 16)) {
                channel = player->channels[cmd->arg1];
                if (IS_SEQUENCE_CHANNEL_VALID(channel)) {
                    switch (cmd->op) {
                        case AUDIOCMD_OP_CHANNEL_SET_VOL_SCALE:
                            if (channel->volumeMod != cmd->asFloat) {
                                channel->volumeMod = cmd->asFloat;
                                channel->changes.s.volume = true;
                            }
                            break;
                        case AUDIOCMD_OP_CHANNEL_SET_VOL:
                            if (channel->volume != cmd->asFloat) {
                                channel->volume = cmd->asFloat;
                                channel->changes.s.volume = true;
                            }
                            break;
                        case AUDIOCMD_OP_CHANNEL_SET_PAN:
                            if (channel->newPan != cmd->asSbyte) {
                                channel->newPan = cmd->asSbyte;
                                channel->changes.s.pan = true;
                            }
                            break;
                        case AUDIOCMD_OP_CHANNEL_SET_FREQ_SCALE:
                            if (channel->freqMod != cmd->asFloat) {
                                channel->freqMod = cmd->asFloat;
                                channel->changes.s.freqMod = true;
                            }
                            break;
                        case AUDIOCMD_OP_CHANNEL_SET_REVERB_VOLUME:
                            if (channel->targetReverbVol != cmd->asSbyte) {
                                channel->targetReverbVol = cmd->asSbyte;
                            }
                            break;
                        case AUDIOCMD_OP_CHANNEL_SET_IO:
                            if (cmd->arg2 < 8) {
                                channel->seqScriptIO[cmd->arg2] = cmd->asSbyte;
                            }
                            break;
                        case AUDIOCMD_OP_CHANNEL_SET_MUTE:
                            channel->muted = cmd->asSbyte;
                            break;
                    }
                }
            }
        }
        cmd->op = 0;
    }
}

u32 AudioThread_GetAsyncLoadStatus(u32* outData) {
    u32 loadStatus = 2;
    *outData = loadStatus & 0xFFFFFF;
    return loadStatus >> 0x18;
}

u8* AudioThread_GetFontsForSequence(s32 seqId, u32* outNumFonts) {
    return AudioLoad_GetFontsForSequence(seqId, outNumFonts);
}

bool AudioThread_ResetComplete(void) {
    s32 pad;
    OSMesg sp18;

    if (!MQ_GET_MESG(gAudioResetQueue, &sp18)) {
        return false;
    }
    if (sp18.data8 != gAudioSpecId) {
        return false;
    }
    return true;
}

void AudioThread_ResetAudioHeap(s32 specId) {
    OSMesg msg;
    msg.data8 = specId & 0xFF;
    MQ_CLEAR_QUEUE(gAudioResetQueue);

    AudioThread_ResetCmdQueue();
    osSendMesg8(gAudioSpecQueue, msg.data8, OS_MESG_NOBLOCK);
}

void AudioThread_PreNMIReset(void) {
    gAudioResetTimer = 1;
    AudioThread_ResetAudioHeap(AUDIOSPEC_CO);
    gAudioResetStep = 0;
}

void AudioThread_Init(void) {
    AudioThread_InitQueues();
}
