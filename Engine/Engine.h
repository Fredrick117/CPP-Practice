#pragma once

void InitializeEngine();

class Point2D
{
public:
	int x;
	int y;

	Point2D();
	Point2D(int _x, int _y);
	Point2D(const Point2D& copy);

	Point2D operator+(Point2D& other);	// Addition
	Point2D operator-(Point2D& other);	// Subtraction
	Point2D operator-();	// Negation
	friend Point2D operator*(Point2D&other, int i);	// Multiplication (integer on right)
	friend Point2D operator*(int i, Point2D& other);
	Point2D operator/(int i);	// Division
	Point2D& operator=(Point2D other);	// Assignment
	Point2D& operator+=(Point2D other);	// Addition assignment
	Point2D& operator-=(Point2D other); // Subtraction assignment
	Point2D& operator*=(int i);		// Multiplication assignment
	Point2D& operator/=(int i);		// Division assignment
	bool operator!=(const Point2D& other);
	bool operator==(const Point2D& other) const;
};