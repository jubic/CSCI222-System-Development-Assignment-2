#ifndef LOGINACCESS_H
#define	LOGINACCESS_H

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct CashierDetails { // Stores one cashier detail
    string id; //Store ID Num
    string encryptedPass; //Store Encrypted Password
    string decryptedPass; //Store Decrypted Password
};

class LoginAccess {
public:
    LoginAccess();

    int getLoginTries() {
        return loginTries;
    };

    void increaseLoginTries() {
        loginTries++;
    };

    int getCashierSize() {
        return cashier.size();
    };
    void changePassword(); //Runs when user wants to change password
    int getLogin();        //Runs to get username and password from user
    void updateDetails();  //Updates the cashier textfile

    int getCashierIndex() {
        return cashierIndex;
    }

private:
    list<CashierDetails> cashier;           //Stores multiples cashier details
    void getLoginDetails();       //Save details from text file to list: cashier
    int checkValidUserPass(string, string); //Returns -1 if successful
    string decryptPass(string);             // Returns a decrypted password
    string encryptPass(string);             // Returns an encrypted password
    int loginTries;                         //Number of time login failed
    int cashierIndex;                       //Index of cashier that logged in
};


#endif	/* LOGINACCESS_H */

