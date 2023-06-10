#include "ASTNode.h"
ASTNode::ASTNode()
{
    text = "";
    type = Program;
    parent = NULL;		
}
map<int,string>  ASTNode::nodeTypeMap = {
    {Program, "Program"},
    {IntDeclaration,"IntDeclaration"},
    {Primary, "Primary"},
    {Multiplicative, "Multiplicative"},
    {Additive, "Additive"},
    {Identifier, "Identifier"},
    {IntLiteral, "IntLiteral"}
};


ASTNode::ASTNode(string text_, ASTNodeType type_)
{
    text = text_;
    type = type_;
    parent = NULL;
}

ASTNode* ASTNode::GetParent()
{
    return parent;
}

vector<ASTNode*> ASTNode::GetChildren()
{
    return child;
}

ASTNodeType ASTNode::getType()
{
    return type;
}
string ASTNode::GetText()
{
    return text;
}

void ASTNode::addChild(string text, ASTNodeType type)
{
    ASTNode* node = new ASTNode(text, type);

    child.push_back(node);
    node->parent = this;
}

void ASTNode::addChild(ASTNode *node)
{
    child.push_back(node);
    node->parent = this;
}
void ASTNode::dump(ASTNode* node, string indent)
{
    if(node == NULL) return;
    cout << indent << nodeTypeMap[node->getType()] << " " << node->GetText() << endl;
    for(auto child : node->GetChildren())
    {
        dump(child,indent+'\t');
    }
}