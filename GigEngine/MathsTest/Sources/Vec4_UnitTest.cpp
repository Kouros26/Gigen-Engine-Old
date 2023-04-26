#include <Vec4/FVec4.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace lm;

#define CHECK_VECTOR4(Vec, VecGlm) CHECK(Vec.x == Catch::Approx(VecGlm.x)); CHECK(Vec.y == Catch::Approx(VecGlm.y)); CHECK(Vec.z == Catch::Approx(VecGlm.z)); CHECK(Vec.w == Catch::Approx(VecGlm.w))

TEST_CASE("Vec4", "[.all][vector][Vec4]")
{
    SECTION("Instantiation")
    {
        // default constructor
        lm::FVec4 empty{};
        glm::vec4 emptyGlm{};
        CHECK_VECTOR4(empty, emptyGlm);

        // destructor
        {
            lm::FVec4 temp;
        }

        // basic constructor
        lm::FVec4 oneParam{ 2.5f };
        glm::vec4 oneParamGlm{ 2.5f };
        CHECK_VECTOR4(oneParam, oneParamGlm);

        lm::FVec4 allParam{ 2.5f, .5f, 2.f, 1.f };
        glm::vec4 allParamGlm{ 2.5f, .5f, 2.f, 1.f };
        CHECK_VECTOR4(allParam, allParamGlm);

        // copy constructor
        lm::FVec4 copy{ allParam };
        glm::vec4 copyGlm{ allParamGlm };
        CHECK_VECTOR4(copy, copyGlm);

        // assignment operator
        empty = allParam;
        emptyGlm = allParamGlm;
        CHECK_VECTOR4(empty, emptyGlm);

        CHECK(sizeof lm::FVec4 == sizeof glm::vec4);

        CHECK(memcmp(&allParam, &allParamGlm, sizeof lm::FVec4) == 0);
    }

    SECTION("Accessor")
    {
        float const x = 2.5f;
        float const y = .5f;
        float const z = 2.f;
        float const w = 1.f;
        lm::FVec4 vec{ x, y, z, w };
        glm::vec4 vecGlm{ x, y, z, w };
        CHECK_VECTOR4(vec, vecGlm);

        CHECK(vec.x == x);
        CHECK(vec.y == y);
        CHECK(vec.z == z);
        CHECK(vec.w == w);

        CHECK(vec[0] == x);
        CHECK(vec[1] == y);
        CHECK(vec[2] == z);
        CHECK(vec[3] == w);
    }
    SECTION("Comparator")
    {
        lm::FVec4 vec{ 2.5f, .5f, 2.f, 1.f };
        glm::vec4 vecGlm{ 2.5f, .5f, 2.f, 1.f };
        CHECK_VECTOR4(vec, vecGlm);

        CHECK(vec == vec);
        CHECK(vecGlm == vecGlm);

        CHECK(vec != lm::FVec4{});
        CHECK(vecGlm != glm::vec4{});

        // compare with same
        // trying to find copy/paste mistake
        lm::FVec4 twos{ 2.f, 2.f, 2.f , 1.f };
        CHECK_FALSE(lm::FVec4{ .5f, 2.f, 2.f , 1.f } == twos);
        CHECK_FALSE(lm::FVec4{ 2, 3, 4 } == twos);
        CHECK_FALSE(twos == lm::FVec4{ 4, 2, 6 });
        CHECK_FALSE(twos == lm::FVec4{ 7, 2, 1, 0 });

        CHECK_FALSE(twos.IsUnit());
        //check if a created vector is unit
        CHECK(lm::FVec4{ 0.2672612419124244f, 0.5345224838248488f, 0.8017837257372732f, 0.0 }.IsUnit());
    }

    SECTION("Constante")
    {
        CHECK_VECTOR4(-lm::FVec4::Forward, glm::vec4(0.f, 0.f, -1.f, 0.f));

        CHECK_VECTOR4(-lm::FVec4::Up, glm::vec4(0.f, -1.f, 0.f, 0.f));

        CHECK_VECTOR4(lm::FVec4::Forward, glm::vec4(0.f, 0.f, 1.f, 0.f));

        CHECK_VECTOR4(-lm::FVec4::Right, glm::vec4(-1.f, 0.f, 0.f, 0.f));

        CHECK_VECTOR4(lm::FVec4::Right, glm::vec4(1.f, 0.f, 0.f, 0.f));

        CHECK_VECTOR4(lm::FVec4::Up, glm::vec4(0.f, 1.f, 0.f, 0.f));

        CHECK_VECTOR4(lm::FVec4::Zero, glm::vec4(0.f, 0.f, 0.f, 0.f));
    }

    SECTION("Arithmetics")
    {
        lm::FVec4 const small{ 2.5f, .5f, 2.f, 1.f };
        lm::FVec4 const big{ 5.f, 1.f, 4.f, 1.f };
        glm::vec4 const smallGlm{ 2.5f, .5f, 2.f, 1.f };
        glm::vec4 const bigGlm{ 5.f, 1.f, 4.f, 1.f };

        SECTION("Addition")
        {
            {
                lm::FVec4 sumAssignement = big;
                sumAssignement += small;
                glm::vec4  sumAssignementGlm = bigGlm;
                sumAssignementGlm += smallGlm;

                CHECK_VECTOR4(sumAssignement, sumAssignementGlm);
            }

            {
                lm::FVec4 sum = big + small;
                glm::vec4 sumGlm = bigGlm + smallGlm;

                CHECK_VECTOR4(sum, sumGlm);

                lm::FVec4 sum2 = small + big;
            }
        }
        SECTION("Inverse")
        {
            lm::FVec4 inverse = -lm::FVec4{ 3.7f, 2.5f, 1.2f, 1.f };
            glm::vec4 inverseGlm = -glm::vec4(3.7f, 2.5f, 1.2f, 1.f);

            CHECK_VECTOR4(inverse, inverseGlm);
        }
        SECTION("Substraction")
        {
            {
                lm::FVec4 subAssignement = big;
                subAssignement -= small;
                glm::vec4 subAssignementGlm = bigGlm;
                subAssignementGlm -= smallGlm;

                CHECK_VECTOR4(subAssignement, subAssignementGlm);
            }

            {
                lm::FVec4 sub = big - small;
                glm::vec4 subGlm = bigGlm - smallGlm;

                CHECK_VECTOR4(sub, subGlm);
            }
        }

        SECTION("Multiplication")
        {
            {
                lm::FVec4 mulAssignement = big;
                mulAssignement *= 2.f;
                glm::vec4 mulAssignementGlm = bigGlm;
                mulAssignementGlm *= 2.f;

                CHECK_VECTOR4(mulAssignement, mulAssignementGlm);
            }

            {
                lm::FVec4 mul = big * 2.f;
                glm::vec4 mulGlm = bigGlm * 2.f;

                CHECK_VECTOR4(mul, mulGlm);
            }

            {
                lm::FVec4 mulAssignement = big;
                mulAssignement *= small;
                glm::vec4 mulAssignementGlm = bigGlm;
                mulAssignementGlm *= smallGlm;

                CHECK_VECTOR4(mulAssignement, mulAssignementGlm);
            }

            {
                lm::FVec4 mul = big * small;
                glm::vec4 mulGlm = bigGlm * smallGlm;

                CHECK_VECTOR4(mul, mulGlm);
            }
        }
        SECTION("Division")
        {
            {
                lm::FVec4 divAssignement = big;
                divAssignement /= 2.f;
                glm::vec4 divAssignementGlm = bigGlm;
                divAssignementGlm /= 2.f;

                CHECK_VECTOR4(divAssignement, divAssignementGlm);
            }

            {
                lm::FVec4 div = big / 2.f;
                glm::vec4 divGlm = bigGlm / 2.f;

                CHECK_VECTOR4(div, divGlm);
            }

            {
                lm::FVec4 divAssignement = big;
                divAssignement /= small;
                glm::vec4 divAssignementGlm = bigGlm;
                divAssignementGlm /= smallGlm;

                CHECK_VECTOR4(divAssignement, divAssignementGlm);
            }

            {
                lm::FVec4 div = big / small;
                glm::vec4 divGlm = bigGlm / smallGlm;

                CHECK_VECTOR4(div, divGlm);
            }
        }
    }

    SECTION("Functionality")
    {
        lm::FVec4 const base{ 2.5f, .5f, 2.f, 1.f };
        lm::FVec4 const other{ 3.75f, 3.f, .75f ,1.f };
        glm::vec4 const baseGlm{ 2.5f, .5f, 2.f, 1.f };
        glm::vec4 const otherGlm{ 3.75f, 3.f, .75f ,1.f };

        SECTION("Dot product")
        {
            float dot = lm::FVec4::Dot(base, other);
            float dotGlm = glm::dot(baseGlm, otherGlm);

            CHECK(dot == dotGlm);
        }

        SECTION("Distance")
        {
            float distance = lm::FVec4::Distance(base, other);
            float distanceGlm = glm::distance(baseGlm, otherGlm);

            CHECK(distance == Catch::Approx(distanceGlm));
        }

        SECTION("Length")
        {
            float length = lm::FVec4::Length(base);
            float lengthGlm = glm::length(baseGlm);

            CHECK(length == Catch::Approx(lengthGlm));
        }

        SECTION("Normalize")
        {
            lm::FVec4 normalized = lm::FVec4::Normalize(base);
            glm::vec4 normalizedGlm = glm::normalize(baseGlm);

            CHECK_VECTOR4(normalized, normalizedGlm);
        }

        SECTION("Lerp")
        {
            lm::FVec4 lerp = lm::FVec4::Lerp(base, other, .5f);
            glm::vec4 lerpGlm = glm::lerp(baseGlm, otherGlm, .5f);

            CHECK_VECTOR4(lerp, lerpGlm);
        }

        SECTION("Projection")
        {
            lm::FVec4 projection = lm::FVec4::Project(base, other);
            glm::vec4 projectionGlm = glm::proj(baseGlm, otherGlm);

            CHECK_VECTOR4(projection, projectionGlm);
        }

        SECTION("Clamp")
        {
            lm::FVec4 clamped = lm::FVec4::Clamp(base, other, other * 2.f);
            glm::vec4 clampedGlm = glm::clamp(baseGlm, otherGlm, otherGlm * 2.f);

            CHECK_VECTOR4(clamped, clampedGlm);
        }

        SECTION("IsZero")
        {
            bool isZero = base.IsZero();

            CHECK(isZero == false);
            CHECK(lm::FVec4::Zero.IsZero() == true);
        }

        SECTION("IsUnit")
        {
            CHECK(base.IsUnit() == false);
            CHECK(lm::FVec4::Forward.IsUnit() == true);
        }
    }
    SECTION("Extra")
    {
        lm::FVec4 const input{ 2.5f, .5f, 2.f, 1.f };

        {
            std::stringstream ss;
            ss << input;

            CHECK(ss.str() == "FVec4(2.5, 0.5, 2, 1)");
        }
    }
}