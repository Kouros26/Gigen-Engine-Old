#pragma once
#include "Mat4/FMat4.hpp"
#include "Vec3/FVec3.hpp"
#include "Vec2/FVec2.hpp"

class RectTransform
{
public:
	RectTransform();
	~RectTransform();

	void SetPosition(lm::FVec2 vec);
	void SetWidth(float w);
	void SetHeight(float h);
	void SetSize(lm::FVec2 vec);

	lm::FVec2 GetPosition();
	lm::FVec2 GetSize();

	_NODISCARD lm::FMat4& getMatrix();
private:
	lm::FVec2 position;
	lm::FVec2 size;

	bool hasChanged = false;

	lm::FMat4 matrix;
};