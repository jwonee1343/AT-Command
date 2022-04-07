#include <stdarg.h>
#include <stdint.h>

enum at_cmd_rsp_type {
	AT_OK		= 1,	// "OK\r\n"
	AT_ERROR 	= 2,	// "ERROR\r\n"
	AT_PARAMS 	= 3,	// "+{cmd}={params}\r\n"
	AT_NO_DATA 	= 4,	// "\r\n"
	AT_INVALID 	= -1,	// Invalid format
};

int16_t at_cmd_parse_rsp(const char *s, char *cmd, char *params);
uint16_t at_cmd_put_test(char *s);
uint16_t at_cmd_put_cmd(char *s, const char *cmd);
uint16_t at_cmd_put_cmd_param(char *s, const char *cmd, char *fmt, ...);