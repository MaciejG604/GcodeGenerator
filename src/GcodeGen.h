#pragma once
#include <vector>

class Entity;
class Line;
class Arc;
class Circle;

class GcodeGen
{
	/*
		Machine parameters here as variables, IF NEEDED
	*/
public:
	/*
		Constructors and Destructors, IF NEEDED
	*/
	void generateCode( const std::vector<Entity*>& eVec );

	void startup();		//function for initial homing
	void finish();		//function for finalizing machine's job, IF NEEDED
};

