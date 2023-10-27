#include <iostream>
#include <string>
#include "Encryption.h"

int main()
{

	std::string filename;
	bool Encrypt = false;

	std::cout << "Enter the filename." << std::endl;
	std::getline(std::cin >> std::ws, filename);

	std::cout << "Encrypt: (1) or Decrypt: (2)." << std::endl;
	int value;
	std::cin >> value;

	if (value == 1) { Encrypt = true; }
	else if(value == 2) {
		Encrypt = false;
	}

	if (Encrypt)
	{
		if (Encryption::encryptFile(filename, true))
		{
			std::cout << "Encryption compleated successfully." << std::endl;
		}
		else {
			std::cerr << "Error: Unable to perfrom encryption." << std::endl;
		}
	}
	else {
		if (Encryption::encryptFile(filename, false))
		{
			std::cout << "Decryption compleated successfully." << std::endl;
		}
		else {
			std::cerr << "Error: Unable to perfrom decryption." << std::endl;
		}
	}

	return 0;
}