#ifndef _PATS_CONFIG_H_
#define _PATS_CONFIG_H_

#include <stddef.h>

/* DUMMY */
typedef int time_t;
typedef int off_t;
typedef int pid_t;
typedef int FILE;
extern int *stderr;

FILE *fopen(const char *path, const char *mode);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int fprintf(FILE *stream, const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);

#endif /* _PATS_CONFIG_H_ */
