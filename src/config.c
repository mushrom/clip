#ifndef _clip_config_c
#define _clip_config_c
#include <config.h>
#include <stdlib.h>

config_t *parse_file( char *file ){
	FILE *fp;
	if (( fp = fopen( file, "r" )) == NULL )
		return 0;
	
	config_t *conf = (config_t *)malloc(sizeof( config_t ));
	conf->items = (config_item_t *)malloc(sizeof( config_item_t ) * BUFFER );
	conf->len = 0;

	char *buf = (char *)malloc( MAX_STR_LEN );

	int i;
	while ( fgets( buf, MAX_STR_LEN, fp )){
		if ( index( buf, '=' ) == NULL || buf[0] == '#' )
			continue;

		i = conf->len;
		if ((( i + 1 ) % BUFFER ) == 0 )
			conf->items = (void *)realloc( conf->items, sizeof( config_item_t ) * ( conf->len + BUFFER ));

		conf->items[i].key  = get_word( buf, 1 );
		conf->items[i].data = get_word( buf, 2 );
		
		#ifdef DEBUG
		printf( "[%u] key: \"%s\", data: \"%s\"\n", conf->len, conf->items[i].key, conf->items[i].data );
		#endif
		conf->len++;
	}

	return conf;
}

char *get_data( config_t *config, char *key ){
	int i;
	for ( i = 0; i < config->len; i++ ){
		if ( strcmp( key, config->items[i].key ) == 0 )
			return config->items[i].data;
	}
	return NULL;
}

char *get_word( char *thing, int wordno ){
        #define VAR_LEN 64
        char *buf = malloc( VAR_LEN );
        bool inword = false;
        int i = 0, j = 0, l = 0, slen = strlen( thing );
        for ( i = 0; j <= wordno && i < slen && l < VAR_LEN; i++ ){
                if (( thing[i] > 'A' && thing[i] < 'z' ) || ( thing[i] >= '.' && thing[i] <= '9' )){ 
                        if ( !inword ){
                                j++; 
                                inword = true; 
                        }   
                        if ( j == wordno ) 
                                buf[l++] = thing[i];
                } else inword = false;
        }   
        buf[l] = '\0';
        return buf;
}

#endif
