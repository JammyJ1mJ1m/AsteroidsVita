#pragma once
#include "../Model.h"
#include <string>
#include <vector>
class ISystem
{
public:
	ISystem() = default;
	virtual ~ISystem() = default;
	virtual void Run(Model* pEntity) = 0;
};