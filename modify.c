#include "makehelper.h"
#include <stdio.h>
#include <string.h>

void modify(char* data, char* modifier, char flag)
{
    char spacedData[strlen(data)+2];
    spacedData[0] = ' ';
    spacedData[1] = '\0';
    strcat(spacedData,data);

    char *modifierToken=strtok(modifier," ");
    if(flag == 'a')
    {
        do
        {
            if(!strstr(spacedData,modifierToken))
            {
                strcat(spacedData," ");
                strcat(spacedData,modifierToken);
            }
        }while((modifierToken = strtok(NULL," ")));
    }
    else if(flag == 'r')
    {
        do
        { 
            char spacedToken[strlen(modifierToken)+2];
            spacedToken[0] = ' ';
            spacedToken[1] = '\0';
            strcat(spacedToken,modifierToken);
            strrm(spacedData,spacedToken);   
        }while((modifierToken = strtok(NULL," ")));
    }
    strcpy(data,spacedData+1);
}


void edit(val* source, val* modifier, char flag)
{
    if (strcmp(modifier->SRCS, "")) {
        modify(source->SRCS, modifier->SRCS, flag);
    }
    if (strcmp(modifier->INCLUDES, "")) {
        modify(source->INCLUDES, modifier->INCLUDES, flag);
    }
    if (strcmp(modifier->LIBS, "")) {
        modify(source->LIBS, modifier->LIBS, flag);
    }
    if (strcmp(modifier->CFLAGS, "")) {
        modify(source->CFLAGS, modifier->CFLAGS, flag);
    }
    if (strcmp(modifier->LFLAGS, "")) {
        modify(source->LFLAGS, modifier->LFLAGS, flag);
    }
    if (strcmp(modifier->MAIN, "")) {
        modify(source->MAIN, modifier->MAIN, flag);
    }
    if (strcmp(modifier->CC, "")) {
        modify(source->CC, modifier->CC, flag);
    }
}
