#pragma once
#include"AstNode.h"
class Expression :public AstNode {
public:
	~Expression() override = default;
};