#ifndef  _STATIC_OBJECT_H_
#define  _STATIC_OBJECT_H_

#include "cocos2d.h"
#include "defs.h"

class StaticObject {
public:
	// Constructor. Note that the node needs to be added to a parent.
	StaticObject(cocos2d::Node* node, cocos2d::Size size, cocos2d::Point pos) :
		_node(node), _size(size), _pos(pos) {
	
		updateNodePosition();
	}

	// Per-frame Update method
	virtual void update() {
		// TODO: should this function stay empty?
		//updateNodePosition();
	}

	// Position revealer. TODO: make a better contract
	const cocos2d::Point& position()
	{
		return _pos;
	}

protected:

	// Set position node to _pos.
	void updateNodePosition() {
		_node->setPosition(cocos2d::Point(_pos.x * defs::SIZE, _pos.y * defs::SIZE));
	}

	cocos2d::Node* _node;
	cocos2d::Size _size;
	cocos2d::Point _pos;


};

#endif  _STATIC_OBJECT_H_