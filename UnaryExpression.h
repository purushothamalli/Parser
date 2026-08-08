#pragma once
#include<iostream>
#include"Expression.h"
#include"Lexer/Token.h"
class UnaryExpression :public Expression {
public:
	Token token_;
	std::unique_ptr<Expression> exp_;
	UnaryExpression(Token token, std::unique_ptr<Expression> exp) :token_{ std::move(token) }, exp_{ std::move(exp) } {}
};