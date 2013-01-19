/* 
 * File:   main.h
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 19, 2013, 7:48 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/*-----------------------------------------------------------------------------
 * Includes
 *----------------------------------------------------------------------------*/    

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <syslog.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "hsignal.h"
#include "hexit.h"
#include "config.h"

/*-----------------------------------------------------------------------------
 * Static configuration
 *----------------------------------------------------------------------------*/
    
#define APP_NAME "slocmonit"
#define DEBUG
#define HOMEDIR "/"    
    
/*-----------------------------------------------------------------------------
 * External declarations
 *----------------------------------------------------------------------------*/

extern FILE *fpl;
extern char *logPath;

/*-----------------------------------------------------------------------------
 * Functions prototypes
 *----------------------------------------------------------------------------*/

void setupSignalsExit(void); 
inline void debugmsg(const char *msg);
void openLog(void);
void closeStdFileDescriptors(void);
void createSID(void);
void changeDir(const char *dir);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

