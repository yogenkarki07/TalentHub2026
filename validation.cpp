#include<iostream>
#include "Headers/Universal.h"
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

bool isValidEmail(string& email) {
    if (email.length() > 30) {
        return false;
    }

    size_t atPos = email.find('@');

    if ( atPos == string::npos || atPos == 0) {
        return false;
    }

    string domain = email.substr(atPos + 1);

    if (domain != "gmail.com" && domain != "outlook.com") {
        return false;
    }

    return true;
}
