/**********************************************************************************
// Blue (Arquivo de Cabeçalho)
// 
// Criação:		10 Out 2012
// Atualização:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Blue faz perseguição suavizada
//
**********************************************************************************/

#ifndef _GEOMETRYWARS_BLUE_H_
#define _GEOMETRYWARS_BLUE_H_

// ---------------------------------------------------------------------------------

#include "Object.h"	
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"
#include "Timer.h"
#include "Explosion.h"
#include "Jogo.h"

// ---------------------------------------------------------------------------------

class Blue : public Object
{
private:
	TileSet  * tileset;                 //folha de sprite --modificado--
	Sprite * sprite;					// sprite do objeto
	Vector * speed;						// velocidade e direção
	Player * player;					// ponteiro para jogador
	Timer  timer;						// controle do tempo
	Animation * ani;
	
public:
	Blue(Player * p);	
	~Blue();
	
	void OnCollision(Object * obj);		// tratamento de colisão
	void Update(float gameTime);		// atualiza estado do objeto
	void Draw();						// desenha objeto
}; 

// ---------------------------------------------------------------------------------

inline void Blue::Draw()
{
	ani->Draw(X(), Y(), 0.6f, 1.0f, speed->angle + 90);
}

// ---------------------------------------------------------------------------------


#endif