/**********************************************************************************
// GeometryWars (Arquivo de Cabe�alho)
//
// Cria��o:		23 Out 2012
// Atualiza��o:	25 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Jogo demonstrando Scrolling e IA
//
**********************************************************************************/

#ifndef _GEOMETRY_WARS_H_
#define _GEOMETRY_WARS_H_

// ------------------------------------------------------------------------------

#include "Resources.h"				// recursos utilizados no jogo (cursor, �cone, etc.) 
#include "Game.h"					// defini��o da classe jogo
#include "Font.h"					// fonte para exibi��o de texto
#include "Sprite.h"					// defini��o dos sprites
#include "Scene.h"					// defini��o da cena do jogo
#include "Player.h"					// defini��o do jogador
#include "Background.h"				// defini��o do pano de fundo
#include "Gameover.h"
#include <sstream>					// sa�da para strings
using std::stringstream;

// ------------------------------------------------------------------------------

class GeometryWars : public Game
{
private:
	Sprite * infoBox;				// caixa de informa��es
	Sprite * keyMap;				// caixa para teclas de atalho
	Background * backg;				// pano de fundo
	Font   * font;					// fonte para texto
	stringstream text;				// texto tempor�rio
	Player * player;

public:
	static Scene * scene;			// cena do jogo
	static short jogador;

	void Init();					// inicializa jogo
	void Update(float gameTime);	// atualiza l�gica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif