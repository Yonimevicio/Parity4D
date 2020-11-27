#pragma once
class MicroTimer
{
public:
	void Start();
	unsigned int Read();
	unsigned int Stop();

private:
	unsigned int last_time = 0, current_time = 0;
	bool counting = false;
};

