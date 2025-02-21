#pragma once
#include <cmath>

namespace vector {
	struct vec2
	{
		float x, y;

		vec2() : x(0), y(0) {}
		vec2(float x, float y) : x(x), y(y) {}

		// 基本运算符重载
		vec2 operator+(const vec2& other) const {
			return { x + other.x, y + other.y };
		}
		vec2 operator-(const vec2& other) const {
			return { x - other.x, y - other.y };
		}
		vec2 operator*(float scalar) const {
			return { x * scalar, y * scalar };
		}
		vec2 operator/(float scalar) const {
			return { x / scalar, y / scalar };
		}

		// 点积、叉积、归一化、长度
		float Dot(const vec2& other) const {
			return x * other.x + y * other.y;
		}
		float Cross(const vec2& other) const {
			return x * other.y - y * other.x;
		}
		float Magnitude() const {
			return std::sqrt(x * x + y * y);
		}
		vec2 Normalized() const {
			float mag = Magnitude();
			return mag != 0 ? (*this) / mag : vec2();
		}
	};

	struct vec3 {
		float x, y, z;

		vec3() : x(0), y(0), z(0) {}
		vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		vec3 operator+(const vec3& other) const {
			return { x + other.x, y + other.y, z + other.z };
		}
		vec3 operator-(const vec3& other) const {
			return { x - other.x, y - other.y, z - other.z };
		}
		vec3 operator*(float scalar) const {
			return { x * scalar, y * scalar, z * scalar };
		}
		vec3 operator/(float scalar) const {
			return { x / scalar, y / scalar, z / scalar };
		}

		// 向量运算
		float Dot(const vec3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}
		vec3 Cross(const vec3& other) const {
			return {
				y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x
			};
		}
		float Magnitude() const {
			return std::sqrt(x * x + y * y + z * z);
		}
		vec3 Normalized() const {
			float mag = Magnitude();
			return mag != 0 ? (*this) / mag : vec3();
		}
	};

	struct vec4 {
		float x, y, z, w;

		vec4() : x(0), y(0), z(0), w(0) {}
		vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		vec4 operator+(const vec4& other) const {
			return { x + other.x, y + other.y, z + other.z, w + other.w };
		}
		vec4 operator-(const vec4& other) const {
			return { x - other.x, y - other.y, z - other.z, w - other.w };
		}
		vec4 operator*(float scalar) const {
			return { x * scalar, y * scalar, z * scalar, w * scalar };
		}
		vec4 operator/(float scalar) const {
			return { x / scalar, y / scalar, z / scalar, w / scalar };
		}

		// 向量运算
		float Dot(const vec4& other) const {
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}
		float Magnitude() const {
			return std::sqrt(x * x + y * y + z * z + w * w);
		}
		vec4 Normalized() const {
			float mag = Magnitude();
			return mag != 0 ? (*this) / mag : vec4();
		}
	};
}