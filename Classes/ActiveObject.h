#ifndef  _ACTIVE_OBJECT_H_
#define  _ACTIVE_OBJECT_H_

#include "cocos2d.h"
#include "defs.h"
#include "StaticObject.h"

class ActiveObject : public StaticObject {
public:
	// Constructor. Note that the node needs to be added to a parent.
	ActiveObject(cocos2d::Node* node, cocos2d::Size size, cocos2d::Point pos) :
		StaticObject(node, size, pos) {
	}
	
	virtual void update() override {
		updatePos();
		updateNodePosition();
	}

protected:

	// Updates position according to velocity
	void updatePos() {
		_pos += _vel;
	}

	cocos2d::Point _vel;

};

#endif  _ACTIVE_OBJECT_H_