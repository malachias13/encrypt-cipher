#include <iostream>
#include <string>
#include "Encryption.h"

int main()
{

	std::string filename;
	std::string key;
	bool Encrypt = false;

	while (true)
	{
		Encryption enObject = Encryption();

		std::cout << "Encrypt: (1) Decrypt: (2) Exit: (3)" << std::endl;
		int value;
		std::cin >> value;

		if (value == 1) { Encrypt = true; }
		else if (value == 2) { Encrypt = false; }
		else { break; }

		std::cout << "Enter the filename." << std::endl;
		std::getline(std::cin >> std::ws, filename);
		std::cout << std::endl;

		std::cout << "Enter Password: ";
		std::getline(std::cin, key);
		std::cout << std::endl;

		enObject.setKey((unsigned char*)key.c_str());

		if (Encrypt)
		{
			if (enObject.encryptFile(filename, true))
			{
				std::cout << "Encryption compleated successfully." << std::endl;
			}
			else {
				std::cerr << "Error: Unable to perfrom encryption." << std::endl;
			}
		}
		else {
			if (enObject.encryptFile(filename, false))
			{
				std::cout << "Decryption compleated successfully." << std::endl;
			}
			else {
				std::cerr << "Error: Unable to perfrom decryption." << std::endl;
			}
		}
		key = std::string::npos;
		std::cout << std::endl;
	}

	return 0;
}
