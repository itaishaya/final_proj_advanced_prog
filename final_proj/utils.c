// Shani Sharon *ID*
// Itai Shaya 207033622

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t convertStringToTime(const char* date) {
    /* This function convert string to a date from time_t format
    * it uses tm struct
    */
    struct tm tm = { 0 };
    int day=0, month=0, year=0;

    if (sscanf(date, "%d/%d/%d", &day, &month, &year) != 3) {
        // Invalid date format
        return (time_t)-1;
    }

    tm.tm_year = year - 1900;  // tm_year is years since 1900
    tm.tm_mon = month - 1;     // tm_mon is months since January (0-11)
    tm.tm_mday = day;          // tm_day is day of the month (1-31)

    return mktime(&tm);
}
