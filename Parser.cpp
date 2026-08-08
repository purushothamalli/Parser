#include <iostream>
#include<string>
#include"Parser.h"
#include"AstPrinter.h"

std::unique_ptr<AstNode> Parser::parse() {
	for (Token& token : this->tokens_) {
		std::cout << token << '\n';
	}
	return std::unique_ptr<AstNode>(this->parseExpression().release());
}
std::unique_ptr<Expression> Parser::parseExpression() {
	return this->parseAdditive();
}
const Token& Parser::current() const {
	return this->tokens_[this->position_];
}
const Token& Parser::peek() const {
	const Token& current = this->current();
	if (current.kind_ == Token::Kind::Eof) return current;
	return this->tokens_[this->position_ + 1];
}
Token Parser::consume() {
	const Token& current = this->current();
	if (current.kind_ == Token::Kind::Eof) return current;
	return std::move(this->tokens_[this->position_++]);
}
bool Parser::atEnd() const {
	return this->current().kind_ == Token::Kind::Eof;
}
std::unique_ptr<Expression> Parser::parsePrimary() {
	const Token& current = this->current();
	if (current.kind_ == Token::Kind::Identifier) return std::make_unique<Identifier>(this->consume());
	else if (current.kind_ == Token::Kind::Number) return std::make_unique<NumberLiteral>(this->consume());
	else if (current.kind_ == Token::Kind::String) return std::make_unique<StringLiteral>(this->consume());
	else throw std::runtime_error{ std::string{"Invalid Token: "} + current.lexeme_ + std::string{"At "} + std::to_string(current.line_) + " " + std::to_string(current.column_) };
}
std::unique_ptr<Expression> Parser::parseUnary() {
	const Token& current = this->current();
	if (current.kind_ == Token::Kind::Operator && (current.lexeme_ == "+" || current.lexeme_ == "-" || current.lexeme_ == "!" || current.lexeme_ == "++" || current.lexeme_ == "--")) {
		Token op = this->consume();
		return std::make_unique<UnaryExpression>(std::move(op), this->parseUnary());
	}
	return parsePrimary();
}
std::unique_ptr<Expression> Parser::parseAdditive() {
	auto left = this->parseMultiplicative();
	while (this->current().kind_ == Token::Kind::Operator && (this->current().lexeme_ == "+" || this->current().lexeme_ == "-")) {
		Token op = this->consume();
		left = std::make_unique<BinaryExpression>(std::move(left), std::move(op), this->parseMultiplicative());
	}
	return left;
}
std::unique_ptr<Expression> Parser::parseMultiplicative() {
	auto left = this->parseUnary();
	while ((this->current().kind_ == Token::Kind::Operator && (this->current().lexeme_ == "*" || this->current().lexeme_ == "/" || this->current().lexeme_ == "%"))) {
		Token op = this->consume();
		left = std::make_unique<BinaryExpression>(std::move(left), std::move(op), this->parseUnary());
	}
	return left;
}
//std::unique_ptr<Expression> Parser::parseBinary() {
//	auto left = this->parseUnary();
//	const Token& current = this->current();
//	if (current.kind_ == Token::Kind::Operator && (current.lexeme_ == "+" || current.lexeme_ == "-" || current.lexeme_ == "*" || current.lexeme_ == "/" || current.lexeme_ == "%" || current.lexeme_ == "==" || current.lexeme_ == "!=" || current.lexeme_ == "<" || current.lexeme_ == ">" || current.lexeme_ == "<=" || current.lexeme_ == ">=" || current.lexeme_ == "&&" || current.lexeme_ == "||")) {
//		return std::make_unique<BinaryExpression>(left, this->consume(), this->parseBinary());
//	}
//	return left;
//}

int main()
{
	std::cout << "Test on expressions parsing: ";
	Parser parser{ "1 + 2 * 3" };
	auto ast = parser.parse();
	if (ast)
		printAst(ast.get(), std::cout, 0);
	return 0;
}