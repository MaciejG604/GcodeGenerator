#pragma once
#include <vector>

#include "Entity.h"
class GcodeGen
{
	//Machine parameters here as variables

	const double MIN_BEND_DISTANCE; //[mm] minimalna d�ugo�� odcinka jaki moze byc zagi�ty - odleg�o�� narz�dzia od g�owicy z drutem
	vector<std::shared_ptr<Entity>> entities;
	GeoVector present_normal = { 0.0,0.0,0.0 };
	double bend_plane_rotation = 0;
public:
	GcodeGen( vector<std::shared_ptr<Entity>> vInput, double bendDistance ) :MIN_BEND_DISTANCE(bendDistance), entities( vInput ) {};

	void startup();		//function for initial homing
	void generate();
	void finish();		//function for finalizing machine's job, IF NEEDED
};

