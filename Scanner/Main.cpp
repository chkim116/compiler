#include "Main.h"

auto main(int argc, char **argv) -> int
{
	// TODO: 코드 주입
	string sourceCode = R""""(
			function main() {
				print 'Hello, World!';
			}
			)"""";

	auto tokenList = scan(sourceCode);
	printTokenList(tokenList);
}

// 반환된 토큰 리스트 출력
auto printTokenList(vector<Token> tokenList) -> void
{
	cout << setw(12) << left << "KIND"
			 << "STRING" << '\n';
	cout << string(23, '-') << '\n';
	for (auto &token : tokenList)
		cout << token << '\n';
}