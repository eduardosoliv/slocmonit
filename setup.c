/*
 * File:   setup.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 29, 2013, 11:31 PM
 */

#include "main.h"

/**
 * Create child
 */
void createChildExitOnFailure(void)
{
    if (createChild() < 0) {
        syslog(LOG_ERR, "Cannot fork.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Fork to create child and exit parent
 *
 * @return PID
 */
pid_t createChild(void)
{
    pid_t pid = fork();

    if (pid > 0) {
        // If comes here we got a good PID, so we can exit the parent process
        exit(EXIT_SUCCESS);
    }

    return pid;
}

/**
 * Close standard file descriptors
 */
int closeStdFileDescriptors(void)
{
    return (close(STDIN_FILENO) == -1 || close(STDOUT_FILENO) == -1 || close(STDERR_FILENO) == -1);
}

/**
 * Create new SID (Session ID)
 */
pid_t createSID(void)
{
    return setsid();
}

/**
 * Change to root directory.
 */
int changeRootDir(void)
{
    return chdir(ROOTDIR);
}