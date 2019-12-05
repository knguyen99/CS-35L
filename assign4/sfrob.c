#include <stdio.h>
#include <stdlib.h>

//return  negative, zero, or positive depending on whether 
//a is less than, equal to, or greater than b
int frobcmp(char const *a, char const *b)
{
	while(*a != ' ' && *b != ' ')
	{
		if((*a^42) < (*b^42))
			return -1;
		if((*a^42) > (*b^42))
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

int main(void){

	char* word = (char*)malloc(sizeof(char));
	char** wordsarr = (char**)malloc(sizeof(char*));
		
	if(ferror(stdin))
	{
		fprintf(stderr, "Input error");
		exit(1);
	}
	char c = getchar();
	int wordArrSize = 0;
	int currWordSize = 0;
	while(!feof(stdin))
	{
		if(ferror(stdin)){
			fprintf(stderr, "Input error");
			exit(1);
		}
		if( c != ' ' ){
			char* tempword = (char*)realloc(word,(currWordSize+2)*sizeof(char));
			if(!tempword){
				fprintf(stderr, "Memory allocation error");
				free(word);
                        	exit(1);
			}
			word = tempword;
			word[currWordSize] = c;
			currWordSize++;
		}
		if( c == ' ' && currWordSize > 1)
		{
			char* tempword = (char*)realloc(word,(currWordSize+2)*sizeof(char));
                        if(!tempword){
                                fprintf(stderr, "Memory allocation error");
				free(word);
                                exit(1);
                        }
			word = tempword;
                        word[currWordSize] = c;
                        currWordSize++;
			char** tempwordsarr = (char**)realloc(wordsarr,(wordArrSize + 2)*sizeof(char*));
			if(!tempwordsarr)
			{
				fprintf(stderr, "Memory allocation error");
                                free(wordsarr);
				exit(1);
			}
			wordsarr = tempwordsarr;
			wordsarr[wordArrSize] = word;
			wordArrSize++;
			currWordSize = 0;
			word = NULL;
			word = (char*)malloc(sizeof(char));	
			}
		
		c = getchar();
	}

	if(currWordSize > 0){
		char* tempword = (char*)realloc(word,(currWordSize+2)*sizeof(char));
		if(!tempword){
			fprintf(stderr, "Memory allocation error");
			free(word);
                        exit(1);
		}
		word = tempword;
		word[currWordSize]= ' ';
		char** tempwordsarr = (char**)realloc(wordsarr,(wordArrSize +2)*sizeof(char*));
                if(!tempwordsarr)
                      	{
                                fprintf(stderr, "Memory allocation error");
                                free(wordsarr);
                                exit(1);
                        }
                wordsarr = tempwordsarr;
                wordsarr[wordArrSize] = word;
                wordArrSize++;
	}
	
	qsort(wordsarr,wordArrSize,sizeof(char*),wrapcmp);

	int p = 0;
	for(; p < wordArrSize; p++){
		int j = 0;
		while( wordsarr[p][j]  != EOF){
			putchar(wordsarr[p][j]);
			if(ferror(stdout)){
				fprintf(stderr,"Output Error");
                                exit(1);
			}
			if(wordsarr[p][j] == ' ')
				break;		
			j++;
		}
	}
	
	int l = 0;
	for(; l < wordArrSize; l++)
        	free(wordsarr[l]);
        free(wordsarr);	
	exit(0);
}

