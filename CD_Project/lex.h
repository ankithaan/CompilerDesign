#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char token[40][40];
int p=0,q;

int isKeyword(char buffer[]){
	char keywords[32][10] = {"program","write","writeln","readln","begin","end"};
	int i, flag = 0;
	for(i = 0; i < 5; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}
	return flag;
}

int tokenn()
{
	char ch, buffer[15], operators[] = "+-*/%=:" , symbols[] = ";()\'" ;
	FILE *fp;
	int i,j=0;

	fp = fopen("file.txt","r");

	if(fp == NULL)
    {
		printf("error while opening the file\n");
		exit(0);
	}

	while((ch = fgetc(fp)) != EOF)
    {
   		for(i = 0; i < 7; ++i)
   		{
   			if(ch == operators[i])
            {
                printf("\t\t\t%c\t\t is operator\n", ch);
   				token[p++][0]=ch;
            }
   		}
   		for(i = 0; i < 5; ++i)
   		{
   			if(ch == symbols[i])
   			{
   			    printf("\t\t\t%c\t\t is symbol \n", ch);
   				token[p++][0]=ch;
   			}
        }

   		if(isalnum(ch))
        {
   			buffer[j++] = ch;
   		}
   		else if(ch == '_'){buffer[j++]='_';}
   		else if((ch == ' ' || ch == '\n') && (j != 0))
   		{
   				buffer[j] = '\0';
   				j = 0;
   				if(isKeyword(buffer) == 1)
   				{
   					printf("\t\t\t%s\t\t is keyword\n", buffer);
   					for(q=0;q<strlen(buffer);q++)
                          token[p][q]=buffer[q];
                    p++;
                }
   				else
                {
                     char ty = buffer[0];
                     if(isdigit(ty) || (ty == '_'))
                        printf("\t%s\t\t is not an indentifier\n", buffer);
                     else
                    {
                        printf("\t\t\t%s\t\t is identifier\n",buffer);
                        for(q=0;q<strlen(buffer);q++)
                          token[p][q]=buffer[q];
                        p++;
                    }
   				}
   		}
        if(ch=='\n')
        {
            token[p++][0]='$';
        }

    }
    token[p][0]='\0';
    printf("\n");

	fclose(fp);

	return 1;
}