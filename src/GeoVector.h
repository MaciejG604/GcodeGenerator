#pragma once
#include <stdexcept>
#include <math.h>

#include "../library/dl_entities.h"
#include "../library/dl_codes.h"

class GeoVector
{
public:
	GeoVector() : data{} {}
	GeoVector( double dX, double dY, double dZ ) : data{ dX, dY, dZ } {}
	GeoVector( double dData[] ) {
		for (int i = 0; i < SIZE; ++i)
			data[i] = dData[i];
	}

	double operator[]( size_t id );

	GeoVector operator+( const GeoVector& pcOther ) const;	//dodawanie wektorów
	GeoVector operator-( const GeoVector& pcOther ) const;	//odejmowanie wektorów
	GeoVector operator*( const GeoVector& pcOther ) const;	//iloczyn wektorowy
	GeoVector operator*( const double dFactor ) const;		//mno¿enie wektora przez liczbê

	bool operator==( const GeoVector& pcOther );
	bool operator!=( const GeoVector& pcOther ) { return !(*this == pcOther); };

	//funkcja zwracaj¹ca true gdy wektory s¹ równoleg³e, pod adresem pFactor zapisywany jest stosunek d³ugoœci wektorów (this/pcOther)
	bool areParallel( const GeoVector& pcOther, double* pFactor = nullptr) const;
	double interAngleDeg( const GeoVector& pcOther ) const;
	GeoVector unitScale() const;
	double length() const;
	void swap( GeoVector pcOther );

	static DL_LineData makeLineData( GeoVector v1, GeoVector v2 );
private:
	static const int SIZE = 3;
	double data[SIZE];
	
};

