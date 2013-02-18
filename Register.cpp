.clear();
    cin.ignore(100, '\n');

    //Saves details into a list called transaction
    transaction.push_back(temp);

    cout << endl << "After adding of new transaction..." << endl;
    listAllTransaction();

    return;
}

void Register::editSalesTransaction() {
    int choice = -1;
    cout << endl << "Editing sales transaction..." << endl << endl;

    while (1) { // Continuos loop, exits when no transactions or -1 is pressed
        //if no more transaction, exit loop
        if (transaction.empty())
            return;

        listAllTransaction();

        cout << "Which transaction would you like to edit." << endl;
        cout << "Please select from 1 - " << transaction.size()
                << ". (Press -1 to quit)" << endl;

        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        if (choice == -1)
            return;

        list<TransactionDetails>::iterator edit = transaction.begin();
        //Moves pointer to correct transaction
        for (int i = 1; i < choice; i++)++edit;
        
        choice = -1;

        cout << "What would you like to edit: " << endl;
        cout << "1) Item Description " << endl;
        cout << "2) Quantity " << endl;
        cout << "3) Unit Price " << endl;
        cout << "4) Date Purchased " << endl;
        cout << "Choice: ";

        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        if (choice == -1)
            return;

        switch (choice) {
            case 1: cout << "Enter new item: " << endl;
                cin >> edit->item;
                break;
            case 2: cout << "Enter new quantity: " << endl;
                cin >> edit->qty;
                break;
            case 3: cout << "Enter new unit price: " << endl;
                cin >> edit->unitPrice;
                break;
            case 4: cout << "Enter new date purchased: " << endl;
                cin >> edit->date;
                break;
        }
    }
}

void Register::removeSalesTransaction() {
    int choice = -1;
    cout << endl << "Removing sales transaction..." << endl << endl;
    while (1) { //Continuos loop, exits when no transactions or -1 is pressed
        //If no more transaction, exit loop
        if (transaction.empty())
            return;

        listAllTransaction();

        cout << "Which transaction would you like to remove." << endl;
        cout << "Please select from 1 - " << transaction.size()
                << ". (Press -1 to quit)" << endl;
        cin >> choice;

        if (choice == -1)
            return;

        list<TransactionDetails>::iterator erase = transaction.begin();
        for (int i = 1; i < choice; i++) ++erase;
        transaction.erase(erase); //Erase the transaction from list
    }
}

void Register::listAllTransaction() {
    cout << endl << "Listing all sales transaction...." << endl;
    
    int ctr = 1; //Indexes each transaction
    list<TransactionDetails>::iterator i;
    for (i = transaction.begin(); i != transaction.end(); ++i) {
        cout << endl << ctr++ << ") " << endl
                << "Item Description:   " << i->item << endl
                << "Quantity Purchased: " << i->qty << endl
                << "Unit Price:         " << i->unitPrice << endl
                << "Date Purchased:     " << i->date << endl;
    }
    return;
}

void Register::getTransactionDetails() {
    fstream fin("transaction.txt");

    if (fin.fail()) {
        cout << "Error: Getting details";
        exit(0);
    }

    char extracted[30];
    int col = 1;

    TransactionDetails temp;
    while (!fin.eof()) {
        if (col > 0 && col < 4) { //First 4 cols, take in values till ':' found
            fin.getline(extracted, 256, ':');
        } else { //Last col saves values till end of next line
            fin >> temp.date;
            fin.clear();
            fin.ignore(100, '\n');
            //Saves extracted transaction
            transaction.push_back(temp);
            col = 0; // 0 is set as it will increase by 1 before restarting loop
        }
        if (col == 1) {
            temp.item = extracted;
        } else if (col == 2) {
            temp.unitPrice = atoi(extracted);
        } else if (col == 3) {
            temp.qty = atoi(extracted);
        }
        col++;
    }
    fin.close();
    return;
}

char Register::interactiveMenu() {
    char choice;
    while (1) { //Continuos loop till choice is from the given a - f
        cout << "Loading interactive menu...." << endl << endl;
        cout << "a) Add new sales transaction" << endl;
        cout << "b) Remove sales transaction" << endl;
        cout << "c) Edit sales entries" << endl;
        cout << "d) Inquire sales transaction" << endl;
        cout << "e) Sales summary report" << endl;
        cout << "f) Quit" << endl;

        cout << "Enter your choice: " << endl;
        cin >> choice;
        cin.clear();
        cin.ignore(100, '\n');

        if (choice == 'a' || choice == 'b' || choice == 'c' || choice == 'd' ||
                choice == 'e' || choice == 'f') {
            return choice;
        } else {
            cout << "Invalid choice. \nPlease re-enter from a - f.\n" << endl;
        }
    }
}

void Register::inquireSalesTransaction() {
    string str1;
    cout << endl << "Inquire sales transaction..." << endl << endl;

    cout << "Enter date purchased to be searched: ";
    cin >> str1;
    cin.clear();
    cin.ignore(100, '\n');

    int ctr = 1;
    list<TransactionDetails>::iterator i;
    for (i = transaction.begin(); i != transaction.end(); ++i) {
        //Display transaction only if date is same as typed by user
        if (str1 == i->date) {
            cout << endl << ctr++ << ") " << endl
                    << "Item Description:   " << i->item << endl
                    << "Quantity Purchased: " << i->qty << endl
                    << "Unit Price:         " << i->unitPrice << endl
                    << "Date Purchased:     " << i->date << endl;
        }
    }
    //If counter remains as 1 means nothing was found
    if (ctr == 1)
        cout << "No transaction was found." << endl;
}

void Register::salesSummaryReport() {
    cout << endl << "Listing sales summary report..." << endl << endl;

    int marked = 0;         // Sets how many have been marked
    string date;            //Saves date being totaled at the current loop
    bool dateFixed = false; //Whether date that needs to be totaled has been set
    int total = 0;          //Total for a given date
    int grandTotal = 0;     //Total for all dates

    cout << endl << "Date\t\tTotal Sales" << endl;
    
    list<TransactionDetails>::iterator i;
    for (i = transaction.begin(); i != transaction.end(); ++i) {
        i->marked = 'O'; //O determines haven been totaled
    }

    while (1) { // Continuos loop until grand total is found
        //Loops from start to end, getting total of a given date
        for (i = transaction.begin(); i != transaction.end(); ++i) {
            //If sales has not been added, and no given date is being totaled
            if (i ->marked != 'X' && !dateFixed) {
                date = i->date;     //Set date to be total to sales date
                i->marked = 'X';    //Set marked to X, to tell it has been added
                marked++;           //Increase number of sales marked
                total += i->unitPrice * i->qty; //Increase total with given sale
                dateFixed = true;   //Date to be total has been found
            //Increase total if date check is same as date being totaled
            } else if (i->date == date) {
                total += i->unitPrice * i->qty;
                marked++;
                i->marked = 'X';
            }
        }
        //Displays the total for given date
        cout << date << "\t\t$" << total << endl;

        
        grandTotal += total;//Increases grandTotal by total
        total = 0;          //Resets total back to 0
        dateFixed = false;  //Informs that a new date must be saved
        date = "";          //Set new date to be saved

        //Once number marked equals to size of sales, display grand total
        if (marked == transaction.size()) {
            cout << "===========================" << endl;
            cout << "Grand Total\t$" << grandTotal << endl << endl;
            return; //Exits the loop
        }
    }

}

void Register::updateDetails() {
    fstream fout("transaction.txt", ios::out);

    if (fout.fail()) {
        cout << "Error: Opening file";
        exit(0);
    }

    list<TransactionDetails>::iterator i;
    for (i = transaction.begin(); i != transaction.end(); ++i) {
        fout << i->item << ":" << i ->unitPrice << ":" << i->qty << ":"
                << i->date << endl;
    }

    fout.close();
}

