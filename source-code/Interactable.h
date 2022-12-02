#pragma once

#include <string>

class Interactable
{
public:
	Interactable(const std::string &interactVerb, const std::string &name);
	virtual ~Interactable() {}

	virtual void interact() = 0;

	const std::string &getInteractVerb() const;
	const std::string &getName() const;
private:
	std::string interactVerb_;
	std::string name_;
};