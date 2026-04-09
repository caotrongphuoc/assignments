#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define MAX_CMD_SIZE 32
#define CMD_SUCCESS       0
#define CMD_NOT_FOUND     1
#define CMD_TOO_LONG      2
#define CMD_TBL_NOT_FOUND 3

typedef void (*pf_cmd_func)(uint8_t*);
typedef struct 
{
	const char* cmd;
	pf_cmd_func func;
} cmd_line_t;

uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command) 
{
	uint8_t cmd[MAX_CMD_SIZE];
	uint8_t* p = command;
	uint8_t i = 0, j = 0;
	if (cmd_table == NULL) return CMD_TBL_NOT_FOUND;
	while (*p) 
	{
		if (*p == ' ' || *p == '\r' || *p == '\n') { cmd[i] = 0; break; }
		else { cmd[i++] = *(p++); if (i >= MAX_CMD_SIZE) return CMD_TOO_LONG; }
	}
	while (cmd_table[j].cmd) 
	{
		if (strcmp((const char*)cmd_table[j].cmd, (const char*)cmd) == 0) 
		{
			cmd_table[j].func(command);
			return CMD_SUCCESS;
		}
		j++;
	}
	return CMD_NOT_FOUND;
}

//test setup
static int called = -1;
void handler_help(uint8_t* args) { called = 0; }
void handler_led(uint8_t* args)  { called = 1; }

cmd_line_t table[] = 
{
	{"help", handler_help},
	{"led",  handler_led},
	{NULL, NULL}
};

int main() 
{
	uint8_t ret;

	// test 1: null table 
	ret = cmd_line_parser(NULL, (uint8_t*)"help ");
	printf("test1 null_table:   %s\n", ret == CMD_TBL_NOT_FOUND ? "PASS" : "FAIL");

	// test 2: cmd available 
	called = -1;
	ret = cmd_line_parser(table, (uint8_t*)"help ");
	printf("test2 valid_cmd:    %s\n", (ret == CMD_SUCCESS && called == 0) ? "PASS" : "FAIL");

	//test 3: cmd not exist 
	called = -1;
	ret = cmd_line_parser(table, (uint8_t*)"reboot ");
	printf("test3 not_found:    %s\n", (ret == CMD_NOT_FOUND && called == -1) ? "PASS" : "FAIL");

	//test 4: cmd too long 
	char big[40];
	memset(big, 'a', 39);
	big[39] = 0;
	ret = cmd_line_parser(table, (uint8_t*)big);
	printf("test4 too_long:     %s\n", ret == CMD_TOO_LONG ? "PASS" : "FAIL");

	return 0;
}