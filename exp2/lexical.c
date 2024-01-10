#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 35
FILE *input, *output;
int line_no = 1, token_no = 0;

int isKeyword(char *identifier)
{
    char keyword[MAX_LENGTH][MAX_LENGTH] = {"auto", "break", "case", "char", "const", "continue", "default",
                                            "do", "double", "else", "enum", "extern", "float", "for", "goto",
                                            "if", "int", "long", "register", "return", "short", "signed",
                                            "sizeof", "static", "struct", "switch", "typedef", "union",
                                            "unsigned", "void", "volatile", "while"};
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        if (strcmp(identifier, keyword[i]) == 0)
        { 
            return 1;
        }
    }
    return 0;
}

void printToken(char *token, char *lexeme)
{
    fprintf(output, "%-10d\t %-10d\t\t %-20s\t\t %-20s\n", line_no, token_no, token, lexeme);
}

int main()
{
    char ch, str[MAX_LENGTH];
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    fprintf(output, "%-10s\t %-10s\t\t %-20s\t\t %-20s\n", "Line no.", "Token no.", "Token", "Lexeme");
    while ((ch = fgetc(input)) != EOF)
    {
        if (ch == '#')
        {
            str[0] = ch;
            int i = 1;
            do
            {
                ch = fgetc(input);
                str[i] = ch;
                i++;
            } while (ch != '>');
            str[i] = '\0';
            printToken("Preprocessor directive", str);
            token_no++;
        }
        else if (ch == '"')
        {
            str[0] = ch;
            int i = 1;
            do
            {
                ch = fgetc(input);
                str[i] = ch;
                i++;
            } while (ch != '"');
            str[i] = '\0';
            printToken("Argument", str);
            token_no++;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
        {
            str[0] = ch, str[1] = '\0';
            printToken("Operator", str);
            token_no++;
        }
        else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '?' ||
                 ch == '@' || ch == '!' ||
                 ch == '%' || ch == ',' || ch == '&')
        {
            str[0] = ch, str[1] = '\0';
            printToken("Seperator", str);
            token_no++;
        }
        else if (isdigit(ch))
        {
            int s = 0;
            do
            {
                str[s] = ch;
                s++;
            } while (isdigit(ch = fgetc(input)));
            str[s] = '\0';
            printToken("Number", str);
            token_no++;
            fseek(input, -1, SEEK_CUR);
        }
        else if (isalpha(ch) || ch == '_')
        {
            int i = 0;
            do
            {
                str[i] = ch;
                i++;
                ch = fgetc(input);
            } while (isalnum(ch) || ch == '_');
            str[i] = '\0';
            if (isKeyword(str))
            {
                printToken("Keyword", str);
            }
            else
            {
                printToken("Identifier", str);
            }
            token_no++;
            fseek(input, -1, SEEK_CUR);
        }
        else if (ch == '\n')
        {
            line_no++;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}
