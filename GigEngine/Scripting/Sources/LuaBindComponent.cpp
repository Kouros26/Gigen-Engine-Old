#include "LuaBindComponent.h"
#include "Component.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Log.h"
#include "GameObject.h"
#include "AudioSource.h"

void GigScripting::LuaBindComponent::BindComponent(sol::state& pLuaState)
{
    auto& luaState = pLuaState;
    luaState["Physics"]["Delegate"] = [&pLuaState](std::string DelegateString)
    {
        DelegatePhysics(pLuaState, DelegateString);
    };
    luaState.new_usertype<Component>("Component",
        "GetOwner", [](Component* pComp) { return pComp->GetGameObject(); }
    );

    luaState.new_usertype<Transform>("Transform",
        "AddPosition", &Transform::AddPosition,
        "AddRotation", &Transform::AddRotation,
        "AddScale", &Transform::AddScale,
        "SetPosition", &Transform::SetLocalPosition,
        "SetRotation", &Transform::SetLocalRotation,
        "SetScale", &Transform::SetLocalScale,
        "GetPosition", &Transform::GetLocalPosition,
        "GetRotation", &Transform::GetLocalRotation,
        "GetScale", &Transform::GetLocalScale,
        "GetWorldPosition", &Transform::GetWorldPosition,
        "GetWorldRotation", &Transform::GetWorldRotation,
        "GetWorldScale", &Transform::GetWorldScale,
        "GetFront", &Transform::GetFront,
        "GetUp", &Transform::GetUp,
        "GetRight", &Transform::GetRight,
        "GetOrientation", &Transform::GetOrientation,
        "SetWorldPosition", &Transform::SetWorldPosition,
        "SetWorldRotation", &Transform::SetWorldRotation,
        "SetWorldScale", &Transform::SetWorldScale,
        "LookAt", &Transform::LookAt,
        "GetMatrix", &Transform::MatrixGetter

    );

    luaState.new_enum<RigidBodyType>("RbShapeType",
        {
            {"BOX", RigidBodyType::BOX},
            {"SPHERE", RigidBodyType::SPHERE},
            {"CAPSULE", RigidBodyType::CAPSULE}
        }
    );

    luaState.new_usertype<RigidBody>("RigidBody",
        "SetMass", &RigidBody::SetMass,
        "AddForce", sol::overload
        (
            sol::resolve<void(const lm::FVec3&)const >(&RigidBody::AddForce),
            sol::resolve<void(const float)const >(&RigidBody::AddForce)

        ),
        "AddTorque", sol::overload
        (
            sol::resolve<void(const lm::FVec3&)const>(&RigidBody::AddTorque),
            sol::resolve<void(const float)const>(&RigidBody::AddTorque)

        ),
        "SetVelocity", &RigidBody::SetVelocity,
        "GetVelocity", &RigidBody::GetLinearVelocity,
        "SetAngularVelocity", &RigidBody::SetAngularVelocity,
        "GetMass", &RigidBody::GetMass,
        "ClearForces", &RigidBody::ClearForces,
        "GetFriction", &RigidBody::GetFriction,
        "SetFriction", &RigidBody::SetFriction,
        "GetBounciness", &RigidBody::GetBounciness,
        "SetBounciness", &RigidBody::SetBounciness,
        "GetAngularVelocity", &RigidBody::GetAngularVelocity,
        "SetLinearFactor", sol::overload
        (

            sol::resolve<void(const lm::FVec3&)const>(&RigidBody::SetLinearFactor),
            sol::resolve<void(const float)const>(&RigidBody::SetLinearFactor)
        ),
        "SetAngularFactor", sol::overload
        (
            sol::resolve<void(const lm::FVec3&)const>(&RigidBody::SetAngularFactor),
            sol::resolve<void(const float)const>(&RigidBody::SetAngularFactor)
        ),
        "GetLinearFactor", &RigidBody::GetLinearFactor,
        "GetAngularFactor", &RigidBody::GetAngularFactor,
        "IsTrigger", &RigidBody::IsTrigger,
        "SetTrigger", &RigidBody::SetTrigger,
        "AddImpulse", sol::overload
        (
            sol::resolve<void(const lm::FVec3&)const>(&RigidBody::AddImpulse),
            sol::resolve<void(const float)const>(&RigidBody::AddImpulse)
        ),
        "SetGravity", &RigidBody::SetGravity,
        "SetGravityEnabled", &RigidBody::SetGravityEnabled,
        "GetGravity", &RigidBody::GetGravity

    );

    luaState.new_usertype<AudioSource>("AudioSource",
        sol::base_classes, sol::bases<Component>(),

        "Play", &AudioSource::Play,
        "Pause", &AudioSource::Pause,
        "UnPause", &AudioSource::UnPause,
        "Stop", &AudioSource::Stop,
        "SetVolume", &AudioSource::SetVolume,
        "SetAudio", &AudioSource::SetAudioWithLuaPath,
        "SetLoop", &AudioSource::SetIsLooping,
        "Set3D", &AudioSource::SetIs2D,
        "IsPlaying", &AudioSource::GetIsPlaying,
        "PlayOnStart", &AudioSource::SetPlayOnStart
    );
}

void GigScripting::LuaBindComponent::DelegatePhysics(sol::state& pLuaState, std::string DelegateString)
{
    if (DelegateFromString(pLuaState, DelegateString))
    {
        getFunctionFromString(DelegateString) = pLuaState[DelegateString];
    }
}

bool  GigScripting::LuaBindComponent::DelegateFromString(sol::state& pLuaState, std::string DelegateString)
{
    if (pLuaState[DelegateString].valid())
    {
        return true;
    }
    else
    {
        std::string err = DelegateString + " Does not exist";
        GIG_LOG(err.c_str());
    }
    return false;
}

std::function<void(GameObject*)>& GigScripting::LuaBindComponent::getFunctionFromString(std::string pInput)
{
    if (pInput.compare("OnCollisionEnter") == 0)
        return delegateFunctions.OnCollisionEnter;

    if (pInput.compare("OnCollisionExit") == 0)
        return delegateFunctions.OnCollisionExit;

    if (pInput.compare("OnTriggerEnter") == 0)
        return delegateFunctions.OnTriggerEnter;

    if (pInput.compare("OnTriggerExit") == 0)
        return delegateFunctions.OnTriggerExit;

    return delegateFunctions.defaultReturn;
}