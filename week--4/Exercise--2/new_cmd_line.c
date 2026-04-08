#include <string.h>
#include "new_cmd_line.h"

uint8_t my_cmd_parse(my_cmd_t* table, uint8_t* input) 
{
	uint8_t cmd[CMD_MAX_SIZE];
	uint8_t len = 0;
	uint8_t i = 0;

	if (table == NULL) return CMD_TABLE_NULL;

	//tach ten command tu input
	while (input[len] != '\0' && input[len] != ' ' && input[len] != '\r' && input[len] != '\n') 
    {
		len++;
	}

	if (len == 0)             return CMD_NOT_FOUND;
	if (len >= CMD_MAX_SIZE)  return CMD_TOO_LONG;

	//copy command ra buffer roi null-terminate 
	memcpy(cmd, input, len);
	cmd[len] = '\0';

	//duyet bang tim command trung khop 
	while (table[i].cmd != NULL) {
		if (strcmp((const char*)cmd, table[i].cmd) == 0) {
			table[i].func(input);
			return CMD_OK;
		}
		i++;
	}

	return CMD_NOT_FOUND;
}