/**********************************************************************************
// Window (Código Fonte)
// 
// Criação:		19 Mai 2007
// Atualização:	20 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	A classe abstrai todos os detalhes de configuração de
//              uma janela para um jogo. 
//
**********************************************************************************/

#include "Window.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Construtor

Window::Window()
{
	hInstance		= GetModuleHandle(NULL);				// identificador da aplicação
	windowHandle	= 0;									// identificador da janela do jogo
	windowWidth		= GetSystemMetrics(SM_CXSCREEN);		// a janela ocupa toda a tela (tela cheia)
	windowHeight	= GetSystemMetrics(SM_CYSCREEN);		// a janela ocupa toda a tela (tela cheia)
	windowIcon		= LoadIcon(NULL, IDI_APPLICATION);		// ícone padrão de uma aplicação
	windowCursor	= LoadCursor(NULL, IDC_ARROW);			// cursor padrão de uma aplicação
	windowColor	    = RGB(0,0,0);							// cor de fundo padrão é preta
	windowTitle		= string("Windows Game");				// título padrão da janela
	windowStyle		= WS_POPUP | WS_VISIBLE;				// estilo para tela cheia
	windowMode		= FULLSCREEN;							// modo padrão é tela cheia
	windowPosX		= 0;									// posição inicial da janela no eixo x
	windowPosY		= 0;									// posição inicial da janela no eixo y
	windowCenterX   = windowWidth/2.0f;						// centro da janela no eixo x
	windowCenterY	= windowHeight/2.0f;					// centro da janela no eixo y
	ZeroMemory(&windowCtrl, sizeof(windowCtrl));			// controle de teclas inicia falso
}

// -------------------------------------------------------------------------------

bool Window::KeyCtrl(int vkcode)
{
	if (windowCtrl[vkcode])
	{
		if (KeyDown(vkcode))
		{
			windowCtrl[vkcode] = false;
			return true;
		}
	}
	else if (KeyUp(vkcode))
	{
		windowCtrl[vkcode] = true;
	}

	return false;
}

// ---------------------------------------------------------------------------------

POINT Window::Mouse()
{
	// pega posição (x,y) do mouse
	POINT pointer;
	GetCursorPos(&pointer);

	// converte para coordenadas da área cliente
	ScreenToClient(windowHandle, &pointer);

	return pointer;
}

// -------------------------------------------------------------------------------

void Window::Mode(int mode)
{
	windowMode = mode;

	if (mode == WINDOWED)
	{
		// modo em janela
		windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE; 
	}
	else
	{
		// modo em tela cheia ou sem bordas
		windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE; 
	} 
}

// -------------------------------------------------------------------------------

void Window::Size(int width, int height)
{ 
	// window size
	windowWidth = width; 
	windowHeight = height;

	// calcula a posição do centro da janela
	windowCenterX = windowWidth/2.0f;
	windowCenterY = windowHeight/2.0f;

	// ajusta a posição da janela para o centro da tela
	windowPosX = (GetSystemMetrics(SM_CXSCREEN)/2) - (windowWidth/2);
	windowPosY = (GetSystemMetrics(SM_CYSCREEN)/2) - (windowHeight/2);
}

// -------------------------------------------------------------------------------

void Window::Print(string text, int x, int y, COLORREF color)
{
	// esta função exibe o texto na posição (x,y) da tela usando a cor especificada
	// ela usa a GDI do Windows (lenta) e deve ser usada apenas para depuração

	// pega o contexto do dispositivo gráfico
	HDC xdc = GetDC(windowHandle); 

	// define a cor do texto
	SetTextColor(xdc, color);

	// define o fundo do texto como transparente
	SetBkMode(xdc, TRANSPARENT);

	// mostra o texto
	TextOut(xdc, x, y, text.c_str(), text.size());

	// libera o contexto do dispositivo
	ReleaseDC(windowHandle, xdc);
}

// -------------------------------------------------------------------------------

bool Window::Initialize()
{
	WNDCLASSEX wndClass; 
	
	// definindo uma classe de janela chamada "GameWindow"
	wndClass.cbSize         = sizeof(WNDCLASSEX);
	wndClass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= Window::WinProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= windowIcon;
	wndClass.hCursor		= windowCursor; 
	wndClass.hbrBackground	= (HBRUSH) CreateSolidBrush(windowColor);
	wndClass.lpszMenuName	= NULL;
	wndClass.lpszClassName	= "GameWindow";
	wndClass.hIconSm        = windowIcon;

	// registrando "GameWindow"
	if (!RegisterClassEx(&wndClass))
		return false;

	// criando uma janela baseada na classe "GameWindow" 
	windowHandle = CreateWindowEx(
		NULL,							// estilos extras
		"GameWindow",					// nome da "window class"
		windowTitle.c_str(),			// título da janela
		windowStyle,					// estilo da janela
		windowPosX, windowPosY,			// posição (x,y) inicial
		windowWidth, windowHeight,		// largura e altura da janela
		NULL,							// identificador da janela pai
		NULL,							// identificador do menu
		hInstance,						// identificador da aplicação
		NULL);							// parâmetros de criação

	// Ao usar o modo em janela é preciso levar em conta que as barras 
	// e bordas ocupam espaço na janela. O código abaixo ajusta o tamanho
	// da janela de forma que a área cliente do jogo fique no tamanho 
	// (windowWidth x windowHeight)

	if (windowMode == WINDOWED)
	{
		// retângulo com o tamanho da área cliente desejada
		RECT winRect = {0, 0, windowWidth, windowHeight};

		// ajusta o tamanho do retângulo
		AdjustWindowRectEx(&winRect,
			GetWindowStyle(windowHandle),
			GetMenu(windowHandle) != NULL,
			GetWindowExStyle(windowHandle));

		// atualiza posição da janela
		windowPosX = (GetSystemMetrics(SM_CXSCREEN)/2) - ((winRect.right - winRect.left)/2);
		windowPosY = (GetSystemMetrics(SM_CYSCREEN)/2) - ((winRect.bottom - winRect.top)/2);

		// redimensiona janela com uma chamada a MoveWindow
		MoveWindow(
			windowHandle,                  // identificador da janela
			windowPosX,                    // posição x
			windowPosY,                    // posição y
			winRect.right - winRect.left,  // largura
			winRect.bottom - winRect.top,  // altura
			TRUE);						   // repintar
	}

	// retorna estado da inicialização (bem sucedida ou não)
	return (windowHandle ? true : false);
}

// -------------------------------------------------------------------------------

LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		// pausa/resume jogo mediante ativação/desativação da janela
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE)
			Engine::Resume();
		else
			Engine::Pause();
		break;

	// impede que ALT-F4 feche a janela
	//case WM_SYSKEYDOWN:
	//	if (wParam == VK_F4)
	//		return 0;
	//	break;

		// a janela foi destruida
	case WM_DESTROY: 
		// envia uma mensagem WM_QUIT para encerrar o loop da aplicação
		PostQuitMessage(0);
		return 0;
    }

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// -----------------------------------------------------------------------------
