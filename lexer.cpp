using namespace std;

namespace easel::lexer {
	void Lexer::Error(string msg) {
		throw runtime_error(std::format("Error on {}:{}: {}", line, column, msg));
	}
	char Lexer::Peek() {
		if (current >= program.size()) return 0;
		return program[current];
	}
	char Lexer::Advance()
	{
		if (current >= program.size()) return 0;
		column++;
		return program[current++];
	}
    auto Lexer::Match(char c) -> optional<char>
    {
        if(Peek() == c) return Advance();
		return nullopt;
    }
    auto Lexer::ScanToken() -> size_t
    {
		auto c = Advance();
		switch (c) {
		case '(': tokens.push_back({ LeftParen, "(", "(", line, column }); break;
		case ')': tokens.push_back({ RightParen, ")", ")", line, column }); break;
		case '{': tokens.push_back({ LeftBrace, "{", "{", line, column }); break;
		case '}': tokens.push_back({ RightBrace, "}", "}", line, column }); break;
		case '[': tokens.push_back({ LeftBracket, "[", "[", line, column }); break;
		case ']': tokens.push_back({ RightBracket, "]", "]", line, column }); break;
		case '.': tokens.push_back({ Period, ".", ".", line, column }); break;
		case '"':
		case '\'': {
			string str;
			while (Peek() != c) {
				str += Advance();
				if (Peek() == 0) {
					Error("Unexpected end of file; expected a closing quote");
				};
			}
			Advance(); // skip closing quote
			tokens.push_back(Token{ String, str, str, line, column }); 
			break;
		}
		case '|':
			if(Match('|').has_value()) tokens.push_back({ Or, "||", "||", line, column }); break;
		case '>': {
			if(Match('=').has_value()) tokens.push_back({ Gte, ">=", ">=", line, column });
			else tokens.push_back({ Gt, ">", ">", line, column }); 
			break;
		}
		case '<': {
			if(Match('=').has_value()) tokens.push_back({ Lte, "<=", "<=", line, column });
			else tokens.push_back({ Lt, "<", "<", line, column }); 
			break;
		}
		case '=':
			if(Match('=').has_value()) tokens.push_back({ Equiv, "==", "==", line, column }); break;
		case '&':
			if(Match('&').has_value()) tokens.push_back({ And, "&&", "&&", line, column }); break;
		case '!': {
			if(Match('=').has_value()) tokens.push_back({ NotEquiv, "!=", "!=", line, column });
			else tokens.push_back({ Not, "!", "!", line, column });
			break;
		}
		default:
			if(isdigit(c)) {
				string num({c});
				while(isdigit(Peek()) || (Peek() == '.' && num.find('.') != string::npos))
					num += Advance();

				string parsenum(num);
				if(parsenum.find('.') == string::npos) parsenum += ".0";
				
				tokens.push_back({ Number, num, atof(parsenum.c_str()), line, column});

			}
		}
		return tokens.size();
	}
	auto Lexer::ScanTokens() -> vector<Token>
	{
		while (Peek() != 0) ScanToken();
		tokens.push_back(Token{ $EOF, nullopt, nullopt, line, column });
		return tokens;
	}
}