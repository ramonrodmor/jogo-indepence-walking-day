/**********************************************************************************
// Home (Arquivo de Cabeçalho)
//
// Criação:		14 Fev 2013
// Atualização:	18 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Tela de abertura do jogo GravityGuy
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
	Animation * anim;				// animação do menu
	Joystick * joy;

public:
	bool joystickOn;					// joystick conectado

	void Init();					// inicia nível
	void Update(float gameTime);	// atualiza lógica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza nível
};

// -----------------------------------------------------------------------------

#endif