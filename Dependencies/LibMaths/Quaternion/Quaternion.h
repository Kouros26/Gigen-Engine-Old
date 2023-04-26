#pragma once
#include <limits>
#include <algorithm>
#include <ostream>

#include "../Vec3/Vec3.h"
#include "../Mat3/Mat3.h"

namespace lm
{
	template <typename T> class Quaternion
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

		//static constexpr Quaternion<T> identity = Quaternion<T>(0, 0, 0, 1);

		

		Quaternion()
		{
			x = y = z = 0;
			w = 1;
		}

		Quaternion(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Quaternion(const Quaternion<T>& q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
		}

		Quaternion(const Mat4<T>& mat)
		{
			this->fromMatrix4(mat);
		}

		~Quaternion()
		{
		}

		const Vec3<T>& getVectorPart() const
		{
			return Vec3<T>(x, y, z);
		}

		T Dot(Quaternion<T> const& p) const
		{
			return (x * p.x) + (y * p.y) + (z * p.z) + (w * p.w);
		}

		Quaternion<T> Negate()
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;
			return *this;
		}

		Quaternion<T> operator+(const Quaternion<T>& q) const
		{
			return Quaternion<T>(x + q.x, y + q.y, z + q.z, w + q.w);
		}

		Quaternion<T> operator-(const Quaternion<T>& q) const
		{
			return Quaternion<T>(x - q.x, y - q.y, z - q.z, w - q.w);
		}

		Quaternion<T> operator*(const Quaternion<T>& q) const
		{
			return Quaternion<T>(w * q.x + x * q.w + y * q.z - z * q.y,
				w * q.y + y * q.w + z * q.x - x * q.z,
				w * q.z + z * q.w + x * q.y - y * q.x,
				w * q.w - x * q.x - y * q.y - z * q.z);
		}

		Quaternion<T> operator*(const T& s) const
		{
			return Quaternion<T>(x * s, y * s, z * s, w * s);
		}

		Vec3<T> operator*(const Vec3<T>& v) const
		{
			const vec3 vector(x, y, z);
			const vec3 uv(vector.CrossProduct(v));
			const vec3 uuv(vector.CrossProduct(uv));

			return v + ((uv * w) + uuv) * 2;
		}

		Quaternion<T> operator/(const T& s) const
		{
			return Quaternion<T>(x / s, y / s, z / s, w / s);
		}
		Quaternion<T> operator-() const
		{
			return Quaternion<T>(-x, -y, -z, -w);
		}

		Quaternion<T>& operator=(const Quaternion<T>& q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
			return *this;
		}
		Quaternion<T>& operator+=(const Quaternion<T>& q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return *this;
		}

		Quaternion<T>& operator-=(const Quaternion<T>& q)
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return *this;
		}
		Quaternion<T>& operator*=(const Quaternion<T>& q)
		{
			*this = *this * q;
			return *this;
		}
		Quaternion<T>& operator*=(const T& s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		Quaternion<T>& operator/=(const T& s)
		{
			x /= s;
			y /= s;
			z /= s;
			w /= s;
			return *this;
		}

		bool operator==(const Quaternion<T>& q) const
		{
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}

		bool operator!=(const Quaternion<T>& q) const
		{
			return x != q.x || y != q.y || z != q.z || w != q.w;
		}

		T Length() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		T LengthSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		Quaternion<T> Conjugate() const
		{
			return Quaternion<T>(-x, -y, -z, w);
		}

		Quaternion<T> Inverse() const
		{
			return Conjugate() / LengthSquared();
		}
		Quaternion<T> Normalize() const
		{
			return *this / Length();
		}
		Quaternion<T> Rotate(const Vec3<T>& v) const
		{
			Quaternion<T> q(v.x, v.y, v.z, 0);
			q = *this * q * Inverse();
			return q;
		}

		Quaternion<T> Rotate(const Quaternion<T>& q) const
		{
			return *this * q * Inverse();
		}

		Quaternion<T> Rotate(const Vec3<T>& axis, const T& angle)
		{
			T halfAngle = angle / 2;
			T sinHalfAngle = sin(degreesToRadians(halfAngle));
			T cosHalfAngle = cos(degreesToRadians(halfAngle));
			return Quaternion<T>(axis.X() * sinHalfAngle, axis.Y() * sinHalfAngle, axis.Z() * sinHalfAngle, cosHalfAngle);
		}

		// Rotate point p by a vector and an angle
		Vec3<T> Rotate(Vec3<T>& v, const T& angle, const Vec3<T>& p)
		{
			v.normalize();
			Quaternion<T> g = Rotate(v, angle);

			Quaternion<T> q(p.X(), p.Y(), p.Z(), 0);

			const Quaternion<T> pPrime(g * q * g.Conjugate());

			return  pPrime.getVectorPart();
		}

		static Quaternion<T> LerpQuaternion(Quaternion<T> a, Quaternion<T> b, float v)
		{
			if (a.Dot(b) < 0)
			{
				b = b.Negate();
			}

			return a - ((a - b) * v);
		}

		static Quaternion<T> NlerpQuaternion(Quaternion<T> a, Quaternion<T> b, float v)
		{
			return LerpQuaternion(a, b, v).Normalize();
		}

		static Quaternion<T> SlerpQuaternion(Quaternion<T> a, Quaternion<T> b, float v)
		{
			Quaternion<T> result;

			float theta = acos(a.Dot(b));
			float sinus = sin(theta);

			if (sinus == 0) return Quaternion<T>();

			float Wa = sin((1 - v) * theta) / sinus;
			float Wb = sin(v * theta) / sinus;

			result = a * Wa + b * Wb;

			result.Normalize();

			return result;
		}

		//Create Matrix3 from Quaternion
		Mat3<T> toMatrix3() const
		{
			Mat3<T> m;
			T xx = x * x;
			T xy = x * y;
			T xz = x * z;
			T xw = x * w;
			T yy = y * y;
			T yz = y * z;
			T yw = y * w;
			T zz = z * z;
			T zw = z * w;
			T ww = w * w;
			T wx = w * x;
			T wy = w * y;
			T wz = w * z;
			m[0][0] = 1 - 2 * yy - 2 * zz;
			m[0][1] = 2 * xy - 2 * wz;
			m[0][2] = 2 * xz + 2 * wy;

			m[1][0] = 2 * xy + 2 * wz;
			m[1][1] = 1 - 2 * xx - 2 * zz;
			m[1][2] = 2 * yz - 2 * wx;

			m[2][0] = 2 * xz - 2 * wy;
			m[2][1] = 2 * yz + 2 * wx;
			m[2][2] = 1 - 2 * xx - 2 * yy;

			return m;
		}

		//Create Matrix4 from Quaternion
		Mat4<T> toMatrix4() const
		{
			Mat4<T> m1;
			m1[0] = lm::Vec4<T>(w, z, -y, x);
			m1[1] = lm::Vec4<T>(-z, w, x, y);
			m1[2] = lm::Vec4<T>(y, -x, w, z);
			m1[3] = lm::Vec4<T>(-x, -y, -z, w);
			
			Mat4<T> m2;
			m2[0] = lm::Vec4<T>(w, z, -y, -x);
			m2[1] = lm::Vec4<T>(-z, w, x, -y);
			m2[2] = lm::Vec4<T>(y, -x, w, -z);
			m2[3] = lm::Vec4<T>(x, y, z, w);

			return m1 * m2;
		}

		//Create Quaternion from Matrix3
		Quaternion<T> fromMatrix3(const Mat3<T>& m)
		{
			T trace = m[0][0] + m[1][1] + m[2][2];
			T s = 0.0f;

			if (trace > 0)
			{
				s = sqrt(trace + 1.0f) * 2;
				x = (m[2][1] - m[1][2]) / s;
				y = (m[0][2] - m[2][0]) / s;
				z = (m[1][0] - m[0][1]) / s;
				w = 0.25f * s;
			}
			else if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
			{
				s = sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2;
				x = 0.25f * s;
				y = (m[0][1] + m[1][0]) / s;
				z = (m[0][2] + m[2][0]) / s;
				w = (m[2][1] - m[1][2]) / s;
			}
			else if (m[1][1] > m[2][2])
			{
				s = sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2;
				x = (m[0][1] + m[1][0]) / s;
				y = 0.25f * s;
				z = (m[1][2] + m[2][1]) / s;
				w = (m[0][2] - m[2][0]) / s;
			}
			else
			{
				s = sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2;
				x = (m[0][2] + m[2][0]) / s;
				y = (m[1][2] + m[2][1]) / s;
				z = 0.25f * s;
				w = (m[1][0] - m[0][1]) / s;
			}

			return *this;
		}

		T& operator[](const int index)
		{
			switch (index)
			{
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			case 3:
				return this->w;
			default:
				return this->x;
			}
		}

		T& operator[](const int index) const
		{
			switch (index)
			{
			case 0:
				return this->x;
			case 1:
				return this->y;
			case 2:
				return this->z;
			case 3:
				return this->w;
			default:
				return this->x;
			}
		}

		T& X()
		{
			return this->x;
		}

		T& X() const
		{
			return this->x;
		}

		T& Y()
		{
			return this->y;
		}

		T& Y() const
		{
			return this->y;
		}

		T& Z()
		{
			return this->z;
		}

		T& Z() const
		{
			return this->z;
		}

		T& W()
		{
			return this->w;
		}

		T& W() const
		{
			return this->w;
		}
	};

	typedef Quaternion<float> Quatf;
}
