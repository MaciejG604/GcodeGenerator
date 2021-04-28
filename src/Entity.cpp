#include "Entity.h"

GeoVector Line::tangentVector()
{
	double tgv_x = data.x1 - data.x2;
	double tgv_y = data.y1 - data.y2;
	double tgv_z = data.z1 - data.z2;
	GeoVector gv_result( tgv_x, tgv_y, tgv_z );
	gv_result.unitScale();
	return gv_result;
}

bool Line::operator^( const Line& pcOther )
{
	bool b_result = ( data.x1 == pcOther.data.x1 && data.y1 == pcOther.data.y1 && data.z1 == pcOther.data.z1 ) ||	//pkt 1 <-> pkt 1
		( data.x1 == pcOther.data.x2 && data.y1 == pcOther.data.y2 && data.z1 == pcOther.data.z2 ) ||	//pkt 1 <-> pkt 2
		( data.x2 == pcOther.data.x2 && data.y2 == pcOther.data.y2 && data.z2 == pcOther.data.z2 ) ||	//pkt 2 <-> pkt 2
		( data.x2 == pcOther.data.x1 && data.y2 == pcOther.data.y1 && data.z2 == pcOther.data.z1 );		//pkt 2 <-> pkt 1

	return b_result;
}

void Line::codePath( shared_ptr<Entity> pcPrevious, shared_ptr<Entity> pcNext )
{

}


void Arc::makeLines()
	{
		GeoVector Ax;
		GeoVector Ay;
		//Wyznaczenie osi okładu lokalnego dla łuku, patrz Arbitrary Axis Algorithm (DXF)
		if (( abs( extrusion[0] ) < ( 1.0 / 64.0 ) ) && ( abs( extrusion[1] ) < ( 1.0 / 64.0 ) ))
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

void Arc::reorder( shared_ptr<Entity> pcPrevious, shared_ptr<Entity> pcNext )
{

}

void Arc::codePath( shared_ptr<Entity> pcPrevious, shared_ptr<Entity> pcNext )
{

}