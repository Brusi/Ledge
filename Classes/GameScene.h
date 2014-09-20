#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameTile.h"
#include "SparseMatrix.h"
#include "Control.h"
#include "ActiveObject.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	// Adds a tile to the level.
	void addTile(IJ ij, GameTile::Type type, int time);
	// Removes a tile from the level
	void removeTile(IJ ij);

	void onMouseDown(cocos2d::Event *event);

	// Overrides update
	void update(float dt) override;


	// Level matrix
	SparseMatrix<GameTile> _level;

	// Control
	std::unique_ptr<Control> _control;

	// Player object TODO: change to player object
	std::unique_ptr<ActiveObject> _player;

};

#endif // __GAME_SCENE_H__
