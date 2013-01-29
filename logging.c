/*
 * File:   logging.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 29, 2013, 11:20 PM
 */

#include "main.h"

/**
 * Open syslog
 */
void lgOpenSyslog(void)
{
    #if defined(DEBUG)
    openlog(APP_NAME, LOG_CONS | LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);
    #else
    openlog(APP_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
    #endif
}

/**
 * Close syslog
 */
void lgCloseSyslog(void)
{
    closelog();
}

/**
 * Open log
 */
void lgOpenLog(void)
{
    // check if log file directive exists on configuration
    if (logPath == NULL) {
        syslog(LOG_ERR, "Missing directive of log on configuration.\n");
        exit(EXIT_FAILURE);
    }

    fpl = fopen(logPath, "a+");
    if (fpl == NULL) {
        syslog(LOG_ERR, "Cannot open log %s.\n", logPath);
        exit(EXIT_FAILURE);
    }
    #if defined(DEBUG)
    debugmsg("Open log successfully.\n");
    #endif
}
