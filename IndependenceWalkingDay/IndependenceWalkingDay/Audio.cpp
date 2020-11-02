/**********************************************************************************
// Audio (Código Fonte)
// 
// Criação:		14 Out 2011
// Atualização:	11 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Classe para reproduzir áudio
//
**********************************************************************************/

#include "Audio.h"
#include "Sound.h"

// ---------------------------------------------------------------------------------

Audio::Audio()
{
	audioEngine = nullptr;
	masterVoice = nullptr;

	// XAudio2 usa a biblioteca COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// cria uma instância da engine XAudio2
	HRESULT hr = XAudio2Create(&audioEngine, 0, XAUDIO2_DEFAULT_PROCESSOR);

	// cria o dispositivo principal de saída de audio
	audioEngine->CreateMasteringVoice(&masterVoice);
}

// ---------------------------------------------------------------------------------

Audio::~Audio()
{
	// deleta todos os sons da coleção
	for (auto i = sounds.begin(); i != sounds.end(); ++i)
	{
		// destroi todas as vozes criadas para este som
		for (uint k = 0; k < i->second->voicesCount; ++k)
			i->second->voices[k]->DestroyVoice();

		// libera o som
		delete i->second;
	}

	// destroi voz mestre
	if (masterVoice) masterVoice->DestroyVoice();

	// libera instância de XAudio2
	if (audioEngine) audioEngine->Release();

	// limpa a coleção de sons
	sounds.clear();

	// XAudio2 usa a biblioteca COM
	CoUninitialize();
}

// ---------------------------------------------------------------------------------

void Audio::Add(uint id, string filename, uint nVoices)
{
	// cria novo som
	Sound * newSound = new Sound(filename, nVoices);

	// cria o número de vozes requisitadas para o som
	for (uint i = 0; i < nVoices; ++i)
		audioEngine->CreateSourceVoice(&newSound->voices[i], (WAVEFORMATEX*)&newSound->soundFormat);

	// insere novo som na coleção
	sounds[id] = newSound;
}

// ---------------------------------------------------------------------------------

void Audio::Play(uint id, bool repeat)
{ 
	Sound * selected = sounds[id];

	// toca áudio em loop ou apenas uma vez
	if (repeat)
		selected->soundBuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	else
		selected->soundBuffer.LoopCount = 0;

	// pega índice da voz corrente
	uint index = selected->currentVoice;

	// limpa voz corrente e inicia reprodução do novo som
	selected->voices[index]->Stop();
	selected->voices[index]->FlushSourceBuffers();
	selected->voices[index]->SetVolume(selected->soundVolume);
	selected->voices[index]->SubmitSourceBuffer(&selected->soundBuffer);
	selected->voices[index]->Start();

	// seleciona outra voz para reprodução do próximo som
	selected->currentVoice = (index + 1) % selected->voicesCount;
}

// ---------------------------------------------------------------------------------

void Audio::Stop(uint id)
{
	Sound * selected = sounds[id];

	for (uint i = 0; i < selected->voicesCount; ++i)
		selected->voices[i]->Stop();
}

// ---------------------------------------------------------------------------------

void Audio::Volume(uint id, float level)
{
	if (level < 0)
		level = 0;

	if (level > XAUDIO2_MAX_VOLUME_LEVEL)
		level = XAUDIO2_MAX_VOLUME_LEVEL;

	Sound * selected = sounds[id];
	selected->soundVolume = level;
	selected->voices[selected->currentVoice]->SetVolume(level);
}

// ---------------------------------------------------------------------------------

void Audio::Frequency(uint id, float level)
{
	if (level < XAUDIO2_MIN_FREQ_RATIO)
		level = XAUDIO2_MIN_FREQ_RATIO;

	Sound * selected = sounds[id];
	selected->soundFrequency = level;
	selected->voices[selected->currentVoice]->SetFrequencyRatio(level);
}

// ---------------------------------------------------------------------------------

