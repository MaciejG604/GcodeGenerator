#pragma once
#include <vector>

#include "entity.h"
class GcodeGen
{
	/*
		Machine parameters here as variables, IF NEEDED
	*/
public:
	/*
		Constructors and Destructors, IF NEEDED
	*/
	void generateCode( std::vector<Entity*> eVec );

	void startup();		//function for initial homing
	void finish();		//function for finalizing machine's job, IF NEEDED
};

