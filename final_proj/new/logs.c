// Shani Sharon 212432967
// Itai Shaya 207033622

#define _CRT_SECURE_NO_WARNINGS

#include "logs.h"
#include <stdio.h>
#include <time.h>

void AddLogEntry(const char* logMessage) {
    /* Appends a log entry to the log file. */
    FILE* logFile = fopen("logs.log", "a");
    if (logFile == NULL) {
        printf("Error opening log file.\n");
        return;
    }

    time_t currentTime;
    struct tm timeInfo;
    char formattedTime[80];

    time(&currentTime);
    localtime_s(&timeInfo, &currentTime);
    strftime(formattedTime, sizeof(formattedTime), "%d/%m/%Y %H:%M:%S", &timeInfo);

    fprintf(logFile, "[%s] %s", formattedTime, logMessage);
    fclose(logFile);
}