#include "assets/filesystem.h"
#include "assets/archive.h"
#include "core/logging.h"
#include <stdlib.h>

// Virtual filesystem that can mount multiple archives

typedef struct {
    IArchive** archives;
    int archiveCount;
    int archiveCapacity;
} FileSystemData;

static int fsFileExists(IFileSystem* self, const char* path) {
    FileSystemData* data = (FileSystemData*)self->userData;
    
    for (int i = 0; i < data->archiveCount; i++) {
        if (data->archives[i]->fileExists(data->archives[i], path)) {
            return 1;
        }
    }
    
    return 0;
}

static int fsReadFile(IFileSystem* self, const char* path, void** buffer, int* size) {
    FileSystemData* data = (FileSystemData*)self->userData;
    
    for (int i = 0; i < data->archiveCount; i++) {
        int result = data->archives[i]->readFile(data->archives[i], path, buffer, size);
        if (result == 0) {
            return 0; // Success
        }
    }
    
    return -1; // File not found
}

static void fsFreeBuffer(IFileSystem* self, void* buffer) {
    if (buffer) {
        free(buffer);
    }
}

IFileSystem* filesystemCreate(void) {
    IFileSystem* fs = (IFileSystem*)malloc(sizeof(IFileSystem));
    FileSystemData* data = (FileSystemData*)malloc(sizeof(FileSystemData));
    
    data->archiveCapacity = 16;
    data->archiveCount = 0;
    data->archives = (IArchive**)malloc(sizeof(IArchive*) * data->archiveCapacity);
    
    fs->userData = data;
    fs->fileExists = fsFileExists;
    fs->readFile = fsReadFile;
    fs->freeBuffer = fsFreeBuffer;
    
    return fs;
}

void filesystemDestroy(IFileSystem* fs) {
    if (fs && fs->userData) {
        FileSystemData* data = (FileSystemData*)fs->userData;
        
        for (int i = 0; i < data->archiveCount; i++) {
            archiveDestroyMPQ(data->archives[i]);
        }
        
        free(data->archives);
        free(data);
        free(fs);
    }
}

void filesystemAddArchive(IFileSystem* fs, const char* archivePath) {
    if (!fs || !fs->userData) return;
    
    FileSystemData* data = (FileSystemData*)fs->userData;
    
    if (data->archiveCount >= data->archiveCapacity) {
        logWarning("Filesystem archive capacity reached");
        return;
    }
    
    IArchive* archive = archiveCreateMPQ();
    if (archive->open(archive, archivePath) == 0) {
        data->archives[data->archiveCount++] = archive;
        logInfo("Archive mounted");
    } else {
        archiveDestroyMPQ(archive);
        logError("Failed to mount archive");
    }
}
