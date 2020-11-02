/**********************************************************************************
// Blue (Arquivo de Cabe�alho)
//
// Cria��o:		10 Out 2012
// Atualiza��o:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descri��o:	Blue faz persegui��o suavizada
//
**********************************************************************************/

#ifndef _GEOMETRYWARS_ALEATORIO_H_
#define _GEOMETRYWARS_ALEATORIO_H_

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

class Aleatorio : public Object
{
private:
	TileSet  * tileset;                 //folha de sprite --modificado--
	Sprite * sprite;					// sprite do objeto
	Player * player;					// ponteiro para jogador
	Timer  timer;						// controle do tempo
	Animation * ani;
	float  delay;						// tempo para mudan�a de dire��o
	Vector * speed;						// velocidade e dire��o

public:
	Aleatorio(Player * p);
	~Aleatorio();


	void Direction();					// muda dire��o da mosca
	void OnCollision(Object * obj);		// tratamento de colis�o
	void Update(float gameTime);		// atualiza estado do objeto
	void Draw();						// desenha objeto
};

// ---------------------------------------------------------------------------------

inline void Aleatorio::Draw()
{
	ani->Draw(X(), Y(), 0.6f, 1.0f, speed->angle + 90);
}

// ---------------------------------------------------------------------------------


#endif