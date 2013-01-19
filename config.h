/* 
 * File:   config.h
 * Author: Eduardo Oliveira <entering@gmail.com>
 *
 * Created on January 19, 2013, 7:45 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

struct config {
    char *key;
    char *value;
};

void readConf(const char *conf);
struct config breakLine(const char *conf, char *line, unsigned int lineNumber);
void assignKey(char **key, char *value, const char *confFile, unsigned int lineNumber);

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

