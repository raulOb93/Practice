#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int card_length(long int);
string cc_type(int,long int);

int main()
{
    long int credit_card_number = 0;
    int credit_card_length = 0;
    do
    {
        // prompt user for credit card number
        cout << "Please provide a credit card number: ";
        cin >> credit_card_number;

        // calculate length of credit card number
        credit_card_length = card_length(credit_card_number);
        cout << credit_card_length << endl;

    } while (credit_card_length > 16 || credit_card_length < 13); // validate length

    string credit_card_type = cc_type(credit_card_length, credit_card_number);
    return 0;
}

string cc_type(int length,long int number)
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
            if (first_digits == 34 || first_digits == 37) // Amex validation based on first 2 digits
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
