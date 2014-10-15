#define NHASH  101

typedef struct  Nameval Nameval;
struct Nameval
{
	char *name;
	char *def;
	Nameval *next;
};

Nameval *symtab[NHASH];


//this is a version for a string
enum {MULTIPLIER = 31};
unsigned hash(char *name)
{
	unsigned int h;
	unsigned char *p;

	for(p = (unsigned char *)str; *p != '\0'; p++)
		h = h * MULTIPLIER + *p;

	return h % NHASH;
}


//this is a version for string array
enum { NPREF = 2};
unsigned int hash(char *s[NPREF])
{
	unsigned int h;
	unsigned char *p;
	int i;

	h = 0; 
	for(i = 0; i < NPREF; i++)
	{
		for(p = (unsigned char *)s[i]; *p != '\0';p++)
			h = h * MULTIPLIER + *p;
	}

	return h % NHASH;
}
