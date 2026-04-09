#include <stdio.h>
#include <stdint.h>
#include <string.h>


#define CMDL_MAX_SIZE      32
#define CMDL_OK       	   0
#define CMDL_NOT_FOUND     1
#define CMDL_TOO_LONG      2
#define CMDL_TABLE_NULL    3

typedef void (*cmdl_func_t)(uint8_t*);
typedef struct {
	const char* cmd;
	cmdl_func_t func;
} my_cmdl_t;

uint8_t my_cmd_parse(my_cmdl_t* table, uint8_t* input) {
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

//test setup
static int called = -1;
void handler_help(uint8_t* args) { called = 0; }
void handler_led(uint8_t* args)  { called = 1; }

my_cmdl_t table[] = {
	{"help", handler_help},
	{"led",  handler_led},
	{NULL, NULL}
};

int main() {
	uint8_t ret;

	// test 1: null table
	ret = my_cmd_parse(NULL, (uint8_t*)"help ");
	printf("test1 null_table:   %s\n", ret == CMDL_TABLE_NULL ? "PASS" : "FAIL");

	// test 2: cmd available
	called = -1;
	ret = my_cmd_parse(table, (uint8_t*)"help ");
	printf("test2 valid_cmd:    %s\n", (ret == CMDL_OK && called == 0) ? "PASS" : "FAIL");

	//test 3: cmd not exist
	called = -1;
	ret = my_cmd_parse(table, (uint8_t*)"reboot ");
	printf("test3 not_found:    %s\n", (ret == CMDL_NOT_FOUND && called == -1) ? "PASS" : "FAIL");

	//test 4: cmd too long
	char big[40];
	memset(big, 'a', 39);
	big[39] = 0;
	ret = my_cmd_parse(table, (uint8_t*)big);
	printf("test4 too_long:     %s\n", ret == CMDL_TOO_LONG ? "PASS" : "FAIL");

	return 0;
}
