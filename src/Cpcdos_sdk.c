#include <stdio.h>
#include <stdarg.h>

//!int printf ( const char * format, ... )
//int imp_printf( const char* format, va_list __local_argv){
int cpc_eval( const char* format, ...){
	va_list _arg_;va_start (_arg_, format);
	
	char BUFFER[4096] = {0};
	va_list arg;
	va_start (arg, format);
		int ret = vsprintf (BUFFER, format, arg);
	va_end (arg);
	printf("CpcDos> %s", BUFFER);
	
	va_end (_arg_);
	return ret;
}