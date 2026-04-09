#ifndef NEW_CMD_LINE_H
#define NEW_CMD_LINE_H

#include <stdint.h>

#define CMD_MAX_SIZE 32

#define CMD_OK            0 //in case cmd ok or cmd success
#define CMD_NOT_FOUND     1 //in case not found
#define CMD_TOO_LONG      2 //in case too long
#define CMD_TABLE_NULL    3 //in case null

typedef void (*cmd_func_t)(uint8_t*);

typedef struct {
	const char* cmd;
	cmd_func_t  func;
} my_cmd_t;

uint8_t my_cmd_parse(my_cmd_t* table, uint8_t* input);

#endif
