#pragma once

#ifndef PYROS_UTIL_H
#define PYROS_UTIL_H

#define ATT_START ";.att_syntax;"
#define ATT_END ";.intel_syntax;"

void *memcpy(char *dst, char *src, int n);
void *memset(char *dst, char src, int n);

int strlen(char *s);
char *strncpy(char *destString, const char *sourceString,int maxLength);
int strcmp(const char *dst, char *src);
int strcpy(char *dst,const char *src);
void strcat(void *dest,const void *src);
int strncmp( const char* s1, const char* s2, int c);

void itoa(char *buf, unsigned long int n, int base);

#endif //PYROS_UTIL_H
