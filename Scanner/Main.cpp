#include "Main.h"

auto main(int argc, char **argv) -> int
{
	string sourceCode = R""""(
		function main() {
			print 'Hello, World!';
			printLine 1234;
		}
	)"""";

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