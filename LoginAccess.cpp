#include "LoginAccess.h"

LoginAccess::LoginAccess() {
    loginTries = 0;
    cashierIndex = 0;
    getLoginDetails();
}

void LoginAccess::getLoginDetails() {
    fstream fin("Cashier.txt");

    if (fin.fail()) {
        cout << "Error: Getting details";
        exit(0);
    }
    string extracted = "";
    int col = 1;
    CashierDetails temp;
    while (!fin.eof()) {
        fin >> extracted;
        //If first col is being extracted, save in id
        if (col == 1) {
            temp.id = extracted;
            col++;
            //remaining col is set to encrypted pass
        } else {
            temp.encryptedPass = extracted;
            //decrypt the pass
            temp.decryptedPass = decryptPass(extracted);
            //Save the details into a list call cashier
            cashier.push_back(temp);
            //Ready to read next id
            col = 1;
        }
    }
    fin.close();
    cout << endl;
}

string LoginAccess::decryptPass(string pass) {
    //Plain:    ABCDEFGHIJKLMNOPQRSTUVWXYZ
    //Cipher:   DEFGHIJKLMNOPQRSTUVWXYZABC
    int idx = 0;
    //Loops through every letter one at a time in the password to be decrypted
    while (idx < pass.length()) {
        //Only use Ceaser cipher if letters are found
        if (isalpha(pass[idx])) {
            //For Caps lock chars
            if (pass[idx] > 64 && pass[idx] < 91) {
                if (pass[idx] < 88) {
                    pass[idx] += 3;
                } else if (pass[idx] == 88) {
                    pass[idx] = 'A';
                } else if (pass[idx] == 89) {
                    pass[idx] = 'B';
                } else
                    pass[idx] = 'C';
                //For small characters
            } else {
                if (pass[idx] < 120) {
                    pass[idx] += 3;
                } else if (pass[idx] == 120) {
                    pass[idx] = 'a';
                } else if (pass[idx] == 121) {
                    pass[idx] = 'b';
                } else
                    pass[idx] = 'c';
            }
        }
        idx++;
    }
    return pass;
}

string LoginAccess::encryptPass(string pass) {
    //Plain:    ABCDEFGHIJKLMNOPQRSTUVWXYZ
    //Cipher:   DEFGHIJKLMNOPQRSTUVWXYZABC
    int idx = 0;
    //Loops through every letter one at a time in the password to be encrypted
    while (idx < pass.length()) {
        //Only use Ceaser cipher if letters are found
        if (isalpha(pass[idx])) {
            //For Caps lock chars
            if (pass[idx] > 64 && pass[idx] < 91) {
                if (pass[idx] > 67) {
                    pass[idx] -= 3;
                } else if (pass[idx] == 67) {
                    pass[idx] = 'Z';
                } else if (pass[idx] == 66) {
                    pass[idx] = 'Y';
                } else
                    pass[idx] = 'X';
                //For small characters
            } else {
                if (pass[idx] > 99) {
                    pass[idx] -= 3;
                } else if (pass[idx] == 99) {
                    pass[idx] = 'z';
                } else if (pass[idx] == 98) {
                    pass[idx] = 'y';
                } else
                    pass[idx] = 'x';
            }
        }
        idx++;
    }
    return pass;
}

int LoginAccess::checkValidUserPass(string id, string pass) {
    int count = 0;
    list<CashierDetails>::iterator i;
    cout << endl << "Checking User and password combination....." << endl;
    //Loops through every cashier in the list
    for (i = cashier.begin(); i != cashier.end(); ++i) {
        count++;
        //If id matches with the list cashier id
        if (id == i->id) {
            //Straight away check password, if true informs log in success
            if (pass == i->decryptedPass) {
                cout << "Successfully log in" << endl << endl;
                //Sets cashierIndex to count for future password updates
                cashierIndex = count;
                return 1;
                //If password is wrong, stop the check at auto prompt invalid pass
            } else {
                cout << "Invalid Password " << endl << endl;
                return -1;
            }
        }
    }
    //If no id matches, it will leave the loop to print this error
    cout << "Invalid ID" << endl << endl;
    return -1;
}

bool checkPassword(string pass) {
    //Check if there are 8 chars
    if (pass.length() < 8) {
        cout << endl << "New Password has to be at least 8 chars long." << endl;
        return false;
    }

    int numCount = 0;
    int alphaCount = 0;

    //Go through every character in password and count num of alphabet and num
    for (int i = 0; i < pass.length(); i++) {
        if (isalpha(pass[i])) {
            alphaCount++;
        } else if (isdigit(pass[i])) {
            numCount++;
        }
    }
    //If there is at least 1 alpha and num
    if (numCount > 0 && alphaCount > 0) {
        cout << endl << "New password valid." << endl;
        return true;
    }

    //If all else fails means, it did not contain 1 num and 1 alpha
    cout << endl << "New password has to contain 1 number and 1 alpha" << endl;
    return false;
}

void LoginAccess::changePassword() {
    string password;
    cout << endl << "Proceeding to Change Password....." << endl;
    while (1) { // keeps looping, only exits when password updated
        cout << "Please enter new password: ";
        cin >> password;
        cin.clear();
        cin.ignore(100, '\n');
        //Check if password is valid
        if (checkPassword(password)) {
            cout << "Updating Password..." << endl;
            list<CashierDetails>::iterator i;
            int counter = 0;
            for (i = cashier.begin(); i != cashier.end(); ++i) {
                counter++;
                //CashierIndex was intialized with position of cashier in the
                //list upon log in
                if (cashierIndex == counter) {
                    cout << "Setting new pass...." << endl;
                    //Set decrypted password with password given
                    i->decryptedPass = password;
                    //Encrypt the new password before saving
                    i->encryptedPass = encryptPass(password);
                    cout << "Successfully updated password.....\n" << endl;
                    return; // breaks loop
                }
            }
        }
    }
}

int LoginAccess::getLogin() {
    string id, pass;
    cout << "Please enter login ID and Password.." << endl;
    cout << "Login ID: ";
    cin >> id;
    cin.clear();
    cin.ignore(100, '\n');

    cout << "Password: ";
    cin >> pass;
    cin.clear();
    cin.ignore(100, '\n');

    return checkValidUserPass(id, pass); //return -1 for failure, 1 for success
}

void LoginAccess::updateDetails() {
    fstream fout("Cashier.txt");

    if (fout.fail()) {
        cout << "Error: Opening file";
        exit(0);
    }
    
    list<CashierDetails>::iterator i;
    for (i = cashier.begin(); i != cashier.end(); ++i) {
        fout << i->id << "  " << i->encryptedPass << endl;
    }

    fout.close();
}

