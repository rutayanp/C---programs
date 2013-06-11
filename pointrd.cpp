#include <iostream>
#include <fstream>
#include <string>
#include <CGAL/basic.h>
#include <cassert>
#include <vector>
#include <algorithm>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/copy_n.h>
#include <CGAL/random_selection.h>
#include <stdlib.h>
using namespace std;
using namespace CGAL;

typedef Cartesian<double>                R;
typedef Point_2<R>                       Point;
typedef Creator_uniform_2<double,Point>  Creator;
typedef std::vector<Point>               Vector;

int main(int argc, char *argv[])
{
	Vector points;

	int in_size = atof(argv[1]);
	points.reserve(in_size);
	fstream fout;
	
	fout.open("/Users/rutayanpatro/iBlob/points.txt",ios::out|ios::trunc); 
	
	Random_points_in_square_2<Point,Creator> g(1,default_random);
	CGAL::copy_n( g, in_size, std::back_inserter(points));
	for (int i=0; i < in_size; i++){	
		fout<<points[i].x()<<","<<points[i].y()<<"\n";
		cout<<points[i].x()<<","<<points[i].y()<<"\n"; 
	}

	fout.close();
}

