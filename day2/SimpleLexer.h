#ifndef SIMPLELEXER_H
#define SIMPLELEXER_H
#include "ASTNode.h"
#include "../day1/TokenReader.h"
class SimpleLexer
{
public:
	ASTNode* parse(string script);
	// 统一入口
	ASTNode* program(TokenReader &reader);
	ASTNode* multiplicative(TokenReader &reader);
	ASTNode* additive(TokenReader& reader);
	ASTNode* multiplyDeclaration(TokenReader& reader);
	ASTNode* intDeclaration(TokenReader& reader);
	ASTNode* assignmentStatement(TokenReader& reader);
};
#endif