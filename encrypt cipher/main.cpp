#include <iostream>
#include <string>
#include "Encryption.h"

int main()
{

	std::string filename;
	bool Encrypt = false;
	Encryption enObject = Encryption();

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

	return 0;
}

//int main(int argc, char* argv[]) {
//
//    unsigned char ciphertext[MAX_BUFFER_SIZE];
//    unsigned char plaintext[MAX_BUFFER_SIZE];
//    memset(plaintext, '\0', MAX_BUFFER_SIZE);
//    memset(ciphertext, '\0', MAX_BUFFER_SIZE);
//
//    int plaintext_len;
//
//    char* str = (char*)"Hello";
//
//    //if (argc != 2) {
//    //    fprintf(stderr, "Usage: %s <source data>\n", argv[0]);
//    //    exit(EXIT_FAILURE);
//    //}
//
//    plaintext_len = strlen(str);
//    memcpy(plaintext, str, plaintext_len);
//    std::cout << "Source Text is : " << std::endl;
//    std::cout << plaintext << std::endl;
//
//    Encryption encObj = Encryption();
//    encObj.setKey((unsigned char*)"PayPal");
//    int ciphertext_len = encObj.encrypt(plaintext, ciphertext);
//    if (ciphertext_len > 0) {
//        encObj.print_ciphertext(ciphertext, ciphertext_len);
//    }
//
//    encObj.setKey((unsigned char*)"Password");
//
//    for (int i = 0; i < 10; i++)
//    {
//        if (i == 9) {
//            encObj.setKey((unsigned char*)"PayPal");
//        }
//        memset(plaintext, '\0', MAX_BUFFER_SIZE);
//        plaintext_len = encObj.decrypt(plaintext, ciphertext, ciphertext_len);
//        if (plaintext_len > 0) {
//            encObj.print_ciphertext(plaintext, plaintext_len);
//        }
//    }
//
//
//    return 0;
//}