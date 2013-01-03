#ifndef _clip_daemon_c
#define _clip_daemon_c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>

#include <config.h>
#include <clipmsg.h>
#include <common.h>
unsigned int running = 1;

void start_server_unix( config_t *config ){
	unsigned int max_connect = 10;

	if ( get_data( config, "sock_file" ) == NULL )
		die( 1, "No \"sock_file\" variable in config\n" );
	if ( get_data( config, "max_connect" ) != NULL )
		max_connect = atoi( get_data( config, "max_connect" ));

	unsigned int sock, client;
	struct sockaddr_un local, remote;
	char *buf = malloc( 1024 );
	int len, recieved;

	sock = socket( AF_UNIX, SOCK_STREAM, 0 );
	local.sun_family = AF_UNIX;
	strncpy( local.sun_path, get_data( config, "sock_file" ), 108 );
	unlink( local.sun_path );
	len = strlen( local.sun_path ) + sizeof( local.sun_family );

	bind( sock, (struct sockaddr *)&local, len );
	listen( sock, max_connect );

	while ( running ){
		len = sizeof( struct sockaddr_un );
		client = accept( sock, (struct sockaddr *)&remote, (socklen_t *)&len );

		recieved = recv( sock, buf, 1024, 0 );
		if ( recieved == 0 ){
			close( client );
			continue;
		}

		printf( "Got \"%s\" from client\n", buf );
		
		printf( "Got connection, closing...\n" );
		close( client );
	}
	free( buf );
}

void init_daemon( config_t *config ){
	if ( get_data( config, "socket" ) != NULL ){
		if ( strcmp( get_data( config, "socket" ), "net" ) == 0 ){
			//Daemon accessed by internet
		} else if ( strcmp( get_data( config, "socket" ), "unix" ) == 0 ){
			//Daemon accessed by local unix socket
			printf( "[debug] Starting local unix server\n" );
			start_server_unix( config );
		} else if ( strcmp( get_data( config, "socket" ), "both" ) == 0 ){
			//Daemon accessed by both internet and unix socket
		} else {
			die( 1, "Expected value \"net\", \"unix\", or \"both\" for variable \"socket\" in config\n" );
		}
	} else {
		die( 1, "No \"socket\" variable in config\n" );
	}
}

int main( int argc, char *argv[] ){
	config_t *conf;
	if ( argc > 1 )
		conf = parse_file( argv[1] );
	else
		conf = parse_file( PREFIX"/etc/daemon.conf" );

	if ( conf )
		init_daemon( conf );
	else 
		die( 1, "Could not open config file\n" );

	return 0;

}

#endif
