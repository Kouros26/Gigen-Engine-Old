#pragma once
#include "Mat4/FMat4.hpp"
#include "Vec3/FVec3.hpp"
#include "Vec2/FVec2.hpp"

enum class AnchorY
{
	DOWN,
	CENTER,
	UP
};

enum class AnchorX
{
	LEFT,
	CENTER,
	RIGHT
};

class RectTransform
{
public:
	RectTransform();
	~RectTransform();

	void SetPosition(lm::FVec2 vec);
	void SetWidth(float w);
	void SetHeight(float h);
	void SetSize(lm::FVec2 vec);

	void SetAnchorX(AnchorX anchor);
	void SetAnchorY(AnchorY anchor);

	AnchorX& GetAnchorX();
	AnchorY& GetAnchorY();

	lm::FVec2 GetPosition();
	lm::FVec2 GetSize();

	[[nodiscard]] lm::FMat4& getMatrix();

private:
	AnchorY anchorY = AnchorY::DOWN;
	AnchorX anchorX = AnchorX::LEFT;

	lm::FVec2 position;
	lm::FVec2 size;

	bool hasChanged = false;

	lm::FMat4 matrix;
};