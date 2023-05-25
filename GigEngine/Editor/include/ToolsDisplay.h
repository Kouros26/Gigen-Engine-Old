#pragma once
#include "FileExplorer.h"
#include "FPSDisplay.h"

class ToolsDisplay : public Displayable
{
public:
	ToolsDisplay();
	~ToolsDisplay() override;

	void Draw() override;

private:

	FileExplorer fileExplorer;
	FPSDisplay fps;

	void DrawExplorer();
	void DrawProfiler();
	void DrawConsole();
};
