#ifndef __FAMINE_H__
# define __FAMINE_H__

#include <stdio.h>
#include <unistd.h>
#include <elf.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

#include "color.h"

int		write_string(char *ptr, size_t size, char *path, int fd);

#endif