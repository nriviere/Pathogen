#pragma once
#include <iostream>
#include "al.h"
#include "alc.h"
#include "sndfile.h"
#include "SoundSource.h"
#include "Indexer.h"

class MyEngine;
class SoundEngine
{
public:
	static const unsigned int SOUND_BUFFERS_COUNT = 2;
	static const unsigned int MAX_SOUND_SOURCE_COUNT = 1000;
	static const unsigned int TEST_SOUND_ID = 0;
	static const unsigned int EXPLOSION_SOUND_ID = 1;
	SoundEngine(MyEngine *engine = NULL);
	~SoundEngine();

	bool init();
	void shutdown();

	void addSource(SoundSource *source);
	void removeSource(SoundSource *source);

	unsigned int loadSound(const char *filename);
	void playSound(unsigned int bufferIndex);
	void update();

protected:
	MyEngine *engine;
	ALCdevice* device;
	ALCcontext* context;
	unsigned int soundBuffers[SOUND_BUFFERS_COUNT];
	SoundSource *soundSources[MAX_SOUND_SOURCE_COUNT];
	Indexer *soundSourceIndexer;
};

