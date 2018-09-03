#include <stdio.h>
#include "utils.h"

int main(int argc, char *argv[]){
	Buffer *buff1=malloc(sizeof(Buffer));
	Buffer *buff2=malloc(sizeof(Buffer));
	Buffer *res=malloc(sizeof(Buffer));
	if(res==NULL || buff1==NULL || buff2==NULL){
		fprintf(stderr, "Failed in malloc buffer\n");
		return 1;
	}
	if(init_buffer(buff1, argv[1])!=0){
		fprintf(stdout,"Error during allocation\n");
		return 1;
	}

/*	if(init_buffer(buff2, argv[2])!=0){
		fprintf(stdout,"Error during allocation\n");
		return 1;
	}
	
	if(init_empty_buffer(res, buff1->len)!=0){
		fprintf(stdout, "Error during allocation res\n");
		return 1;
	}

	if(xor_opti(res, *buff1, *buff2)!=0){
		fprintf(stderr, "Bad length\n");
		return 1;
	}
*/	
	print_hex(*buff1);
	print_b64(buff1);

	return 0;
}
