""#include <stdio.h>
#include <assert.h>
#include "Engine.h"

#pragma region Point2D class
Point2D::Point2D(int _x, int _y)
{
	x = _x;
	y = _y;
}

Point2D::Point2D()
{
	x = 0;
	y = 0;
}

Point2D::Point2D(const Point2D& copy) : x(copy.x), y(copy.y)
{ }

Point2D Point2D::operator+(Point2D& other)
{
	return Point2D(x + other.x, y + other.y);
}

Point2D Point2D::operator-(Point2D& other)
{
	return Point2D(x - other.x, y - other.y);
}

Point2D Point2D::operator-()
{
	return Point2D(x *= -1, y *= -1);
}

Point2D operator*(Point2D& other, int i)
{
    return Point2D(other.x * i, other.y * i);
}

Point2D operator*(int i, Point2D& other)
{
    return Point2D(i * other.x, i * other.y);
}

Point2D Point2D::operator/(int i)
{
	return Point2D(x / i, y / i);
}

Point2D& Point2D::operator=(Point2D other)
{
	x = other.x;
	y = other.y;
    return *this;
}

Point2D& Point2D::operator+=(Point2D other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Point2D& Point2D::operator-=(Point2D other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Point2D& Point2D::operator*=(int i)
{
	x *= i;
	y *= i;
	return *this;
}

Point2D& Point2D::operator/=(int i)
{
	x /= i;
	y /= i;
	return *this;
}

bool Point2D::operator!=(const Point2D& other)
{
    return (x != other.x || y != other.y);
}

bool Point2D::operator==(const Point2D& other) const
{
    return (x == other.x && y == other.y);
}
#pragma endregion Point2D class

void InitializeEngine()
{
    printf("Initializing engine!");
}