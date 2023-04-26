#include <Quaternion/FQuat.hpp>
#include <Vec3/FVec3.hpp>
#include <Vec4/FVec4.hpp>
#include <Utilities.h>
#include <Mat3/FMat3.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY
#include <glm/gtc/quaternion.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace lm;

#define CHECK_QUAT(quat, quatGlm)\
CHECK(quat.x == Catch::Approx(quatGlm.x));\
CHECK(quat.y == Catch::Approx(quatGlm.y));\
CHECK(quat.z == Catch::Approx(quatGlm.z));\
CHECK(quat.w == Catch::Approx(quatGlm.w))

#define CHECK_MAT3(mat, matGlm)\
CHECK(mat[0][0] == Catch::Approx(matGlm[0][0])); \
CHECK(mat[0][1] == Catch::Approx(matGlm[0][1])); \
CHECK(mat[0][2] == Catch::Approx(matGlm[0][2])); \
CHECK(mat[1][0] == Catch::Approx(matGlm[1][0])); \
CHECK(mat[1][1] == Catch::Approx(matGlm[1][1])); \
CHECK(mat[1][2] == Catch::Approx(matGlm[1][2])); \
CHECK(mat[2][0] == Catch::Approx(matGlm[2][0])); \
CHECK(mat[2][1] == Catch::Approx(matGlm[2][1])); \
CHECK(mat[2][2] == Catch::Approx(matGlm[2][2]))

#define CHECK_VECTOR3(Vec, VecGlm)\
 CHECK(Vec.x == Catch::Approx(VecGlm.x));\
 CHECK(Vec.y == Catch::Approx(VecGlm.y));\
 CHECK(Vec.z == Catch::Approx(VecGlm.z))

TEST_CASE("Quaternion", "[.all][Quaternion]")
{
    SECTION("Instantiation")
    {
        // Default Constructor
        lm::FQuat empty;
        glm::quat emptyGlm{};

        CHECK_QUAT(empty, emptyGlm);

        // Destructor
        {
            lm::FQuat temp;
        }

        // Basic Constructor
        lm::FQuat allParam{ .5f, 2.f, 5.f, 2.5f }; // Axis X, Axis, Y, Axis Z, Angle W
        glm::quat allParamGlm{ 2.5f, .5f, 2.f, 5.f }; // Angle W, Axis X, Axis, Y, Axis Z
        CHECK_QUAT(allParam, allParamGlm);

        // Copy Constructor
        lm::FQuat copy{ allParam };
        glm::quat copyGlm{ allParamGlm };
        CHECK_QUAT(copy, copyGlm);

        //One param
        lm::FQuat oneParam{ 2.5f };
        glm::quat oneParamGlm{ 0, 2.5f, 2.5f,2.5f };
        CHECK_QUAT(oneParam, oneParamGlm);

        // Assignment Operator
        empty = allParam;
        emptyGlm = allParamGlm;
        CHECK_QUAT(empty, emptyGlm);

        //from axis and angle
        SECTION("From Axis and Angle")
        {
            lm::FQuat fromAxisAngle{ lm::FVec3{ 1.f, 2.f, 3.f }, 4.f };

            glm::quat fromAxisAngleGlm = glm::angleAxis(glm::radians(4.f), glm::normalize(glm::vec3{ 1.f, 2.f, 3.f }));

            CHECK_QUAT(fromAxisAngle, fromAxisAngleGlm);
        }

        SECTION("From Matrix3")
        {
            lm::FQuat fromMatrix3{ lm::FMat3{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f } };
            glm::quat fromMatrix3Glm{ glm::mat3{ 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f } };
            CHECK_QUAT(fromMatrix3, fromMatrix3Glm);
        }

        // Size compare
        CHECK(sizeof lm::FQuat == sizeof glm::quat);

        // Memory
        CHECK(memcmp(&allParam, &allParamGlm, sizeof lm::FQuat) == 0);
    }

    SECTION("Accessor")
    {
        SECTION("Index Operator")
        {
            lm::FQuat quat{ 1.f, 2.f, 3.f, 4.f };
            glm::quat quatGlm{ 4.f, 1.f, 2.f, 3.f };

            CHECK_QUAT(quat, quatGlm);

            quat[0] = 5.f;
            quatGlm[0] = 5.f;
            CHECK_QUAT(quat, quatGlm);

            quat[1] = 6.f;
            quatGlm[1] = 6.f;
            CHECK_QUAT(quat, quatGlm);

            quat[2] = 7.f;
            quatGlm[2] = 7.f;
            CHECK_QUAT(quat, quatGlm);

            quat[3] = 8.f;
            quatGlm[3] = 8.f;
            CHECK_QUAT(quat, quatGlm);

            CHECK(quat[0] == Catch::Approx(quatGlm[0]));
            CHECK(quat[1] == Catch::Approx(quatGlm[1]));
            CHECK(quat[2] == Catch::Approx(quatGlm[2]));
            CHECK(quat[3] == Catch::Approx(quatGlm[3]));
        }

        SECTION("X")
        {
            lm::FQuat quat{ 1.f, 2.f, 3.f, 4.f };
            glm::quat quatGlm{ 4.f, 1.f, 2.f, 3.f };

            CHECK_QUAT(quat, quatGlm);

            quat.x = 5.f;
            quatGlm.x = 5.f;
            CHECK_QUAT(quat, quatGlm);

            CHECK(quat.x == Catch::Approx(quatGlm.x));
        }

        SECTION("Y")
        {
            lm::FQuat quat{ 1.f, 2.f, 3.f, 4.f };
            glm::quat quatGlm{ 4.f, 1.f, 2.f, 3.f };

            CHECK_QUAT(quat, quatGlm);

            quat.y = 5.f;
            quatGlm.y = 5.f;
            CHECK(quat.y == Catch::Approx(quatGlm.y));
        }

        SECTION("Z")
        {
            lm::FQuat quat{ 1.f, 2.f, 3.f, 4.f };
            glm::quat quatGlm{ 4.f, 1.f, 2.f, 3.f };

            CHECK_QUAT(quat, quatGlm);

            quat.z = 5.f;
            quatGlm.z = 5.f;
            CHECK_QUAT(quat, quatGlm);

            CHECK(quat.z == Catch::Approx(quatGlm.z));
        }
    }

    SECTION("Comparator")
    {
        // Compare with self
        lm::FQuat self{ 1.f, 2.f, 3.f, 4.f };
        CHECK(self == self);

        // Compare with self
        CHECK(lm::FQuat{ 1.f, 2.f, 3.f, 4.f } == lm::FQuat{ 1.f, 2.f, 3.f, 4.f });

        // trying to find copy/paste mistake
        lm::FQuat twos{ 2.f, 2.f,2.f,2.f };
        CHECK_FALSE(lm::FQuat{ .5f, 2.f, 2.f, 2.f } == twos);
        CHECK_FALSE(lm::FQuat{ 2.f, .5f, 2.f, 2.f } == twos);
        CHECK_FALSE(lm::FQuat{ 2.f, 2.f, .5f, 2.f } == twos);
        CHECK_FALSE(lm::FQuat{ 2.f, 2.f, 2.f, .5f } == twos);
        CHECK_FALSE(twos == lm::FQuat{ .5f, 2.f, 2.f, 2.f });
        CHECK_FALSE(twos == lm::FQuat{ 2.f, .5f, 2.f, 2.f });
        CHECK_FALSE(twos == lm::FQuat{ 2.f, 2.f, .5f, 2.f });
        CHECK_FALSE(twos == lm::FQuat{ 2.f, 2.f, 2.f, .5f });

        // Testing comparison
        CHECK_FALSE(self.isUnit());
        CHECK(lm::FQuat{ sqrtf(0.25f), sqrtf(0.25f), sqrtf(0.25f), sqrtf(0.25f) }.isUnit());

        CHECK_FALSE(self != self);
    }

    SECTION("Arithmetic")
    {
        lm::FQuat const small{ 2.f, 3.f, 4.f, 1.f };
        lm::FQuat const big{ 3.f, 2.f, 1.f, 4.f, };

        glm::quat const smallGlm{ 1.f, 2.f, 3.f, 4.f };
        glm::quat const bigGlm{ 4.f, 3.f, 2.f, 1.f };

        SECTION("Addition")
        {
            {
                lm::FQuat sum = big;
                sum += small;

                glm::quat sumGlm = bigGlm;
                sumGlm += smallGlm;

                CHECK_QUAT(sum, sumGlm);
            }

            {
                lm::FQuat sum = big + small;

                glm::quat sumGlm = bigGlm + smallGlm;

                CHECK_QUAT(sum, sumGlm);
            }
        }

        SECTION("Opposite")
        {
            lm::FQuat opposite = -big;

            glm::quat oppositeGlm = -bigGlm;

            CHECK_QUAT(opposite, oppositeGlm);
        }

        SECTION("Subtraction")
        {
            lm::FQuat difference = big - small;

            glm::quat differenceGlm = bigGlm - smallGlm;

            CHECK_QUAT(difference, differenceGlm);
        }

        SECTION("Multiplication")
        {
            {
                lm::FQuat product = big * small;

                glm::quat productGlm = bigGlm * smallGlm;

                CHECK_QUAT(product, productGlm);
            }

            {
                lm::FQuat product = big * 2.f;

                glm::quat productGlm = bigGlm * 2.f;

                CHECK_QUAT(product, productGlm);
            }

            {
                lm::FQuat product;
                product *= big;

                glm::quat productGlm{};
                productGlm *= bigGlm;

                CHECK_QUAT(product, productGlm);
            }
            {
                lm::FQuat product(1);
                lm::FVec3 const vec{ 1.f, 2.f, 3.f };
                lm::FVec3 result = vec * product;

                glm::quat productGlm(0, 1, 1, 1);
                glm::vec3 const vecGlm{ 1.f, 2.f, 3.f };
                glm::vec3 resultGlm = vecGlm * productGlm;

                CHECK(result[0] == resultGlm[0]);
                CHECK(result[1] == resultGlm[1]);
                CHECK(result[2] == resultGlm[2]);
            }
            {
                lm::FQuat product(1);
                lm::FVec4 const vec{ 1.f, 2.f, 3.f ,4.f };
                lm::FVec4 result = vec * product;

                glm::quat productGlm(0, 1, 1, 1);
                glm::vec4 const vecGlm{ 1.f, 2.f, 3.f ,4.f };
                glm::vec4 resultGlm = vecGlm * productGlm;

                CHECK(result[0] == resultGlm[0]);
                CHECK(result[1] == resultGlm[1]);
                CHECK(result[2] == resultGlm[2]);
                CHECK(result[3] == resultGlm[3]);
            }
        }

        SECTION("Division")
        {
            {
                lm::FQuat quotient = big / 2.f;

                glm::quat quotientGlm = bigGlm / 2.f;

                CHECK_QUAT(quotient, quotientGlm);
            }
        }
    }

    SECTION("Transformation")
    {
        lm::FQuat const origin{ .5f, 2.f , 1.f, 2.5f };
        lm::FQuat const rotation{ 0.5f, 0.5f, 0.5f, 0.5f };

        glm::quat const originGlm{ 2.5f, .5f, 2.f, 1.f };
        glm::quat const rotationGlm{ 0.5f, 0.5f, 0.5f, 0.5f };

        SECTION("Rotate")
        {
            lm::FQuat rotated = rotation * origin;

            glm::quat rotatedGlm = rotationGlm * originGlm;

            CHECK_QUAT(rotated, rotatedGlm);
            SECTION("Around Axis")
            {
                rotated = FQuat::Rotate(origin, lm::FVec3{ 1.f, 0.f, 0.f });

                glm::quat qv = glm::quat(0.f, 1.f, 0.f, 0.f);
                rotatedGlm = originGlm * qv * glm::inverse(originGlm);

                CHECK_QUAT(rotated, rotatedGlm);
            }
            SECTION("Around Quat")
            {
                rotated = FQuat::Rotate(origin, rotation);

                rotatedGlm = originGlm * rotationGlm * glm::inverse(originGlm);

                CHECK_QUAT(rotated, rotatedGlm);
            }
            SECTION("Around Axis and Angle")
            {
                rotated = FQuat::Rotate(origin, lm::FVec3{ 1.f, 0.f, 0.f }, 45.f);

                glm::quat qv = glm::angleAxis(glm::radians(45.f), glm::vec3(1.f, 0.f, 0.f));
                rotatedGlm = originGlm * qv * glm::inverse(originGlm);

                CHECK_QUAT(rotated, rotatedGlm);
            }
        }
    }

    SECTION("Functionality")
    {
        lm::FQuat const base{ .5f, 2.f, 7.f, 2.5f };
        lm::FQuat const other{ 3.f, 2.f, 1.f, 4.f };

        glm::quat const baseGlm{ 2.5f, .5f, 2.f, 7.f };
        glm::quat const otherGlm{ 4.f, 3.f, 2.f, 1.f };

        SECTION("Cross")
        {
            lm::FQuat cross = FQuat::Cross(base, other);

            glm::quat crossGlm = glm::cross(baseGlm, otherGlm);

            CHECK_QUAT(cross, crossGlm);
        }

        SECTION("Dot")
        {
            float dot = FQuat::Dot(base, other);

            float dotGlm = glm::dot(baseGlm, otherGlm);

            CHECK(dot == dotGlm);
        }

        SECTION("Length")
        {
            float length = FQuat::Length(base);

            float lengthGlm = glm::length(baseGlm);

            CHECK(length == lengthGlm);
        }

        SECTION("length2")
        {
            float lengthSquared = FQuat::Length2(base);

            float lengthSquaredGlm = glm::length(baseGlm) * glm::length(baseGlm);

            CHECK(lengthSquared == Catch::Approx(lengthSquaredGlm));
        }

        SECTION("Inverse")
        {
            lm::FQuat inverse = FQuat::Inverse(base);

            glm::quat inverseGlm = glm::inverse(baseGlm);

            CHECK_QUAT(inverse, inverseGlm);
        }

        SECTION("Normalize")
        {
            lm::FQuat normalized = FQuat::Normalize(base);

            glm::quat normalizedGlm = glm::normalize(baseGlm);

            CHECK_QUAT(normalized, normalizedGlm);
        }
        SECTION("IsUnit")
        {
            CHECK_FALSE(base.isUnit());
            lm::FQuat unitaire{ 1,0,0, 0 };
            CHECK(unitaire.isUnit());
        }
        SECTION("Angle")
        {
            lm::FQuat angled{ 1,0,0, 1 };
            glm::quat angledGlm{ 1,0,0, 1 };
            float angle = angled.getAngle();

            float angleGlm = glm::angle(angledGlm);

            CHECK(angle == Catch::Approx(angleGlm));
        }
        SECTION("ToRotateMat3")
        {
            lm::FMat3 mat = FQuat::ToRotateMat3(base);

            glm::mat3 matGlm = glm::mat3_cast(glm::normalize(baseGlm));

            CHECK_MAT3(mat, matGlm);
        }
        SECTION("Lerp")
        {
            lm::FQuat lerp = FQuat::Lerp(base, other, .5f);

            glm::quat lerpGlm = glm::mix(baseGlm, otherGlm, .5f);

            CHECK_QUAT(lerp, lerpGlm);
        }
        SECTION("SLERP")
        {
            lm::FQuat slerp = FQuat::SLerp(base, other, .5f);

            glm::quat slerpGlm = glm::slerp(baseGlm, otherGlm, .5f);

            CHECK_QUAT(slerp, slerpGlm);
        }
        SECTION("NLerp")
        {
            lm::FQuat nlerp = FQuat::NLerp(base, other, .5f);

            glm::quat nlerpGlm = glm::normalize(glm::mix(baseGlm, otherGlm, .5f));

            CHECK_QUAT(nlerp, nlerpGlm);
        }
        SECTION("FromEuler")
        {
            lm::FQuat euler = FQuat::FromEuler(45.f, 45.f, 45.f);

            glm::quat eulerGlm = glm::quat(glm::vec3(glm::radians(45.f), glm::radians(45.f), glm::radians(45.f)));

            CHECK_QUAT(euler, eulerGlm);
        }
    }

    SECTION("Extra")
    {
        SECTION("Serialization")
        {
            lm::FQuat const input{ 1.f, 2.f, 3.f, 4.f };

            std::stringstream buffer;
            buffer << input;
            CHECK(buffer.str() == "FQuat(1, 2, 3, 4)");
        }
    }
}