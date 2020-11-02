/**********************************************************************************
// Explosion (Código Fonte)
//
// Criação:		17 Mar 2013
// Atualização:	17 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#include "Explosion.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(float x, float y)
{
	ParticleDesc exploDesc;
	exploDesc.imgFile = "Resources/Particle.png";	// arquivo de imagem
	exploDesc.baseAngle = rand() % 360;				// direção da explosão
	exploDesc.spread = 180;							// espalhamento em graus
	exploDesc.lifeTime = 0.7f;						// tempo de vida em segundos
	exploDesc.genTime = 0.000f;						// tempo entre geração de novas partículas
	exploDesc.minSpeed = 0.01f;						// velocidade mínima das partículas
	exploDesc.maxSpeed = 0.03f;						// velocidade máxima das partículas
	exploDesc.r = 180.0f;							// cor da partícula
	exploDesc.g = 0.0f;								// cor da partícula
	exploDesc.b = 0.0f;								// cor da partícula
	exploDesc.a = 1.0f;								// cor da partícula

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