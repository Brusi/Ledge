#include "Player.h"

#include <math.h>

#include "defs.h"

USING_NS_CC;

// Initialize collision points
const Point Player::_floor_left(-0.33f, -1.0f);
const Point Player::_floor_right(0.33f, -1.0f);

const Point Player::_left_top(-0.5f, 0.75f);
const Point Player::_left_bottom(-0.5f, -0.75f);

const Point Player::_right_top(0.5f, 0.75f);;
const Point Player::_right_bottom(0.5f, -0.75f);;

void Player::update()
{
	// Check jump
	if (_isOnFloor) {
		if (_control->isKeyPressed(Control::UP)) {
			_vel.y = defs::JUMP_SPEED;
			_isOnFloor = false;
		}
	} else {
		// If on air, then gravity can be controlled
		if (_control->isKeyPressed(Control::UP)) {
			_vel.y -= defs::GRAVITY;
		}
		else if (_control->isKeyPressed(Control::DOWN)) {
			_vel.y -= defs::GRAVITY * 4;
		} else {
			_vel.y -= defs::GRAVITY * 2;
		}
 	}

	
	// Check move to the sides
	if (_control->isKeyPressed(Control::RIGHT) && !_control->isKeyPressed(Control::LEFT)) {
		_vel.x += defs::MOVE_ACC;
	} else if (_control->isKeyPressed(Control::LEFT)) {
		_vel.x -= defs::MOVE_ACC;
	} else {
		if (_isOnFloor) {
			// Immediately stop if on floor
			_vel.x = 0;
		}
	}

	// Apply friction
	_vel.x = _vel.x * (1.0 - defs::FRICTION);
	_vel.y = _vel.y * (1.0 - defs::FRICTION);
	
	updatePos();
	
	checkFloor();
	checkWall();

	// DEBUG: wrap
	if (_pos.x > defs::SCREEN_WIDTH / defs::SIZE) {
		_pos.x -= defs::SCREEN_WIDTH / defs::SIZE;
	}
	else if (_pos.x < 0) {
		_pos.x += defs::SCREEN_WIDTH / defs::SIZE;
	}

	if (_pos.y > defs::SCREEN_HEIGHT / defs::SIZE) {
		_pos.y -= defs::SCREEN_HEIGHT / defs::SIZE;
	}
	else if (_pos.y < 0) {
		_pos.y += defs::SCREEN_HEIGHT / defs::SIZE;
	}

	updateNodePosition();
}

bool Player::checkCollisionPoint(const Point& collision_point)
{
	Point toCheck = _pos + collision_point;
	IJ ij(toCheck.x, toCheck.y); // Should round-down the values

	//CCLOG("Checking point i: %d, j: %d . Type is %d", ij.i, ij.j, GameTile::SOLID);
	if (_level->getAt(ij).type() == GameTile::SOLID) {
		return true;
	}
	return false;
}

void Player::checkFloor()
{
	if (checkCollisionPoint(_floor_left) || checkCollisionPoint(_floor_right)) {
		_pos.y = ceil(_pos.y);
		_isOnFloor = true;
		_vel.y = 0;
	} else {
		_isOnFloor = false;
	}
}

void Player::checkWall()
{
	if (checkCollisionPoint(_left_top) || checkCollisionPoint(_left_bottom)) {
		_pos.x = ceil(_pos.x) - 0.5f;
		_vel.x = 0;
		// TODO habg on wall?
	}
	else {
		//_isOnFloor = false;
	}

	if (checkCollisionPoint(_right_top) || checkCollisionPoint(_right_bottom)) {
		_pos.x = floor(_pos.x) + 0.5f;
		_vel.x = 0;
		// TODO habg on wall?
	}
}
