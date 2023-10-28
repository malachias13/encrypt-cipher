#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <list>

#include <string.h>
#include <sstream>

#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#define MAX_BUFFER_SIZE    2'151'205


class Encryption
{
public:
	 bool encryptFile(const std::string& filename, bool bEncrypt);

public:
	Encryption();
	// OpenSSL code.
	int encrypt(unsigned char* plaintData, unsigned char* cipherData, int plainData_len = -1);
	int decrypt(unsigned char* plainData, unsigned char* cipherData, int ciphertext_len);
	void print_ciphertext(unsigned char* ciphertext, int ciphertext_len);

	void setKey(unsigned char* _key);
	void setIV(unsigned char* _iv);
	~Encryption();

private:
	unsigned char* Random16Bit();

private:
	unsigned char* key;
	unsigned char* iv;

};

