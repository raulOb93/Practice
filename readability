#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

string user_text(void);
int text_length(string);
int letters_c(string u_string, int length);
int words_c(string u_string, int length);
int sentence_c(string u_string, int length);
int index_calculation(int letters, int words, int sentences);


int main(void)
{

    string u_text = user_text();
    int text_length = strlen(u_text);
    int letters_count = letters_c(u_text, text_length);
    int words_count = words_c(u_text, text_length);
    int sentences_count = sentence_c(u_text, text_length);
    int cl_index = index_calculation(letters_count, words_count, sentences_count);

    if (cl_index < 1) //validate value of index and print result
    {
        printf("Before Grade 1\n");
    }
    else if (cl_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", cl_index);
    }
    return 0;
}

string user_text(void) //ask user for string to analize
{
    string text = get_string("Please provide text to analize: ");

    return text; //return string
}

int letters_c(string u_string, int length) //check if current posistion is letter
{
    int count = 0;
    for (int i = 0; i <= length; i++)
    {
        if (u_string[i] >= 65 && u_string[i] <= 90) //range for capital letters
        {
            count++;
        }
        if (u_string[i] > 96 && u_string[i] <= 122) // range for lower case letters
        {
            count++;
        }
    }
    return count; //return leters count
}

int words_c(string u_string, int length) //words function looking for blank spaces
{
    int count = 0;
    for (int i = 0; i <= length ; i++) //scroll the entire string
    {
        if (u_string[i] == 32) //if current position  is blank space, increase word count
        {
            count++;
        }
    }
    return ++count; //return count of words
}

int sentence_c(string u_string, int length) //look for special characters
{
    int count = 0;
    for (int i = 0; i <= length; i++) //iterate for the entire string
    {
        if (u_string[i] == 46 || u_string[i] == 63 || u_string[i] == 33) //looking for . ! ?
        {
            count++;
        }
    }
    return count;
}

int index_calculation(int letters, int words, int sentences) //calculate index
{
    float lettersI = (letters / (float)words) * 100 ; //get the letters per 100 words
    float sentencesI = (sentences / (float)words) * 100; // get sentences per 100 words
    int indexCL = round(0.0588 * lettersI - 0.296 * sentencesI - 15.8); // Coleman-Liau formula
    return indexCL;
}
