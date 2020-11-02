/**********************************************************************************
// Vector (Codigo Fonte)
// 
// Criação:		18 Nov 2011
// Atualização:	30 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Classe para representar um vetor em 2D
//
**********************************************************************************/

#include "Vector.h"

// ------------------------------------------------------------------------------

const double Vector::PI = 3.1415926535;

// ------------------------------------------------------------------------------

Vector::Vector()
{
	angle     = 0;
	magnitude = 0;
}

// ------------------------------------------------------------------------------

Vector::Vector(float ang, float mag)
{
	angle     = ang;
	magnitude = mag;
}

// ------------------------------------------------------------------------------

void Vector::Rotate(float theta)
{
	angle -= theta;

	// mantém o ângulo entre 0 e 359 graus
	while (angle < 0 || angle >= 360)
		angle += (angle >= 360 ? -360.0f : 360.0f);
}

// ------------------------------------------------------------------------------

void Vector::Add(const Vector &v)
{
	float rx, ry;

	rx = CompX() + v.CompX();
	ry = CompY() + v.CompY();

	magnitude = sqrt(pow(rx,2) + pow(ry,2));
	
	// ajusta o ângulo de acordo com o quadrante do vetor resultante
	if (rx > 0) 
	{
		// 1o Quadrante
		if (ry >= 0)
		{
			// acha o ângulo em radianos
			angle = atan(ry/rx);
			// converte de radianos para graus
			angle = float((180.0 * angle) / PI);
		}
		// 4o Quadrante
		else // (ry < 0)
		{
			// acha o ângulo em radianos
			angle = atan(ry/rx);
			// converte de radianos para graus
			angle = float((180.0 * angle) / PI) + 360.0f;
		}
	}
	// 2o e 3o Quadrante
	else if (rx < 0)
	{
		// acha o ângulo em radianos
		angle = atan(ry/rx);
		// converte de radianos para graus
		angle = float((180.0 * angle) / PI) + 180.0f;
	}
	else // (rx == 0)
	{
		if (ry > 0)
			angle = 90.0f;
		else if (ry < 0)
			angle = 270.0f;
		else // (ry == 0)
			angle = v.angle;
	}
}

// ------------------------------------------------------------------------------

float Vector::Angle(float x1, float y1, float x2, float y2)
{
	float dx, dy;
	float ang;

	dx = x2 - x1;
	dy = y2 - y1;

	// ajusta o ângulo de acordo com o quadrante do vetor resultante
	if (dx > 0)
	{
		// 1o Quadrante
		if (dy >= 0)
		{
			// acha o ângulo em radianos
			ang = atan(dy / dx);
			// converte de radianos para graus
			ang = float((180.0 * ang) / PI);
		}
		// 4o Quadrante
		else // (ry < 0)
		{
			// acha o ângulo em radianos
			ang = atan(dy / dx);
			// converte de radianos para graus
			ang = float((180.0 * ang) / PI) + 360.0f;
		}
	}
	// 2o e 3o Quadrante
	else if (dx < 0)
	{
		// acha o ângulo em radianos
		ang = atan(dy / dx);
		// converte de radianos para graus
		ang = float((180.0 * ang) / PI) + 180.0f;
	}
	else // (rx == 0)
	{
		if (dy > 0)
			ang = 90.0f;
		else if (dy < 0)
			ang = 270.0f;
		else
			ang = 0.0f;
	}

	return ang;
}

// ------------------------------------------------------------------------------

float Vector::Distance(float x1, float y1, float x2, float y2)
{
	float dx, dy;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	return sqrt(dx*dx + dy*dy);
}

// ------------------------------------------------------------------------------