#include "HashTable.h"

HashTable::HashTable()
{
	unique_ptr<unordered_map<int, int, str_hash>> _HashTable(new unordered_map<int,int,str_hash>);
	m_HashTable = _HashTable.get();
	for (int i = 2; i < 398; i++)
	{
		m_HashTable->insert(pair<int, int>(i, i));
	}
	m_HashTable = _HashTable.release();
	_HashTable.reset();
}

void HashTable::printHashTable()
{
	for (auto it = m_HashTable->begin(); it != m_HashTable->end(); it++)
	{
		cout << "bucket is " << m_HashTable->bucket(it->first) << endl;
		cout << it->first << " " << it->second << endl;
	}
}

char HashTable::Decryption_by_HashTable(int Encrypted_Integer,int &offset)
{
	for (auto it = m_HashTable->begin(); it != m_HashTable->end(); it++)
	{
		if (m_HashTable->bucket(it->first) == Encrypted_Integer)
		{
			HashTable_Decrypted_Password.push_back(it->first);
		}
	}

	vector<int> tempt = HashTable_Decrypted_Password;
	HashTable_Decrypted_Password.clear();

	for (auto it = tempt.begin(); it != tempt.end(); it++)
	{
		if (*it - offset > 1 && *it - offset < 256)
		{
			return (char)(*it - offset);
			break;
		}
	}

}

void HashTable::Decryption_to_the_string()
{
	vector<int> answer = { 27,32,28,103,13,33,103,39,102,114,52,9,12,20,7,34,41,36,14,69,25,46,10,33,28,15,33,27,103,101,28,15,108,114,101 };
	for (auto itself = answer.begin(); itself != answer.end(); itself++)
	{
		for (auto it = m_HashTable->begin(); it != m_HashTable->end(); it++)
		{
			if (m_HashTable->bucket(it->first) == *itself)
			{
				if (itself == answer.begin())
				{
					HashTable_Decrypted_Password.push_back(it->first);
				}
				else
				{
					HashTable_Decrypted_Password.push_back(it->first - *(itself-1));
				}
			}
		}
		cout << *itself << " : ";
		for (auto it2 = HashTable_Decrypted_Password.begin(); it2 != HashTable_Decrypted_Password.end(); it2++)
		{
			cout << (char)*it2 << " ";
		}
		cout << endl;

		HashTable_Decrypted_Password.clear();
	}


}

HashTable::~HashTable()
{
	if (m_HashTable != NULL)
	{
		delete m_HashTable;
		m_HashTable = NULL;
	}
}
