#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <any>
#include "User.h"
using namespace std;

//execute login or register according to user's choice
void Login_Or_Register(string choice_made_by_users)
{
	if (choice_made_by_users == "1")
	{
		int x = 0;
		cout << "-------------------LOGIN YOUR ACCOUNT----------------------" << endl;
		for (x = 0; x < 3; x++)
		{
			cout << "PLEASE ENTER YOUR USERNAME:" << endl;
			string username;
			cin >> username;
			cin.get();
			cout << "PLEASE ENTER YOUR PASSWORD:" << endl;
			string password1;
			getline(cin, password1);
			vector<char> password;
			for (int i = 0; i < password1.size(); i++)
			{
				password.push_back(password1[i]);
			}
			User u1;
			int result = u1.Authenticating(username, password);
			if (result == 1)
			{
				cout << "------------------------SUCCESS!---------------------------" << endl;
				break;
			}
			else if(result == 2)
			{
				cout << "-----------------------FAILURE!----------------------------" << endl;
				cout << "----------------YOU HAVE " << 2-x << " TIMES TO TRY--------------------" << endl;
			}
			else if(result == 3)
			{
				cout << "-------------PLEASE REGISTER AN ACCOUNT FIRST!--------------" << endl;
				Login_Or_Register("2");
				break;
			}
		}
		if (x == 3)
		{
			cout << "-------------SORRY,YOU HAVE USED ALL TRIES------------------" << endl;
			cout << "-------------IF YOU DONOT HAVE AN ACCOUNT-------------------" << endl;
			cout << "-------------PLEASE REGISTER AN ACCOUNT FIRST!--------------" << endl;
			cout << "-------------PRESS 1 TO REGISTER,PRESS 2 TO EXIT------------" << endl;
			string choice2;
			cin >> choice2;
			if (choice2 == "1")
			{
				Login_Or_Register("2");
			}
			else if (choice2 == "2")
			{
				return;
			}
		}
	}
	else if (choice_made_by_users == "2")
	{
		cout << "----------------REGISTER YOUR ACCOUNT----------------------" << endl;
		cout << "PLEASE ENTER YOUR USERNAME:" << endl;
		string username;
		cin >> username;
		cin.get();
		cout << "PLEASE ENTER YOUR PASSWORD:" << endl;
		string password1;
		getline(cin, password1);
		vector<char> password;
		for (int i = 0; i < password1.size(); i++)
		{
			password.push_back(password1[i]);
		}
		User u1;
		u1.Register(username, password);
		cout << "-------------------REGISTER SUCEESS------------------------" << endl;
	}
}

template<class T>
void passwordtest(T** s1)
{
	cout << "---------INPUT THE EXECUTING TIME YOU WANT THE FUNCTION TO USE----------" << endl;
	clock_t Time;
	cin >> Time;
	if ((*s1)->Authenticating(Time) == false)
	{
		cout << "A PASSWORD LIST IS BEING CREATED,PLEASE WAIT..." << endl;
		(*s1)->Register();
		cout << "-------------------CREATING PASSWORD SUCEESS----------------------------" << endl;
		passwordtest(s1);
	}
	else
	{
		cout << "-------------------CRACKING PASSWORD SUCEESS----------------------------" << endl;
	}
}

bool menu()
{
	//choose to use which function
	string choice_made_by_users = "0";
	while (choice_made_by_users != "1" && choice_made_by_users != "2" && choice_made_by_users != "3" && choice_made_by_users != "4" && choice_made_by_users != "5")
	{
		cin >> choice_made_by_users;
		if (choice_made_by_users == "1" || choice_made_by_users == "2")
		{
			Login_Or_Register(choice_made_by_users);
			cout << "-----------------------------------------------------------" << endl;
			cout << "------------YOU CAN USE OTHER FUNCTIONS------------------" << endl;
			return true;
		}
		else if (choice_made_by_users == "3")
		{
			StrengthTest* s1 = new StrengthTest();
			passwordtest(&s1);
			cout << "-----------------------------------------------------------" << endl;
			cout << "------------YOU CAN USE OTHER FUNCTIONS------------------" << endl;
			cout << "PRESS 4:SHOW PERCENTAGE OF SUCCESSFULLY DECRYPTED PASSWORD" << endl;
			cout << "PRESS 5:SHOW THE TIME USED TO DECRYPT PASSWORD" << endl;
			cout << "PRESS 6:QUIT THE PASSWORD TEST FUNCTION" << endl;
			cout << "-----------------------------------------------------------" << endl;

			string choic3 = "0";
			cin >> choic3;
			while (choic3 != "")
			{
				if (choic3 == "4")
				{
					s1->Percentage();
					cout << "-----------------------------------------------------------" << endl;
					cout << "------------YOU CAN USE OTHER FUNCTIONS------------------" << endl;
					cin >> choic3;
				}
				else if (choic3 == "5")
				{
					s1->Time();
					cout << "-----------------------------------------------------------" << endl;
					cout << "------------YOU CAN USE OTHER FUNCTIONS------------------" << endl;
					cin >> choic3;
				}
				else if (choic3 == "6")
				{
					delete s1;
					s1 = NULL;
					cout << "--------------------WELCOME!-------------------------------" << endl;
					cout << "PRESS 1:LOGIN IN A CREATED ACCOUNT" << endl;
					cout << "PRESS 2:CREATE AN ACCOUNT" << endl;
					cout << "PRESS 3:PASSWORD STRENGTH TEST" << endl;
					cout << "PRESS 4:ENTER AN INTEGER STRING TO DECRYPT IT" << endl;
					cout << "PRESS 5:EXIT" << endl;
					cout << "-----------------------------------------------------------" << endl;
					return true;
				}
				else
				{
					cout << "THE NUMBER YOU ENTERED IS ILLEGAL,PLEASE ENTER 4 OR 5 OR 6!" << endl;
				}
			}
			return true;
		}
		else if (choice_made_by_users == "4")
		{
			/*string decrypted_password_selected_by_users;*/
			//cout << "PLEASE ENTER AN INTEGER STRING WHICH YOU WANT TO DECRYPT : " << endl;
			//cin >> decrypted_password_selected_by_users;
			/*decryption d(decrypted_password_selected_by_users);*/
			//d.Decryption(decrypted_password_selected_by_users);
			//cout << "THE DECRYPTED PASSWORD IS :";
			//for (auto it = d.m_decrypted_password.begin(); it != d.m_decrypted_password.end(); it++)
			//{
			//	cout << *it;
			//}
			//cout << endl;

			HashTable h;
			h.Decryption_to_the_string();
			cout << "-----------------------------------------------------------" << endl;
			cout << "------------YOU CAN USE OTHER FUNCTIONS------------------" << endl;
			return true;
		}
		else if (choice_made_by_users == "5")
		{
			cout << "---------------------EXIT!-------------------------------" << endl;
			return false;
		}
		else
		{
			cout << "PLEASE ENTER 1,2,3,4 OR 5!" << endl;
		}
	}
}


int main()
{
	//menu
	cout << "--------------------WELCOME!-------------------------------" << endl;
	cout << "PRESS 1:LOGIN IN A CREATED ACCOUNT" << endl;
	cout << "PRESS 2:CREATE AN ACCOUNT" << endl;
	cout << "PRESS 3:PASSWORD STRENGTH TEST" << endl;
	cout << "PRESS 4:ENTER AN INTEGER STRING TO DECRYPT IT" << endl;
	cout << "PRESS 5:EXIT" << endl;
	cout << "-----------------------------------------------------------" << endl;


	bool (*pf)();
	pf = menu;

	while (pf() == true)
	{
		pf();
	}


	return 0;
}