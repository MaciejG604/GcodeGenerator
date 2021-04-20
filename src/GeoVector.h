#pragma once
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

	GeoVector operator+( const GeoVector& pcOther );

	GeoVector operator*( const GeoVector& pcOther );
	GeoVector operator*( const double dFactor );

private:
	static const int SIZE = 3;
	double data[SIZE];
	
};

