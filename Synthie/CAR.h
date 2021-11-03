#pragma once
#include "CAudioNode.h"

class CAR :
	public CAudioNode
{
public:
	double attack;
	double release;
	double time;
	CAudioNode* source;

public:
	CAR();
	~CAR() {};
	void SetSource(CAudioNode* source);
	void Start();
	bool Generate(double duration);
	bool Generate();
};

