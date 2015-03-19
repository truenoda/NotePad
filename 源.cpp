#include <iostream>
#include <stdio.h>
#include <string.h>
#include<fstream>
#include<iomanip>
using namespace std;
ofstream fout("e:/token.txt"); 
#define TokenSize 81
#define Error -1
#define Identifier 1
#define KeyWord 2
#define RNumber 3
#define INumber 33
#define LNumber 34
#define LPar 4
#define RPar 5
#define Plus 6
#define PlusPlus 7
#define PlusEq 8
#define Minus 9
#define MinusMinus 10
#define MinusEq 11
#define Star 12
#define StarEq 13
#define LT 14
#define Lshift 15
#define LSEQ 16
#define LE 17
#define LSB 18
#define RSB 19
#define Comma 20
#define EQ 21
#define EQEQ 22
#define Dot 23
#define MAXTOKEN 100
char ch,token[TokenSize+1],*KeyWords[]={"auto","break","case","char","const","continue","default","do","double",
	"else","enum","extern","float","for","goto","if","int","long","register","return","short",
	"signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
"volatile","while"};
int const KWsize=sizeof(KeyWords)/sizeof(char*);
int IsLetter()
{
	return ch<='Z'&&ch>='A'||ch<='z'&&ch>='a'||ch=='_';
}
int IsDigit()
{
	return ch<='9'&&ch>='0';
}
int IsKey()
{
	int low,up,m,r;
	low=0;up=KWsize-1;
	while(low<=up)
	{
		m=(low+up)/2;
		if((r=strcmp(token,KeyWords[m]))==0)
			return m+1;
		else{
			if(r<0)
				up=m-1;
			else
				low=m+1;
		}
	}
	return 0;

}
int e_part(int *i)
{
	if(IsDigit()){
		while(IsDigit()){
			token[(*i)++]=ch;
			ch=getchar();
		}
		ungetc(ch,stdin);
		token[*i]='\0';
		return 1;
	}
	else
		if(ch=='+'||ch=='-')
		{
			token[(*i)++]=ch;
			ch=getchar();
			if(IsDigit())
			{
				while(IsDigit())
				{
					token[(*i)++]=ch;
					ch=getchar();
				}
				ungetc(ch,stdin);
				token[*i]='\0';
				return 1;
			}
			else return 0;
		}
		else return 0;
}
int GetToken()
{
	int line=1;
	int i=0,IsInt=1;
	token[0]='\0';
	do{
		ch=getchar();
	}while(ch==' '||ch=='\n'||ch=='\t');
	do 
	{
		line++;
	} while (ch=='\n');
	if(IsLetter())
	{
		while(IsLetter()||IsDigit())
		{
			token[i++]=ch;
			ch=getchar();
		}
		token[i]='\0';
		ungetc(ch,stdin);
		if(IsKey())
			return KeyWord;
		else
			return Identifier;

	}
	else
		if(IsDigit())
		{
			while(IsDigit())
			{
				token[i++]=ch;
				ch=getchar();
			}
			if(ch=='1'||ch=='L')
			{
				token[i++]=ch;
				token[i]='\0';
				return LNumber;
			}
			if(ch=='.')
			{
				IsInt=0;
				token[i++]=ch;
				ch=getchar();
				if(IsDigit())
				{
					while(IsDigit())
					{
						token[i++]=ch;
						ch=getchar();
					}
				}
			}
			if(ch=='e'||ch=='E')
			{
				IsInt=0;
				token[i++]=ch;
				ch=getchar();
				if(e_part(&i))
					return RNumber;
				else
					return Error;
			}
			ungetc(ch,stdin);
			token[i]='\0';
			if(IsInt)
				return INumber;
			else
				return RNumber;
		}
		else
			switch(ch)
		{
			case '.':
				token[i++]='.';
				ch=getchar();
				if(IsDigit())
				{
					while(IsDigit())
					{
						token[i++]=ch;
						ch=getchar();
					}
					if(ch=='e'||ch=='E')
					{
						token[i++]=ch;
						ch=getchar();
						if(e_part(&i))
							return RNumber;
						else
							return Error;
					}
					ungetc(ch,stdin);
					token[i]='\0';
					return RNumber;

				}
				else{
					ungetc(ch,stdin);
					token[i]='\0';
					return Dot;
				}
			case '(':
				token[0]='(';
				token[1]='\0';
				return LPar;
			case ')':
				token[0]=')';
				token[1]='\0';
				return RPar;
			case '+':
				token[0]='+';
				ch=getchar();
				token[1]=ch;
				token[2]='\0';
				if(ch=='=')
					return PlusEq;
				else
					if(ch=='+')
						return PlusPlus;
					else
					{
						ungetc(ch,stdin);
						token[1]='\0';
						return Plus;

					}
			case '-':
				token[0]='-';
				ch=getchar();
				token[1]=ch;
				token[2]='\0';
				if(ch=='=')
					return MinusEq;
				else
					if(ch=='-')
						return MinusMinus;
					else{
						ungetc(ch,stdin);
						token[1]='\0';
						return Minus;
					}
				
			case '*':
				token[0]='*';
				if(ch=='=')
				{
					token[1]='=';
					token[2]='\0';
					return StarEq;
				}
				else
				{
					ungetc(ch,stdin);
					token[1]='\0';
					return Star;
				}
			case '<':
				token[0]='<';
				ch=getchar();
				token[1]=ch;
				token[2]='\0';
				if(ch=='=')
					return LE;
				else
					if(ch=='<')
					{
						ch=getchar();
						if(ch=='=')
						{
							token[2]='=';
							token[3]='\0';
							return LSEQ;
						}
						else{
							ungetc(ch,stdin);
							return Lshift;
						}
					}
					else{
						ungetc(ch,stdin);
						token[1]='\0';
						return LT;
					}
			case '[':
				token[0]='[';
				token[1]='\0';
				return LSB;
			case ']':
				token[0]=']';
				token[1]='\0';
				return RSB;
			case ',':
				token[0]=',';
				token[1]='\0';
				return Comma;
			case '=':
				token[0]='=';
				ch=getchar();
				if(ch=='=')
				{
					token[1]='=';
					token[2]='\0';
					return EQEQ;
				}
				else 
				{
					ungetc(ch,stdin);
					token[1]='\0';
					return EQ;
				}
			default:
				return Error;
		}
}
string Ttype;
string value;
int linenum;
/*
List cifa(char * infn,List t)
{
	string arr="";
	char ch=' ';
	int line=1;
	ifstream fpin;
	fpin.open(infn,ios::in);
	while(fpin.get(ch))
	{
		arr="";
		if(ch==' '||ch=='\t'){}
		else
		{
			if(ch=='\n')
			{
				line++;
			}
			else
			{
				if(IsLetter(ch))
				{
					while(IsLetter(ch)||IsDigit(ch))
					{
						if((ch<='Z')&&(ch>='A'))
							ch=ch+32;
						arr=arr+ch;
						fpin.get(ch);
					}
					fpin.seekg(-1L,ios::cur);//»ØÍË

					if(IsKey(arr))
					{
						Token Tkeyword;
						Tkeyword.linenum=line;
						Tkeyword.Ttype=arr;
						Tkeyword.value=arr;
						t.inserttail(Tkeyword);
					}
					else
					{
						Token Tid;
						Tid.linenum=line;
						Tid.Ttype="id";
						Tid.value=arr;
						t.inserttail(Tid);
					}

				}
				else
					if(IsDigit(ch))
					{
						while(IsDigit(ch))
						{
							arr=arr+ch;
							fpin.get(ch);
						}
						fpin.seekg(-1L,ios::cur);
						Token Tnumber;
						Tnumber.linenum=line;
						Tnumber.Ttype="intc";
						Tnumber.value=arr;
						t.inserttail(Tnumber);
					}
			}
		}
	}
	fpin.close();
	return t;
}
*/
void main()
{
	GetToken();
}
