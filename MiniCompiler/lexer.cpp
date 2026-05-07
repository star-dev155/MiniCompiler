// The code below defines the implementation of the Lexer class for a mini compiler. The Lexer class is responsible for taking a source string and breaking it down into a sequence of tokens that represent the basic elements of the programming language, such as identifiers, numbers, keywords, and operators. The implementation includes methods for advancing through the source string, skipping whitespace, and recognizing identifiers and numbers.
// This mini compiler lexer supports basic arithmetic operators, assignment, and simple keywords like "let" and "print". The tokenize method processes the input source code and generates a vector of tokens that can be used for further stages of compilation, such as parsing and code generation.

#include "lexer.h"
#include <cctype>

namespace MiniCompiler
{
	Lexer::Lexer(const std::string& source) : source(source), position(0) {}

	std::vector<Token> Lexer::tokenize() {
		std::vector<Token> tokens;
		while (position < source.size()) {
			skipWhitespace();
			if (position >= source.size()) break;
			char current = currentChar();
			if (std::isalpha(current)) {
				tokens.push_back(identifier());
			}
			else if (std::isdigit(current)) {
				tokens.push_back(number());
			}
			else {
				switch (current) {
				case '+': tokens.push_back({ TokenType::Plus, "+" }); advance(); break;
				case '-': tokens.push_back({ TokenType::Minus, "-" }); advance(); break;
				case '*': tokens.push_back({ TokenType::Star, "*" }); advance(); break;
				case '/': tokens.push_back({ TokenType::Slash, "/" }); advance(); break;
				case '=': tokens.push_back({ TokenType::Equal, "=" }); advance(); break;
				case ';': tokens.push_back({ TokenType::Semicolon, ";" }); advance(); break;
				case '(': tokens.push_back({ TokenType::LeftParen, "(" }); advance(); break;
				case ')': tokens.push_back({ TokenType::RightParen, ")" }); advance(); break;
				default:
					tokens.push_back({ TokenType::Unknown, std::string(1, current) });
					advance();
					break;
				}
			}
		}
		tokens.push_back({ TokenType::EndOfFile, "" });
		return tokens;
	}
	char Lexer::currentChar() const {
		return position < source.size() ? source[position] : '\0';
	}
	void Lexer::advance() {
		if (position < source.size()) position++;
	}
	void Lexer::advance(size_t steps) {
		position += steps;
		if (position > source.size()) position = source.size();
	}
	void Lexer::skipWhitespace() {
		while (position < source.size() && std::isspace(currentChar())) {
			position++;
		}
	}
	Token Lexer::identifier() {
		size_t start = position;
		while (position < source.size() && std::isalnum(currentChar())) {
			position++;
		}
		std::string value = source.substr(start, position - start);
		if (value == "let") return { TokenType::Let, value };
		if (value == "print") return { TokenType::Print, value };
		return { TokenType::Identifier, value };
	}

	Token Lexer::number() {
		size_t start = position;
		while (position < source.size() && std::isdigit(static_cast<unsigned char>(currentChar()))) {
			position++;
		}
		// Optionally handle decimals: if (currentChar() == '.') ...
		std::string value = source.substr(start, position - start);
		return { TokenType::Number, value };
	}
}