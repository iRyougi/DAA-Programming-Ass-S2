#include<stdio.h>
#include"lib.h"

int main(int argc, char *argv[]){
	printf("This is only an example.\n");
	printf("The input file is \"%s\".\n",argv[1]);
	printf("The output file should be \"%s_out\".\n",argv[1]);
	return 0;
}