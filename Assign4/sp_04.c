#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void check(char []);
int repeated(char[]);

char keywords[30][10]={"void","main","include","stdio","conio","int","float","char","printf","scanf","clrscr","do","while","for","switch","if","else","getch","define","return"};
char operators[20][3]={"+","-","/","*","%","<",">","=","&","|","!"};
char spChar[15][3]={"#",".","'","}","{","(",")",";",",","[","]"};
char invToken[5][5]={"@","$","`"};

struct universalSymbolTable
{
	char symbol[10];
	char symType[20];
	char comment[20];
	int index;
}ust[100];

struct terminal
{
	char symbol[10];
	char symbolType[20];
}ter[50];

struct identifier
{
	char symbol[10];
}iden[10];

struct constants
{
	char symbol[10];
}con[10];

int I,J,K,M,R;

void main()
{
	FILE *fp;
	char str[100];
	char c,ch;
	int i;
	
	printf("Enter The Source File Name: ");
	scanf("%s",str);
	fp=fopen(str,"r+");
	if(fp==NULL)
	{
		printf("\nError in opening file");		
		exit(0);
	}
	printf("\n\n\tSOURCE PROGRAM\n\n");
	while(!feof(fp))
	{
		ch=fgetc(fp);
		printf("%c",ch);
	}
	
	
	fseek(fp,0,SEEK_SET);
	while(!feof(fp))
	{
		fgets(str,70,fp);
		check(str);
	}
	fclose(fp);
	printf("\nTERMINAL TABLE\n\n");
	printf("\tINDEX   \tSYMBOL\t\tSYMBOL_TYPE\n\n");
	for(i=0;i<J;i++)
	{
		if(i==40)
		{
			printf("\n\n");
		}
		printf("\t  %d  \t\t %s\t\t%s\n",i,ter[i].symbol,ter[i].symbolType);
	}
		
	printf("\nIDENTIFIER TABLE\n\n");
	printf("\tINDEX\tIDENTIFIER\n\n");
	for(i=0;i<K;i++)
	{
		printf("\t  %d\t   %s\n",i,iden[i].symbol);
	}
		
	printf("\nLITERAL TABLE\n\n");
	printf("\tINDEX\tCONSTANTS\n\n");
	for(i=0;i<M;i++)
	{
		printf("\t  %d\t   %s\n",i,con[i].symbol);
	}
		
	printf("\nUNIVERSAL SYMBOL TABLE\n\n");
	printf("\tSYMBOL\t\tSYMBOL TYPE\tCOMMENT\t\t\tINDEX\n\n");
	for(i=0;i<I;i++)
	{
		if(i==40||i==80)
		{						
			printf("\n\n");
		}
		printf("\t%s\t\t%s\t%s\t  %d\n",ust[i].symbol,ust[i].symType,ust[i].comment,ust[i].index);
	}	
}


void check(char str[100])
{
	int i=0,flag=0,j,k,m;
	char S[10];
	char N[10];
	char c[4];
	while(str[i]!='\n')
	{
		if(str[i]==34)//34 is ascii of "
		{
			i++;
			while(str[i]!=34)
				i++;
		}
		while(str[i]==' '||str[i]=='\t'||str[i]==34)
			i++;
	    if(str[i]=='@'||str[i]=='$'||str[i]=='^')
		{
            printf("\n \tInvalid Token ->%c",str[i]);		
            break;
		}
		if(isalpha(str[i]))
		{
			for(j=0;isalpha(str[i]);i++,j++)
			{
				S[j]=str[i];
			}
			S[j]='\0';
			flag=0;
			for(k=0;k<30;k++)
			{
				if(strcmp(S,keywords[k])==0)
				{
					if(!repeated(S))
					{
						strcpy(ter[J].symbol,S);
						strcpy(ter[J].symbolType,"KEYWORD");
						R=J;
						J++;
					}
					strcpy(ust[I].symbol,S);
					strcpy(ust[I].symType,"TERMINAL");
					strcpy(ust[I].comment,"KEYWORD\t\t");
					ust[I].index=R;
					I++;
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				if(!repeated(S))
				{
					strcpy(iden[K].symbol,S);
					R=K;
					K++;
				}
				strcpy(ust[I].symbol,S);
				strcpy(ust[I].symType,"IDENTIFIER");
				strcpy(ust[I].comment,"\t\t");
				ust[I].index=R;
				I++;
			    flag=1;
			}
		}
		else
		{
			if(isdigit(str[i]))
			{
				for(j=0;isdigit(str[i]);i++,j++)
				{
					N[j]=str[i];
				}
				if(str[i]=='.' && isdigit(str[i+1]) )
				{
					N[j]='.';
					i++;
					j++;
					while(isdigit(str[i]))
					{
						N[j]=str[i];
						j++;
						i++;
					}
				}
				N[j]='\0';
				if(!repeated(N))
				{
					strcpy(con[M].symbol,N);
					R=M;
					M++;
				}
				strcpy(ust[I].symbol,N);
				strcpy(ust[I].symType,"LITERAL");
				strcpy(ust[I].comment,"\t\t\t");
				ust[I].index=R;
				I++;
			}
			else
			{
				c[0]=str[i];
				c[1]='\0';
				for(j=0;j<3;j++)
				{
					if(strcmp(c,invToken[j])==0)
					{
					printf("\t Invalid token !!! -> %c",c);
					}
				}
				for(j=0;j<11;j++)
				{
					if(strcmp(c,spChar[j])==0)
					{

						if(!repeated(c))
						{
							strcpy(ter[J].symbol,c);
							strcpy(ter[J].symbolType,"SPECIAL CHARACTER");
							R=J;
							J++;
						}
						i++;
						strcpy(ust[I].symbol,c);
						strcpy(ust[I].symType,"TERMINAL");
						strcpy(ust[I].comment,"SPECIAL CHARACTER");
						ust[I].index=R;
						I++;
						break;
					}
				}
				for(j=0;j<20;j++)
				{

					if(strcmp(c,operators[j])==0)
					{
						if(!repeated(c))
						{
							strcpy(ter[J].symbol,c);
							strcpy(ter[J].symbolType,"OPERATOR");
							R=J;
							J++;
						}
						i++;
						strcpy(ust[I].symbol,c);
						strcpy(ust[I].symType,"TERMINAL");
						strcpy(ust[I].comment,"OPERATOR\t");
						ust[I].index=R;
						I++;
						break;
					}
				}
			}
		}
	}
}

int repeated(char string[])
{
	int JJ;
	for(JJ=0;JJ<=20;JJ++)
	{
		if(strcmp(string,ter[JJ].symbol)==0||strcmp(string,iden[JJ].symbol)==0||strcmp(string,con[JJ].symbol)==0)
		{
			R=JJ;
			return 1;
		}
	}
	return 0;
}
