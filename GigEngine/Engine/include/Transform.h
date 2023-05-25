#pragma once
#include "Vec3/FVec3.hpp"
#include "Mat4/FMat4.hpp"
#include <Quaternion/FQuat.hpp>

class RigidBody;
class Transform
{
public:
	Transform(const lm::FVec3& pos = { 0 }, const lm::FVec3& rot = { 0 }, const lm::FVec3& scl = { 1 });
	~Transform();

	void LookAt(const lm::FVec3& target, const lm::FVec3& up);

	void SetWorldPosition(const lm::FVec3& pos);
	void SetWorldRotation(const lm::FVec3& rot);
	void SetWorldScale(const lm::FVec3& scl);

	void SetLocalPosition(const lm::FVec3& pos);
	void SetLocalRotation(const lm::FVec3& rot);
	void SetLocalScale(const lm::FVec3& scl);

	void AssignWorldPosition(const lm::FVec3& pos);
	void AssignWorldRotation(const lm::FVec3& rot);
	void AssignWorldScale(const lm::FVec3& scl);

	void AssignLocalPosition(const lm::FVec3& pos);
	void AssignLocalRotation(const lm::FVec3& rot);
	void AssignLocalScale(const lm::FVec3& scl);

	[[nodiscard]] lm::FVec3 GetWorldPosition() const;
	[[nodiscard]] lm::FVec3 GetWorldScale() const;
	[[nodiscard]] lm::FVec3 GetWorldRotation() const;
	[[nodiscard]] lm::FQuat GetOrientation();

	[[nodiscard]] lm::FVec3 GetLocalPosition() const;
	[[nodiscard]] lm::FVec3 GetLocalScale() const;
	[[nodiscard]] lm::FVec3 GetLocalRotation() const;

	void AddPosition(const lm::FVec3& pos);
	void AddRotation(const lm::FVec3& rot);
	void AddScale(const lm::FVec3& scl);

	void RigidBodyAddPosition(const lm::FVec3& pPosition);
	void RigidBodyAddRotation(const lm::FVec3& pRotation);

	void SetOwnerRigidBody(RigidBody* rigidBody);

	lm::FVec3 GetFront();
	lm::FVec3 GetUp();
	lm::FVec3 GetRight();

	lm::FMat4 GetMatrix();
	lm::FMat4& MatrixGetter();

private:
	void UpdateMatrix();
	void LimitRotation();

	RigidBody* ownerRigidBody = nullptr;

	lm::FVec3 worldPosition{ 0 };
	lm::FVec3 worldRotation{ 0 };
	lm::FVec3 worldScale{ 1 };

	lm::FVec3 localPosition{ 0 };
	lm::FVec3 localRotation{ 0 };
	lm::FVec3 localScale{ 1 };

	lm::FMat4 worldMatrix;

	bool hasChanged = true;
};