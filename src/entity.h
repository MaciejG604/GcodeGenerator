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


using namespace std;

struct Entity {
    virtual ~Entity() = default;
};

struct Line : Entity{
public:
	Line( DL_LineData cData ) :data( cData ) {};
private:
    DL_LineData data;
};


struct Arc : Entity {
public:
	Arc( DL_ArcData arcData, GeoVector geoExtr ) : data( arcData ), extrusion( geoExtr ) {};

	void makeLines()
	{
		GeoVector Ax;
		GeoVector Ay;
		//Wyznaczenie osi okładu lokalnego dla łuku, patrz Arbitrary Axis Algorithm (DXF)
		if (( abs( extrusion[0] ) < (1.0 / 64.0) ) && ( abs( extrusion[1] ) < (1.0 / 64.0) ))
		{
			//Ax = Wy X N ( where “X” is the cross - product operator )
			Ax = GeoVector( 0, 1, 0 )*extrusion;
		}
		else
		{
			//Ax = Wz X N ( where “X” is the cross - product operator )
			Ax = GeoVector( 0, 0, 1 )*extrusion;
			
		}
		//Scale Ax to unit length.
		Ax.unitScale();
		//Ay = N X Ax and Scale Ay to unit length
		Ay = extrusion * Ax;
		Ay.unitScale();

		//z twierdzenia cosinusów
		const double STEP_ANGLE = ( 180 / M_PI ) * acos( 1 - ( STEP_DISTANCE * STEP_DISTANCE ) / ( 2 * data.radius * data.radius ) );

		GeoVector start;

		{
			double x_start = data.radius * deg_cos( data.angle1 );
			double y_start = data.radius * deg_sin( data.angle1 );
			start = GeoVector( data.cx, data.cy, data.cz ) + Ax * x_start + Ay * y_start;
		}

		while (abs( data.angle2 - data.angle1 ) > STEP_ANGLE)
		{
			//współrzędne  początku i konca odcinka aproksymujacego czesc łuku, w lokalnym, płaskim układzie wspolrz
			data.angle1 += STEP_ANGLE;
			if (data.angle1 > 360)
				data.angle1 -= 360;
			double x_end = data.radius * deg_cos( data.angle1 );
			double y_end = data.radius * deg_sin( data.angle1 );
			GeoVector end = GeoVector( data.cx, data.cy, data.cz ) + Ax * x_end + Ay * y_end;

			line_aproxim.push_back( Line( GeoVector::makeLineData( start, end ) ) );
			start = end;
		}
	}

private:
	DL_ArcData data;
	GeoVector extrusion; //wektor normalny do płaszczyzny łuku
	vector<Line> line_aproxim;
};

struct Circle : Entity {
public:
	Circle(DL_CircleData cData) :data(cData) {};
private:
    DL_CircleData data;
};
