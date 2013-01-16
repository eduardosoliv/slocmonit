/*
 * File:   main.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 16, 2013, 1:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <syslog.h>

#include "hsignal.h"

// Defines
#define APP_NAME "slocmonit"
#define DEBUG

// Global variables
FILE *fpl = NULL, *fple = NULL;

/*
 * Main function, entry point
 */
int main(int argc, char** argv) {
    // Open syslog
    #if defined(DEBUG)
    openlog(APP_NAME, LOG_CONS | LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);
    #else
    openlog(APP_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
    #endif

    // Setup signals
    signal(SIGHUP, hsignalHandler);
    signal(SIGINT, hsignalHandler);
    signal(SIGQUIT, hsignalHandler);
    signal(SIGILL, hsignalHandler);
    signal(SIGABRT, hsignalHandler);
    signal(SIGFPE, hsignalHandler);
    signal(SIGSEGV, hsignalHandler);
    signal(SIGPIPE, hsignalHandler);
    signal(SIGALRM, hsignalHandler);
    signal(SIGTERM, hsignalHandler);

    printf("going...\n");
    return (EXIT_SUCCESS);
}
