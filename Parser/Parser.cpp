#include <set>
#include <iostream>
#include "Token.h"
#include "Node.h"

using std::cout;
using std::set;

auto parse(vector<Token>) -> Program *;
static auto parseFunction() -> Function *;
static auto parseBlock() -> vector<Statement *>;
static auto parseVariable() -> Variable *;
static auto parseExpressionStatement() -> ExpressionStatement *;

auto skipCurrent(Kind kind) -> void;
auto skipCurrentIf(Kind kind) -> bool;

static vector<Token>::iterator current;

auto parse(vector<Token> tokens) -> Program *
{
	auto result = new Program();
	current = tokens.begin();

	while (current->kind != Kind::EndOfToken)
	{
		// 구문 분석
		switch (current->kind)
		{
		case Kind::Function:
		{
			result->functions.push_back(parseFunction());
			break;
		}
		default:
			cout << *current << " 잘못된 구문입니다.";
			exit(1);
		}
	}
	return result;
}

auto parseFunction() -> Function *
{
	auto result = new Function();
	skipCurrent(Kind::Function);

	// 함수 이름 확인
	result->name = current->string;
	skipCurrent(Kind::Identifier);

	// 매개 변수 확인 ex (args)
	skipCurrent(Kind::LeftParen);
	if (current->kind != Kind::RightParen)
	{
		do
		{
			result->parameters.push_back(current->string);
			skipCurrent(Kind::Identifier);
		} while (skipCurrentIf(Kind::Comma));
	}
	skipCurrent(Kind::RightParen);

	// 함수 블록 확인 ex { }
	skipCurrent(Kind::LeftBrace);
	result->block = parseBlock();
	skipCurrent(Kind::RightBrace);

	return result;
}

auto parseBlock() -> vector<Statement *>
{
	vector<Statement *> result;
	while (current->kind != Kind::RightBrace)
	{
		switch (current->kind)
		{
		case Kind::EndOfToken:
			cout << *current << " 잘못된 구문입니다.";
			exit(1);
		case Kind::Variable:
			result.push_back(parseVariable());
			break;
		default:
			result.push_back(parseExpressionStatement());
			break;
		}
	}

	return result;
}

auto parseExpressionStatement() -> ExpressionStatement *
{
	auto result = new ExpressionStatement();
	results->expression = parseExpression();
	skipCurrent(Kind::semicolon);
	return result;
}

auto parseExpression() -> Expression *
{
	return parseAssignment();
}

auto parseAssignment() -> Expression *
{
	auto result = parseOr();

	if (current->kind != Kind::Assignment)
	{
		return result;
	}

	skipCurrent(Kind::Assignment);

	if (auto getVariable = dynamic_cast<GetVariable *>(result))
	{
		auto result = new SetVariable();
		result->name = getVariable->name;
		result->value = parseAssignment();
		return result;
	}

	if (auto getElement = dynamic_cast<GetElement *>(result))
	{
		auto result = new SetElement();
		result->sub = getElement->sub;
		result->index = getElement->index;
		result->value = parseAssignment();
		return result;
	}

	cout << "잘못된 대입 연산 식입니다.";
	exit(1);
}

auto parseVariable() -> Variable *
{
	auto result = new Variable();

	// 변수 키워드 var 스킵
	skipCurrent(Kind::Variable);

	result->name = current->string;
	skipCurrent(Kind::Identifier);

	// 할당 연산자 = 스킵
	skipCurrent(Kind::Assignment);

	// 변수 초기화 식 구문 분석
	result->expression = parseExpression();

	if (result->expression == nullptr)
	{
		cout << "변수 선언에 초기화식이 없습니다.";
		exit(1);
	}
	skipCurrent(Kind::Semicolon);
	return result;
}

auto parseOr() -> Expression *
{
	auto result = parseAnd();

	while (skipCurrentIf(Kind::LogicalOr))
	{
		auto temp = new Or();
		temp->lhs = result;
		temp->rhs = parseAnd();
		result = temp;
	}
	return result;
}

auto skipCurrent(Kind kind) -> void
{
	if (current->kind != kind)
	{
		cout << toString(kind) + " 토큰이 필요합니다.";
	}
	current++;
}

auto skipCurrentIf(Kind token_kind) -> bool
{
	if (current->kind != token_kind)
		return false;
	current++;
	return true;
}