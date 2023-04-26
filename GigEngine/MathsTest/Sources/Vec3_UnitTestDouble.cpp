#include <vec3/DVec3.hpp>

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

TEST_CASE("Vector3", "[.all][vector][Vector3][double]")
{
	SECTION("Instantiation")
	{
		// default constructor
		lm::DVec3 empty{};
		glm::dvec3 emptyGlm{};
		CHECK_VECTOR3(empty, emptyGlm);

		// destructor
		{
			lm::DVec3 temp;
		}

		// basic constructor
		lm::DVec3 oneParam{ 2.5f };
		glm::dvec3 oneParamGlm{ 2.5f };
		CHECK_VECTOR3(oneParam, oneParamGlm);

		lm::DVec3 allParam{ 2.5f, .5f, 2.f };
		glm::dvec3 allParamGlm{ 2.5f, .5f, 2.f };
		CHECK_VECTOR3(allParam, allParamGlm);

		// copy constructor
		lm::DVec3 copy{ allParam };
		glm::dvec3 copyGlm{ allParamGlm };
		CHECK_VECTOR3(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR3(empty, emptyGlm);

		CHECK(sizeof lm::DVec3 == sizeof glm::dvec3);

		CHECK(memcmp(&allParam, &allParamGlm, sizeof lm::DVec3) == 0);
	}

	SECTION("Accessor")
	{
		double const x = 2.5f;
		double const y = .5f;
		double const z = 2.f;
		lm::DVec3 quaternion{ x, y, z };

		{
			lm::DVec3 const& vectorConst = quaternion;
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
		lm::DVec3 self{ 2.5f, .5f, 2.f };
		CHECK(self == self);

		// compare with same
		CHECK(lm::DVec3{ 2.5f, .5f, 2.f } == lm::DVec3{ 2.5f, .5f, 2.f });

		// trying to find copy/paste mistake
		lm::DVec3 twos{ 2.f, 2.f, 2.f };
		CHECK_FALSE(lm::DVec3{ .5f, 2.f, 2.f } == twos);
		CHECK_FALSE(lm::DVec3{ 2.f, .5f, 2.f } == twos);
		CHECK_FALSE(lm::DVec3{ 2.f, 2.f, .5f } == twos);
		CHECK_FALSE(twos == lm::DVec3{ .5f, 2.f, 2.f });
		CHECK_FALSE(twos == lm::DVec3{ 2.f, .5f, 2.f });
		CHECK_FALSE(twos == lm::DVec3{ 2.f, 2.f, .5f });

		CHECK_FALSE(self.IsUnit());
		lm::DVec3 unit{ 0.2672612419124244, 0.5345224838248488, 0.8017837257372732 };
		CHECK(unit.IsUnit());
	}

	SECTION("Constant")
	{
		CHECK_VECTOR3(-lm::DVec3::Forward, glm::dvec3(0.f, 0.f, -1.f));

		CHECK_VECTOR3(-lm::DVec3::Up, glm::dvec3(0.f, -1.f, 0.f));

		CHECK_VECTOR3(lm::DVec3::Forward, glm::dvec3(0.f, 0.f, 1.f));

		CHECK_VECTOR3(-lm::DVec3::Right, glm::dvec3(-1.f, 0.f, 0.f));

		CHECK_VECTOR3(lm::DVec3::Right, glm::dvec3(1.f, 0.f, 0.f));

		CHECK_VECTOR3(lm::DVec3::Up, glm::dvec3(0.f, 1.f, 0.f));

		CHECK_VECTOR3(lm::DVec3::Zero, glm::dvec3(0.f, 0.f, 0.f));
	}

	SECTION("Arithmetic")
	{
		lm::DVec3 const small{ 2.5f, .5f, 2.f };
		lm::DVec3 const big{ 3.75f, 3.f, .75f };

		glm::dvec3 const smallGlm{ 2.5f, .5f, 2.f };
		glm::dvec3 const bigGlm{ 3.75f, 3.f, .75f };

		SECTION("Addition")
		{
			{
				lm::DVec3 sumAssignment = big;
				sumAssignment += small;

				glm::dvec3 sumAssignmentGlm = bigGlm;
				sumAssignmentGlm += smallGlm;

				CHECK_VECTOR3(sumAssignment, sumAssignmentGlm);
			}

			{
				lm::DVec3 sum = big + small;

				glm::dvec3 sumGlm = bigGlm + smallGlm;

				CHECK_VECTOR3(sum, sumGlm);
			}
		}

		SECTION("Inverse")
		{
			lm::DVec3 inverse = -lm::DVec3{ 3.7f, 3.f, .7f };

			glm::dvec3 inverseGlm = -glm::dvec3{ 3.7f, 3.f, .7f };

			CHECK_VECTOR3(inverse, inverseGlm);
		}

		SECTION("Substraction")
		{
			{
				lm::DVec3 differenceAssignment = big;
				differenceAssignment -= small;

				glm::dvec3 differenceAssignmentGlm = bigGlm;
				differenceAssignmentGlm -= smallGlm;

				CHECK_VECTOR3(differenceAssignment, differenceAssignmentGlm);
			}

			{
				lm::DVec3 difference = big - small;

				glm::dvec3 differenceGlm = bigGlm - smallGlm;

				CHECK_VECTOR3(difference, differenceGlm);
			}
		}

		SECTION("Multiplication")
		{
			{
				lm::DVec3 productAssignment = big;
				productAssignment *= small;

				glm::dvec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= smallGlm;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}

			{
				lm::DVec3 product = big * small;

				glm::dvec3 productGlm = bigGlm * smallGlm;

				CHECK_VECTOR3(product, productGlm);
			}

			{
				lm::DVec3 productAssignment = big;
				productAssignment *= 2.f;

				glm::dvec3 productAssignmentGlm = bigGlm;
				productAssignmentGlm *= 2.f;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);

				productAssignment = big * 2.f;

				productAssignmentGlm = bigGlm * 2.0;

				CHECK_VECTOR3(productAssignment, productAssignmentGlm);
			}
		}

		SECTION("Division")
		{
			{
				lm::DVec3 quotientAssignment = big;
				quotientAssignment /= small;

				glm::dvec3 quotientAssignmentGlm = bigGlm;
				quotientAssignmentGlm /= smallGlm;

				CHECK_VECTOR3(quotientAssignment, quotientAssignmentGlm);
			}

			{
				lm::DVec3 quotient = big / small;

				glm::dvec3 quotientGlm = bigGlm / smallGlm;

				CHECK_VECTOR3(quotient, quotientGlm);
			}
		}
	}

	SECTION("Functionality")
	{
		lm::DVec3 const base{ 2.5f, .5f, 2.f };
		lm::DVec3 const other{ 3.75f, 3.f, .75f };

		glm::dvec3 const baseGlm{ 2.5f, .5f, 2.f };
		glm::dvec3 const otherGlm{ 3.75f, 3.f, .75f };

		SECTION("Cross")
		{
			lm::DVec3 cross = DVec3::Cross(base, other);

			glm::dvec3 crossGlm = glm::cross(baseGlm, otherGlm);

			CHECK_VECTOR3(cross, crossGlm);
		}

		SECTION("Dot")
		{
			double dot = DVec3::Dot(base, other);

			double dotGlm = glm::dot(baseGlm, otherGlm);

			CHECK(dot == dotGlm);
		}

		SECTION("Distance")
		{
			{
				double distance = DVec3::Distance(base, other);

				double distanceGlm = glm::distance(baseGlm, otherGlm);

				CHECK(distance == Catch::Approx(distanceGlm));
			}
		}

		SECTION("Magnitude")
		{
			{
				double magnitude = DVec3::Length(base);

				double magnitudeGlm = glm::length(baseGlm);

				CHECK(magnitude == Catch::Approx(magnitudeGlm));
			}

			{
				double magnitudeSquare = DVec3::Length2(base);

				double magnitudeSquareGlm = glm::length2(baseGlm);

				CHECK(magnitudeSquare == Catch::Approx(magnitudeSquareGlm));
			}
		}

		SECTION("Normal")
		{
			lm::DVec3 normalize = DVec3::Normalize(base);

			glm::dvec3 normalizeGlm = glm::normalize(baseGlm);

			CHECK_VECTOR3(normalize, normalizeGlm);
		}

		SECTION("ProjectOnto")
		{
			lm::DVec3 project = DVec3::Project(base, other);

			glm::dvec3 projectGlm = glm::proj(baseGlm, otherGlm);

			CHECK_VECTOR3(project, projectGlm);
		}

		SECTION("ReflectOnto")
		{
			lm::DVec3 reflect = DVec3::Reflect(base, DVec3::Normalize(other));

			glm::dvec3 reflectGlm = glm::reflect(baseGlm, glm::normalize(otherGlm));

			CHECK_VECTOR3(reflect, reflectGlm);
		}

		SECTION("Refract")
		{
			lm::DVec3 refract = DVec3::Refract(base, DVec3::Normalize(other), .5f);

			glm::dvec3 refractGlm = glm::refract(baseGlm, glm::normalize(otherGlm), 0.5);

			CHECK_VECTOR3(refract, refractGlm);
		}

		SECTION("Angle")
		{
			double angle = DVec3::AngleBetween(base, other);

			double angleGlm = glm::angle(glm::normalize(baseGlm), glm::normalize(otherGlm));

			CHECK(angle == Catch::Approx(angleGlm));
		}

		SECTION("Lerp")
		{
			lm::DVec3 lerp = DVec3::Lerp(base, other, .5f);

			glm::dvec3 lerpGlm = glm::lerp(baseGlm, otherGlm, 0.5);

			CHECK_VECTOR3(lerp, lerpGlm);
		}

		SECTION("Clamp")
		{
			lm::DVec3 clamp = DVec3::Clamp(base, other, other * 2.f);

			glm::dvec3 clampGlm = glm::clamp(baseGlm, otherGlm, otherGlm * 2.0);

			CHECK_VECTOR3(clamp, clampGlm);
		}

		SECTION("IsZero")
		{
			CHECK_FALSE(base.IsZero());
			CHECK(lm::DVec3::Zero.IsZero() == true);
		}

		SECTION("IsUnit")
		{
			CHECK_FALSE(base.IsUnit());
			CHECK(lm::DVec3(1.f, 0.f, 0.f).IsUnit() == true);
		}
	}

	SECTION("Extra")
	{
		lm::DVec3 const input{ 2.5f, -.5f, 2.f };
		{
			std::stringstream buffer;

			buffer << input;

			CHECK(buffer.str() == "DVec3(2.5, -0.5, 2)");
		}
	}
}