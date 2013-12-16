#include "SoundEngine.h"



SoundEngine::SoundEngine(MyEngine *engine)
{
	this->engine = engine;
	soundSourceIndexer = new Indexer(MAX_SOUND_SOURCE_COUNT);
	for (int i = 0; i < MAX_SOUND_SOURCE_COUNT; i++)
	{
		soundSources[i] = NULL;
	}
}


SoundEngine::~SoundEngine()
{
	for (int i = 0; i < MAX_SOUND_SOURCE_COUNT; i++)
	{
		if (soundSources[i] != NULL)
		{
			removeSource(soundSources[i]);
		}
	}
	delete soundSourceIndexer;
}

bool SoundEngine::init()
{
	device = alcOpenDevice(NULL);
	if (!device)
		return false;

	// Création du contexte
	context = alcCreateContext(device, NULL);
	if (!context)
		return false;

	// Activation du contexte
	if (!alcMakeContextCurrent(context))
		return false;

	soundBuffers[TEST_SOUND_ID] = loadSound("assets/sounds/test1.wav");
	soundBuffers[EXPLOSION_SOUND_ID] = loadSound("assets/sounds/explosion.wav");
	return true;
}

void SoundEngine::shutdown()
{
	alcMakeContextCurrent(NULL);

	// Destruction du contexte
	alcDestroyContext(context);

	// Fermeture du device
	alcCloseDevice(device);
}

void SoundEngine::addSource(SoundSource *source)
{
	unsigned int index = soundSourceIndexer->getNextIndex();
	if (index != UINT_MAX)
	{
		source->setSoundEngineIndex(index);
		soundSources[index] = source;
	}
}
void SoundEngine::removeSource(SoundSource *source)
{
	unsigned int index = source->getSoundEngineIndex();
	if (index < MAX_SOUND_SOURCE_COUNT)
	{
		delete soundSources[index];
		soundSources[index] = NULL;
		soundSourceIndexer->releaseIndex(index);
	}
}

unsigned int SoundEngine::loadSound(const char *filename)
{
	SF_INFO FileInfos;
	SNDFILE* File = sf_open(filename, SFM_READ, &FileInfos);
	if (!File)
		return 0;
	// Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
	ALsizei NbSamples = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
	ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

	// Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
	ALshort * Samples = new ALshort[NbSamples];
	if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
		return 0;
	// Fermeture du fichier
	sf_close(File);

	// Détermination du format en fonction du nombre de canaux
	ALenum Format;
	switch (FileInfos.channels)
	{
		case 1:  Format = AL_FORMAT_MONO16;   break;
		case 2:  Format = AL_FORMAT_STEREO16; break;
		default: return 0;
	}
	// Création du tampon OpenAL
	ALuint Buffer;
	alGenBuffers(1, &Buffer);

	// Remplissage avec les échantillons lus
	alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

	// Vérification des erreurs
	if (alGetError() != AL_NO_ERROR)
		return 0;

	return Buffer;
}

void SoundEngine::playSound(unsigned int bufferIndex)
{
	SoundSource *source = new SoundSource(soundBuffers[bufferIndex]);
	addSource(source);
	source->play();
}

void SoundEngine::update()
{
	for (int i = 0; i < MAX_SOUND_SOURCE_COUNT; i++)
	{
		if (soundSources[i] != NULL)
		{
			if (!soundSources[i]->isPlaying())
			{
				removeSource(soundSources[i]);
			}
		}
	}
}