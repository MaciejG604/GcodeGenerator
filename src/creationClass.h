#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <vector>
#include <iostream>
#include "entity.h"

class creationClass : public DL_CreationAdapter {
public:
	creationClass();
	~creationClass();

	virtual void addLine(const DL_LineData& data);
	virtual void addArc(const DL_ArcData& data,const DL_Extrusion& extrusion);
	virtual void addCircle(const DL_CircleData& data);

	shared_ptr<Entity> get(int id);

	int size();

private:
	vector<std::shared_ptr<Entity>> entities;
};