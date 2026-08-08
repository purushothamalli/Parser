#pragma once
#include<vector>
#include"AstNode.h"
#include"Identifier.h"
#include"NumberLiteral.h"
#include"StringLiteral.h"
#include"UnaryExpression.h"
#include"BinaryExpression.h"
#include"Lexer/Token.h"
#include"Lexer/Lexer.h"
class Parser {
private:
	std::vector<Token> tokens_;
	std::size_t position_ = 0;
	const Token& current() const;
	const Token& peek() const;
	Token consume();
	bool atEnd() const;
	std::unique_ptr<Expression> parseExpression();
	std::unique_ptr<Expression> parsePrimary();
	std::unique_ptr<Expression> parseUnary();
	std::unique_ptr<Expression> parseAdditive();
	std::unique_ptr<Expression> parseMultiplicative();
	//std::unique_ptr<Expression> parseBinary();
public:
	Parser(std::string text) {
		Lexer lexer{ text };
		this->tokens_ = lexer.tokenize();
	}
	std::unique_ptr<AstNode> parse();
};