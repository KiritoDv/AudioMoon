#pragma once

#include "AudioFile.h"

struct AudioBuffer {
	int bufferSize;
	double* bufferData;
};

struct AudioObject {
		
	AudioFile<double> data;
	AudioBuffer buffer;
	bool loop;

};
