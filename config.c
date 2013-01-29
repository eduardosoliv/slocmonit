/*
 * File:   config.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 19, 2013, 7:45 PM
 */

#include "main.h"

// Global variables
char *logPath;
char *pidFile;

/**
 * Read configuration file
 * @param conf
 */
void readConf(const char *confFile)
{
    // try to open config file
    FILE *fpconf = fopen(confFile, "r");
    if (fpconf == NULL) {
        syslog(LOG_ERR, "Cannot open configuration file %s.", confFile);
        exit(EXIT_FAILURE);
    }

    // initialize variables
    char * line = NULL;
    size_t len_allocated = 0;
    unsigned int lineNumber = 0;

    while (getline(&line, &len_allocated, fpconf) != -1) {
        ++lineNumber;

        // Skip comments and blank lines
        if (line[0] == '#' || line[0] == '\0') {
            continue;
        }

        struct config conf = breakLine(confFile, line, lineNumber);

        if (strcmp(conf.key, "log") == 0) {
            assignKey(&logPath, conf.value, confFile, lineNumber);
        } else if (strcmp(conf.key, "pidfile") == 0) {
            assignKey(&pidFile, conf.value, confFile, lineNumber);
        }
    }
}

/**
 * Break line
 * @param conf
 * @param line
 * @param lineNumber
 */
struct config breakLine(const char *confFile, char *line, unsigned int lineNumber)
{
    struct config conf;

    conf.key = strtok(line, "=");
    conf.value = strtok(NULL, "\n");

    if (conf.key == NULL || conf.value == NULL) {
        syslog(LOG_ERR, "Error reading %s:%d.", confFile, lineNumber);
        exit(EXIT_FAILURE);
    }

    return conf;
}

/**
 * Assign to key
 * @param key
 * @param value
 * @param confFile
 * @param lineNumber
 */
void assignKey(char **key, char *value, const char *confFile, unsigned int lineNumber)
{
    (*key) = (char *) malloc(strlen(value)+1);
    if ((*key) == NULL) {
        syslog(LOG_ERR, "Cannot allocate memory reading from %s:%d", confFile, lineNumber);
        exit(EXIT_FAILURE);
    }
    strcpy((*key), value);
}