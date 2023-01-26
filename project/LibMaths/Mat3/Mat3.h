#pragma once

#include "../Vec3/Vec3.h"
#include "../Mat4/Mat4.h"

namespace lm
{
	template <typename T> class Mat3
	{

	private:

		Vec3<T> matrix[3];

	public:

		static constexpr Mat3<T> identity = Mat3<T>();

		Mat3()
		{
			this->matrix[0] = Vec3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
			this->matrix[1] = Vec3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
			this->matrix[2] = Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
		}

		explicit Mat3(const T init)
		{
			this->matrix[0] = Vec3<T>(init, static_cast<T>(0), static_cast<T>(0));
			this->matrix[1] = Vec3<T>(static_cast<T>(0), init, static_cast<T>(0));
			this->matrix[2] = Vec3<T>(static_cast<T>(0), static_cast<T>(0), init);
		}

		Mat3(const Vec3<T>& v1, const Vec3<T>& v2, const Vec3<T>& v3)
		{
			this->matrix[0] = v1;
			this->matrix[1] = v2;
			this->matrix[2] = v3;
		}

		Mat3(const Mat3<T>& mat3)
		{
			for (unsigned int i = 0; i < 3; i++)
				this->matrix[i] = mat3.matrix[i];
		}

		explicit Mat3(const Mat4<T>& mat4)
		{
			for (unsigned int i = 0; i < 3; i++)
				this->matrix[i] = Vec3<T>(mat4[i].X(), mat4[i].Y(), mat4[i].Z());
		}

		Mat3<T>& operator=(const Mat3<T>& mat3)
		{
			if (this == &mat3)
				return *this;

			for (unsigned int i = 0; i < 3; i++)
				this->matrix[i] = mat3.matrix[i];

			return *this;
		}

		T operator[](int idx) const
		{
			unsigned int vecIdx = idx / 3;
			idx = idx % 3;
			switch (idx)
			{
				case 0: return this->matrix[vecIdx].X();
				case 1: return this->matrix[vecIdx].Y();
				case 2: return this->matrix[vecIdx].Z();

				default: return this->matrix[vecIdx].X();
			}
		}

		T& operator[](int idx)
		{
			unsigned int vecIdx = idx / 3;
			idx = idx % 3;
			switch (idx)
			{
				case 0: return this->matrix[vecIdx].X();
				case 1: return this->matrix[vecIdx].Y();
				case 2: return this->matrix[vecIdx].Z();

				default: return this->matrix[0].X();
			}
		}

		T operator[](const char* idx) const
		{
			unsigned int vecIdx = idx[1] - '1';
			switch (idx[0])
			{
				case 'x': return this->matrix[vecIdx].X();
				case 'y': return this->matrix[vecIdx].Y();
				case 'z': return this->matrix[vecIdx].Z();

				default: return this->matrix[0].X();
			}
		}

		T& operator[](const char* idx)
		{
			unsigned int vecIdx = idx[1] - '1';
			switch (idx[0])
			{
				case 'x': return this->matrix[vecIdx].X();
				case 'y': return this->matrix[vecIdx].Y();
				case 'z': return this->matrix[vecIdx].Z();

				default: return this->matrix[0].X();
			}
		}

		Mat3<T> Scale(const T scale) const
		{
			Mat3<T> mat3(*this);
			for (unsigned int i = 0; i < 3; i++)
			{
				mat3.matrix[i].X() *= scale;
				mat3.matrix[i].Y() *= scale;
				mat3.matrix[i].Z() *= scale;
			}

			return mat3;
		}

		Mat3<T>& Scale(const T scale)
		{
			for (unsigned int i = 0; i < 3; i++)
			{
				this->matrix[i].X() *= scale;
				this->matrix[i].Y() *= scale;
				this->matrix[i].Z() *= scale;
			}

			return *this;
		}

		Mat3<T> DotProduct(const Mat3<T>& mat3) const
		{
			Mat3<T> newMat3;

			for (unsigned int i = 0; i < 3; i++)
			{
				Vec3<T> vec3;
				for (unsigned int j = 0; j < 3; j++)
				{
					vec3[j] = this->matrix[i].X() * mat3.matrix[0][j]
								+ this->matrix[i].Y() * mat3.matrix[1][j]
								+ this->matrix[i].Z() * mat3.matrix[2][j];
				}
				newMat3.matrix[i] = vec3;
			}

			return newMat3;
		}

		Mat3<T> Transpose() const
		{
			return Mat3<T>(Vec3<T>(this->matrix[0].X(), this->matrix[1].X(), this->matrix[2].X()),
							Vec3<T>(this->matrix[0].Y(), this->matrix[1].Y(), this->matrix[2].Y()),
							Vec3<T>(this->matrix[0].Z(), this->matrix[1].Z(), this->matrix[2].Z()));
		}

		T Determinant() const
		{
			return ((this->matrix[0].X() * ((this->matrix[1].Y() * this->matrix[2].Z()) - (this->matrix[1].Z() * this->matrix[2].Y()))) -
				    (this->matrix[0].Y() * ((this->matrix[1].X() * this->matrix[2].Z()) - (this->matrix[1].Z() * this->matrix[2].X()))) +
				    (this->matrix[0].Z() * ((this->matrix[1].X() * this->matrix[2].Y()) - (this->matrix[1].Y() * this->matrix[2].X()))));
		}

		Mat3<T> Minor() const
		{
			Mat3<T> newMat3;
			newMat3.matrix[0].X() = ((this->matrix[1].Y() * this->matrix[2].Z()) - (this->matrix[1].Z() * this->matrix[2].Y()));
			newMat3.matrix[0].Y() = ((this->matrix[1].X() * this->matrix[2].Z()) - (this->matrix[1].Z() * this->matrix[2].X()));
			newMat3.matrix[0].Z() = ((this->matrix[1].X() * this->matrix[2].Y()) - (this->matrix[1].Y() * this->matrix[2].X()));

			newMat3.matrix[1].X() = ((this->matrix[0].Y() * this->matrix[2].Z()) - (this->matrix[0].Z() * this->matrix[2].Y()));
			newMat3.matrix[1].Y() = ((this->matrix[0].X() * this->matrix[2].Z()) - (this->matrix[0].Z() * this->matrix[2].X()));
			newMat3.matrix[1].Z() = ((this->matrix[0].X() * this->matrix[2].Y()) - (this->matrix[0].Y() * this->matrix[2].X()));

			newMat3.matrix[2].X() = ((this->matrix[0].Y() * this->matrix[1].Z()) - (this->matrix[0].Z() * this->matrix[1].Y()));
			newMat3.matrix[2].Y() = ((this->matrix[0].X() * this->matrix[1].Z()) - (this->matrix[0].Z() * this->matrix[1].X()));
			newMat3.matrix[2].Z() = ((this->matrix[0].X() * this->matrix[1].Y()) - (this->matrix[0].Y() * this->matrix[1].X()));

			return newMat3;
		}

		Mat3<T> Cofactor() const
		{
			Mat3<T> min = this->Minor();
			min.matrix[0].Y() *= -1;
			min.matrix[1].X() *= -1;
			min.matrix[1].Z() *= -1;
			min.matrix[2].Y() *= -1;
			return min;
		}

		Mat3<T> Adjugate() const
		{
			Mat3<T> cof = this->Cofactor();
			cof = cof.Transpose();
			return cof;
		}

		Mat3<T> Inverse() const
		{
			constexpr T determinant = this->Determinant();
			constexpr T div = 1.0f / determinant;

			Mat3 mat3 = this->Adjugate();
			return Mat3<T>( Vec3<T>(mat3.matrix[0].X() * div, mat3.matrix[0].Y() * div, mat3.matrix[0].Z() * div),
							Vec3<T>(mat3.matrix[1].X() * div, mat3.matrix[1].Y() * div, mat3.matrix[1].Z() * div),
							Vec3<T>(mat3.matrix[2].X() * div, mat3.matrix[2].Y() * div, mat3.matrix[2].Z() * div));
		}

		Mat3<T> operator*(const float scale) const
		{
			return this->Scale(scale);
		}

		void operator*=(const float scale)
		{
			*this = this->Scale(scale);
		}

		Mat3<T> operator*(const Mat3<T>& mat3) const
		{
			return this->DotProduct(mat3);
		}

		Vec3<T> operator*(const Vec3<T>& vec3)
		{
			Vec3<T> newVec3;
			newVec3.X() = (this->matrix[0].X() * vec3.X()) + (this->matrix[1].X() * vec3.Y()) + (this->matrix[2].X() * vec3.Z());
			newVec3.Y() = (this->matrix[0].Y() * vec3.X()) + (this->matrix[1].Y() * vec3.Y()) + (this->matrix[2].Y() * vec3.Z());
			newVec3.Z() = (this->matrix[0].Z() * vec3.X()) + (this->matrix[1].Z() * vec3.Y()) + (this->matrix[2].Z() * vec3.Z());
			return newVec3;
		}
		
		void operator*=(const Mat3<T>& mat3)
		{
			*this = this->DotProduct(mat3);
		}

		bool operator==(const Mat3<T>& mat3) const
		{
			if (this == &mat3)
				return true;

			for (unsigned int i = 0; i < 3; i++)
				if (this->matrix[0] != mat3.matrix[0])
					return false;

			return true;
		}

		bool operator!=(const Mat3<T>& mat3) const
		{
			return !(*this == mat3);
		}
	};

	typedef Mat3<float> mat3;
}