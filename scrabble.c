#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char LETTER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'v', 'W', 'X', 'Y', 'Z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");


    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
        printf("Player 1 wins!");
    else if (score2 == score1)
        printf("Tie!");
    else
        printf("Player 2 wins!");

}

int compute_score(string word)
{// TODO: Compute and return score for string

    int word_score = 0; //set value of word to 0
    int letter_value = 0;
    char current_Letter = 0;
    //letter is selected based on position staring from left to right and run cycle upt lenght of the word .
    //inex = position of current letter
    //word is the word introduced by the user
    //current letter is selected letter of word
    for (int index = 0, length = strlen(word); index < length; index++)
    {
        current_Letter = toupper(word[index]);
        if (current_Letter > 64 && current_Letter < 91)
        {
            for (int j = 0; LETTER[j] != current_Letter ; j++)
            {
                letter_value = POINTS[j];
            }
        }
        else
            letter_value = 0;

        //set value of letter based on index
        word_score = word_score + letter_value;
    }
    return word_score;
}
