#ifndef _clip_clipmsg_h
#define _clip_clipmsg_h
#include <stdint.h>

enum c_msg_act {
	C_MSG_SEND,
	C_MSG_GET,
	C_MSG_CLEAR,
	C_MSG_ERROR
};

enum c_msg_error {
	E_MSG_NODATA,
	E_MSG_TOOMUCHINFO,
	E_MSG_NOCLIP,
	E_MSG_NOUSER,
	E_MSG_OLDVERSION
};

typedef struct c_msg {
	uint32_t user_hash;
	uint32_t clip_no;
	uint32_t action;
	uint32_t status;
	uint32_t len;
	uint32_t version;
	unsigned char *data;
} c_msg_t;

#endif
