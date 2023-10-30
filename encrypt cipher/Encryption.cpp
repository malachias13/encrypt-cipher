#include "Encryption.h"
#include <fstream>
#include <vector>
#include <random>
#include <string>



bool Encryption::encryptFile(const std::string& filename, bool bEncrypt)
{

    // open file
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) { return false; }
    if (!inFile.is_open()) { inFile.open(filename); }

    // Read the content of the file
    unsigned char byte = 0;
    std::vector<unsigned char> content;
   // std

    while (true) 
    {
        inFile.read((char*)&byte, sizeof(unsigned char));
        if (inFile.eof()) { break; }
        content.push_back(byte);
    }

    inFile.close();
    unsigned char* Data = new unsigned char[MAX_BUFFER_SIZE];
    memset(Data, '\0', MAX_BUFFER_SIZE);

    int Data_len = 0;

    if (bEncrypt)
    {
        Data_len = encrypt(content.data(), Data, content.size());
    }
    else {

        Data_len = decrypt(Data, content.data(), content.size());
    }

    if (Data_len < 0) { return false; }

	// Write content to file.
	std::ofstream outFile(filename, std::ios::trunc | std::ios::binary);
	if (!outFile) { return false; }

	for (int i = 0; i < Data_len; i++)
	{
		outFile.write((const char*)&Data[i], sizeof(unsigned char));
	}

	outFile.close();

    delete[] Data;

    return true;
}

Encryption::Encryption()
{
    key = (unsigned char*)"01234567890123456789012345678901"; // A 256 bit key 32 bytes
    iv = (unsigned char*)"0269872681772902";

    //iv = Random16Bit();     // A 128 bit IV  16 bytes

}

int Encryption::encrypt(unsigned char* plaintData, unsigned char* cipherData, int plainData_len)
{

    EVP_CIPHER_CTX* ctx;
    int len;
    if (plainData_len == -1) {
        plainData_len = strlen((char*)plaintData);
    }
    int cipherData_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        std::cout << "encrypt: EVP_CIPHER_CTX_new() error" << std::endl;
        return -1;
    }

    /*
    * Initialise the encryption operation
    */
       
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    {
        std::cout << "encrypt: EVP_EncryptInit_ex() error" << std::endl;
        return -1;
    }

    /*
    * Provide the message to be encrypted, and obtain the encrypted output.
    */

    if (1 != EVP_EncryptUpdate(ctx, cipherData, &len, plaintData, plainData_len))
    {
        std::cout << "encrypt: EVP_EncryptUpdate() error" << std::endl;
        return -1;
    }

    cipherData_len = len;

    /*
    * Finalise the encryption. Further cipherData bytes may be written at
    * this stage.
    */

    if (1 != EVP_EncryptFinal_ex(ctx, cipherData + len, &len))
    {
        std::cout << "encrypt: EVP_EncryptFinal_ex() error" << std::endl;
        return -1;
    }

    cipherData_len += len;

    /* Clean up*/
    EVP_CIPHER_CTX_free(ctx);

    return cipherData_len;
}

int Encryption::decrypt(unsigned char* plainData, unsigned char* cipherData, int ciphertext_len)
{
    EVP_CIPHER_CTX* ctx;
    int len;
    int plainData_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        std::cout << "decrypt: EVP_CIPHER_CTX_new error" << std::endl;
        return -1;
    }

    /*
    * Initialise the decryption operation.
    */
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) 
    {
        std::cout << "decrypt: EVP_DecryptInit_ex() error" << std::endl;
        return -1;
    }

    /*
    * Provide the message to be decrypted, and obtain the plainData output.
    */

    if (1 != EVP_DecryptUpdate(ctx, plainData, &len, cipherData, ciphertext_len))
    {
        std::cout << "decrypt: EVP_DecryptUpdate() error" << std::endl;
        return -1;
    }
    plainData_len = len;

    /*
    * Finalise the decryption.
    */
    if (1 != EVP_DecryptFinal_ex(ctx, plainData + len, &len)) 
    {
        std::cout << "decrypt: EVP_DecryptFinal_ex() error" << std::endl;
        return -1;
    }
    plainData_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plainData_len;
}

void Encryption::print_ciphertext(unsigned char* ciphertext, int ciphertext_len)
{
    printf("Ciphertext is:\n");
    BIO_dump_fp(stdout, (const char*)ciphertext, ciphertext_len);
}

void Encryption::setKey(unsigned char* _key)
{
    key = _key;
}

void Encryption::setIV(unsigned char* _iv)
{
    iv = _iv;
}

Encryption::~Encryption()
{
}

unsigned char* Encryption::Random16Bit()
{
    srand(time(0));
    unsigned long long number;

    // Ensure most significant digit is not 0
    number = rand() % 9 + 1;

    // Add 15 more digits (which can also be 0)
    for (unsigned int i = 0; i < 15; i++)
    {
        number *= 10;
        number += rand() % 10;
    }

    return (unsigned char*)std::to_string(number).c_str();
}
