/**********************************************************************************
// Joystick (Código Fonte)
// 
// Criação:		09 Nov 2011
// Atualização:	25 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Gerencia entrada pelo joystick
//
**********************************************************************************/

// ---------------------------------------------------------------------------------

#include "Joystick.h"
#include "Engine.h"

// ---------------------------------------------------------------------------------

Joystick::Joystick()
{
	dinput      = nullptr;
	joyDev      = nullptr;

	ZeroMemory(&joyState, sizeof(joyState));
	ZeroMemory(&joyCtrl, sizeof(joyCtrl));

	// cria o objeto direct input
	DirectInput8Create(
		GetModuleHandle(NULL),		// identificador da janela
		DIRECTINPUT_VERSION,		// versão do direct input
		IID_IDirectInput8,			// identificador da interface
		(void **) &dinput,			// objeto direct input
		NULL);						// sempre nulo

	// busca por dispositivos conectados usando a função callback JoystickEnumerate
	dinput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,		// procure apenas joysticks
		JoystickEnumerate,			// função de enumeração
		&joysticks,					// endereço da lista de joysticks
		DIEDFL_ATTACHEDONLY);		// apenas dispositivos conectados

	// seleciona e inicializa o primeiro joystick encontrado
	selected = joysticks.begin();
}

// ---------------------------------------------------------------------------------

Joystick::~Joystick()
{
	// libera o dispositivo joystick
	if (joyDev)
		joyDev->Unacquire();

	// apaga o objeto joystick
	if (joyDev)
		joyDev->Release();

	// apaga o objeto direct input
	if (dinput)
		dinput->Release();
}

// ---------------------------------------------------------------------------------

bool Joystick::Initialize()
{
	// se o direct input não foi inicializado saia
	if (!dinput)
		return false;

	// libera o joystick selecionado
	if (joyDev)
		joyDev->Unacquire();

	// apaga o objeto do jostick selecionado
	if (joyDev)
		joyDev->Release();

	// verifica se existe algum joystick no sistema
	if (joysticks.empty())
		return false;

	// cria o dispositivo joystick 
	if (FAILED(dinput->CreateDevice(selected->guid, &joyDev, NULL)))
		return false;

	// seleciona o nível de cooperação para o joystick
	if (FAILED(joyDev->SetCooperativeLevel(Engine::window->Id(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		return false;

	// seleciona o formato de dados
	if (FAILED(joyDev->SetDataFormat(&c_dfDIJoystick)))
		return false;

	// enumera os objetos do joystick selecionado (botões e eixos)
	joystickObjects.clear();
    if(FAILED(joyDev->EnumObjects(JoystickEnumObjects, &joystickObjects, DIDFT_ALL)))
		return false;
	
    // ajusta a faixa de movimento e a zona morta de um eixo
    DIPROPRANGE joyAxisRange; 
	DIPROPDWORD deadZone;

	for (auto i = joystickObjects.begin(); i != joystickObjects.end(); ++i)
	{
		// se o objeto é um eixo
		if (i->type & DIDFT_AXIS)
		{
			// define faixa do eixo
			joyAxisRange.diph.dwSize       = sizeof(DIPROPRANGE); 
			joyAxisRange.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
			joyAxisRange.diph.dwHow        = DIPH_BYID; 
			joyAxisRange.diph.dwObj        = i->type;
			joyAxisRange.lMin              = -1000; 
			joyAxisRange.lMax              = +1000; 
    
			// aplica a faixa no eixo
			if (FAILED(joyDev->SetProperty(DIPROP_RANGE, &joyAxisRange.diph))) 
				return false;

			// define a zona morta
			deadZone.diph.dwSize       = sizeof(deadZone);
			deadZone.diph.dwHeaderSize = sizeof(deadZone.diph);
			deadZone.diph.dwHow        = DIPH_BYID;
			deadZone.diph.dwObj        = i->type;
			deadZone.dwData            = 2000;

			// aplica a zona morta no eixo
			if (FAILED(joyDev->SetProperty(DIPROP_DEADZONE, &deadZone.diph)))
				return false;
		}
	}

	// requisita acesso ao joystick
	if(FAILED(joyDev->Acquire()))
		return false;

	// inicialização bem sucedida
	return true;
}

// ---------------------------------------------------------------------------------

bool Joystick::GetState()
{
	
	// é preciso usar Poll() antes de ler o estado do joystick
	// porque alguns drivers de joystick não atualizam seu estado
	// interno automaticamente

	// sempre atualiza o estado interno do joystick antes ler seu estado
	if (FAILED(joyDev->Poll()))
		return false;

	// lê o estado do joystick
	HRESULT result = joyDev->GetDeviceState(sizeof(DIJOYSTATE), (LPVOID) &joyState); 

	// aconteceu alguma falha na leitura
	if(FAILED (result))
	{
		if (result == DIERR_NOTACQUIRED || result == DIERR_INPUTLOST)
		{
			// libera o dispositivo joystick
			joyDev->Unacquire();

			// tenta re-capturar o joystick
			joyDev->Acquire();
		}
		else
		{
			return false;
		}	
	}
	
	// leitura bem sucedida
	return true;
}

// ---------------------------------------------------------------------------------

bool Joystick::ButtonCtrl(int button)
{
	if (joyCtrl[button])
	{
		if (ButtonDown(button))
		{
			joyCtrl[button] = false;
			return true;
		}
	} 
	else if (ButtonUp(button))
	{
		joyCtrl[button] = true;
	}

	return false;
}

// ---------------------------------------------------------------------------------

long Joystick::Axis(int axis)
{ 
	switch (axis)
	{
	case JoyAxisX:
		return joyState.lX; 
	case JoyAxisY:
		return joyState.lY; 
	case JoyAxisZ:
		return joyState.lZ;
	case JoyAxisRX:
		return joyState.lRx; 
	case JoyAxisRY:
		return joyState.lRy; 
	case JoyAxisRZ:
		return joyState.lRz;

	default:
		return 0;
	}	
}

long Joystick::Slider(int slider)
{
	if (slider < 2)
		return joyState.rglSlider[slider];
	else
		return 0;
}

// ---------------------------------------------------------------------------------

long Joystick::Pov(int pov)
{
	if (pov < 4)
		return joyState.rgdwPOV[pov];
	else 
		return 0;
}

// ---------------------------------------------------------------------------------

bool Joystick::SelectNext()
{
	++selected;

	if (selected == joysticks.end())
		selected = joysticks.begin();		

	// inicializa joystick selecionado
	if (Initialize())
		return true;
	else
		return false;
}

// ---------------------------------------------------------------------------------

bool Joystick::SelectPrev()
{
	if (selected == joysticks.begin())
		selected = joysticks.end();

	--selected;
	
	// inicializa joystick selecionado
	if (Initialize())
		return true;
	else
		return false;
}

// ---------------------------------------------------------------------------------

BOOL CALLBACK JoystickEnumerate(LPCDIDEVICEINSTANCE lpDDi, LPVOID data)
{
	// registro que guarda nome e GUID do joystick 
	JoyInfo joy;

	// copia identificador do joystick
	joy.guid = lpDDi->guidInstance;

	// copia nome do joystick
	joy.name = lpDDi->tszInstanceName;

	// push joystick into the list
	((list<JoyInfo>*) data)->push_back(joy);

	// continua enumeração até o fim
	return DIENUM_CONTINUE;
}

// ---------------------------------------------------------------------------------

BOOL CALLBACK JoystickEnumObjects(LPCDIDEVICEOBJECTINSTANCE lpDIdoi, LPVOID data)
{
	// registro que guarda nome, identificador e tipo dos objetos do joystick 
	// (botões, eixos, povs e sliders)
	JoyObjs button;

	// copia o identificador, tipo e nome do objeto
	button.guid = lpDIdoi->guidType;
	button.type = lpDIdoi->dwType;
	button.name = lpDIdoi->tszName;
	
	// se o tipo do objeto é conhecido, insere-o na lista de objetos do joystick
	if (lpDIdoi->guidType != GUID_Unknown)
		((list<JoyObjs>*) data)->push_back(button);

	// continua enumeração até o fim
	return DIENUM_CONTINUE;
}

// ---------------------------------------------------------------------------------