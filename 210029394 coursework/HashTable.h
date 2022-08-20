#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <any>
using namespace std;

struct str_hash
{
	size_t operator()(int key) const
	{
		int step = 0;
		if (key == 1)
		{
			step = 0;
		}
		while (key != 1)
		{
			if (key % 2 == 0)
			{
				key = key / 2;
				step++;
			}
			else
			{
				key = key * 3 + 1;
				step++;
			}
		}
		return step;
	}
};

class HashTable
{
public:
	HashTable();
	void printHashTable();
	char Decryption_by_HashTable(int Encrypted_Integer,int &offset);
	void Decryption_to_the_string();
	~HashTable();
	unordered_map<int, int, str_hash> *m_HashTable;
	vector<int> HashTable_Decrypted_Password;
};
