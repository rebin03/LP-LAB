%{ 
%} 

%s Q1 Q2 Q3 DEAD 

%% 
<INITIAL>1 BEGIN Q1; 
<INITIAL>0 BEGIN Q2; 
<INITIAL>[^01\n] BEGIN DEAD; 
<INITIAL>\n BEGIN INITIAL; {printf("Accepted\n");} 

<Q1>1 BEGIN INITIAL; 
<Q1>0 BEGIN Q3; 
<Q1>[^01\n] BEGIN DEAD; 
<Q1>\n BEGIN INITIAL; {printf("Not Accepted\n");} 

<Q2>1 BEGIN Q3; 
<Q2>0 BEGIN INITIAL; 
<Q2>[^01\n] BEGIN DEAD; 
<Q2>\n BEGIN INITIAL; {printf("Not Accepted\n");} 

<Q3>1 BEGIN Q2; 
<Q3>0 BEGIN Q1; 
<Q3>[^01\n] BEGIN DEAD; 
<Q3>\n BEGIN INITIAL; {printf("Not Accepted\n");} 


<DEAD>[^\n] BEGIN DEAD; 
<DEAD>\n BEGIN INITIAL; {printf("Invalid\n");} 

%% 

int main() 
{ 
	printf("Enter String\n"); 
	yylex(); 
	return 0; 
} 
int yywrap()
{
    return 1;
}