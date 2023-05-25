#pragma once
#include <map>
#include <vector>
#include <assimp/anim.h>

#include "BoneInfo.h"
#include "IResource.h"
#include "Model.h"
#include "Mat4/FMat4.hpp"
#include "Quaternion/FQuat.hpp"
#include "Vec3/FVec3.hpp"

struct KeyPosition
{
    lm::FVec3 position;
    float timeStamp;
};

struct KeyRotation
{
    lm::FQuat orientation;
    float timeStamp;
};

struct KeyScale
{
    lm::FVec3 scale;
    float timeStamp;
};

class Bone
{
private:
    std::vector<KeyPosition> positions;
    std::vector<KeyRotation> rotations;
    std::vector<KeyScale> scales;
    int numPositions;
    int numRotations;
    int numScalings;

    std::string name;
    int id;

    lm::FVec3 localPos;
    lm::FQuat localRot;
    lm::FVec3 localScl;

public:

    Bone(const std::string& pName, int pId, const aiNodeAnim* pChannel);

    void Update(float pAnimationTime);

    [[nodiscard]] int GetPositionIndex(float pAnimationTime) const;
    [[nodiscard]] int GetRotationIndex(float pAnimationTime) const;
    [[nodiscard]] int GetScaleIndex(float pAnimationTime) const;

    [[nodiscard]] std::string GetBoneName() const;
    [[nodiscard]] int GetBoneID() const;

    [[nodiscard]] lm::FMat4 GetLocalTransform() const;
    lm::FVec3& GetLocalPos();
    lm::FQuat& GetLocalRot();
    lm::FVec3& GetLocalScl();

private:

    float GetScaleFactor(float pLastTimeStamp, float pNextTimeStamp, float pAnimationTime);

    lm::FVec3 InterpolatePosition(float pAnimationTime);
    lm::FQuat InterpolateRotation(float pAnimationTime);
    lm::FVec3 InterpolateScaling(float pAnimationTime);
};

class Animation : public IResource
{
private:

    double duration;
    double ticksPerSecond;
    std::vector<Bone> bones;
    NodeData rootNode;
    std::map<std::string, BoneInfo> boneMap;

public:

    Animation() = default;
    Animation(const std::string& pAnimationPath, Model* pModel);
    ~Animation() override;

    void Init() override;

    Bone* FindBone(const std::string& pName);

    [[nodiscard]] double GetTicksPerSecond() const;
    [[nodiscard]] double GetDuration() const;
    NodeData& GetRootNode();
    std::map<std::string, BoneInfo>& GetBoneIDMap();
    std::vector<Bone>& GetBones();

private:
};

namespace AnimUtils
{
    lm::FMat4 GetTransform(const lm::FVec3& pPos, const lm::FQuat& pRot, const lm::FVec3& pScl);
}