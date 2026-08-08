#pragma once
#include"Expression.h"
class NumberLiteral :public Expression {
public:
	Token token;
	NumberLiteral(Token token)
};