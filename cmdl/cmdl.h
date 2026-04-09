#ifndef __CMDL_H__
#define __CMDL_H__

#include <stdint.h>

#define CMDL_MAX_SIZE 32
#define CMDL_OK            0 //in case cmd ok or cmd success
#define CMDL_NOT_FOUND     1 //in case not found
#define CMDL_TOO_LONG      2 //in case too long
#define CMDL_TABLE_NULL    3 //in case null

typedef void (*cmdl_func_t)(uint8_t*);

typedef struct {
	const char* cmd;
	cmdl_func_t  func;
} cmdl_t;

uint8_t cmdl_parse(cmdl_t* table, uint8_t* input);

#endif //__CMDL_H__
