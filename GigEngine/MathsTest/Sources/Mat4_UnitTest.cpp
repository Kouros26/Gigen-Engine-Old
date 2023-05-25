#include <Mat4/FMat4.hpp>
#include <Quaternion/FQuat.hpp>
#include <Mat3/FMat3.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "Vec3/FVec3.hpp"
#include "glm/gtx/matrix_decompose.hpp"

using namespace lm;

#define CHECK_MAT4(Mat,GlmMat) \
CHECK(Mat[0][0] == Catch::Approx(GlmMat[0][0])); \
CHECK(Mat[0][1] == Catch::Approx(GlmMat[0][1])); \
CHECK(Mat[0][2] == Catch::Approx(GlmMat[0][2])); \
CHECK(Mat[0][3] == Catch::Approx(GlmMat[0][3])); \
CHECK(Mat[1][0] == Catch::Approx(GlmMat[1][0])); \
CHECK(Mat[1][1] == Catch::Approx(GlmMat[1][1])); \
CHECK(Mat[1][2] == Catch::Approx(GlmMat[1][2])); \
CHECK(Mat[1][3] == Catch::Approx(GlmMat[1][3])); \
CHECK(Mat[2][0] == Catch::Approx(GlmMat[2][0])); \
CHECK(Mat[2][1] == Catch::Approx(GlmMat[2][1])); \
CHECK(Mat[2][2] == Catch::Approx(GlmMat[2][2])); \
CHECK(Mat[2][3] == Catch::Approx(GlmMat[2][3])); \
CHECK(Mat[3][0] == Catch::Approx(GlmMat[3][0])); \
CHECK(Mat[3][1] == Catch::Approx(GlmMat[3][1])); \
CHECK(Mat[3][2] == Catch::Approx(GlmMat[3][2])); \
CHECK(Mat[3][3] == Catch::Approx(GlmMat[3][3]));

#define CHECK_VECTOR3(Vec, VecGlm)\
 CHECK(Vec.x == Catch::Approx(VecGlm.x));\
 CHECK(Vec.y == Catch::Approx(VecGlm.y));\
 CHECK(Vec.z == Catch::Approx(VecGlm.z))

TEST_CASE("Mat4", "[.all][matrice][Mat4]")
{
	SECTION("Instantiation")
	{
		// default constructor
		lm::FMat4 empty{};
		glm::mat4 emptyGlm{};
		CHECK_MAT4(empty, emptyGlm);

		// destructor
		{
			lm::FMat4 temp;
		}

		// basic constructor
		lm::FMat4 oneParam{ 2.5f };
		glm::mat4 oneParamGlm{ 2.5f };
		CHECK_MAT4(oneParam, oneParamGlm);

		lm::FMat4 allParam{ 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f };
		glm::mat4 allParamGlm{ 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f };
		CHECK_MAT4(allParam, allParamGlm);

		// copy constructor
		lm::FMat4 copy{ allParam };
		glm::mat4 copyGlm{ allParamGlm };
		CHECK_MAT4(copy, copyGlm);

		//from pos and quat
		lm::FMat4 fromPosQuat{ lm::FVec3{ 2.5f, .5f, 2.f }, lm::FQuat{ 1.f, 2.f, 3.f, 4.f } };
		glm::mat4 fromPosQuatGlm{ glm::toMat4(glm::normalize(glm::quat{4.f, 1.f,2.f,3.f})) };
		fromPosQuatGlm = glm::translate(fromPosQuatGlm, glm::vec3{ 2.5f, .5f, 2.f });
		CHECK_MAT4(fromPosQuat, fromPosQuatGlm);

		//Vec4
		lm::FMat4 fromVec4{ lm::FVec4{ 2.5f, .5f, 2.f, 1.f }, lm::FVec4{ 2.5f, .5f, 2.f, 1.f }, lm::FVec4{ 2.5f, .5f, 2.f, 1.f }, lm::FVec4{ 2.5f, .5f, 2.f, 1.f } };
		glm::mat4 fromVec4Glm{ glm::vec4{ 2.5f, .5f, 2.f, 1.f }, glm::vec4{ 2.5f, .5f, 2.f, 1.f }, glm::vec4{ 2.5f, .5f, 2.f, 1.f }, glm::vec4{ 2.5f, .5f, 2.f, 1.f } };
		CHECK_MAT4(fromVec4, fromVec4Glm);

		//Mat3
		lm::FMat4 fromMat3{ lm::FMat3{ 2.5f, .5f, 2.f, 2.5f, .5f, 2.f, 2.5f, .5f, 2.f } };
		glm::mat4 fromMat3Glm{ glm::mat3{ 2.5f, .5f, 2.f, 2.5f, .5f, 2.f, 2.5f, .5f, 2.f } };
		CHECK_MAT4(fromMat3, fromMat3Glm);

		// assignment operator
		empty = allParam;
		emptyGlm = allParamGlm;
		CHECK_MAT4(empty, emptyGlm);

		//assign from Mat3
		empty = lm::FMat3{ 2.5f, .5f, 2.f, 2.5f, .5f, 2.f, 2.5f, .5f, 2.f };
		emptyGlm = glm::mat3{ 2.5f, .5f, 2.f, 2.5f, .5f, 2.f, 2.5f, .5f, 2.f };
		CHECK_MAT4(empty, emptyGlm);

		// vector constructor
		lm::FMat4 vecParam{ lm::FVec4{ 2.5f, .5f, 2.f, 1.f }, lm::FVec4{ 2.5f, .5f, 2.f, 1.f }, lm::FVec4{ 2.5f, .5f, 2.f, 1.f }, lm::FVec4{ 2.5f, .5f, 2.f, 1.f } };
		glm::mat4 vecParamGlm{ glm::vec4{ 2.5f, .5f, 2.f, 1.f }, glm::vec4{ 2.5f, .5f, 2.f, 1.f }, glm::vec4{ 2.5f, .5f, 2.f, 1.f }, glm::vec4{ 2.5f, .5f, 2.f, 1.f } };
		CHECK_MAT4(vecParam, vecParamGlm);

		CHECK(sizeof lm::FMat4 == sizeof glm::mat4);

		CHECK(memcmp(&allParam, &allParamGlm, sizeof lm::FMat4) == 0);
	}

	SECTION("Accessor")
	{
		float const x = 2.5f;
		float const y = .5f;
		float const z = 2.f;
		float const w = 1.f;

		lm::FMat4 mat{ x, y, z, w, x, y, z, w, x, y, z, w, x, y, z, w };
		glm::mat4 matGlm{ x, y, z, w, x, y, z ,w, x, y, z, w, x, y, z, w };

		CHECK(mat[0][0] == x);
		CHECK(mat[0][1] == y);
		CHECK(mat[0][2] == z);
		CHECK(mat[0][3] == w);
		CHECK(mat[1][0] == x);
		CHECK(mat[1][1] == y);
		CHECK(mat[1][2] == z);
		CHECK(mat[1][3] == w);
		CHECK(mat[2][0] == x);
		CHECK(mat[2][1] == y);
		CHECK(mat[2][2] == z);
		CHECK(mat[2][3] == w);
		CHECK(mat[3][0] == x);
		CHECK(mat[3][1] == y);
		CHECK(mat[3][2] == z);
		CHECK(mat[3][3] == w);

		CHECK_MAT4(mat, matGlm);
	}

	SECTION("Comparator")
	{
		lm::FMat4 mat{ 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f };

		CHECK(mat == mat);
		CHECK(mat != lm::FMat4::Identity());
	}

	SECTION("Arithmetics")
	{
		lm::FMat4 const mat{ 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f };
		glm::mat4 const matGlm{ 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f };

		lm::FMat4 const mat2{ 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f };
		glm::mat4 const mat2Glm{ 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f, 2.5f, .5f, 2.f, 1.f };
		SECTION("Multiplication")
		{
			FMat4 Multiplication = mat * mat2;
			glm::mat4 MultiplicationGlm = matGlm * mat2Glm;
			CHECK_MAT4(Multiplication, MultiplicationGlm);

			Multiplication *= mat2;
			MultiplicationGlm *= mat2Glm;
			CHECK_MAT4(Multiplication, MultiplicationGlm);

			FMat4 Multiplication2 = mat2 * mat;
			glm::mat4 Multiplication2Glm = mat2Glm * matGlm;
			CHECK_MAT4(Multiplication2, Multiplication2Glm);

			CHECK_MAT4(2.f * mat, 2.f * matGlm);

			lm::FVec3 const vec{ 1.5f,0.5f,1.f };

			lm::FVec3 result = mat * vec;
			CHECK(result.x == Catch::Approx(2.5));
			CHECK(result.y == Catch::Approx(0.5));
			CHECK(result.z == Catch::Approx(2));

			lm::FVec4 result2 = mat * FVec4(vec);
			CHECK(result2.x == Catch::Approx(10));
			CHECK(result2.y == Catch::Approx(2));
			CHECK(result2.z == Catch::Approx(8));
		}
		SECTION("Unary Minus")
		{
			CHECK_MAT4(-mat, -matGlm);
		}

		SECTION("Addition")
		{
			lm::FMat4 Addition = mat + mat2;
			glm::mat4 AdditionGlm = matGlm + mat2Glm;
			CHECK_MAT4(Addition, AdditionGlm);

			Addition += mat2;
			AdditionGlm += mat2Glm;
			CHECK_MAT4(Addition, AdditionGlm);
		}
		SECTION("Substract")
		{
			lm::FMat4 Substract = mat - mat2;
			glm::mat4 SubstractGlm = matGlm - mat2Glm;
			CHECK_MAT4(Substract, SubstractGlm);

			Substract -= mat2;
			SubstractGlm -= mat2Glm;
			CHECK_MAT4(Substract, SubstractGlm);
		}
		SECTION("Scalar division")
		{
			lm::FMat4 Division = mat / 2.f;
			glm::mat4 DivisionGlm = matGlm / 2.f;
			CHECK_MAT4(Division, DivisionGlm);

			Division /= 2.f;
			DivisionGlm /= 2.f;
			CHECK_MAT4(Division, DivisionGlm);
		}
	}

	SECTION("Functionality")
	{
		lm::FMat4 const mat{ 1,0,0,1,0,2,1,2,2,1,0,1,2,0,1,4 };
		glm::mat4 const matGlm{ 1,0,0,1,0,2,1,2,2,1,0,1,2,0,1,4 };

		SECTION("IsOrthogonal")
		{
			lm::FMat4 ortho{ FVec4(0,0,0,1), FVec4(0,0,1,0), FVec4(1,0,0,0), FVec4(0,1,0,0) };
			glm::mat4 orthoGlm{ glm::vec4(0,0,0,1), glm::vec4(0,0,1,0), glm::vec4(1,0,0,0), glm::vec4(0,1,0,0) };
			CHECK(ortho.IsOrthogonal());
			SECTION("Inverse from ortho")
			{
				CHECK_MAT4(FMat4::InverseOrtho(ortho), FMat4::Inverse(ortho));
			}
		}

		SECTION("Transpose")
		{
			CHECK_MAT4(FMat4::Transpose(mat), glm::transpose(matGlm));
		}

		SECTION("Inverse")
		{
			CHECK_MAT4(FMat4::Inverse(mat), glm::inverse(matGlm));
		}

		SECTION("Identity")
		{
			CHECK_MAT4(FMat4::Identity(), glm::mat4(1.f));
		}

		SECTION("Translation")
		{
			FMat4 translateMat = FMat4::Translation(FVec3{ 2.f, 3.f, 4.f });
			glm::mat4 translateMatGlm = glm::translate(glm::mat4(1.f), glm::vec3(2.f, 3.f, 4.f));
			CHECK_MAT4(translateMat, translateMatGlm);
		}

		SECTION("Rotate")
		{
			SECTION("Axis Angle")
			{
				FMat4 rotateMat = FMat4::Rotate(FMat4::Identity(), 0.5f, FVec3(2, 3, 4));
				glm::mat4 rotateMatGlm = glm::rotate(glm::mat4(1.f), glm::radians(0.5f), glm::vec3(2.f, 3.f, 4.f));
				CHECK_MAT4(rotateMat, rotateMatGlm);
			}
			SECTION("Euler Angle")
			{
				FVec3 rot(0.5f, 0.6f, 0.7f);
				FMat4 rotateMat2 = FMat4::Rotate(FMat4::Identity(), rot);
				glm::mat4 rotateMat2Glm = glm::eulerAngleYXZ(0.5f, 0.6f, 0.7f);
				CHECK_MAT4(rotateMat2, rotateMat2Glm);

				SECTION("XYZEuler")
				{
					FMat4 rotateMat3 = FMat4::RotationEuler(rot);
					glm::mat4 rotateMat3Glm = glm::eulerAngleXYZ(0.5f, 0.6f, 0.7f);

					CHECK_MAT4(rotateMat3, rotateMat3Glm);
				}
				SECTION("YXZEuler")
				{
					FMat4 rotateMAt4 = FMat4::YXZRotation(rot);
					glm::mat4 rotateMat4Glm = glm::eulerAngleYXZ(0.5f, 0.6f, 0.7f);

					CHECK_MAT4(rotateMAt4, rotateMat4Glm);
				}
			}
			SECTION("RotationX")
			{
				FMat4 rotateMat2 = FMat4::XRotation(0.5f);
				glm::mat4 rotateMat2Glm = glm::rotate(glm::mat4(1.f), glm::radians(0.5f), glm::vec3(1.f, 0.f, 0.f));
				CHECK_MAT4(rotateMat2, rotateMat2Glm);

				FMat4 rotateMat3 = FMat4::XRotation(rotateMat2, 0.5f);
				glm::mat4 rotateMat3Glm = glm::rotate(rotateMat2Glm, glm::radians(0.5f), glm::vec3(1.f, 0.f, 0.f));
				CHECK_MAT4(rotateMat3, rotateMat3Glm);
			}
			SECTION("RotationY")
			{
				FMat4 rotateMat2 = FMat4::YRotation(0.5f);
				glm::mat4 rotateMat2Glm = glm::rotate(glm::mat4(1.f), glm::radians(0.5f), glm::vec3(0.f, 1.f, 0.f));
				CHECK_MAT4(rotateMat2, rotateMat2Glm);

				FMat4 rotateMat3 = FMat4::YRotation(rotateMat2, 0.5f);
				glm::mat4 rotateMat3Glm = glm::rotate(rotateMat2Glm, glm::radians(0.5f), glm::vec3(0.f, 1.f, 0.f));
				CHECK_MAT4(rotateMat3, rotateMat3Glm);
			}
			SECTION("RotationZ")
			{
				FMat4 rotateMat2 = FMat4::ZRotation(0.5f);
				glm::mat4 rotateMat2Glm = glm::rotate(glm::mat4(1.f), glm::radians(0.5f), glm::vec3(0.f, 0.f, 1.f));
				CHECK_MAT4(rotateMat2, rotateMat2Glm);

				FMat4 rotateMat3 = FMat4::ZRotation(rotateMat2, 0.5f);
				glm::mat4 rotateMat3Glm = glm::rotate(rotateMat2Glm, glm::radians(0.5f), glm::vec3(0.f, 0.f, 1.f));
				CHECK_MAT4(rotateMat3, rotateMat3Glm);
			}
		}

		SECTION("Scale")
		{
			FMat4 scaleMat = FMat4::Scale(FVec3{ 2.f, 3.f, 4.f });
			glm::mat4 scaleMatGlm = glm::scale(glm::mat4(1.f), glm::vec3(2.f, 3.f, 4.f));
			CHECK_MAT4(scaleMat, scaleMatGlm);
		}

		SECTION("Orthographic")
		{
			FMat4 orthoMat = FMat4::Orthographic(2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
			glm::mat4 orthoMatGlm = glm::ortho(2.f, 3.f, 4.f, 5.f, 6.f, 7.f);
			CHECK_MAT4(orthoMat, orthoMatGlm);
		}

		SECTION("Perspective")
		{
			FMat4 perspectiveMat = FMat4::Perspective(2.f, 3.f, 4.f, 5.f);
			glm::mat4 perspectiveMatGlm = glm::perspective(glm::radians(2.f), 3.f, 4.f, 5.f);
			CHECK_MAT4(perspectiveMat, perspectiveMatGlm);
		}

		SECTION("LookAt")
		{
			FMat4 lookAtMat = FMat4::LookAt(FVec3{ 2.f, 3.f, 4.f }, FVec3{ 5.f, 6.f, 7.f }, FVec3{ 8.f, 9.f, 10.f });
			glm::mat4 lookAtMatGlm = glm::lookAt(glm::vec3(2.f, 3.f, 4.f), glm::vec3(5.f, 6.f, 7.f), glm::vec3(8.f, 9.f, 10.f));
			CHECK_MAT4(lookAtMat, lookAtMatGlm);
		}
		SECTION("MVP")
		{
			FMat4 model = FMat4::Identity();
			FMat4 view = FMat4::LookAt(FVec3{ 2.f, 3.f, 4.f }, FVec3{ 5.f, 6.f, 7.f }, FVec3{ 8.f, 9.f, 10.f });
			FMat4 projection = FMat4::Perspective(2.f, 3.f, 4.f, 5.f);

			FMat4 mvp = projection * view * model;

			glm::mat4 modelGlm = glm::mat4(1.f);
			glm::mat4 viewGlm = glm::lookAt(glm::vec3(2.f, 3.f, 4.f), glm::vec3(5.f, 6.f, 7.f), glm::vec3(8.f, 9.f, 10.f));
			glm::mat4 projectionGlm = glm::perspective(glm::radians(2.f), 3.f, 4.f, 5.f);

			glm::mat4 mvpGlm = projectionGlm * viewGlm * modelGlm;
			CHECK_MAT4(mvp, mvpGlm);
		}
		SECTION("To Matrix 4")
		{
			FMat4 mat4 = FMat4::ToMat4(FMat3(5));
			glm::mat4 mat4Glm = glm::mat3(5);
			CHECK_MAT4(mat4, mat4Glm);
		}
		SECTION("Transform")
		{
			FMat4 mat4 = FMat4::Identity();
			FVec3 vec3 = FVec3(1, 2, 3);
			mat4 = FMat4::Transform(vec3, vec3, vec3);
			glm::mat4 mat4Glm = glm::mat4(1);
			glm::vec3 vec3Glm = glm::vec3(1, 2, 3);
			// transform  = translate * zRot * xRot * yRot * Scale;
			mat4Glm = glm::translate(mat4Glm, vec3Glm) * glm::rotate(glm::mat4(1.f), glm::radians(3.f), glm::vec3(0.f, 0.f, 1.f)) * glm::rotate(glm::mat4(1.f), glm::radians(1.f), glm::vec3(1.f, 0.f, 0.f)) * glm::rotate(glm::mat4(1.f), glm::radians(2.f), glm::vec3(0.f, 1.f, 0.f)) * glm::scale(mat4Glm, vec3Glm);
			CHECK_MAT4(mat4, mat4Glm);
			SECTION("With Quat")
			{
				mat4 = FMat4::Identity();
				vec3 = FVec3(1, 2, 3);
				FQuat quat = FQuat(1, 2, 3, 4);
				mat4 = FMat4::Transform(vec3, quat, vec3);
				mat4Glm = glm::mat4(1);
				vec3Glm = glm::vec3(1, 2, 3);
				// transform  = translate * zRot * xRot * yRot * Scale;
				mat4Glm = glm::translate(mat4Glm, vec3Glm) * glm::toMat4(glm::normalize(glm::quat(4, 1, 2, 3))) * glm::scale(mat4Glm, vec3Glm);
				CHECK_MAT4(mat4, mat4Glm);
			}
		}

		SECTION("Decompose")
		{
			FMat4 mat4 = FMat4::Identity();
			FVec3 vec3 = FVec3(1, 2, 3);
			FVec3 rot = FVec3(1, 2, 3);
			FQuat rotx = FQuat(FVec3::Right, rot.x);
			FQuat roty = FQuat(FVec3::Up, rot.y);
			FQuat rotz = FQuat(FVec3::Forward, rot.z);
			FQuat quat = rotx * roty * rotz;
			mat4 = FMat4::Transform(vec3, quat, vec3);

			FVec3 scale;
			FVec3 rotation;
			FVec3 translation;
			FMat4::Decompose(mat4, scale, rotation, translation);

			CHECK(vec3 == translation);
			//CHECK(rot == rotation); aproximation needed
			CHECK(rot.x == Catch::Approx(rotation.x));
			CHECK(rot.y == Catch::Approx(rotation.y));
			CHECK(rot.z == Catch::Approx(rotation.z));

			CHECK(vec3 == scale);
		}
	}
}