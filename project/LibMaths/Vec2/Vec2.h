#pragma once

#include <iostream>
#include <string>
#include "../Vec4/Vec4.h"
#include "Constants.h"


namespace lm
{
	template <typename T> class Vec2
	{

	private:

		T x;
		T y;

		T Length2() const
		{
			return (this->x * this->x) + (this->y * this->y);
		}

	public:

		static const T unitVal;
		static const Vec2<T> zero;
		static const Vec2<T> up;
		static const Vec2<T> down;
		static const Vec2<T> left;
		static const Vec2<T> right;

		Vec2()
		{
			this->x = 0;
			this->y = 0;
		}

		explicit Vec2(const T init)
		{
			this->x = init;
			this->y = init;
		}

		Vec2(const T x, const T y)
		{
			this->x = x;
			this->y = y;
		}

		Vec2(const Vec2<T>& vec2)
		{
			this->x = vec2.x;
			this->y = vec2.y;
		}

		explicit Vec2(const Vec4<T>& vec4)
		{
			this->x = vec4.X();
			this->y = vec4.Y();
		}

		explicit Vec2(const Vec3<T>& vec3)
		{
			this->x = vec3.X();
			this->y = vec3.Y();
		}

		Vec2<T>& operator=(const Vec2<T>& vec2)
		{
			if (this == &vec2)
				return *this;

			this->x = vec2.x;
			this->y = vec2.y;

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

		T X() const
		{
			return this->x;
		}

		T Y() const
		{
			return this->y;
		}

		T Length() const
		{
			return sqrt((this->x * this->x) + (this->y * this->y));
		}

		bool IsUnit() const
		{
			return std::abs(this->Length() - unitVal) <= std::numeric_limits<T>::epsilon() ||
				std::abs(this->Length() - unitVal) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(this->Length()), std::abs(unitVal));
		}

		T DotProduct(const Vec2<T>& vec2) const
		{
			return (this->x * vec2.x) + (this->y * vec2.y);
		}

		T CrossProduct(const Vec2<T>& vec2) const
		{
			return (this->x * vec2.y) - (this->y * vec2.x);
		}
		
		T RadAngle(const Vec2<T>& vec2) const
		{
			constexpr T product = this->DotProduct(vec2);

			constexpr T lengthA2 = this->Length2();
			constexpr T lengthB2 = vec2.Length2();
			constexpr T length2Product = lengthA2 * lengthB2;

			constexpr T length = sqrt(length2Product);

			return std::acos(product / length);
		}

		T DegAngle(const Vec2<T>& vec2) const
		{
			return radiansToDegrees(this->RadAngle(vec2));	
		}

		Vec2<T> Project(const Vec2<T>& vec2) const
		{
			constexpr T product = this->DotProduct(vec2);
			constexpr T length = vec2.Length2();
			constexpr T division = product / length;

			return Vec2<T>(division * vec2.x, division * vec2.y);
		}

		Vec2<T> Reflexion(const Vec2<T>& vec2) const
		{
			if (!vec2.IsUnit())
			{
				Vec2<T> proj = this->Project(vec2);
				proj *= 2;
				return Vec2<T>(this->x - proj.x, this->y - proj.y);
			}

			constexpr T product = this->DotProduct(vec2);
			constexpr T doubledProduct = 2 * product;
			constexpr Vec2<T> vecProduct = doubledProduct * vec2;

			return Vec2<T>(this->x - vecProduct.x, this->y - vecProduct.y);
		}

		Vec2<T> Perpendicular(const Vec2<T>& vec2) const
		{
			constexpr Vec2<T> proj = this->Project(vec2);
			return Vec2<T>(this->x - proj.x, this->y - proj.y);
		}

		Vec2<T> Add(const Vec2<T>& vec2) const
		{
			return Vec2<T>(this->x + vec2.x, this->y + vec2.y);
		}

		Vec2<T>& Add(const Vec2<T>& vec2)
		{
			this->x += vec2.x;
			this->y += vec2.y;
			return *this;
		}

		Vec2<T> Scale(const T scale) const
		{
			return Vec2<T>(this->x * scale, this->y * scale);
		}

		Vec2<T>& Scale(const T scale)
		{
			this->x *= scale;
			this->y *= scale;
			return *this;
		}

		Vec2<T> Normalized() const
		{
			return Vec2<T>(this->x / this->Length(), this->y / this->Length());
		}

		void Normalize()
		{
			T length = this->Length();

			this->x /= length;
			this->y /= length;
		}

		T& operator[](const int idx)
		{
			switch (idx)
			{
				case 0:		return x;
				case 1:		return y;

				case 'x':	return x;
				case 'y':	return y;

				default:	return x;
			}
		}

		T& operator[](const char* idx)
		{
			switch (idx[0])
			{
				case 'x': return x;
				case 'y': return y;
				
				default: return x;
			}
		}

		T operator[](const char* idx) const
		{
			switch (idx[0])
			{
				case 'x': return x;
				case 'y': return y;

				default: return x;
			}
		}

		bool operator==(const Vec2<T>& vec2) const
		{
			if (this == &vec2)
				return true;

			return std::abs(this->Length() - vec2.Length()) <= std::numeric_limits<T>::epsilon() ||
				std::abs(this->Length() - vec2.Length()) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(this->Length()), std::abs(vec2.Length()));
		}

		bool operator!=(const Vec2<T>& vec2) const
		{
			return !(*this == vec2);
		}

		bool operator<(const Vec2<T>& vec2) const
		{
			return this->Length() < vec2.Length();
		}

		bool operator<=(const Vec2<T>& vec2) const
		{
			return this->Length() < vec2.Length() || (*this == vec2);
		}

		bool operator>(const Vec2<T>& vec2) const
		{
			return !(*this < vec2);
		}

		bool operator>=(const Vec2<T>& vec2) const
		{
			return !(*this <= vec2);
		}

		Vec2<T> operator+(const Vec2<T>& vec2) const
		{
			return Vec2(this->x + vec2.x, this->y + vec2.y);
		}

		void operator+=(const Vec2<T>& vec2)
		{
			this->x += vec2.x;
			this->y += vec2.y;
		}

		Vec2<T> operator-(const Vec2<T>& vec2) const
		{
			return Vec2(this->x - vec2.x, this->y - vec2.y);
		}

		void operator-=(const Vec2<T>& vec2)
		{
			this->x -= vec2.x;
			this->y -= vec2.y;
		}

		Vec2<T> operator-() const
		{
			return Vec2(-this->x, -this->y);
		}

		Vec2<T> operator*(const T value) const
		{
			return this->Scale(value);
		}

		void operator*=(const T value)
		{
			*this = this->Scale(value);
		}

		Vec2<T> operator*(const Vec2<T>& vec2) const
		{
			return this->CrossProduct(vec2);
		}

		void operator*=(const Vec2<T>& vec2)
		{
			*this = this->CrossProduct(vec2);
		}

		Vec2<T> operator/(const T value) const
		{
			return Vec2(this->x / value, this->y / value);
		}

		void operator/=(const T value)
		{
			this->x /= value;
			this->y /= value;
		}

		void operator++(int)
		{
			T length = this->Length();
			this->x *= (length + 1) / length;
			this->y *= (length + 1) / length;
		}

		void operator--(int)
		{
			T length = this->Length();
			this->x *= (length - 1) / length;
			this->y *= (length - 1) / length;
		}
	};

	template<class T> std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec2)
	{
		return os << vec2.X() << ',' << vec2.Y();
	}

	template<class T> void operator>>(std::istream& is, Vec2<T>& vec2)
	{
		std::string str;
		is >> str;

		int delimiter = -1;
		for (unsigned int i = 0; i < str.length(); i++)
			if (str[i] == ',') {
				delimiter = i;
				break;
			}

		if (delimiter == -1 || (str[0] < '0' || str[0] > '9')
			|| (str[delimiter + 1] < '0' || str[delimiter + 1] > '9'))
		{
			vec2.X() = 0;
			vec2.Y() = 0;
		}

		else
		{
			std::string xStr = str.substr(0, delimiter);
			std::string yStr = str.substr(++delimiter, str.length());

			vec2.X() = std::stof(xStr);
			vec2.Y() = std::stof(yStr);
		}
	}

	template<class T> std::string operator+(const std::string& str, const Vec2<T>& vec2)
	{
		return  str + "x:" + std::to_string(vec2.X()) + ", y : " + std::to_string(vec2.Y());
	}

	template<class T> void operator+=(std::string& str, const Vec2<T>& vec2)
	{
		str += "x:" + std::to_string(vec2.X()) + ", y : " + std::to_string(vec2.Y());
	}

	template<class T> Vec2<T> operator*(const double value, const Vec2<T>& vec2)
	{
		return vec2 * T(value);
	}

	template<class T> Vec2<T> operator/(const double value, const Vec2<T>& vec2)
	{
		return Vec2<T>(T(value / vec2.X()), T(value / vec2.Y()));
	}

	template<class T> const T operator,(const Vec2<T>& vec1, const Vec2<T>& vec2)
	{
		return vec1.dotProduct(vec2);
	}

	template<class T> const Vec2<T> Vec2<T>::zero = Vec2();
	template<class T> const Vec2<T> Vec2<T>::up(0, 1);
	template<class T> const Vec2<T> Vec2<T>::down(0, -1);
	template<class T> const Vec2<T> Vec2<T>::left(-1, 0);
	template<class T> const Vec2<T> Vec2<T>::right(1, 0);
	template<class T> const T Vec2<T>::unitVal = 1;

	typedef Vec2<float> vec2;
}