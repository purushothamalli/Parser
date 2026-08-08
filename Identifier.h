#pragma once
#include<iostream>
#include"Expression.h"
#include"Lexer/Token.h"
class Identifier :public Expression {
public:
	Token token_;
	Identifier(Token token) :token_{ std::move(token) } {}
};