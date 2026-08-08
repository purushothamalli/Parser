#pragma once
#include "NumberLiteral.h"
#include "Identifier.h"
#include "StringLiteral.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"

static void printIndent(std::ostream& os, int indent) {
    for (int i = 0; i < indent; ++i) os << "  ";
}

void printAst(const AstNode* node, std::ostream& os, int indent) {
    if (!node) {
        printIndent(os, indent);
        os << "<null>\n";
        return;
    }

    if (auto n = dynamic_cast<const NumberLiteral*>(node)) {
        printIndent(os, indent);
        os << "NumberLiteral: " << n->token_.lexeme_ << '\n';
        return;
    }
    if (auto id = dynamic_cast<const Identifier*>(node)) {
        printIndent(os, indent);
        os << "Identifier: " << id->token_.lexeme_ << '\n';
        return;
    }
    if (auto s = dynamic_cast<const StringLiteral*>(node)) {
        printIndent(os, indent);
        os << "StringLiteral: " << s->token_.lexeme_ << '\n';
        return;
    }
    if (auto u = dynamic_cast<const UnaryExpression*>(node)) {
        printIndent(os, indent);
        os << "UnaryExpression: " << u->token_.lexeme_ << '\n';
        printAst(u->exp_.get(), os, indent + 1);
        return;
    }
    if (auto b = dynamic_cast<const BinaryExpression*>(node)) {
        printIndent(os, indent);
        os << "BinaryExpression: " << b->token_.lexeme_ << '\n';
        printAst(b->left_.get(), os, indent + 1);
        printAst(b->right_.get(), os, indent + 1);
        return;
    }

    printIndent(os, indent);
    os << "UnknownNode\n";
}