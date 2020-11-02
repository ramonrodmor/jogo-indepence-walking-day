/**********************************************************************************
// Image (C�digo Fonte)
// 
// Cria��o:		16 Mar 2012
// Atualiza��o:	23 Jul 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Define uma classe para representar imagens
//
**********************************************************************************/

#include "Image.h"
#include "Graphics.h"

// -------------------------------------------------------------------------------

Image::Image(string filename)
{
	textureView = nullptr;

	// cria sharer resource view da imagem em disco
	D3D11CreateTextureFromFile(
		Graphics::Device(),			// dispositivo Direct3D
		Graphics::Context(),		// contexto do dispositivo
		filename.c_str(),			// nome do arquivo de imagem
		nullptr,					// retorna textura 
		&textureView,				// retorna view da textura
		width,						// retorna largura da imagem
		height);					// retorna altura da imagem
}

// -------------------------------------------------------------------------------

Image::Image(string filename, uint tileWidth, uint tileHeight, uint numColumns, 
	 int * tileMap, uint tileMapCols, uint tileMapRows)
{
	// textura para guardar os blocos de imagem
	ID3D11Resource * mapTexture = nullptr;
	uint mapWidth = 0;
	uint mapHeight = 0;

	// cria textura fonte (blocos de imagem)
	D3D11CreateTextureFromFile(
		Graphics::Device(),			// dispositivo Direct3D
		Graphics::Context(),		// contexto do dispositivo
		filename.c_str(),			// nome do arquivo de imagem
		&mapTexture,				// retorna textura 
		nullptr,					// retorna view da textura
		mapWidth,					// retorna largura da imagem
		mapHeight);					// retorna altura da imagem

	
	// descri��o da textura de destino
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = tileWidth * tileMapCols;
	desc.Height = tileHeight * tileMapRows;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	// cria textura de destino (imagem gerada a partir dos blocos) 
	ID3D11Texture2D* texture = nullptr;
	Graphics::Device()->CreateTexture2D(&desc, nullptr, &texture);

	// preenche imagem destino a partir dos blocos de imagens
	for (uint j = 0; j < tileMapRows; ++j)
	{
		for (uint i = 0; i < tileMapCols; ++i)
		{
			// os �ndices do mapa gerado pelo aplicativo Tiled iniciam em 1
			// e os �ndices do vetor de blocos no C++ iniciam em 0,
			// por isso � necess�rio subtrair um da vari�vel tileNum
			uint tileNum = tileMap[i + j * tileMapCols] - 1;
			
			uint x = i * tileWidth;
			uint y = j * tileHeight;

			D3D11_BOX sourceRegion;
			sourceRegion.left = (tileNum % numColumns) * tileWidth;
			sourceRegion.top = (tileNum / numColumns) * tileHeight;
			sourceRegion.right = sourceRegion.left + tileWidth;
			sourceRegion.bottom = sourceRegion.top + tileHeight;
			sourceRegion.front = 0;
			sourceRegion.back = 1;

			// copia regi�o de uma textura para outra
			Graphics::Context()->CopySubresourceRegion(texture, 0, x, y, 0, mapTexture, 0, &sourceRegion);
		}
	}

	// descri��o da resource view da textura de destino
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	memset(&viewDesc, 0, sizeof(viewDesc));
	viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;

	// inicializa atributos da imagem
	textureView = nullptr;
	width = desc.Width;
	height = desc.Height;

	// cria uma shader resource view para a textura obtida
	Graphics::Device()->CreateShaderResourceView(texture, &viewDesc, &textureView);

	// texturas n�o s�o mais necess�rias
	mapTexture->Release();
	texture->Release();
}

// -------------------------------------------------------------------------------

Image::~Image()
{
	// libera mem�ria ocupada pela texture view
	if (textureView)
	{
		// pega ponteiro para recurso
		ID3D11Resource * resource = nullptr;
		textureView->GetResource(&resource);

		// liberando a view n�o libera automaticamente
		// o recurso que foi criado junto com a view
		if (resource)
		{
			resource->Release();
			resource = nullptr;
		}

		textureView->Release();
		textureView = nullptr;
	}
}

// -------------------------------------------------------------------------------