#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int unique(const char* str)
{
	size_t i =0;
	for(; i < strlen(str); i ++)
	{
		size_t j = i+1;
		for(;j<strlen(str); j++)
		{
			if(str[i] == str[j])
			{
				return 0;
			}
		} 
	}
	return 1;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Incorrect number of arguments \n");
		exit(1);
	}

	char* from = argv[1];
	char* to = argv[2];
	int fromLen = strlen(from);
	int toLen = strlen(to);
	
	if(fromLen != toLen)
	{
		fprintf(stderr, "Unequal lengths of arguments \n");
		exit(1);
	}

	if(!(unique(from)))
	{
		fprintf(stderr, "Duplicate in from string \n");
		exit(1);
	}

	char c;
	c = getchar();
	int replace = 0;
	while(c != EOF && !ferror(stdin))
	{
		size_t i = 0;
		for(; i < fromLen; i++)
		{
			if(c == from[i])
			{
				putchar(to[i]);
				replace = 1;
				break;
			}
		}
		if(!replace)
		{
			putchar(c);
		}
		replace = 0;
		c = getchar();
	}

	if(ferror(stdin))
	{
		fprintf(stderr, "Input error \n");
		exit(1);
	}

	exit(0);
}
