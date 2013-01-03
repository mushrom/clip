#ifndef _clip_common_c
#define _clip_common_c
#include <common.h>

void die( int status, char *format, ... ){
	va_list args;

	va_start( args, format );
	printf( "Error: " );
	vprintf( format, args );

	exit( status );
}

#endif
