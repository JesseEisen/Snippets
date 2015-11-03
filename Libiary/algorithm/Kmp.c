#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN  100

int next[LEN];

void Next(char *p)
{
	int plen = strlen(p);
	int k = -1;
	int j = 0;

	next[0] = -1;
	while(j < plen - 1)
	{
		if(k > 0 && p[j] != p[k])
		{
			k = next[k];
		}else
		{
			++k;
			++j;
			next[j] = k;
		}
	}
}


int KmpSearch(char *s, char *p)
{
	int i = 0;
	int j = 0;
	int slen = strlen(s);
	int plen = strlen(p);

	while(i < slen && j < plen)
	{
		if(j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}else
		{
			j = next[j];
		}
	}

	if(j == plen)
		return i - j;
	else 
		return -1;
}


//test kmp
int main(int argc, char const *argv[])
{
	char *s = "abcdabceabcfabce";
	char *p = "abcf";

	Next(p);
	printf("Find that at %d\n",KmpSearch(s,p));

	return 0;
}