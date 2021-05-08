#include "GcodeGen.h"

void GcodeGen::startup()
{
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
	std::cout << "Obrót p³aszczyzny o " << bend_plane_rotation << " stopni" << std::endl;
	bend_plane_rotation = 0;
}