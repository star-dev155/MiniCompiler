// The code below defines a simple lexer for a mini compiler. It includes an enumeration for token types, a structure to represent a token, and a class to perform lexical analysis on a given source string. The lexer will tokenize the input source code into a vector of tokens that can be used for further processing in the compilation pipeline.

#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cstddef>

namespace MiniCompiler
{
	enum class TokenType
	{	
		Identifier,
		Number,
		Let,
		Print,
		Plus,
		Minus,
		Star,
		Slash,
		Equal,
		Semicolon,
		LeftParen,
		RightParen,
		EndOfFile,
		Unknown
	};

	struct Token
	{
		TokenType type;
		std::string value;
	};

	class Lexer {
	public:
		explicit Lexer(const std::string& source);

		std::vector<Token> tokenize();

	private:
		std::string source;
		size_t position;

		char currentChar() const;
		void advance();

		void advance(size_t steps);

		void skipWhitespace();

		Token identifier();
		Token number();
	};
}