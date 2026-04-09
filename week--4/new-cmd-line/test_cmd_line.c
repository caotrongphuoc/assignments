#include <stdio.h>
#include <string.h>
#include "new_cmd_line.h"

static int called = -1;
void h_help(uint8_t* args) { called = 0; }
void h_led(uint8_t* args)  { called = 1; }

my_cmd_t table[] = 
{
	{"help", h_help},
	{"led",  h_led},
	{NULL, NULL}
};

int main() 
{
	uint8_t ret;

	//case 1: null table 
	ret = my_cmd_parse(NULL, (uint8_t*)"help");
	printf("test1 null_table:  %s\n", ret == CMD_TABLE_NULL ? "PASS" : "FAIL");

	//case 2: cmd hop le
	called = -1;
	ret = my_cmd_parse(table, (uint8_t*)"help");
	printf("test2 valid_cmd:   %s\n", (ret == CMD_OK && called == 0) ? "PASS" : "FAIL");

	//case 3: cmd khong ton tai 
	called = -1;
	ret = my_cmd_parse(table, (uint8_t*)"reboot");
	printf("test3 not_found:   %s\n", (ret == CMD_NOT_FOUND && called == -1) ? "PASS" : "FAIL");

	//case 4: cmd qua dai
	char big[40];
	memset(big, 'x', 39);
	big[39] = 0;
	ret = my_cmd_parse(table, (uint8_t*)big);
	printf("test4 too_long:    %s\n", ret == CMD_TOO_LONG ? "PASS" : "FAIL");

	return 0;
}