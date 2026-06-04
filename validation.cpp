#include<iostream>

#include "Headers/validation.h"

using namespace std;

bool isValidPassword(string& password){
    bool hasUpper = false ;
    bool hasLower = false ;
    bool hasDigit = false;
    bool hasSpecial = false;

    if ( password.length() < 8){
        return false;
    }

    for (char pw : password){
        if (isupper(pw)){
            hasUpper = true;
        }
        else if (islower(pw)){
            hasLower = true;
        }
        else if (isdigit(pw)){
             hasDigit = true;
        }
        else{
            hasSpecial = true;
        }
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}
