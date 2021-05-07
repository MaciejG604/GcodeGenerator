#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include <vector>
#include <iostream>
#include "entity.h"

class creationClass : public DL_CreationAdapter {
public:
	creationClass();
	~creationClass();

	void addLine(const DL_LineData& data) override;
	void addArc(const DL_ArcData& data) override;
	//void addCircle(const DL_CircleData& data) override;

	shared_ptr<Entity> get(int id);
	vector<std::shared_ptr<Entity>> data() { return entities; };
	int size();

private:
	vector<std::shared_ptr<Entity>> entities;
};