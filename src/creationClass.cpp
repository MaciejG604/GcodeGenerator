#define _CRT_SECURE_NO_WARNINGS
#include "creationClass.h"
#include <iostream>
#include <stdio.h>
#include <memory>

creationClass::creationClass() {}
creationClass::~creationClass() {}

void creationClass::addLine(const DL_LineData& data) {
	this->entities.push_back(std::make_shared<Line>(data));
}

void creationClass::addArc(const DL_ArcData& data, const DL_Extrusion& extrusion) {
	double dir[3];
	extrusion.getDirection(dir);
	this->entities.push_back(std::make_shared<Arc>(data, GeoVector(dir[0], dir[1], dir[2])));
}


void creationClass::addCircle(const DL_CircleData& data) {
	this->entities.push_back(std::make_shared<Circle>(data));
}


shared_ptr<Entity> creationClass::get(int id) {
	return entities.at(id);
}

int creationClass::size() {
	return this->entities.size();
}