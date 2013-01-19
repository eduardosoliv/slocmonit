/*
 * File:   hsignal.c
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 16, 2013, 1:09 AM
 */

#include "main.h"

/**
 * Install signal handlers
 */
void hsignalInstall(void)
{
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
}

/**
 * Function that handle signals
 */
void hsignalHandler(int sig)
{
	char ddate[64];
	utilGetDate(ddate);
	switch(sig) {
		case SIGHUP: /* Report that user's terminal is disconnected. Signal used to report the termination of the controlling process. */
			fprintf(fpl, "%s - Received SIGHUP signal. Discarded.\n", ddate);
			break;
		case SIGINT: /* Interrupt from keyboard */
			fprintf(fpl, "%s - Received SIGINT signal. Discarded.\n", ddate);
			break;
		case SIGQUIT: /* Quit from keyboard */
			fprintf(fpl, "%s - Received SIGQUIT signal. Discarded.\n", ddate);
                        break;
		case SIGILL: /* Illegal Instruction */
			fprintf(fpl, "%s - Received SIGILL signal (Illegal Instruction). Terminating. \n", ddate);
	                exit(EXIT_FAILURE);
		case SIGABRT: /* Abort signal */
			fprintf(fpl, "%s - Received SIGABRT (Abort signal). Terminating. \n", ddate);
			exit(EXIT_FAILURE);
		case SIGFPE: /* Floating point exception */
			fprintf(fpl, "%s - Received SIGFPE (Floating point exception). Terminating. \n", ddate);
                        exit(EXIT_FAILURE);
		case SIGSEGV: /* Invalid memory reference */
			fprintf(fpl, "%s - Received SIGSEGV (Segmentation fault). Terminating. \n", ddate);
                        exit(EXIT_FAILURE);
		case SIGPIPE: /* Broken pipe: write to pipe with no readers */
			fprintf(fpl, "%s - Received SIGPIPE (Broken pipe: write to pipe with no readers). Terminating. \n", ddate);
                        exit(EXIT_FAILURE);
		case SIGALRM: /* Timer signal from alarm(2) */
			// No alarms used
			fprintf(fpl, "%s - Received SIGALRM (Timer signal from alarm(2)). Discarded. \n", ddate);
                        break;
		case SIGTERM:
			fprintf(fpl, "%s - STOP.\n", ddate);
			exit(EXIT_SUCCESS);
		default:
			fprintf(fpl, "%s - Unhandled signal.\n", ddate);
                        exit(EXIT_FAILURE);
	}
}
