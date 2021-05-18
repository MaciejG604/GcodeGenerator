#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "../library/dl_global.h"
#include "../library/dl_creationadapter.h"
#include "GeoVector.h"

#include <math.h>
#include <string>
#include <vector>
#include <iostream>

const double STEP_DISTANCE = 5.0; //maksymalna długość odcinków uzytych do aproksymacji

//wrappery na funkcje przyjmujace argumenty w stopniach
inline double deg_sin	( double x ) { return std::sin( ( M_PI / 180 )*x ); }
inline double deg_cos	( double x ) { return std::cos( ( M_PI / 180 )*x ); }
double angle_difference( double startAngle, double endAngle );
class Line;

using namespace std;

class Entity {
public:
    virtual ~Entity() = default;
	virtual void makeLines() = 0;	//tworzy aproksymacje danego obiektu odcinkami
	virtual void reorder( shared_ptr<Entity>) = 0;	//zmienia kolejność składowych kształtu (pozwala na porpawne zwracanie first i last)
	virtual Line firstLine() = 0;	//zwraca odcinek początkowy kształtu
	virtual Line lastLine() = 0;	//zwraca odcinek końcowy kształtu
	virtual double codePath( shared_ptr<Entity>, GeoVector&) = 0; //funkcja generujaca gcode, zwraca kąt obortu płaszczyzny gięcia
};

class Line : public Entity{
public:
	Line( DL_LineData cData ) :data( cData ) {};
	void makeLines() override {};

	void reorder( shared_ptr<Entity> pcPrevious ) override;
	Line firstLine() override { return *this; };
	Line lastLine() override { return *this; };
	double codePath( shared_ptr<Entity> pcPrevious, GeoVector& gvNormal) override;

	//zwraca wektor styczny do odcinka
	GeoVector tangentVector() const;

	//zwraca true jeśli obiekt pcOther ma punkt końcowy lub początkowy wspólny z this
	bool operator^( const Line& pcOther ) const;
	
	//zwraca parę wektorów stycznych do obu prostych, zaczepionych w punkcie wspólnym prostych - [wektor z this, wektor z pcPrevious]
	pair<GeoVector, GeoVector> intersectionVectors( const Line& pcPrevious ) const;

	//zwraca wartość kąta pomiędzy odcinkami w stopniach
	double interAngleDeg( const Line& pcOther) const;
	
	inline double length() const;
private:
    DL_LineData data;
};


class Arc : public Entity {
public:
	Arc( DL_ArcData arcData, GeoVector geoExtr ) : data( arcData ), extrusion( geoExtr ) {};

	void makeLines() override;
	void reorder( shared_ptr<Entity> pcPrevious ) override;
	double codePath( shared_ptr<Entity> pcPrevious, GeoVector& gvNormal ) override;

	Line firstLine() override { return *line_aproxim.front(); };
	Line lastLine() override { return *line_aproxim.back(); };
	
private:
	DL_ArcData data;
	GeoVector extrusion; //wektor normalny do płaszczyzny łuku
	vector<shared_ptr<Line>> line_aproxim;
};

/*
TODO:
class Circle : public Entity {
public:
	Circle(DL_CircleData cData) :data(cData) {};
	void makeLines() override {};
	void reorder( shared_ptr<Entity> pcPrevious, shared_ptr<Entity> pcNext ) override {};
	Line firstLine() override { return line_aproxim.front(); };
	Line lastLine() override { return line_aproxim.back(); };
private:
    DL_CircleData data;
};
*/
