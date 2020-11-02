/**********************************************************************************
// GeometryWars (Arquivo de Cabeçalho)
//
// Criação:		23 Out 2012
// Atualização:	25 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Jogo demonstrando Scrolling e IA
//
**********************************************************************************/

#ifndef _GEOMETRY_WARS_H_
#define _GEOMETRY_WARS_H_

// ------------------------------------------------------------------------------

#include "Resources.h"				// recursos utilizados no jogo (cursor, ícone, etc.) 
#include "Game.h"					// definição da classe jogo
#include "Font.h"					// fonte para exibição de texto
#include "Sprite.h"					// definição dos sprites
#include "Scene.h"					// definição da cena do jogo
#include "Player.h"					// definição do jogador
#include "Background.h"				// definição do pano de fundo
#include "Gameover.h"
#include <sstream>					// saída para strings
using std::stringstream;

// ------------------------------------------------------------------------------

class GeometryWars : public Game
{
private:
	Sprite * infoBox;				// caixa de informações
	Sprite * keyMap;				// caixa para teclas de atalho
	Background * backg;				// pano de fundo
	Font   * font;					// fonte para texto
	stringstream text;				// texto temporário
	Player * player;

public:
	static Scene * scene;			// cena do jogo
	static short jogador;

	void Init();					// inicializa jogo
	void Update(float gameTime);	// atualiza lógica do jogo
	void Draw();					// desenha jogo
	void Finalize();				// finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif