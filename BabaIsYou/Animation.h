#pragma once
struct Animation
{
	int index;
	int maxframe;
	int playspeed;

	Animation() {}
	Animation(int _index, int _maxframe, int _playspeed)
	: index(_index), maxframe(_maxframe), playspeed(_playspeed)
	{};
};

