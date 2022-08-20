#include "decryption.h"


decryption::decryption(const string& Encrypted_password)
{
	m_Encrypted_password = new string(Encrypted_password);
	function_used_Encrypted_password_string.push_back(*m_Encrypted_password);
	m_encrypted_password_integer.push_back(0);
}

void decryption::Decryption(string & function_used_Encrypted_password)
{
	//clear the transstream
	trans_stream.clear();
	//take the first 3 characters of the string as the encrypted password of the first character
	string first_3_characters_string = function_used_Encrypted_password.substr(0, 3);
	int first_3_characters_integer;
	trans_stream << first_3_characters_string;
	trans_stream >> first_3_characters_integer;

	//first character's step
	if (password_number == 0)
	{
		if (first_3_characters_integer > 0 && first_3_characters_integer < 128 && (*first_3_characters_string.begin()) != '0' && m_decryption_HashTable.Decryption_by_HashTable(first_3_characters_integer,m_encrypted_password_integer[password_number]))
		{
			//record the offset
			m_encrypted_password_integer.push_back(first_3_characters_integer);

			//record the decrypted character
			m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_3_characters_integer, m_encrypted_password_integer[password_number]));

			//record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
			password_number++;

			//create a new string which should be used as the next
			string next = m_Encrypted_password->erase(0, 3);

			//if the next string is not empty,recursive method
			if (next != "")
			{
				function_used_Encrypted_password_string.push_back(next);
				Decryption(next);
			}
			else
			{
				return;
			}
		}

		else
		{
			//clear the stringstream
			trans_stream.clear();

			//take first two characters as the step
			string first_2_characters_string = function_used_Encrypted_password.substr(0, 2);
			int first_2_characters_integer;
			trans_stream << first_2_characters_string;
			trans_stream >> first_2_characters_integer;

			if ((*first_2_characters_string.begin()) != '0' && m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]))
			{
				//record the offset
				m_encrypted_password_integer.push_back(first_2_characters_integer);

				//record the decrypted character
				m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]));

				//record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
				password_number++;

				//create a new string which should be used as the next
				string next = m_Encrypted_password->erase(0, 2);

				//if the next string is not empty,recursive method
				if (next != "")
				{
					function_used_Encrypted_password_string.push_back(next);
					Decryption(next);
				}
				else
				{
					return;
				}
			}

			else
			{
				//clear the stringstream
				trans_stream.clear();

				//take first characters as the step
				string first_1_characters_string = function_used_Encrypted_password.substr(0, 1);
				int first_1_characters_integer;
				trans_stream << first_1_characters_string;
				trans_stream >> first_1_characters_integer;

				if (first_1_characters_string != "0" && m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]))
				{
					//record the offset
					m_encrypted_password_integer.push_back(first_1_characters_integer);

					//record the decrypted character
					m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]));

					//record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
					password_number++;

					//create a new string which should be used as the next
					string next = m_Encrypted_password->erase(0, 1);

					//if the next string is not empty,recursive method
					if (next != "")
					{
						function_used_Encrypted_password_string.push_back(next);
						Decryption(next);
					}
					else
					{
						return;
					}
				}
			}

		}
	}

	//other characters
	else
	{
	    if (first_3_characters_integer > 1 && first_3_characters_integer < 144 && (*first_3_characters_string.begin()) != '0' && m_decryption_HashTable.Decryption_by_HashTable(first_3_characters_integer, m_encrypted_password_integer[password_number]))
	    {
			//record the offset
			m_encrypted_password_integer.push_back(first_3_characters_integer);

			//record the decrypted character
			m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_3_characters_integer, m_encrypted_password_integer[password_number]));

			//record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
			password_number++;

			//create a new string which should be used as the next
			string next = m_Encrypted_password->erase(0, 3);

			//if the next string is not empty,recursive method
			if (next != "")
			{
				function_used_Encrypted_password_string.push_back(next);
				Decryption(next);
			}
			else
			{
				return;
			}
	    }
		
		else
		{
			//-----------------------first number is 0---------------------------
			if ((*first_3_characters_string.begin()) == '0')
			{
				//clear the stringstream
				trans_stream.clear();

				//take first two characters as the step
				string first_2_characters_string = function_used_Encrypted_password_string[password_number - 1].substr(0, 2);
				int first_2_characters_integer;
				trans_stream << first_2_characters_string;
				trans_stream >> first_2_characters_integer;


				if (m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]))
				{
					//popback last wrong number
					m_encrypted_password_integer.erase(m_encrypted_password_integer.begin() + password_number);

					//erase last wrong number in the final answer
					m_decrypted_password.erase(m_decrypted_password.begin() + password_number-1);

					//erase last wrong function used string
					function_used_Encrypted_password_string.erase(function_used_Encrypted_password_string.begin() + password_number);

					//password_number - 1
					password_number--;

					//record the offset
					m_encrypted_password_integer.push_back(first_2_characters_integer);

					//record the decrypted character
					m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]));

					//record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
					password_number++;

					//create a new string which should be used as the next
					string next = m_Encrypted_password->erase(0, 2);

					//if the next string is not empty,recursive method
					if (next != "")
					{
						function_used_Encrypted_password_string.push_back(next);
						Decryption(next);
					}
					else
					{
						return;
					}
				}

				//the 2 number has some problems
				else
				{
					//clear the stringstream
					trans_stream.clear();

					//take first two characters as the step
					string first_1_characters_string = function_used_Encrypted_password_string[password_number - 1].substr(0, 2);
					int first_1_characters_integer;
					trans_stream << first_1_characters_string;
					trans_stream >> first_1_characters_integer;

					if (m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]))
					{
						//popback last wrong number
						m_encrypted_password_integer.erase(m_encrypted_password_integer.begin() + password_number);

						//erase last wrong number in the final answer
						m_decrypted_password.erase(m_decrypted_password.begin() + password_number-1);

						//erase last wrong function used string
						function_used_Encrypted_password_string.erase(function_used_Encrypted_password_string.begin() + password_number);

						//password_number - 1
						password_number--;

						//record the offset
						m_encrypted_password_integer.push_back(first_1_characters_integer);

						//record the decrypted character
						m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]));

						//record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
						password_number++;

						//create a new string which should be used as the next
						string next = m_Encrypted_password->erase(0, 1);

						//if the next string is not empty,recursive method
						if (next != "")
						{
							function_used_Encrypted_password_string.push_back(next);
							Decryption(next);
						}
						else
						{
							return;
						}
					}
				}
			}

			//----------------------------------if the number slected is over 144--------------------------------
			else if (first_3_characters_integer >= 144 || !m_decryption_HashTable.Decryption_by_HashTable(first_3_characters_integer, m_encrypted_password_integer[password_number]))
			{
			    //clear the stringstream
			    trans_stream.clear();

			    //take first two characters as the step
			    string first_2_characters_string = function_used_Encrypted_password.substr(0, 2);
			    int first_2_characters_integer;
			    trans_stream << first_2_characters_string;
			    trans_stream >> first_2_characters_integer;

			    if ((*first_2_characters_string.begin()) != '0' && m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]))
			    {
				    //record the offset
				     m_encrypted_password_integer.push_back(first_2_characters_integer);

				    //record the decrypted character
				    m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]));
 
				    //record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
				     password_number++;

				    //create a new string which should be used as the next
				    string next = m_Encrypted_password->erase(0, 2);

				    //if the next string is not empty,recursive method
				    if (next != "")
				    {
					    function_used_Encrypted_password_string.push_back(next);
					    Decryption(next);
				    }
				    else
				    {
					    return;
				    }
			    }

			    else
			    {
				     //clear the stringstream
				     trans_stream.clear();

				     //take first characters as the step
				     string first_1_characters_string = function_used_Encrypted_password.substr(0, 1);
				     int first_1_characters_integer;
				     trans_stream << first_1_characters_string;
				     trans_stream >> first_1_characters_integer;

				     if (first_1_characters_string != "0" && m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]))
				     {
					       //record the offset
					        m_encrypted_password_integer.push_back(first_1_characters_integer);

					        //record the decrypted character
					        m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]));

					        //record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
					        password_number++;

					         //create a new string which should be used as the next
					         string next = m_Encrypted_password->erase(0, 1);

					        //if the next string is not empty,recursive method
					         if (next != "")
					        {
						          function_used_Encrypted_password_string.push_back(next);
						          Decryption(next);
					         }
					        else
					         {
						          return;
					         }
				     }

					 //if 1-digit,2-digit,3-digit are both wrong
					 else
					 {
						 //clear the stream
						 trans_stream.clear();

						 //search the first 3-digit number's subscript
						 int first_3_characters_subscript=0;
						 for (int i = 0;i<m_encrypted_password_integer.size();i++)
						 {
							 if (m_encrypted_password_integer[i] >= 100)
							 {
								 first_3_characters_subscript = i;
								 break;
							 }
						 }

						 //to see if there are 3-digit numbers in the vector
						 if (first_3_characters_subscript != 0)
						 {
							 //reset the first_2_characters_string
							 first_2_characters_string = function_used_Encrypted_password_string[first_3_characters_subscript - 1].substr(0, 2);
							 trans_stream << first_2_characters_string;
							 trans_stream >> first_2_characters_integer;

							 if ((*first_2_characters_string.begin()) != '0' && m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]))
							 {  
								 //erase the wrong number in the vector<int>
								 m_encrypted_password_integer.erase(m_encrypted_password_integer.begin() + first_3_characters_subscript, m_encrypted_password_integer.end());

								 //erase the wrong string in the vector<string>
								 function_used_Encrypted_password_string.erase(function_used_Encrypted_password_string.begin() + first_3_characters_subscript, function_used_Encrypted_password_string.end());

								 //erase the wrong char in the vector<char>
								 m_decrypted_password.erase(m_decrypted_password.begin() + first_3_characters_subscript - 1, m_decrypted_password.end());

								 //delete the wrong password_number
								 password_number = first_3_characters_subscript - 1;

								 //record the offset
								 m_encrypted_password_integer.push_back(first_2_characters_integer);

								 //record the decrypted character
								 m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_2_characters_integer, m_encrypted_password_integer[password_number]));

								 //record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
								 password_number++;

								 //create a new string which should be used as the next
								 string next = m_Encrypted_password->erase(0, 2);

								 //if the next string is not empty,recursive method
								 if (next != "")
								 {
									 function_used_Encrypted_password_string.push_back(next);
									 Decryption(next);
								 }
								 else
								 {
									 return;
								 }
							 }
							 else
							 {
								 //reset the first_1_characters_string
								 first_1_characters_string = function_used_Encrypted_password_string[first_3_characters_subscript - 1].substr(0, 1);
								 trans_stream << first_1_characters_string;
								 trans_stream >> first_1_characters_integer;

								 if ((*first_1_characters_string.begin()) != '0' && m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]))
								 {
									 //erase the wrong number in the vector<int>
									 m_encrypted_password_integer.erase(m_encrypted_password_integer.begin() + first_3_characters_subscript, m_encrypted_password_integer.end());

									 //erase the wrong string in the vector<string>
									 function_used_Encrypted_password_string.erase(function_used_Encrypted_password_string.begin() + first_3_characters_subscript, function_used_Encrypted_password_string.end());

									 //erase the wrong char in the vector<char>
									 m_decrypted_password.erase(m_decrypted_password.begin() + first_3_characters_subscript - 1, m_decrypted_password.end());

									 //delete the wrong password_number
									 password_number = first_3_characters_subscript - 1;

									 //record the offset
									 m_encrypted_password_integer.push_back(first_1_characters_integer);

									 //record the decrypted character
									 m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]));

									 //record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
									 password_number++;

									 //create a new string which should be used as the next
									 string next = m_Encrypted_password->erase(0, 1);

									 //if the next string is not empty,recursive method
									 if (next != "")
									 {
										 function_used_Encrypted_password_string.push_back(next);
										 Decryption(next);
									 }
									 else
									 {
										 return;
									 }
								 }
							 }
						 }

						 //if there are no 3-digit numbers in the vector<int>
						 else if(first_3_characters_subscript == 0)
						 {
							 //clear the stream
							 trans_stream.clear();

							 //search the first 2-digit number's subscript
							 int first_2_characters_subscript = 0;
							 for (int i = 0; i < m_encrypted_password_integer.size(); i++)
							 {
								 if (m_encrypted_password_integer[i] >= 10)
								 {
									 first_2_characters_subscript = i;
									 break;
								 }
							 }

							 //reset the first_1_characters_string
							 first_1_characters_string = function_used_Encrypted_password_string[first_2_characters_subscript - 1].substr(0, 2);
							 trans_stream << first_1_characters_string;
							 trans_stream >> first_1_characters_integer;

							 if ((*first_1_characters_string.begin()) != '0' && m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]))
							 {
								 //erase the wrong number in the vector<int>
								 m_encrypted_password_integer.erase(m_encrypted_password_integer.begin() + first_2_characters_subscript, m_encrypted_password_integer.end());

								 //erase the wrong string in the vector<string>
								 function_used_Encrypted_password_string.erase(function_used_Encrypted_password_string.begin() + first_2_characters_subscript, function_used_Encrypted_password_string.end());

								 //erase the wrong char in the vector<char>
								 m_decrypted_password.erase(m_decrypted_password.begin() + first_2_characters_subscript - 1, m_decrypted_password.end());

								 //delete the wrong password_number
								 password_number = first_2_characters_subscript - 1;

								 //record the offset
								 m_encrypted_password_integer.push_back(first_1_characters_integer);

								 //record the decrypted character
								 m_decrypted_password.push_back(m_decryption_HashTable.Decryption_by_HashTable(first_1_characters_integer, m_encrypted_password_integer[password_number]));

								 //record the total number of the characters in the final answer(also the subscript of the last element in the offset vector)
								 password_number++;

								 //create a new string which should be used as the next
								 string next = m_Encrypted_password->erase(0, 1);

								 //if the next string is not empty,recursive method
								 if (next != "")
								 {
									 function_used_Encrypted_password_string.push_back(next);
									 Decryption(next);
								 }
								 else
								 {
									 return;
								 }
							 }

						 }
					 }
			    }
            }
			
			         
			
		}
	 
    }

 


}


decryption::~decryption()
{
	if (m_Encrypted_password != NULL)
	{
		delete m_Encrypted_password;
		m_Encrypted_password = NULL;
	}
}