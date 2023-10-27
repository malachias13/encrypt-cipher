#pragma once

#include<string>
#include <list>

class Encryption
{
public:
	static bool encryptFile(const std::string& filename, bool encrypt);

private:
	static bool perfromshift(std::list<unsigned char>& content, bool encrypt);
};

