/*
 * File:   logging.h
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 29, 2013, 11:21 PM
 */

#ifndef LOGGING_H
#define	LOGGING_H

#ifdef	__cplusplus
extern "C" {
#endif

// Prototypes
void lgOpenSyslog(void);
void lgCloseSyslog(void);
void lgOpenLog(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LOGGING_H */

