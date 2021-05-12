#include "GcodeGen.h"


void GcodeGen::startup()
{
	std::cout << "G91" << std::endl;
	std::cout << "G28.1" << std::endl;

	for (auto elem : entities)
		elem->makeLines();

	entities.front()->reorder( nullptr );

	for (unsigned i = 1; i < entities.size(); ++i)
		entities[i]->reorder( entities[i-1] );
}

void GcodeGen::generate()
{
	bend_plane_rotation += entities.front()->codePath( nullptr, present_normal );

	for (unsigned i = 1; i < entities.size(); ++i)
		bend_plane_rotation += entities[i]->codePath( entities[i - 1] , present_normal );
}

void GcodeGen::finish()
{
	std::cout << "G28 X" << std::endl;
	std::cout << "G1 Z" << bend_plane_rotation/1.8 << " F3500" << std::endl;
	bend_plane_rotation = 0;
}