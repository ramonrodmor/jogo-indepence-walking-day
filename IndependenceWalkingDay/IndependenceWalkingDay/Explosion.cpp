/**********************************************************************************
// Explosion (C�digo Fonte)
//
// Cria��o:		17 Mar 2013
// Atualiza��o:	17 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Efeito de explos�o usando sistema de part�culas
//
**********************************************************************************/

#include "Explosion.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(float x, float y)
{
	ParticleDesc exploDesc;
	exploDesc.imgFile = "Resources/Particle.png";	// arquivo de imagem
	exploDesc.baseAngle = rand() % 360;				// dire��o da explos�o
	exploDesc.spread = 180;							// espalhamento em graus
	exploDesc.lifeTime = 0.7f;						// tempo de vida em segundos
	exploDesc.genTime = 0.000f;						// tempo entre gera��o de novas part�culas
	exploDesc.minSpeed = 0.01f;						// velocidade m�nima das part�culas
	exploDesc.maxSpeed = 0.03f;						// velocidade m�xima das part�culas
	exploDesc.r = 180.0f;							// cor da part�cula
	exploDesc.g = 0.0f;								// cor da part�cula
	exploDesc.b = 0.0f;								// cor da part�cula
	exploDesc.a = 1.0f;								// cor da part�cula

	explosion = new Particles(exploDesc);
	explosion->Generate(x, y, 50);
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
	delete explosion;
}


// -------------------------------------------------------------------------------

void Explosion::Update(float gameTime)
{
	explosion->Update(50 * gameTime);
	if (explosion->Inactive())
		GeometryWars::scene->Remove();
}

// -------------------------------------------------------------------------------