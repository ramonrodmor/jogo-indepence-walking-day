/**********************************************************************************
// Game (C�digo Fonte)
//
// Cria��o:		08 Dez 2012
// Atualiza��o:	15 Mai 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Uma class abstrata para representar um jogo.
//
//              Para criar um jogo o programador deve criar uma classe derivada
//              de Game e sobrescrever os m�todos Init, Update, Draw e Finalize.
//              Para rodar o jogo, deve-se passar o objeto Game para o m�todo
//              Start() de um objeto Engine.
//
**********************************************************************************/

#include "Game.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe

Window * Game::window = nullptr;				// ponteiro para a janela
ViewPort Game::viewport = { 0 };				// coordenadas da janela no mundo do jogo

float Game::worldWidth   = 0;					// largura do mundo do jogo
float Game::worldHeight  = 0;					// altura do mundo do jogo
float Game::worldCenterX = 0;					// centro do mundo do jogo no eixo x
float Game::worldCenterY = 0;					// centro do mundo do jogo no eixo y

// -------------------------------------------------------------------------------

Game::Game()
{
	if (!window)
	{
		// assume que a inst�ncia da engine �  
		// criada antes da inst�ncia do jogo
		window = Engine::window;
	}
}

// -------------------------------------------------------------------------------

Game::~Game()
{
}

// -------------------------------------------------------------------------------

void Game::OnPause()
{
	Sleep(10);
}

// -------------------------------------------------------------------------------

void Game::WorldSize(float width, float height)
{
	worldWidth = width;
	worldHeight = height;
	worldCenterX = worldWidth / 2;
	worldCenterY = worldHeight / 2;
}

// -------------------------------------------------------------------------------

 float Game::WorldWidth()
{
	 return worldWidth;
}

// -------------------------------------------------------------------------------

 float Game::WorldHeight()
{
	return worldHeight;
}

// -------------------------------------------------------------------------------

 float Game::WorldCenterX()
{
	return worldCenterX;
}

// -------------------------------------------------------------------------------

 float Game::WorldCenterY()
{
	return worldCenterY;
}

// -------------------------------------------------------------------------------