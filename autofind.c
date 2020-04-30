#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "makehelper.h"
void findfiles(char *OUT,char *PATERN){
	char command[80]="find -type f -name '*";
	strcat(command,PATERN);
	strcat(command,"' > temp3245");
	system(command);
	FILE *temp=fopen("temp3245","r");
	char b[200];
	while(fscanf(temp,"%199[^\n]\n",b)==1){
		strcat(OUT," ");
		strcat(OUT,b);
	}
	fclose(temp);
}
