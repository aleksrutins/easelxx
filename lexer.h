#pragma once

namespace easel::lexer {
	using ValueType = std::variant<std::string, double>;

	enum TokenType {
		LeftParen,
		RightParen,
		LeftBrace,
		RightBrace,
		LeftBracket,
		RightBracket,
		Period,
		Comma,
		Colon,
		Keyword,
		Identifier,
		String,
		Number,
		Or,
		Not,
		And,
		Equiv,
		NotEquiv,
		Gt,
		Gte,
		Lt,
		Lte,
		Plus,
		Minus,
		Asterisk,
		Slash,
		$EOF
	};

	class Token {
	public:
		TokenType type;
		std::optional<std::string> value;
		std::optional<ValueType> content;
		int line;
		int column;

		Token(TokenType type, std::optional<std::string> value, std::optional<std::string> content, int line, int column)
			: type(type)
			, value(value)
			, content(content)
			, line(line)
			, column(column) {}

		inline operator std::string() const {
			return value.value_or("");
		}
	};

	class Lexer {
		std::string program;
		std::vector<Token> tokens;
		int current;
		int line;
		int column;
	public:
		Lexer(std::string program)
			: program(program)
			, tokens()
			, current(0)
			, line(1)
			, column(0) {}

		void Error(std::string message);

		char Peek();
		char Advance();
		auto Match(char) -> std::optional<char>;
		auto ScanToken() -> std::size_t;
		auto ScanTokens() -> std::vector<Token>;
	};
}