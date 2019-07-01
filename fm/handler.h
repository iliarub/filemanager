#ifndef _HENDLER
#define _HENDLER

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int filecreate(char* x);
int filewrite(char* x, char* y);
int fileread(char* x, char* y);
void curses(char* x, int maxlen);
#endif
