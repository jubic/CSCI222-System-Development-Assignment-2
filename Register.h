#ifndef REGISTER_H
#define	REGISTER_H

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct TransactionDetails { // holds 1 sales transaction
    string item;
    int unitPrice;
    int qty;
    string date;
    char marked; //Marks if transaction have been counted for sales summary
};
class Register {
public:
    Register();
    char interactiveMenu();         //Displays the textual menu select style
    void getTransactionDetails();   //Get sales transactions from text file
    void addSalesTransaction();     //Add a new sales transaction
    void editSalesTransaction();    //Edit any sales transaction
    void removeSalesTransaction();  //Remove any sales transaction
    void listAllTransaction();      //List all available sales transaction
    void inquireSalesTransaction(); //Inquire transaction based on date
    void salesSummaryReport();      //Displays sakes summary report
    void updateDetails();           //Update details for transaction.txt
private:
    list<TransactionDetails> transaction; // List to save transactions
};


#endif	/* REGISTER_H */

