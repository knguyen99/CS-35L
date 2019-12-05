#include <unistd.h>
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
				return 0;
		} 
	}
	return 1;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		write(STDERR_FILENO, "Incorrect number of arguments \n",1);
		exit(1);
	}

	char* from = argv[1];
	char* to = argv[2];
	int fromLen = strlen(from);
	int toLen = strlen(to);
	
	if(fromLen != toLen)
	{
		write(STDERR_FILENO, "Unequal lengths of arguments \n",1);
		exit(1);
	}

	if(!(unique(from)))
	{
		write(STDERR_FILENO, "Duplicate in from string \n",1);
		exit(1);
	}

	char c;
	int replace = 0;	
	while(read(STDIN_FILENO,&c,1) > 0)
	{
		size_t i = 0;
		for(; i < fromLen; i++)
		{
			if(c == from[i])
			{
				replace = 1;
				write(STDOUT_FILENO,&to[i],1);
				break;
			}
		}
		if(!replace)
		{
			write(STDOUT_FILENO,&c,1);
		}
		replace = 0;
	}

	exit(0);
}
