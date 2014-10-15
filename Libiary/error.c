#include "base.h"

#define BUFSIZE 1024

/* *****************************************************************************/
/**
 * @Synopsis  err_doit print and return to caller
 *
 * @Param errorflag
 * @Param errno
 * @Param msg
 * @Param ap
 */
/* *****************************************************************************/
void err_doit(int errorflag, int error,const char *fmt, va_list ap)
{
	char buf[BUFSIZE];
	vsnprintf(buf,BUFSIZE,fmt,ap);

	if(errorflag)
	{
		snprintf(buf+strlen(buf), BUFSIZE+strlen(buf), " :%s", strerror(error));
	}

	strcat(buf,"\n");
	fflush(stderr);
	fputs(buf,stderr);
	fflush(NULL);
}

/* *****************************************************************************/
/**
 * @Synopsis  err_ret print error message
 *
 * @Param fmt
 * @Param ...
 */
/* *****************************************************************************/
void err_ret(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);

}


/* *****************************************************************************/
/**
 * @Synopsis  err_sys print error msg and termial
 *
 * @Param fmt
 * @Param ...
 */
/* *****************************************************************************/
void err_sys(const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap,fmt);
	err_doit(1,errno,fmt,ap);
	va_end(ap);

	exit(1);
}



/* *****************************************************************************/
/**
 * @Synopsis  err_msg just print the message we input
 *
 * @Param fmt
 * @Param ...
 */
/* *****************************************************************************/
void err_msg(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(0,0,fmt,ap);
	va_end(ap);

}


/* *****************************************************************************/
/**
 * @Synopsis  err_quit print the message we input and terminaled
 *
 * @Param fmt
 * @Param ...
 */
/* *****************************************************************************/
void err_quit(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(0,0,fmt,ap);
	va_end(ap);

	exit(1);
}





