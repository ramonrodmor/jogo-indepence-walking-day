/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:		10 Out 2012
// Atualização:	21 Mar 2013
// Compilador:	Visual C++ 11
//
// Descrição:	Define a classe jogador
//
**********************************************************************************/

#ifndef _GEOMETRYWARS_PLAYER_H_
#define _GEOMETRYWARS_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Vector.h"						// representação de vetores
#include "Object.h"						// objetos do jogo
#include "Sprite.h"						// sprites
#include "Timer.h"						// controle do tempo
#include "Joystick.h"
#include "Animation.h"

// ---------------------------------------------------------------------------------
enum estado {PARADO , ANDANDO};
//----------------------------------------------------------------------------------
class Player : public Object
{
private:
	TileSet  * tileset;                 //folha de sprite --modificado--
	Animation * ani;                     //animacao ---modificado--
	Sprite * sprite;					// sprite do objeto
	Joystick * joy;						// entrada de joystick
	Timer  timer;						// controle do tempo

public:
	Vector * speed;						// velocidade e direção
	bool joystickOn;					// joystick conectado
	

	void OnCollision(Object * obj);		// tratamento de colisão
	void Move(Vector & v);				// movimenta jogador
	void Update(float gameTime);		// atualiza estado do objeto
	void Draw();						// desenha objeto


	uint estado;		                 // estado do player --modificado--
	uint estadoAnterior;                  //estado anterior do player --modificado--

	Player();
	~Player();
}; 

// ---------------------------------------------------------------------------------

inline void Player::Draw()
{ ani->Draw(X(), Y(), 0.19f, 1.0f, -speed->angle + 90.0f); }

// ---------------------------------------------------------------------------------

#endif