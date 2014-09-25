#ifndef  _PLAYER_H_
#define  _PLAYER_H_

#include "cocos2d.h"
#include "defs.h"

#include <memory>

#include "ActiveObject.h"
#include "Control.h"
#include "GameTile.h"
#include "SparseMatrix.h"

class Player : public ActiveObject {
public:
	// Constructor. Note that the node needs to be added to a parent.
	Player(cocos2d::Node* node, cocos2d::Size size, cocos2d::Point pos,
		Control* control,
		SparseMatrix<GameTile>* level) :
		ActiveObject(node, size, pos), _control(control), _level(level) {

		_isOnFloor = false;
	}

	static Player* create(cocos2d::Node* parent, const IJ& initIJ);

	// Per-frame Update method
	virtual void update() override;

private:

	// Check a collision point
	bool checkCollisionPoint(const cocos2d::Point& p);
	
	// Check collisions
	void checkFloor();
	void checkWall();

	
	
	// The control to which the player will listen. Owned by player.
	Control* _control;
	// The level to which the player will listen.
	SparseMatrix<GameTile>* _level;

	// Flag which indicates whether the player is standing on the floor
	bool _isOnFloor;



	// Collision Points
	static const cocos2d::Point _floor_left;
	static const cocos2d::Point _floor_right;

	static const cocos2d::Point _left_top;
	static const cocos2d::Point _left_bottom;

	static const cocos2d::Point _right_top;
	static const cocos2d::Point _right_bottom;


};

#endif  _PLAYER_H_