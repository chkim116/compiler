#pragma once
#include <map>
#include <vector>

using std::map;
using std::vector;

struct Program
{
	vector<struct Function *> functions;
};

struct Statement
{
};
struct Expression
{
};

struct Function : Statement
{
	string name;
	vector<string> parameters;
	vector<Statement *> block;
};
struct Return : Statement
{
	Expression *expression;
};
struct Variable : Statement
{
	string name;
	Expression *expression;
};
struct For : Statement
{
	Variable *variable;
	Expression *condition;
	Expression *expression;
	vector<Statement *> block;
};
struct Break : Statement
{
};
struct Continue : Statement
{
};
struct If : Statement
{
	vector<Expression *> conditions;
	vector<vector<Statement *> > blocks;
	vector<Statement *> elseBlock;
};
struct Print : Statement
{
	bool lineFeed = false;
	vector<Expression *> arguments;
};
struct ExpressionStatement : Statement
{
	Expression *expression;
};

struct Or : Expression
{
	Expression *lhs;
	Expression *rhs;
};
struct And : Expression
{
	Expression *lhs;
	Expression *rhs;
};
struct Relational : Expression
{
	Kind kind;
	Expression *lhs;
	Expression *rhs;
};
struct Arithmetic : Expression
{
	Kind kind;
	Expression *lhs;
	Expression *rhs;
};
// 단항 연산
struct Unary : Expression
{
	Kind kind;
	Expression *sub;
};
// 함수 호출 ex) add(1,2)
struct Call : Expression
{
	Expression *sub;
	vector<Expression *> arguments;
};
// 배열과 맵 원소 참조 표현 ex map['a'], arr[0]
struct GetElement : Expression
{
	Expression *sub;
	Expression *index;
};
// 배월과 맵의 원소 수정 map['a'] = 3
struct SetElement : Expression
{
	Expression *sub;
	Expression *index;
	Expression *value;
};
// 변수 참조
struct getVariable : Expression
{
	string name;
};
// 변수 수정
struct SetVariable : Expression
{
	string name;
	Expression *value;
};
struct NullLiteral : Expression
{
};
struct BooleanLiteral : Expression
{
	bool value = false;
};
struct NumberLiteral : Expression
{
	double value = 0.0;
};
struct StringLiteral : Expression
{
	string value;
};
struct ArrayLiteral : Expression
{
	vector<Expression *> values;
};
struct MapLiteral : Expression
{
	map<string, Expression *> values;
};
