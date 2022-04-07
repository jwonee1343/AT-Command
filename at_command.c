#include "at_command.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

static inline const char *copy_string_until(const char *from, char *to, char next_ch)
{
	while (*from != next_ch) {
		if (!*from)
			return NULL;

		*(to++) = *(from++);
	}
	*to = '\0';

	return from;
}

static inline bool string_compare(const char *s1, const char *s2)
{
	while (*s1 && s2) {
		if (*s1 != *s2)
			return false;
	}

	return *s1 == *s2;
}

int16_t at_cmd_parse_rsp(const char *s, char *cmd, char *params)
{
	*cmd = '\0';
	*params = '\0';

	if (*s == '+') { // "+"
		s++;
		s = copy_string_until(s, cmd, '=');		// "+{cmd}="
		if (s) {
			s++;
			s = copy_string_until(s, cmd, '\r');	// "+{cmd}={params}\r"
			if (s) {
				if (*s == '\n')			// "+{cmd}={params}\r\n"
					return AT_PARAMS;
			}
		}
	} else {
		if (string_compare(s, "\r\n"))			// "\r\n"
			return AT_NO_DATA;
		else if (string_compare(s, "OK\r\n"))		// "OK\r\n"
			return AT_OK;
		else if (string_compare(s, "ERROR\r\n"))	// "ERRROR\r\n"
			return AT_ERROR;
	}

	return AT_INVALID;
}

uint16_t at_cmd_put_test(char *s)
{
	uint16_t i = 0;

	s[i++] = 'A';
	s[i++] = 'T';
	s[i++] = '\r';
	s[i++] = '\n';
	s[i] = '\0';

	return i;
}

uint16_t at_cmd_put_cmd(char *s, const char *cmd)
{
	uint16_t i = 0;

	s[i++] = 'A';
	s[i++] = 'T';
	s[i++] = '+';
	while (*cmd)
		s[i++] = *(cmd++);

	s[i++] = '\r';
	s[i++] = '\n';
	s[i] = '\0';

	return i;
}

uint16_t at_cmd_put_cmd_param(char *s, const char *cmd, char *fmt, ...)
{
	uint16_t i = 0;
	va_list params;

	s[i++] = 'A';
	s[i++] = 'T';
	s[i++] = '+';
	while (*cmd)
		s[i++] = *(cmd++);

	s[i++] = '=';
	va_start(params, fmt);
	i += vsprintf(s + i, fmt, params);
	va_end(params);
	s[i++] = '\r';
	s[i++] = '\n';
	s[i] = '\0';

	return i;
}
