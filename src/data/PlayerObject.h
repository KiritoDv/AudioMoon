#pragma once

enum PlayerStatus {
	FREE, PLAYING, DEAD
};

struct PlayerObject{
	unsigned int source;
	PlayerStatus status;
};