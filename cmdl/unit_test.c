#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cmdl.h"
#include "cmdl.c"

//test setup
static int called = -1;
void handler_help(uint8_t* args) { (void)args; called = 0; }
void handler_led(uint8_t* args)  { (void)args; called = 1; }

cmdl_t table[] = {
	{"help", handler_help},
	{"led",  handler_led},
	{NULL, NULL}
};

int main() {
	uint8_t ret;

	// test 1: null table
	ret = cmdl_parse(NULL, (uint8_t*)"help ");
	printf("test1 null_table:   %s\n", ret == CMDL_TABLE_NULL ? "PASS" : "FAIL");

	// test 2: cmd available
	called = -1;
	ret = cmdl_parse(table, (uint8_t*)"help ");
	printf("test2 valid_cmd:    %s\n", (ret == CMDL_OK && called == 0) ? "PASS" : "FAIL");

	//test 3: cmd not exist
	called = -1;
	ret = cmdl_parse(table, (uint8_t*)"reboot ");
	printf("test3 not_found:    %s\n", (ret == CMDL_NOT_FOUND && called == -1) ? "PASS" : "FAIL");

	//test 4: cmd too long
	char big[40];
	memset(big, 'a', 39);
	big[39] = 0;
	ret = cmdl_parse(table, (uint8_t*)big);
	printf("test4 too_long:     %s\n", ret == CMDL_TOO_LONG ? "PASS" : "FAIL");

	return 0;
}
