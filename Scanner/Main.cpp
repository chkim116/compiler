#include "Main.h"

// TODO: scan 출력
auto scan(string) -> vector<Token>;

auto main() -> void
{
	// TODO: 코드 주입
	string sourceCode = "코드";

	auto tokenList = scan(sourceCode);
	printTokenList(tokenList);
}

// 반환된 토큰 리스트 출력
auto printTokenList(vector<Token> tokenList) -> void
{
	cout << setw(12) << left << "KIND"
			 << "STRING" << endl;
	cout << string(23, '-') << endl;
	for (auto &token : tokenList)
		cout << token << endl;
}