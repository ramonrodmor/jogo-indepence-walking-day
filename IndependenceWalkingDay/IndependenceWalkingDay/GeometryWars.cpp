/**********************************************************************************
// GeometryWars (Código Fonte)
//
// Criação:		23 Out 2012
// Atualização:	25 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Jogo demonstrando Scrolling e IA
//
**********************************************************************************/

#include "GeometryWars.h"			// classe do jogo
#include "Engine.h"					// motor de jogo
#include "Magenta.h"				// inimigo rosa
#include "Blue.h"					// inimigo azul
#include "Green.h"					// inimigo verde
#include "Linear.h"
#include "Aleatorio.h"
#include "Player.h"

// ------------------------------------------------------------------------------

Scene * GeometryWars::scene = nullptr;
short GeometryWars::jogador = 0;

// ------------------------------------------------------------------------------

void GeometryWars::Init()
{
	// cria fontes para exibição de texto
	font = new Font("Resources/Tahoma10.png");
	font->Spacing("Resources/Tahoma10.dat");

	// carrega/incializa objetos
	backg = new Background("Resources/SpaceArt.jpg");
	keyMap = new Sprite("Resources/Keymap.png");
	player = new Player();
	scene = new Scene();

	// calcula posição para manter viewport centralizada
	float difx = (WorldWidth() - window->Width()) / 2.0f;
	float dify = (WorldHeight() - window->Height()) / 2.0f;

	// inicializa viewport para o centro do background
	viewport.left = 0.0f + difx;
	viewport.right = viewport.left + window->Width();
	viewport.top = 0.0f + dify;
	viewport.bottom = viewport.top + window->Height();

	// adiciona objetos na cena
	scene->Add(player, MOVING);
	scene->CollisionResolution(player);
	GeometryWars::jogador = 1;
	Jogo::onda = 1;
	Jogo::pontuacao = 0;
	Jogo::inimigos = 0;
	
	Object * obj;
	for (int i = 0; i < Jogo::onda ; i++)
	{
		obj = new Magenta(player);
		scene->Add(obj, MOVING);
		scene->CollisionResolution(obj);

		obj = new Blue(player);
		scene->Add(obj, MOVING);
		scene->CollisionResolution(obj);

		obj = new Aleatorio(player);
		scene->Add(obj, MOVING);
		scene->CollisionResolution(obj);

		obj = new Linear(player);
		scene->Add(obj, MOVING);
		scene->CollisionResolution(obj);

		obj = new Green(player);
		scene->Add(obj, MOVING);
		scene->CollisionResolution(obj);
		Jogo::inimigos += 5;
	}

	Jogo::audio->Play(FASE1, true);
}

// ------------------------------------------------------------------------------

void GeometryWars::Update(float gameTime)
{
	

	if (Jogo::inimigos < 1)
	{
		Jogo::onda++;
		Object * obj;
		for (int i = 0; i < Jogo::onda; i++)
		{
			obj = new Magenta(player);
			scene->Add(obj, MOVING);
			scene->CollisionResolution(obj);

			obj = new Blue(player);
			scene->Add(obj, MOVING);
			scene->CollisionResolution(obj);

			obj = new Aleatorio(player);
			scene->Add(obj, MOVING);
			scene->CollisionResolution(obj);

			obj = new Linear(player);
			scene->Add(obj, MOVING);
			scene->CollisionResolution(obj);

			obj = new Green(player);
			scene->Add(obj, MOVING);
			scene->CollisionResolution(obj);
			Jogo::inimigos += 5;
		}
	}

	float deltaT = 50 * gameTime;

	if (window->KeyCtrl(VK_ESCAPE))
	{
		Jogo::audio->Stop(FASE1);
		Jogo::pontuacao = Jogo::onda = 0;
		Jogo::NextLevel<Menu>();
	}

	scene->Update(deltaT);
	scene->CollisionDetection();

	// ---------------------------------------------------
	// atualiza a viewport
	// ---------------------------------------------------
	viewport.left = player->X() - window->CenterX();
	viewport.right = player->X() + window->CenterX();
	viewport.top = player->Y() - window->CenterY();
	viewport.bottom = player->Y() + window->CenterY();

	if (viewport.left < 0)
	{
		viewport.left = 0;
		viewport.right = float(window->Width());
	}
	else if (viewport.right > WorldWidth())
	{
		viewport.left = float(WorldWidth() - window->Width());
		viewport.right = float(WorldWidth());
	}

	if (viewport.top < 0)
	{
		viewport.top = 0;
		viewport.bottom = float(window->Height());
	}
	else if (viewport.bottom > WorldHeight())
	{
		viewport.top = float(WorldHeight() - window->Height());
		viewport.bottom = float(WorldHeight());
	}

	if (GeometryWars::jogador == 0)
	{
		viewport.top = 0;
		viewport.bottom = 0;
		viewport.right = 0;
		viewport.left = 0;
		Sleep(20);
		Jogo::audio->Stop(FASE1);
		Jogo::NextLevel<Gameover>();
		//return;
	}
}

// ------------------------------------------------------------------------------

void GeometryWars::Draw()
{
	backg->Draw(viewport);
	keyMap->Draw(viewport.left + window->CenterX() + 250, viewport.top + window->Height() - 16.0f);
	keyMap->Draw(viewport.left + window->CenterX() - 250, viewport.top + window->Height() - 16.0f);

	scene->Draw();

	text.str("");
	text << "Pontuação: " << Jogo::pontuacao << "\t" << "Onda de inimigos: " << Jogo::onda;
	font->Draw(window->CenterX() - 360.0f, window->Height() - 17.0f, text.str());

	text.str("");
	text << "Inimigos: " << Jogo::inimigos;
	font->Draw(window->CenterX() + 225.0f, window->Height() - 17.0f, text.str());
}

// ------------------------------------------------------------------------------

void GeometryWars::Finalize()
{
	delete scene;
	delete infoBox;
	delete keyMap;
	delete backg;
	delete font;
}
