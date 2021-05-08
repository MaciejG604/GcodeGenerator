#include "GeoVector.h"

double GeoVector::operator[]( size_t id )
{
	if (id >= 0 && id < SIZE)
		return data[id];
	else
		throw std::out_of_range( "operator[]" );
}

GeoVector GeoVector::operator+( const GeoVector& pcOther ) const
{
	GeoVector c_result = *this;
	for (int i = 0; i < SIZE; ++i)
		c_result.data[i] += pcOther.data[i];
	return c_result;
}

GeoVector GeoVector::operator-( const GeoVector& pcOther ) const
{
	GeoVector c_result = *this;
	for (int i = 0; i < SIZE; ++i)
		c_result.data[i] -= pcOther.data[i];
	return c_result;
}

GeoVector GeoVector::operator*( const GeoVector& pcOther ) const
{
	double x_result = this->data[1] * pcOther.data[2] - this->data[2] * pcOther.data[1];
	double y_result = this->data[2] * pcOther.data[0] - this->data[0] * pcOther.data[2];
	double z_result = this->data[0] * pcOther.data[1] - this->data[1] * pcOther.data[0];

	return GeoVector ( x_result, y_result, z_result );
}

GeoVector GeoVector::operator*( const double dFactor ) const
{
	GeoVector c_result;
	for (int i = 0; i < SIZE; ++i)
		c_result.data[i] = this->data[i] * dFactor;
	return c_result;
}

bool GeoVector::operator==( const GeoVector& pcOther )
{
	for (int i = 0; i < SIZE; ++i)
	{
		if (abs(data[i] - pcOther.data[i]) > 1.e-6)
			return false;
	}
	return true;
}

double GeoVector::interAngleDeg( const GeoVector& pcOther ) const
{
	double dot_product = data[0] * pcOther.data[0] + data[1] * pcOther.data[1] + data[2] * pcOther.data[2];
	double angle = ( 180 / M_PI ) * std::acos( dot_product / ( this->length() * pcOther.length() ) );
	return angle;
}

GeoVector GeoVector::unitScale() const
{
	double new_data[SIZE];
	double length = sqrt( data[0] * data[0] + data[1] * data[1] + data[2] * data[2] );
	for (int i = 0; i < SIZE; ++i)
		new_data[i] = data[i] / length;
	return GeoVector( new_data );
}

bool GeoVector::areParallel( const GeoVector& pcOther, double* pFactor ) const
{
	if (this->length() < 1.e-6 || pcOther.length() < 1.e-6)
		throw std::exception( "Zero vector used" );
	else
	{
		bool b_result = false;
		if (( ( *this ) * pcOther ).length() < 1.e-6)
		{
			b_result = true;
			if (pFactor != nullptr)
			{
				for (int i = 0; i < SIZE; ++i)
					if (abs(this->data[i]) >= 1.e-4  && abs(pcOther.data[i]) >= 1.e-4)
					{
						*pFactor = this->data[i] / pcOther.data[i];
						break;
					}
			}
		}
		return b_result;
	}
}

double GeoVector::length() const
{
	return std::sqrt( data[0] * data[0] + data[1] * data[1] + data[2] * data[2] );
}

void GeoVector::swap( GeoVector pcOther )
{
	GeoVector temp = pcOther;
	pcOther = *this;
	*this = temp;
}

DL_LineData GeoVector::makeLineData( GeoVector v1, GeoVector v2 )
{
	return DL_LineData( v1[0], v1[1], v1[2], v2[0], v2[1], v2[2] );
}
