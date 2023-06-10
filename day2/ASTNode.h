#ifndef ASTNODE_H
#define ASTNODE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
enum ASTNodeType{
	Program = 0,
	IntDeclaration,
	ExpressionStmt,
	AssignmentStmt,
	Primary,
	Multiplicative,
	Additive,
	Identifier,
	IntLiteral,
};
class ASTNode {
private:
	string text;
	ASTNodeType type;
	ASTNode* parent;
	vector<ASTNode*> child;
	void initMap();
public:
	static map<int,string>  nodeTypeMap;
	ASTNode();
	ASTNode(string text_, ASTNodeType type_);
	string GetText();
	ASTNodeType getType();
	ASTNode* GetParent();
	vector<ASTNode*> GetChildren();
	void addChild(string text, ASTNodeType type);
	void addChild(ASTNode *node);
	void dump(ASTNode* node, string indent);
};
#endif