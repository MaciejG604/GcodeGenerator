#include <stdexcept>

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
	GeoVector c_result;
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
		c_result.data[i] *= dFactor;
	return c_result;
}
