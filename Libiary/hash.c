#define NHASH  101

typedef struct  Nameval Nameval;
struct Nameval
{
	char *name;
	char *def;
	Nameval *next;
};

Nameval *symtab[NHASH];



enum {MULTIPLIER = 31}
unsigned hash(char *name)
{
	unsigned int h;
	unsigned char *p;

	for(p = (unsigned char *)str; p != NULL; p++)
		h = h * MULTIPLIER + p;

	return h % NHASH;
}
