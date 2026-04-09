#include <string.h>
#include "cmdl.h"

uint8_t cmdl_parse(cmdl_t* table, uint8_t* input) {
	uint8_t cmd[CMDL_MAX_SIZE];
	uint8_t len = 0;
	uint8_t i = 0;

	if (table == NULL) return CMDL_TABLE_NULL;

	//tach ten command tu input
	while (input[len] != '\0' && input[len] != ' ' && input[len] != '\r' && input[len] != '\n') {
		len++;
	}

	if (len == 0)             return CMDL_NOT_FOUND;
	if (len >= CMDL_MAX_SIZE)  return CMDL_TOO_LONG;

	//copy command ra buffer roi null-terminate 
	memcpy(cmd, input, len);
	cmd[len] = '\0';

	//duyet bang tim command trung khop 
	while (table[i].cmd != NULL) {
		if (strcmp((const char*)cmd, table[i].cmd) == 0) {
			table[i].func(input);
			return CMDL_OK;
		}
		i++;
	}

	return CMDL_NOT_FOUND;
}
