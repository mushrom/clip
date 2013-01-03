#include <stdio.h>
#include <stdlib.h>
#include <config.h>

int main( int argc, char *argv[] ){
	if ( argc < 2 )
		return 1;

	config_t *result = parse_file( argv[1] );

	printf( "Server: %s, port: %s\n", get_data( result, "server" ), get_data( result, "port" ));
	printf( "[debug] parse returned %u\n", result );

	free( result );

	return 0;
}
