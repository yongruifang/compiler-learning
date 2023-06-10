#include "SimpleScript.h"
void SimpleScript::start(bool verbose_)
{
    verbose = verbose_;
    cout << "Simple Script Language!" << endl;
    cout << "Type 'exit();' to quit" << endl;
    if(verbose == true){ 
        cout << "verbse mode" << endl; 
    }
    string script = "";
    cout << ">";
    SimpleLexer lexer;
    while(true){
        getline(cin, script);
        cout << script << endl;
        if(script == "exit();"){
            break;
        }
        ASTNode* root = lexer.parse(script);
        // if(verbose == true){
        //     root->dump(root, "");
        // }
        evaluate(root, "");
        cout << "\n>";
    }
}
int SimpleScript::evaluate(ASTNode* node, string indent)
{
    int result = 0;
    if(verbose){
        cout << indent << "Compute: " << ASTNode::nodeTypeMap[node->getType()] << endl;
    }
    ASTNode *child1, *child2;
    int value1, value2;
    string varName = "";
    switch(node->getType())
    {
        case Program:
            for(auto c : node->GetChildren()){
                result = evaluate(c, indent+'\t');
            }
            break;
        case Additive:
            child1 = node->GetChildren()[0];
            value1 = evaluate(child1, indent + "\t");
            child2 = node->GetChildren()[1];
            value2 = evaluate(child2, indent + "\t");
            if(node->GetText()=="Plus"){
                result = value1 + value2;
            }else if(node->GetText()=="Minus"){
                result = value1 - value2;
            }
            break;
        case Multiplicative:
            child1 = node->GetChildren()[0];
            value1 = evaluate(child1, indent + "\t");
            child2 = node->GetChildren()[1];
            value2 = evaluate(child2, indent + "\t");
            if(node->GetText()=="Star"){
                result = value1 * value2;
            }else if(node->GetText()=="Slash"){
                result = value1 / value2;
            }
            break;
        case IntLiteral:
            result = stoi(node->GetText());
            break;
        case Identifier:
            varName = node->GetText();
            if(variables.find(varName) != variables.end()){ //存储区中存在
                result = variables[varName]; // 返回变量值
            }else{
                cout << "unknown variable: " << varName << endl;
            }
            break;
        case AssignmentStmt:
            varName = node->GetText();
            if(variables.find(varName) != variables.end()){ 
                result = evaluate(node->GetChildren()[0], indent + "\t");
                variables[varName] = result;
            }else{
                cout << "unknown variable: " << varName << endl;
            }
            break;
        case IntDeclaration:
            varName = node->GetText();
            if(variables.find(varName) != variables.end()){ 
                cout << "variable has been declared: " << varName << endl;
            }else{
                if(node->GetChildren().size() > 0){
                    result = evaluate(node->GetChildren()[0], indent + "\t");
                    variables[varName] = result;
                }else{
                    variables[varName] = 0;
                }
            }
            break;
        default:
            break;
    }
    if(verbose){
        cout << indent << "Result: " << result << endl;
    }else if(indent == ""){ //顶层节点
        if(node->getType() == IntDeclaration || node->getType() == AssignmentStmt){
            cout << node->GetText() << " = " << result << endl;
        }else if(node->getType() != Program){
            cout << result << endl;
        }
    }
    return result;
}