#ifndef  DEFS_H_
#define  DEFS_H_

namespace defs {
	// Screen and resolution
	const int FULL_WIDTH = 1920; // Full HD width

	const float SCALE = 0.5;
	
	const int SCREEN_WIDTH = 1920 * SCALE;
	const int SCREEN_HEIGHT = SCREEN_WIDTH * 9 / 16;
	
	// Standard tile size
	const int SIZE = SCREEN_WIDTH / 32;
	const int RADIUS = SIZE / 2;

	// Player constants
	const float GRAVITY = 0.015;
	const float JUMP_SPEED = 0.5;
	const float MOVE_ACC = 0.02;

	const float FRICTION = 0.04;
}






#endif // DEFS_H_
