#include "User.h"


StrengthTest::StrengthTest()
{
	m_Test_HashTable = new HashTable();
}

//generate 20000 passwords
void StrengthTest::Register()
{
	//must be put out of loop
	srand(time(0));
	//1-10000£ºget 10 numbers randomly which will be the ASCII of characters in the first 10000 password
	int ASCII_value1[10];
	for (int x = 0; x < 10; x++)
	{
		ASCII_value1[x] = rand() % (122 - 97 + 1) + 97;
	}
	//10000-20000
	vector<int> ASCII_value2;
	for (int y = 2; y < 256; y++)
	{
		ASCII_value2.push_back(y);
	}
	//creating passwords
	for (int k = 0; k < 20000; k++)
	{
		if (k < 10000)
		{
			for (int j = 0; j < (k / 100) + 1; j++)
			{
				//get a subscript of the ASCII array
				int subscript = rand() % 10;
				m_password.push_back((char)ASCII_value1[subscript]);
			}


			//password encrypted
			Encryption();

			//write the encrypted password into txt
			fstream ofs;
			ofs.open("passwordtest.txt", ios::app);
			for (auto it = m_encrypted_password.begin(); it != m_encrypted_password.end(); it++)
			{
				ofs << *it;
			}
			ofs << endl;
			ofs.close();

			//clear the password and encrypted password
			m_encrypted_password.clear();
			m_password.clear();
		}
		else
		{
			vector<int> ASCII_value3 = ASCII_value2;
			//fullfill the password
			for (int j = 0; j < (k - 10000) / 100 + 1; j++)
			{
				//get the ASCII
				auto it = ASCII_value3.begin()+rand()%ASCII_value3.size();
				//put the character with ASCII in the password
				m_password.push_back((char)*it);
				//delete the ASCII
				ASCII_value3.erase(it);
			}

			//Encrypted
			Encryption();

			//write the encrypted password into txt
			fstream ofs;
			ofs.open("passwordtest.txt", ios::app);
			for (auto it = m_encrypted_password.begin(); it != m_encrypted_password.end(); it++)
			{
				ofs << *it;
			}
			ofs << endl;
			ofs.close();

			//clear the password and encrypted password
			m_encrypted_password.clear();
			m_password.clear();
		}
	}
}


//decryption
bool StrengthTest::Authenticating(clock_t &Time)
{
	fstream ifs;
	ifs.open("passwordtest.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "FAIL TO OPERN FILE!" << endl;
		return false;
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

	//open the file again
	ifs.open("passwordtest.txt", ios::in);
	stringstream test_password_stream;
	string test_password_string;
	int test_password;
	vector<char> decrypted_password;
	int start_sign = 0;
	clock_t endtime = Time*1000;
	cout << "-------------------CRACKING PASSWORD ...----------------------------" << endl;
	fstream ofs;
	clock_t start, end ;
	start = clock();
	TIME.push_back(start);
	end = clock();
	
	for (int i = 0; i < 20000; i++)
	{
		if(end -start <= endtime)
		{
			getline(ifs, test_password_string);
		    test_password_stream << test_password_string;
			test_password_stream >> test_password;

			////decryption
			////first part:1-100
			if (i < 100)
			{
				cout << m_Test_HashTable->Decryption_by_HashTable(test_password, start_sign) << endl;
				m_password.push_back(m_Test_HashTable->Decryption_by_HashTable(test_password, start_sign));
				Encryption();
				ofs.open("decrypted password.txt", ios::app);
				for (auto it = m_encrypted_password.begin(); it != m_encrypted_password.end(); it++)
				{
					ofs << *it;
				}
				ofs << endl;
				ofs.close();
				m_password.clear();
				m_encrypted_password.clear();
			}

			/////*second part:101-10000*/
			else if (i < 10000)
			{
				decrypted_password.clear();
				decryption d1(test_password_string);
				d1.Decryption(test_password_string);
				m_password = d1.m_decrypted_password;
				Encryption();
				ofs.open("decrypted password.txt", ios::app);
				for (auto it = d1.m_decrypted_password.begin(); it != d1.m_decrypted_password.end(); it++)
				{
					cout << *it;
				}
				cout << endl;

				for (auto it = m_encrypted_password.begin(); it != m_encrypted_password.end(); it++)
				{
					ofs << *it;
				}
				ofs << endl;
				ofs.close();
				m_password.clear();
				m_encrypted_password.clear();
			}

			////third part:10001-10100
			if (i >= 10000 && i < 10100)
			{
				cout << m_Test_HashTable->Decryption_by_HashTable(test_password, start_sign) << endl;
				m_password.push_back(m_Test_HashTable->Decryption_by_HashTable(test_password, start_sign));
				Encryption();
				ofs.open("decrypted password.txt", ios::app);
				for (auto it = m_encrypted_password.begin(); it != m_encrypted_password.end(); it++)
				{
					ofs << *it;
				}
				ofs << endl;
				ofs.close();
				m_password.clear();
				m_encrypted_password.clear();
			}

			////forth part:10100-17800
			else if (i >= 10100 && i < 20000)
			{
				decrypted_password.clear();
				decryption d1(test_password_string);
				d1.Decryption(test_password_string);
				m_password = d1.m_decrypted_password;
				Encryption();
				ofs.open("decrypted password.txt", ios::app);
				for (auto it = d1.m_decrypted_password.begin(); it != d1.m_decrypted_password.end(); it++)
				{
					cout << *it;
				}
				cout << endl;

				for (auto it = m_encrypted_password.begin(); it != m_encrypted_password.end(); it++)
				{
					ofs << *it;
				}
				ofs << endl;
				ofs.close();
				m_password.clear();
				m_encrypted_password.clear();
			}

			if ((i + 1) % 100 == 0)
			{
				end = clock();
				TIME.push_back(end);
			}

			test_password_stream.clear();
		}

	}
	cout << "-----------------------------------------------------------" << endl;
	ifs.close();
	return true;
}


//show percentage
void StrengthTest::Percentage()
{
	fstream ifs1;
	ifs1.open("decrypted password.txt", ios::in);
	if (!ifs1.is_open())
	{
		cout << "FAIL TO OPERN FILE!" << endl;
		return;
	}
    string decrypted_by_decryption_function_string;

	fstream ifs2;
	ifs2.open("passwordtest.txt", ios::in);
	if (!ifs2.is_open())
	{
		cout << "FAIL TO OPERN FILE!" << endl;
		return;
	}
	string passwordtest_string;


	vector<double> Number_of_same_characters_vector;

	double Number_of_same_characters = 0;

	for (int i = 0; i < 20000; i++)
	{
		getline(ifs1, decrypted_by_decryption_function_string);
		getline(ifs2, passwordtest_string);

		int len = 0;
		if (decrypted_by_decryption_function_string.size() >= passwordtest_string.size())
		{
			len = passwordtest_string.size();
		}
		else
		{
			len = decrypted_by_decryption_function_string.size();
		}

		for (int j = 0; j < len; j++)
		{
			if (decrypted_by_decryption_function_string[j] == passwordtest_string[j] )
			{
				Number_of_same_characters++;
			}
		}
		Number_of_same_characters_vector.push_back(Number_of_same_characters / passwordtest_string.size());
		Number_of_same_characters = 0;
	}

	double sum_of_all = 0;
	for (int i = 0; i < Number_of_same_characters_vector.size(); i++)
	{
		sum_of_all = sum_of_all + Number_of_same_characters_vector[i];
		if ((i + 1) % 100 == 0)
		{
			cout << i + 1 - 99 << " - " << i + 1 << " percentage of passwords being discoverd : " << (sum_of_all / 100) * 100 << " % " << endl;
			sum_of_all = 0;
		}
	}
}


//show time
void StrengthTest::Time()
{
	auto it = TIME.begin();
	cout << "1 - 100" << " average time used to decrypt is : " << (double)(((*(it+1))-(*it))/100) << " ms "<< endl;
	for (int i = 2; i < TIME.size(); i++)
	{
		cout << (i - 1) * 100 + 1 << " - " << i * 100 << "average time used to decrypt is : " << (double)((TIME[i] - TIME[i - 1])/100) << " ms " << endl;
	}
}



StrengthTest::~StrengthTest()
{
	if (m_Test_HashTable != NULL)
	{
		delete m_Test_HashTable;
		m_Test_HashTable = NULL;
	}
}