#pragma once

#include "DurationTimer.h"

class Living
{
public:
	Living(float lifeSecs);

	virtual ~Living() {}

	void update(float deltaTime);

	void kill();

	bool isLive() const;
private:
	DurationTimer lifeTimer_;

	bool isLive_;
};