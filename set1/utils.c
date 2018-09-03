#include "utils.h"

uint8_t alpha[64]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int init_buffer(Buffer *res, char *argv){
	size_t len=strlen(argv);
	res->len=len;
	res->str=malloc(sizeof(uint8_t)*len);
	if(res->str==NULL){
		return 1;
	}
	return raw_string_to_buff(res, argv, len);
}

int init_empty_buffer(Buffer *res, size_t len){
	res->len=len;
	res->str=malloc(sizeof(uint8_t)*len);
	if(res->str==NULL){
		return 1;
	}
	return 0;
}

void print_hex(Buffer buff){
	size_t i=0;
	for(i=0; i<buff.len; i++){
		fprintf(stdout, "%x", buff.str[i]);
	}
	fprintf(stdout,"\n");
	return;
}

void print_b64(Buffer *buff){
	size_t size=buff->len;
	while(size>0){
		size_t pos=buff->len-size;
		if(size>=3){
		
			fprintf(stdout,"%c%c%c%c", alpha[buff->str[pos]>>2], alpha[((buff->str[pos]&0x03)<<4)+(buff->str[pos+1]>>4)], alpha[((buff->str[pos+1]&0x0F)<<2)+(buff->str[pos+2]>>6)], alpha[(buff->str[pos+2]&0x3F)]);
			size-=3;
		}else if(size==2){
			fprintf(stdout,"%c%c%c=", alpha[buff->str[pos+0]>>2], alpha[((buff->str[pos+0]&0x03)<<4)+(buff->str[pos+1]>>4)], alpha[((buff->str[pos+1]&0x0F)<<4)]);
			size-=2;
		}else{
			fprintf(stdout, "%c%c==", alpha[(buff->str[pos]>>2)], alpha[(buff->str[pos]&0x03)<<4]);
			fprintf(stdout,"\n");
			return;
		}
	}
	fprintf(stdout,"\n");
	return;
}

int compare(Buffer buff1, Buffer buff2){
	int res=1;
	size_t i=0;
	if(buff1.len != buff2.len){
		res=0;
	}
	
	for(i=0; i<buff1.len; i++){
		if(buff1.str[i]!=buff2.str[i]){
			res=0;
		}
	}
	return res;
}

int raw_string_to_buff(Buffer* res, char* str, size_t len){
	size_t start=0;
	size_t j=0;
	if(len&1==1){
		res->len=(len+1)>>1;
		if(str[0]>=48 && str[0]<=57){
			res->str[0]=str[0]-48;
		}else if(str[0]>=65 && str[0]<=70){
			res->str[0]=str[0]-55;
		}else if(str[0]>=97 && str[0]<=102){
			res->str[0]=str[0]-87;
		}
		else{
			return 1;
		}
		str+=1;
		j=1;
	}else{	
		res->len=(len>>1);
	}
	
	for(size_t i=start; i<len; i++){
		if((i&1)==0){
			if(str[i]>=48 && str[i]<=57){
				res->str[j]=(str[i]-48)<<4;
			}else if(str[i]>=65 && str[i]<=70){
				res->str[j]=(str[i]-55)<<4;
			}else if(str[i]>=97 && str[i]<=102){
				res->str[j]=(str[i]-87)<<4;
			}
			else{
				return 1;
			}
		}
		else{
			if(str[i]>=48 && str[i]<=57){
				res->str[j]+=(str[i]-48);
			}else if(str[i]>=65 && str[i]<=70){
				res->str[j]+=(str[i]-55);
			}else if(str[i]>=97 && str[i]<=102){
				res->str[j]+=(str[i]-87);
			}
			else{
				return 1;
			}
			j++;
		}
	}
	return 0;
}

int xor_opti(Buffer *res, Buffer buff1, Buffer buff2){
	if(buff1.len != buff2.len){
		return 1;
	}
	
	for(size_t i=0; i<buff1.len; i++){
		res->str[i] = buff1.str[i] ^ buff2.str[i];
	}
	return 0;
}
