#include <stdio.h>
#include "makehelper.h"
#include <string.h>
#include <stdlib.h>
void readMakefile(val *v){
	FILE *make=fopen("Makefile","r");
	if(make==NULL){
		printf("Old Makefile doesn't exist");
		return;
	}
	char buffer[250];
	memset(buffer,0,sizeof(buffer));
	char *p;
	while((fgets(buffer,250,make))){
		if(buffer[strlen(buffer)-1]=='\n')	buffer[strlen(buffer)-1]='\0';
		if(strstr(buffer,"MAIN=")){
			//	p=strfr(buffer,"MAIN =","");
			p=strchr(buffer,'=')+1;
			//		assign(v->MAIN,p);
			memmove(v->MAIN,p,strlen(p));
		//	printf("%s\nMAIN=%s\n",p,v->MAIN);
			//	free(p);
		}
		else if(strstr(buffer,"SRCS=")){
			//	p=strfr(buffer,"SRCS =","");
			p=strchr(buffer,'=')+1;
			//assign(v->SRCS,p);
			memmove(v->SRCS,p,strlen(p));
		//	printf("%s\nSRCS=%s\n",p,v->SRCS);
			//	free(p);
		}
		else if(strstr(buffer,"INCLUDES=")){
			//	p=strfr(buffer,"INCLUDES =","");
			p=strchr(buffer,'=')+1;
			//	assign(v->INCLUDES,p);
			memmove(v->INCLUDES,p,strlen(p));
		//	printf("%s\nINCLUDES=%s\n",p,v->INCLUDES);
			//	free(p);
		}
		else if(strstr(buffer,"LIBS=")){
			//          p=strfr(buffer,"LIBS =","");
			p=strchr(buffer,'=')+1;
			//          assign(v->LIBS,p);
			memmove(v->LIBS,p,strlen(p));
		//	printf("%s\nLIBS=%s\n",p,v->LIBS);
			//         free(p);
		}
		else if(strstr(buffer,"CFLAGS=")){
			//                 p=strfr(buffer,"CFLAGS =","");
			//                 assign(v->CFLAGS,p);
			//                 free(p);
			p=strchr(buffer,'=')+1;
			//		    assign(v->CFLAGS,p);
			memmove(v->CFLAGS,p,strlen(p));
		//	printf("%s\nCFLAGS=%s\n",p,v->CFLAGS);
		}
		else if(strstr(buffer,"LFLAGS=")){
			//          p=strfr(buffer,"LFLAGS =","");
			p=strchr(buffer,'=')+1;
			// assign(v->LFLAGS,p);
			memmove(v->LFLAGS,p,strlen(p));
		//	printf("%s\nLFLAGS=%s\n",p,v->LFLAGS);
			//          free(p);
		}
		else if(strstr(buffer,"CC=")){
			//        p=strfr(buffer,"CC =","");
			//	  p=strchr(buffer,'=')+1;
			p=strchr(buffer,'=')+1;
			memmove(v->CC,p,strlen(p));
            if(!strcmp(v->CC,"clang"))
                assign(v->EXT,".c");
            else if(!strcmp(v->CC,"clang++"))
                assign(v->EXT,".cpp");
		//	assign(v->CC,p);
		//	printf("%s\nCC=%s\n",p,v->CC);
			//           free(p);
		}
		else if(strstr(buffer,"End of variables")){
			fclose(make);
			break;
		}

		memset(buffer,0,sizeof(buffer));

	}
}
