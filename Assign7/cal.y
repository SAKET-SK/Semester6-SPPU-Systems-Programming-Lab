%{
#include<stdio.h>
#include<stdlib.h>
void yyerror(char *);
int pw=1,i;
%}

%token NUM
%left '+' '-'
%left '*''/'
%left '^'
%left '('')'
%%

op:expn{
		printf("Answer:%d\n",$1);
	 };

expn:'-'expn{$$=-$2;}
    |expn '+' expn{$$=$1+$3;}
    |expn'-'expn{$$=$1-$3;}
    |expn'*'expn{$$=$1*$3;}
    |expn'/'expn
	{
		if($3==0)
		{
			printf("Divide by zero Error!!");
			exit(0);
		}
		else
		{
			$$=$1/$3;
		}
	}
    |'('expn')'{$$=$2;}
    |expn'^'expn
	{
		for(i=0;i<$3;i++)
		{
			pw=pw*$1;
		}
		$$=pw;
	}
    |NUM{$$=$1;}
    ;
%%

main()
{
	printf("Enter Expression:");
	yyparse();
}
void yyerror(char *str)
{
	printf("%s",str);
	exit(0);
}

yywrap()

{ 
 
return(1);

}

