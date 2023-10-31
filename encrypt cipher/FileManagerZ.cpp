#include "FileManagerZ.h"
#include <string>
#include <fstream>
#include <iostream>


FileManagerZ::FileManagerZ(std::vector<std::string> blackListedFolders)
	:BlackListedFolders(blackListedFolders)
{
}

void FileManagerZ::ReadFilesInFolder(const char* folder)
{
	namespace fs = std::filesystem;
	bool isBlacklisted = false;
	for (const auto& entry : fs::directory_iterator(folder))
	{
		if(!IsFile(entry.path().generic_string().c_str())){ continue; }
		for (int i = 0; i < BlackListedFolders.size(); i++)
		{
			if (isBlacklisted = entry.path().parent_path().filename() != BlackListedFolders[i]) { continue; }
			else {
				std::cout << entry.path().parent_path().filename() << "is a blacklisted Folder." << std::endl;
				break;
			}
		}
		if(isBlacklisted == true)
			Files.push_back(entry.path().generic_string());
	}
}

std::string FileManagerZ::RelativeRootName(const std::filesystem::path path)
{
	std::string StrPath = path.generic_string();
	std::string root;
	for (int i = 0; i < StrPath.size(); i++)
	{
		if (StrPath[i] == '/') { return root; }
		root += StrPath[i];
	}
	return root;
}

void FileManagerZ::AddBlackListedFolder(const char* folder)
{
	BlackListedFolders.push_back(folder);
}

bool FileManagerZ::IsFile(const char* file)
{
	std::ifstream OutFile(file, std::ios::binary);
	if (OutFile)
	{
		OutFile.close();
		return true;
	}
	else
	{
		OutFile.close();
		return false;
	}
}
