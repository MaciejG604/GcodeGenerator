#pragma once
#include <vector>

#include "entity.h"
class GcodeGen
{
	/*
		Machine parameters here as variables, IF NEEDED
	*/
	static const double MIN_BEND_DISTANCE; //[mm] minimalna d�ugo�� odcinka jaki moze byc zagi�ty - odleg�o�� narz�dzia od g�owicy z drutem
public:
	/*
		Constructors and Destructors, IF NEEDED
	*/
	void generateCode( std::vector<Entity*> eVec );

	void startup();		//function for initial homing
	void finish();		//function for finalizing machine's job, IF NEEDED
};

