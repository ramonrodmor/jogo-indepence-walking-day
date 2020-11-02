/**********************************************************************************
// InputDemo (Código Fonte)
//
// Criação:		14 Mai 2012
// Atualização:	20 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Exemplo de interface menu
//
**********************************************************************************/

#include "Engine.h"
#include "Jogo.h"

// ------------------------------------------------------------------------------

Game *  Jogo::level = nullptr;
bool    Jogo::viewBBox = false;
Audio * Jogo::audio = nullptr;
int		Jogo::pontuacao = 0;
int		Jogo::onda = 0;
int		Jogo::inimigos = 0;

// ------------------------------------------------------------------------------

void Jogo::Init()
{
	// cria sistema de audio
	audio = new Audio();
	audio->Add(MENU, "Resources/menu.wav");
	audio->Add(FASE1, "Resources/jogo.wav");
	audio->Add(GAMEOVER, "Resources/Gameover.wav");
	audio->Add(TIRO, "Resources/tiro.wav");
	
	// cria mouse
	viewBBox = false;
	ctrlKey = true;
	level = new Menu();
	level->Init();

}

// ------------------------------------------------------------------------------

void Jogo::Update(float gameTime)
{
	// habilita/desabilita visualização da bounding box
	if (window->KeyUp('B'))
		ctrlKey = true;
	if (ctrlKey && window->KeyDown('B'))
	{
		viewBBox = !viewBBox;
		ctrlKey = false;
	}

	// atualiza nível
	level->Update(gameTime);
}

// ------------------------------------------------------------------------------

void Jogo::Draw()
{
	// desenha nível
	level->Draw();
}

// ------------------------------------------------------------------------------

void Jogo::Finalize()
{
	level->Finalize();
	delete level;
	delete audio;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// cria motor do jogo
	Engine * engine = new Engine();

	// configura janela
	engine->window->Mode(WINDOWED);
	engine->window->Size(800, 600);
	engine->window->Color(0, 0, 0);
	engine->window->Title("Independence Walking Day");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	engine->window->HideCursor(true);

	// configura dispositivo gráfico
	//engine->graphics->VSync(true);

	// cria e inicia o jogo
	Game * game = new Jogo();
	game->WorldSize(1920, 1200);
	engine->Start(game);

	delete engine;
	return 0;
}

// ----------------------------------------------------------------------------
