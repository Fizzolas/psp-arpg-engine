#ifndef CORE_LOGGING_H
#define CORE_LOGGING_H

void loggingInit(void);
void loggingShutdown(void);
void logInfo(const char* message);
void logWarning(const char* message);
void logError(const char* message);

#endif
