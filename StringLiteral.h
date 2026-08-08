#pragma once
#include<iostream>
#include"Expression.h"
#include"Lexer/Token.h"
class StringLiteral :public Expression {
public:
	Token token_;
	StringLiteral(Token token) :token_{ std::move(token) } {}
};