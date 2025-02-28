// Shani Sharon 212432967
// Itai Shaya 207033622

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

time_t ParseDateString(const char* dateString) {
    /* Converts a date string in "DD/MM/YYYY" format to a time_t value.
     * Uses the tm struct for date parsing.
     * Returns (time_t)-1 if the date format is invalid.
     */
    struct tm dateInfo = { 0 };  // Initialize tm struct to zero
    int day = 0, month = 0, year = 0;

    // Parse the date string into day, month, and year
    if (sscanf(dateString, "%d/%d/%d", &day, &month, &year) != 3) {
        // Invalid date format
        return (time_t)-1;
    }

    // Populate the tm struct
    dateInfo.tm_year = year - 1900;  // tm_year is years since 1900
    dateInfo.tm_mon = month - 1;     // tm_mon is months since January (0-11)
    dateInfo.tm_mday = day;          // tm_mday is day of the month (1-31)

    // Convert tm struct to time_t
    return mktime(&dateInfo);
}