#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <limits.h>
int fopt = 0;
int cmp = 0;

char decode(char a)
{
	if(fopt)
	{
		a = a^42;
		if(a <= UCHAR_MAX)
			a = toupper(a);
		return a;
	}
	return a^42;
}

int frobcmp(char const *a, char const *b)
{
	while(*a != ' ' && *b != ' ')
	{
		if(decode(*a) < decode(*b))
			return -1;
		if(decode(*a) > decode(*b))
			return 1;
		a++;
		b++;
	}
	if( *a == ' ' && *b == ' ')
		return 0; 
	else if( *a == ' ' )
		return -1;
	else
		return 1;
}

int wrapcmp(const void* a, const void* b){
	const char* ptra = *(const char**)a;
	const char* ptrb = *(const char**)b;
	return frobcmp(ptra,ptrb);
}

int main(int argc, char* argv[]){
	
	if(argc > 2)
	{
		char errmsg[] = "Invalid number of args \n";
		write(STDERR_FILENO, errmsg, sizeof(errmsg));
		exit(1);
	}
	
	if(argc == 2)
	{
		if(strcmp(argv[1],"-f")!= 0)
		{
			char errmsg[] = "Invalid option \n";
			write(STDERR_FILENO, errmsg, sizeof(errmsg));
			exit(1);
		}
		fopt = 1;
	}
	
	struct stat filestat;
	ssize_t nfile = fstat(0,&filestat);
	if(nfile < 0)
	{
		char errmsg[] = "Error in file stat \n";
		write(STDERR_FILENO, errmsg, sizeof(errmsg));
		exit(1);
	}	

	size_t fileSize = filestat.st_size +1;

	char* inp;
	char** wordsarr;
	int wordArrSize = 0;
	int wordArrCount = 0;
	int word = 0;	
	if(S_ISREG(filestat.st_mode))
	{
		inp = (char*)malloc(sizeof(char)*fileSize);
		if(!inp)
		{
			char errmsg[] = "Memory allocation error \n";
			write(STDERR_FILENO, errmsg, sizeof(errmsg));
			exit(1);
		}
		nfile = read(STDIN_FILENO,inp,filestat.st_size);
		if(nfile < 0)
		{
			char errmsg[] = "Error in read \n";
			write(STDERR_FILENO, errmsg, sizeof(errmsg));
			exit(1); 
		}

		size_t i = 0;
		for(; i < nfile; i++)
		{
			if(inp[i] == ' ' && word)
			{	
				wordArrSize++;
				word = 0;
			}
			else
			{
				while(inp[i] == ' ' && i < nfile)
				{
					i++;
				}
				if(i < nfile)
				{
					word = 1;
				} 
			}
		}
		if(word)
			wordArrSize++;
		char** tempwordsarr = (char**)malloc(sizeof(char*)*wordArrSize);
		if(!tempwordsarr)
		{
			char errmsg[] = "Memory allocation error \n";
                        write(STDERR_FILENO, errmsg, sizeof(errmsg));
                        exit(1);
		}
		wordsarr = tempwordsarr;
		word = 0;
		size_t g = 0;
		for(; g < nfile; g++)
		{
			if(inp[g] != ' ' && !word)
			{
				wordsarr[wordArrCount] = &inp[g];
				wordArrCount++;
				word = 1;
			} 
			if(inp[g] == ' ' && word)
			{
				word = 0;
			}
		}
						
	}
	else 
	{
		wordsarr = (char**)malloc(sizeof(char*));
		char* str = (char*)malloc(sizeof(char));
		char currC[1];
		ssize_t nfile2 = read(STDIN_FILENO, currC, 1);
		if(nfile2 < 0)
                {
                        char errmsg[] = "Error in read \n";
                        write(STDERR_FILENO, errmsg, sizeof(errmsg));
                        exit(1);
                }
		char nextC[1];
		ssize_t nfile3 = read(STDIN_FILENO, nextC, 1);
		if(nfile3 < 0)
		{
			char errmsg[] = "Error in read \n";
                        write(STDERR_FILENO, errmsg, sizeof(errmsg));
                        exit(1);
		}
		long currwordsize = 0;
		while(nfile2 > 0)
		{
			str[currwordsize] = currC[0];
			char* tempword = (char*)realloc(str, (currwordsize+2)*sizeof(char));
			if(!tempword)
			{
                        	char errmsg[] = "Memory allocation error \n";
                        	write(STDERR_FILENO, errmsg, sizeof(errmsg));
				free(str);
                        	exit(1);
			}
			str = tempword;
			currwordsize++;
			if(currC[0] == ' ')
			{
				wordsarr[wordArrCount] = str;
				char** tempwordsarr = (char**)realloc(wordsarr,(wordArrCount+2)*sizeof(char*));
				if(!tempwordsarr)
				{
					char errmsg[] = "Memory allocation error \n";
                                	write(STDERR_FILENO, errmsg, sizeof(errmsg));
                                	free(wordsarr);
                                	exit(1);	
				}
				wordsarr = tempwordsarr;
				wordArrCount++;
				str = NULL;
				str = (char*)malloc(sizeof(char));
				currwordsize = 0; 
			}
			if(currC[0] == ' ' && nextC[0] == ' ')
			{
				while(currC[0] == ' ')
				{
					nfile2 = read(STDIN_FILENO,currC,1);
					if(nfile2 < 0)
                			{
                        			char errmsg[] = "Error in read \n";
                        			write(STDERR_FILENO, errmsg, sizeof(errmsg));
						exit(1);
               				}
					
				}
				nfile3 = read(STDIN_FILENO,nextC,1);
				if(nfile3 < 0)
				{	
					char errmsg[] = "Error in read \n";
					write(STDERR_FILENO, errmsg, sizeof(errmsg));
					exit(1);
				}
				currwordsize++;
				continue;
			}
			else if(currC[0] == ' ' && nfile3 == 0)
				break;
			else if(!nfile3)
			{
				currC[0] = ' ';
				continue;
			}
			
			currC[0] = nextC[0];
			nfile3 = read(STDIN_FILENO,nextC,1);
		}
		free(str);
	}

	qsort(wordsarr,wordArrCount,sizeof(char*),wrapcmp);

	size_t p = 0;
	for(;p < wordArrCount; p++)
	{
		size_t q = 0;
		long len = 0;
		while(wordsarr[p][q] != ' ')
		{
			len++;
			q++;
		}
		len++;	
		nfile = write(STDOUT_FILENO, wordsarr[p], len);
		if(nfile < 0)
		{
			char errmsg[] = "Error in write \n";
                        write(STDERR_FILENO, errmsg, sizeof(errmsg));
                        exit(1);
		} 
	}

	if(S_ISREG(filestat.st_mode))
	{
		free(inp);
	}
	else
	{
		int l = 0;
		for(; l < wordArrCount; l++)
		{
        		if(wordsarr[l])	
				free(wordsarr[l]);
		}
	}
	if(wordsarr)
        	free(wordsarr);
	exit(0);
}

