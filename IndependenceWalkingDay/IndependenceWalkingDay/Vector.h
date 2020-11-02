/**********************************************************************************
// Vector (Arquivo de Cabeçalho)
// 
// Criação:		18 Nov 2011
// Atualização:	30 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Classe para representar um vetor em 2D
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
	float angle;											// ângulo do vetor com a horizontal
	float magnitude;										// magnitude do vetor

	Vector();												// construtor padrão
	Vector(float ang, float mag);							// constructor com ângulo e magnitude

	void  Rotate(float theta);								// rotaciona vetor pelo ângulo fornecido (em graus)
	float CompX() const;									// retorna componente X do vetor
	float CompY() const; 									// retorna componente Y do vetor
	float Rad() const;										// retorna ângulo em radianos
	void  Add(const Vector &v);							    // adiciona o vetor passado por parâmetro
	float Angle(float x1, float y1, float x2, float y2);	// ajusta o ângulo do vetor na direção de (x1,y1) para (x2,y2)
	float Distance(float x1, float y1, float x2, float y2);	// retorna a distância entre os pontos (x1,y1) e (x2,y2) 
}; 

// ---------------------------------------------------------------------------------
// Funções Membro Inline

// retorna componente X do vetor
inline float Vector::CompX() const 
{ return magnitude * cos(Rad()); }	

// retorna componente Y do vetor
inline float Vector::CompY() const 
{ return magnitude * sin(Rad()); }	

// retorna ângulo em radianos
inline float Vector::Rad() const
{ return float(angle * PI / 180.0); }

// ------------------------------------------------------------------------------



#endif