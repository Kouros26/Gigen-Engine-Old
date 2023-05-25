#include "LuaBindMath.h"

#include "Vec2/FVec2.hpp"
#include "Vec3/FVec3.hpp"
#include "Vec4/FVec4.hpp"
#include "Mat4/FMat4.hpp"
#include "Mat3/FMat3.hpp"
#include "Quaternion/FQuat.hpp"
#include "Utilities.h"

void GigScripting::LuaBindMath::BindMath(sol::state& pLua)
{
    using namespace lm;

    auto& luaState = pLua;

    luaState.new_usertype<FVec2>("Vector2",
        /* Constructor */
        sol::constructors<
        FVec2(),
        FVec2(float, float),
        FVec2(float),
        FVec2(const FVec2&)
        >(),

        /* Operators */
        sol::meta_function::addition, sol::resolve<FVec2(const FVec2&) const>(&FVec2::operator+),
        sol::meta_function::subtraction, sol::resolve<FVec2(const FVec2&) const>(&FVec2::operator-),
        sol::meta_function::multiplication, sol::resolve<FVec2(const FVec2&) const>(&FVec2::operator*),
        sol::meta_function::division, sol::resolve<FVec2(const FVec2&) const>(&FVec2::operator/),
        sol::meta_function::unary_minus, sol::resolve<FVec2() const>(&FVec2::operator-),
        sol::meta_function::to_string, [](const FVec2& pVec2) { return "FVec2(" + std::to_string(pVec2.x) + "," + std::to_string(pVec2.y) + ")"; },

        /* Variables */
        "x", &FVec2::x,
        "y", &FVec2::y,

        /* Data */
        "One", []() { return FVec2::One; },
        "Zero", []() { return FVec2::Zero; },

        /* Functions */
        "Dot", &FVec2::Dot,
        "Length", &FVec2::Length,
        "Normalize", &FVec2::Normalize,
        "Lerp", &FVec2::Lerp,
        "Reflect", &FVec2::Reflect,
        "Project", &FVec2::Project,
        "AngleBetween", &FVec2::AngleBetween
    );

    luaState.new_usertype<FVec3>("Vector3",
        /* Constructor */
        sol::constructors<
        FVec3(),
        FVec3(float, float, float),
        FVec3(float),
        FVec3(const FVec3&)
        >(),

        /* Operators */
        sol::meta_function::addition, sol::resolve<FVec3(const FVec3&) const>(&FVec3::operator+),
        sol::meta_function::subtraction, sol::resolve<FVec3(const FVec3&) const>(&FVec3::operator-),
        sol::meta_function::multiplication, sol::resolve<FVec3(const float) const>(&FVec3::operator*),
        sol::meta_function::division, sol::resolve<FVec3(const float) const>(&FVec3::operator/),
        sol::meta_function::unary_minus, sol::resolve<FVec3() const>(&FVec3::operator-),
        sol::meta_function::to_string, [](const FVec3& pVec3) { return "FVec3(" + std::to_string(pVec3.x) + "," + std::to_string(pVec3.y) + "," + std::to_string(pVec3.z) + ")"; },

        /* Variables */
        "x", &FVec3::x,
        "y", &FVec3::y,
        "z", &FVec3::z,

        /* Data */
        "One", []() { return FVec3::One; },
        "Zero", []() { return FVec3::Zero; },
        "Forward", []() { return FVec3::Forward; },
        "Up", []() { return FVec3::Up; },
        "Right", []() { return FVec3::Right; },
        "Backward", []() { return FVec3::Forward * -1; },
        "Down", []() { return FVec3::Up * -1; },
        "Left", []() { return FVec3::Right * -1; },

        /* Functions */
        "Length", &FVec3::Length,
        "Dot", &FVec3::Dot,
        "Cross", &FVec3::Cross,
        "Normalize", &FVec3::Normalize,
        "Lerp", &FVec3::Lerp,
        "AngleBetween", &FVec3::AngleBetween,
        "Distance", &FVec3::Distance
    );

    luaState.new_usertype<FVec4>("Vector4",
        /* Constructor */
        sol::constructors<
        FVec4(),
        FVec4(float, float, float, float),
        FVec4(float),
        FVec4(float, float, float)
        >(),

        /* Operators */
        sol::meta_function::addition, sol::resolve<FVec4(const FVec4&) const>(&FVec4::operator+),
        sol::meta_function::subtraction, sol::resolve<FVec4(const FVec4&) const>(&FVec4::operator-),
        sol::meta_function::multiplication, sol::resolve<FVec4(const float) const>(&FVec4::operator*),
        sol::meta_function::division, sol::resolve<FVec4(const float) const>(&FVec4::operator/),
        sol::meta_function::unary_minus, sol::resolve<FVec4() const>(&FVec4::operator-),
        sol::meta_function::to_string, [](const FVec4& pVec4) { return "FVec4(" + std::to_string(pVec4.x) + "," + std::to_string(pVec4.y) + "," + std::to_string(pVec4.z) + "," + std::to_string(pVec4.w) + ")"; },

        /* Variables */
        "x", &FVec4::x,
        "y", &FVec4::y,
        "z", &FVec4::z,
        "w", &FVec4::w,

        /* Data */
        "One", []() { return FVec4::One; },
        "Zero", []() { return FVec4::Zero; },
        "Forward", []() { return FVec4::Forward; },
        "Up", []() { return FVec4::Up; },
        "Right", []() { return FVec4::Right; },
        "Backward", []() { return FVec4::Forward * -1; },
        "Down", []() { return FVec4::Up * -1; },
        "Left", []() { return FVec4::Right * -1; },

        /* Functions */
        "Length", &FVec4::Length,
        "Dot", &FVec4::Dot,
        "Normalize", &FVec4::Normalize,
        "Lerp", &FVec4::Lerp
    );

    luaState.new_usertype<FMat3>("Matrix3",
        /* Constructor */
        sol::constructors <
        FMat3(),
        FMat3(const float),
        FMat3(const float, const float, const float,
            const float, const float, const float,
            const float, const float, const  float),
        FMat3(const FVec3&, const FVec3&, const FVec3&)
        >(),

        /* Operators */
        sol::meta_function::addition, &FMat3::operator+,
        sol::meta_function::subtraction, sol::resolve<FMat3(const FMat3&) const >(&FMat3::operator-),
        sol::meta_function::multiplication, sol::overload
        (
            sol::resolve<FMat3(float) const>(&FMat3::operator*),
            sol::resolve<FMat3(const FMat3&) const>(&FMat3::operator*)
        ),
        sol::meta_function::division, sol::resolve<FMat3(float) const>(&FMat3::operator/),
        sol::meta_function::to_string, [](const FMat3& target)
        {
            return "FMat3(" +
                std::to_string(target[0][0]) + "," + std::to_string(target[0][1]) + "," + std::to_string(target[0][2]) + "\n" +
                "," + std::to_string(target[1][0]) + "," + std::to_string(target[1][1]) + "," + std::to_string(target[1][2]) + "\n" +
                "," + std::to_string(target[2][0]) + "," + std::to_string(target[2][1]) + "," + std::to_string(target[2][2]) + ")";
        },

        /* Data */
            "Identity", []() { return FMat3::identity; },

            /* Functions */
            "Transpose", &FMat3::Transpose,
            "Determinant", &FMat3::Determinant,
            "Inverse", &FMat3::Inverse,
            "Rotation", &FMat3::Rotation,
            "Rotate", &FMat3::Rotate
            );

    luaState.new_usertype<FMat4>("Matrix4",
        /* Constructor */
        sol::constructors <
        FMat4(),
        FMat4(const float),
        FMat4(const float, const float, const float, const float,
            const float, const float, const float, const float,
            const float, const float, const float, const float,
            const float, const float, const float, const float),
        FMat4(const FVec4&, const FVec4&, const FVec4&, const FVec4&)
        >(),

        /* Operators */
        sol::meta_function::addition, &FMat4::operator+,
        sol::meta_function::subtraction, sol::resolve<FMat4(const FMat4&) const >(&FMat4::operator-),
        sol::meta_function::multiplication, sol::overload
        (
            sol::resolve<FMat4(float) const>(&FMat4::operator*),
            sol::resolve<FMat4(const FMat4&) const>(&FMat4::operator*)
        ),
        sol::meta_function::division, sol::resolve<FMat4(float) const>(&FMat4::operator/),
        sol::meta_function::to_string, [](const FMat4& target)
        {
            return "FMat4(" +
                std::to_string(target[0][0]) + "," + std::to_string(target[0][1]) + "," + std::to_string(target[0][2]) + "," + std::to_string(target[0][3]) + "\n" +
                "," + std::to_string(target[1][0]) + "," + std::to_string(target[1][1]) + "," + std::to_string(target[1][2]) + "," + std::to_string(target[1][3]) + "\n" +
                "," + std::to_string(target[2][0]) + "," + std::to_string(target[2][1]) + "," + std::to_string(target[2][2]) + "," + std::to_string(target[2][3]) + "\n" +
                "," + std::to_string(target[3][0]) + "," + std::to_string(target[3][1]) + "," + std::to_string(target[3][2]) + "," + std::to_string(target[3][3]) + ")";
        },

        /* Data */
            "Identity", []() { return FMat4::IdentityMatrix; },

            /* Functions */
            "Transpose", &FMat4::Transpose,
            "Inverse", &FMat4::Inverse,
            "Translation", &FMat4::Translation,
            "Translate", &FMat4::Translate,
            "RotateY", [](const FMat4& pMat, const float pAngle) { return FMat4::YRotation(pMat, pAngle); },
            "RotateX", [](const FMat4& pMat, const float pAngle) { return FMat4::XRotation(pMat, pAngle); },
            "RotateZ", [](const FMat4& pMat, const float pAngle) { return FMat4::ZRotation(pMat, pAngle); },
            "RotateYXZ", &FMat4::YXZRotation,
            "RotationEuler", &FMat4::RotationEuler,
            "CreatePerspective", &FMat4::Perspective,
            "LookAt", &FMat4::LookAt

            );

    luaState.new_usertype<FQuat>("Quaternion",
        /* Constructor */
        sol::constructors <
        FQuat(),
        FQuat(const float),
        FQuat(const float, const float, const float),
        FQuat(const float, const float, const float, const float),
        FQuat(const FVec3&, float),
        FQuat(const FMat3&)
        >(),

        /* Operators */
        sol::meta_function::addition, &FQuat::operator+,
        sol::meta_function::subtraction, sol::resolve<const FQuat(const FQuat&) const>(&FQuat::operator-),
        sol::meta_function::multiplication, sol::overload
        (
            sol::resolve<const FQuat(float const&) const>(&FQuat::operator*),
            sol::resolve<const FQuat(const FQuat&) const>(&FQuat::operator*),
            sol::resolve<const FVec3(const FVec3&) const>(&FQuat::operator*),
            sol::resolve<const FVec4(const FVec4&) const>(&FQuat::operator*)
        ),
        sol::meta_function::division, &FQuat::operator/,
        sol::meta_function::to_string, [](const FQuat& pQuat) { return "FQuat(" + std::to_string(pQuat.x) + ","
        + std::to_string(pQuat.y) + "," + std::to_string(pQuat.z) + "," + std::to_string(pQuat.w) + ")"; },

        /* Variables */
        "x", &FQuat::x,
        "y", &FQuat::y,
        "z", &FQuat::z,
        "w", &FQuat::w,

        /* Data */
        "Identity", []() { return FQuat::identity; },

        /* Functions */
        "Length", &FQuat::Length,
        "Normalize", &FQuat::Normalize,
        "Conjugate", &FQuat::Conjugate,
        "Inverse", &FQuat::Inverse,
        "Dot", &FQuat::Dot,
        "Slerp", &FQuat::SLerp,
        "Cross", &FQuat::Cross,
        "NLerp", &FQuat::NLerp,
        "Lerp", &FQuat::Lerp,
        "IsUnit", &FQuat::isUnit,
        "GetAngle", sol::overload
        (
            sol::resolve<float() const>(&FQuat::getAngle),
            sol::resolve<float(const FQuat&) const>(&FQuat::getAngle)
        ),
        "Rotate", sol::overload
        (
            sol::resolve<FQuat(FQuat const&, FVec3 const&) >(&FQuat::Rotate),
            sol::resolve<FQuat(FQuat const&, FQuat const&) >(&FQuat::Rotate),
            sol::resolve<FQuat(FQuat const&, FVec3 const&, float const&) >(&FQuat::Rotate)
        ),
        "FromEuler", sol::overload
        (
            sol::resolve<FQuat(const float, const float, const float) >(&FQuat::FromEuler),
            sol::resolve<FQuat(FVec3 const&) >(&FQuat::FromEuler)
        ),

        "ToMat3", &FQuat::ToRotateMat3,
        "FromMat3", &FQuat::FromMatrix3

    );

    luaState.create_named_table("MathsTools");
    luaState["MathsTools"]["ToRadians"] = [](const float pAngle) { return lm::degreesToRadians(pAngle); };
    luaState["MathsTools"]["ToDegrees"] = [](const float pAngle) { return lm::radiansToDegrees(pAngle); };
    luaState["MathsTools"]["Clamp"] = [](const float pValue, const float pMin, const float pMax) { return lm::clamp(pValue, pMin, pMax); };
    luaState["MathsTools"]["RandomInt"] = [](const int pMin, const int pMax) { return lm::randomInt(pMin, pMax); };
    luaState["MathsTools"]["RandomFloat"] = [](const float pMin, const float pMax) { return lm::randomFloat(pMin, pMax); };
}