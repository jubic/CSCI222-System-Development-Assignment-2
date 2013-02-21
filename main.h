#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <unistd.h>

using namespace std;
//////////////////////////////////////////////////////////////
/*
To compile the code enter
g++ main.cpp -l sqlite3 -o main
./main
*/
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
static bool firstline=true;

static int globnum;
static string tempValues[1000];
/////////////////////////////////////////////////////////////////////////////////////////////////
class Function
{
	public:
		sqlite3 *db;
		sqlite3_stmt * selectStmt;
		string login_username, login_pos;
		char *sqlQuery;
		int rc;
		char *szErrMsg;
		
		fstream file;
		Function();
		~Function();
		static int callback(void *NotUsed, int argc, char **argv, char **szColName)
		{
			if (firstline==true || firstline!=false){
		    	for (int i = 0; i < argc; i++)
		    	{
		    	    cout.width(17); cout << left << szColName[i];
		    	}
				printf("\n");
				firstline=false;
			}
			for(int i = 0; i < argc; i++)
			{
		    	cout.width(17); cout << argv[i] << left;
			globnum++;
			}
			std::cout << "\n";
			return 0;
		}
		static int listview(void *NotUsed, int argc, char **argv, char **szColName)
		{
			for(int i = 0; i < argc; i++)
			{
			std::cout << szColName[i] << ":" << argv[i] << std::endl;
			}
			std::cout << "\n";
			return 0;
		}
		static int listwithnumbers(void *NotUsed, int argc, char **argv, char **szColName)
		{
			for(int i = 0; i < argc; i++)
			{
				tempValues[globnum] = argv[i];				
				cout << globnum++ <<") " << argv[i] << endl;
				
			}
			return 0;
		}
		static int getColumnArray(void *NotUsed, int argc, char **argv, char **szColName)
		{
			for(int i = 0; i < argc; i++)
			{
				tempValues[globnum++] = argv[i];				
				
			}
			return 0;
		}

		string sql_output(char *);
		int testStr(char *, int);

};
class mFunction:public virtual Function
{
	public:
		
		mFunction();
		~mFunction();
		void account_fname(string);
		void account_email(string);
		void account_mobile(string);
		void account_username(string);
		void account_password(string);
		void account_pos(string);
		void account_lock(string);
		void account_qna(string);
		void edit_fname(string);
		void edit_email(string);
		void edit_mobile(string);
		void edit_username(string);
		void edit_password(string);
		void edit_pos(string);
		void edit_lock(string);
		void edit_qna(string);
		int admn_verify(string);
		
		void class_management();
		void add_class();
		void remove_class();
		void add_student();
		void remove_student();
		void change_venue();
		void announcement();

		int check_warning(string,string);
		void account();
		void account_menu(string);
};

class Admin:public virtual Function, public virtual mFunction
{
	public:
		Admin();
		~Admin();

		void admn_menu();
		void admn_account_menu();
		void admn_edit_account();
		void admn_edit_account_menu(string);
		void admn_class();
		void admn_unlock_account();
		void admn_delete_account();
		void admn_pending_position();
		void admn_view_menu();
		void admn_view_module();
		void admn_view_sem();
		void admn_view_lect();
		void admn_view_stud();
		void admn_import();
		void admn_reg_page();	
		void admn_reg_post(string);
		void admn_announcement_menu();
		void announcement_edit();
		void announcement_delete();
		
};
class Lect:public virtual Function, public virtual mFunction
{
	public:
		Lect();
		~Lect();
		void lect_menu();
		void lect_attendance();
};
class Stud:public virtual Function, public virtual mFunction
{
	public:
		Stud();
		~Stud();
		void stud_currMod();
		void stud_viewAtt();
		void stud_timetable();
		void stud_menu();
		void stud_appeal();
};
class Main:public Admin, public Lect, public Stud
{
	public:
		Main();
		~Main();
		//Function func;
		void account_lock();
		void login_menu();
		void reg_page();
		void reg_post(string, string);
		void forget_pass();
		void main_menu();
		
		

};
#endif
