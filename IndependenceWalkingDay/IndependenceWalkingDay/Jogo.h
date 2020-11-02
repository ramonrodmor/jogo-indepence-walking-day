/**********************************************************************************
// MenuDemo (Arquivo de Cabe�alho)
//
// Cria��o:		14 Mai 2012
// Atualiza��o:	20 Jun 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Exemplo de interface menu
//
**********************************************************************************/

#ifndef _JOGO_H_
#define _JOGO_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Resources.h"
#include "Audio.h"
#include "GeometryWars.h"
#include "Menu.h"

// ------------------------------------------------------------------------------

enum Music  { MENU, FASE1, GAMEOVER, TIRO };
enum JogoObj { INIMIGO, MISSIL, PLAYER };

// ------------------------------------------------------------------------------

class Jogo : public Game
{
private:

	Sprite  * backg;				// plano de fundo
	bool ctrlKey;					// controla pressionamento de teclas
	static Game * level;			// n�vel atual do jogo

public:

	static Audio	* audio;		// audio do jogo
	static bool  viewBBox;			// visualiza bounding box
	static int pontuacao;
	static int onda;
	static int inimigos;

	template<class T>
	static void NextLevel()			// muda para pr�ximo n�vel do jogo
	{
		if (level)
		{
			level->Finalize();
			delete level;
			level = new T();
			level->Init();
		}
	};

	void Init();					// inicializa jogo
	void Update(float gameTime);	// atualiza l�gica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif