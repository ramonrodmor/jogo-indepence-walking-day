/**********************************************************************************
// Sound (Arquivo de Cabeçalho)
// 
// Criação:		14 Out 2011
// Atualização:	11 Jun 2014
// Compilador:	Visual C++ 12
//
// Descrição:	Representa um som no formato WAVE
//
**********************************************************************************/

#ifndef _DESENVJOGOS_SOUND_H_
#define _DESENVJOGOS_SOUND_H_

// ---------------------------------------------------------------------------------

#include "Types.h"
#include <string>										
using std::string;

// include XAudio2 API
// Windows 8 
#include <xaudio2.h> 
#pragma comment(lib,"xaudio2.lib") 

// include XAudio2 API
// Windows 7 64 bits
//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\XAudio2.h> 

// include XAudio2 API
// Windows 7 32 bits 
//#include <C:\Program Files\Microsoft DirectX SDK (June 2010)\Include\XAudio2.h> 

// ---------------------------------------------------------------------------------

class Sound
{
private:
	WAVEFORMATEXTENSIBLE soundFormat;					// formato do arquivo .wav
	XAUDIO2_BUFFER       soundBuffer;					// buffer com os dados do som
	float                soundVolume;					// volume do som
	float				 soundFrequency;				// freqüência do som

	uint				voicesCount;					// número de vozes para este som
	uint				currentVoice;					// voz selecionada
	IXAudio2SourceVoice  ** voices;						// vetor de ponteiros para vozes

	HRESULT FindChunk(HANDLE hFile, 
		              DWORD fourcc, 
					  DWORD & dwChunkSize, 
					  DWORD & dwChunkDataPosition);		// localiza blocos no arquivo RIFF

	HRESULT ReadChunkData(HANDLE hFile, 
		                  void * buffer, 
						  DWORD buffersize, 
						  DWORD bufferoffset);			// lê blocos do arquivo para um buffer

	friend class Audio;

public:
	Sound(string fileName, uint nVoices);				// construtor
	~Sound();											// destrutor
};

// ---------------------------------------------------------------------------------


#endif