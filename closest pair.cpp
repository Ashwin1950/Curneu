#include <bits/stdc++.h>
#include<windows.h> 
using namespace std; 

#define min(x,y) ((x) < (y))? (x) : (y)

class Point 
{ 
	public: 
	float x, y; 
}points[2]; 


int compareX(const void* a, const void* b) ;
int compareY(const void* a, const void* b) ;
float dist(Point p1, Point p2) ;
float bruteForce(Point P[], int n) ;
float stripClosest(Point strip[], int size, float d) ;
int abs(int x) ;
float closestUtil(Point P[], int n) ;
float closest(Point P[], int n) ;

int main() 
{ 
	Point P[100];
	/*P[0].x=0.5;
	P[0].y=0.3;
	P[1].x=0.9;
	P[1].y=0.3;
	P[2].x=0.63;
	P[2].y=0.38;
	P[3].x=0.03;
	P[3].y=0.49;*/
	//P[0].setXY(9,3);
	//P[1].setXY(5,4); 
	for(int i=0;i<100;i++){
		P[i].x=(rand()%100)/float(100);
		//cout<<P[i].x<<" ";
		P[i].y=(rand()%100)/float(100);
		//cout<<P[i].y<<"\n";
	}
	int n = sizeof(P) / sizeof(P[0]); 
	cout << "The Smallest Distance among the " << n << " random points is : " << closest(P, n) << endl; 
	cout << "The Closest Points are : " << endl;
	cout << points[0].x << "," << points[0].y << endl;
	cout << points[1].x << "," << points[1].y << endl;
	/*for(int i=0;i<10;i++){
		//P[i].x=(rand()%100)/float(100);
		cout<<P[i].x<<" ";
		//P[i].y=(rand()%100)/float(100);
		cout<<P[i].y<<"\n";
	}*/
	return 0; 
} 


int compareX(const void* a, const void* b) 
{ 
	Point *p1 = (Point *)a, *p2 = (Point *)b; 
	return (p1->x - p2->x); 
} 

int compareY(const void* a, const void* b) 
{ 
	Point *p1 = (Point *)a, *p2 = (Point *)b; 
	return (p1->y - p2->y); 
} 

float dist(Point p1, Point p2) 
{ 
	return sqrt( ((p1.x - p2.x)*(p1.x - p2.x) + 
				(p1.y - p2.y)*(p1.y - p2.y) )
			); 
} 

float bruteForce(Point P[], int n) 
{ 
	float min = 1.1; 
	for (int i = 0; i < n; i++) 
		for (int j = i+1; j < n; j++) 
			if (dist(P[i], P[j]) < min) {
				min = dist(P[i], P[j]);
				points[0]=P[i];
				points[1]=P[j]; 
			}
	return min; 
} 

float stripClosest(Point strip[], int size, float d) 
{ 
	float min = d;

	qsort(strip, size, sizeof(Point), compareY); 

	for (int i = 0; i < size; ++i) 
		for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) 
			if (dist(strip[i],strip[j]) < min) {
				min = dist(strip[i], strip[j]); 
				points[0]=strip[i];
				points[1]=strip[j];
			}

	return min; 
} 

int abs(int x)
{
	if(x<0)
		x=-x;
	return x;
}

float closestUtil(Point P[], int n) 
{ 
	if (n <= 3) 
		return bruteForce(P, n); 
	int mid = n/2; 
	Point midPoint = P[mid]; 
 
	float dl = closestUtil(P, mid); 
	float dr = closestUtil(P + mid, n - mid); 

	float d = min(dl, dr); 
	Point strip[n];
	int j = 0; 
	for (int i = 0; i < n; i++) 
		if (abs(P[i].x - midPoint.x) < d) {
			strip[j] = P[i];
			j++;
		}
			
	return min(d, stripClosest(strip, j, d) );
} 

float closest(Point P[], int n) 
{ 
	qsort(P, n, sizeof(Point), compareX); 
	return closestUtil(P, n); 
} 

