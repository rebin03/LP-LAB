#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Define the DFA transitions and accepting state
#define NUM_STATES 4
#define NUM_SYMBOLS 2

int transitionTable[NUM_STATES][NUM_SYMBOLS] = {
    // State Q0 State Q1 State Q2 State Q3
    {3, 1}, // Transition for symbol '0' (from Q0)
    {0, 2}, // Transition for symbol '1' (from Q0)
    {1, 3}, // Transition for symbol '0' (from Q1)
    {2, 0}  // Transition for symbol '1' (from Q1)
};

int acceptingState = 0; // Accepting state is Q0

// Function to simulate the DFA
bool runDFA(const char *input)
{
    int currentState = 0; // Start from the initial state (Q0)

    for (size_t i = 0; i < strlen(input); i++)
    {
        char symbol = input[i];
        int symbolIndex = symbol - '0'; // Convert character '0' or '1' to index 0 or 1

        if (symbolIndex < 0 || symbolIndex >= NUM_SYMBOLS)
        {
            // Invalid input symbol
            return false;
        }

        currentState = transitionTable[currentState][symbolIndex];
    }

    return currentState == acceptingState; // Check if the final state is the accepting state
}

int main()
{
    char input[100];
    printf("Enter a string (0s and 1s): ");
    scanf("%s", input);

    if (runDFA(input))
    {
        printf("Accepted\n");
    }
    else
    {
        printf("Not Accepted\n");
    }

    return 0;
}