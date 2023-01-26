#pragma once
#include <limits>
#include <algorithm>
#include <ostream>

#include "../Vec3/Vec3.h"

namespace lm
{
	template <typename T> class Vec4
	{

	private:

		T x;
		T y;
		T z;
		T w;


		T Length2() const
		{
			return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
		}

	public:

		static float RadiansToDegrees(const float rad)
		{
			return rad * (HALF_CIRCLE / (float)M_PI);
		}

		static float DegreesToRadians(const float deg)
		{
			return deg * ((float)M_PI / HALF_CIRCLE);
		}

		static const T unitVal;
		static const Vec4<T> zero;
		static const Vec4<T> up;
		static const Vec4<T> down;
		static const Vec4<T> left;
		static const Vec4<T> right;

		Vec4()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 1;
		}

		explicit Vec4(const T init)
		{
			this->x = init;
			this->y = init;
			this->z = init;
			this->w = 1;
		}

		Vec4(const T x, const T y, const T z, const T w = 1)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		explicit Vec4(const Vec3<T>& vec3, float w = 1)
		{
			this->x = vec3.X();
			this->y = vec3.Y();
			this->z = vec3.Z();
			this->w = w;
		}

		Vec4(const Vec4<T>& vec4)
		{
			this->x = vec4.x;
			this->y = vec4.y;
			this->z = vec4.z;
			this->w = vec4.w;
		}

		Vec4& operator=(const Vec4<T>& vec4)
		{
			if (this == &vec4)
				return *this;

			this->x = vec4.x;
			this->y = vec4.y;
			this->z = vec4.z;
			this->w = vec4.w;

			return *this;
		}

		T& X()
		{
			return this->x;
		}

		T& Y()
		{
			return this->y;
		}

		T& Z()
		{
			return this->z;
		}

		T& W()
		{
			return this->w;
		}

		T X() const
		{
			return this->x;
		}

		T Y() const
		{
			return this->y;
		}

		T Z() const
		{
			return this->z;
		}

		T W() const
		{
			return this->w;
		}

		T Length() const
		{
			return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
		}

		bool IsUnit() const
		{
			return std::abs(this->Length() - unitVal) <= std::numeric_limits<T>::epsilon() ||
				std::abs(this->Length() - unitVal) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(this->Length()), std::abs(unitVal));
		}

		T DotProduct(const Vec4<T>& vec4) const
		{
			return (this->x * vec4.x) + (this->y * vec4.y) + (this->z * vec4.z);
		}

		Vec4<T> CrossProduct(const Vec4<T>& vec4) const
		{
			return Vec4<T>((this->y * vec4->z) - (this->z * vec4->y),
							(this->z * vec4->x) - (this->x * vec4->z),
							(this->x * vec4->y) - (this->y * vec4->x)), 1;
		}

		T RadAngle(const Vec4<T>& vec4) const
		{
			constexpr T product = this->DotProduct(vec4);

			constexpr T lengthA2 = this->Length2();
			constexpr T lengthB2 = vec4.Length2();
			constexpr T length2Product = lengthA2 * lengthB2;

			constexpr T length = sqrt(length2Product);

			return std::acos(product / length);
		}

		T DegAngle(const Vec4<T>& vec4) const
		{
			return radiansToDegrees(this->RadAngle(vec4));
		}

		Vec4<T> Project(const Vec4<T>& vec4) const
		{
			constexpr T product = this->DotProduct(vec4);
			constexpr T length = vec4.Length2();
			constexpr T division = product / length;

			return Vec4<T>(division * vec4.x, division * vec4.y, division * vec4.z, 1);
		}

		Vec4<T> Reflexion(const Vec4<T>& vec4) const
		{
			if (!vec4.IsUnit())
			{
				Vec4<T> proj = this->Project(vec4);
				proj *= 2;
				return Vec4<T>(this->x - proj.x, this->y - proj.y, this->z - proj.z, 1);
			}

			constexpr T product = this->DotProduct(vec4);
			constexpr T doubledProduct = 2 * product;
			constexpr Vec4<T> vecProduct = doubledProduct * vec4;

			return Vec4<T>(this->x - vecProduct.x, this->y - vecProduct.y, this->z - vecProduct.z, 1);
		}

		Vec4<T> Perpendicular(const Vec4<T>& vec4) const
		{
			constexpr Vec4<T> proj = this->Project(vec4);

			return Vec4<T>(this->x - proj.x, this->y - proj.y, this->z - proj.z, 1);
		}

		Vec4<T> Add(const Vec4<T>& vec4) const
		{
			return Vec4<T>(this->x + vec4.x, this->y + vec4.y, this->z + vec4.z, 1);
		}

		Vec4<T>& Add(const Vec4<T>& vec4)
		{
			this->x += vec4.x;
			this->y += vec4.y;
			this->z += vec4.z;
			return *this;
		}

		Vec4<T> Scale(const T scale) const
		{
			return Vec4<T>(this->x * scale, this->y * scale, this->z * scale, this->w * scale);
		}

		Vec4<T>& Scale(const T scale)
		{
			this->x *= scale;
			this->y *= scale;
			this->z *= scale;
			return *this;
		}

		Vec4<T> Normalized() const
		{
			T length = this->Length();

			return Vec4<T>(this->x / length, this->y / length, this->z / length, 1);
		}

		void Normalize()
		{
			T length = this->Length();
			this->x /= length;
			this->y /= length;
			this->z /= length;
		}

		T& operator[](const int idx)
		{
			switch (idx)
			{
				case 0:		return x;
				case 1:		return y;
				case 2:		return z;
				case 3:		return w;

				case 'x':	return x;
				case 'y':	return y;
				case 'z':	return z;
				case 'w':	return w;

				default:	return x;
			}
		}

		T operator[](const int idx) const
		{
			switch (idx)
			{
				case 0:		return x;
				case 1:		return y;
				case 2:		return z;
				case 3:		return w;

				case 'x':	return x;
				case 'y':	return y;
				case 'z':	return z;
				case 'w':	return w;

				default:	return x;
			}
		}

		T& operator[](const char* idx)
		{
			switch (idx[0])
			{
				case 'x': return x;
				case 'y': return y;
				case 'z': return z;
				case 'w': return w;

				default: return x;
			}
		}

		T operator[](const char* idx) const
		{
			switch (idx[0])
			{
				case 'x': return x;
				case 'y': return y;
				case 'z': return z;
				case 'w': return w;

				default: return x;
			}
		}

		bool operator==(const Vec4<T>& vec4) const
		{
			if (this == &vec4)
				return true;

			return std::abs(this->Length() - vec4.Length()) <= std::numeric_limits<T>::epsilon() ||
				std::abs(this->Length() - vec4.Length()) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(this->Length()), std::abs(vec4.Length()));
		}

		bool operator!=(const Vec4<T>& vec4) const
		{
			return !(*this == vec4);
		}

		bool operator<(const Vec4<T>& vec4) const
		{
			return this->Length() < vec4.Length();
		}

		bool operator<=(const Vec4<T>& vec4) const
		{
			return this->Length() < vec4.Length() || (*this == vec4);
		}

		bool operator>(const Vec4<T>& vec4) const
		{
			return !(*this < vec4);
		}

		bool operator>=(const Vec4<T>& vec4) const
		{
			return !(*this <= vec4);
		}

		Vec4<T> operator+(const Vec4<T>& vec4) const
		{
			return Vec4(this->x + vec4.x, this->y + vec4.y, this->z + vec4.z, this->w + vec4.w);
		}

		void operator+=(const Vec4<T>& vec4)
		{
			this->x += vec4.x;
			this->y += vec4.y;
			this->z += vec4.z;
		}

		Vec4<T> operator-(const Vec4<T>& vec4) const
		{
			return Vec4(this->x - vec4.x, this->y - vec4.y, this->z - vec4.z, this->w - vec4.w);
		}

		void operator-=(const Vec4<T>& vec4)
		{
			this->x -= vec4.x;
			this->y -= vec4.y;
			this->z -= vec4.z;
		}

		Vec4<T> operator-() const
		{
			return Vec4(-this->x, -this->y, -this->z);
		}

		Vec4<T> operator*(const T value) const
		{
			return this->Scale(value);
		}

		void operator*=(const T value)
		{
			*this = this->Scale(value);
		}

		Vec4<T> operator*(const Vec4<T>& vec4) const
		{
			return this->CrossProduct(vec4);
		}

		void operator*=(const Vec4<T>& vec4)
		{
			*this = this->CrossProduct(vec4);
		}

		Vec4<T> operator/(const T value) const
		{
			return Vec4(this->x / value, this->y / value, this->z / value);
		}

		void operator/=(const T value)
		{
			this->x /= value;
			this->y /= value;
			this->z /= value;
		}

		void operator++(int)
		{
			T length = this->Length();
			this->x *= (length + 1) / length;
			this->y *= (length + 1) / length;
			this->z *= (length + 1) / length;
		}

		void operator--(int)
		{
			T length = this->Length();
			this->x *= (length - 1) / length;
			this->y *= (length - 1) / length;
			this->z *= (length - 1) / length;
		}

		void Homogenize()
		{
			if (this->w == 0)
				return;

			this->x /= this->w;
			this->y /= this->w;
			this->z /= this->w;
		}

		Vec3<T> Homogenized()
		{
			if (this->w == 0)
				return Vec3<T>();

			return Vec3<T>(this->x / this->w, this->y / this->w, this->z / this->w);
		}

		float GetMagnitude() const
		{
			return this->Length();
		}
	};

	template<class T> std::ostream& operator<<(std::ostream& os, const Vec4<T>& vec4)
	{
		return os << vec4.X() << ',' << vec4.Y() << ',' << vec4.Z() << ',' << vec4.W();
	}

	template <class T> Vec4<T> operator*(const double value, const Vec4<T>& vec4)
	{
		return vec4 * T(value);
	}

	template <class T> Vec4<T> operator/(const double value, const Vec4<T>& vec4)
	{
		return Vec4<T>(T(value / vec4.X()), T(value / vec4.Y()), T(value / vec4.Z()));
	}

	template <class T> T operator,(const Vec4<T>& vec1, const Vec4<T>& vec2)
	{
		return vec1.dotProduct(vec2);
	}

	template <class T> const Vec4<T> Vec4<T>::zero = Vec4();
	template <class T> const Vec4<T> Vec4<T>::up(0, 1, 0);
	template <class T> const Vec4<T> Vec4<T>::down(0, -1, 0);
	template <class T> const Vec4<T> Vec4<T>::left(-1, 0, 0);
	template <class T> const Vec4<T> Vec4<T>::right(1, 0, 0);
	template <class T> const T Vec4<T>::unitVal = 1;

	typedef Vec4<float> vec4;
}