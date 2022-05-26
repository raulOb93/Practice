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
    
    

    return type;
}

