#include <stdexcept>
#include <math.h>

#include "GeoVector.h"

double GeoVector::operator[]( size_t id )
{
	if (id >= 0 && id < SIZE)
		return data[id];
	else
		throw std::out_of_range( "operator[]" );
}

GeoVector GeoVector::operator+( const GeoVector& pcOther )
{
	GeoVector c_result = *this;
	for (int i = 0; i < SIZE; ++i)
		c_result.data[i] += pcOther.data[i];
	return c_result;
}

GeoVector GeoVector::operator*( const GeoVector& pcOther )
{
	double x_result = this->data[1] * pcOther.data[2] - this->data[2] * pcOther.data[1];
	double y_result = this->data[2] * pcOther.data[0] - this->data[0] * pcOther.data[2];
	double z_result = this->data[0] * pcOther.data[1] - this->data[1] * pcOther.data[0];

	return GeoVector ( x_result, y_result, z_result );
}

GeoVector GeoVector::operator*( const double dFactor )
{
	GeoVector c_result;
	for (int i = 0; i < SIZE; ++i)
		c_result.data[i] = this->data[i] * dFactor;
	return c_result;
}

void GeoVector::unitScale()
{
	double length = sqrt( data[0] * data[0] + data[1] * data[1] + data[2] * data[2] );
	for (int i = 0; i < SIZE; ++i)
		data[i] = data[i] / length;
}

DL_LineData GeoVector::makeLineData( GeoVector v1, GeoVector v2 )
{
	return DL_LineData( v1[0], v1[1], v1[2], v2[0], v2[1], v2[2] );
}
