#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>

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

//GLOBAL VARIABLES
int insize; //total no. of points in input
vector<points_2d> upoints; //upper points

double crossproduct(vector<points_2d> &v, int p0, int p1, int p2)
{
	double crossproduct;
	crossproduct = ((v[p2].x() - v[p0].x()) * (v[p1].y() - v[p0].y())) - ((v[p1].x() - v[p0].x()) * (v[p2].y() - v[p0].y()));
	return crossproduct;
}

int second (std::stack<int> s)
{
	int tmp, second;
	tmp = s.top();
	s.pop();
	second = s.top();
	s.push(tmp);
	return second;
}

void upperch (vector<points_2d> &up)
{
	int i, first = 0;
	std::stack<int> s;
	//vector<points_2d> temp;
	s.push(first); //push the index of first element in the stack
	s.push(first + 1);	//push the index of second element in the stack

	for (i= 2 ; i < up.size(); i++){
		while (s.size() >1 && crossproduct(up, second(s), i, s.top()) > 0){
			s.pop();
		}
		s.push(i);
	}

	int index; //for debug purpose only
	if(DEBUG == 1){
		cout << "hello\n";
		for(i = 0; i < s.size() ; i++){
			index = s.top();
			cout << up[index].x() << "," << up[index].y() << "\n";
			//temp.push_back(up[index]);
			s.pop();
		}

		/*for(i = 0; i < s.size ; i++){
			cout << temp[i].x() << "," << temp[i].y() << "\n";
		}*/
	}

}

points_2d hullupperpoints(vector<points_2d> &v)
{
	int i;
	double tmp;
	bool val;
	for(i=1; i<insize-1; i++){
		tmp = crossproduct(v, 0, i, 9);
		if(tmp > 0){
			upoints.push_back(v[i]);
		}
	}

	if(DEBUG == 1){
		cout << "-----------------\n";
		for(i = 0; i< upoints.size() ; i++){
			cout<< upoints[i].x() << "," << upoints[i].y() << "\n";
		}
	}

	upperch(upoints);
}

int main(int argc, char *argv[])
{

	insize = atoi(argv[1]);
	points_2d *p;
	vector<points_2d> points;
	points.reserve(insize);
	p = new points_2d[insize];
	double tmp; //to store the result of the test cross product
	bool val; //to store if it is clock wise or not ...TRUE = CW FALSE = CCW

	p[0].setVal(0,0);
	p[1].setVal(0.5,0.5);
	p[2].setVal(1,-0.5);
	p[3].setVal(1,3);
	p[4].setVal(1.5, -2);
	p[5].setVal(1.8, -3);
	p[6].setVal(2,1);
	p[7].setVal(3,4);
	p[8].setVal(3.5,7);
	p[9].setVal(4,-0.2);
	
	if( DEBUG == 1){
		for(int i=0; i<insize;i++){
			cout<<p[i].x()<<","<<p[i].y()<<"\n";
		}
	}

	for(int i=0; i<insize;i++){
		points.push_back(p[i]);
	}

	if(DEBUG == 1){
		cout<<"------------\n";
		for(int i=0; i<insize;i++){
			cout<<points[i].x()<<","<<points[i].y()<<"\n";
		}
	}

	hullupperpoints(points);
	return 0;

}
