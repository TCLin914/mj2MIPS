#include <stdio.h>
#include <string>
#include <fstream>
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

//TODO: Add include llmv

extern SymbolTable yySymbolTable;

CodeGenVisitor::CodeGenVisitor()
{
    module = new Modul("Mini-Java", context);
    isRHSVisit = true;
}

void CodeGenVisitor::Visit(Goal* node)
{
    const int INDEX_OF_MAINCLASS = 0;
    const int INDEX_OF_ClASSDECLARATIONLIST = 1;
    
    if(node -> GetChild(INDEX_OF_ClASSDECLARATIONLIST) != NULL)
        node -> GetChild(INDEX_OF_ClASSDECLARATIONLIST) -> Accept(this);
    
    Function* mainFunc = cast<Function>(module -> getOrInsertFunction("main", ToLLVMType(VOID_T), (Type*) 0));
    currentFunction = mainFunc;
    currentBB = BasicBlock::Create(context, "EntryBlock", mainFunc);
    if(node -> GetChild(INDEX_OF_MAINCLASS) != NULL)
        node -> GetChild(INDEX_OF_MAINCLASS) -> Accept(this);
    //TODO:
}
void CodeGenVisitor::Visit(MainClass* node)
{
    //TODO:
}
void CodeGenVisitor::Visit(ClassDeclarationList* node)
{
    const int NUMBER_OF_ClASSDECLARATIONLIST_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_ClASSDECLARATIONLIST_CHILDREN);
}
void CodeGenVisitor::Visit(ClassDeclaration* node)
{
    //TODO:
}
void CodeGenVisitor::Visit(MethodDeclarationList* node)
{
    const int NUMBER_OF_METHODDECLARATIONLIST_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_METHODDECLARATIONLIST_CHILDREN);
}
void CodeGenVisitor::Visit(MethodDeclaration* node)
{
    //TODO:
}
void CodeGenVisitor::Visit(StatementList* node)
{
    const int NUMBER_OF_STATEMENTLIST_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_STATEMENTLIST_CHILDREN);
}
void CodeGenVisitor::Visit(Println* node)
{
    //TODO:
}
void CodeGenVisitor::Visit(IfStatement* node)
{
    const int INDEX_OF_PREDICATE = 0;
    const int INDEX_OF_TRUE_BLOCK = 1;
    const int INDEX_OF_FALSE_BLOCK = 2;
    if(node -> GetChild(INDEX_OF_PREDICATE) != NULL)
    {
        node -> GetChild(INDEX_OF_PREDICATE) -> Accept(this);
        if(values.size() >= 1)
        {
            if(types.back() == BOOL_T)
                PopTypes(1);
            else
            {
                printf("Error occurs in Visit(IfStatement*) : invalid type\n");
                return;
            }
            BasicBlock* trueBB = BasicBlock::Create(context, "TrueBlock", currentFunction);
            BasicBlock* previousBB = currentBB;
            currentBB = trueBB;
            if(node -> GetChild(INDEX_OF_TRUE_BLOCK) != NULL)
                node -> GetChild(INDEX_OF_TRUE_BLOCK) -> Accept(this);
            BasicBlock* trueBBEnd = currentBB;
            BasicBlock* falseBB = BasicBlock::Create(context, "FalseBlock", currentFunction);
            currentBB = falseBB;
            if(node -> GetChild(INDEX_OF_FALSE_BLOCK) != NULL)
                node -> GetChild(INDEX_OF_FALSE_BLOCK) -> Accept(this);
            BasicBlock* falseBBEnd = currentBB;
            BasicBlock* nextCurrentBB = BasicBlock::Create(context, "", currentFunction);
            BranchInst::Create(trueBB, falseBB, Pop(), previousBB);
            BranchInst::Create(nextCurrentBB, trueBBEnd);
            BranchInst::Create(nextCurrentBB, falseBBEnd);
            currentBB = nextCurrentBB;
        }
    }
}
void CodeGenVisitor::Visit(WhileStatement* node)
{
    const int INDEX_OF_PREDICATE = 0;
    const int INDEX_OF_BODY = 1;
    if(node -> GetChild(INDEX_OF_PREDICATE) != NULL)
    {
        BasicBlock* predicateBB = BasicBlock::Create(context, "PredicateBlock", currentFunction);
        BranchInst::Create(predicateBB, currentBB/*=prior predicatedBB*/);
        currentBB = predicateBB;
        node -> GetChild(INDEX_OF_PREDICATE) -> Accept(this);
        if(values.size() >= 1)
        {
            if(types.back() == BOOL_T)
                PopTypes(1);
            else 
            {
                printf("Error occurs in Visit(WhileStatement*) : invalid type\n");
                return;
            }
            BasicBlock* bodyBB = BasicBlock::Create(context, "", currentFunction);
            currentBB = bodyBB;
            if(node -> GetChild(INDEX_OF_BODY) != NULL)
                node -> GetChild(INDEX_OF_BODY) -> Accept(this);
            BranchInst::Create(predicateBB, currentBB/*=BodyBBEnd*/);
            BasicBlock* nextCurrentBB = BasicBlock::Create(context, "", currentFunction);
            BranchInst::Create(bodyBB, nextCurrentBB, Pop(), predicateBB);
            currentBB = nextCurrentBB;
        }
    }
}
void CodeGenVisitor::Visit(Assignment* node)
{
    const int NUMBER_OF_ASSIGNMENT_CHILDREN = 2;
    const int INDEX_OF_LHS = 0;
    const int INDEX_OF_RHS = 1;
    if(node -> GetChild(INDEX_OF_LHS) != NULL)
    {
        isRHSVisit = false;
        node -> GetChild(INDEX_OF_LHS) -> Accept(this);
        isRHSVisit = true;
    }
    if(node -> GetChild(INDEX_OF_RHS) != NULL)
        node -> GetChild(INDEX_OF_RHS) -> Accept(this);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = Pop();
        Value* operand1 = Pop();
        builder.CreateStore(operand2, operand1);
    }
    else if(values.size() == 1)
        printf("Error occurs in Visit(Assignment*) : values.size() = 1\n");
}
void CodeGenVisitor::Visit(And* node)
{
    const int NUMBER_OF_AND_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_AND_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = Pop();
        Value* operand1 = Pop();
        switch(type)
        {
            case BOOL_T:
                values.push_back(builder.CreateAnd(operand1, operand2));
                break;
            default:
                printf("Error occurs in Visit(And*) : invalid type\n");
                return;
        }
        types.push_back(BOOL_T);
    }
    else if(values.size() == 1)
        printf("Error occurs in Visit(And*) : valuse.size() = 1\n");
}
void CodeGenVisitor::Visit(LessThan* node)
{
    const int NUMBER_OF_LESS_THAN_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_LESS_THAN_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = Pop();
        Value* operand1 = Pop();
        switch(type)
        {
            case BOOL_T:
                values.push_back(builder.CreateICmpSLT(operand1, operand2));
                break;
            default:
                printf("Error occurs in Visit(LessThan*) : invalid type\n");
                return;
        }
        types.push_back(BOOL_T);
    }
    else if(values.size() == 1)
        printf("Error occurs in Visit(LessThan*) : valuse.size() = 1\n");
}
void CodeGenVisitor::Visit(Add* node)
{
    const int NUMBER_OF_ADD_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_ADD_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = pop();
        Value* operand1 = pop();
        switch(type)
        {
            case INTEGER_T:
                values.push_back(builder.CreateAdd(operand1, operand2));
                break;
            default:
                printf("Error occurs in Visit(Add*) : invalid type\n");
                return;
        }
        types.push_back(type);    
    }
    else if(values.size() == 1)
        printf("Error occurs in Visit(Add*) : values.size() = 1\n");
}
void CodeGenVisitor::Visit(Subtract* node)
{
    const int NUMBER_OF_SUBTRACE_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_SUBTRACE_CHILDREN);
    if(value.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = pop();
        Value* operand1 = pop();
        switch(type)
        {
            case INTEGER_T:
                values.push_back(builder.CreateSub(operand1, operand2));
                break;
            default:
                printf("Error occurs in Visit(Subtract*) : invalid type\n");
                return;
        }
        types.push_back(type);    
    }
    else if(values.size() == 1)
        printf("Error occurs in Visit(Subtract*) : values.size() = 1\n");
}
void CodeGenVisitor::Visit(Multiply* node) 
{
    const int NUMBER_OF_MULTIPLY_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_MULTIPLY_CHILDREN);
    if(value.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = pop();
        Value* operand1 = pop();
        switch(type)
        {
            case INTEGER_T:
                values.push_back(builder.CreateMul(operand1, operand2));
                break;
            default:
                printf("Error occurs in Visit(Multiply*) : invalid type\n");
                return;
        }
        types.push_back(type);    
    }
    else if(values.size() == 1)
        printf("Error occurs in Visit(Multiply*) : values.size() = 1\n");
}
void CodeGenVisitor::Visit(Not* node)
{
    const int NUMBER_OF_NOT_CHILDREN = 1;
    VisitChildren(nNode, NUMBER_OF_NOT_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_UNARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_UNARY_OPERATOR);        
        switch(type)
        {
            case BOOL_T:
                values.push_back(builder.CreateNot(Pop()));
                break;
            default:
                printf("Error occurs in Visit(Not*) : invalid type\n");
                types.pop_back();
        }
        types.push_back(BOOL_T);
    }
}


void CodeGenVisitor::Visit(Variable* node)
{
    const int NUMBER_OF_VARIABLE_CHILDREN = 1;
    Symbol* varSymbol = node -> GetSymbol();
    VisitChildren(node, NUMBER_OF_VARIABLE_CHILDREN);
    Value* resultVal;
    if(varSymbol -> type != ARRAY_T)
        resultVal = varSymbol -> value;
    //TODO:
}
void CodeGenVisitor::Visit(ConstantInteger* node)
{
    int constInt = node -> GetIntValue();
    IRBuilder<> builder(currentBB);
    values.push_back(builder.getInt32(constInt));
    types.push_back(INTEGER_T);
}
void CodeGenVisitor::Visit(ConstantBoolean* node)
{
    ConstantInt* constBoolean;
    if(node -> GetBoolValue())
        constBoolean = ConstantInt::getTrue(context);
    else 
        constBoolean = ConstantInt::getFalse(context);
    values.push_back(constBoolean);
    types.push_back(BOOL_T);
}
void CodeGenVisitor::Visit(PrintlnStatement*);

void CodeGenVisitor::Visit(ExpressionList*);


void CodeGenVisitor::Visit(ArrayAssignment*);
void CodeGenVisitor::Visit(ArrayLengthExpression*);
void CodeGenVisitor::Visit(FunctionCall*);
void CodeGenVisitor::Visit(ThisExpression*);
void CodeGenVisitor::Visit(NewExpression*);
void CodeGenVisitor::Visit(NewArray*);

void CodeGenVisitor::AllocateArguments(vector<Symbol*> symbols)
{
    Function::arg_iterator args_val = currentFunction -> arg_begin();
    IRBuilder<> builder(currentBB);
    for(int i = 0; i < symbols.size(); i++, args_val++)
    {
        char allocaArgName[1000];
        strcpy(allocaArgName, symbols[i] -> id.c_str());
        strcat(allocaArgName, "_arg");        
        args_val -> setName(allocaArgName);
        Value* arg_ptr = builder.CreateAlloca(ToLLVMType(symbols[i] -> type), 0, symbols[i] -> id.c_str());
        builder.CreateStore(args_val, arg_ptr);
        symbols[i] -> value = arg_ptr;
    }
}
void CodeGenVisitor::AllocateVariables(SymbolTable* symbolTable, bool isGlobal)
{
    for(int i = 0; i < symbolTable -> Size(); i++)
    {
        Symbol* symbol = symbolTable -> GetSymbol(i);
        if(symbol -> symbolTable == NULL && symbol -> value == NULL) //symbol == variable && != argument
        {            
            Type* type = ToLLVMType(symbol -> type);
            if(!isGlobal)
            {
                IRBuilder<> builder(currentBB); //there are no BB for allocate global
                symbol -> value = builder.CreateAlloca(type, NULL, symbol -> id.c_str());
            }
            else
            {
                GlobalVariable* globalVar = new GlobalVariable(*module, type, false, GlobalValue::ExternalLinkage, 0, symbol -> id.c_str());                
                globalVar -> setAlignment(4);
                // Initialize variable value
                /*
                if(symbol -> type != ARRAY_T)
                {                    
                    ConstantInt* zero = ConstantInt::get(context, APInt(32, StringRef("0"), 10));
                    ConstantFP* fzero = ConstantFP::get(context, APFloat(0.000000e+00));
                    if(symbol -> type == INTEGER_T)
                        globalVar -> setInitializer(zero);
                    else if(symbol ->type == REAL_T)
                        globalVar->setInitializer(fzero);                    
                }
                else
                {
                    ConstantAggregateZero* zeroArray = ConstantAggregateZero::get(type);
                    globalVar->setInitializer(zeroArray);
                }
                */	
                symbol -> value = globalVar;
            }
        }
    }
}
/*
Type* CodeGenVisitor::GetArrayType(Symbol* symbol)  
{
    Type* type = ArrayType::get(ToLLVMType(symbol->type), 0); //              
    return type;
}
*/
Type* CodeGenVisitor::ToLLVMType(Type_t type)
{
    switch(type)
    {
        case INTEGER_T:
            return Type::getInt32Ty(context);
        case BOOL_T:
            return Type::getInt1Ty(context);
        case VOID_T:
            return Type::getVoidTy(context);
        case ARRAY_T:
            return ArrayType::get(getInt32Ty(context), 0); //Initialize int array size to zero.
        default:
            printf("Error occurs in TypeTToLLVMTyVisitChildrenpe(Type_t): invalid type\n");
    }
}
Value* CodeGenVisitor::Pop()
{
    Value* value = values.back();
    values.pop_back();
    return value;
}
void CodeGenVisitor::VisitChildren(Node* pNode, int number)
{
    for(int i = 0; i < number; i++)
    {
        if(pNode -> GetChild(i) != NULL)
            pNode -> GetChild(i) -> Accept(this);
    }
}
Type_t CodeGenVisitor::PopTypes(int number)
{
    Type_t type = types.back();
    for(int i = 0; i < number; i++)
        types.pop_back();
    return type;
}
    
    
    
    
    
    
    
    
    
    
