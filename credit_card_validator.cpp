#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int card_length(long int);
string card_type(int,long int);
int checksum_value(long int, int);


int main()
{
    long int credit_card_number = 0;
    int credit_card_length = 0 ;
    do
    {
        // prompt user for credit card number
        cout << "Please provide a credit card number: ";
        cin >> credit_card_number;

        // calculate length of credit card number
       credit_card_length = card_length(credit_card_number);

    } while (credit_card_length > 16 || credit_card_length < 13); // validate length

    string credit_card_type = card_type(credit_card_length, credit_card_number); // getting type of credit card

    if (credit_card_type[0] != 73)  //validate it's not an invalid number.
    {
        int checksum = checksum_value(credit_card_number, credit_card_length); //checksum function

        if ((checksum % 10) == 0) //if cheksum module isn't 0
        {
            printf("%s\n", credit_card_type);
        }
        else //setting value to invalid as it returns a fake value if not
        {
            printf("INVALID\n");
        }

    }
    else
    {
        printf("%s\n", credit_card_type);
    }

    return 0;
}

int card_length(long int card_number)
{
    //function to calculate the length of credit card number
    int i = 0;
    while (card_number) //will iterate until card number is 0
    {
        card_number /= 10;
        i++; 
    }
    return i;
}

string card_type(int length,long int number)
{
    string type = "INVALID"; //Setting Invalid as default output, if value doesnt change it will return Invalid as no conditions were covered
    int first_digits = number / pow(10, (length - 2)); //obtaining digit of type

        if (length == 16) //Obtaining type 
        {
            if (first_digits >= 51 && first_digits <= 55) // Mastercad validation
            {
                type = "MASTERCARD";
            }
            else if (first_digits >= 40 && first_digits <= 49) // VISA validation with 16 digits
            {
                type = "VISA";
            }
            else if (first_digits >= 60 && first_digits <= 65) // Discover validation based on first 2 digits
            {
                type = "DISCOVER";
            }
        }
        else if (length == 15) // Amex validation based on length
        {
            if (first_digits == 34 || first_digits == 37)
            {
                type = "AMEX";
            }
        }
        else if (length == 13 && first_digits >= 40 && first_digits <= 49) // VISA validation with 13 digits
        {
            type = "VISA";
        } 
   
    return type;
}

int checksum_value(long int mcc_number, int cc_length)
{
    int checksum_val = 1; // set to one to provide invalid result if not satisfying algorithm
    int odd = 0, pair = 0;
    for (int i = 1; i <= cc_length; i++) //adding not multiplied positions
    {
        int digit = mcc_number % 10;
        if (i % 2 != 0) // if number is pair muliply by 2 
        {
            odd += digit; 
        }
        else // add pair position numbers on credit card
        {
            digit *= 2;
            if ((digit) > 9)
            {
                pair += digit % 10;
                digit /= 10;
                pair++;
            }
            else
            {
                pair += digit;//
            }
        }

        mcc_number /= 10; //dividing by 10 to reduce

    }
    checksum_val = pair + odd; //adding values to return checksum

    return checksum_val;

}