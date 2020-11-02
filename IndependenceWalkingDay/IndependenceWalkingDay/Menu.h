/**********************************************************************************
// Home (Arquivo de Cabe�alho)
//
// Cria��o:		14 Fev 2013
// Atualiza��o:	18 Jun 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Tela de abertura do jogo GravityGuy
//
**********************************************************************************/

#ifndef _MARIO_HOME_H_
#define _MARIO_HOME_H_

// ------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "TileSet.h"
#include "Animation.h"

// ------------------------------------------------------------------------------

class Menu : public Game
{
private:
	Sprite * fundo;					// background
	Animation * anim;				// anima��o do menu
	Joystick * joy;

public:
	bool joystickOn;					// joystick conectado

	void Init();					// inicia n�vel
	void Update(float gameTime);	// atualiza l�gica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza n�vel
};

// -----------------------------------------------------------------------------

#endif