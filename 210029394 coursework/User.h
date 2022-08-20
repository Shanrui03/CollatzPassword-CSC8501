#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <any>
#include "decryption.h"
using namespace std;

class User
{
public:
	User();
	void Encryption();
	virtual void Register(const string& name, const vector<char>& password);
	virtual int Authenticating(const string& username,const vector<char>& password);
	~User();
protected:
	vector<char> m_password;
	vector<int> m_encrypted_password;
private:
	string m_username;
};

class StrengthTest : public User
{
public:
	StrengthTest();
	virtual void Register();
	virtual bool Authenticating(clock_t &Time);
	void Percentage();
	void Time();
	~StrengthTest();
    HashTable* m_Test_HashTable;
	vector<clock_t> TIME;
}; 