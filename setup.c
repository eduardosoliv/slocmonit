/*
 * File:   setup.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 29, 2013, 11:31 PM
 */

#include "main.h"

/**
 * Close standard file descriptors
 */
void closeStdFileDescriptors(void)
{
    if (close(STDIN_FILENO) == -1 || close(STDOUT_FILENO) == -1 || close(STDERR_FILENO) == -1) {
        die("Cannot close standard file descriptors.\n");
    }
    #if defined(DEBUG)
    debugmsg("Standard file descriptors closed successfully.\n");
    #endif
}

/**
 * Create new SID (Session ID)
 */
void createSID(void)
{
    pid_t sid = setsid();
    if (sid < 0) {
        die("Cannot create new sid for the child process.\n");
    }
    #if defined(DEBUG)
    debugmsg("SID set successfully.\n");
    #endif
}

/**
 * Change directory
 * @param dir
 */
void changeDir(const char *dir)
{
    // @todo refactor this function move to util part
    char ddate[64];
    utilGetDate(ddate);
    if (chdir(HOMEDIR) < 0) {
        fprintf(fpl, "%s - Cannot change to dir %s.\n", ddate, dir);
        exit(EXIT_FAILURE);
    }
    #if defined(DEBUG)
    fprintf(fpl, "%s - Changed to %s successfully.\n", ddate, dir);
    #endif
}