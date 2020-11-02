/**********************************************************************************
// Magenta (Arquivo de Cabeçalho)
//
// Criação:		10 Out 2012
// Atualização:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Magenta faz perseguição direta
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
	Vector * speed;						// velocidade e direção
	Player * player;					// ponteiro para jogador
	Timer  timer;						// medidor de tempo

public:
	Linear(Player * p);
	~Linear();

	void OnCollision(Object * obj);		// tratamento de colisão
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