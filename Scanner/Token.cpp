#include <map>
#include "Token.h"

using std::map;

static map<string, Kind> stringToKind = {
		{"#unknown", Kind::Unknown},
		{"#EndOfToken", Kind::EndOfToken},

		{"null", Kind::NullLiteral},
		{"true", Kind::TrueLiteral},
		{"false", Kind::FalseLiteral},
		{"#Number", Kind::NumberLiteral},
		{"#String", Kind::StringLiteral},
		{"#identifier", Kind::Identifier},

		{"function", Kind::Function},
		{"return", Kind::Return},
		{"var", Kind::Variable},
		{"for", Kind::For},
		{"break", Kind::Break},
		{"continue", Kind::Continue},
		{"if", Kind::If},
		{"elif", Kind::Elif},
		{"else", Kind::Else},
		{"print", Kind::Print},
		{"printLine", Kind::PrintLine},

		{"and", Kind::LogicalAnd},
		{"or", Kind::LogicalOr},

		{"=", Kind::Assignment},

		{"+", Kind::Add},
		{"-", Kind::Subtract},
		{"*", Kind::Multiply},
		{"/", Kind::Divide},
		{"%", Kind::Modulo},

		{"==", Kind::Equal},
		{"!=", Kind::NotEqual},
		{"<", Kind::LessThan},
		{">", Kind::GreaterThan},
		{"<=", Kind::LessOrEqual},
		{">=", Kind::GreaterOrEqual},

		{",", Kind::Comma},
		{":", Kind::Colon},
		{";", Kind::Semicolon},
		{"(", Kind::LeftParen},
		{")", Kind::RightParen},
		{"{", Kind::LeftBrace},
		{"}", Kind::RightBrace},
		{"[", Kind::LeftBracket},
		{"]", Kind::RightBracket},
};

// 식별자인지, 키워드인지 체크한다.
// 식별자는 유저가 정한 이름이다.
auto toKind(string string) -> Kind
{
	if (stringToKind.count(string))
		return stringToKind.at(string);
	return Kind::Unknown;
}
