#pragma once
#include <vector>

#include "Entity.h"
class GcodeGen
{
	//Machine parameters here as variables

	const double MIN_BEND_DISTANCE; //[mm] minimalna d³ugoœæ odcinka jaki moze byc zagiêty - odleg³oœæ narzêdzia od g³owicy z drutem
	const double BENDING_FACTOR;
	vector<std::shared_ptr<Entity>> entities;
	GeoVector present_normal = { 0.0,0.0,0.0 };
	double bend_plane_rotation = 0;
public:
	GcodeGen( vector<std::shared_ptr<Entity>> vInput, double bendDistance, double bending_factor ) :BENDING_FACTOR(bending_factor), MIN_BEND_DISTANCE(bendDistance), entities( vInput ) {};

	void startup();		//function for initial homing
	void generate();
	void finish();		//function for finalizing machine's job, IF NEEDED
};

