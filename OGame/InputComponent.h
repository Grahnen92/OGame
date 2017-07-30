#pragma once


#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include <functional>
#include <vector>

struct KeyBoardEvent
{
	KeyBoardEvent() {}
	KeyBoardEvent(int _key, int _action, std::function<void()> _function) : key(_key), action(_action), function(_function) {}

	int action;
	int key;
	std::function<void()> function;

	void callEvent(int _key, int _action) {
		if (key == _key && action == _action)
			function();
	}
};

class InputComponent
{
public:
	InputComponent();
	~InputComponent();
	
	template<class Func, class Obj>
	void addKeyBoardEvent(int _key, int _action, Func&& _func, Obj&& _obj) {
		std::function<void(void)> new_keyboard_event = std::bind(_func, _obj);
		keyboard_events.push_back(KeyBoardEvent(_key, _action, new_keyboard_event));
	}

	void callKeyboardEvents(int _key, int _action) {
		for (auto & event : keyboard_events) {
			event.callEvent(_key, _action);
		}
	}

private:
	std::vector<KeyBoardEvent> keyboard_events;
	std::vector<std::function<float()>> axis_events;
	

};

#endif
