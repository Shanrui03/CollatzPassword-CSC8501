#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <any>
#include "HashTable.h"
using namespace std;

class decryption
{
public:
	decryption(const string& Encrypted_password);
	void Decryption(string& function_used_Encrypted_password);

	//save the final answer
	vector<char> m_decrypted_password;

	//save the encrypted integer of last step
	vector<int> m_encrypted_password_integer;

	//save the encrypted password which the decryption function is using now
	vector<string> function_used_Encrypted_password_string;

	//count the number of characters in the final password
	int password_number = 0;

	//hash table
	HashTable m_decryption_HashTable;

	//change string to integer
	stringstream trans_stream;

	//save the original encrypted password
	string *m_Encrypted_password;




	~decryption();
};
