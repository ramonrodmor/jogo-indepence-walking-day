/**********************************************************************************
// Engine (Arquivo de Cabeçalho)
//
// Criação:		15 Mai 2014
// Atualização: 23 Mai 2014
// Compilador:	Visual C++ 12
//
// Descrição:	A função da Engine é rodar jogos criados a partir da classe 
//              abstrata Game. Todo jogo deve ser uma classe derivada de Game 
//              e portanto deve implementar as funções membro Init, Update, Draw 
//              e Finalize, que serão chamadas pelo motor em um loop de tempo real. 
//              Para usar a classe Engine, o programador deve criar uma instância 
//              e chamar o método Start(), passando um objeto derivado de Game.
//
**********************************************************************************/

#ifndef _DESENVJOGOS_ENGINE_H_
#define _DESENVJOGOS_ENGINE_H_

// ---------------------------------------------------------------------------------

#include "Game.h"						// implementação do jogo
#include "Window.h"						// janela do jogo
#include "Graphics.h"					// hardware gráfico
#include "Renderer.h"					// renderizador de sprites
#include "Timer.h"						// medidor de tempo

// ---------------------------------------------------------------------------------

class Engine
{
private:
	static Game * game;					// jogo a ser executado
	static bool gamePaused;				// estado do jogo
	static Timer timer;					// medidor de tempo

	int Run();							// inicia execução do jogo
	float FrameTime();					// calcula o tempo do quadro	

public:
	static Window   * window;			// janela do jogo
	static Graphics * graphics;			// dispositivo gráfico
	static Renderer * renderer;			// renderizador de sprites

	Engine();							// construtor
	~Engine();							// destrutor

	int Start(Game * level);			// inicia o game loop
	static void Pause();				// pausa o game loop
	static void Resume();				// reinicia o game loop
	
	template<class T> 
	static void Next()					// muda para próximo nível do jogo
	{
		if (game)
		{
			game->Finalize();
			delete game;
			game = new T();
			game->Init();
		}
	};
};

// ---------------------------------------------------------------------------------

#endif