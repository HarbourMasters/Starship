#ifndef BUILD_H
#define BUILD_H

#include <libultraship/libultra.h>
#include "macros.h"

// Version information
extern_s char gBuildVersion[];
extern_s u16 gBuildVersionMajor;
extern_s u16 gBuildVersionMinor;
extern_s u16 gBuildVersionPatch;

extern_s char gGitBranch[];
extern_s char gGitCommitHash[];
extern_s char gGitCommitTag[];
extern_s char gBuildTeam[];
extern_s char gBuildDate[];
extern_s char gBuildMakeOption[];

#endif
