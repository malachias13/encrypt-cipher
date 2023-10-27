#include "Encryption.h"
#include <fstream>
#include <cctype>
#include <conio.h>
#include <iostream>


bool Encryption::encryptFile(const std::string& filename, bool encrypt)
{

    // open file
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) { return false; }

    // Read the content of the file
    unsigned char data = 0;
    std::list<unsigned char> content;

    while (true) 
    {
        inFile.read((char*)&data, sizeof(unsigned char));
        if (inFile.eof()) { break; }
        content.push_back(data);
    }

    inFile.close();

    if (perfromshift(content, encrypt))
    {
        // Write content to file.
        std::ofstream outFile(filename, std::ios::trunc | std::ios::binary);
        if (!outFile) { return false; }

        for (unsigned char& ch : content)
        {
            outFile.write((const char*)&ch, sizeof(unsigned char));
        }

        outFile.close();

        return true;
    }


    return false;
}

bool Encryption::perfromshift(std::list<unsigned char>& content, bool encrypt)
{
    int shift = encrypt ? 3 : -3;

    for (unsigned char& ch : content)
    {
        ch = static_cast<unsigned char>(ch + shift % 255);
    }

    return true;
}
