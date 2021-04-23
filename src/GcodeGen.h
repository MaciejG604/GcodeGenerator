#pragma once
#include <vector>

#include "entity.h"
class GcodeGen
{
	/*
		Machine parameters here as variables, IF NEEDED
	*/
	static const double MIN_BEND_DISTANCE; //[mm] minimalna d³ugoœæ odcinka jaki moze byc zagiêty - odleg³oœæ narzêdzia od g³owicy z drutem
public:
	/*
		Constructors and Destructors, IF NEEDED
	*/
	void generateCode( std::vector<Entity*> eVec );

	void startup();		//function for initial homing
	void finish();		//function for finalizing machine's job, IF NEEDED
};

