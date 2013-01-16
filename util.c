/*
 * File:   util.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 16, 2013, 1:11 AM
 */

#include <time.h>

/**
 * Store date and time in argument passed
 * @param ddate
 */
void utilGetDate(char *ddate)
{
        time_t rawtime;
        struct tm * timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(ddate, 64, "%Y-%m-%d %H:%M:%S", timeinfo);
}