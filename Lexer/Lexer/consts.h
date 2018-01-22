#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <map>

static const char STRING_QUOTE_VALUE = '\"';
static const char CHAR_QUOTE_VALUE = '\'';
static const char SCREENING_VALUE = '\\';
static const std::string LINE_COMMENT = "line comment";
static const std::string OPEN_BLOCK_COMMENT = "opening block comment";
static const std::string CLOSE_BLOCK_COMMENT = "closing block comment";
static const std::string CLOSE_BLOCK_COMMENT_VALUE = "*/";
static const char WHITESPACE = ' ';

const std::map<std::string, std::string> TOKENS = { { "int", "keyword" },{ "float", "keyword" },{ "double", "keyword" },{ "bool", "keyword" },{ "string", "keyword" },{ "char", "keyword" },
{ "void", "keyword" },{ "class", "keyword" },{ "public", "keyword" },{ "private", "keyword" },{ "protected", "keyword" },{ "final", "keyword" },{ "static", "keyword" },{ "extends", "keyword" },
{ "implements", "keyword" },{ "try", "keyword" },{ "catch", "keyword" },{ "finally", "keyword" },{ "while", "keyword" },{ "if", "keyword" },{ "for", "keyword" },{ "do", "keyword" },{ "throw", "keyword" },
{ "throws", "keyword" },{ "new", "keyword" },{ "delete", "keyword" },{ "return", "keyword" },{ "struct", "keyword" },{ "enum", "keyword" },{ "true", "boolean" },{ "false", "boolean" },{ "+", "operator" },
{ "-", "operator" },{ "*", "operator" },{ "/", "operator" },{ "=", "operator" },{ "!", "operator" },{ "<", "operator" },{ ">", "operator" },{ "%", "operator" },{ "%=", "operator" },{ "+=", "operator" },
{ "-=", "operator" },{ "*=", "operator" },{ "/=", "operator" },{ "==", "operator" },{ "!=", "operator" },{ "<=", "operator" },{ ">=", "operator" },{ "?", "operator" },{ "++", "operator" },
{ "--", "operator" },{ "\"", "string quote" },{ "\'", "char quote" },{ ";", "semicilon" },{ ",", "comma" },{ ":", "colon" },{ "(", "opening bracket" },{ ")", "closing bracket" },
{ "[", "opening square bracket" },{ "]", "closing square bracket" },{ "{", "opening block bracket" },{ "}", "closing block bracket" },{ "//", "line comment" },{ "/*", "opening block comment" },
{ "*/", "closing block comment" },{ "NULL", "keyword" },{ "null", "keyword" },{ ".", "dot" }
};

static const std::string INT_TOKEN = "integer";
static const std::string FLOAT_TOKEN = "float";
static const std::string DOUBLE_TOKEN = "double";
static const std::string BIN_NUMBER_TOKEN = "bin number";
static const std::string OCT_NUMBER_TOKEN = "oct number";
static const std::string HEX_NUMBER_TOKEN = "hex number";
static const std::vector<char> AVALIABLE_FOR_BIN = { '0', '1' };
static const std::vector<char> AVALIABLE_FOR_OCT = { '0', '1', '2', '3', '4', '5', '6', '7' };
static const std::vector<char> AVALIABLE_FOR_HEX = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
static const std::string BIN_NUMBER_PREF = "0b";
static const std::string OCT_NUMBER_PREF = "0c";
static const std::string HEX_NUMBER_PREF = "0h";
static const char FLOAT_END = 'f';
static const char DOUBLE_END = 'd';

static const std::string ID_TOKEN = "identificator";
static const std::string STRING_TOKEN = "string";
static const std::string CHAR_TOKEN = "character";
static const std::string DOT_TOKEN = "dot";
static const char DOT_VALUE = '.';
static const std::string ERROR = "error";
static const std::string EOF_TOKEN = "EOF";

static const std::vector<char> SEPARATOR_VALUES = { '+', '-', '*', '/', '=', '<', '>', '!', ';', ',', ':', '(', ')', '[', ']', '{', '}', '\"', '\'', '%' };