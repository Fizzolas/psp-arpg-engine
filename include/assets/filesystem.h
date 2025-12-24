#ifndef ASSETS_FILESYSTEM_H
#define ASSETS_FILESYSTEM_H

// Virtual filesystem abstraction

typedef struct IFileSystem IFileSystem;

struct IFileSystem {
    void* userData;
    
    int (*fileExists)(IFileSystem* self, const char* path);
    int (*readFile)(IFileSystem* self, const char* path, void** buffer, int* size);
    void (*freeBuffer)(IFileSystem* self, void* buffer);
};

IFileSystem* filesystemCreate(void);
void filesystemDestroy(IFileSystem* fs);
void filesystemAddArchive(IFileSystem* fs, const char* archivePath);

#endif
