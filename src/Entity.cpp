#include "Entity.h"

double angle_difference( double startAngle, double endAngle )
{
	double diff = 0.0;
	diff = endAngle - startAngle;
	if (startAngle > endAngle)
		diff = 360 - abs(diff);
	return diff;
}

void Line::reorder( shared_ptr<Entity> pcPrevious)
{
	//ADDITIONAL: przy okazji sprawdzanie ciągłości ścieżki
}

GeoVector Line::tangentVector() const
{
	double tgv_x = data.x2 - data.x1;
	double tgv_y = data.y2 - data.y1;
	double tgv_z = data.z2 - data.z1;
	GeoVector gv_result( tgv_x, tgv_y, tgv_z );
	//gv_result = gv_result.unitScale();
	return gv_result;
}

bool Line::operator^( const Line& pcOther ) const
{
	bool b_result = ( data.x1 == pcOther.data.x1 && data.y1 == pcOther.data.y1 && data.z1 == pcOther.data.z1 ) ||	//pkt 1 <-> pkt 1
		( data.x1 == pcOther.data.x2 && data.y1 == pcOther.data.y2 && data.z1 == pcOther.data.z2 ) ||	//pkt 1 <-> pkt 2
		( data.x2 == pcOther.data.x2 && data.y2 == pcOther.data.y2 && data.z2 == pcOther.data.z2 ) ||	//pkt 2 <-> pkt 2
		( data.x2 == pcOther.data.x1 && data.y2 == pcOther.data.y1 && data.z2 == pcOther.data.z1 );		//pkt 2 <-> pkt 1

	return b_result;
}

double Line::length() const
{
	double d_x = data.x1 - data.x2;
	double d_y = data.y1 - data.y2;
	double d_z = data.z1 - data.z2;
	double d_result = std::sqrt( d_x * d_x + d_y * d_y + d_z * d_z );

	return d_result;
}

pair<GeoVector, GeoVector> Line::intersectionVectors( const Line& pcPrevious ) const
{
	GeoVector a1 = { data.x1, data.y1, data.z1 };
	GeoVector a2 = { data.x2, data.y2, data.z2 };

	GeoVector b1 = { pcPrevious.data.x1, pcPrevious.data.y1, pcPrevious.data.z1 };
	GeoVector b2 = { pcPrevious.data.x2, pcPrevious.data.y2, pcPrevious.data.z2 };

	GeoVector intersection;
	GeoVector end_this;
	GeoVector end_prev;

	if (a2 == b1)		//pkt 2 <-> pkt 1 - przypadek występujacy dla line_aproxim w Arc
	{
		intersection = a2;	//też b1
		end_this = a1;
		end_prev = b2;
	}
	else if (a1 == b2)	//pkt 1 <-> pkt 2
	{
		intersection = a1;	//też b2
		end_this = a2;
		end_prev = b1;
	}
	else if (a2 == b2)	//pkt 2 <-> pkt 2
	{
		intersection = a2;	//też b2
		end_this = a1;
		end_prev = b1;
	}
	else if (a1 == b1)	//pkt 1 <-> pkt 1
	{
		intersection = a1;	//też b1
		end_this = a2;
		end_prev = b2;
	}

	//zwroc wektory o długosci 1, styczne do prostych
	return pair<GeoVector, GeoVector>{ (end_this - intersection), (end_prev - intersection) };
}

double Line::interAngleDeg( const Line& pcOther) const
{
	double by_line1 = this->length(), by_line2 = pcOther.length();
	double oppos_line;

	if ( data.x2 == pcOther.data.x1 && data.y2 == pcOther.data.y1 && data.z2 == pcOther.data.z1 )		//pkt 2 <-> pkt 1 - przypadek występujacy dla line_aproxim w Arc
		oppos_line = Line( DL_LineData( data.x1, data.y1, data.z1, pcOther.data.x2, pcOther.data.y2, pcOther.data.z2 ) ).length();
	else if ( data.x1 == pcOther.data.x2 && data.y1 == pcOther.data.y2 && data.z1 == pcOther.data.z2 )	//pkt 1 <-> pkt 2
		oppos_line = Line( DL_LineData( data.x2, data.y2, data.z2, pcOther.data.x1, pcOther.data.y1, pcOther.data.z1 ) ).length();
	else if ( data.x2 == pcOther.data.x1 && data.y2 == pcOther.data.y1 && data.z2 == pcOther.data.z1 )	//pkt 2 <-> pkt 2
		oppos_line = Line( DL_LineData( data.x1, data.y1, data.z1, pcOther.data.x1, pcOther.data.y1, pcOther.data.z1 ) ).length();
	else if (data.x1 == pcOther.data.x1 && data.y1 == pcOther.data.y1 && data.z1 == pcOther.data.z1)	//pkt 1 <-> pkt 1
		oppos_line = Line( DL_LineData( data.x2, data.y2, data.z2, pcOther.data.x2, pcOther.data.y2, pcOther.data.z2 ) ).length();

	//z twierdzenie cosinusów
	double angle_result = ( 180 / M_PI ) * std::acos( ( by_line1*by_line1 + by_line2 * by_line2 - oppos_line * oppos_line ) / ( 2 * by_line1*by_line2 ) );

	return 180 - angle_result;
}

double Line::codePath( shared_ptr<Entity> pcPrevious, GeoVector& gvNormal )
{
	double plane_rotation = 0;
	//TODO Gcode
	std::cout << "Wysun drut na " << length() << " mm" << std::endl;

	if (pcPrevious != nullptr)
	{	
		auto temp = intersectionVectors( pcPrevious->lastLine() );
		//wektory styczne (	TANGent)
		GeoVector tang_this = temp.first;
		GeoVector tang_previous = temp.second;
		GeoVector new_normal = (tang_previous * tang_this).unitScale();

		//zmiana kąta płaszczyzny gięcia
		double direction = 0.0;
		if (gvNormal == GeoVector{ 0.0,0.0,0.0 })
		{
			gvNormal = new_normal;
			//zgięcie drutu w lewo
			std::cout << "Zegnij drut o " << 180 - tang_this.interAngleDeg( tang_previous ) << " stopni" << std::endl;
		}
		else if (new_normal.areParallel( gvNormal, &direction ))
		{	
			if (direction < 0.0)	//zgięcie drutu w prawo
				std::cout << "Zegnij drut o -" << 180 - tang_this.interAngleDeg( tang_previous ) << " stopni" << std::endl;
			else	//zgięcie drutu w lewo
				std::cout << "Zegnij drut o " << 180 - tang_this.interAngleDeg( tang_previous ) << " stopni" << std::endl;
		}
		else
		{
			if (( gvNormal * new_normal ).areParallel( tang_previous, &direction ))
			{
				plane_rotation = gvNormal.interAngleDeg( new_normal );
				if (direction > 0.0)//kąt skierowany w lewo
				{
					std::cout << "Obrot plaszczyzny w lewo o " << plane_rotation << " stopni" << std::endl;
					plane_rotation = -plane_rotation;
				}
				else //( direction < 0.0 ) kąt skierowany w prawo
					std::cout << "Obrot plaszczyzny w prawo o " << plane_rotation << " stopni" << std::endl;
				gvNormal = new_normal;
			}

			//zgięcie drutu w lewo
			std::cout << "Zegnij drut o " << 180 - tang_this.interAngleDeg( tang_previous ) << " stopni" << std::endl;
		}
	}
	return plane_rotation;
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
		Ax = Ax.unitScale();
		//Ay = N X Ax and Scale Ay to unit length
		Ay = extrusion * Ax;
		Ay = Ay.unitScale();

		//z twierdzenia cosinusów
		const double STEP_ANGLE = ( 180 / M_PI ) * acos( 1 - ( STEP_DISTANCE * STEP_DISTANCE ) / ( 2 * data.radius * data.radius ) );

		GeoVector start;

		//pierwszy punkt
		{
			double x_start = data.radius * deg_cos( data.angle1 );
			double y_start = data.radius * deg_sin( data.angle1 );
			start = GeoVector( data.cx, data.cy, data.cz ) + Ax * x_start + Ay * y_start;
		}

		double start_angle = data.angle1;
		double end_angle = data.angle2;

		while (angle_difference(start_angle, end_angle) >= STEP_ANGLE * 2)
		{
			//współrzędne  początku i konca odcinka aproksymujacego czesc łuku, w lokalnym, płaskim układzie wspolrz
			start_angle += STEP_ANGLE;
			if (start_angle > 360)
				start_angle -= 360;
			double x_end = data.radius * deg_cos( start_angle );
			double y_end = data.radius * deg_sin( start_angle );
			GeoVector end = GeoVector( data.cx, data.cy, data.cz ) + Ax * x_end + Ay * y_end;

			line_aproxim.push_back( make_shared<Line>(GeoVector::makeLineData( start, end )) );
			start = end;
		}

		//ostatni punkt
		{
			double x_end = data.radius * deg_cos( data.angle2 );
			double y_end = data.radius * deg_sin( data.angle2 );
			GeoVector end = GeoVector( data.cx, data.cy, data.cz ) + Ax * x_end + Ay * y_end;
			line_aproxim.push_back( make_shared<Line>( GeoVector::makeLineData( start, end ) ) );
		}
	}

void Arc::reorder( shared_ptr<Entity> pcPrevious)
{
	//if(pcPrevious != nullptr && !(pcPrevious->lastLine() ^ this->firstLine()) )
		//std::reverse(line_aproxim.begin(), line_aproxim.end());
	//ADDITIONAL - obsługa niejednoznaczności (pcPrev.lastline ma punkt wspólny z this->firstLine i jednocześnie z lastLine)
	//przy okazji sprawdzanie ciągłości ścieżki
}

double Arc::codePath( shared_ptr<Entity> pcPrevious, GeoVector& gvNormal )
{
	double plane_rotation = 0;
	plane_rotation += line_aproxim.front()->codePath( pcPrevious, gvNormal);

	unsigned int i;
	for ( i = 1; i < line_aproxim.size(); ++i)
		plane_rotation += line_aproxim[i]->codePath( line_aproxim[i-1], gvNormal );

	return plane_rotation;
}

Line Arc::firstLine(){ return *line_aproxim.front(); };
Line Arc::lastLine(){ return *line_aproxim.back(); };