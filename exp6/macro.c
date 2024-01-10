#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Namtab
{
    char name[20];
    int start;
    int end;
    int clcnt;
};

char Deftab[1000];
struct Namtab Namtabs[20];
int NamtabCount = 0;

int isMacro(char *word)
{
    for (int i = 0; i < NamtabCount; i++)
    {
        if (strcmp(word, Namtabs[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void stripSymbols(char *line)
{
    int size = strlen(line);
    for (int i = 0; i < size; i++)
    {
        if (line[i] == '\t' || line[i] == ',')
        {
            line[i] = ' ';
        }
    }
    if (line[size - 1] == '\n')
    {
        line[size - 1] = '\0';
    }
}

void getInstructions(char *line, char *instructions[], int *instructionCount)
{
    stripSymbols(line);
    int i = 0;

    char *token = strtok(line, " ");
    while (token != NULL)
    {

        if (strlen(token) > 0)
        {
            instructions[i] = token;
            i++;
        }

        token = strtok(NULL, " ");
    }

    *instructionCount = i;
}

void defineMacro(FILE *inputFile, char *macroDefinition[], int macroDefCount)
{
    char *macroName = macroDefinition[0];
    int argCount = macroDefCount - 2;
    Namtabs[NamtabCount].clcnt = 0;

    strcpy(Namtabs[NamtabCount].name, macroName);

    char macroLine[100];
    char *macroInstructions[20];
    int macroInstructionCount;

    for (int i = 0; i < macroDefCount; i++)
    {
        strcat(Deftab, macroDefinition[i]);
        strcat(Deftab, " ");
    }

    strcat(Deftab, "\n");

    Namtabs[NamtabCount].start = strlen(Deftab);

    while (fgets(macroLine, 100, inputFile))
    {
        getInstructions(macroLine, macroInstructions, &macroInstructionCount);
        if (macroInstructionCount == 0)
        {
            continue;
        }
        if (strcmp(macroInstructions[1], "RESW") == 0 || strcmp(macroInstructions[1], "RESB") == 0 || strcmp(macroInstructions[1], "BYTE") == 0 || strcmp(macroInstructions[1], "WORD") == 0)
        {
            strcat(Deftab, macroInstructions[0]);
            strcat(Deftab, "$");
            strcat(Deftab, " ");
            for (int i = 1; i < macroInstructionCount; i++)
            {

                char *word = macroInstructions[i];

                for (int j = 0; j < argCount; j++)
                {

                    if (strcmp(word, macroDefinition[j + 2]) == 0)
                    {

                        strcpy(word, "# ");
                        word[1] = j + '0';
                    }
                }

                strcat(Deftab, word);
                strcat(Deftab, " ");
            }

            strcat(Deftab, "\n");

            if (strcmp(macroInstructions[0], "MEND") == 0)
            {
                break;
            }
        }
        else
        {
            for (int i = 0; i < macroInstructionCount; i++)
            {

                char *word = macroInstructions[i];

                for (int j = 0; j < argCount; j++)
                {

                    if (strcmp(word, macroDefinition[j + 2]) == 0)
                    {

                        strcpy(word, "# ");
                        word[1] = j + '0';
                    }
                }

                strcat(Deftab, word);
                strcat(Deftab, " ");
            }

            strcat(Deftab, "\n");

            if (strcmp(macroInstructions[0], "MEND") == 0)
            {
                break;
            }
        }
    }

    Namtabs[NamtabCount].end = strlen(Deftab) - 6;

    NamtabCount++;
}

void expandMacro(FILE *outputFile, char *macroName, char *argTab[], int macroArgCount)
{
    int macroIndex = isMacro(macroName);
    int macroStart = Namtabs[macroIndex].start;
    int macroEnd = Namtabs[macroIndex].end;
    Namtabs[macroIndex].clcnt++;
    printf("\nArg Tab:\n");
    for (int i = macroStart; i < macroEnd; i++)
    {
        char c = Deftab[i];
        char b;
        if (c == '$')
        {
            b = Namtabs[macroIndex].clcnt + '0';
            fprintf(outputFile, "%c", b);
        }
        else
        {
            if (c == '#')
            {

                int argNumber = Deftab[i + 1] - '0';

                fprintf(outputFile, "%s ", argTab[argNumber]);
                printf("%s\n", argTab[argNumber]);
                i++;
            }
            else
            {

                fprintf(outputFile, "%c", c);
            }
        }
    }
}

int main()
{
    FILE *inputFile, *outputFile;
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    char line[100];
    char *instructions[10];
    int instructionCount;

    while (fgets(line, 100, inputFile))
    {
        getInstructions(line, instructions, &instructionCount);
        if (instructionCount == 0)
        {
            continue;
        }
        if (strcmp(instructions[0], "END") == 0)
        {
            fprintf(outputFile, "END");
            break;
        }
        else if (strcmp(instructions[1], "MACRO") == 0)
        {
            defineMacro(inputFile, instructions, instructionCount);
        }
        else if (isMacro(instructions[0]) != -1)
        {
            char **argTab = &instructions[1];
            expandMacro(outputFile, instructions[0], argTab, instructionCount - 1);
        }
        else if (isMacro(instructions[1]) != -1)
        {
            char **argTab = &instructions[2];
            expandMacro(outputFile, instructions[1], argTab, instructionCount - 2);
        }
        else
        {

            for (int i = 0; i < instructionCount; i++)
            {
                fprintf(outputFile, "%s ", instructions[i]);
            }
            fprintf(outputFile, "\n");
        }
    }

    printf("Namtab:\n");
    for (int i = 0; i < NamtabCount; i++)
    {
        printf("%s \n", Namtabs[i].name);
    }

    printf("\nDeftab:\n%s\n", Deftab);
    printf("Check output.txt for expanded code\n");
    return 0;
}