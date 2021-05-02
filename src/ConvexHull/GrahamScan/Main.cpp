/*

   Convex Hull, COS30008, 2021

*/

#include "Point2DSet.h"

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	Point2DSet lSet;

	lSet.populate("points.txt");

	cout << "Points:" << endl;
	Point2D temp("id", 11, 6);

	for (const Point2D& p : lSet)
	{
		cout << boolalpha << p << " " 
			<< p.isCollinear(temp) << endl;
	}

	//Point2DSet lConvexHull;

	//lSet.buildConvexHull( lConvexHull );

	//cout << "Convex hull:" << endl;

	//size_t lSize = lConvexHull.size();

	//for ( size_t i = 0; i < lSize; i++ )
	//{
	//    cout
	//        << lConvexHull[i].getId()
	//        << " - "
	//        << lConvexHull[(i + 1) % lSize].getId() << endl;
	//}

	return 0;
}
