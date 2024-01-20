// Name: Or Badani
// ID: 316307586

/*
FileHandler.h
*/

#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>


class FileHandler {
public:
	bool openFile(const std::string&, std::fstream&, bool);
	bool openFileBin(const std::string&, std::fstream&, bool);
	bool openFileOverwrites(const std::string&, std::fstream&);
	bool closeFile(std::fstream&);
	bool writeToFile(std::fstream&, const char*, uint32_t);
	bool readFileIntoPayload(std::fstream&, char*, uint32_t);
	void hexifyToFile(std::fstream&, const char*, unsigned int);

	bool isExistent(const std::string&);
	uint32_t getFileSize(const std::string&);
};

