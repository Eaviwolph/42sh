#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int i;

	i = 0;
	while (i < PATH_MAX - 1)
	{
		putchar('a');
		i++;
	}
	putchar('\n');
	i = 0;
	while (i < PATH_MAX - 2)
	{
		putchar('b');
		i++;
	}
	putchar('\n');
	return (0);
}
