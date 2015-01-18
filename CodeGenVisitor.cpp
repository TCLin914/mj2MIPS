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

extern SymbolTable yySymbolTable;

CodeGenVisitor::CodeGenVisitor()
{
    module = new Module("Mini-Java", context);
    module -> dump();
    isRHSVisit = true;
}

void CodeGenVisitor::ExternalFunctionsDef() ////
{
    PointerType* pointerType = PointerType::get(IntegerType::get(module -> getContext(), 8), 0);
    vector<Type*> printSting_args;
    printSting_args.push_back(pointerType);
    FunctionType* FuncTy_6 = FunctionType::get(/*Result=*/IntegerType::get(module -> getContext(), 32), /*Params=*/printSting_args, /*isVarArg=*/true);
    printFunc = module->getFunction("printf");
    if(!printFunc) {

        printFunc = Function::Create(FuncTy_6, GlobalValue::ExternalLinkage, "printf", module);
        printFunc -> setCallingConv(CallingConv::C);
    }
    //AttrListPtr* printFunc_PAL;
    //printFunc -> setAttributes(printFunc_PAL);

    ArrayType* arrayTy = ArrayType::get(IntegerType::get(module -> getContext(), 8), 4);
    gvar_array__str1 = new GlobalVariable(*module, arrayTy, /*isConstant=*/true, GlobalValue::PrivateLinkage, 0, /*Name=*/".str1");
    gvar_array__str1 -> setAlignment(1);
    Constant *const_array_7 = ConstantDataArray::getString(module -> getContext(), "%d\x0A", true);
    gvar_array__str1 -> setInitializer(const_array_7);
    ConstantInt* const_int32_9 = ConstantInt::get(module -> getContext(), APInt(32, StringRef("0"), 10));
    std::vector<Constant*> const_ptr_10_indices;
    const_ptr_10_indices.push_back(const_int32_9);
    const_ptr_10_indices.push_back(const_int32_9);
    printIntArg = ConstantExpr::getGetElementPtr(gvar_array__str1, const_ptr_10_indices);
    
    gvar_array__str2 = new GlobalVariable(*module, arrayTy, /*isConstant=*/true, GlobalValue::PrivateLinkage, 0, /*Name=*/".str2");
    gvar_array__str2 -> setAlignment(1);
    Constant *const_array_8 = ConstantDataArray::getString(module -> getContext(), "%g\x0A", true);
    gvar_array__str2 -> setInitializer(const_array_8);
    printRealArg = ConstantExpr::getGetElementPtr(gvar_array__str2, const_ptr_10_indices);

    gvar_array__str3 = new GlobalVariable(*module, arrayTy, /*isConstant=*/true, GlobalValue::PrivateLinkage, 0, /*Name=*/".str3");
    gvar_array__str3 -> setAlignment(1);
    Constant *const_array_9 = ConstantDataArray::getString(module -> getContext(), "%s\x0A", true);
    gvar_array__str3 -> setInitializer(const_array_9);
    printStringArg = ConstantExpr::getGetElementPtr(gvar_array__str3, const_ptr_10_indices);
}

void CodeGenVisitor::Visit(Goal* node)
{
    printf("Visit Goal node");
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
    mainFunc -> dump();
    outs() << *module;
    
}
void CodeGenVisitor::Visit(MainClass* node)
{
    printf("Visit MainClass node");
    const int NUMBER_OF_MAINCLASS_CHILDREN = 1;
    VisitChildren(node, NUMBER_OF_MAINCLASS_CHILDREN);   
}

void CodeGenVisitor::Visit(ClassDeclarationList* node)
{
    printf("Visit ClassDeclarationList node");
    const int NUMBER_OF_ClASSDECLARATIONLIST_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_ClASSDECLARATIONLIST_CHILDREN);
}

void CodeGenVisitor::Visit(ClassDeclaration* node)
{
    printf("Visit ClassDeclaration node");
    const int NUMBER_OF_CLASSDECLARATION_CHILDREN = 1;
    Symbol* classSymbol = node -> GetClassSymbol();
    SymbolTable* classSymbolTable = classSymbol -> symbolTable;
    
    StructType* classType = module -> getTypeByName(classSymbol -> id);
    if(!classType)
    {
        classType = StructType::create(context, classSymbol -> id); 
        
    }
    else
    {
        printf("Error occurs in Visit(ClassDeclaration*) : Class Declaration duplicate\n");
    }
    vector<Type*> classTypeFields;
    for(int i = 0; i < classSymbol -> parameters -> size(); i++)
    {
        classTypeFields.push_back(ToLLVMType((*classSymbol -> parameters)[i] -> type)); //TODO:
    }
    if(classType -> isOpaque())
    {
        classType -> setBody(classTypeFields, false);
    }       
    currentPointerType = PointerType::get(classType, 0);   
    classSymbol -> structType = classType;
    VisitChildren(node, NUMBER_OF_CLASSDECLARATION_CHILDREN);    
}

void CodeGenVisitor::Visit(MethodDeclarationList* node)
{
    printf("Visit MethodDeclarationList node");
    const int NUMBER_OF_METHODDECLARATIONLIST_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_METHODDECLARATIONLIST_CHILDREN);
}

void CodeGenVisitor::Visit(MethodDeclaration* node)
{
    printf("Visit MethodDeclaration node");
    const int NUMBER_OF_METHODDECLARATION_CHILDREN = 2;
    Symbol* methodSymbol = node -> GetMethodSymbol();
    SymbolTable* methodSymbolTable = methodSymbol -> symbolTable;
    Symbol* retSymbol = methodSymbolTable -> GetSymbol(methodSymbol -> id);
    vector<Type*> methodArgs;
    methodArgs.push_back(currentPointerType); //set class pointer
    for(int i = 0; i < methodSymbol -> parameters -> size(); i++)
        methodArgs.push_back(ToLLVMType((*methodSymbol -> parameters)[i] -> type));
        
    FunctionType* methodType = FunctionType::get(ToLLVMType(retSymbol -> type), methodArgs, false);
    Function* method = cast<Function>(module -> getOrInsertFunction(methodSymbol -> id.c_str(), methodType));
    methodSymbol -> value = method;
    currentFunction = method;
     
    currentBB = BasicBlock::Create(context, "", method);
    AllocateArguments(*(methodSymbol -> parameters));
    AllocateVariables(methodSymbol -> symbolTable);
    VisitChildren(node, NUMBER_OF_METHODDECLARATION_CHILDREN);
    if(methodSymbol -> type != VOID_T)
    {
        //isRHSVisit = true;
        // ReturnInst::Create(context, Dereference(retSymbol -> value), currentBB);
        Value* retValue = Pop();
        ReturnInst::Create(context, Dereference(retValue), currentBB);
    }
    /*
    else
        ReturnInst::Create(context, currentBB);
    */    
}

void CodeGenVisitor::Visit(StatementList* node)
{
    printf("Visit StatementList node");
    const int NUMBER_OF_STATEMENTLIST_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_STATEMENTLIST_CHILDREN);
}

void CodeGenVisitor::Visit(IfStatement* node)
{
    printf("Visit IfStatement node");
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
    printf("Visit WhileStatement node");
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
    printf("Visit Assignment node");
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
    printf("Visit And node");
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
    printf("Visit LessThan node");
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
    printf("Visit Add node");
    const int NUMBER_OF_ADD_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_ADD_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = Pop();
        Value* operand1 = Pop();
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
    printf("Visit Subtract node");
    const int NUMBER_OF_SUBTRACE_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_SUBTRACE_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = Pop();
        Value* operand1 = Pop();
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
    printf("Visit Multiply node");
    const int NUMBER_OF_MULTIPLY_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_MULTIPLY_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_BINARY_OPERATOR);
        Value* operand2 = Pop();
        Value* operand1 = Pop();
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
    printf("Visit Not node");
    const int NUMBER_OF_NOT_CHILDREN = 1;
    VisitChildren(node, NUMBER_OF_NOT_CHILDREN);
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
    printf("Visit Variable node");
    const int NUMBER_OF_VARIABLE_CHILDREN = 1;
    Symbol* varSymbol = node -> GetSymbol();
    VisitChildren(node, NUMBER_OF_VARIABLE_CHILDREN);
    Value* resultVal;
    /*
    if(varSymbol -> type != ARRAY_T)
        resultVal = varSymbol -> value;
    */
    resultVal = varSymbol -> value;
    values.push_back(resultVal);
    types.push_back(varSymbol -> type);    
}

void CodeGenVisitor::Visit(ConstantInteger* node)
{
    printf("Visit ConstantInteger node");
    int constInt = node -> GetIntValue();
    IRBuilder<> builder(currentBB);
    values.push_back(builder.getInt32(constInt));
    types.push_back(INTEGER_T);
}

void CodeGenVisitor::Visit(ConstantBoolean* node)
{
    printf("Visit ConstantBoolean node");
    ConstantInt* constBoolean;
    if(node -> GetBoolValue())
        constBoolean = ConstantInt::getTrue(context);
    else 
        constBoolean = ConstantInt::getFalse(context);
    values.push_back(constBoolean);
    types.push_back(BOOL_T);
}

void CodeGenVisitor::Visit(PrintlnStatement* node) 
{
    printf("Visit PrintlnStatement node");
    const int NUMBER_OF_PRINTLNSTATEMENT_CHILDREN = 1;
    //Symbol* funcSymbol = node -> GetFuncSymbol();
    VisitChildren(node, NUMBER_OF_PRINTLNSTATEMENT_CHILDREN);
    std::vector<Value*> int32_18_params;
    int32_18_params.push_back(printStringArg);
    int32_18_params.push_back(Pop());
    PopTypes(NUMBER_OF_PRINTLNSTATEMENT_CHILDREN);
    CallInst::Create(printFunc, int32_18_params, "", currentBB);    
}

void CodeGenVisitor::Visit(ExpressionList* node)
{
    printf("Visit ExpressionList node");
    const int NUMBER_OF_EXPRESSIONLIST_CHILDREN = 2;
    VisitChildren(node, NUMBER_OF_EXPRESSIONLIST_CHILDREN);
}

void CodeGenVisitor::Visit(ArrayAssignment* node)
{
    printf("Visit ArrayAssignment node");
    const int INDEX_OF_VARIABLE = 0;
    const int INDEX_OF_ARRAY_INDEX = 1;
    const int INDEX_OF_VALUE = 2;
    const int NUMBER_OF_ARRAYASSIGNMENT_CHILDREN = 3;
    VisitChildren(node, NUMBER_OF_ARRAYASSIGNMENT_CHILDREN);
    vector<Value*> ranges;
    if(values.size() >= NUMBER_OF_ARRAYASSIGNMENT_CHILDREN)
    {
        Value* value = Pop();
        Value* index = Pop();
        Value* variable = Pop();       
        PopTypes(NUMBER_OF_ARRAYASSIGNMENT_CHILDREN);
        ranges.push_back(ConstantInt::get(context, APInt(32, StringRef("0"), 10)));
        ranges.push_back(index);
        
        Constant* ptr = ConstantExpr::getGetElementPtr((Constant*)variable, ranges);
        StoreInst* inst = new StoreInst(value, ptr, false, currentBB);        
    }
    else
    {
        printf("Error occurs in Visit(ArrayAssignment*) : values.size is incorrect\n");
    }   
}

void CodeGenVisitor::Visit(ArrayLengthExpression* node)
{
    printf("Visit ArrayLenghtExpression node");
    const int NUMBER_OF_ARRAYLENGTHEXPRESSION_CHILDREN = 1;
    VisitChildren(node, NUMBER_OF_ARRAYLENGTHEXPRESSION_CHILDREN);
    if(values.size() >= NUMBER_OF_ARRAYLENGTHEXPRESSION_CHILDREN)
    {
        ArrayType* arrayType = (ArrayType*)Pop() -> getType();
        IRBuilder<> builder(currentBB);
        values.push_back(builder.getInt32(arrayType -> getNumElements()));
        types.push_back(INTEGER_T);   
    }
    else
    {
        printf("Error occurs in Visit(ArrayLengthExpression*) : values.size is incorrect\n");
    }
}

void CodeGenVisitor::Visit(FunctionCall* node)
{
    printf("Visit FunctionCall node");
    const int NUMBER_OF_FUNCTION_CALL_CHILDREN = 2;
    const int INDEX_OF_CLASS = 0;
    const int INDEX_OF_PARAMETERS = 1;
    Symbol* funcSymbol = node -> GetFuncSymbol();
    node -> GetChild(INDEX_OF_PARAMETERS) -> Accept(this); // get parameters
    Value* classVariable;
    if(values.size() >= (*funcSymbol->parameters).size())
    {
        node -> GetChild(INDEX_OF_CLASS) -> Accept(this);
        classVariable = Pop();
        PopTypes(1);
        IRBuilder<> builder(currentBB);
        vector<Value*> parameters = ReversedOrderPop((*funcSymbol -> parameters).size());
        parameters.insert(parameters.begin(), classVariable);
        Value* retValue = builder.CreateCall(funcSymbol -> value, parameters);
        if(funcSymbol->type != VOID_T)
        {
            values.push_back(retValue);
            types.push_back(funcSymbol -> type);
        }         
    }    
}

void CodeGenVisitor::Visit(ThisExpression* node)
{
    //IRBuilder<> builder(currentBB);
    //Value* value = builder.CreateAlloca
    //TODO:

}

void CodeGenVisitor::Visit(NewExpression* node)
{
    printf("Visit NewExpression node");
    Symbol* classSymbol = node -> GetClassSymbol();
    IRBuilder<> builder(currentBB); 
    Value* value = builder.CreateAlloca(classSymbol -> structType, NULL, classSymbol -> id.c_str());
     
    values.push_back(value);
    types.push_back(CLASS_T);
}

void CodeGenVisitor::Visit(NewArray* node)
{
    printf("Visit NewArray node");
    const int NUMBER_OF_NEWARRAY_CHILDREN = 1;
    VisitChildren(node, NUMBER_OF_NEWARRAY_CHILDREN);
    if(values.size() >= NUMBER_OF_OPERANDS_OF_UNARY_OPERATOR)
    {
        IRBuilder<> builder(currentBB);
        Type_t type = PopTypes(NUMBER_OF_OPERANDS_OF_UNARY_OPERATOR);
        Value* val = Pop();          
        int arraySize;
        if (ConstantInt* ci = dyn_cast<ConstantInt>(val)) 
        {
            if (ci -> getBitWidth() <= 32) 
            {
                arraySize = ci -> getSExtValue();
            } 
            else
            {
                printf("Error occurs in Visit(NewArray*) : Array size exceed 32 bits\n");
            }
        }
        else
        {
             printf("Error occurs in Visit(NewArray*) : ConstantInt* ci = dyn_cast<ConstantInt>(val)\n");
        }
        switch(type)
        {
            case INTEGER_T:
                values.push_back(builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), arraySize)));
                break;
            default:
                printf("Error occurs in Visit(NewArray*) : invalid type\n");
                types.pop_back();
        }
        types.push_back(ARRAY_T);
    }    
    else
    {
        printf("Error occurs in Visit(NewArray*) : values.size is incorrect\n");
    }
}

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

vector<Value*> CodeGenVisitor::ReversedOrderPop(int num)
{
    vector<Value*> result;
    for(int i = num; i > 0; i--)
        result.push_back(values[values.size() - i]);
    for(int i = num; i > 0; i--)
        Pop();
    if(num > 0)
        PopTypes(num);
    return result;
}

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
            return ArrayType::get(Type::getInt32Ty(context), 0); //Initialize int array size to zero.
        case CLASS_T:
            return StructType::get(context, false);
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

Value* CodeGenVisitor::Dereference(Value* value)    //
{
    return new LoadInst(value, "", false, currentBB);
}
    
    
    
    
    
    
    
    
    
    
