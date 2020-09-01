#include "AudioPlayer.h"

#include <iostream>

void TEST_ERROR(const char * _msg) {
	ALint error = alGetError();
	if (error != AL_NO_ERROR) {				
		fprintf(stderr, "Error: %s Code: %d\n", _msg, error);
		return;
	}
}

AudioPlayer::AudioPlayer() {

}

AudioPlayer::~AudioPlayer() {	
	/* exit context */
	for (auto source : sourcePool){
		alDeleteSources(1, &source->source);
	}
	
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void AudioPlayer::initDevice() {
	AudioPlayer::bindDefaultDevice();

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		fprintf(stderr, "failed to make default context\n");
	}

	alGetError();

	//initSourcePool();
}

void AudioPlayer::preloadSound(int pool_id, const char * path) {

	AudioFile<double> tmp;
	tmp.shouldLogErrorsToConsole(false);
	tmp.load(path);
	tmp.printSummary();

    int numChannels = tmp.getNumChannels();
    int numSamples = tmp.getNumSamplesPerChannel();

	int bufferSize = numSamples * numChannels;
	double* bufferData = (double*)malloc(sizeof(double) * bufferSize);

	int b = 0;

	for (int c = 0; c < numChannels; c++) {
		for (int i = 0; i < tmp.getNumSamplesPerChannel(); i++) {
			bufferData[b++] = tmp.samples[c][i];
		}
	}

	AudioBuffer buffer = { static_cast<int>(sizeof(double) * bufferSize), bufferData };
	AudioObject* obj = new AudioObject({tmp, buffer, false});
	
	soundPool.insert(std::pair<int, AudioObject *>(pool_id, obj));
}

void AudioPlayer::initSourcePool(){
	int size = SOURCE_POOL_SIZE;

	for (int id = 0; id < size; id++) {
		ALuint source;
		alGenSources((ALuint)1, &source);
		sourcePool.push_back(new PlayerObject({ source, PlayerStatus::FREE }));
	}
}

PlayerObject * AudioPlayer::getFreeSource() {	
	PlayerObject* tmp;

	ALuint source;
	alGenSources((ALuint)1, &source);
	sourcePool.push_back(tmp = new PlayerObject({ source, PlayerStatus::FREE }));

	return tmp;
}

void AudioPlayer::playBackgroundSequence(int pool_id, float pitch, float gain) {

	PlayerObject * obj = AudioPlayer::getFreeSource();
	printf("Using ID: %d\n", obj->source);

	ALfloat origin[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	AudioPlayer::playSequence(soundPool[pool_id], obj, pitch, gain, origin, {}, {}, {}, {});
}


void AudioPlayer::bindDefaultDevice() {
	if (!defaultDeviceName)
		defaultDeviceName = alcGetString(NULL, ALC_DEFAULT_ALL_DEVICES_SPECIFIER);

	device = alcOpenDevice(defaultDeviceName);
	if (!device) {
		fprintf(stderr, "Unable to open default device\n");
	}

	fprintf(stdout, "Device: %s\n", alcGetString(device, ALC_DEVICE_SPECIFIER));
}

void AudioPlayer::playSequence(AudioObject * object, PlayerObject * source, float pitch, float gain, ALfloat* origin, Vec3f listenerPos, Vec3f listenerVel, Vec3f sourcePos, Vec3f sourceVel) {
	ALuint buffer;
	ALint source_state;

	if (source->status == PlayerStatus::PLAYING) return;

	source->status = PlayerStatus::PLAYING;	

	alListener3f(AL_POSITION, listenerPos.x, listenerPos.y, listenerPos.z);
	alListener3f(AL_VELOCITY, listenerVel.x, listenerVel.y, listenerVel.z);
	alListenerfv(AL_ORIENTATION, origin);
	
	alSourcef(source->source, AL_PITCH, pitch);
	alSourcef(source->source, AL_GAIN, gain);
	alSource3f(source->source, AL_POSITION, sourcePos.x, sourcePos.y, sourcePos.z);
	alSource3f(source->source, AL_VELOCITY, sourceVel.x, sourceVel.y, sourceVel.z);
	alSourcei(source->source, AL_LOOPING, false);

	alGenBuffers((ALuint)1, &buffer);

	AudioFile<double> data = object -> data;
	AudioBuffer a_buffer = object->buffer;

	alBufferData(buffer, AL_FORMAT_STEREO_DOUBLE_EXT, a_buffer.bufferData, a_buffer.bufferSize, data.getSampleRate());
	TEST_ERROR("buffer copy");
	alSourcei(source->source, AL_BUFFER, buffer);
	TEST_ERROR("buffer binding");
		
	alSourcePlay(source->source);
	TEST_ERROR("source playing");
	
	alGetSourcei(source->source, AL_SOURCE_STATE, &source_state);

	TEST_ERROR("source state get");

	//printf("%d - %d\n", source_state, AL_PLAYING);
	
	playingPool.push_back(buffer);

	source->status = FREE;
	//alDeleteBuffers(1, &buffer);
}

void AudioPlayer::cleanupBuffers() {
	for (auto source : playingPool) {
		
	}
}