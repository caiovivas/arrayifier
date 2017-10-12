#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* sanitize(char* src);
int except(char* msg);

int main(int argc, char *argv[]){
	if(argc < 3 || argc > 3)except("Bad arguments, please enter source and output filenames.");
	FILE* fp;
	fp = fopen(argv[1], "r");
	if(!fp)except("Source file does not exist.");
	FILE* out;
	out = fopen(argv[2], "w");
	char buf[255];
	fprintf(out, "{");
	int total = 0;
	while(fgets(buf, 255, (FILE*)fp)){
		sanitize(buf);
		
		if(!total){
			fprintf(out, "\"%s\"", buf);
		}
		else
			fprintf(out, ",\"%s\"", buf);
		total++;
	}
	fprintf(out, "}");
	fclose(fp);
	fclose(out);
	printf("Successfully arrayified %d elements to \"%s\"!", total, argv[2]);
	return 0;
}

char* sanitize(char* src){
	char* n = src;
	do{
		n[strcspn(n, " ")] = 0;
		n[strcspn(n, "\r\n")] = 0;
	}while(n[strcspn(n, " ")] || n[strcspn(n, "\r\n")]);
}

int except(char* msg){
	printf("Error: %s", msg);
	exit(0);
}