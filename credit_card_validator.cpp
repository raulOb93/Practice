#include<iostream>
#include<cmath>

int credit_card_number;
int credit_card_length;
std::string cc_type(int, int);

int main(){

    do{
    //prompt user for credit card number
    std::cout << "Please provide credit card number: ";
    std::cin >> credit_card_number;

    //calculate length of credit card number
    credit_card_length = sizeof(credit_card_number);

    }while(credit_card_length > 16 || credit_card_length < 13); //validate length

   
    std::string credit_card_type = cc_type(credit_card_length, credit_card_number); 
    return 0;
}

std::string cc_type(int length, int number){
    std::string type;
    
       string cc_type = "INVALID"; /*Setting Invalid as default output, if value doesnt change
    it will return Invalid as no conditions were covered*/
    if (length >= 13 && length <= 16) //validate is not smaller or larger than expected
    {
        int first_digits = card_number / pow(10, (length - 2)); //obtaining digit of type and verification
        //AMEX
        if (length == 15) //Amex validation based on length
        {
            if (first_digits == 34 || first_digits == 37)  //Amex validation based on first 2 digits
            {
                cc_type = "AMEX";
            }
        }
        else if (length == 16)
        {
            if (first_digits >= 51 && first_digits <= 55)// Mastercad validation
            {
                cc_type = "MASTERCARD";
            }

            else if (first_digits >= 40 && first_digits <= 49) //VISA validation with 16 digits
            {
                cc_type = "VISA";
            }
        }
        else if (length == 13 && first_digits >= 40 && first_digits <= 49) //VISA validation with 13 digits
        {
            cc_type = "VISA";
        }
    }
    

    return type;
}

