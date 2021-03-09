#include "famine.h"

int		outputhandle(int ac, char **av)
{
	for (int i = 0; i < ac; ++i)
		if (strcmp("-sh", av[i]) == 0 || strcmp("--show", av[i]) == 0)
			return (0);
	int buf[100];
	for (int i = 0; i < 100; ++i)
	{
		pipe(&buf[i]);
		dup2(buf[i], i);      // replace stdout with output to child
	}
	struct sigaction new_action;
	//new_action.sa_handler = _handler;
    	new_action.sa_flags = SA_ONSTACK;
	sigemptyset(&new_action.sa_mask);
	//for (int i = 1; i < 57; ++i)
	//	sigaddset(&new_action.sa_mask, i);
	//sigaddset(&new_action.sa_mask, SIGINT);
	sigaddset(&new_action.sa_mask, SIGSEGV);


	for (int i = 0; i < ac; ++i)
		if (strcmp("-sg", av[i]) == 0 || strcmp("--segfault", av[i]) == 0)
		{
			printf(av[1000]);
			break;
		}
}
