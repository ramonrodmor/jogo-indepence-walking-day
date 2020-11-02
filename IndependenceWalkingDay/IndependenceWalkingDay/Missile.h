/**********************************************************************************
// Missile (Arquivo de Cabe�alho)
// 
// Cria��o:		23 Nov 2011
// Atualiza��o:	01 Abr 2013
// Compilador:	Visual C++ 11
//
// Descri��o:	Define uma classe para um m�ssil/proj�til
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
	Sprite * sprite;							// sprite do m�ssil
	Vector   speed;								// velocidade do m�ssil
	
public:
	Missile(Player * player);					// construtor
	~Missile();									// destrutor

	void OnCollision(Object * obj);				// tratamento de colis�o
	void Update(float gameTime);				// atualiza estado 
	void Draw();								// desenha objeto
}; 

// ------------------------------------------------------------------------------

#endif