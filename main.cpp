#include "LoginAccess.h"
#include "Register.h"

int main() {

    LoginAccess LA;

    cout << "Welcome to POS System" << endl;
    cout << "Proceeding to login page." << endl;
    cout << "Failure to log in for more than three time will result in lock "
         << "of system." << endl << endl;

    int success = -1;
    do {
        success = LA.getLogin();
        //If not successful, increase loginTries
        if (success == -1) {
            LA.increaseLoginTries();
        }
        cout << "Login Tries: " << LA.getLoginTries() << endl << endl;
        if (LA.getLoginTries() > 3) {
            cout << "More than three tries have been registered." << endl;
            cout << "Proceeding to lock the register." << endl;
            cout << "LOCKED" << endl;
            return 0;
        }
    } while (success == -1);

    while (1) { // Keeps Looping as long as user does not key 1 or 2
        int choice = 0;
        cout << "Options: " << endl;
        cout << "1) Change Password" << endl;
        cout << "2) Proceed to cash register" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        if (choice == 1) {
            LA.changePassword();
            LA.updateDetails(); //Updates only if password is changed
            break;
        } else if (choice == 2) {
            break;
        } else
            cout << "Incorrect Choice. Please try again." << endl << endl;
    }

    Register r;

    while (1) { //Loops till f is chosen
        cout << endl;
        //InteractiveMenu will return letter chosen by user, from a - f
        switch (r.interactiveMenu()) {
            case 'a': r.addSalesTransaction();
                break;
            case 'b': r.removeSalesTransaction();
                break;
            case 'c': r.editSalesTransaction();
                break;
            case 'd': r.inquireSalesTransaction();
                break;
            case 'e':r.salesSummaryReport();
                break;
            case 'f': cout << "Logging of from register" << endl;
                r.updateDetails();
                return 0;
        }
    }
}

