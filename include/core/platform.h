#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

void platformInit(void);
void platformShutdown(void);
const char* platformGetAppDir(void);
const char* platformGetUserDataDir(void);
const char* platformGetGameDataDir(void);

#endif
