#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define ERROR -1
#define STACK_INIT_SIZE 50
#define STACK_ADD_SIZE  10
#define MAXSIZE         50

struct stack
{
	char *top;
	char *base;
	int size;
};


double val[MAXSIZE]; //use to calc
int sp = 0;  //use to calc
typedef struct stack stack;
char expression[MAXSIZE];
stack s2; //use to store the pola expression

//initstack
int initstack(stack *s)
{
	int len = STACK_INIT_SIZE;
	s->base = (char *)malloc(len *sizeof(char));
	if(s->base == NULL)
		return ERROR;
	s->top = s->base;
	s->size = STACK_INIT_SIZE;
	return OK;
}

//empty
int isempty(stack s)
{
	if(s.top == s.base)
		return OK;
	return 0;
}



//get top
char gettop(stack s)
{
	char e;
	if(s.top == s.base)
		return ERROR; //stack is empty
	e =*(s.top - 1);
	return e;
}

//push
int push(stack *s, char e)
{
	//stack full
	if((s->top - s->base) >= s->size)
	{
		int addsize = STACK_ADD_SIZE;
		s->base = (char *)realloc(s->base,(s->size + addsize)*sizeof(char));
		if(s->base == NULL)
			return ERROR;
		s->top = s->base + s->size; //goto the top
		s->size += addsize;
	}

	//push
	*s->top++ = e;
	return OK;
}

//pop
char pop(stack *s)
{
	char e;
	if(s->top == s->base)
		return ERROR; //stack empty;
	e = *--s->top;
	return e;
}

void destroy(stack s)
{
	free(s.base);
	s.base =NULL;
	s.top = NULL;
	s.size = 0;

}

//print stack
void printstack(stack s)
{
	char *q;
	int i;
	q = s.top - 1;

	for(i = 0; i < (s.top-s.base); i++)
	{ 
		printf("%c",*q);
		q--;
	} 

	printf("\n");
}

void convert2pola(int len)
{
	stack s1; 
	int i;
	char ch;

	initstack(&s1); //use to store the option

	for(i = 0; i < len; i++)
	{
		switch(expression[i])
		{
			case '(':
				push(&s1,expression[i]);
				break;
			case ')':
				while(gettop(s1) != '(')
				{
					ch = pop(&s1);
					push(&s2,ch);
				}
				//if option is ( then pop it, do anything
				pop(&s1);
				break;
			//if operators, just push them into stack
			case '+':
			case '-':
				for(ch = gettop(s1);!isempty(s1);ch=gettop(s1))
				{
					if(ch == '(')
						break;
					else
					{
						ch = pop(&s1);
						push(&s2,ch);
					}
				}
				push(&s1,expression[i]);
				break;
			case '*':
			case '/':
				for(ch = gettop(s1); !isempty(s1)&& ch != '+' && ch !='-';ch =gettop(s1))
				{
					if(ch == '(')
						break;
					else
					{
						ch = pop(&s1);
						push(&s2,ch);
					}
				}
				push(&s1,expression[i]);
				break; 
			default:
				push(&s2,expression[i]);
	 	}
	} 
	while(isempty(s1) == 0) //stack is not empty
	{
		ch = pop(&s1);
		push(&s2,ch);
	}

	destroy(s1);
}	


void Push(double f)
{
	if(sp < MAXSIZE)
		val[sp++] = f;
	else
		printf("Push: stack full, can't push %g\n",f);
}

double Pop(void)
{
	if(sp > 0)
		return val[--sp];
	else
		printf("Pop: error, stack empty\n");
}	


int main(int argc, const char *argv[])
{
	int  i = 0,j,len;
	char ch;
	char result[MAXSIZE];
	char *p;
	double  op;
	stack stack1;


	initstack(&stack1);
	initstack(&s2);

	printf("please input a expression:\n");
	while((ch = getchar()) != '\n')
	{ 
		if(ch == ' ' || ch == '\t')
			continue;
		expression[i++] = ch;
	}

	len = i;
	/*for(i = 0; i<sizeof(expression)/ sizeof(char); i++)
		printf("%c",expression[i]);
	printf("\n");
	*/
	convert2pola(len);
	p = s2.base; 
	for(i=0; i < (s2.top - s2.base); i++)
	{
		result[i] = *p++;
	}
	destroy(s2);

	for(j = 0; j < i; j++)
	{
		printf("%c",result[j]);
		if(isdigit(result[j]))
		{
			Push((double)(result[j]-'0'));
		}else if(result[j] == '+')
		{
			Push((Pop()+Pop()));
		}else if(result[j] == '*')
		{
			Push((Pop() * Pop()));
		}else if(result[j] == '-')
		{
			op = Pop();
			Push((Pop()-op));
		}else if(result[j] == '/')
		{
			op = Pop();
			if(op != 0)
			{
				Push((Pop()/op));
			}else
			{
				printf("error: zero divisor\n");
			}
		}else
		{
			printf("error operators\n");
			break;
		}
	}
	
	printf("\nresult is: %g\n",Pop());
	/*for(i  = 0; i < 5;i++)
	{
		scanf("%c",&ch);
		push(&s1,ch);
	}
	printstack(s1);
	printf("%c %c\n",gettop(s1),pop(&s1));
	printstack(s1);
	*/
	return 0;
}
