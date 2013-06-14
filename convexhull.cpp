#include <iostream>
#include <stdlib.h>
#include <vector>

#define DEBUG 1

using namespace std;

class points_2d{

private:
	double i;
	double j;

public:
	points_2d()
	{
		i = 0;
		j = 0;
	}

	void setVal(double x, double y)
	{
		i = x;
		j = y;
	}

	double x()
	{
		return i;
	}

	double y()
	{
		return j;
	}
};

void hullupperpoints(vector<points_2d> &v){

}

int main(int argc, char *argv[])
{
	int insize; //total no. of points in input

	insize = atoi(argv[1]);
	points_2d *p;
	vector<points_2d> points;
	points.reserve(insize);
	p = new points_2d[insize];


	p[0].setVal(0,0);
	p[1].setVal(0.5,0.5);
	p[2].setVal(1,-0.5);
	p[3].setVal(1,3);
	p[4].setVal(1.5, -2);
	p[5].setVal(1.8, -3);
	p[6].setVal(2,1);
	p[7].setVal(3,4);
	p[8].setVal(3.5,7);
	p[9].setVal(4,-4);
	
	if( DEBUG == 1){
		for(int i=0; i<insize;i++){
			cout<<p[i].x()<<","<<p[i].y()<<"\n";
		}
	}

	for(int i=0; i<insize;i++){
		points.push_back(p[i]);
	}


	if( DEBUG == 1){
			cout<<"------------\n";
			for(int i=0; i<insize;i++){
				cout<<points[i].x()<<","<<points[i].y()<<"\n";
			}
		}

	hullupperpoints(points);
	return 0;

}
