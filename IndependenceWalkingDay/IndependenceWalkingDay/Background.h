/**********************************************************************************
// Background (Arquivo de Cabe�alho)
// 
// Cria��o:		07 Dez 2011
// Atualiza��o:	30 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Define uma classe para construir backgrounds
//
**********************************************************************************/

#ifndef _DESENVJOGOS_BACKGROUND_H_
#define _DESENVJOGOS_BACKGROUND_H_

// -------------------------------------------------------------------------------

#include "Types.h"          // tipos espec�ficos da engine
#include "Image.h"			// imagem do background
#include <string>			// string de C++
using std::string;			// usando strings

// -------------------------------------------------------------------------------

class Background
{
private:
	SpriteInfo spriteInfo;				// informa��es do sprite 
	const Image * image;				// imagem da superf�cie

public:
	Background(string filename);		// construtor	
	~Background();						// destrutor

	void Draw(ViewPort & sourceRect);	// desenha uma por��o da imagem na tela
	uint Width();						// retorna a largura do background
    uint Height();						// retorna a altura do background
}; 

// ---------------------------------------------------------------------------------
// Fun��es Inline

// retorna a largura do sprite
inline uint Background::Width() 
{ return image->Width(); }

// retorna a altura do sprite
inline uint Background::Height() 
{ return image->Height(); }

// -------------------------------------------------------------------------------


#endif