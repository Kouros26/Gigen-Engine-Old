#include <Vec2/FVec2.hpp>

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

#define CHECK_VECTOR2(Vec, VecGlm) CHECK(Vec.x == Catch::Approx(VecGlm.x)); CHECK(Vec.y == Catch::Approx(VecGlm.y))

TEST_CASE("Vector2", "[.all][vector][Vector2]")
{
	SECTION("Instantiation")
	{
		// default constructor
		lm::FVec2 empty{};
		glm::vec2 emptyGlm{};
		CHECK_VECTOR2(empty, emptyGlm);

		// destructor
		{
			lm::FVec2 temp; (void)temp;
		}

		// basic constructor
		lm::FVec2 oneParam{ 2.5f };
		glm::vec2 oneParamGlm{ 2.5f };
		CHECK_VECTOR2(oneParam, oneParamGlm);

		lm::FVec2 allParam{ 2.5f, .5f };
		glm::vec2 allParamGlm{ 2.5f, .5f };
		CHECK_VECTOR2(allParam, allParamGlm);

		// copy constructor
		lm::FVec2 copy{ allParam };
		glm::vec2 copyGlm{ allParamGlm };
		CHECK_VECTOR2(copy, copyGlm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_VECTOR2(empty, emptyGlm);

		CHECK(sizeof lm::FVec2 == sizeof glm::vec2);

		CHECK(memcmp(&allParam, &allParamGlm, sizeof lm::FVec2) == 0);
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		lm::FVec2 vec{ x, y };
		glm::vec2 vecGlm{ x, y };
		CHECK_VECTOR2(vec, vecGlm);

		CHECK(vec.x == x);
		CHECK(vec.y == y);
		CHECK(vecGlm.x == x);
		CHECK(vecGlm.y == y);

		CHECK(vec[0] == x);
		CHECK(vec[1] == y);
		CHECK(vecGlm[0] == x);
		CHECK(vecGlm[1] == y);
	}

	SECTION("Arithmetic")
	{
		float const x = 2.5f;
		float const y = .5f;
		lm::FVec2 vec{ x, y };
		glm::vec2 vecGlm{ x, y };

		float const x2 = 2.5f;
		float const y2 = .5f;
		lm::FVec2 vec2{ x2, y2 };
		glm::vec2 vec2Glm{ x2, y2 };

		SECTION("Addition")
		{
			vec += vec2;
			vecGlm += vec2Glm;
			CHECK_VECTOR2(vec, vecGlm);
			vec = vec + vec2;
			vecGlm = vecGlm + vec2Glm;
			CHECK_VECTOR2(vec, vecGlm);
		}

		SECTION("Subtraction")
		{
			vec -= vec2;
			vecGlm -= vec2Glm;
			CHECK_VECTOR2(vec, vecGlm);

			vec = vec - vec2;
			vecGlm = vecGlm - vec2Glm;
			CHECK_VECTOR2(vec, vecGlm);
		}
		SECTION("Multiplication")
		{
			vec *= vec2;
			vecGlm *= vec2Glm;
			CHECK_VECTOR2(vec, vecGlm);
		}

		SECTION("Division")
		{
			vec /= vec2;
			vecGlm /= vec2Glm;
			CHECK_VECTOR2(vec, vecGlm);
		}
		SECTION("Scalar multiplication")
		{
			SECTION("Unary minus")
			{
				vec = -vec;
				vecGlm = -vecGlm;
				CHECK_VECTOR2(vec, vecGlm);
			}

			lm::FVec2 mult = lm::FVec2::Multiply(vec, 2.5f);
			glm::vec2 multGlm = glm::vec2(vecGlm * 2.5f);
			CHECK_VECTOR2(mult, multGlm);
		}
	}

	SECTION("Comparison")
	{
		float const x = 2.5f;
		float const y = .5f;
		lm::FVec2 vec{ x, y };
		glm::vec2 vecGlm{ x, y };

		float const x2 = 2.5f;
		float const y2 = .5f;
		lm::FVec2 vec2{ x2, y2 };
		glm::vec2 vec2Glm{ x2, y2 };

		// equality
		CHECK((vec == vec2) == (vecGlm == vec2Glm));
		CHECK((vec != vec2) == (vecGlm != vec2Glm));
	}

	SECTION("Functions")
	{
		float const x = 2.5f;
		float const y = .5f;
		lm::FVec2 vec{ x, y };
		lm::FVec2 vec2{ x, y };
		glm::vec2 vecGlm{ x, y };
		glm::vec2 vec2Glm{ x, y };

		SECTION("Length")
		{
			float length = lm::FVec2::Length(vec);
			float lengthGlm = glm::length(vecGlm);
			CHECK(length == Catch::Approx(lengthGlm));
		}
		SECTION("Normalize")
		{
			vec = FVec2::Normalize(vec);

			vecGlm = glm::normalize(vecGlm);
			CHECK_VECTOR2(vec, vecGlm);
		}

		SECTION("Dot")
		{
			float dot = FVec2::Dot(vec, vec2);
			float dotGlm = glm::dot(vecGlm, vec2Glm);
			CHECK(dot == Catch::Approx(dotGlm));
		}

		SECTION("Angle")
		{
			float angle = FVec2::AngleBetween(vec, vec2);
			float angleGlm = glm::orientedAngle(vecGlm, vec2Glm);
			CHECK(angle == Catch::Approx(angleGlm));
		}

		SECTION("Reflect")
		{
			vec = FVec2::Reflect(vec, vec2);

			vecGlm = glm::reflect(vecGlm, vec2Glm);
			CHECK_VECTOR2(vec, vecGlm);

			lm::FVec2 reflect2 = FVec2::Reflect(lm::FVec2(3.f, 4.f), lm::FVec2(1));
			glm::vec2 reflect2Glm = glm::reflect(glm::vec2(3.f, 4.f), glm::vec2(1));
			CHECK_VECTOR2(reflect2, reflect2Glm);
		}

		SECTION("Clamp")
		{
			FVec2::Clamp(vec, vec2, FVec2(vec2.x + 1.f, vec2.y + 1.f));

			vecGlm = glm::clamp(vecGlm, vec2Glm, glm::vec2(vec2Glm.x + 1, vec2Glm.y + 1));
			CHECK_VECTOR2(vec, vecGlm);
		}

		SECTION("Lerp")
		{
			FVec2::Lerp(vec, vec2, .5f);

			vecGlm = glm::lerp(vecGlm, vec2Glm, .5f);
			CHECK_VECTOR2(vec, vecGlm);
		}

		SECTION("IsUnit")
		{
			bool isUnit = vec.IsUnit();
			bool isUnitGlm = glm::epsilonEqual(glm::length(vecGlm), 1.f, 0.0001f);
			CHECK(isUnit == isUnitGlm);
		}

		SECTION("IsZero")
		{
			bool isZero = vec.IsZero();
			bool isZeroGlm = vecGlm == glm::vec2(0.f);
			CHECK(isZero == isZeroGlm);
		}
	}
}