#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>

int main()
{
	char *line;
	int fd = open("/home/olaurine/get_next_line/file", O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		printf("%s\n", line);
	}
	printf("%s\n", line);
}
