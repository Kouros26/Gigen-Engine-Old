#include "IResource.h"
#include <fstream>
#include <filesystem>
#include <iostream>

std::string readFile(const std::string& path) {
	std::string content;
	std::ifstream file(path);

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) 
			content.append(line + "\n");

		file.close();
	}
	return content;
}