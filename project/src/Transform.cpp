#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::SetPosition(lm::vec3 pos)
{
	position = pos;
}

void Transform::SetRotation(lm::vec3 rot)
{
	rotation = rot;
	ClampRotation();
}

void Transform::SetScale(lm::vec3 scl)
{
	scale = scl;
}

lm::vec3 Transform::GetPosition() const
{
	return position;
}

lm::vec3 Transform::GetScale() const
{
	return scale;
}

lm::vec3 Transform::GetRotation() const
{
	return rotation;
}

void Transform::AddPosition(lm::vec3 pos)
{
	position += pos;
}

lm::vec3 Transform::GetFront()
{
	lm::mat4 inverse = GetMatrix().GetInverse();
	lm::vec4 temp = inverse[2];
	lm::vec3 forward(temp[0], temp[1], temp[2]);

	return -forward.Normalized();
}

lm::vec3 Transform::GetRight()
{
	lm::mat4 inverse = GetMatrix().GetInverse();
	lm::vec4 temp = inverse[0];
	lm::vec3 forward(temp[0], temp[1], temp[2]);

	return forward.Normalized();
}

lm::vec3 Transform::GetUp()
{
	lm::mat4 inverse = GetMatrix().GetInverse();
	lm::vec4 temp = inverse[1];
	lm::vec3 forward(temp[0], temp[1], temp[2]);

	return forward.Normalized();
}

lm::mat4 Transform::GetMatrix()
{
	UpdateMatrix();
	return matrix;
}

void Transform::AddRotation(lm::vec3 rot)
{
	rotation += rot;
	ClampRotation();
}

void Transform::AddScale(lm::vec3 scl)
{
	scale += scl;
}

void Transform::UpdateMatrix()
{
	matrix = lm::mat4::CreateTransformMatrix(position, rotation, scale);
}

void Transform::ClampRotation()
{
	for (int i = 0; i < 3; i++)
	{
		while (rotation[i] < 0)
		{
			rotation[i] += 360;
		}
		while (rotation[i] > 360)
		{
			rotation[i] -= 360;
		}
	}
}