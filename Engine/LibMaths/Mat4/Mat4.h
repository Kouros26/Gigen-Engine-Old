#pragma once
#include <cmath>
#include "../Vec4/Vec4.h"

namespace lm
{
	template <typename T> class Mat4
	{

	private:

		Vec4<T> matrix[4];

	public:

		Mat4()
		{
			this->matrix[0] = Vec4<T>(1, 0, 0, 0);
			this->matrix[1] = Vec4<T>(0, 1, 0, 0);
			this->matrix[2] = Vec4<T>(0, 0, 1, 0);
			this->matrix[3] = Vec4<T>(0, 0, 0, 1);
		}

		//static constexpr Mat4<T> identity = Mat4<T>();

		explicit Mat4(const T init)
		{
			this->matrix[0] = Vec4<T>(init, 0, 0, 0);
			this->matrix[1] = Vec4<T>(0, init, 0, 0);
			this->matrix[2] = Vec4<T>(0, 0, init, 0);
			this->matrix[2] = Vec4<T>(0, 0, 0, 1);
		}

		Mat4(const Vec4<T>& v1, const Vec4<T>& v2, const Vec4<T>& v3, const Vec4<T>& v4)
		{
			this->matrix[0] = v1;
			this->matrix[1] = v2;
			this->matrix[2] = v3;
			this->matrix[3] = v4;
		}

		Mat4(const Mat4<T>& mat4)
		{
			for (unsigned int i = 0; i < 4; i++)
				this->matrix[i] = mat4.matrix[i];
		}

		Mat4<T>& operator=(const Mat4<T>& mat4)
		{
			if (this == &mat4)
				return *this;

			for (unsigned int i = 0; i < 4; i++)
				this->matrix[i] = mat4.matrix[i];

			return *this;
		}

		Vec4<T> operator[](int idx) const
		{
			if (idx >= 0 && idx < 4)
				return this->matrix[idx];
			return this->matrix[0];
		}

		Vec4<T>& operator[](int idx)
		{
			if (idx >= 0 && idx < 4)
				return this->matrix[idx];
			return this->matrix[0];
		}

		T operator[](const char* idx) const
		{
			unsigned int vecIdx = idx[1] - '1';
			switch (idx[0])
			{
			case 'x': return this->matrix[vecIdx].X();
			case 'y': return this->matrix[vecIdx].Y();
			case 'z': return this->matrix[vecIdx].Z();
			case 'w': return this->matrix[vecIdx].W();

			default: return this->matrix[0].X();
			}
		}

		T& operator[](const char* idx)
		{
			unsigned int vecIdx = idx[1] - '0';
			switch (idx[0])
			{
			case 'x': return this->matrix[vecIdx].X();
			case 'y': return this->matrix[vecIdx].Y();
			case 'z': return this->matrix[vecIdx].Z();
			case 'w': return this->matrix[vecIdx].W();

			default: return this->matrix[0].X();
			}
		}

		Mat4<T> operator*(const Mat4<T>& mat4) const
		{
			Mat4<T> newMat4;

			for (unsigned int i = 0; i < 4; i++)
			{
				Vec4<T> vec4;
				for (unsigned int j = 0; j < 4; j++)
				{
					vec4[j] = this->matrix[0][j] * mat4.matrix[i].X()
						+ this->matrix[1][j] * mat4.matrix[i].Y()
						+ this->matrix[2][j] * mat4.matrix[i].Z()
						+ this->matrix[3][j] * mat4.matrix[i].W();
				}
				newMat4.matrix[i] = vec4;
			}

			return newMat4;
		}

		Vec4<T> operator*(const Vec4<T>& vec4) const
		{
			Vec4<T> newVec4;
			newVec4.X() = (this->matrix[0][0] * vec4.X()) + (this->matrix[1].X() * vec4.Y()) + (this->matrix[2].X() * vec4.Z()) + (this->matrix[3].X() * vec4.W());
			newVec4.Y() = (this->matrix[0][1] * vec4.X()) + (this->matrix[1].Y() * vec4.Y()) + (this->matrix[2].Y() * vec4.Z()) + (this->matrix[3].Y() * vec4.W());
			newVec4.Z() = (this->matrix[0].Z() * vec4.X()) + (this->matrix[1].Z() * vec4.Y()) + (this->matrix[2].Z() * vec4.Z()) + (this->matrix[3].Z() * vec4.W());
			newVec4.W() = (this->matrix[0].W() * vec4.X()) + (this->matrix[1].W() * vec4.Y()) + (this->matrix[2].W() * vec4.Z()) + (this->matrix[3].W() * vec4.W());
			return newVec4;
		}

		static Mat4<T> CreateTransformMatrix(const Vec3<T>& position, const Vec3<T>& rotation, const Vec3<T>& scaleVec)
		{
			return Translation(position) * ZRotation(rotation.Z()) * XRotation(rotation.X()) * YRotation(rotation.Y()) * Scale(scaleVec);
		}

		static Mat4<T> CreateView(const Vec3<T>& position, const Vec3<T>& rotation)
		{
			return Translation(position) * XRotation(rotation.X()) * YRotation(rotation.Y());
		}

		static Mat4<T> LookAt(lm::vec3 const& eye, lm::vec3 const& center, lm::vec3 const& up)
		{
			lm::vec3  f = (center - eye).Normalized();
			lm::vec3  u = up.Normalized();
			lm::vec3  r = f.CrossProduct(u).Normalized();
			u = r.CrossProduct(f);

			lm::Mat4<T> Result;
			Result[0][0] = r.X();
			Result[1][0] = r.Y();
			Result[2][0] = r.Z();
			Result[0][1] = u.X();
			Result[1][1] = u.Y();
			Result[2][1] = u.Z();
			Result[0][2] = -f.X();
			Result[1][2] = -f.Y();
			Result[2][2] = -f.Z();
			Result[3][0] = -(r.DotProduct(eye));
			Result[3][1] = -(u.DotProduct(eye));
			Result[3][2] = f.DotProduct(eye);
			return Result;
		}

		Mat4<T> Transpose()
		{
			return Mat4<T>(Vec4<T>(this->matrix[0].X(), this->matrix[1].X(), this->matrix[2].X(), this->matrix[3].X()),
				Vec4<T>(this->matrix[0].Y(), this->matrix[1].Y(), this->matrix[2].Y(), this->matrix[3].Y()),
				Vec4<T>(this->matrix[0].Z(), this->matrix[1].Z(), this->matrix[2].Z(), this->matrix[3].Z()),
				Vec4<T>(this->matrix[0].W(), this->matrix[1].W(), this->matrix[2].W(), this->matrix[3].W()));
		}

		Mat4<T> GetInverse()
		{
			std::swap(this->matrix[0].Z(), this->matrix[2].X());
			std::swap(this->matrix[0].Y(), this->matrix[1].X());
			std::swap(this->matrix[1].Z(), this->matrix[2].Y());

			this->matrix[3] *= -1;
			return *this;
		}

		static Mat4<T> Translation(const Vec3<T>& translation)
		{
			Mat4<T> translate;
			translate["x3"] = translation.X();
			translate["y3"] = translation.Y();
			translate["z3"] = translation.Z();
			return translate;
		}

		static Mat4<T> Scale(const Vec3<T>& scale)
		{
			Mat4<T> matrixScale;
			matrixScale["x0"] = scale.X();
			matrixScale["y1"] = scale.Y();
			matrixScale["z2"] = scale.Z();
			return matrixScale;
		}

		static Mat4<T> XRotation(float angle)
		{
			float rad = static_cast<float>(lm::vec4::DegreesToRadians(angle));

			Mat4<T> matrixScale;
			matrixScale["y1"] = std::cosf(rad);
			matrixScale["y2"] = -std::sinf(rad);

			matrixScale["z1"] = std::sinf(rad);
			matrixScale["z2"] = std::cosf(rad);

			return matrixScale;
		}

		static Mat4<T> YRotation(float angle)
		{
			float rad = static_cast<float>(lm::vec4::DegreesToRadians(angle));

			Mat4<T> matrixRotation;
			matrixRotation["x0"] = std::cosf(rad);
			matrixRotation["x2"] = std::sinf(rad);

			matrixRotation["z0"] = -std::sinf(rad);
			matrixRotation["z2"] = std::cosf(rad);

			return matrixRotation;
		}

		static Mat4<T> ZRotation(float angle)
		{
			float rad = static_cast<float>(lm::vec4::DegreesToRadians(angle));

			Mat4<T> matrixScale;
			matrixScale["x0"] = std::cosf(rad);
			matrixScale["x1"] = -std::sinf(rad);

			matrixScale["y0"] = std::sinf(rad);
			matrixScale["y1"] = std::cosf(rad);

			return matrixScale;
		}

		static Mat4<T> PerspectiveProjection(const float& fov, const float& aspect, const float& near, const float& far)
		{
			float scale = tanf(fov * static_cast<float>(M_PI / 360)) * near;
			float r = aspect * scale;
			float l = -r;
			float t = scale;
			float b = -t;

			float x1 = 2 * near / (r - l);
			float y2 = 2 * near / (t - b);
			float x3 = (r + l) / (r - l);
			float y3 = (t + b) / (t - b);
			float z3 = -(far + near) / (far - near);
			float z4 = -(2 * far * near) / (far - near);

			Mat4<T> mat4;

			mat4.matrix[0] = lm::Vec4<T>(x1, 0, 0, 0);
			mat4.matrix[1] = lm::Vec4<T>(0, y2, 0, 0);
			mat4.matrix[2] = lm::Vec4<T>(x3, y3, z3, -1);
			mat4.matrix[3] = lm::Vec4<T>(0, 0, z4, 0);

			return mat4;
		}

		bool operator==(const Mat4<T>& mat4) const
		{
			if (this == &mat4)
				return true;

			for (unsigned int i = 0; i < 4; i++)
				if (this->matrix[i] != mat4.matrix[i])
					return false;

			return true;
		}

		bool operator!=(const Mat4<T>& mat4) const
		{
			return !(*this == mat4);
		}

		vec3 ExtractScale()
		{
			constexpr vec3 xScalar(this->matrix[0].X(), this->matrix[0].Y(), this->matrix[0].Z());
			constexpr vec3 yScalar(this->matrix[1].X(), this->matrix[1].Y(), this->matrix[1].Z());
			constexpr vec3 zScalar(this->matrix[2].X(), this->matrix[2].Y(), this->matrix[2].Z());
			constexpr float x = xScalar.Length();
			constexpr float y = yScalar.Length();
			constexpr float z = zScalar.Length();
			vec3 scalar(x, y, z);
			return scalar;
		}

		vec3 ExtractRotation(vec3 scale)
		{
			float theta, gamma, phi;

			Mat4<T> rotationMatrix(Vec4<T>(this->matrix[0].X() / scale.X(), this->matrix[0].Y() / scale.X(), this->matrix[0].Z() / scale.X(), 0),
				Vec4<T>(this->matrix[1].X() / scale.Y(), this->matrix[1].Y() / scale.Y(), this->matrix[1].Z() / scale.Y(), 0),
				Vec4<T>(this->matrix[2].X() / scale.Z(), this->matrix[2].Y() / scale.Z(), this->matrix[2].Z() / scale.Z(), 0),
				Vec4<T>(0, 0, 0, 1));

			if (rotationMatrix[2].X() != 1 || rotationMatrix[2].X() != -1)
			{
				theta = -asin(rotationMatrix[2].X());

				gamma = atan2(rotationMatrix[2].Y() / cos(theta), rotationMatrix[2].Z() / cos(theta));

				phi = atan2(rotationMatrix[1].X() / cos(theta), rotationMatrix[0].X() / cos(theta));
			}

			else
			{
				phi = 0;

				if (rotationMatrix[2].X() != -1)
				{
					theta = M_PI / 2;
					gamma = atan2(rotationMatrix[0].Y(), rotationMatrix[0].Z());
				}
				else
				{
					theta = -M_PI / 2;
					gamma = atan2(-rotationMatrix[0].Y(), -rotationMatrix[0].Z());
				}
			}

			vec3 rotateVector(gamma * (180 / M_PI), theta * (180 / M_PI), phi * (180 / M_PI));

			return rotateVector;
		}
	};

	//template <class T> const Mat4<T> Mat4<T>::identity = Mat4();

	typedef Mat4<float> mat4;
}