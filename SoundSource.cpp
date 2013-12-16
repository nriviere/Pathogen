#include "SoundSource.h"
#include "al.h"
#include "alc.h"

SoundSource::SoundSource(unsigned int bufferID)
{
	this->bufferID = bufferID;
	soundEngineIndex = UINT_MAX;
	alGenSources(1,&sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);
}


SoundSource::~SoundSource()
{
	alSourcei(sourceID, AL_BUFFER, 0);
	alDeleteSources(1, &sourceID);
}



void SoundSource::setSoundEngineIndex(unsigned int index)
{
	soundEngineIndex = index;
}

unsigned int SoundSource::getSoundEngineIndex()
{
	return soundEngineIndex;
}

void SoundSource::play()
{
	alSourcePlay(sourceID);
}

bool SoundSource::isPlaying()
{
	ALint status;
	alGetSourcei(sourceID, AL_SOURCE_STATE, &status);
	return status == AL_PLAYING;
}