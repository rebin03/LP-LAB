#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    FILE *input, *output;
    int l = 1;
    int t = 0;
    int j = 0;
    int i, flag;
    char digit[30];
    char ch, str[20];
    int s;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    char keyword[35][30] = {"auto", "break", "case", "char", "const", "continue", "default",
                            "do", "double", "else", "enum", "extern", "float", "for", "goto",
                            "if", "int", "long", "register", "return", "short", "signed",
                            "sizeof", "static", "struct", "switch", "typedef", "union",
                            "unsigned", "void", "volatile", "while"};
    fprintf(output, "  Line no. \t\t Token no. \t\t Token \t\t\t\t\t Lexeme\n");
    fprintf(output, "_____________________________________________________________________________________\n\n");
    while (!feof(input))
    {
        i = 0;
        flag = 0;
        ch = fgetc(input);

    label:
        if (ch == '#')
        {
            fprintf(output, "%7d\t\t %7d\t\t Preprocessor directive\t %7c", l, t, ch);
            // fprintf(output, "#");
            while ((ch = fgetc(input)) != '>')
            {
                fprintf(output, "%c", ch);
            }
            fprintf(output, ">\n");
            t++;
        }
        else if (ch == '"')
        {
            fprintf(output, "%7d\t\t %7d\t\t Argument\t\t\t\t %7c", l, t, ch);
            do
            {
                ch = fgetc(input);
                fprintf(output, "%c", ch);
            } while (ch != '"');
            fprintf(output, "\n");
            t++;
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
        {
            fprintf(output, "%7d\t\t %7d\t\t Operator\t\t %7c\n", l, t, ch);
            t++;
        }
        else if (ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == '?' ||
                 ch == '@' || ch == '!' || ch == '%' || ch == ',' || ch == '&')
        {
            fprintf(output, "%7d\t\t %7d\t\t Seperator\t\t\t %7c\n", l, t, ch);
            t++;
        }

        else if (isdigit(ch))
        {
            s = 0;
            while (isdigit(ch))
            {
                digit[s] = ch;
                ch = fgetc(input);
                s++;
            }

            digit[s] = '\0';

            fprintf(output, "%7d\t\t %7d\t\t Digit\t\t \t\t\t\t%7s\n", l, t, digit);
            t++;
            goto label;
        }
        else if (isalpha(ch))
        {
            str[i] = ch;
            i++;
            ch = fgetc(input);
            while (isalnum(ch) && ch != ' ')
            {
                str[i] = ch;
                i++;
                ch = fgetc(input);
            }
            str[i] = '\0';
            for (j = 0; j <= 30; j++)
            {
                if (strcmp(str, keyword[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                fprintf(output, "%7d\t\t %7d\t\t Keyword\t\t\t\t\t %7s\n", l, t, str);
                t++;
            }
            else
            {
                fprintf(output, "%7d\t\t %7d\t\t Identifier\t\t\t\t\t %7s\n", l, t, str);
                t++;
                goto label;
            }
        }
        else if (ch == '\n')
        {
            l++;
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}