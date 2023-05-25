#pragma once
#include "Displayable.h"
#include <string>

class FileExplorer : public Displayable
{
public:
	FileExplorer();
	~FileExplorer() override;

	void Draw() override;

private:
	[[nodiscard]] const char* GetIconOfFile(const std::string& str) const;

	bool isDragging = false;

	const std::string rootDirPath = "../../../Resources";
	std::string currentDirPath;
	const float padding = 16.0f;
	const float cellSize = 100.0f;
};
