#include <iostream>
#include <string>
#include <stdlib.h> 

#include "Encryption.h"
#include "FileManagerZ.h"

void HandleDisplayMessage(const std::string& filename, bool isEncrypting, bool isSuccessful);

int main()
{

	std::string filename;
	std::string key;
	bool Encrypt = false;
	std::vector<std::string> blackListedFolders{"Windows","C:","System32"};

	while (true)
	{
		Encryption enObject = Encryption();

		FileManagerZ filemanager(blackListedFolders);

		std::cout << "Encrypt: (1) Decrypt: (2) Exit: (3)" << std::endl;
		int value;
		std::cin >> value;

		if (value == 1) { Encrypt = true; }
		else if (value == 2) { Encrypt = false; }
		else { break; }

		std::cout << "Enter the filename or folder." << std::endl;
		std::getline(std::cin >> std::ws, filename);
		std::cout << std::endl;

		std::cout << "Enter Password: ";
		std::getline(std::cin, key);
		std::cout << std::endl;
		system("cls");

		enObject.setKey((unsigned char*)key.c_str());

		if (!filemanager.IsFile(filename.c_str()))
		{
			filemanager.ReadFilesInFolder(filename.c_str());
			for (int i = 0; i < filemanager.GetFiles().size(); i++)
			{
				bool succeed = enObject.encryptFile(filemanager.GetFiles()[i], Encrypt);
				HandleDisplayMessage(filemanager.GetFiles()[i], Encrypt, succeed);
			}
		}
		else {
			bool succeed = enObject.encryptFile(filename, Encrypt);
			HandleDisplayMessage(filename, Encrypt, succeed);
		}
		
		key = std::string::npos;
		std::cout << std::endl;
	}

	return 0;
}

void HandleDisplayMessage(const std::string& filename, bool isEncrypting, bool isSuccessful)
{
	if (isSuccessful)
	{
		/* Error handling */
		if (isEncrypting)
			std::cout << filename << "-> Encryption compleated successfully." << std::endl;
		else
			std::cout << filename << "-> Decryption compleated successfully." << std::endl;

	}
	else {
		/* Error handling */
		if (isEncrypting)
			std::cerr << filename << "-> Error: Unable to perfrom encryption." << std::endl;
		else
			std::cerr << filename << "-> Error: Unable to perfrom encryption." << std::endl;
	}
}