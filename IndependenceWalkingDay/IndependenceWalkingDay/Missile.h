/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
// 
// Criação:		23 Nov 2011
// Atualização:	01 Abr 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Define uma classe para um míssil/projétil
//
**********************************************************************************/

#ifndef _GEOMETRYWARS_MISSILE_H_
#define _GEOMETRYWARS_MISSILE_H_

// --------------------------------------------------------------------------------

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 

// --------------------------------------------------------------------------------

class Missile : public Object
{
private:
	Sprite * sprite;							// sprite do míssil
	Vector   speed;								// velocidade do míssil
	
public:
	Missile(Player * player);					// construtor
	~Missile();									// destrutor

	void OnCollision(Object * obj);				// tratamento de colisão
	void Update(float gameTime);				// atualiza estado 
	void Draw();								// desenha objeto
}; 

// ------------------------------------------------------------------------------

#endif