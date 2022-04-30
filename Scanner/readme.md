# 어휘 분석 (Scanner)
- 어휘 분석이란 프로그래밍 언어로 작성한 소스 코드의 문자열을 분석하는 과정이다.
- 문자열이란 키워드, 식별자, 연산자, 구분자, 숫자 리터럴, 문자열 리터럴로 구성된다.

## 어휘와 토큰
- 어휘 분석을 위하여 가장 먼저 해야 할 일은 소스 코드에 사용되는 어휘들을 정의하는 것이다.

Kind.h 파일에 사용할 어휘들을 정의한다. 열거형인 `enum`을 사용한다. Kind.cpp 파일에서는 Kind.h에서 정의된 열거형 멤버들과 어휘 문자열들을 연관 시킨다. 이러한 어휘의 종류와 문자열을 묶어 **토큰**이라고 한다. 예를 들어 키워드 for 토큰의 **문자열은 for**이고, **종류는 Kind::For**이다.

## 어휘 분석
- 어휘들을 정의하는 게 끝났으면, 어휘 분석의 결과를 다룰 수 있도록 구조체를 구현한다.

토큰 구조체를 작성해 보자. 어휘 분석의 결과는 토큰 구조체의 리스트가 된다. 방금 전에 만든 Kind.* 파일들은 이제 Token.*로 변경한다.

```cpp
// Token.cpp -> Token.cpp

// .. 이전 로직 동일

struct Token {
	Kind kind = Kind::Unknown;
	string string;
}
```
어휘 분석이란 소스 코드 문자열에 포함된 어휘들을 분석하는 것이고, 토큰은 분석된 어휘의 문자열과 종류의 쌍을 의미한다. 즉 **어휘 분석은 소스 코드를 입력받아 토큰 리스트를 출력하는 행위**이다.

토큰 구조체를 만들었으니, 이 구조체를 활용해 토큰들을 스캔하는 함수를 만들어 보자.

```cpp
auto main() -> void
{
	string sourceCode = "코드";

	auto tokenList = scan(sourceCode);
	printTokenList(tokenList);
}
```

`scan()`로 소스 코드를 스캔하면, `printTokenList()`가 콘솔창에 출력하도록 한다.
아직은 미구현이므로 결과물은 확인할 수 없다.

## 스캔
- 스캔이란 소스 코드 문자열을 처음부터 끝까지 문자 단위로 순회하여 토큰 리스트에 토큰을 추가하는 과정이다.

기본적으로 `scan()` 함수에서는 소스 코드 문자열을 처음부터 끝까지 문자 단위로 순회하며 토큰 리스트에 토큰을 추가한다. 그리고 순회가 끝나면 `EndOfToken` 토큰을 추가한 후 토큰 리스트를 반한한다.

```cpp
// Scanner.cpp

// 현재 문자를 가리키는 전역 변수
static string::iterator current;

auto scan(string sourceCode) -> vector<Token>
{
	vector<Token> result;
	sourceCode += '\0';
	current = sourceCode.begin();
	while (*current != '\0')
	{
		// 이곳에서 문자열들을 체크할 예정이다.
	}
	result.push_back({Kind::EndOfToken});
	return result;
}
```

`scan()` 안에 있는 `while`문에서 토큰을 검사하는 로직을 수행한다. 이를 위해 switch 문법으로 각각 토큰 리스트를 취하도록 한다.

현 예제에서는 사용할 수 없는 문자, 공백-탭-개행, 숫자 리터럴, 문자열 리터럴, 식별자-키워드, 연산자-구분자를 찾아낸다.

```cpp
enum class CharType
{
	Unknown,							 // 사용할 수 없는 문자
	WhiteSpace,						 // 공백, 탭, 개행
	NumberLiteral,				 // 숫자 리터럴
	StringLiteral,				 // 문자 리터럴
	IdentifierAndKeyword,	 // 식별자, 키워드
	OperatorAndPunctuator, // 연산자, 구분자
};
```
어휘 분석의 핵심은 반복문을 통하여 입력된 값이 어떤 토큰에 해당하는지 체크하는 것이라 볼 수 있다.

코드는 `Scanner.cpp`에서 확인할 수 있다.


## 토큰 리스트 출력
다음과 같은 소스 코드를 출력해보자.

```cpp
auto main(int argc, char **argv) -> int
{
	string sourceCode = R""""(
		function main() {
			print 'Hello, World!';
			printLine 1234;
		}
	)"""";

	// 스캔하고
	auto tokenList = scan(sourceCode);

	// 출력한다.
	printTokenList(tokenList);
}
```

다음 같이 콘솔창에 출력된다.

```
KIND        STRING
-----------------------
function    function
#identifier main
(           (
)           )
{           {
print       print
#String     Hello, World!
;           ;
printLine   printLine
#Number     1234
;           ;
}           }
#EndOfToken 
```

-> binary 관련 에러가 나타날 수 있다. 이때는 `Token.cpp` 파일 밑에 다음과 같은 함수를 추가해 준다. include도 빼먹지 말자.

```cpp
// Token.cpp
static auto kindToString = []
{
	map<Kind, string> result;
	for (auto &[key, value] : stringToKind)
		result[value] = key;
	return result;
}();

auto toString(Kind type) -> string
{
	if (kindToString.count(type))
		return kindToString.at(type);
	return "";
}

auto operator<<(ostream &stream, Token &token) -> ostream &
{
	return stream << setw(12) << left << toString(token.kind) << token.string;
}
```


---

어휘 분석에 대해 정리해보자면 다음과 같은 특징이 있다.

1. 어휘 분석은 컴파일 과정의 첫 단계이다.
2. 소스 코드 문자열을 분석하는 것이다.
3. 문자열이란 어휘들의 나열이다.
4. 어휘에는 식별자, 키워드, 연산자, 구분자, 숫자 리터럴, 문자열 리터럴이 있다.
5. 어휘 분석기의 입력은 소스 코드 문자열이고, 출력은 토큰 리스트다.