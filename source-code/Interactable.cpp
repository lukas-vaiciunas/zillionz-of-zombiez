#include "Interactable.h"

Interactable::Interactable(const std::string &interactVerb, const std::string &name) :
	interactVerb_(interactVerb),
	name_(name)
{}

const std::string &Interactable::getInteractVerb() const
{
	return interactVerb_;
}

const std::string &Interactable::getName() const
{
	return name_;
}