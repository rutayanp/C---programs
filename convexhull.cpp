#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <omp.h>
#include <stdio.h>

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
int insize;						//total no. of points in input
int nthreads, tid;
int size_up; 					//no. of elements in the upoints
points_2d *upoints;
//vector<points_2d> upoints;	//upper points

double crossproduct(points_2d *v, int p0, int p1, int p2)
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

	if (DEBUG == 1)
		cout << "the 2nd element is : " << second <<"\n";

	return second;
}

void upperch (points_2d *up)
{
	int i, first = 0;
	int size; //size of the result stack
	std::stack<int> s;
	int blocksize;

	//blocksize = up.size()/nthreads;
	//first = tid * blocksize;

	s.push(first); //push the index of first element in the stack
	s.push(first + 1);	//push the index of second element in the stack
//	#pragma omp parallel private(i)
	{
		for (i= first + 2 ; i < first + size_up; i++){
			while (s.size() > 1 && crossproduct(up, second(s), i, s.top()) > 0){
				if(DEBUG == 1)
					cout << "popped element" << s.top() << "\n";
				s.pop();
			}
			s.push(i);
		}
	}

	if (DEBUG == 1)
		cout << "size of stack " << s.size() << "\n";

	size = s.size();

	int index; //for debug purpose only
	if(DEBUG == 1){
		cout << "-------\n";
		for(i = 0; i < size ; i++){
			index = s.top();
			cout << up[index].x() << "," << up[index].y() << "\n";
			s.pop();
		}

	}

}

points_2d hullupperpoints(points_2d *v)
{
	int i, j=0;
	double tmp;
	bool val;
	//points_2d upoints[insize];
	upoints = new points_2d[insize];
	#pragma omp for private(i, tmp)
		for(i=0; i<insize; i++){
			tmp = crossproduct(v, 0, i, 9);
			if(tmp >= 0){
				upoints[j].setVal(v[i].x(),v[i].y());
				j++;
				size_up++;
				//upoints.push_back(v[i]);
			}
		}

	if(DEBUG == 1){
		cout << "-----------------\n";
		for(i = 0; i< size_up ; i++){
			cout<< upoints[i].x() << "," << upoints[i].y() << "\n";
		}
	}

	//upperch(upoints);
}

int main(int argc, char *argv[])
{

	insize = atoi(argv[1]);
	points_2d *p;
	points_2d *points;
	points = new points_2d[insize];
	p = new points_2d[insize];
	double tmp; //to store the result of the test cross product
	bool val; //to store if it is clock wise or not ...TRUE = CW FALSE = CCW

	nthreads = omp_get_max_threads();
	omp_set_num_threads(nthreads);

	p[0].setVal(0,0);
	p[1].setVal(0.5,0.5);
	p[2].setVal(1,-0.5);
	p[3].setVal(1,7);
	p[4].setVal(1.5, -2);
	p[5].setVal(1.8, -3);
	p[6].setVal(2,8);
	p[7].setVal(3,4);
	p[8].setVal(3.5,7);
	p[9].setVal(4,-0.2);
	
	if( DEBUG == 1){
		for(int i=0; i<insize;i++){
			cout<<p[i].x()<<","<<p[i].y()<<"\n";
		}
	}

	for(int i=0; i<insize;i++){
		points[i] = p[i];
	}

	if(DEBUG == 1){
		cout<<"------------\n";
		for(int i=0; i<insize;i++){
			cout<<points[i].x()<<","<<points[i].y()<<"\n";
		}
	}

	#pragma omp parallel
	{
		tid = omp_get_thread_num();
		printf("hello form thread : %d \n",tid); //because cout is not thread safe ....
	}

	hullupperpoints(points);
	upperch(upoints);

	return 0;

}
