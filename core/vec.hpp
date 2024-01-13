#pragma once

class Vec {
public:
	float x, y;

	Vec() {
		x = y = 0.0f;
	};
	Vec(float _x, float _y) {
		x = _x; y = _y;
	}

	Vec& add(const Vec& v) {
		x += v.x; y += v.y;
		return *this;
	}
	Vec& sub(const Vec& v) {
		x -= v.x; y -= v.y;
		return *this;
	}
	Vec& mul(const Vec& v) {
		x *= v.x; y *= v.y;
		return *this;
	}
	Vec& div(const Vec& v) {
		x /= v.x; y /= v.y;
		return *this;
	}

	friend Vec& operator+(Vec v1, const Vec& v2) {
		return v1.add(v2);
	}
	friend Vec& operator-(Vec v1, const Vec& v2) {
		return v1.sub(v2);
	}
	friend Vec& operator*(Vec v1, const Vec& v2) {
		return v1.mul(v2);
	}
	friend Vec& operator/(Vec v1, const Vec& v2) {
		return v1.div(v2);
	}

	Vec& operator+=(const Vec& v) {
		return add(v);
	}
	Vec& operator-=(const Vec& v) {
		return sub(v);
	}
	Vec& operator*=(const Vec& v) {
		return mul(v);
	}
	Vec& operator/=(const Vec& v) {
		return div(v);
	}
};