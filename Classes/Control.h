#ifndef  _CONTROL_H_
#define  _CONTROL_H_

/*
 * Abstract interface for any game controllers - Keyboard, Gamepad, Playback etc.
 */

class Control {
public:
	enum Key {
		UP, DOWN, LEFT, RIGHT, JUMP
	};

	virtual bool isKeyPressed(Key key) const = 0;
	
};

#endif  _CONTROL_H_