#include "GcodeGen.h"

const double GcodeGen::MIN_BEND_DISTANCE = 5; //[mm]


void GcodeGen::generate()
{
	for (int i = 0; i < entities.size(); ++i)
	{
		if (i == 0)
			entities[i]->codePath( nullptr, entities[i + 1] );
	}
}
