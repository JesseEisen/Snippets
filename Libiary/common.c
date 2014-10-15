#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int  bufp = 0;

int getch(void)
{

	return bufp > 0?buf[--bufp]:getchar();

}

void ungetch(int c)
{
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;
	if(c != EOF)
		*w++ = c; 
	if(!isalpha(c))
	{ 
		*w = '\0';
		return c;
 	}

	for(; --lim > 0; w++)
		if(!isalnum(*w = getch()))
	 	{
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];


}

void ungets(char *s)
{
	int len = strlen(s);

	while(len > 0)
		ungetch(s[-len]);
}
