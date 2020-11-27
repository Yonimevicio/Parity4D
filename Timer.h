#pragma once
class Timer
{
public :
	void Start();
	unsigned int Read();
	void Stop();

private:
	unsigned int last_time = 0, current_time = 0;
	bool counting = false;
};

