#pragma once

class DurationTimer
{
public:
	DurationTimer(float targetSecs);

	void update(float deltaTime);

	void hardReset();
	void softReset();
	void rig();

	bool isDone() const;
	float getTargetSecs() const;
	float getElapsedSecs() const;
private:
	float targetSecs_;
	float elapsedSecs_;
};