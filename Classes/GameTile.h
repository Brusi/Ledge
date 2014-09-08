#ifndef __GAME_TILE_H__
#define __GAME_TILE_H__

#include "cocos2d.h"
#include "IJ.h"


class GameTile
{
public:
	
	// Enumerable of possible tile types
	enum Type { EMPTY, SOLID };

	GameTile() : _type(EMPTY), _time(0) {}
	GameTile(IJ ij, Type type, int time, cocos2d::Node* parent) : _type(type), _time(time) {
		_node = cocos2d::Sprite::create("tile.png");
		_node->setScale(defs::SCALE);
		//_node->setAnchorPoint(cocos2d::Point(5,5));
		//_node->setAnchorPoint(cocos2d::Point(defs::RADIUS, defs::RADIUS));
		
		_node->setPosition(ij.toPoint());
		parent->addChild(_node);
	}

	// Deletes the tile node.
	void destroy() {
		_node->getParent()->removeChild(_node);
		_node = NULL;
	}

	Type type() const {
		return _type;
	}
	int time() const {
		return _time;
	}

    
private:
	Type _type;
	int _time;
	cocos2d::Node* _node;
	
};

#endif // GAME_TILE
