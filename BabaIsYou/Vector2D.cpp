#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.f;
	y = 0.f;
}

Vector2D::Vector2D(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2D Vector2D::Add(const Vector2D& vec)
{
	Vector2D myvec(x, y);
	myvec.x += vec.x;
	myvec.y += vec.y;

	return myvec;
}

Vector2D Vector2D::Sub(const Vector2D& vec)
{
	Vector2D myvec(x, y);
	myvec.x -= vec.x;
	myvec.y -= vec.y;

	return myvec;
}

Vector2D Vector2D::Mul(const Vector2D& vec)
{
	Vector2D myvec(x, y);
	myvec.x *= vec.x;
	myvec.y *= vec.y;

	return myvec;
}

Vector2D Vector2D::Div(const Vector2D& vec)
{
	Vector2D myvec(x, y);
	myvec.x /= vec.x;
	myvec.y /= vec.y;

	return myvec;
}

Vector2D operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Sub(v2);
}

Vector2D operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Mul(v2);
}

Vector2D operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Div(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

bool Vector2D::operator==(const Vector2D& vec)
{
	if (x == vec.x && y == vec.y)
		return true;

	return false;
}

Vector2D Vector2D::operator+(const int i)
{
	Vector2D vec(x, y);
	vec.x += i;
	vec.y += i;

	return vec;
}

Vector2D Vector2D::operator+(const float f)
{
	Vector2D vec(x, y);
	vec.x += f;
	vec.y += f;

	return vec;
}

Vector2D Vector2D::operator*(const int i)
{
	Vector2D vec(x, y);
	vec.x *= i;
	vec.y *= i;

	return vec;
}

Vector2D Vector2D::operator*(const float f)
{
	Vector2D vec(x, y);
	vec.x *= f;
	vec.y *= f;

	return vec;
}

bool Vector2D::operator>(Vector2D& v1)
{
	if(x > v1.x || y > v1.y)
		return true;

	return false;
}
bool Vector2D::operator<(Vector2D& v1)
{
	if (x < v1.x || y < v1.y)
		return true;

	return false;
}

Vector2D& Vector2D::Zero()
{
	x = 0;
	y = 0;

	return *this;
}

int Vector2D::Size()
{
	if(x != 0)
		return static_cast<int>(x);
	else
		return static_cast<int>(y);
}

void Vector2D::RoundVectorf()
{
	x = roundf(x);
	y = roundf(y);
}