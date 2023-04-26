#pragma once
#include "Displayable.h"

class FileDisplay : public Displayable
{
public:
	FileDisplay();
	~FileDisplay() override;

	void Draw() override;
};
