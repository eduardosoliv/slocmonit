/*
 * File:   hexit.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 17, 2013, 1:01 AM
 */

#include "main.h"

/**
 * Bye is executed on exit
 */
void bye(void) {
    if (fpl != NULL) {
        fclose(fpl);
    }
}

/**
 * Die will print a message to log and exit with failure code
 * @param msg
 */
void die(const char *msg) {
    char ddate[64];
    utilGetDate(ddate);
    fprintf(fpl, "%s - %s", ddate, msg);
    exit(EXIT_FAILURE);
}