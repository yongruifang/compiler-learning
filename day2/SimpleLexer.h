#ifndef SIMPLELEXER_H
#define SIMPLELEXER_H
#include "ASTNode.h"
#include "../day1/TokenReader.h"
class SimpleLexer
{
public:
	ASTNode* multiplicative(TokenReader &reader);
	ASTNode* additive(TokenReader& reader);
	ASTNode* multiplyDeclaration(TokenReader& reader);
};
#endif