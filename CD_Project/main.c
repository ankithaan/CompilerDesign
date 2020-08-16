#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "lex.h"  //lex.h is the header file to include the lexical analyzer to get the tokens for the code sinppet

char item[50];

 //char gram[][][] is the grammar for the given code sinppet

 char gram[25][25][25]=
 {
     {"S","K","$"},
     {"S","Q","M","U","I","E","I","SC","$"},
     {"K","program","A","SC","$"},
     {"K","begin","$"},
     {"K","write","(","\'","P","\'",")","$"},
     {"K","readln","(","C",")","$"},
     {"K","writeln","(","C",")","$"},
     {"K","end","$"},
     {"A","p_name","$"},
     {"SC",";","$"},
     {"P","string","$"},
     {"C","var","$"},
     {"Q","variable","$"},
     {"I","ab","$"},
     {"I","cd","$"},
     {"M",":","$"},
     {"U","=","$"},
     {"E","+","$"}
  };

//char par_table[][][] is the matrix form of the parse table for the considered grammar

 char par_table[25][25][25]=
 {
     {"S","program","0"},
     {"S","begin","0"},
     {"S","write","0"},
     {"S","readln","0"},
     {"S","writeln","0"},
     {"S","end","0"},
     {"S","variable","1"},
     {"K","program","2"},
     {"K","begin","3"},
     {"K","write","4"},
     {"K","readln","5"},
     {"K","writeln","6"},
     {"K","end","7"},
     {"A","p_name","8"},
     {"SC",";","9"},
     {"P","string","10"},
     {"C","var","11"},
     {"Q","variable","12"},
     {"I","ab","13"},
     {"I","cd","14"},
     {"M",":","15"},
     {"U","=","16"},
     {"E","+","17"}
};
int prod(int x , char str[]);
char stack[40][40];
char queue[40][40];
int l=1,i,front=0,rear=-1,s=-1,r;
char str[40];
char nwstr[40];
int main()
{
     int x;
     printf("\n\n\t\t--------------LEXICAL ANALYSER--------------\n\n");
     tokenn();
     printf("\n\n\t\t--------------SYNTAX ANALYSER--------------\n");
     start : strcpy(stack[r],"S");

     printf("\nLINE %d : " , l);
     while(strcmp(queue[rear],"$")!=0)
     {
         rear++;
         s++;
         printf("%s ",token[s]);
         strcpy(queue[rear],token[s]);
    }
    printf("\n");
    l1: strcpy(nwstr,queue[front]);
    while(strcmp(nwstr,"$")!=0)
     {
         for(i=0;i<25;i++)
         {
             strcpy(str,stack[r]);
             strcpy(nwstr,queue[front]);
             if((strcmp(par_table[i][0],str)==0)&&(strcmp(par_table[i][1],nwstr)==0))
             {

                 x=atoi(par_table[i][2]);
                 r=prod(x,str);
             }
             else if((strcmp(str,nwstr))==0)
             {
                 strcpy(item,queue[front]);
                 printf("\t%s matched\n",item);
                 front++;
                 strcpy(str,queue[front]);
                 strcpy(item,stack[r]);

                 r++;
                 goto l1;
             }
         }
     }

    if(strcmp(stack[r],"\0")!=0)
     {
        printf("\tNot correct syntax\n");
     }
     else if(token[s+1][0]=='\0')
     {
         printf("LINE %d parsed. Correct Syntax\n" , l);
         printf("\n\t-----------THANK YOU-------------\n");
         exit(0);
     }
     else
    {
        printf("LINE %d parsed. Correct Syntax\n" , l);
         l=l+1;
         rear=-1;
         front=0;
        goto start;
    }
    return 0;
}


int prod(int x,char str[])
{
     char cpstr[40];
     int y=1,count_no=0;
     printf("\t%s ->",gram[x][0]);
    l2 : strcpy(cpstr,gram[x][y]);
     while(strcmp(cpstr,"$")!=0)
     {
         strcpy(str,cpstr);
         printf("%s",str);
         strcpy(stack[r],str);
         count_no++;
         r++;y++;
         goto l2;
     }

    if(count_no>r)
    {
         r = count_no-r;
    }
    else
    {
         r = r-count_no;
    }
    printf("\n");
    return r;
}