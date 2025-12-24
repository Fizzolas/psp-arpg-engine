#ifndef ASSETS_DATAROOT_H
#define ASSETS_DATAROOT_H

typedef struct {
    int fileCount;
    char** filePaths;
    int* fileStatus; // 1 = found, 0 = missing
} DataCheckResult;

void datarootInit(void);
void datarootShutdown(void);
DataCheckResult datarootCheckFiles(void);
void datarootFreeCheckResult(DataCheckResult* result);
const char* datarootResolve(const char* relativePath);

#endif
