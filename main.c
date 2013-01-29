/*
 * File:   main.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 16, 2013, 1:06 AM
 */

#include "main.h"

FILE *fpl = NULL;

/*
 * Main function, entry point
 */
int main(int argc, char** argv)
{
    // Open syslog
    lgOpenSyslog();

    // Fork
    pid_t pid = fork();
    if (pid < 0) {
        syslog(LOG_ERR, "Cannot fork.\n");
        exit(EXIT_FAILURE);
    }

    // If comes here we got a good PID, so we can exit the parent process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Install signal handlers and setup exit function
    setupSignalsExit();

    // get path to configuration
    if (argc != 2) {
        syslog(LOG_ERR, "Configuration file not passed. Please use %s <path-configuration-file>.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // read configuration
    readConf(argv[1]);

    // open log
    lgOpenLog();

    // Syslog not needed anymore, just write to log file
    lgCloseSyslog();

    // Close out the standard file descriptors
    closeStdFileDescriptors();

    // Create a new SID for the child process
    createSID();

    // Change the current dir (prevent unmount)
    changeDir(HOMEDIR);

    // Read old PID check if is still running
    FILE *fopid = fopen(pidFile, "r");
    if (fopid != NULL) { // file exists
        char * line = NULL;
        size_t len_allocated = 0;
        ssize_t res = getline(&line, &len_allocated, fopid);
        if (res != -1) {
            // remove newline
            size_t len = strlen(line);
            if(line[len-1] == '\n') {
                line[len-1] = '\0';
            }
            #if defined(DEBUG)
            char ddate[64];
            utilGetDate(ddate);
            fprintf(fpl, "%s - Old PID %s.\n", ddate, line);
            #endif
        }
    }

    return (EXIT_SUCCESS);
}

/**
 * Debug message
 * @param msg
 */
inline void debugmsg(const char *msg) {
    char ddate[64];
    utilGetDate(ddate);
    fprintf(fpl, "%s - %s", ddate, msg);
}
