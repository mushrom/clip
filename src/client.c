#ifndef _clip_client_c
#define _clip_client_c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <config.h>
#include <clipmsg.h>
#include <common.h>

int connect_to_unix( config_t *config ){
	int len, sock;
	struct sockaddr_un remote;
	if ( get_data( config, "sock_file" ) != NULL ){
		if (( sock = socket( AF_UNIX, SOCK_STREAM, 0 )) == -1 )
			die( 1, "Could not open socket\n" );
			
		remote.sun_family = AF_UNIX;
		strncpy( remote.sun_path, get_data( config, "sock_file" ), 108 );
		len = strlen( remote.sun_path ) + sizeof( remote.sun_family );
		if ( connect( sock, (struct sockaddr *)&remote, len ) == -1 )
			die( 1, "Could not open connect to socket %s\n", get_data( config, "sock_file"));

		#ifdef DEBUG
		printf( "Client connected\n" );
		#endif
		return sock;
	} else {
		die( 1, "No variable \"sock_file\" in config\n" );
	}

	return -1;
}

int connect_to_serv( config_t *config ){
	if ( get_data( config, "connect" ) != NULL ){
		return connect_to_unix( config );
	} else {
		die( 1, "No variable \"socket\" in config\n" );
	}
	return 0;
}

void test_connect( int sock ){
	char *str = "Testing the client<->daemon connection";
	if (( send( sock, str, strlen( str ), 0 )) < 0 )
		die( 1, "Could not send\n" );
}

int main( int argc, char *argv[] ){
	int sock;
	config_t *conf;
	if ( argc > 1 )
		conf = parse_file( argv[1] );
	else
		conf = parse_file( PREFIX"/etc/client.conf" );

	if ( conf )
		printf( "Read client config.\n" );
	else
		die( 1, "Could not open client config\n" );

	sock = connect_to_serv( conf );

	if ( sock < 0 )
		die( 1, "Unknown socket error" );

	test_connect( sock );
	close( sock );

	free( conf );

	return 0;
}
#endif
