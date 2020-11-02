/**********************************************************************************
// Joystick (Arquivo de Cabe�alho)
// 
// Cria��o:		09 Nov 2011
// Atualiza��o:	25 Jun 2014
// Compilador:	Visual C++ 12
//
// Descri��o:	Gerencia entrada pelo joystick
//
**********************************************************************************/

#ifndef _DESENVJOGOS_JOYSTICK_H_
#define _DESENVJOGOS_JOYSTICK_H_

// ---------------------------------------------------------------------------------

#define INITGUID								// for�a inclus�o dos GUIDs do DirectX
#define DIRECTINPUT_VERSION 0x0800				// usa vers�o 8 do DirectInput

// ---------------------------------------------------------------------------------

#include <dinput.h>
#include <list>
#include <string>
using std::list;
using std::string;

// ---------------------------------------------------------------------------------

// eixos do joystick
enum JoyAxis {
	JoyAxisX, 
	JoyAxisY, 
	JoyAxisZ, 
	JoyAxisRX, 
	JoyAxisRY, 
	JoyAxisRZ  };

// informa��es do joystick
struct JoyInfo {
	GUID   guid;
	string name; };

// objetos do joystick (bot�es e eixos)
struct JoyObjs {
	GUID   guid;
	DWORD  type;
	string name; };

// ---------------------------------------------------------------------------------

class Joystick
{
private:
	LPDIRECTINPUT8 dinput;						// objeto direct input
	LPDIRECTINPUTDEVICE8 joyDev;				// dispositivo do joystick
	DIJOYSTATE joyState;						// estado do joystick
	bool joyCtrl[10];							// controle da libera��o de bot�es

	list<JoyInfo> joysticks;					// lista dos dispositivos tipo joystick
	list<JoyObjs> joystickObjects;				// lista de bot�es e eixos para o joystick selecionado
	list<JoyInfo>::const_iterator selected;		// aponta para o joystick selecionado	

public:
	Joystick();									// construtor
	~Joystick();								// destrutor

	bool Initialize();							// inicializa joystick		
	bool GetState();							// atualiza estado do joystick
	bool ButtonDown(int button);				// verifica se um bot�o do joystick est� pressionado
	bool ButtonUp(int button);					// verifica se um bot�o do joystick est� liberado
	bool ButtonCtrl(int button);				// registra novo pressionamento somente ap�s libera��o
	long Axis(int axis); 						// retorna o movimento de um eixo do joystick
	long Slider(int slider);					// retorna movimento do slider
	long Pov(int pov);							// retorna o movimento do D-pad
	bool SelectNext();							// seleciona o pr�ximo joystick
	bool SelectPrev();							// seleciona o joystick anterior 
	const string * Name();						// retorna o nome do joystick selecionado
	list<JoyObjs>&	Objects();					// retorna lista de bot�es e eixos do joystick 
};

// -------------------------------------------------------------------------------

// fun��es membro InLine

// verifica se o bot�o do joystick est� pressionado
inline bool Joystick::ButtonDown(int button)
{ return joyState.rgbButtons[button] && 0x80; }

// verifica se o bot�o do joystick est� pressionado
inline bool Joystick::ButtonUp(int button)
{ return !(joyState.rgbButtons[button] && 0x80); }

// retorna o nome do joystick selecionado
inline const string * Joystick::Name() 
{ return &(*selected).name; }

// retorna lista de bot�es e eixos do joystick 
inline list<JoyObjs>& Joystick::Objects() 
{ return joystickObjects;}

// ---------------------------------------------------------------------------------

// fun��o callback que enumera os joysticks
BOOL CALLBACK JoystickEnumerate(LPCDIDEVICEINSTANCE lpDDi, LPVOID data);

// fun��o callback que enumera os bot�es e eixos do joystick
BOOL CALLBACK JoystickEnumObjects(LPCDIDEVICEOBJECTINSTANCE lpDIdoi, LPVOID data);

// ---------------------------------------------------------------------------------

#endif