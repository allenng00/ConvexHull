/*

*/

#include "Vector2D.h"

// 2D vector constructor; default is unit vector î
Vector2D::Vector2D(double aX, double aY) {
	this->fX = aX;
	this->fY = aY;
}

// getters & setters for x and y coordinates
void Vector2D::setX(double aX) {
	this->fX = aX;
}
double Vector2D::getX() const {
	return this->fX;
}
void Vector2D::setY(double aY) {
	this->fY = aY;
}
double Vector2D::getY() const {
	return this->fY;
}

// 2D vector addition: this + aRHS; returns a fresh 2D vector
Vector2D Vector2D::operator+(const Vector2D& aRHS) const {
	Vector2D temp(0, 0);

	temp.setX(this->getX() + aRHS.getX());
	temp.setX(this->getY() + aRHS.getY());

	return temp;
}

// 2D vector subtraction: this - aRHS; returns a fresh 2D vector
Vector2D Vector2D::operator-(const Vector2D& aRHS) const {
	Vector2D temp(0, 0);

	temp.setX(this->getX() - aRHS.getX());
	temp.setX(this->getY() - aRHS.getY());

	return temp;
}

// Length (or magnitude) of a 2D vector
double Vector2D::magnitude() const {
	double length = sqrt(
		pow(this->getX(), 2)
		+ pow(this->getY(), 2)
	);

	return length;
}

// Direction (angle) of 2D vector
// The angle is the tangent of y divided by x (hint: atan2)
double Vector2D::direction() const {
	double angle = atan2(
		this->getY(),
		this->getX()
	);

	//if (angle < 0) {
	//	angle += 2 * pi;
	//}

	return angle;
}

// Inner product (scalar product) of two 2D vectors
// Does not require angle between vectors
double Vector2D::dot(const Vector2D& aRHS) const {
	double result =
		this->getX() * aRHS.getX() +
		this->getY() * aRHS.getY();

	return result;
}

// In 2D, the cross product of two 2D vectors is
// the determinate of the matrix
//
//        | x1 x2 |
//    det |       | = x1*y2 - x2*y1
//        | y1 y2 |
//
double Vector2D::cross(const Vector2D& aRHS) const {
	double result =
		this->getX() * aRHS.getY() -
		this->getY() * aRHS.getX();

	return result;
}

// Angle between two 2D vectors
// The function must properly handle null vectors = [0,0]
// and return an angle consistent with the dot product.
double Vector2D::angleBetween(const Vector2D& aRHS) const {
	double angle;

	if (this == NULL) {
		return aRHS.direction();
	}
	else {
		angle = acos(
			this->dot(aRHS) /
			(this->magnitude() * aRHS.magnitude()));
	}

	return angle;
}


// I/O for 2D vectors
std::ostream& operator<<(std::ostream& aOutStream, const Vector2D& aObject) {
	aOutStream << "["
		<< aObject.fX << ","
		<< aObject.fY << "]";

	return aOutStream;
}
std::istream& operator>>(std::istream& aInStream, Vector2D& aObject) {
	aInStream >> aObject.fX >> aObject.fY;

	return aInStream;
}