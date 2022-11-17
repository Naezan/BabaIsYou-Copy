#pragma once
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float _x, float _y);

	Vector2D Add(const Vector2D& vec);
	Vector2D Sub(const Vector2D& vec);
	Vector2D Mul(const Vector2D& vec);
	Vector2D Div(const Vector2D& vec);
	
	friend Vector2D operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);
	
	bool operator==(const Vector2D& vec);

	Vector2D operator+(const int i);
	Vector2D operator+(const float f);
	Vector2D operator*(const int i);
	Vector2D operator*(const float f);

	bool operator>(Vector2D& v1);
	bool operator<(Vector2D& v1);

	Vector2D& Zero();
	int Size();
	void RoundVectorf();
};

