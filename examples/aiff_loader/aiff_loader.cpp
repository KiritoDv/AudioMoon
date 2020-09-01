#include <audio/AudioPlayer.h>

#define Baka 1;
#define Example 2;

int main(int argc, char** argv) {

	AudioPlayer a;
	a.initDevice();

	a.preloadSound(1, R"(C:\Users\Ruine\Music\b\example.wav)");
    a.playBackgroundSequence(1, 0.5f, 0.5f);

	a.cleanupBuffers();

	while (true){}

	return 0;
}