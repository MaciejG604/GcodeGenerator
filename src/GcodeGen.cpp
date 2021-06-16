#include "GcodeGen.h"

void GcodeGen::startup()
{
	std::cout << "M3 S61" << std::endl; //schowanie trzpienia
	std::cout << "G91" << std::endl;	   //zmiana wartoœci ze wspó³¿êdnych na przyrostowe
	std::cout << "$22=1" << std::endl;  //w³¹czenie homingu w ustawieniach grbl'a
	std::cout << "$27=45" << std::endl; //ustawienie dystansu o jaki ma siê przesun¹æ element zginaj¹cy
	std::cout << "$24=80" << std::endl; //szybkoœæ przesuwu elementu zginaj¹cego
	std::cout << "$h" << std::endl;		//w³¹czenie operacji homing z konsoli grbl'a
	std::cout << "M3 S122" << std::endl; //ponowrot trzepienia


	for (auto elem : entities)
		elem->makeLines(); //wywo³anie funckji aproksymuj¹cej ³uki odcinkami

	entities.front()->reorder( nullptr );

	for (unsigned i = 1; i < entities.size(); ++i)
		entities[i]->reorder( entities[i - 1] );
}

void GcodeGen::generate()
{
	bend_plane_rotation += entities.front()->codePath( nullptr, present_normal, BENDING_FACTOR );

	for (unsigned i = 1; i < entities.size(); ++i)
		bend_plane_rotation += entities[i]->codePath( entities[i - 1], present_normal, BENDING_FACTOR );
}

void GcodeGen::finish()
{
	std::cout << "M3 S61" << std::endl; //schowanie trzpienia
	std::cout << "$h" << std::endl;		//w³¹czenie operacji homing z konsoli grbl'a
	std::cout << "M3 S122" << std::endl; //powrot trzpienia
	bend_plane_rotation = 0;
}