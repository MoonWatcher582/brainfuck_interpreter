#include "brainfuck.h"

char brainfuck[ARR_SIZE];	/*Brainfuck program runs over a large array*/
int arr_index;			/*Current index in the array*/
int count;			/*Current index in the executable file*/
FILE* fp;			/*The executable file*/
int flag;			/*Error check*/

int main(int argc, char **argv){
	char c;		
	count = 0;	
	arr_index = 0;
	
	if(argc < 2){
		printf("No brainfuck source file specified\n");
		return 1;
	}else if(argc > 2){
		printf("Too many arguments - interpreter only runs one file\n");
		return 1; 
	}
	
	if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0){
		printf("brainfuck <filename>\n");
		printf("Enter a brainfuck file to have it executed\n");
		return 0;
	}
	
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("Invalid file specified\n");
		return 1;
	}	
	
	c = fgetc(fp);
	count++;
	while(c != EOF){
		if(c == ' ' || c == '\n' || c == '\t'){
			c = fgetc(fp);
			continue;
		}
		
		printf("%c\n", c);		
		flag = process_char(c);
		
		if(!flag){
			printf("Error at command %d; %c\n", count,c);
			return 1;
		}
		
		c = fgetc(fp);
		count++;
	}
}

int process_char(char c){
	if(c == '+'){
		brainfuck[arr_index]++;
	}else if(c == '-'){
		brainfuck[arr_index]--;
	}else if(c == '>'){
		arr_index++;
	}else if(c == '<'){
		arr_index--;
	}else if(c == '.'){
		printf("%c", brainfuck[arr_index]);
	}else if(c == ','){

	}else if(c == '['){
		int loop = arr_index;
		FILE* temp = fopen("temp", "w");
		c = fgetc(fp);
		while(c != ']'){
			fputs(&c, temp);
			c = fgetc(fp);
			if(c == '['){
				process_char(c);
			}
		}
	}else if(c == ']'){
		while(loop){
			
		}	
	}else{
		return 0;
	}
	return 1;
}
