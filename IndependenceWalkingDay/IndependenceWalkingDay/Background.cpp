/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:		07 Dez 2011
// Atualização:	30 Jul 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Define uma classe para construir backgrounds
//
**********************************************************************************/


#include "Background.h"
#include "Engine.h"

// -------------------------------------------------------------------------------

Background::Background(string filename)
{
	// carrega imagem
	image = new Image(filename);

	// configura registro spriteInfo
	spriteInfo.x = Engine::window->CenterX();
	spriteInfo.y = Engine::window->CenterY();
	spriteInfo.scale = 1.0f;
	spriteInfo.depth = 1.0f;
	spriteInfo.rotation = 0.0f;	
	spriteInfo.color = Color(1, 1, 1, 1);
	spriteInfo.texture = image->View();
}

// -------------------------------------------------------------------------------

Background::~Background()
{
	delete image;
}

// -------------------------------------------------------------------------------

void Background::Draw(ViewPort & vp)
{ 
	// posiciona viewport no background
	spriteInfo.width = uint(vp.right - vp.left);
	spriteInfo.height = uint(vp.bottom - vp.top);
	spriteInfo.texCoord.x = vp.left / float(image->Width());
	spriteInfo.texCoord.y = vp.top / float(image->Height());
	spriteInfo.texSize.x = spriteInfo.width / float(image->Width());
	spriteInfo.texSize.y = spriteInfo.height / float(image->Height());

	// adiciona o sprite na lista de desenho
	Engine::renderer->Draw(spriteInfo);
}

// -------------------------------------------------------------------------------

