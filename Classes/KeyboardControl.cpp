#include "KeyboardControl.h"

USING_NS_CC;

namespace {
	//	Converts keyboard keycode to Control::Key
	Control::Key keycodeToKey(EventKeyboard::KeyCode keyCode)
	{
		switch (keyCode) {
			case EventKeyboard::KeyCode::KEY_UP_ARROW: return Control::UP;
			case EventKeyboard::KeyCode::KEY_DOWN_ARROW: return Control::DOWN;
			case EventKeyboard::KeyCode::KEY_LEFT_ARROW: return Control::LEFT;
			case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: return Control::RIGHT;
			case EventKeyboard::KeyCode::KEY_SPACE: return Control::JUMP;
		}
	}
}

KeyboardControl::KeyboardControl(Node* node)
{
	_listener = EventListenerKeyboard::create();
	_listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		// Add key to _pressed
		Key key = keycodeToKey(keyCode);
		_pressed.insert(key);
	};
	
	_listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		// Remove key from _pressed
		Key key = keycodeToKey(keyCode);
		if (_pressed.find(key) != _pressed.end()) {
			_pressed.erase(key);
		}
	};

	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, node);
}

bool KeyboardControl::isKeyPressed(Key key) const
{
	return _pressed.find(key) != _pressed.end();
}
