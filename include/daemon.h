#ifndef _clip_daemon_h
#define _clip_daemon_h

typedef struct clipboard {
	unsigned int len;
	char *data;
} clipboard_t;

typedef struct user {
	unsigned int user_hash;
	unsigned int clip_num;
	struct clipboard *clips;
}

void init_daemon( config_t *config );

#endif
