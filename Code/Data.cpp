#include "Data.h"
#include <fstream>
#include <iostream>

using namespace std;

Data Data::instance;

Data::Data()
{

}

void Data::load(const char* filename)
{
	fstream fin(filename, ios::in);
	if(!fin)
	{
		cerr<<"# ERROR: Couldn't open file "<<filename<<"."<<endl;
		return;
	}

	// Just in case it has been loaded previously, delete stuff
	t.resize(0); y.resize(0);

	double temp1, temp2;
	while(fin>>temp1 && fin>>temp2)
	{
		t.push_back(temp1);
		y.push_back(temp2);
	}
	cout<<"# Loaded "<<t.size()<<" data points from file "<<filename<<".";
	cout<<endl;
	fin.close();
}

