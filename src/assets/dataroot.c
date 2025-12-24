#include "assets/dataroot.h"
#include "core/platform.h"
#include "core/logging.h"
#include <pspkernel.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Expected Diablo II file structure
static const char* requiredFiles[] = {
    "d2data.mpq",
    "d2char.mpq",
    "d2sfx.mpq",
    "d2music.mpq",
    "d2video.mpq",
    "d2exp.mpq"
};

static const int requiredFileCount = sizeof(requiredFiles) / sizeof(requiredFiles[0]);

void datarootInit(void) {
    logInfo("Data root initialized");
    
    // Create userdata directory if it doesn't exist
    sceIoMkdir(platformGetUserDataDir(), 0777);
    sceIoMkdir(platformGetGameDataDir(), 0777);
}

void datarootShutdown(void) {
    logInfo("Data root shutdown");
}

DataCheckResult datarootCheckFiles(void) {
    DataCheckResult result;
    result.fileCount = requiredFileCount;
    result.filePaths = (char**)malloc(sizeof(char*) * requiredFileCount);
    result.fileStatus = (int*)malloc(sizeof(int) * requiredFileCount);
    
    for (int i = 0; i < requiredFileCount; i++) {
        char fullPath[512];
        snprintf(fullPath, sizeof(fullPath), "%s%s", 
                 platformGetGameDataDir(), requiredFiles[i]);
        
        // Allocate and copy path
        result.filePaths[i] = (char*)malloc(strlen(fullPath) + 1);
        strcpy(result.filePaths[i], fullPath);
        
        // Check if file exists
        int fd = sceIoOpen(fullPath, PSP_O_RDONLY, 0777);
        if (fd >= 0) {
            result.fileStatus[i] = 1;
            sceIoClose(fd);
        } else {
            result.fileStatus[i] = 0;
        }
    }
    
    return result;
}

void datarootFreeCheckResult(DataCheckResult* result) {
    if (result) {
        if (result->filePaths) {
            for (int i = 0; i < result->fileCount; i++) {
                if (result->filePaths[i]) {
                    free(result->filePaths[i]);
                }
            }
            free(result->filePaths);
        }
        if (result->fileStatus) {
            free(result->fileStatus);
        }
    }
}

const char* datarootResolve(const char* relativePath) {
    static char resolvedPath[512];
    snprintf(resolvedPath, sizeof(resolvedPath), "%s%s",
             platformGetGameDataDir(), relativePath);
    return resolvedPath;
}
