// Shani Sharon 212432967
// Itai Shaya 207033622

#define _CRT_SECURE_NO_WARNINGS

#include "logs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void AddLog(const char* text)
{
    /* This function appends to the log file each action done by the user.
    * the log file is logs.log and is created on initial startup, this function just appends text
    */
    FILE* file = fopen("logs.log", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    time_t current_time;
    struct tm time_info;
    char formatted_time[80];

    time(&current_time);
    localtime_s(&time_info, &current_time);
    strftime(formatted_time, sizeof(formatted_time), "%d/%m/%Y %H:%M:%S", &time_info);
    fprintf(file, "[%s] %s", formatted_time, text);
    fclose(file);
}

