#pragma once
#include <limits>
#include <ostream>
#include "Constants.h"

namespace lm
{
	template <typename T> class Vec3
	{

	private:

		T x;
		T y;
		T z;

		T Length2() const
		{
			return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
		}

	public:

		static const T unitVal;
		static const Vec3<T> zero;
		static const Vec3<T> up;
		static const Vec3<T> down;
		static const Vec3<T> left;
		static const Vec3<T> right;
		static const Vec3<T> forward;
		static const Vec3<T> backward;

		static Vec3<T> LerpPosition(Vec3<T> a, Vec3<T> b, float v)
		{
			return a + (v * (b - a));
		}

		static Vec3<T> SlerpPosition(Vec3<T> a, Vec3<T> b, float v)
		{
			float dot = a.DotProduct(b);

			if (dot > 1) dot = 1;
			if (dot < -1) dot = -1;

			float theta = acos(dot) * v;

			Vec3<T> relativeVec = b - (a * dot);
			relativeVec.Normalize();

			return ((a * cos(theta)) + (relativeVec * sin(theta)));
		}

		static Vec3<T> NlerpPosition(Vec3<T> a, Vec3<T> b, float v)
		{
			Vec3<T> result = LerpPosition(a, b, v);
			result.Normalize();
			return result;
		}

		Vec3()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		explicit Vec3(const T init)
		{
			this->x = init;
			this->y = init;
			this->z = init;
		}

		Vec3(const T x, const T y, const T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vec3(const Vec3<T>& vec3)
		{
			this->x = vec3.x;
			this->y = vec3.y;
			this->z = vec3.z;
		}

		Vec3& operator=(const Vec3<T>& vec3)
		{
			if (this == &vec3)
				return *this;

			this->x = vec3.x;
			this->y = vec3.y;
			this->z = vec3.z;

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

		T Length() const
		{
			return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
		}

		bool IsUnit() const
		{
			return std::abs(this->Length() - unitVal) <= std::numeric_limits<T>::epsilon() ||
				std::abs(this->Length() - unitVal) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(this->Length()), std::abs(unitVal));
		}

		T DotProduct(const Vec3<T>& vec3) const
		{
			return (this->x * vec3.x) + (this->y * vec3.y) + (this->z * vec3.z);
		}

		Vec3<T> CrossProduct(const Vec3<T>& vec3) const
		{
			return Vec3<T>( (this->y * vec3.z) - (this->z * vec3.y), 
							(this->z * vec3.x) - (this->x * vec3.z),
							(this->x * vec3.y) - (this->y * vec3.x));
		}

		T RadAngle(const Vec3<T>& vec3) const
		{
			constexpr T product = this->DotProduct(vec3);

			constexpr T lengthA2 = this->Length2();
			constexpr T lengthB2 = vec3.Length2();
			constexpr T length2Product = lengthA2 * lengthB2;

			constexpr T length = sqrt(length2Product);

			return std::acos(product / length);
		}

		T DegAngle(const Vec3<T>& vec3) const
		{
			return radiansToDegrees(this->RadAngle(vec3));
		}

		Vec3<T> Project(const Vec3<T>& vec3) const
		{
			constexpr T product = this->DotProduct(vec3);
			constexpr T length = vec3.Length2();
			constexpr T division = product / length;

			return Vec3<T>(division * vec3.x, division * vec3.y, division * vec3.z);
		}

		Vec3<T> Reflexion(const Vec3<T>& vec3) const
		{
			if (!vec3.IsUnit())
			{
				Vec3<T> proj = this->Project(vec3);
				proj *= 2;
				return Vec3<T>(this->x - proj.x, this->y - proj.y, this->z - proj.z);
			}

			constexpr T product = this->DotProduct(vec3);
			constexpr T doubledProduct = 2 * product;
			constexpr Vec3<T> vecProduct = doubledProduct * vec3;

			return Vec3<T>(this->x - vecProduct.x, this->y - vecProduct.y, this->z - vecProduct.z);
		}

		Vec3<T> Perpendicular(const Vec3<T>& vec3) const
		{
			constexpr Vec3<T> proj = this->Project(vec3);

			return Vec3<T>(this->x - proj.x, this->y - proj.y, this->z - proj.z);
		}

		Vec3<T> Add(const Vec3<T>& vec3) const
		{
			return Vec3<T>(this->x + vec3.x, this->y + vec3.y, this->z + vec3.z);
		}

		Vec3<T>& Add(const Vec3<T>& vec3)
		{
			this->x += vec3.x;
			this->y += vec3.y;
			this->z += vec3.z;
			return *this;
		}

		Vec3<T> Scale(const T scale) const
		{
			return Vec3<T>(this->x * scale, this->y * scale, this->z * scale);
		}

		Vec3<T>& Scale(const T scale)
		{
			this->x *= scale;
			this->y *= scale;
			this->z *= scale;
			return *this;
		}

		Vec3<T>& Scale(const Vec3<T>& vec3)
		{
			this->x *= vec3.X();
			this->y *= vec3.Y();
			this->z *= vec3.Z();
			return *this;
		}

		Vec3<T> Scaled(const Vec3<T>& vec3)
		{
			return lm::Vec3<T>(this->x * vec3.X(), this->y * vec3.Y(), this->z * vec3.Z());
		}

		Vec3<T> Normalized() const
		{
			T length = this->Length();

			return Vec3<T>(this->x / length, this->y / length, this->z / length);
		}

		void Normalize()
		{
			T length = this->Length();

			if (length == 0) return;

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
				
				case 'x':	return x;
				case 'y':	return y;
				case 'z':	return z;

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

				case 'x':	return x;
				case 'y':	return y;
				case 'z':	return z;

				default:	return x;
			}
		}

		T& operator[](const char* idx)
		{
			switch (idx[0])
			{
				case 'x' : return x;
				case 'y' : return y;
				case 'z' : return z;

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

				default: return x;
			}
		}

		bool operator==(const Vec3<T>& vec3) const
		{
			if (this == &vec3)
				return true;

			return std::abs(this->Length() - vec3.Length()) <= std::numeric_limits<T>::epsilon() ||
				std::abs(this->Length() - vec3.Length()) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(this->Length()), std::abs(vec3.Length()));
		}

		bool operator!=(const Vec3<T>& vec3) const
		{
			return !(*this == vec3);
		}

		bool operator<(const Vec3<T>& vec3) const
		{
			return this->Length() < vec3.Length();
		}

		bool operator<=(const Vec3<T>& vec3) const
		{
			return this->Length() < vec3.Length() || (*this == vec3);
		}

		bool operator>(const Vec3<T>& vec3) const
		{
			return !(*this < vec3);
		}

		bool operator>=(const Vec3<T>& vec3) const
		{
			return !(*this <= vec3);
		}

		Vec3<T> operator+(const Vec3<T>& vec3) const
		{
			return Vec3(this->x + vec3.x, this->y + vec3.y, this->z + vec3.z);
		}

		void operator+=(const Vec3<T>& vec3)
		{
			this->x += vec3.x;
			this->y += vec3.y;
			this->z += vec3.z;
		}

		Vec3<T> operator-(const Vec3<T>& vec3) const
		{
			return Vec3(this->x - vec3.x, this->y - vec3.y, this->z - vec3.z);
		}

		void operator-=(const Vec3<T>& vec3)
		{
			this->x -= vec3.x;
			this->y -= vec3.y;
			this->z -= vec3.z;
		}

		Vec3<T> operator-() const
		{
			return Vec3(-this->x, -this->y, -this->z);
		}

		Vec3<T> operator*(const T value) const
		{
			return this->Scale(value);
		}

		void operator*=(const T value)
		{
			*this = this->Scale(value);
		}

		Vec3<T> operator*(const Vec3<T>& vec3) const
		{
			return this->CrossProduct(vec3);
		}

		void operator*=(const Vec3<T>& vec3)
		{
			*this = this->CrossProduct(vec3);
		}

		Vec3<T> operator/(const T value) const
		{
			return Vec3(this->x / value, this->y / value, this->z / value);
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
	};

	template<class T> std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec3)
	{
		return os << vec3.X() << ',' << vec3.Y() << ',' << vec3.Z();
	}

	template <class T> Vec3<T> operator*(const double value, const Vec3<T>& vec3)
	{
		return vec3 * T(value);
	}

	template <class T> Vec3<T> operator/(const double value, const Vec3<T>& vec3)
	{
		return Vec3<T>(T(value / vec3.X()), T(value / vec3.Y()), T(value / vec3.Z()));
	}

	template <class T> const T operator,(const Vec3<T>& vec1, const Vec3<T>& vec2)
	{
		return vec1.dotProduct(vec2);
	}

	template <class T> const Vec3<T> Vec3<T>::zero = Vec3();
	template <class T> const Vec3<T> Vec3<T>::up(0, 1, 0);
	template <class T> const Vec3<T> Vec3<T>::down(0, -1, 0);
	template <class T> const Vec3<T> Vec3<T>::left(-1, 0, 0);
	template <class T> const Vec3<T> Vec3<T>::right(1, 0, 0);
	template <class T> const Vec3<T> Vec3<T>::forward(0, 0, -1);
	template <class T> const Vec3<T> Vec3<T>::backward(0, 0, 1);
	template <class T> const T Vec3<T>::unitVal = 1;

	typedef Vec3<float> vec3;
}