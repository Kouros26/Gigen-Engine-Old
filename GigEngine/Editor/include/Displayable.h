#pragma once

class Displayable
{
public:
	Displayable();
	virtual ~Displayable() = default;

	virtual void Draw() = 0;

	[[nodiscard]] float GetWidth() const;
	[[nodiscard]] float GetHeight() const;

protected:
	void LimitWidthResize();
	void LimitHeightResize();

	float width;
	float height;
};
