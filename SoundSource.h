#pragma once
#include <iostream>

class SoundSource
{
protected:
	unsigned int bufferID,sourceID;
	unsigned int soundEngineIndex;
public:
	SoundSource(unsigned int bufferID = UINT_MAX);
	~SoundSource();

	void setSoundEngineIndex(unsigned int index);
	unsigned int getSoundEngineIndex();
	void play();
	bool isPlaying();
};

