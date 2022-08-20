#include "User.h"


User::User()
{

}

void User::Encryption()
{
	int offset = 0;
	int record = 0;
	for (int i = 0; i < m_password.size(); i++)
	{
		int step = 0;
		int record_ASCII = 0;
		//we must use a integer to store the ascii of character,otherwise the algorithsm will be wrong
		if ((int)m_password[i] > 0)
		{
            record_ASCII = (int)m_password[i];
		}
		else if ((int)m_password[i] < 0)
		{
			record_ASCII = (int)m_password[i] + 256;
		}

		record = record_ASCII + offset;

		if (record == 1)
		{
			step = 0;
		}
		while (record != 1)
		{
			if (record % 2 == 0)
			{
				record= record / 2;
				step++;
			}
			else
			{
				record = record * 3 + 1;
				step++;
			}
		}
		m_encrypted_password.push_back(step);
		offset = step;
	}
}

void User::Register(const string& username, const vector<char>& password)
{
	this->m_username = username;
	this->m_password = password;
	Encryption();
	fstream ofs;
	ofs.open("password.txt", ios::app);
	ofs << this->m_username << " ";
	for (auto it = m_encrypted_password.begin(); it != m_encrypted_password.end(); it++)
	{
		ofs << *it;
	}
	ofs << endl;
	ofs.close();
}

int User::Authenticating(const string& username, const vector<char>& password)
{
	this->m_username = username;
	this->m_password = password;
	Encryption();
	stringstream encrypted_password_stream;
	string encrypted_password;
	copy(m_encrypted_password.begin(), m_encrypted_password.end(), ostream_iterator<int>(encrypted_password_stream, ""));
	encrypted_password = encrypted_password_stream.str();
	string username_password = this->m_username + " " + encrypted_password;
	fstream ifs;

	//to catch an error of missing file
	try {
		ifs.open("password.txt", ios::in);
		if (!ifs.is_open())
		{
			throw "FILE IS MISSING!";
		}
	}catch (const char* msg)
	{
		cerr << msg << endl;
		return 3;
	}

	//count the number of lines
	char count;
	int LineCnt = 0;
	while (ifs.get(count))
	{
		if (count == '\n')
		{
			LineCnt++;
		}
	}

	ifs.close();

	//open again to regain the file
	ifs.open("password.txt", ios::in);
	int count_try = 0;
	string username_password_saved;
	for (int i = 0; i < LineCnt; i++)
	{
		getline(ifs, username_password_saved);
		if (username_password == username_password_saved)
		{
			return 1;
		}
		else
		{
			count_try++;
		}
	}
	if (count_try == LineCnt)
	{
		return 2;
	}
}

User::~User()
{

}