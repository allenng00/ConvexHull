/*

*/


#include "Point2D.h"

static const Point2D gCoordinateOrigin;

// Direction (angle) of point w.r.t. aOther
double Point2D::directionTo(const Point2D& aOther) const {
	return this->fPosition.angleBetween(aOther.fPosition);
}

// Length (or magnitude) of point w.r.t. aOther
double Point2D::magnitudeTo(const Point2D& aOther) const {
	Vector2D temp = this->fPosition - aOther.fPosition;

	return temp.magnitude();
}

Point2D::Point2D() {
	this->fPosition = Vector2D(0, 0);
	this->setOrigin(gCoordinateOrigin);
}

Point2D::Point2D(const std::string& aId, double aX, double aY) {
	this->fId = aId;
	this->fPosition.setX(aX);
	this->fPosition.setY(aY);
	this->setOrigin(gCoordinateOrigin);
}

Point2D::Point2D(std::istream& aIStream) {
	double x, y;
	aIStream >> this->fId >> x >> y;
	this->setX(x);
	this->setY(y);
	this->setOrigin(gCoordinateOrigin);
}

// getters & setters
const std::string& Point2D::getId() const {
	return this->fId;
}

void Point2D::setX(const double& aX) {
	this->fPosition.setX(aX);
}

const double Point2D::getX() const {
	return this->fPosition.getX();
}

void Point2D::setY(const double& aY) {
	this->fPosition.setY(aY);
}

const double Point2D::getY() const {
	return this->fPosition.getY();
}

void Point2D::setOrigin(const Point2D& aPoint) {
	this->fOrigin = aPoint.fOrigin;
}

const Point2D& Point2D::getOrigin() const {
	return *(this->fOrigin);
}

// 2D vector this - aRHS
Vector2D Point2D::operator-(const Point2D& aRHS) const {
	Vector2D result;

	double x = this->fPosition.getX() - aRHS.fPosition.getX();
	double y = this->fPosition.getY() - aRHS.fPosition.getY();

	result.setX(x);
	result.setY(y);

	return result;
}

// Direction (angle) of point w.r.t. origin
double Point2D::direction() const {
	return this->fPosition.direction();
}

// Length (or magnitude) of point w.r.t. origin
double Point2D::magnitude() const {
	return this->fPosition.magnitude();
}

// Are this point and aOther on the same line segment?
bool Point2D::isCollinear(const Point2D& aOther) const {
	double
		x1 = this->fPosition.getX(),
		x2 = aOther.fPosition.getX(),
		y1 = this->fPosition.getY(),
		y2 = aOther.fPosition.getY();

	if (x1 == 0 && x2 == 0) {
		return !(abs(y1 - y2) < epsilon);
	}
	else if (y1 == 0 && y2 == 0) {
		return !(abs(x1 - x2) < epsilon);
	}
	else {
		return (abs(x1 / x2 - y1 / y2) < epsilon);
	}
}

// Does line segment this-aP2 make a right turn at this point?
bool Point2D::isClockwise(const Point2D& aP0, const Point2D& aP2) const {
	Vector2D p0p2 = aP2 - aP0;
	Vector2D p0p1 = *this - aP0;

	return (p0p2.cross(p0p1) > 0);
}

// Is this' y-coordinate less than aRHS's y-coordinate?
// If there is a tie, this' x-coordinate less than aRHS's x-coordinate?
bool Point2D::operator<(const Point2D& aRHS) const {
	double
		x1 = this->fPosition.getX(),
		x2 = aRHS.fPosition.getX(),
		y1 = this->fPosition.getY(),
		y2 = aRHS.fPosition.getY();

	if (y2 - y1 > epsilon) {
		return true;
	}
	else if (abs(y2 - y1) < epsilon) {
		return (x1 - x2 < epsilon);
	}

	return false;
}

void Point2D::operator=(const Point2D aRHS) {
	this->fId = aRHS.fId;
	this->setX(aRHS.getX());
	this->setY(aRHS.getY());
}
// I/O for 2D points
std::ostream& operator<<(std::ostream& aOStream, const Point2D& aObject) {
	aOStream << aObject.fId << ": ("
		<< aObject.fPosition.getX() << ","
		<< aObject.fPosition.getY() << ")";
	return aOStream;
}

std::istream& operator>>(std::istream& aIStream, Point2D& aObject) {
	double x, y;
	aIStream >> aObject.fId >> x >> y;
	aObject.setX(x);
	aObject.setY(y);
	return aIStream;
}