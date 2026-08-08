#pragma once
#include<iostream>
#include"Expression.h"
#include"Lexer/Token.h"
class BinaryExpression :public Expression {
public:
	std::unique_ptr<Expression> left_;
	Token token_;
	std::unique_ptr<Expression> right_;
	BinaryExpression(std::unique_ptr<Expression> left, Token token, std::unique_ptr<Expression> right)
		:left_{ std::move(left) }
		, token_{ std::move(token) }
		, right_{ std::move(right) } 
	{}
};