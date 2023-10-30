#pragma once

#include <vector>
#include <filesystem>

class FileManagerZ
{
public:
	FileManagerZ() {}
	FileManagerZ(std::vector<std::string> blackListedFolders);

private:
	std::vector<std::string> BlackListedFolders;
	std::vector<std::string> Files;

public:
	void ReadFilesInFolder(const char* folder);
	std::string RelativeRootName(const std::filesystem::path path);
	void AddBlackListedFolder(const char* folder);
	bool IsFile(const char* file);
	/* Setters */
	void SetBlackListedFolders(std::vector<std::string> folders) { BlackListedFolders = folders; }
	/* Getters */
	const std::vector<std::string>& GetBlackListedFolders() { return BlackListedFolders; }
	std::vector<std::string> GetFiles() const { return Files; }
};

