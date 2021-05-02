/*

	Point Set, COS30008, 2021, v0.1

 */

#include "Point2DSet.h"

 // Add a 2D point to set
void Point2DSet::add(const Point2D& aPoint) {
	this->fPoints.push_back(aPoint);
}
void Point2DSet::add(Point2D&& aPoint) {
	this->fPoints.push_back(aPoint);
}

// Remove the last point in the set
void Point2DSet::removeLast() {
	this->fPoints.pop_back();
}

// Tests aPoint, returns true if aPoint makes no left turn
bool Point2DSet::doesNotTurnLeft(const Point2D& aPoint) const {
	size_t size = this->size();
	Point2D p1 = this->operator[](size - 1);
	Point2D p0 = this->operator[](size - 2);

	if ((aPoint.isCollinear(p1) && aPoint.isCollinear(p0))
		|| (p1.isClockwise(p0, aPoint))) {
		return true;
	}
	return false;
}

// Load 2D points from file
void Point2DSet::populate(const std::string& aFileName) {
	std::ifstream is(aFileName);

	std::string tempStr = "empty";
	Point2D tempPoint;
	std::stringstream ss;

	if (is.good()) {
		std::getline(is, tempStr);

		while (!tempStr.empty()) {
			ss.clear();
			ss << tempStr;
			ss >> tempPoint;
			this->add(tempPoint);

			std::getline(is, tempStr);
		};
	}
}

// Run Graham's scan using out parameter aConvexHull
void Point2DSet::buildConvexHull(Point2DSet& aConvexHull) {
	size_t pos = 1;
	size_t size = this->size();
	Point2D tempPoint;
	Comparator byCoord = &orderByCoordinates;
	Comparator byAngle = &orderByPolarAngle;

	// Get p0
	if (size != 0) {
		this->sort(byCoord);
		aConvexHull.fPoints.push_back(this->operator[](0));
		this->fPoints.erase(this->begin());
		this->sort(byAngle);

		for (pos; pos < size && pos < 3; pos++) {
			aConvexHull.fPoints.push_back(this->operator[](pos));
		}

		if (size < 3) {
			return;
		}
		else {

			for (pos; pos < size; pos++) {
				tempPoint = this->operator[](pos);

				while (this->doesNotTurnLeft(tempPoint)) {
					aConvexHull.fPoints.pop_back();
				}

				this->fPoints.push_back(tempPoint);
			}
		}
	}
}

// Returns numner of elements in set
size_t Point2DSet::size() const {
	return this->fPoints.size();
}

// Clears set
void Point2DSet::clear() {
	this->fPoints.clear();
}

// Sort set using stable_sort on vectors
void Point2DSet::sort(Comparator aComparator) {
	std::stable_sort(this->begin(), this->end(), aComparator);
}

// Indexer for set
const Point2D& Point2DSet:: operator[](size_t aIndex) const {
	return this->fPoints[aIndex];
}

// Iterator methods
Point2DSet::Iterator Point2DSet::begin() const {
	return this->fPoints.begin();
}
Point2DSet::Iterator Point2DSet::end() const {
	return this->fPoints.end();
}

bool orderByCoordinates(const Point2D& aLeft, const Point2D& aRight) {
	return aLeft < aRight;
}

bool orderByPolarAngle(const Point2D& aLHS, const Point2D& aRHS) {
	return
		aLHS.direction()
		< aRHS.direction();
}