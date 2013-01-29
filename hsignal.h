/*
 * File:   hsignal.h
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 16, 2013, 1:07 AM
 */

#ifndef HSIGNAL_H
#define	HSIGNAL_H

#ifdef	__cplusplus
extern "C" {
#endif

// Prototypes
void setupSignalsExit(void);
void hsignalInstall(void);
void hsignalHandler(int sig);

#ifdef	__cplusplus
}
#endif

#endif	/* HSIGNAL_H */

