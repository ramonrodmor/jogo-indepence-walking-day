/**********************************************************************************
// Vector (Arquivo de Cabe�alho)
// 
// Cria��o:		18 Nov 2011
// Atualiza��o:	30 Jun 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Classe para representar um vetor em 2D
//
**********************************************************************************/

#ifndef _DESENVJOGOS_VECTOR_H_
#define _DESENVJOGOS_VECTOR_H_

// --------------------------------------------------------------------------------

#include <cmath>

// --------------------------------------------------------------------------------

class Vector
{
private:
	static const double PI;									// constante PI

public:
	float angle;											// �ngulo do vetor com a horizontal
	float magnitude;										// magnitude do vetor

	Vector();												// construtor padr�o
	Vector(float ang, float mag);							// constructor com �ngulo e magnitude

	void  Rotate(float theta);								// rotaciona vetor pelo �ngulo fornecido (em graus)
	float CompX() const;									// retorna componente X do vetor
	float CompY() const; 									// retorna componente Y do vetor
	float Rad() const;										// retorna �ngulo em radianos
	void  Add(const Vector &v);							    // adiciona o vetor passado por par�metro
	float Angle(float x1, float y1, float x2, float y2);	// ajusta o �ngulo do vetor na dire��o de (x1,y1) para (x2,y2)
	float Distance(float x1, float y1, float x2, float y2);	// retorna a dist�ncia entre os pontos (x1,y1) e (x2,y2) 
}; 

// ---------------------------------------------------------------------------------
// Fun��es Membro Inline

// retorna componente X do vetor
inline float Vector::CompX() const 
{ return magnitude * cos(Rad()); }	

// retorna componente Y do vetor
inline float Vector::CompY() const 
{ return magnitude * sin(Rad()); }	

// retorna �ngulo em radianos
inline float Vector::Rad() const
{ return float(angle * PI / 180.0); }

// ------------------------------------------------------------------------------



#endif