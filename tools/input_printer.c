#include <stdio.h>

int main()
{
	int c;
	while((c = getchar()))
	    printf("\\x%x", c);
}
