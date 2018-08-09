#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


struct Buffer{
	size_t len;
	uint8_t *str;
}typedef Buffer;

int init_buffer(Buffer *res, char *argv);
void print_hex(Buffer buff);
void print_b64(Buffer buff);
int compare(Buffer buff1, Buffer buff2);
int raw_string_to_buff(Buffer* res, char* str, size_t len);
int xor_opti(Buffer *res, Buffer buff1, Buffer buff2);
int init_empty_buffer(Buffer *res, size_t len);
