/*
 * File:   setup.h
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 29, 2013, 11:31 PM
 */

#ifndef SETUP_H
#define	SETUP_H

#ifdef	__cplusplus
extern "C" {
#endif

// Prototypes
void createChildExitOnFailure(void);
pid_t createChild(void);
int closeStdFileDescriptors(void);
pid_t createSID(void);
int changeRootDir(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SETUP_H */

