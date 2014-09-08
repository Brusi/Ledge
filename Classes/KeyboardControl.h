#ifndef  _KEYBOARD_CONTROL_H_
#define  _KEYBOARD_CONTROL_H_

#include "Control.h"

#include "cocos2d.h"
#include <set>


/*
 * Keyboard Control
 */


class KeyboardControl : public Control {
public:

	// Constructor. Gets the node to listen to.
	KeyboardControl::KeyboardControl(cocos2d::Node* node);

	virtual bool isKeyPressed(Key key) const;

private:
	std::set<Key> _pressed;
	cocos2d::EventListenerKeyboard* _listener;
};


#endif  _KEYBOARD_CONTROL_H_

