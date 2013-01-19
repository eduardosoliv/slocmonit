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
    
    // Open syslog
    #if defined(DEBUG)
    openlog(APP_NAME, LOG_CONS | LOG_PERROR | LOG_PID | LOG_NDELAY, LOG_USER);
    #else
    openlog(APP_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
    #endif

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
    openLog();
        
    // Syslog not needed anymore, just write to log file 
    closelog();   
    
    // Close out the standard file descriptors
    closeStdFileDescriptors();

    // Create a new SID for the child process
    createSID();
    
    // Change the current dir (prevent unmount)
    changeDir(HOMEDIR);   
    
    return (EXIT_SUCCESS);
}

/**
 * Setup signal handlers and exit function
 */
void setupSignalsExit(void)
{
    // Install signal handlers
    hsignalInstall();

    // Setup exit function
    if (atexit(bye) != 0) {
        syslog(LOG_ERR, "Cannot set exit function.\n");
        exit(EXIT_FAILURE);
    }  
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

/**
 * Open log
 */
void openLog(void)
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