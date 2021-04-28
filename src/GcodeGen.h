#pragma once
#include <vector>

#include "Entity.h"
class GcodeGen
{
	/*
		Machine parameters here as variables, IF NEEDED
	*/
	static const double MIN_BEND_DISTANCE; //[mm] minimalna d³ugoœæ odcinka jaki moze byc zagiêty - odleg³oœæ narzêdzia od g³owicy z drutem
	vector<std::shared_ptr<Entity>> entities;

public:
	GcodeGen( vector<std::shared_ptr<Entity>> vInput ) :entities( vInput ) {};

	void startup();		//function for initial homing
	void generate();
	void finish();		//function for finalizing machine's job, IF NEEDED
};

