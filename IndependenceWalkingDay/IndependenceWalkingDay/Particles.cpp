/**********************************************************************************
// Particles (Código Fonte)
// 
// Criação:		07 Out 2012
// Atualização:	17 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Define um sistema de partículas
//
**********************************************************************************/

#include "Particles.h"
#include "Geometry.h"
#include <cmath>


// ---------------------------------------------------------------------------------

Particles::Particles(const ParticleDesc& desc)
{
	sprite = new Sprite(desc.imgFile);
	lifeTime = desc.lifeTime;
	genTime = desc.genTime;
	minSpeed = desc.minSpeed;
	maxSpeed = desc.maxSpeed;
	r = desc.r;
	g = desc.g;
	b = desc.b;
	a = desc.a;
	baseAngle = desc.baseAngle;
	spread = desc.spread;
	timer.Start();
}

// ---------------------------------------------------------------------------------

Particles::~Particles()
{
	delete sprite;
	for (auto i = particles.begin(); i != particles.end(); ++i)
		delete (*i);
	particles.clear();
}

// ---------------------------------------------------------------------------------

void Particles::GenParticle(float posX, float posY)
{
	Particle * p = new Particle();
	p->x = posX;
	p->y = posY;
	
	int angle = baseAngle + spread - (rand() % (2*spread+1));
	
	if (angle > 360)
		angle -= 360;
	else if (angle < 0)
		angle += 360;
	
	p->speed.angle = float(angle);	
	p->speed.magnitude = minSpeed + (rand() % 101) * 0.01f * (maxSpeed-minSpeed);
	p->timeStamp = timer.TimeStamp();

	particles.push_back(p);
}

// ---------------------------------------------------------------------------------

void Particles::Generate(float x, float y, int num)
{
	if (num == 1)
	{
		if (timer.Elapsed(genTime)) 
		{
			GenParticle(x, y);
			timer.Reset();
		}
	} 
	else 
	{	
		for (int i=0; i < num; i++)
			GenParticle(x, y);		
	}
}

// ---------------------------------------------------------------------------------

void Particles::Update(float deltaT)
{
	float lifePercent = 0;
	float timeElapsed = 0;
	const float dimTime = 0.6f;

	auto i = particles.begin();
	while (i != particles.end())
	{
		Particle * p = *i;
		p->x += p->speed.CompX() * deltaT;
		p->y -= p->speed.CompY() * deltaT;
		
		timeElapsed = timer.Elapsed(p->timeStamp);
		lifePercent = timeElapsed/lifeTime;

		// torna partícula transparente com o passar do tempo
		if (lifePercent > dimTime)
			a = 1.0f - pow(lifePercent, 3);

		// remove partícula sem vida
		if (timeElapsed > lifeTime)
		{
			delete *i;
			i = particles.erase(i);
		}
		else
		{
			i++;
		}
	}
}

// ---------------------------------------------------------------------------------


void Particles::Draw(float z, float scaleFactor)
{
	float lifePercent = 0.0f;
	float timeElapsed = 0.0f;
	
	for (auto i = particles.begin(); i != particles.end(); ++i)
	{
		Particle * p = *i;

		timeElapsed = timer.Elapsed(p->timeStamp);
		lifePercent = timeElapsed/lifeTime;

		// escala cresce quadraticamente com o tempo de vida
		float scale = 1.0f + pow(lifePercent, 2) * scaleFactor;

		sprite->Draw(p->x, p->y, z, scale, 0, Color(r, g, b, a));
	}	
}

// ---------------------------------------------------------------------------------
