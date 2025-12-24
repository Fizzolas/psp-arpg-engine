#ifndef ASSETS_ARCHIVE_H
#define ASSETS_ARCHIVE_H

// Interface for archive formats (MPQ, etc.)

typedef struct IArchive IArchive;

struct IArchive {
    void* userData;
    
    int (*open)(IArchive* self, const char* path);
    void (*close)(IArchive* self);
    int (*fileExists)(IArchive* self, const char* filename);
    int (*readFile)(IArchive* self, const char* filename, void** buffer, int* size);
    void (*freeBuffer)(IArchive* self, void* buffer);
};

// MPQ archive implementation (stub)
IArchive* archiveCreateMPQ(void);
void archiveDestroyMPQ(IArchive* archive);

#endif
