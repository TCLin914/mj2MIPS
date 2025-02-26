#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include "CodeGenVisitor.h"
#include "Node.h" 	
#include "Type.h"
#include "Goal.h"
#include "MainClass.h"
#include "Add.h"
#include "Subtract.h"
#include "Multiply.h"
#include "And.h" 
#include "LessThan.h"
#include "Assignment.h"
#include "ClassDeclarationList.h"
#include "MethodDeclarationList.h"
#include "MethodDeclaration.h"
#include "StatementList.h"
#include "ExpressionList.h"
#include "Not.h" 
#include "PrintlnStatement.h"
#include "Variable.h"
#include "ClassDeclaration.h"
#include "NewArray.h"
#include "ArrayLengthExpression.h"
#include "IfStatement.h"
#include "WhileStatement.h"
#include "ArrayAssignment.h"
#include "FunctionCall.h"
#include "ConstantInteger.h"
#include "ConstantBoolean.h"
#include "ThisExpression.h"
#include "NewExpression.h"
#include "Symbol.h"
#include "SymbolTable.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/raw_ostream.h"
//#include "llvm/Support/IRBuilder.h"
#include "llvm/IR/IRBuilder.h"

int yyparse();
extern SymbolTable yySymbolTable;
extern Node* yyHeader;
extern bool yyIntegratedSymbolTable;

using namespace std;
using namespace llvm;

int main(int argc, char* argv[])
{
    bool initialized = false;
    bool semanticValid = false;
    Visitor* codeGenVisitor = new CodeGenVisitor();
    printf("%s\n", argv[1]);
    freopen(argv[1], "r", stdin);
    yyparse();
    freopen("con","r",stdin);
    //Initialize(&yySymbolTable);
    yyHeader -> SetSymbolTable(&yySymbolTable, &yySymbolTable);
    printf("%s%s\n", "yyIntegratedSymbolTable= ", yyIntegratedSymbolTable ? "true" : "false");
    if(yyIntegratedSymbolTable)
	initialized = yyHeader -> Initialize();
    printf("%s%s\n", "initialized= ", initialized ? "true" : "false");
    if(initialized)
        semanticValid = yyHeader -> SemanticCheck();
    printf("%s%s\n", "semanticValid= ", semanticValid ? "true" : "false");
    
    if(semanticValid)
    {
        ((CodeGenVisitor*)codeGenVisitor) -> ExternalFunctionsDef();
        yyHeader -> Accept(codeGenVisitor);
    }
	//system("pause");
	return 0;
}
