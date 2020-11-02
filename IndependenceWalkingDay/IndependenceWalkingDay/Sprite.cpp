/**********************************************************************************
// Sprite (Código Fonte)
// 
// Criação:		11 Jul 2007
// Atualização:	23 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Define uma classe para representar um sprite
//
**********************************************************************************/

#include "Sprite.h"
#include "Engine.h"

// ---------------------------------------------------------------------------------

Sprite::Sprite(string filename)
{
	// carrega imagem
	image = new Image(filename);
	localImage = true;
	
	// configura registro sprite
	spriteInfo.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(const Image * img)
{
	// aponta para imagem externa
	image = img;
	localImage = false;

	// configura registro sprite
	spriteInfo.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{
	if (localImage)
		delete image;
}

// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z, float scale, float rotation, Color & color)
{
	// ajusta coordenadas para viewport
	x -= Game::viewport.left;
	y -= Game::viewport.top;

	spriteInfo.x = x;
	spriteInfo.y = y;
	spriteInfo.scale = scale;
	spriteInfo.depth = z;
	spriteInfo.rotation = rotation * XM_PI / 180.0f;
	spriteInfo.width = image->Width();
	spriteInfo.height = image->Height();
	spriteInfo.color = color;

	// adiciona o sprite na lista de desenho
	Engine::renderer->Draw(spriteInfo);
}

// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z, float scale, float rotation, Color & color, RECT & region)
{
	// ajusta coordenadas para viewport
	x -= Game::viewport.left;
	y -= Game::viewport.top;

	spriteInfo.x = x;
	spriteInfo.y = y;
	spriteInfo.scale = scale;
	spriteInfo.depth = z;
	spriteInfo.rotation = rotation * XM_PI / 180.0f;
	spriteInfo.width = region.right - region.left;
	spriteInfo.height = region.bottom - region.top;
	spriteInfo.texCoord.x = float(region.left) / image->Width();
	spriteInfo.texCoord.y = float(region.top) / image->Height();
	spriteInfo.texSize.x = float(spriteInfo.width) / image->Width();
	spriteInfo.texSize.y = float(spriteInfo.height) / image->Height();
	spriteInfo.color = color;

	// adiciona o sprite na lista de desenho
	Engine::renderer->Draw(spriteInfo);
}

// ---------------------------------------------------------------------------------