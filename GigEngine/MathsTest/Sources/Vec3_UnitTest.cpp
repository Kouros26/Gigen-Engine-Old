#include <Vec3/FVec3.hpp>

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

#define CHECK_VECTOR3(Vec, VecGlm) CHECK(Vec.x == Catch::Approx(VecGlm.x)); CHECK(Vec.y == Catch::Approx(VecGlm.y)); CHECK(Vec.z == Catch::Approx(VecGlm.z))

TEST_CASE("Vector3", "[.all][vector][Vector3][float]")
{
	SECTION("Instantiation")
	{
		// default constructor
		lm::FVec3 empty{};
		glm::vec3 emptyGlm{};
		CHECK_VECTOR3(empty, emptyGlm);

		// destructor
		{
			lm::FVec3 temp;
		}

		// basic constructor
		lm::FVec3 oneParam{ 2.5f };
		glm::vec3 oneParamGlm{ 2.5f };
		CHECK_VECTOR3(oneParam, oneParamGlm);

		lm::FVec3 allParam{ 2.5f, .5f, 2.f };
		glm::vec3 allParamGlm{ 2.5f, .5f, 2.f };
		CHECK_VECTOR3(allParam, allParamGlm);

		// copy constructor
		lm::FVec3 copy{ allParam };
		glm::vec3 copyGlm{ allParamGlm };
		CHECK_VECTOR3(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR3(empty, emptyGlm);

		CHECK(sizeof lm::FVec3 == sizeof glm::vec3);

		CHECK(memcmp(&allParam, &allParamGlm, sizeof lm::FVec3) == 0);
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		float const z = 2.f;
		lm::FVec3 quaternion{ x, y, z };

		{
			lm::FVec3 const& vectorConst = quaternion;
			CHECK(vectorConst[0] == x);
			CHECK(vectorConst[1] == y);
			CHECK(vectorConst[2] == z);
		}

		{
			quaternion[0] += 1.f;
			quaternion[1] += 1.f;
			quaternion[2] += 1.f;
			CHECK(quaternion[0] == x + 1.f);
			CHECK(quaternion[1] == y + 1.f);
			CHECK(quaternion[2] == z + 1.f);
		}
	}

	SECTION("Comparator")
	{
		// compare with self
		lm::FVec3 self{ 2.5f, .5f, 2.f };
		CHECK(self == self);

		// compare with same
		CHECK(lm::FVec3{ 2.5f, .5f, 2.f } == lm::FVec3{ 2.5f, .5f, 2.f });

		// trying to find copy/paste mistake
		lm::FVec3 twos{ 2.f, 2.f, 2.f };
		CHECK_FALSE(lm::FVec3{ .5f, 2.f, 2.f } == twos);
		CHECK_FALSE(lm::FVec3{ 2.f, .5f, 2.f } == twos);
		CHECK_FALSE(lm::FVec3{ 2.f, 2.f, .5f } == twos);
		CHECK_FALSE(twos == lm::FVec3{ .5f, 2.f, 2.f });
		CHECK_FALSE(twos == lm::FVec3{ 2.f, .5f, 2.f });
		CHECK_FALSE(twos == lm::FVec3{ 2.f, 2.f, .5f });

		CHECK_FALSE(self.IsUnit());
		CHECK(lm::FVec3{ 0.771516740f, 0.154303357f, 0.617213428f }.IsUnit());
	}

	SECTION("Constant")
	{
		CHECK_VECTOR3(-lm::FVec3::Forward, glm::vec3(0.f, 0.f, -1.f));

		CHECK_VECTOR3(-lm::FVec3::Up, glm::vec3(0.f, -1.f, 0.f));

		CHECK_VECTOR3(lm::FVec3::Forward, glm::vec3(0.f, 0.f, 1.f));

		CHECK_VECTOR3(-lm::FVec3::Right, glm::vec3(-1.f, 0.f, 0.f));

		CHECK_VECTOR3(lm::FVec3::Right, glm::vec3(1.f, 0.f, 0.f));

		CHECK_VECTOR3(lm::FVec3::Up, glm::vec3(0.f, 1.f, 0.f));

		CHECK_VECTOR3(lm::FVec3::Zero, glm::vec3(0.f, 0.f, 0.f));
	}

	SECTION("Arithmetic")
	{
		lm::FVec3 const small{ 2.5f, .5f, 2.f };
		lm::FVec3 const big{ 3.75f, 3.f, .75f };

		glm::vec3 const smallGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const bigGlm{ 3.75f, 3.f, .75f };

		SECTION("Addition")
		{
			{
				lm::FVec3 sumAssignment = big;
				sumAssignment += small;

				glm::vec3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_VECTOR3(sumAssignment, sumAssignmentGlm);
			}

			{
				lm::FVec3 sum = big + small;

				glm::vec3 sumGlm = bigGlm + smallGlm;

				CHECK_VECTOR3(sum, sumGlm);
			}
		}

		SECTION("Inverse")
		{
			lm::FVec3 inverse = -lm::FVec3{ 3.7f, 3.f, .7f };

			glm::vec3 inverseGlm = -glm::vec3{ 3.7f, 3.f, .7f };

			CHECK_VECTOR3(inverse, inverseGlm);
		}

		SECTION("Substraction")
		{
			{
				lm::FVec3 differenceAssignment = big;
				differenceAssignment -= small;

				glm::vec3 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_VECTOR3(differenceAssignment, differenceAssignmentGlm);
			}

			{
				lm::FVec3 difference = big - small;

				glm::vec3 differenceGlm = bigGlm - smallGlm;

				CHECK_VECTOR3(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				lm::FVec3 productAssignment = big;
				productAssignment *= small;

				glm::vec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}

            {
                lm::FVec3 productAssignment = big;
                productAssignment *= 2.f;

				glm::vec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= 2.f;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);

				productAssignment = big * 2.f;

				productAssignmentGlm = bigGlm * 2.f;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}
		}

		SECTION("Division")
		{
			{
				lm::FVec3 quotientAssignment = big;
				quotientAssignment /= small;

				glm::vec3 quotientAssignmentGlm = bigGlm;
				quotientAssignmentGlm /= smallGlm;

                CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
            }
        }
    }

	SECTION("Functionality")
	{
		lm::FVec3 const base{ 2.5f, .5f, 2.f };
		lm::FVec3 const other{ 3.75f, 3.f, .75f };

		glm::vec3 const baseGlm{ 2.5f, .5f, 2.f };
		glm::vec3 const otherGlm{ 3.75f, 3.f, .75f };

		SECTION("Cross")
		{
			lm::FVec3 cross = FVec3::Cross(base, other);

			glm::vec3 crossGlm = glm::cross(baseGlm, otherGlm);

			CHECK_VECTOR3(cross, crossGlm);
		}

		SECTION("Dot")
		{
			float dot = FVec3::Dot(base, other);

			float dotGlm = glm::dot(baseGlm, otherGlm);

			CHECK(dot == dotGlm);
		}

		SECTION("Distance")
		{
			{
				float distance = FVec3::Distance(base, other);

				float distanceGlm = glm::distance(baseGlm, otherGlm);

				CHECK(distance == Catch::Approx(distanceGlm));
			}
		}

		SECTION("Magnitude")
		{
			{
				float magnitude = FVec3::Length(base);

				float magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				float magnitudeSquare = FVec3::Length2(base);

				float magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		SECTION("Normal")
		{
			lm::FVec3 normalize = FVec3::Normalize(base);

			glm::vec3 normalizeGlm = glm::normalize(baseGlm);

			CHECK_VECTOR3(normalize, normalizeGlm);
		}

		SECTION("ProjectOnto")
		{
			lm::FVec3 project = FVec3::Project(base, other);

			glm::vec3 projectGlm = glm::proj(baseGlm, otherGlm);

			CHECK_VECTOR3(project, projectGlm);
		}

		SECTION("ReflectOnto")
		{
			lm::FVec3 reflect = FVec3::Reflect(base, FVec3::Normalize(other));

			glm::vec3 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

            CHECK_VECTOR3(reflect, reflectGlm);


           
        }

		SECTION("Refract")
		{
			lm::FVec3 refract = FVec3::Refract(base, FVec3::Normalize(other), .5f);

			glm::vec3 refractGlm = glm::refract(baseGlm, glm::normalize(otherGlm), .5f);

			CHECK_VECTOR3(refract, refractGlm);
		}

		SECTION("Angle")
		{
			float angle = FVec3::AngleBetween(base, other);

			float angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

			CHECK(angle == Catch::Approx(angleGlm));
		}

		SECTION("Lerp")
		{
			lm::FVec3 lerp = FVec3::Lerp(base, other, .5f);

			glm::vec3 lerpGlm = glm::lerp(baseGlm, otherGlm, .5f);

			CHECK_VECTOR3(lerp, lerpGlm);
		}

		SECTION("Clamp")
		{
			lm::FVec3 clamp = FVec3::Clamp(base, other, other * 2.f);

			glm::vec3 clampGlm = glm::clamp(baseGlm, otherGlm, otherGlm * 2.f);

			CHECK_VECTOR3(clamp, clampGlm);
		}

		SECTION("IsZero")
		{
			CHECK_FALSE(base.IsZero());
			CHECK(lm::FVec3::Zero.IsZero() == true);
		}

		SECTION("IsUnit")
		{
			CHECK_FALSE(base.IsUnit());
			CHECK(lm::FVec3(1.f, 0.f, 0.f).IsUnit() == true);
		}
	}

	SECTION("Extra")
	{
		lm::FVec3 const input{ 2.5f, -.5f, 2.f };
		{
			std::stringstream buffer;

			buffer << input;

            CHECK(buffer.str() == "FVec3(2.5, -0.5, 2)");
        }
    }

}