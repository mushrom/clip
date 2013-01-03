#ifndef _clip_config_h
#define _clip_config_h
#include <string.h>
#include <stdio.h>

#define MAX_STR_LEN 	256
#define BUFFER		8

typedef struct config_item {
	char *key;
	char *data;
} config_item_t;

typedef struct config {
	config_item_t *items;
	unsigned int len;
} config_t;

typedef enum { false, true } bool;

config_t *parse_file( char *file );
char *get_data( config_t *config, char *key ); 
char *get_word( char *thing, int wordno );
#endif
