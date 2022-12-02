#include "Listener.h"
#include "EventQueue.h"

Listener::Listener(const std::unordered_set<EventType> &listenedEvents) :
	listenedEvents_(listenedEvents)
{
	EventQueue::getInstance().attachListener(this);
}

Listener::Listener(std::unordered_set<EventType> &&listenedEvents) :
	listenedEvents_(listenedEvents)
{
	EventQueue::getInstance().attachListener(this);
}

Listener::~Listener()
{
	EventQueue::getInstance().detachListener(this);
}

bool Listener::listensForEventType(EventType eventType) const
{
	return listenedEvents_.find(eventType) != listenedEvents_.end();
}