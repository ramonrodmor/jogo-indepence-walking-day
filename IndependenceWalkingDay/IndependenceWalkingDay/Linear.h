/**********************************************************************************
// Magenta (Arquivo de Cabe�alho)
//
// Cria��o:		10 Out 2012
// Atualiza��o:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descri��o:	Magenta faz persegui��o direta
//
**********************************************************************************/

#ifndef _GEOMETRYWARS_LINEAR_H_
#define _GEOMETRYWARS_LINEAR_H_

// ---------------------------------------------------------------------------------

#include "Object.h"	
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"
#include "Explosion.h"
#include "Jogo.h"

// ---------------------------------------------------------------------------------

class Linear : public Object
{
private:
	TileSet  * tileset;                 //folha de sprite --modificado--
	Animation * ani;
	Sprite * sprite;					// sprite do objeto
	Vector * speed;						// velocidade e dire��o
	Player * player;					// ponteiro para jogador
	Timer  timer;						// medidor de tempo

public:
	Linear(Player * p);
	~Linear();

	void OnCollision(Object * obj);		// tratamento de colis�o
	void Update(float gameTime);		// atualiza estado do objeto
	void Draw();						// desenha objeto
};

// ---------------------------------------------------------------------------------

inline void Linear::Draw()
{
	ani->Draw(X(), Y(), 0.6f, 1.0f, speed->angle + 90);
}

// ---------------------------------------------------------------------------------


#endif