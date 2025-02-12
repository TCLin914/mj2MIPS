#pragma once
#include <vector>
#include "Visitor.h"
#include "Type.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Attributes.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/raw_ostream.h"
//#include "llvm/Support/IRBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Bitcode/ReaderWriter.h"


using namespace std;
using namespace llvm;

class CodeGenVisitor : public Visitor
{
public:
    CodeGenVisitor();
    virtual void Visit(ClassDeclarationList*);
    virtual void Visit(MethodDeclarationList*);
    virtual void Visit(MethodDeclaration*);
    virtual void Visit(StatementList*);
    virtual void Visit(Assignment*);
    virtual void Visit(And*);
    virtual void Visit(LessThan*);
    virtual void Visit(Add*);
    virtual void Visit(Subtract*);
    virtual void Visit(Multiply*);
    virtual void Visit(Not*);    
    virtual void Visit(IfStatement*);
    virtual void Visit(WhileStatement*);
    virtual void Visit(MainClass*);
    virtual void Visit(Variable*);
    virtual void Visit(PrintlnStatement*);
    virtual void Visit(Goal*);
    virtual void Visit(ExpressionList*);
    virtual void Visit(ConstantInteger*);
    virtual void Visit(ConstantBoolean*);
    virtual void Visit(ClassDeclaration*);
    virtual void Visit(ArrayAssignment*);
    virtual void Visit(ArrayLengthExpression*);
    virtual void Visit(FunctionCall*);
    virtual void Visit(ThisExpression*);
    virtual void Visit(NewExpression*);
    virtual void Visit(NewArray*);
    void ExternalFunctionsDef();
protected:
private:
    static const int NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR = 2;
    static const int NUMBER_OF_OPERANDS_OF_UNARY_OPERATOR = 1;
    void VisitChildren(Node*, int);
    void AllocateArguments(vector<Symbol*>);
    void AllocateVariables(SymbolTable*, bool isGlobal = false);
    vector<Value*> ReversedOrderPop(int num);
    Value* Dereference(Value*);
    Type* GetArrayType(Symbol*);
    Type* ToLLVMType(Type_t);
    Type* ToLLVMPointType(Type_t);
    LLVMContext context;
    Module* module;
    Function* currentFunction;
    BasicBlock* currentBB;
    PointerType* currentPointerType;
    bool isRHSVisit;
    
    Value* Pop();
    Type_t PopTypes(int);    
    vector<Value*> values;
    vector<Type_t> types;
    
    Function* printFunc;
    GlobalVariable* gvar_array__str1;   //"%d\n"
    GlobalVariable* gvar_array__str2;   //"%g\n"
    GlobalVariable* gvar_array__str3;   //"%s\n"
    Constant* printIntArg;
    Constant* printRealArg;
    Constant* printStringArg;
    
    void Outputs();
};
