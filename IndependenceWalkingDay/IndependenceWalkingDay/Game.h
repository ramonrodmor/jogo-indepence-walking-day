/**********************************************************************************
// Game (Arquivo de Cabeçalho)
// 
// Criação:		08 Dez 2012
// Atualização:	15 Mai 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Uma class abstrata para representar um jogo.
//
//              Para criar um jogo o programador deve criar uma classe derivada
//              de Game e sobrescrever os métodos Init, Update, Draw e Finalize.
//              Para rodar o jogo, deve-se passar o objeto Game para o método 
//              Start() de um objeto Engine.
//
**********************************************************************************/

#ifndef _DESENVJOGOS_GAME_H_
#define _DESENVJOGOS_GAME_H_

// ---------------------------------------------------------------------------------

#include "Window.h"

// ---------------------------------------------------------------------------------

class Game
{
	// Membros protegidos são privados para o mundo externo mas
	// públicos para as classes derivadas, ou seja, as classes
	// derivadas de Game serão capazes de acessar estes membros.
protected:
	 static Window * window;							// janela do jogo

	 static float worldWidth;							// largura do mundo do jogo
	 static float worldHeight;							// altura do mundo do jogo
	 static float worldCenterX;							// centro do mundo do jogo no eixo x
	 static float worldCenterY;							// centro do mundo do jogo no eixo y
	 
public:
	static ViewPort viewport;							// coordenadas da janela no mundo do jogo

	Game();												// construtor
	virtual ~Game();									// destrutor

	static void WorldSize(float width, float height);	// define o tamanho do mundo do jogo

	static float WorldWidth();							// retorna a largura atual do mundo do jogo
	static float WorldHeight();							// retorna a altura atual do mundo do jogo
	static float WorldCenterX();						// retorna o centro do mundo de jogo no eixo x
	static float WorldCenterY();						// retorna o centro do mundo de jogo no eixo y	

	// Estes métodos são puramente virtuais, isto é, devem ser 
	// implementados em todas as classes derivas de Game.
	virtual void Init()                 = 0;	// inicialização do jogo
	virtual void Update(float gameTime) = 0;	// atualização do jogo
	virtual void Draw()                 = 0;	// desenho da cena
	virtual void Finalize()             = 0;	// finalização do jogo
	virtual void OnPause();						// jogo foi pausado
};

// ---------------------------------------------------------------------------------

#endif