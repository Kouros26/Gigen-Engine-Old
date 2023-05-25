#pragma once
#include "Displayable.h"
#include <string>

class MenuBarDisplay : public Displayable
{
public:
	MenuBarDisplay();
	~MenuBarDisplay() override;

	void Draw() override;

private:
	void DrawPlayPause() const;
};
