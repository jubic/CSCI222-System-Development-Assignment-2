#include "main.h"

string Function::sql_output(char *sql)
{
	string s;
	int res;
	int ctotal;
	
	sqlite3_prepare(db, sql, -1, &selectStmt, 0);
	ctotal = sqlite3_column_count(selectStmt);
	while (1)
	{
		res = sqlite3_step(selectStmt);
		if ( res == SQLITE_ROW ) 
		{	
			for ( int i = 0; i < ctotal; i++ ) 
			{
				s = (char*)sqlite3_column_text(selectStmt, i);
			}
		}
		if ( res == SQLITE_DONE || res==SQLITE_ERROR)    
		{
			break;
		}
	}
	sqlite3_finalize(selectStmt);
	return s;
}
//test string function()
int Function::testStr(char array[], int number)
{
    int check;
    bool alpha = false;
    bool digit = false;
     for(int counter = 0; counter < number; counter++)
     {
             //test alphabet
             if(isalpha(array[counter]))
             {
             alpha = true;
             }
     }//end for loop

	 
     for(int counter = 0; counter < number; counter++)
     {
             //test digit
             if(isdigit(array[counter]))
             {
             digit = true;
             }
     }//end for loop}

if( alpha && digit)
//test=true;
//check = 1;
return 1;
else if(alpha == false)
//check = 2;
return 2;
else if(digit == false)
//check = 3;
return 3;
}//end of testStr () 
Function::Function()
{
	rc = sqlite3_open("Assn2", &db);
	if(rc)
	{
		std::cout << "Can't open database\n";
	}
	else
	{
	}
}
Function::~Function()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////

mFunction::mFunction()
{
}
mFunction::~mFunction()
{
}

Admin::Admin()
{
}
Admin::~Admin()
{
}

Lect::Lect()
{
}
Lect::~Lect()
{
}

Stud::Stud()
{
}
Stud::~Stud()
{
}

Main::Main()
{
}
Main::~Main()
{
}
void Main::login_menu()
{
	const char *mypass="null";
	const int maxPasswordLength = 500;
 	char password[maxPasswordLength];

	int tries = 1;
	string tries_username = "";
	string s;
	do
	{
		int res =1;
		int ctotal;
		string username;
		cout<<endl<<"Login Page"<<endl;
		cout<<"Username : ";
		cin>>username;
		char *password=getpass("Enter password: ");
		//cout<<"Password : ";
		//cin>>password;
		char chkuser[1000];
		char chkboth[1000];
		char chklock[1000];
		char chkpos[1000];
		char gettries[1000];
		char update_tries_lock[1000];
		strcpy(chkuser,"SELECT COUNT(*) FROM USER WHERE username ='");
		strcat(chkuser,username.c_str());
		strcat(chkuser,"';");
		strcpy(chkboth,"SELECT COUNT(*) FROM USER WHERE username ='");
		strcat(chkboth,username.c_str());
		strcat(chkboth,"' AND password ='");
		strcat(chkboth,password);
		strcat(chkboth,"';");
		strcpy(chklock,"SELECT lock FROM USER WHERE username ='");
		strcat(chklock,username.c_str());
		strcat(chklock,"' AND password ='");
		strcat(chklock,password);
		strcat(chklock,"';");
		strcpy(chkpos,"SELECT position FROM USER WHERE username ='");
		strcat(chkpos,username.c_str());
		strcat(chkpos,"' AND password ='");
		strcat(chkpos,password);
		strcat(chkpos,"';");
		strcpy(gettries,"SELECT noofattemps FROM USER WHERE username ='");
		strcat(gettries,username.c_str());
		strcat(gettries,"';");
		//Checking username 1st
		sqlQuery = chkuser;
		s = sql_output(sqlQuery);
		if(s == "1")//username exists
		{
			//CHECK BOTH
			sqlQuery = chklock;
			s = sql_output(sqlQuery);
			if(s=="U")
			{
				sqlQuery = chkpos;
				s = sql_output(sqlQuery);
				if(s == "ADMN")
				{
					cout<<"Login Successful As Admin"<<endl;
					login_username = username;
					login_pos = s;
					admn_menu();
					break;
				}
				else if(s == "LECT")
				{
					cout<<"Login Successful As Lecturer"<<endl;
					login_username = username;
					login_pos = s;
					lect_menu();
					break;
				}
				else if(s == "STUD")
				{
					cout<<"Login Successful As Student"<<endl;
					login_username = username;
					login_pos = s;
					stud_menu();
					break;
				}
			}
			else if(s=="L")
			{
				account_lock();
				break;
			}
			else
			{
				//WRONG PASSWORD
				cout<<"Wrong password";
				sqlQuery = gettries;
				s = sql_output(sqlQuery);
				int tries = atoi(s.c_str());
				cout<<"No of attempts left : "<<2 - tries<<endl;
				if(tries < 3)
				{
					string stry, slock;				
					tries++;
					ostringstream toString;
					toString<<tries;
					stry = toString.str();
					if(tries == 3)
					{
						slock = "L";
					}
					else
					{
						slock = "U";
					}
					strcpy(update_tries_lock,"UPDATE USER SET noofattemps =");
					strcat(update_tries_lock,stry.c_str());
					strcat(update_tries_lock,",lock = '");
					strcat(update_tries_lock,slock.c_str());
					strcat(update_tries_lock,"' WHERE username = '");
					strcat(update_tries_lock,username.c_str());
					strcat(update_tries_lock,"';");
					sqlQuery = update_tries_lock;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					int res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);
					if(slock=="L")
					{
						account_lock();
						break;
					}
				}
				else
				{
					account_lock();
					break;
				}
			}
		}
		else
		{
			cout<<"Invalid Username & Password"<<endl;
		}	
	}while(1);

}
void Main::account_lock()
{
	cout<<"Account is Locked"<<endl;
}
void Main::reg_page()
{
	string selectstmt, insertstmt, s;
	char stmt[1000];
	string nric, name,mail,mobile,username,password, qns, ans;
	const int NUMBER = 100;
	char password2[NUMBER];
	char mobile2[NUMBER];
	do
	{
		cout<<"NRIC :";
		cin>>nric;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE nric = '"+nric+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;	
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			cout<<"NRIC already exist"<<endl;
		}
		else
		{
			break;
		}
	}while(1);
	cin.clear();
	cin.ignore(100,'\n');
	cout<<"Full name : ";
	getline(cin,name,'\n');
	do
	{
		cout<<"Email : ";
		cin>>mail;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE email = '"+mail+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;	
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			cout<<"Email already exist"<<endl;
		}
		else
		{
			break;
		}
	}while(1);
	do{
		cout<<"Mobile No : ";
		cin>>mobile;
		strcpy(mobile2,mobile.c_str());
		int nx = strlen(mobile2);
		int te = (testStr(mobile2, nx));

		if (te == 3){
			cout<<"-  There should not be letter in your mobile no.\n";
		}
		else{
			break;
		}

	}while(1);
	do
	{
		cout<<"Username : ";
		cin>>username;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE username = '"+username+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			cout<<"Username already exist"<<endl;
		}
		else
		{
			break;
		}
	}while(1);
	do
	{
		cout<<"Password : ";
		cin>>password;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE password = '"+password+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		s = sql_output(sqlQuery);
		strcpy(password2,password.c_str());
		int nx = strlen(password2);
		int te = (testStr(password2, nx));
		if(nx < 8)
		{
			cout<<"-  The password entered is less than 8 characters.\n\n";
		}
		else
		{
			if (te == 1)
			{		
				break;
			}
			else if (te == 2)
			{
				cout<<"-  No letter found in password\n";
			}
			else if (te == 3)
			{
				cout<<"-  Digit not found in password.\n";
			}
		}
	}while(1);
	cout<<"Security Question : ";
	cin.clear();
	cin.ignore(100,'\n');
	getline(cin,qns,'\n');
	cout<<"Answer : ";
	cin.clear();
	cin.ignore(100,'\n');
	getline(cin,ans,'\n');
	insertstmt="INSERT INTO USER(nric, name,email,mobileNo,username,password,question,answer) VALUES ('"+nric+"','"+name+"', '"+mail+"', "+mobile+", '"+username+"', '"+password+"','"+qns+"','"+ans+"');";
	strcpy(stmt, insertstmt.c_str());	
	sqlQuery = stmt;
	sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
	int res=sqlite3_step(selectStmt);
	sqlite3_finalize(selectStmt);
	reg_post(username, "STUD");
}
void Main::reg_post(string user, string oldpos)
{
	login_username=user;
	login_pos="STUD";
	int choice;
	string newpos;
	string insertstmt;
	char stmt[1000];
	cout<<"Please select the post you want to apply"<<endl;
	cout<<"1)	Admin"<<endl;
	cout<<"2)	Lecturer"<<endl;
	cout<<"3)	Student"<<endl;
	cout<<"Please enter your choice : ";
	cin>>choice;
	if(choice == 3)
	{
		newpos = "STUD";
		stud_menu();
	}
	else
	{
		if(choice == 1)
		{
			newpos = "ADMN";
		}
		else if(choice == 2)
		{
			newpos = "LECT";
		}
		insertstmt="INSERT INTO PENDING VALUES ('"+user+"','"+oldpos+"','"+newpos+"');";
		strcpy(stmt, insertstmt.c_str());	
		sqlQuery = stmt;
		sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
		int res=sqlite3_step(selectStmt);
		sqlite3_finalize(selectStmt);
		if(oldpos == "STUD")
		{
			stud_menu();
		}
		else if(oldpos == "LECT")
		{
			lect_menu();
		}
	}
}
void Admin::admn_reg_page()
{
	string selectstmt, insertstmt, s;
	char stmt[1000];
	string nric, name,mail,mobile,username,password, qns, ans;
	const int NUMBER = 100;
	char password2[NUMBER];
	char mobile2[NUMBER];
	do
	{
		cout<<"NRIC :";
		cin>>nric;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE nric = '"+nric+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;	
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			cout<<"NRIC already exist"<<endl;
		}
		else
		{
			break;
		}
	}while(1);
	cout<<"Full name : ";
	cin.clear();
	cin.ignore(100,'\n');
	getline(cin,name,'\n');
	do
	{
		cout<<"Email : ";
		cin>>mail;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE email = '"+mail+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;	
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			cout<<"Email already exist"<<endl;
		}
		else
		{
			break;
		}
	}while(1);
	do{
		cout<<"Mobile No : ";
		cin>>mobile;
		strcpy(mobile2,mobile.c_str());
		int nx = strlen(mobile2);
		int te = (testStr(mobile2, nx));

		if (te == 3){
			cout<<"-  There should not be letter in your mobile no.\n";
		}
		else{
			break;
		}

	}while(1);
	do
	{
		cout<<"Username : ";
		cin>>username;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE username = '"+username+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			cout<<"Username already exist"<<endl;
		}
		else
		{
			break;
		}
	}while(1);
	do
	{
		cout<<"Password : ";
		cin>>password;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE password = '"+password+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		s = sql_output(sqlQuery);
		strcpy(password2,password.c_str());
		int nx = strlen(password2);
		int te = (testStr(password2, nx));
		if(nx < 8)
		{
			cout<<"-  The password entered is less than 8 characters.\n\n";
		}
		else
		{
			if (te == 1)
			{		
				break;
			}
			else if (te == 2)
			{
				cout<<"-  No letter found in password\n";
			}
			else if (te == 3)
			{
				cout<<"-  Digit not found in password.\n";
			}
		}
	}while(1);
	cout<<"Security Question : ";
	
	cin.clear();
	cin.ignore(100,'\n');
	getline(cin,qns,'\n');
	cout<<"Answer : ";
	
	cin.clear();
	cin.ignore(100,'\n');
	getline(cin,ans,'\n');
	insertstmt="INSERT INTO USER(nric, name,email,mobileNo,username,password,question,answer) VALUES ('"+nric+"','"+name+"', '"+mail+"', "+mobile+", '"+username+"', '"+password+"','"+qns+"','"+ans+"');";
	strcpy(stmt, insertstmt.c_str());	
	sqlQuery = stmt;
	sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
	int res=sqlite3_step(selectStmt);
	sqlite3_finalize(selectStmt);
	admn_reg_post(username);
}
void Admin::admn_reg_post(string user)
{
	do
	{
		string choice, pos;
		cout<<"Please select the post you want to apply"<<endl;
		cout<<"1)	Admin"<<endl;
		cout<<"2)	Lecturer"<<endl;
		cout<<"3)	Student"<<endl;
		cout<<"Please enter your choice : ";
		cin>>choice;
		if(choice=="1"||choice=="2"||choice=="3")
		{
			if(choice=="1")
			{
				pos="ADMN";
			}
			else if(choice=="2")
			{
				pos="LECT";
			}
			else if(choice=="3")
			{
				pos="STUD";
			}
			string updatePosition;
			char stmt[1000];
			updatePosition = "UPDATE USER SET position = '"+pos+"' WHERE username = '"+user+"';";
			strcpy(stmt, updatePosition.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
			cout<<"Position has been updated"<<endl;
			break;
		}
		
	}while(1);
}
void Main::forget_pass()
{
	string username, qn, answer, ans, selectQns, selectAns, updatePass, newpass1, newpass2;
	char stmt[1000];
	cout<<"Forget Password"<<endl;
	do
	{
		cout<<"Please enter your username : ";
		cin>>username;
		selectQns = "SELECT question FROM USER WHERE username = '"+username+"' AND lock ='U';";
		strcpy(stmt, selectQns.c_str());	
		sqlQuery = stmt;
		qn = sql_output(sqlQuery);
		if(qn!="")
		{
			do
			{
				cout<<"Security Question : "<<qn<<endl;
				cout<<"Answer : ";
				cin>>answer;
				selectAns = "SELECT answer FROM USER WHERE username = '"+username+"' AND lock ='U';";
				strcpy(stmt, selectAns.c_str());	
				sqlQuery = stmt;
				ans = sql_output(sqlQuery);
				if(ans == answer)
				{
					do
					{
						cout<<"New Password :";
						cin>>newpass1;
						cout<<"Confirm New Password :";
						cin>>newpass2;
						if(newpass1==newpass2)
						{
							updatePass = "UPDATE USER SET password = '"+newpass2+"' WHERE username = '"+username+"';";
							strcpy(stmt, updatePass.c_str());	
							sqlQuery = stmt;
							sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
							int res=sqlite3_step(selectStmt);
							sqlite3_finalize(selectStmt);
							break;
						}
						else
						{
							cout<<"Both password doesn't match. Please try again"<<endl;
						}
					}while(1);
					break;
				}
				else
				{
					cout<<"Security Answer is wrong"<<endl;
				}
			}while(1);
			break;
		}
		else
		{
			cout<<"Username Invalid"<<endl;
		}
	}while(1);
}
void Admin::admn_menu()
{
	string selectstmt, updatestmt, s;
	char stmt[1000];
	string aID,classID,tempNRIC,viewApp,tmpStat;
	const int NUMBER = 100;
	char password2[NUMBER];
	char mobile2[NUMBER];	
	do
	{
		int choice;
		
		selectstmt = "SELECT COUNT(*) FROM appeal;";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;	
		s = sql_output(sqlQuery);
		if (s != "0")
		{
			cout<<endl<<"There are "<<s<<" numbers of appeal"<<endl;
			cout<<"Do you want to view it ? (Y/N)"<<endl;
			cin>>viewApp;
			
			if (viewApp == "Y")
			{
				do
				{
					selectstmt = "SELECT aID as 'Attendance ID' ,classID as 'Class ID',nric,reason from appeal;";
					const char *viewstmt;			
					viewstmt = selectstmt.c_str();
					firstline = true;
					rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			
			
					if(rc != SQLITE_OK)
					{
						std::cout << "SQL Error: " << szErrMsg << std::endl;
						sqlite3_free(szErrMsg);
						break;
					}firstline = true;
					cout<<"Please enter the appeal id you wish to correct(0 to go admin menu) : ";
					cin>>aID;   

					selectstmt = "SELECT nric FROM appeal WHERE aID = '"+aID+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					tempNRIC = sql_output(sqlQuery);

					selectstmt = "SELECT classID FROM appeal WHERE aID = '"+aID+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					classID = sql_output(sqlQuery);
	
					
					updatestmt="update attendance set status='Y' where nric ='"+tempNRIC+"' and classID='"+classID+"';";
			
					strcpy(stmt, updatestmt.c_str());	
					sqlQuery = stmt;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					int res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);

					updatestmt="delete from appeal where aID='"+aID+"';";
					strcpy(stmt, updatestmt.c_str());	
					sqlQuery = stmt;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);

					selectstmt = "SELECT COUNT(*) FROM appeal;";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
				}while (aID != "0" && s != "0");
			}	
		}				
			cout<<endl<<endl<<"Admin Page"<<endl;
			cout<<"1)	Accounts Management"<<endl;
			cout<<"2)	Class Management"<<endl;
			cout<<"3)	Announcement Management"<<endl;
			cout<<"4)	View Management"<<endl;
			cout<<"5)	Import Data Management"<<endl;
			cout<<"6)	Logout"<<endl;
			cout<<"Please enter your choice : ";
			cin>>choice;
			cin.clear();
			cin.ignore(100,'\n');
			cout<<endl<<endl;
			if(choice == 1)
			{
				admn_account_menu();
			}
			else if (choice == 2)
			{
				class_management();
			}
			else if(choice == 3)
			{
				admn_announcement_menu();
			}
			else if(choice == 4)
			{
				admn_view_menu();
			}
			else if(choice == 5)
			{
				admn_import();
			}
			else if(choice == 6)
			{
				break;
			}
		
	}while(1);
	
}
void Admin::admn_account_menu()
{
	do
	{
		int choice;
		cout<<"Account Management"<<endl;
		cout<<"1)	Create Account"<<endl;
		cout<<"2)	Edit Account"<<endl;
		cout<<"3)	Unlock Account"<<endl;
		cout<<"4)	Delete Account"<<endl;
		cout<<"5)	Pending Change of Position"<<endl;
		cout<<"6)	Return back to main menu"<<endl;
		cout<<"Please enter your choice : ";
		cin>>choice;
		if(choice == 1)
		{
			admn_reg_page();
		}
		else if(choice == 2)
		{
			admn_edit_account();
		}
		else if(choice == 3)
		{
			admn_unlock_account();
		}
		else if(choice == 4)
		{
			admn_delete_account();
		}
		else if(choice == 5)
		{
			admn_pending_position();
		}
		else if(choice == 6)
		{
			break;
		}
	}while(1);
}
void Admin::admn_edit_account()
{
	do {
		string choice, selectstmt, s;
		char *selectQuery;
		char stmt[1000];
		cout<<"To view all accounts type : 'viewall' or 'exit' to return or alternatively," <<endl;
		cout<< "Please key in the username you wish to edit: ";
		cin>>choice;
		if (choice == "viewall")
		{
			//Display All code here(callback function)
			selectstmt = "SELECT nric,name,email,mobileNo,username,position,lock,noofattemps FROM User;";
			const char *viewstmt;			
			viewstmt = selectstmt.c_str();
			firstline = true;
			rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				std::cout << "SQL Error: " << szErrMsg << std::endl;
				sqlite3_free(szErrMsg);
				break;
			}   
			firstline=true;
		}
		else if (choice == "exit")
		{
			admn_account_menu();
			break;
		}
		else
		{
			selectstmt = "SELECT COUNT(*) FROM USER WHERE username = '"+choice+"';";
			strcpy(stmt, selectstmt.c_str());	
			sqlQuery = stmt;	
			s = sql_output(sqlQuery);
			if(s=="1")
			{
				admn_edit_account_menu(choice);
				break;
			}
			else
			{
				cout<<"Invalid username"<<endl;
			}
		}
	}while(1);
}
void Admin::admn_edit_account_menu(string user)
{
	do
	{
		int choice;
		cout<<endl<<"Which field of user '"<< user << "' you wish to edit?"<<endl;
		cout<<"1)	Edit Full Name"<<endl;
		cout<<"2)	Edit Email"<<endl;
		cout<<"3)	Edit Mobile No"<<endl;
		cout<<"4)	Edit Username"<<endl;
		cout<<"5)	Edit Password"<<endl;
		cout<<"6)	Edit Position"<<endl;
		cout<<"7)	Edit Lock Status"<<endl;
		cout<<"8)	Edit Security Question and Answer"<<endl;
		cout<<"9)	Return back to Account Management"<<endl;
		cout<<"Please enter your choice : ";
		cin>>choice;
		if (choice==1)
		{
			account_fname(user);
		}
		else if (choice==2)
		{
			account_email(user);
		}
		else if (choice==3)
		{
			account_mobile(user);
		}
		else if (choice==4)
		{
			account_username(user);
		}
		else if (choice==5)
		{
			edit_password(user);
		}
		else if (choice==6)
		{
			account_pos(user);
		}
		else if (choice==7)
		{
			account_lock(user);
		}
		else if (choice==8)
		{
			account_qna(user);
		}
		else if (choice==9)
		{
			admn_edit_account();
			break;
		}
	}while(1);
}
void Admin::admn_unlock_account()
{
	string choice, selectstmt, updateLock, s;
	char stmt[1000];
	char *selectQuery;
	selectstmt = "SELECT COUNT(*) FROM user where lock ='L';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;	
	s = sql_output(sqlQuery);
	if(s!="0")
	{
		do {
			cout<<"To view all accounts type : 'viewall' or 'exit' to return or alternatively," <<endl;
			cout<< "Please key in the username you wish to unlock: ";
			cin>>choice;
			if (choice == "viewall")
			{
				//Display All code here(callback function)
				const char *viewstmt;
				selectstmt = "SELECT nric as 'NRIC',name,email,mobileNo,username,position,lock,noofattemps as 'No of attempts' FROM User WHERE lock = 'L';";
				firstline = true;
				viewstmt = selectstmt.c_str();
				rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
				if(rc != SQLITE_OK)
				{
					std::cout << "SQL Error: " << szErrMsg << std::endl;
					sqlite3_free(szErrMsg);
					break;
				} 
				firstline=true;
			}
			else if (choice == "exit")
			{
				admn_account_menu();
				break;
			}
			else
			{
				selectstmt = "SELECT COUNT(*) FROM user WHERE username = '"+choice+"' AND lock ='L';";
				strcpy(stmt, selectstmt.c_str());	
				sqlQuery = stmt;	
				s = sql_output(sqlQuery);
				if(s=="1")
				{
					updateLock = "UPDATE USER SET lock = 'U' WHERE username = '"+choice+"';";
					strcpy(stmt, updateLock.c_str());	
					sqlQuery = stmt;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					int res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);

					updateLock = "UPDATE USER SET noofattemps = 0 WHERE username = '"+choice+"';";
					strcpy(stmt, updateLock.c_str());	
					sqlQuery = stmt;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);

					cout<<"Username : "<<choice<<" has been unlocked"<<endl;
					break;
				}
				else
				{
					cout<<"Invalid username"<<endl;
				}
			}
		}while(1);
	}
	else
	{
		cout<<"No Lock Change"<<endl;
	}
}
void Admin::admn_delete_account()
{
	string choice, selectstmt, s, deleteUser;
	char stmt[1000];
	char *selectQuery;
	do 
	{
		cout<<"To view all user account request type : 'viewall' or 'exit' to return or alternatively," <<endl;
		cout<< "Please key in the username you wish to process: ";
		cin>>choice;
		if (choice == "viewall")
		{
			//Display All code here(callback function)
			const char *viewstmt;
			selectstmt = "SELECT nric,name,email,mobileNo,username,password,position,lock,question,answer,noofattemps FROM USER WHERE username !='"+login_username+"';";
			viewstmt = selectstmt.c_str();
			rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				std::cout << "SQL Error: " << szErrMsg << std::endl;
				sqlite3_free(szErrMsg);
				break;
			}   
			firstline=true;
		}
		else if (choice == "exit")
		{
			//admn_account_menu();
			break;
		}
		else
		{
			if(choice!=login_username)
			{
			selectstmt = "SELECT COUNT(*) FROM USER WHERE username = '"+choice+"';";
			strcpy(stmt, selectstmt.c_str());	
			sqlQuery = stmt;	
			s = sql_output(sqlQuery);
			if(s=="1")
			{
				do
				{
					string confirm;
					cout<<"Are you sure you want to delete '"<<choice<<"' (Y/N) :";
					cin>>confirm;
					if(confirm=="y"||confirm=="Y")
					{
						deleteUser = "DELETE FROM USER WHERE username = '"+choice+"';";
						strcpy(stmt, deleteUser.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
						cout<<"Username : "<<choice<<" successfully deleted"<<endl;
						break;
					}
					else if(confirm=="n"||confirm=="N")
					{
						break;
					}
				}while(1);
				break;
			}
			else
			{
				cout<<"Invalid username"<<endl;
			}
			}
			else
			{
				cout<<"You can't delete your own account"<<endl;
			}
		
		}
	}while(1);
}
void Admin::admn_pending_position()
{
	string choice, selectstmt, s, deletePending;
	char stmt[1000];
	char *selectQuery;
	selectstmt = "SELECT COUNT(*) FROM pending;";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;	
	s = sql_output(sqlQuery);
	if(s!="0")
	{
		do {
			cout<<"To view all pending request type : 'viewall' or 'exit' to return or alternatively," <<endl;
			cout<< "Please key in the NRIC you wish to process: ";
			cin>>choice;
			if (choice == "viewall")
			{
				//Display All code here(callback function)
				const char *viewstmt;
				selectstmt = "SELECT nric,curposition,aplposition FROM pending;";
				viewstmt = selectstmt.c_str();
				rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
				if(rc != SQLITE_OK)
				{
					std::cout << "SQL Error: " << szErrMsg << std::endl;
					sqlite3_free(szErrMsg);
					break;
				}
				firstline=true;
			}
			else if (choice == "exit")
			{
				//admn_account_menu();
				break;
			}
			else
			{
				selectstmt = "SELECT COUNT(*) FROM pending WHERE nric = '"+choice+"';";
				strcpy(stmt, selectstmt.c_str());	
				sqlQuery = stmt;	
				s = sql_output(sqlQuery);
				if(s=="1")
				{
					selectstmt = "SELECT nric AS 'NRIC', curposition AS 'Current Position', aplposition AS 'Applied Position' FROM PENDING;";
					const char *viewstmt;
					viewstmt = selectstmt.c_str();
					rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
					if(rc != SQLITE_OK)
					{
						std::cout << "SQL Error: " << szErrMsg << std::endl;
						sqlite3_free(szErrMsg);
						break;
					}
					edit_pos(choice);
					deletePending = "DELETE FROM PENDING WHERE nric = '"+choice+"';";
					strcpy(stmt, deletePending.c_str());	
					sqlQuery = stmt;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					int res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);
					break;
				}
				else
				{
					cout<<"Invalid username"<<endl;
				}
			
			}
		}while(1);
	}
	else
	{
		cout<<"No Pending Change"<<endl;
	}
}
void Admin::admn_announcement_menu()
{
	do
	{	
		string choice;
		cout<<"Announcement Management"<<endl;
		cout<<"1)	Create Announcement"<<endl;
		cout<<"2)	Edit Announcement"<<endl;
		cout<<"3)	Delete Announcement"<<endl;
		cout<<"4)	Return back to main menu"<<endl;
		cout<<"Please input your choice : ";
		cin>>choice;
		if(choice=="1")
		{
			announcement();
		}
		else if(choice=="2")
		{
			announcement_edit();
		}
		else if(choice=="3")
		{
			announcement_delete();
		}
		else if(choice=="4")
		{
			break;
		}
	}while(1);
}
void Admin::announcement_edit()
{
	string selectstmt,newAnnc,updatestmt;
	char stmt[1000];
	char *selectQuery;
	string aID;
	const char *viewstmt;
	cout<<"Announcements available : "<<endl;
	selectstmt = "SELECT aid,nric,classID,position,remarks FROM announcement;";
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
	}
	cout<<"Please input the announcement that you want to edit (0 to cancel): ";
	cin>>aID;
	if (aID != "0")
	{
		cout<<"Input the new announcement :";
		cin>>newAnnc;
		updatestmt="update announcement set remarks='"+newAnnc+"' where aID ='"+aID+"';";
		strcpy(stmt, updatestmt.c_str());	
		sqlQuery = stmt;
		sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
		int res=sqlite3_step(selectStmt);
		sqlite3_finalize(selectStmt);
	}
}
void Admin::announcement_delete()
{
	string selectstmt,deletestmt;
	char stmt[1000];
	char *selectQuery;
	string aID;
	const char *viewstmt;	
	cout<<"Announcements available : "<<endl;
	selectstmt = "SELECT aid,nric,classID,position,remarks FROM announcement;";
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
	}
	cout<<"Please input the announcement that you want to delete (0 to cancel): ";
	cin>>aID;
	if (aID != "0")
	{
		deletestmt ="delete from announcement where aID ='"+aID+"';";
		strcpy(stmt, deletestmt.c_str());	
		sqlQuery = stmt;
		sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
		int res=sqlite3_step(selectStmt);
		sqlite3_finalize(selectStmt);
	}
}
void Admin::admn_view_menu()
{
	do
	{
		string choice;
		cout<<"View Management"<<endl;
		cout<<"1)	Modules"<<endl;
		cout<<"2)	Semester"<<endl;//Module
		cout<<"3)	Lecturers"<<endl;
		cout<<"4)	Students"<<endl;//Module
		cout<<"5)	Return to main menu"<<endl;
		cout<<"Please enter your choice:";
		cin>>choice;
		if(choice=="1")
		{
			admn_view_module();
		}
		if(choice=="2")
		{
			admn_view_sem();
		}
		if(choice=="3")
		{
			admn_view_lect();
		}
		if(choice=="4")
		{
			admn_view_stud();
		}
		if(choice=="5")
		{
			break;
		}
	}while(1);
}
void Admin::admn_view_module()
{
	string selectstmt;
	//Display All code here(callback function)
	selectstmt = "SELECT * FROM module_view;";
	const char *viewstmt;			
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
	}
	firstline=true;
}
void Admin::admn_view_sem()
{
	string selectstmt;
	//Display All code here(callback function)
	selectstmt = "SELECT * FROM semester_view;";
	const char *viewstmt;			
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
	}
	firstline=true;
}
void Admin::admn_view_lect()
{
	string selectstmt;
	//Display All code here(callback function)
	selectstmt = "SELECT * FROM lecturer_view;";
	const char *viewstmt;			
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
	}
	firstline=true;
}
void Admin::admn_view_stud()
{
	string selectstmt;
	//Display All code here(callback function)
	selectstmt = "SELECT * FROM student_view;";
	const char *viewstmt;			
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
	}
	firstline=true;
}
void Admin::admn_import()
{
	//Import file
	int count;
	string filename, dup,lines;
	string type, filetype;
	string nric, classid, status, modulename, modulecode, sid, semester, year, date, totalnoofhrs;
	string name, email, mobileNo, username, password, position, lock, question, answer, noofattemps;
	string venueid, level, unit, vtype, modulegroup, duration;
	string insertstmt, selectstmt, s, cdate, ctime, curposition, aplposition, aid;
	string classID, remarks, warnid, warning, sEID, sID, markedAtt, reason;
	char stmt[1000];
	type = "";
	count=0;
	do
	{
		cout<<"Please enter filename :";
		getline(cin,filename,'\n');
		if(filename.find(".txt") != string::npos)
		{
			file.open(filename.c_str(),ios::in);
			while (file)
			{
				if(type=="")
				{
					getline(file,type);
				}
				if(type == "USER")
				{
					dup="0";
					getline(file,nric, ',');
					getline(file,name, ',');
					getline(file,email, ',');
					getline(file,mobileNo, ',');
					getline(file,username, ',');
					getline(file,password, ',');
					getline(file,position, ',');
					getline(file,lock, ',');
					getline(file,question, ',');
					getline(file,answer, ',');
					getline(file,noofattemps);
					selectstmt = "SELECT COUNT(*) FROM user WHERE nric = '"+nric+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1" || nric =="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO user VALUES ('"+nric+"', '"+name+"','"+email+"',"+mobileNo+",'"+username+"','"+password+"','"+position+"','"+lock+"','"+question+"','"+answer+"',"+noofattemps+");";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type == "MODULE")
				{
					dup="0";
					getline(file,username, ',');
					getline(file,modulename, ',');
					getline(file,modulecode, ',');
					getline(file,totalnoofhrs);
					selectstmt = "SELECT COUNT(*) FROM module WHERE modulecode = '"+modulecode+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||username=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO module VALUES ('"+username+"', '"+modulename+"','"+modulecode+"','"+totalnoofhrs+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type == "SEMESTER")
				{
					dup="0";
					getline(file,modulecode, ',');
					getline(file,semester, ',');
					getline(file,year);
					selectstmt = "SELECT COUNT(*) FROM semester WHERE modulecode = '"+modulecode+"' AND semester = '"+semester+"' AND year = '"+year+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||modulecode=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO semester VALUES (NULL,'"+modulecode+"','"+semester+"','"+year+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type == "VENUE")
				{
					dup="0";
					getline(file,level, ',');
					getline(file,unit, ',');
					getline(file,vtype);
					selectstmt = "SELECT COUNT(*) FROM venue WHERE level = '"+level+"' AND unit = '"+unit+"' AND vtype = '"+vtype+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||level=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO venue VALUES (NULL,'"+level+"','"+unit+"','"+vtype+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type == "CLASS")
				{
					dup="0";
					getline(file,nric, ',');
					getline(file,modulecode, ',');
					getline(file,modulegroup, ',');
					getline(file,cdate, ',');
					getline(file,ctime, ',');
					getline(file,duration, ',');
					getline(file,sid, ',');
					getline(file,venueid, ',');
					getline(file,markedAtt);
					selectstmt = "SELECT COUNT(*) FROM class WHERE modulecode = '"+modulecode+"' AND modulegroup = '"+modulegroup+"' AND date = '"+cdate+"' AND time = '"+ctime+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||nric=="")
					{
	 					dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO class VALUES (NULL,'"+nric+"', '"+modulecode+"','"+modulegroup+"','"+cdate+"','"+ctime+"',"+duration+","+sid+","+venueid+","+markedAtt+");";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type=="ATTENDANCE")
				{
					dup="0";
					getline(file,nric, ',');
					getline(file,classid, ',');
					getline(file,status);
					selectstmt = "SELECT COUNT(*) FROM attendance WHERE nric = '"+nric+"' AND classID = '"+classid+"' AND status = '"+status+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||nric=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO attendance VALUES ('"+nric+"', '"+classid+"','"+status+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type=="PENDING")
				{
					dup="0";
					getline(file,nric, ',');
					getline(file,curposition, ',');
					getline(file,aplposition);
					selectstmt = "SELECT COUNT(*) FROM pending WHERE nric = '"+nric+"' AND curposition = '"+curposition+"' AND aplposition = '"+aplposition+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||nric=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO pending VALUES ('"+nric+"', '"+curposition+"','"+aplposition+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type=="ANNOUNCEMENT")
				{
					dup="0";
					getline(file,nric, ',');
					getline(file,classID, ',');
					getline(file,position, ',');
					getline(file,remarks);
					selectstmt = "SELECT COUNT(*) FROM announcement WHERE nric = '"+nric+"' AND classID = '"+classID+"' AND position = '"+position+"' AND remarks = '"+remarks+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||nric=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO announcement VALUES (NULL,'"+nric+"', '"+classID+"','"+position+"','"+remarks+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type=="WARNING")
				{
					dup="0";
					getline(file,nric, ',');
					getline(file,warning);
					selectstmt = "SELECT COUNT(*) FROM warning WHERE nric = '"+nric+"' AND warning = '"+warning+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||nric=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO warning VALUES (NULL,'"+nric+"', '"+warning+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type=="STUDENTENROLMENT")
				{
					dup="0";
					getline(file,nric, ',');
					getline(file,modulecode, ',');
					getline(file,sID);
					selectstmt = "SELECT COUNT(*) FROM studentEnrolment WHERE nric = '"+nric+"' AND modulecode = '"+modulecode+"' AND sID = '"+sID+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||nric=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO studentEnrolment VALUES (NULL,'"+nric+"', '"+modulecode+"','"+sID+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
				else if(type=="APPEAL")
				{
					dup="0";
					getline(file,classID , ',');
					getline(file,nric, ',');
					getline(file,reason);
					selectstmt = "SELECT COUNT(*) FROM appeal WHERE classID  = '"+classID +"' AND nric = '"+nric+"' AND reason = '"+reason+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					s = sql_output(sqlQuery);
					if(s=="1"||classID=="")
					{
						dup = "1";
					}
					if(dup=="0")
					{
						count++;
						insertstmt="INSERT INTO appeal VALUES (NULL,'"+classID+"', '"+nric+"','"+reason+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
				}
			}
			if(count==0)
			{
				cout<<"No File/Records found..."<<endl;
			}
			else
			{
				file.close();
				cout<<count<<" records read in successfully!"<<endl;
				break;
			}
		}
		else
		{
			cout<<"Error file name pls enter (.txt) at the back"<<endl;
		}
	}while(1);
}
void Lect::lect_menu()
{
	do
	{
		string choice;
		cout<<endl<<endl<<"Lecturer Page"<<endl;
		cout<<"1)	Mark Attendance"<<endl;
		cout<<"2)	Class Management"<<endl;
		cout<<"3)	Account Management"<<endl;
		cout<<"4)	Logout"<<endl;
		cout<<"Please enter your choice : ";
		cin>>choice;
		if(choice=="1")
		{
			lect_attendance();
		}
		else if(choice=="2")
		{
			class_management();
		}
		else if(choice=="3")
		{
			account();
		}
		else if(choice=="4")
		{
			break;
		}
	}while(1);
}
void mFunction::class_management()
{
	bool check = false;
	string choice;
	do
	{
		cout<<"Class Management"<<endl;
		cout<<"\ta. Add New Class"<<endl;
		cout<<"\tb. Remove Class"<<endl;
		cout<<"\tc. Add Student"<<endl;
		cout<<"\td. Remove Student"<<endl;
		cout<<"\te. Change Venue"<<endl;
		if (login_pos == "LECT")
		cout<<"\tf. Announcement"<<endl;
		cout<<"\tg. Back"<<endl;
		cout<<endl<<"Input your choice : ";
		cin>>choice;
		if (choice == "a")
			add_class();
		else if(choice == "b")
			remove_class();
		else if (choice == "c")
			add_student();
		else if(choice == "d")
			remove_student();
		else if (choice == "e")
			change_venue();
		else  if (choice == "f" && login_pos == "LECT")
			announcement();
		else if (choice == "g")
			check = true;
		else
		{
			cin.clear();
			cin.ignore(100,'\n');
			cout<<endl<<"Please input a,b,c,d, or e!"<<endl;
		}
	}while (!check);
}
void mFunction::add_class()
{
	int choice;
	string selectstmt,date,time,s,modulecode,smester,nric;
	char stmt[1000];
	char modulegroup;
	bool check;
	string venID;
	
	cout<<endl<<"Add Class"<<endl;
	cout<<endl<<"The modules that you are assigned : "<<endl;
	globnum = 1;
	if (login_pos == "ADMN")
		selectstmt = "SELECT modulecode from module;";
	else
		selectstmt = "SELECT modulecode from module where username='"+login_username+"';";
	const char *viewstmt;			
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, listwithnumbers, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		cout << "SQL Error: " << szErrMsg << endl;
		sqlite3_free(szErrMsg);
	}
	if (login_pos == "ADMN")
		selectstmt = "SELECT count(*) from module;";
	else
		selectstmt = "SELECT count(*) from module where username='"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	if (s== "0")
		cout <<"There are currently no module for you to create a class !"<<endl;
	else
	{
		do
		{
			cout<<"Please input the id of the module (1 or 2 etc,0 to cancel) : ";
			cin>>choice;
			cin.clear();	
			cin.ignore(100,'\n');
			if ((choice < 1 || choice >= globnum) && (choice != 0))
				cout<<"Please input the id that is shown above !"<<endl;
		}while ((choice < 1 || choice >= globnum)&&(choice!=0));
		if (choice != 0)
		{
			modulecode = tempValues[choice];
			do
			{
				cout<<endl<<"Please input module group (A,B or C) : ";
				cin>>modulegroup;
				cin.clear();
				cin.ignore(100,'\n');
				if (modulegroup != 'A' && modulegroup != 'B' && modulegroup != 'C')
					cout<<"Please enter either A, or B , or C !"<<endl;
			}while (modulegroup != 'A' && modulegroup != 'B' && modulegroup != 'C');	
	
			cout<<endl<<"Please input date (dd/mm/yy) : ";
			cin>>date;
			cout<<"Please input time (hh:mm) : ";
			cin>>time;
	
			selectstmt = "SELECT COUNT(*) FROM class WHERE date = '"+date+"' AND time = '"+time+"' and modulecode='"+modulecode+"';";
			strcpy(stmt, selectstmt.c_str());	
			sqlQuery = stmt;
			s = sql_output(sqlQuery);
	
			if (s == "0")
			{
				cout<<endl<<"Here are the semesters that are available for the module :"<<endl;
				globnum = 1;
				selectstmt = "SELECT sid as 'Sem ID',modulecode,semester,year from semester where modulecode='"+modulecode+"';";
				const char *viewstmt;			
				viewstmt = selectstmt.c_str();
				rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
				if(rc != SQLITE_OK)
				{
					cout << "SQL Error: " << szErrMsg << endl;
					sqlite3_free(szErrMsg);
				}
				if (globnum == 1)
					cout<<endl<<"No semesters exist for this module, please ask admin to create"<<endl;
				else
				{
					do
					{
						cout<<"Please input the sid of the semester : ";
						cin>>choice;
						cin.clear();	
						cin.ignore(100,'\n');
						if (choice < 1 || choice >= globnum)
							cout<<"Please input the id that is shown above !"<<endl;
					}while (choice < 1 || choice >= globnum);
					globnum = 1;
					ostringstream Convert;

					Convert << choice; 

					smester = Convert.str();
					cout<<endl<<endl;

					selectstmt = "SELECT venueid as 'Venue ID',level as 'Level',unit as 'Unit Type' from venue where venueid not in (select venueid from class where date='"+date+"' and time = '"+time+"');";
					firstline = true;
					viewstmt = selectstmt.c_str();

					rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
					if(rc != SQLITE_OK)
					{
						cout << "SQL Error: " << szErrMsg << endl;
						sqlite3_free(szErrMsg);
					}
					firstline = true;
					if (globnum != 1)
					{
						cout<<"Please input the venue id : ";
						cin>>venID;
						string insertstmt;
						selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
						strcpy(stmt, selectstmt.c_str());	
						sqlQuery = stmt;
						nric = sql_output(sqlQuery);
						insertstmt="INSERT INTO class(nric,modulecode,modulegroup,date,time,duration,sid,venueid) VALUES ('"+nric+"', '"+modulecode+"', '"+modulegroup+"', '"+date+"', '"+time+"',3,'"+smester+"','"+venID+"');";
						strcpy(stmt, insertstmt.c_str());	
						sqlQuery = stmt;
						sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
						int res=sqlite3_step(selectStmt);
						sqlite3_finalize(selectStmt);
					}
					else
						cout<<"No more venues available!"<<endl;
				}
			}
			else
			{
				cout<<"Class already existed!"<<endl;
			}
		}
	}
}


void mFunction::remove_class()
{
	string date,time,selectstmt,dltstmt,nric,s;
	char stmt[1000];
	int choice;
	cout<<"Remove Class"<<endl;
	cout<<"Please input date of class : ";
	cin>>date;
	globnum = 1;
	selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	nric = sql_output(sqlQuery);
	string insertstmt;
	if (login_pos == "ADMN")
		selectstmt = "SELECT time as 'Time' from class where date = '"+date+"';";
	else
		selectstmt = "SELECT time as 'Time' from class where nric='"+nric+"' and date = '"+date+"';";
	cout<<endl<<"Time of Classes : "<<endl;
	const char *viewstmt;			
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, listwithnumbers, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		cout << "SQL Error: " << szErrMsg << endl;
		sqlite3_free(szErrMsg);
	}
	if (login_pos == "ADMN")
		selectstmt = "SELECT count(*) from class where date = '"+date+"'";
	else
		selectstmt = "SELECT count(*) from class where nric='"+nric+"' and date = '"+date+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	if (s=="0")
		cout<<"There are no classes on that date!"<<endl;
	else
	{
		do
		{
			cout<<"Please input the id of the time (1 or 2 etc),0 to cancel : ";
			cin>>choice;
			cin.clear();	
			cin.ignore(100,'\n');
			if (choice < 1 || choice >= globnum)
				cout<<"Please input the id that is shown above !"<<endl;
		}while (choice <0 || choice >= globnum);
		if (choice != 0)
		{
			time = tempValues[choice];
			dltstmt="delete from class where date ='"+date+"' and time ='"+time+"';";
				strcpy(stmt, dltstmt.c_str());	
				sqlQuery = stmt;
				sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
				int res=sqlite3_step(selectStmt);
				sqlite3_finalize(selectStmt);
		}	
		else
			cout<<"Back to main menu..."<<endl;
	}
}
void mFunction::add_student()
{

	string nric,s;
	string selectstmt,modulecode,smester;
	char stmt[1000];
	int choice;
	cout<<endl<<"Add Student"<<endl;
	if (login_pos == "ADMN")
		selectstmt = "SELECT count(*) from module;";
	else
		selectstmt = "SELECT count(*) from module where username='"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	if (s== "0")
		cout<<"There are currently no modules that you can assign a student to!"<<endl;
	else
	{
		do
		{
	
			cout<<"Please input the NRIC of the student (0 to cancel): ";
			cin>>nric;
			selectstmt = "SELECT count(*) from user where nric='"+nric+"';";
			strcpy(stmt, selectstmt.c_str());	
			sqlQuery = stmt;
			s = sql_output(sqlQuery);

			if (s == "0" && nric != "0")
			{
				cout<<"Student with this NRIC does not exists!"<<endl;
			}
		}while (s == "0" && nric != "0");

		if (s != "0")
		{
		
			cout<<endl<<"The modules that you are assigned : "<<endl;
			globnum = 1;
			if (login_pos == "ADMN")
				selectstmt = "SELECT modulecode from module;";
			else
				selectstmt = "SELECT modulecode from module where username='"+login_username+"';";
			const char *viewstmt;			
			viewstmt = selectstmt.c_str();
			rc = sqlite3_exec(db, viewstmt, listwithnumbers, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				cout << "SQL Error: " << szErrMsg << endl;
				sqlite3_free(szErrMsg);
			}
	
			do
			{
				cout<<"Please input the id of the module (1 or 2 etc) : ";
				cin>>choice;
				cin.clear();	
				cin.ignore(100,'\n');
				if (choice < 1 || choice >= globnum)
					cout<<"Please input the id that is shown above !"<<endl;
			}while (choice < 1 || choice >= globnum);
			modulecode = tempValues[choice];



			cout<<endl<<"The semesters available for the module : "<<endl;
			globnum = 1;
			selectstmt = "SELECT sid,semester,year from semester where modulecode='"+modulecode+"';";	
			viewstmt = selectstmt.c_str();
			rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				cout << "SQL Error: " << szErrMsg << endl;
				sqlite3_free(szErrMsg);
			}
	
			cout<<"Please input the sid : ";
			cin>>smester;


			string insertstmt;

			insertstmt="INSERT INTO studentEnrolment(nric,modulecode,sID) VALUES ('"+nric+"', '"+modulecode+"', '"+smester+"');";
			strcpy(stmt, insertstmt.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
		}
	}
}

void mFunction::remove_student()
{
	string date,time,nric,modulecode,selectstmt,dltstmt,s;
	char stmt[1000];
	int choice;
	cout<<"Remove Class"<<endl;
	cout<<"Please input the nric of the student : ";
	cin>>nric;
	globnum = 1;
	selectstmt = "SELECT count(*) from studentEnrolment where nric='"+nric+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	if (s!= "0")
	{
		selectstmt = "SELECT modulecode from studentEnrolment where nric='"+nric+"';";
	
		const char *viewstmt;			
		viewstmt = selectstmt.c_str();
		rc = sqlite3_exec(db, viewstmt, listwithnumbers, 0, &szErrMsg);
		if(rc != SQLITE_OK)
		{
			cout << "SQL Error: " << szErrMsg << endl;
			sqlite3_free(szErrMsg);
		}
		do
		{
			cout<<"Please input the id of the module (1 or 2 etc),0 to cancel : ";
			cin>>choice;
			cin.clear();	
			cin.ignore(100,'\n');
			if (choice < 1 || choice >= globnum)
				cout<<"Please input the id that is shown above !"<<endl;
		}while (choice <0 || choice >= globnum);
		modulecode = tempValues[choice];
		if (choice != 0)
		{
			time = tempValues[choice];
			dltstmt="delete from studentEnrolment where nric ='"+nric+"' and modulecode ='"+modulecode+"';";
				strcpy(stmt, dltstmt.c_str());	
				sqlQuery = stmt;
				sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
				int res=sqlite3_step(selectStmt);
				sqlite3_finalize(selectStmt);
		}	
		else
			cout<<"Back to main menu..."<<endl;
	}
	else
		cout<<"There are no modules for that student!"<<endl;
}
void mFunction::change_venue()
{
	string selectstmt,date,time,classID,updatestmt,nric,s;
	char stmt[1000];
	char modulegroup;
	bool check;
	string venID;
	const char *viewstmt;
	selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	nric = sql_output(sqlQuery);

	if (login_pos == "ADMN")
		selectstmt = "SELECT count(*) from class;";
	else
		selectstmt = "SELECT count(*) from class where nric='"+nric+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	if (s== "0")
		cout<<"There are currently no class that you can change venue!"<<endl;
	else
	{
		globnum = 1;
		if (login_pos == "ADMN")
			selectstmt = "SELECT classID,nric,modulecode,modulegroup,date,time,duration,sid,venueid,markedAtt from class;";
		else
			selectstmt = "SELECT classID,nric,modulecode,modulegroup,date,time,duration,sid,venueid,markedAtt from class where nric='"+nric+"';";			
		viewstmt = selectstmt.c_str();
		rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
		if(rc != SQLITE_OK)
		{
			cout << "SQL Error: " << szErrMsg << endl;
			sqlite3_free(szErrMsg);
		}
		cout<<"Please input the class ID : ";
		cin>>classID;
	
		selectstmt = "SELECT date FROM class WHERE classID = '"+classID+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		date = sql_output(sqlQuery);
		selectstmt = "SELECT time FROM class WHERE classID = '"+classID+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		time = sql_output(sqlQuery);
		
		selectstmt = "SELECT count(*) from venue where venueid not in (select venueid from class where date='"+date+"' and time = '"+time+"');";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		s = sql_output(sqlQuery);
		if (s== "0")
			cout<<"There are currently no more venue!"<<endl;
		else
		{
				cout.width(17); cout<<"Venue ID"<<left;
				cout.width(17); cout<<"Level"<<left;
				cout.width(17); cout<<"Level"<<left<<endl;
			selectstmt = "SELECT venueid as 'Venue Id',level as 'Level',unit as 'Unit' from venue where venueid not in (select venueid from class where date='"+date+"' and time = '"+time+"');";
			firstline = true;
			viewstmt = selectstmt.c_str();
			rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				cout << "SQL Error: " << szErrMsg << endl;
				sqlite3_free(szErrMsg);
			}
			firstline = true;

			cout<<"Please input the venue id : ";
			cin>>venID;

			updatestmt="update class set venueid='"+venID+"' where classID ='"+classID+"';";
			strcpy(stmt, updatestmt.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
		}
	}
}
void mFunction::announcement()
{
	string selectstmt,date,time,classID,announcement,nric,s;
	char stmt[1000];
	char modulegroup;
	bool check;
	const char *viewstmt;
	if (login_pos == "ADMN")
		selectstmt = "SELECT count(*) from class;";
	else
	{
		selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		nric = sql_output(sqlQuery);
		string insertstmt;
		selectstmt = "SELECT count(*) from class where nric='"+nric+"';";			
	}	
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	if (s== "0")
		cout<<"There are currently no classes that you can announce to!"<<endl;
	else
	{
		globnum = 1;
		if (login_pos == "ADMN")
			selectstmt = "SELECT classID as 'ClassID' ,nric as 'NRIC',modulecode as 'Module Code' ,modulegroup as 'Module Group' ,date,time,duration,sid as 'semester ID',venueid as 'venue ID',markedAtt as 'Attendance' from class;";
		else
		{
			selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
			strcpy(stmt, selectstmt.c_str());	
			sqlQuery = stmt;
			nric = sql_output(sqlQuery);
			string insertstmt;
			selectstmt = "SELECT classID as 'ClassID' ,nric as 'NRIC',modulecode as 'Module Code' ,modulegroup as 'Module Group' ,date,time,duration,sid as 'semester ID',venueid as 'venue ID',markedAtt as 'Attendance' from class where nric='"+nric+"';";			
		}	
		viewstmt = selectstmt.c_str();
		firstline = true;
		rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
		
		if(rc != SQLITE_OK)
		{
			cout << "SQL Error: " << szErrMsg << endl;
			sqlite3_free(szErrMsg);
		}
		firstline = true;
		cout<<"Please input the class ID : ";
		cin>>classID;
		cout<<"Please input the announcement : ";
		cin.clear();
		cin.ignore(100,'\n');
		getline(cin,announcement,'\n');
		selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		nric = sql_output(sqlQuery);
		string insertstmt;

		insertstmt="INSERT INTO announcement(nric,classID,position,remarks) VALUES ('"+nric+"', '"+classID+"', '','"+announcement+"');";

		strcpy(stmt, insertstmt.c_str());	
		sqlQuery = stmt;
		sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
		int res=sqlite3_step(selectStmt);
		sqlite3_finalize(selectStmt);
	}
}
void Lect::lect_attendance()
{
	//Select or enter class ID
	string selectstmt,date,time,classID,announcement,nric,sID,modulecode,updatestmt,insertstmt,s;
	char stmt[1000];
	char modulegroup;
	bool check;
	int choice,warnLevel;
	const char *viewstmt;
	do
	{
		cout<<"Select which classes do you want to mark attendance for : "<<endl;
		cout<<"\t 1) Classes that its attendance have not been marked"<<endl;
		cout<<"\t 2) Edit the attendance of the classes that was marked"<<endl;
		cout<<"\t 3) Back"<<endl;
		cout<<"Please enter your choice : ";
		cin>>choice;
		cin.clear();
		cin.ignore(100,'\n');
		if (choice != 1 && choice != 2 && choice != 3)
			cout<<"Please enter either 1 or 2 or 3!"<<endl;
	}while (choice != 1 && choice != 2 && choice != 3);
	if (choice != 3)
	{
		globnum = 1;
		selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		nric = sql_output(sqlQuery);
		if (choice == 1)
			selectstmt = "SELECT count(*) from class where nric='"+nric+"' and markedAtt = 0";
		else
		{
			selectstmt = "SELECT count(*) from class where nric='"+nric+"' and markedAtt = 1";	
		}	
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		s = sql_output(sqlQuery);
		if (s== "0")
			cout<<"There are no classes that you can mark attendance to!"<<endl;
		else
		{
			if (choice == 1)
				selectstmt = "SELECT classID,nric,modulecode,modulegroup,date,time,duration,sid,venueid,markedAtt from class where nric='"+nric+"' and markedAtt = 0";
			else
				selectstmt = "SELECT classID,nric,modulecode,modulegroup,date,time,duration,sid,venueid,markedAtt from class where nric='"+nric+"' and markedAtt = 1";
			viewstmt = selectstmt.c_str();
			firstline = true;
			rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				cout << "SQL Error: " << szErrMsg << endl;
				sqlite3_free(szErrMsg);
			}
			firstline = true;
			cout<<"Please input the class ID : ";
			cin>>classID;
			selectstmt = "SELECT modulecode FROM class WHERE classID = '"+classID+"';";
				strcpy(stmt, selectstmt.c_str());	
				sqlQuery = stmt;
				modulecode = sql_output(sqlQuery);
			if  (choice == 1)
			{
				selectstmt = "SELECT sID FROM class WHERE classID = '"+classID+"';";
				strcpy(stmt, selectstmt.c_str());	
				sqlQuery = stmt;
				sID = sql_output(sqlQuery);

				globnum = 1;
				selectstmt = "select nric from studentEnrolment where sID='"+sID+"' and modulecode='"+modulecode+"'";
				viewstmt = selectstmt.c_str();
		
				rc = sqlite3_exec(db, viewstmt, getColumnArray, 0, &szErrMsg);
				if(rc != SQLITE_OK)
				{
					cout << "SQL Error: " << szErrMsg << endl;
					sqlite3_free(szErrMsg);
				}
				for (int i = 1; i < globnum; i++)
				{
					insertstmt="INSERT INTO attendance(nric,classID,status) VALUES ('"+tempValues[i]+"', '"+classID+"','Y');";
					strcpy(stmt, insertstmt.c_str());	
					sqlQuery = stmt;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					int res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);
				}
				updatestmt="update class set markedAtt=1 where classID ='"+classID+"';";
				strcpy(stmt, updatestmt.c_str());	
				sqlQuery = stmt;
				sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
				int res=sqlite3_step(selectStmt);
				sqlite3_finalize(selectStmt);
			}
			string tmpStat;
			do
			{
				selectstmt = "select nric,classID,status from attendance where classID='"+classID+"'";
				viewstmt = selectstmt.c_str();
				rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
				if(rc != SQLITE_OK)
				{
					cout << "SQL Error: " << szErrMsg << endl;
					sqlite3_free(szErrMsg);
				}
				cout<<"To change the status of any student , please enter the nric of any absent members,enter 0 to end : ";
				cin>>nric;
				string tmpcount1,tmpcount2,tmpcount3;
				char tmp1[1000],tmp2[100],tmp3[100];
				char stmt1[1000],stmt2[1000],stmt3[1000];
				int count;
				if (nric != "0")
				{
					selectstmt = "SELECT status FROM attendance WHERE nric = '"+nric+"' and classID='"+classID+"';";
					strcpy(stmt, selectstmt.c_str());	
					sqlQuery = stmt;
					tmpStat = sql_output(sqlQuery);
					if (tmpStat == "Y")
						updatestmt="update attendance set status='N' where nric ='"+nric+"' and classID='"+classID+"';";
					else 	if (tmpStat == "N")
						updatestmt="update attendance set status='Y' where nric ='"+nric+"' and classID='"+classID+"';";
			
					strcpy(stmt, updatestmt.c_str());	
					sqlQuery = stmt;
					sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
					int res=sqlite3_step(selectStmt);
					sqlite3_finalize(selectStmt);
					warnLevel = check_warning(nric,modulecode);
					if (warnLevel == 1)
					{
						selectstmt = "select count(*) from warning where nric='"+nric+"' and warning='First warning! Attendance for "+modulecode+" is below 90%';";
						strcpy(stmt1, selectstmt.c_str());	
						sqlQuery = stmt1;
						tmpcount1 = sql_output(sqlQuery);
						strcpy(tmp1,tmpcount1.c_str());	
						count = atoi(tmp1);
						if (count == 0)
						{
							insertstmt="insert into warning(nric,warning) values ('"+nric+"','First warning! Attendance for "+modulecode+" is below 90%');";
			
							strcpy(stmt, insertstmt.c_str());	
							sqlQuery = stmt;
							sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
							int res=sqlite3_step(selectStmt);
							sqlite3_finalize(selectStmt);
						}
					}
					else if (warnLevel == 2)
					{
						selectstmt = "select count(*) from warning where nric='"+nric+"' and warning='Second warning! Attendance for "+modulecode+" is below 80%';";
						strcpy(stmt2, selectstmt.c_str());	
						sqlQuery = stmt2;
						tmpcount2 = sql_output(sqlQuery);
						strcpy(tmp2,tmpcount2.c_str());	
						count = atoi(tmp2);
						if (count == 0)
						{
							insertstmt="insert into warning(nric,warning) values ('"+nric+"','Second warning! Attendance for "+modulecode+" is below 80%');";
							strcpy(stmt, insertstmt.c_str());	
							sqlQuery = stmt;
							sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
							int res=sqlite3_step(selectStmt);
							sqlite3_finalize(selectStmt);
						}
					}
					else if (warnLevel == 3)
					{
						selectstmt = "select count(*) from warning where nric='"+nric+"' and warning='Last warning! Attendance for "+modulecode+" is below 75%';";	
						strcpy(stmt3, selectstmt.c_str());	
						sqlQuery = stmt3;
						tmpcount3 = sql_output(sqlQuery);
						strcpy(tmp3,tmpcount3.c_str());	
						count = atoi(tmp3);
						if (count == 0)
						{
							insertstmt="insert into warning(nric,warning) values ('"+nric+"','Last warning! Attendance for "+modulecode+" is below 75%');";
							strcpy(stmt, insertstmt.c_str());	
							sqlQuery = stmt;
							sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
							int res=sqlite3_step(selectStmt);
							sqlite3_finalize(selectStmt);
						}
					}
				}
			}while (nric != "0");
		}
	}
}
int mFunction::check_warning(string nric,string modulecode)
{
	string selectstmt;
	char stmt[1000],stmt2[1000];
	char tmp[100],tmp2[100];
	string tmpcount,tmphour;
	int count;
	double percent,totalhour,hoursattended;
	selectstmt = "select count(*) from attendance where nric='"+nric+"' and status='N' and classID in (select classID from class where modulecode='"+modulecode+"');";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	tmpcount = sql_output(sqlQuery);
	strcpy(tmp,tmpcount.c_str());	
	count = atoi(tmp);

	selectstmt = "select totalnoofhrs from module where modulecode='"+modulecode+"';";
	strcpy(stmt2, selectstmt.c_str());
	sqlQuery = stmt2;
	tmphour = sql_output(sqlQuery);
	strcpy(tmp2,tmphour.c_str());
	totalhour = atoi(tmp2);

	hoursattended = totalhour - (count*3);
	percent = hoursattended/totalhour;
	percent = percent * 100;
	if (percent < 75)
		return 3;
	else if (percent < 80)
		return 2;
	else if (percent < 90)
		return 1;
	return 0;
}


void mFunction::account()
{
	//Display code here
	string selectstmt = "SELECT name AS 'Full Name', email AS 'Email', mobileNo AS 'Mobile No.',question AS 'Security Question',answer AS 'Security Answer' FROM User WHERE username = '"+login_username+"';";
	const char *viewstmt;			
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, listview, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		std::cout << "SQL Error: " << szErrMsg << std::endl;
		sqlite3_free(szErrMsg);
	}
	do
	{
		string choice;
		cout<<"Do you want to edit your account (Y/N) :";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			account_menu(login_username);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::account_menu(string user)//For LECT and STUD
{
	do
	{
		string choice;
		cout<<"Please select which field to edit"<<endl;
		cout<<"1)	Email"<<endl;
		cout<<"2)	Mobile"<<endl;
		cout<<"3)	Password"<<endl;
		cout<<"4)	Secret Question & Answer"<<endl;
		cout<<"5)	Return to homepage"<<endl;
		cout<<"Please enter your choice :";
		cin>>choice;
		if(choice=="1")
		{
			account_email(user);
		}
		else if(choice=="2")
		{
			account_mobile(user);
		}
		else if(choice=="3")
		{
			account_password(user);
		}
		else if(choice=="4")
		{
			account_qna(user);
		}
		else if(choice=="5")
		{
			break;
		}
	}while(1);
}

void Stud::stud_menu()
{
	do
	{
		string selectstmt,nric;
		char stmt[1000],stmt2[1000];
		char tmp[100],tmp2[100];
		string tmpcount,tmpcount2;
		int count,count2;
const char *viewstmt;
		selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		nric = sql_output(sqlQuery);

		selectstmt = "select count(*) from warning where nric='"+nric+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		tmpcount = sql_output(sqlQuery);
		strcpy(tmp,tmpcount.c_str());	
		count = atoi(tmp);
		if (count > 0)
		{
			globnum=1;
			string selectstmt = "SELECT warning FROM warning WHERE nric = '"+nric+"';";
					
			viewstmt = selectstmt.c_str();
			rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				std::cout << "SQL Error: " << szErrMsg << std::endl;
				sqlite3_free(szErrMsg);
			}
		}
		cout<<endl;
		selectstmt = "select count(*) from announcement where position = 'STUD';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		tmpcount = sql_output(sqlQuery);
		strcpy(tmp,tmpcount.c_str());	
		count = atoi(tmp);
	
		selectstmt = "select count(*) from announcement where classID in (select classID from class where nric='"+nric+"');";
		strcpy(stmt2, selectstmt.c_str());	
		sqlQuery = stmt2;
		tmpcount2 = sql_output(sqlQuery);
		strcpy(tmp2,tmpcount2.c_str());	
		count2 = atoi(tmp2);
		if (count > 0 || count2 > 0)
		{
			globnum = 1;
			cout<<endl;
			selectstmt = "SELECT remarks FROM announcement WHERE position = 'STUD';";
						
			viewstmt = selectstmt.c_str();
			rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				std::cout << "SQL Error: " << szErrMsg << std::endl;
				sqlite3_free(szErrMsg);
			}

			selectstmt = "SELECT remarks FROM announcement WHERE classID in (select classID from class where modulecode in (select modulecode from studentEnrolment where nric='"+nric+"'));";
			viewstmt = selectstmt.c_str();
			rc = sqlite3_exec(db, viewstmt, listwithnumbers, 0, &szErrMsg);
			if(rc != SQLITE_OK)
			{
				std::cout << "SQL Error: " << szErrMsg << std::endl;
				sqlite3_free(szErrMsg);
			}
		}
		cout<<endl;
		string choice;
		cout<<endl<<"Student Page"<<endl;
		cout<<"1)	Appeal for attendance"<<endl;
		cout<<"2)	Account Information"<<endl;
		cout<<"3)	View Attendance"<<endl;
		cout<<"4)	Current Modules"<<endl;
		cout<<"5)	View Timetable"<<endl;
		cout<<"6)	Logout"<<endl;
		cout<<"Please enter your choice :";
		cin>>choice;
		if(choice == "1")
		{
			stud_appeal();
		}
		else if(choice=="2")
		{
			account();
		}
		else if(choice=="3")
		{
			stud_viewAtt();
		}
		else if(choice=="4")
		{
			stud_currMod();
		}
		else if(choice=="5")
		{
			stud_timetable();		
		}
		else if(choice=="6")
		{
			cout<<"Logging out";
			break;
		}
	}while(1);
	
}
void Stud::stud_appeal()
{
	string selectstmt,reason,nric,classID,insertstmt;
	char stmt[1000];
	const char *viewstmt;

	cout<<"Your attendance Report : "<<endl;
	selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	nric = sql_output(sqlQuery);
	selectstmt = "SELECT nric as 'NRIC',classID,status from attendance where nric ='"+nric+"' and status='N' and classID not in (select classID from APPEAL where nric='"+nric+"')";
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		cout << "SQL Error: " << szErrMsg << endl;
		sqlite3_free(szErrMsg);
	}
	cout<<"Please input the classID : ";
	cin>>classID;
	cin.clear();
	cin.ignore(100,'\n');
	cout<<"Please input your reason : ";
	getline(cin,reason,'\n');
	insertstmt="INSERT INTO APPEAL(classID, nric,reason) VALUES ('"+classID+"','"+nric+"','"+reason+"');";
	strcpy(stmt, insertstmt.c_str());	
	sqlQuery = stmt;
	sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
	int res=sqlite3_step(selectStmt);
	sqlite3_finalize(selectStmt);
}
void Stud::stud_viewAtt()
{
	string selectstmt,nric;
	char stmt[1000];
	const char *viewstmt;

	cout<<"Your attendance Report : "<<endl;
	selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	nric = sql_output(sqlQuery);
	selectstmt = "SELECT nric as 'NRIC',classID,status from attendance where nric ='"+nric+"'";
		
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		cout << "SQL Error: " << szErrMsg << endl;
		sqlite3_free(szErrMsg);
	}
	
}
void Stud::stud_currMod()
{
	string selectstmt,nric;
	char stmt[1000];
	const char *viewstmt;

	cout<<"Your Enrolled Module : "<<endl;
	selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	nric = sql_output(sqlQuery);
	selectstmt = "SELECT sEID as 'Student Enrollment ID',nric as 'NRIC',modulecode as 'Module Code',sID from studentEnrolment where nric ='"+nric+"'";
		firstline = true;
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		cout << "SQL Error: " << szErrMsg << endl;
		sqlite3_free(szErrMsg);
	}
	firstline = true;
}
void Stud::stud_timetable()
{
	string selectstmt,nric;
	char stmt[1000];
	const char *viewstmt;

	cout<<"Your timetable : "<<endl;
	selectstmt = "SELECT nric FROM user WHERE username = '"+login_username+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	nric = sql_output(sqlQuery);
	selectstmt = "SELECT modulecode,modulegroup,date,time from class where modulecode in (select modulecode from studentEnrolment where nric='"+nric+"')";
		firstline = true;
	viewstmt = selectstmt.c_str();
	rc = sqlite3_exec(db, viewstmt, callback, 0, &szErrMsg);
	if(rc != SQLITE_OK)
	{
		cout << "SQL Error: " << szErrMsg << endl;
		sqlite3_free(szErrMsg);
	}
	firstline = true;
}
void Main::main_menu()
{
	do
	{
		string choice;
		cout<<endl<<endl<<"Welcome to XXX school system"<<endl;
		cout<<"1)	Login"<<endl;
		cout<<"2)	Forget Password"<<endl;
		cout<<"3)	Register"<<endl;
		cout<<"4)	Quit"<<endl<<endl;
		cout<<"Please enter your choice : ";
		cin>>choice;
		if(choice=="1")
		{
			login_menu();
		}
		else if(choice=="2")
		{
			forget_pass();
		}
		else if(choice=="3")
		{
			reg_page();
		}
		else if(choice=="4")
		{
			cout<<"Thank you for using the program"<<endl;
			break;
		}
		cout<<endl;
	}while(1);
}
///////////////////////////////////////EDITING ACCOUNT CODES HERE/////////////////////////////////////////////////////
void mFunction::account_fname(string user)
{
	string selectstmt, s;
	char stmt[1000];
	selectstmt = "SELECT name FROM USER WHERE username = '"+user+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	cout<<"Existing Full Name : "<<s<<endl;
	do
	{
		string choice;
		cout<<"Do you confirm you want to edit(Y/N):";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			edit_fname(user);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::account_email(string user)
{
	string selectstmt, s;
	char stmt[1000];
	selectstmt = "SELECT email FROM USER WHERE username = '"+user+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	cout<<"Existing Email : "<<s<<endl;
	do
	{
		string choice;
		cout<<"Do you confirm you want to edit(Y/N):";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			edit_email(user);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::account_mobile(string user)
{
	string selectstmt, s;
	char stmt[1000];

	selectstmt = "SELECT mobileNo FROM USER WHERE username = '"+user+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	cout<<"Existing Mobile : "<<s<<endl;
	do
	{
		string choice;
		cout<<"Do you confirm you want to edit(Y/N):";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			edit_mobile(user);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::account_username(string user)
{
	cout<<"Existing Username : "<<user<<endl;
	do
	{
		string choice;
		cout<<"Do you confirm you want to edit(Y/N):";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			edit_username(user);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::account_password(string user)
{
	int tries=0;
	string epass,npass1,npass2,selectstmt,updatePass,s;
	char stmt[1000];
	const int NUMBER = 100;	
	char password2[NUMBER];
	do
	{
		cout<<"Existing Password :";
		cin>>epass;
		selectstmt = "SELECT COUNT(*) FROM USER WHERE username = '"+user+"' AND password = '"+epass+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;	
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			do
			{
				cout<<"New Password :";
				cin>>npass1;
				cout<<"Confirm New Password :";
				cin>>npass2;
				if(npass1==npass2)
				{
					strcpy(password2,npass2.c_str());
					int nx = strlen(password2);
					int te = (testStr(password2, nx));
					if(nx < 8)
					{
						cout<<"-  The password entered is less than 8 characters.\n\n";
					}
					else
					{
						if (te == 1)
						{		
							updatePass = "UPDATE USER SET password = '"+npass2+"' WHERE username = '"+user+"';";
							strcpy(stmt, updatePass.c_str());	
							sqlQuery = stmt;
							sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
							int res=sqlite3_step(selectStmt);
							sqlite3_finalize(selectStmt);
							break;
						}
						else if (te == 2)
						{
							cout<<"-  No letter found in password\n";
						}
						else if (te == 3)
						{
							cout<<"-  Digit not found in password.\n";
						}
					}
				}
				else
				{
					cout<<"-  Password does not match"<<endl;
				}
			}while(1);
			break;
		}
		else
		{
			tries++;
			if(tries<3)
			{
				cout<<"Invalid Password"<<endl;
			}
			else
			{
				break;
			}
		}
	}while(1);

}
void mFunction::account_pos(string user)
{
	string selectstmt, s;
	char stmt[1000];
	selectstmt = "SELECT position FROM USER WHERE username = '"+user+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	cout<<"Existing Position : "<<s<<endl;
	do
	{
		string choice;
		cout<<"Do you confirm you want to edit(Y/N):";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			edit_pos(user);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::account_lock(string user)
{
	string selectstmt, s;
	char stmt[1000];
	selectstmt = "SELECT lock FROM USER WHERE username = '"+user+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	cout<<"Existing Lock Status : "<<s<<endl;
	do
	{
		string choice;
		cout<<"Do you confirm you want to edit(Y/N):";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			edit_lock(user);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::account_qna(string user)
{
	string selectstmt, s;
	char stmt[1000];
	selectstmt = "SELECT question FROM USER WHERE username = '"+user+"';";
	strcpy(stmt, selectstmt.c_str());	
	sqlQuery = stmt;
	s = sql_output(sqlQuery);
	cout<<"Existing Security Question : "<<s<<endl;
	do
	{
		string choice;
		cout<<"Do you confirm you want to edit(Y/N):";
		cin>>choice;
		if(choice=="y"||choice=="Y")
		{
			edit_qna(user);
			break;
		}
		else if(choice=="n"||choice=="N")
		{
			break;
		}
	}while(1);
}
void mFunction::edit_fname(string user)
{
	int check;
	if(login_pos=="ADMN")
	{
		check=admn_verify(login_username);
	}
	else
	{
		check=1;
	}
	if(check==1)
	{
		do
		{
			string fname;
			cout<<"New Full name :";
			cin.clear();
			cin.ignore(100,'\n');
			getline(cin,fname,'\n');
			string updateFname;
			char stmt[1000];
			updateFname = "UPDATE USER SET name = '"+fname+"' WHERE username = '"+user+"';";
			strcpy(stmt, updateFname.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
			cout<<"Full Name has been updated"<<endl;
			break;
		}while(1);
	}
	else
	{
		cout<<"Password error"<<endl;
	}
}
void mFunction::edit_email(string user)
{
	do
	{
		string email;
		cout<<"New Email :";
		cin>>email;
		string updateEmail;
		char stmt[1000];
		updateEmail = "UPDATE USER SET email = '"+email+"' WHERE username = '"+user+"';";
		strcpy(stmt, updateEmail.c_str());	
		sqlQuery = stmt;
		sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
		int res=sqlite3_step(selectStmt);
		sqlite3_finalize(selectStmt);
		cout<<"Email has been updated"<<endl;
		break;
	}while(1);
}
void mFunction::edit_mobile(string user)
{
	const int NUMBER = 100;
	char mobile2[NUMBER];
	do
	{
		string mobile;
		cout<<"New Mobile No :";
		cin>>mobile;
		strcpy(mobile2,mobile.c_str());
		int nx = strlen(mobile2);
		int te = (testStr(mobile2, nx));
		if (te == 3){
			cout<<"-  There should not be letter in your mobile no.\n";
		}
		else{
			string updateMobile;
			char stmt[1000];
			updateMobile = "UPDATE USER SET mobileNo = '"+mobile+"' WHERE username = '"+user+"';";
			strcpy(stmt, updateMobile.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
			cout<<"Mobile No. has been updated"<<endl;
			break;
		}
	}while(1);
}
void mFunction::edit_username(string user)
{
	int check;
	if(login_pos=="ADMN")
	{
		check=admn_verify(login_username);
	}
	else
	{
		check=1;
	}
	if(check==1)
	{
		do
		{
			string username;
			cout<<"New Username :";
			cin>>username;
			string updateUsername;
			char stmt[1000];
			updateUsername = "UPDATE USER SET username = '"+username+"' WHERE username = '"+user+"';";
			strcpy(stmt, updateUsername.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
			cout<<"Username has been updated"<<endl;
			break;
		}while(1);
	}
	else
	{
		cout<<"Password error"<<endl;
	}
}
void mFunction::edit_password(string user)
{
	int check;
	if(login_pos=="ADMN")
	{
		check=admn_verify(login_username);
	}
	else
	{
		check=1;
	}
	if(check==1)
	{
		do
		{
			string password;
			cout<<"New Password :";
			cin>>password;
			string updatePassword;
			char stmt[1000];
			updatePassword = "UPDATE USER SET password = '"+password+"' WHERE username = '"+user+"';";
			strcpy(stmt, updatePassword.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
			cout<<"Password has been updated"<<endl;
			break;
		}while(1);
	}
	else
	{
		cout<<"Password error"<<endl;
	}
}
void mFunction::edit_pos(string user)
{
	int check;
	if(login_pos=="ADMN")
	{
		check=admn_verify(login_username);
	}
	else
	{
		check=1;
	}
	if(check==1)
	{
		do
		{
			string choice, pos;
			cout<<"1)	ADMN"<<endl;
			cout<<"2)	LECT"<<endl;
			cout<<"3)	STUD"<<endl;
			cout<<"Please enter choice :";
			cin>>choice;
			if(choice=="1"||choice=="2"||choice=="3")
			{
				if(choice=="1")
				{
					pos="ADMN";
				}
				else if(choice=="2")
				{
					pos="LECT";
				}
				else if(choice=="3")
				{
					pos="STUD";
				}
				string updatePosition;
				char stmt[1000];
				updatePosition = "UPDATE USER SET position = '"+pos+"' WHERE username = '"+user+"';";
				strcpy(stmt, updatePosition.c_str());	
				sqlQuery = stmt;
				sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
				int res=sqlite3_step(selectStmt);
				sqlite3_finalize(selectStmt);
				cout<<"Position has been updated"<<endl;
				break;
			}
			else
			{
				cout<<"Invalid choice"<<endl;
			}
		}while(1);
	}
	else
	{
		cout<<"Password error"<<endl;
	}
}
void mFunction::edit_lock(string user)
{
	int check;
	if(login_pos=="ADMN")
	{
		check=admn_verify(login_username);
	}
	else
	{
		check=1;
	}
	if(check==1)
	{
		do
		{
			string choice, lock;
			cout<<"1)	LOCK";
			cout<<"2)	UNLOCK";
			cout<<"Please enter choice :";
			cin>>choice;
			if(choice=="1"||choice=="2"||choice=="3")
			{
				if(choice=="1")
				{
					lock="L";
				}
				else if(choice=="2")
				{
					lock="U";
				}
				string updateLock;
				char stmt[1000];
				updateLock = "UPDATE USER SET lock = '"+lock+"' WHERE username = '"+user+"';";
				strcpy(stmt, updateLock.c_str());	
				sqlQuery = stmt;
				sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
				int res=sqlite3_step(selectStmt);
				sqlite3_finalize(selectStmt);
				cout<<"Lock Status has been updated"<<endl;
				break;
			}
			else
			{
				cout<<"Invalid choice"<<endl;
			}
		}while(1);
	}
	else
	{
		cout<<"Password error"<<endl;
	}
}
void mFunction::edit_qna(string user)
{
	int check;
	if(login_pos=="ADMN")
	{
		check=admn_verify(login_username);
	}
	else
	{
		check=1;
	}
	if(check==1)
	{
		do
		{
			string qn, ans;
			cout<<"New Security Question :";
			cin.clear();
			cin.ignore(100,'\n');
			getline(cin,qn,'\n');
			cout<<"New Answer :";
			cin.clear();
			cin.ignore(100,'\n');
			getline(cin,ans,'\n');
			string updateQna;
			char stmt[1000];
			updateQna = "UPDATE USER SET question = '"+qn+"', answer ='"+ans+"' WHERE username = '"+user+"';";
			strcpy(stmt, updateQna.c_str());	
			sqlQuery = stmt;
			sqlite3_prepare(db, sqlQuery, -1, &selectStmt, 0);
			int res=sqlite3_step(selectStmt);
			sqlite3_finalize(selectStmt);
			cout<<"Security Question and Answer has been updated"<<endl;
			break;
		}while(1);
	}
	else
	{
		cout<<"Password error"<<endl;
	}
}
////////////////////////////////////////////EDIT ACCOUNT CODE END/////////////////////////////////////
int mFunction::admn_verify(string user)
{
	do
	{
		string password;
		cout<<"Please enter your password:";
		cin>>password;
		string selectstmt, s;
		char stmt[1000];
		selectstmt = "SELECT COUNT(*) FROM USER WHERE username = '"+user+"' AND password = '"+password+"';";
		strcpy(stmt, selectstmt.c_str());	
		sqlQuery = stmt;
		s = sql_output(sqlQuery);
		if(s=="1")
		{
			return 1;
			break;
		}
		else
		{
			return 0;
			break;
		}
	}while(1);
}
