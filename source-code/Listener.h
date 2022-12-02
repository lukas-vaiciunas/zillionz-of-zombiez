#pragma once

class Event;

#include "EventType.h"
#include <unordered_set>

class Listener
{
public:
	Listener(const std::unordered_set<EventType> &listenedEvents);
	Listener(std::unordered_set<EventType> &&listenedEvents);
	virtual ~Listener();
	
	virtual void onEvent(const Event &ev) = 0;

	bool listensForEventType(EventType eventType) const;
private:
	std::unordered_set<EventType> listenedEvents_;
};