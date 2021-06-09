#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

char buffer[30];
int i=0;
void S();
void E();
void T();
void T1();
void F();
void A();
void E1();

void S()
{
	printf("\nThe Production S => A=E  is used");
	A();
	if(buffer[i]=='=')
	{
		printf("\n......Match the terminal =");
		i++;
		E();
	}
	else
	{
		printf("\nError Condition ");
		exit(0);
	}
}


void A()
{
	if(isalpha(buffer[i]))
	{
		printf("\n......Match the terminal %c",buffer[i]);
		i++;
	}
	else
	{
		printf("\nError condition");
		exit(0);
	}
}



void E()
{
	printf("\nThe Production E => T E1 is used");
	T();
	E1();
}

void  E1()
{
	if(buffer[i]=='+')
	{
	printf("\nThe production  E1 => +T E1 is used");
	printf("\n......Match the terminal +");
	i++;
	T();
	E1();
	}
	else
	printf("\nThe production E1 => <Epsilon> is used");
}

void T()
{
	printf("\nThe Production T => F T1 is used");
	F();
	T1();
}

void  T1()
{
	if(buffer[i]=='*')
	{
	printf("\nThe production  T1 => *F T1 is used");
	printf("\n......Match the terminal *");
	i++;
	F();
	T1();
	}
	else
	printf("\nThe production T1 => <Epsilon> is used");
}

void F()
{
	if(buffer[i]=='(')
	{
		printf("\nThe production  F => (E) is used");
		printf("\n......Match the terminal (");
		i++;
		E();
		if(buffer[i]==')')
		{
				printf("\n.....Match the terminal )");
				i++;
		}
		else
		{
			printf("\nError condition");
			exit(0);
		}
		return;
	}

	if(buffer[i]=='a')
	{
		printf("\nThe production  F => a is used");
		printf("\n......Match the terminal a");
		i++;
		return;
	}
	if(buffer[i]=='b')
	{
		printf("\nThe production  F => b is used");
		printf("\n......Match the terminal b");
		i++;
		return;
	}
	printf("\nError condition");
	exit(0);
}


void main()
{ 
   printf("\nEnter input string:");
   gets(buffer);
   S();
   printf("\nIt is a valid string");
}
