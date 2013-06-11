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

#define DEBUG 1

using namespace std;
using namespace CGAL;

typedef Cartesian<double>                R;
typedef Point_2<R>                       Point;
typedef Creator_uniform_2<double,Point>  Creator;
typedef std::vector<Point>               Vector;

class points_2d {
	private:
		double x;
		double y;

	public:
		void setValue(double i, double j)
		{
			x = i;
			y = j;
			if(DEBUG == 0) 
				cout<<x<<","<<y<<"\n";
		}

		void printVal()
		{
			cout<<x<<","<<y<<"\n";
		}
};

int main(int argc, char *argv[])
{
	Vector points;
	vector<points_2d> mypoints;
	points_2d *p; //to insert points into the vector
	int in_size = atof(argv[1]);
	points.reserve(in_size);
	mypoints.reserve(in_size);
	ofstream fout;
	ifstream fin;
	
	fout.open("/Users/rutayanpatro/iBlob/points.txt",ios::out|ios::trunc); 
	
	Random_points_in_square_2<Point,Creator> g(1,default_random);
	CGAL::copy_n( g, in_size, std::back_inserter(points));
	for (int i=0; i < in_size; i++){	
		fout<<points[i].x()<<","<<points[i].y()<<"\n";
		if(DEBUG == 1)
			cout<<points[i].x()<<","<<points[i].y()<<"\n"; 
	}
	
	if(DEBUG == 1) 
		cout<<"------------\n";
	fout.close();

	fin.open("/Users/rutayanpatro/iBlob/points.txt",ios::in);
	
	string x,y;
	int temp=0,i=0;
	string line,token;
	stringstream iss;
	while ( getline(fin, line) )
	{
		iss << line;
		while ( getline(iss, token, ',') )
		{
			if(temp ==0){
				x= token;
				temp = 1;
			}else{
				y=token;
				temp = 0;
			}
			
			if(temp == 0){
				if(DEBUG == 0) cout<<x<<","<<y<<"\n";
				p = new points_2d;
				p->setValue(atof(x.c_str()),atof(y.c_str()));
				
				mypoints.push_back(*p);
				
			}
		}
		iss.clear();
	
	}
	if(DEBUG == 1){
		for(i=0;i<in_size; i++){
	        	mypoints[i].printVal();
		}
	}
	fin.close();
}

