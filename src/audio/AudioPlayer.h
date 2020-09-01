#pragma once
#include <AL/alext.h>
#include <map>
#include "data/AudioObject.h"
#include "data/PlayerObject.h"
#include <cstring>

#define SOURCE_POOL_SIZE 150;

enum PlayerType {
	BACKGROUND, POSITIONED
};

struct Vec3f {
	float x = 0;
	float y = 0;
	float z = 0;
};

class AudioPlayer {	
	public:
		AudioPlayer();
		~AudioPlayer();
		void initDevice();
		void preloadSound(int pool_id, const char * path);
		void playBackgroundSequence(int pool_id, float pitch, float gain);
		void cleanupBuffers();
	private:
		std::vector<PlayerObject *> sourcePool;
		std::vector<ALuint> playingPool;
		std::map<int, AudioObject *> soundPool;
		const ALCchar* defaultDeviceName;
		ALCdevice* device;
		ALCcontext* context;
		void bindDefaultDevice();
		void initSourcePool();
		PlayerObject * getFreeSource();
		void playSequence(AudioObject * object, PlayerObject * source, float pitch, float gain, ALfloat* origin, Vec3f listenerPos, Vec3f listenerVel, Vec3f sourcePos, Vec3f sourceVel);

};

