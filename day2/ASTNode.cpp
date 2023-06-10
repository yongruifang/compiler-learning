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
int ASTNode::evaluate(ASTNode* node, string indent)
{
    if(node == NULL) return 0;
    int result = 0;
    cout << indent << "Compute: " << nodeTypeMap[node->type] << endl;
    ASTNode *child1=NULL, *child2 =NULL;
    int value1 , value2;
    switch(node->type){
        case Program:
            for(auto c : node->GetChildren())
            {
                result = evaluate(c, indent+"\t");
            }
            break;
        case Additive :
            child1 = node->GetChildren()[0];
            value1 = evaluate(child1, indent+"\t");
            child2 = node->GetChildren()[1];
            value2 = evaluate(child2, indent+"\t");
            result = value1 + value2;
            break;
        case Multiplicative:
            child1 = node->GetChildren()[0];
            value1 = evaluate(child1, indent+"\t");
            child2 = node->GetChildren()[1];
            value2 = evaluate(child2, indent+"\t");
            result = value1 * value2;
            break;           
        case IntLiteral:
            result = stoi(node->GetText());
            break;
        default:
            break;
    }
    cout << indent << "Result: "<< result << endl;
    return result;
}