#define _GNU_SOURCE

#include <fcntl.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define MALICIOUS_FILE "syl.lys"

static int (*original_open)(const char *filename, int flags, ...) = NULL;

int open (const char *filename, int flags, ...)
{
    if (strcmp(filename, MALICIOUS_FILE) == 0) 
    {
        errno = ENOENT;
        return -1;
    }
    original_open = dlsym(RTLD_NEXT, "open");
    return original_open(filename, flags);
}