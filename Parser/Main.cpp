#include "Main.h"

auto main(int argc, char **argv) -> int
{
	string sourceCode = R""""(
		function main() {
			printLine 'Hello, World!';
			printLine 1 + 2 * 3;
		}
	)"""";

	auto tokenList = scan(sourceCode);
	auto syntaxTree = parse(tokenList);

	printSyntaxTree(syntaxTree);
}