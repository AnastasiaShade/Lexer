#include <string>
#include <vector>
#include "consts.h"
#include <iostream>

class CLexer
{
public:
	CLexer();
	~CLexer() = default;

	void FindTokens(std::string line);
	std::vector<std::string> GetTokens();
	std::vector<std::string> GetTokenTypes();

private:
	
	std::string GetToken(size_t & it, std::string & line);
	std::string GetChars(char quote, std::string & line, size_t &it);
	std::string GetIdentificator(std::string & line, size_t & it);
	std::string GetNumber(std::string & line, size_t & it);
	std::string GetOperator(std::string & line, size_t & it);
	std::string GetTokenType(std::string & token);
	void SkipComment(size_t & it, std::string & line);
	bool IsString(std::string & token);
	bool IsChar(std::string & token);
	bool IsIdentificator(std::string & token);
	bool IsNumber(std::string & token);
	bool IsStartsLikeNumber(size_t it, std::string & token);
	bool HaveOtherBase(size_t it, std::string & token);
	bool IsValidNumberSymbol(size_t it, std::string & token);
	bool CheckBase(std::string & token, const std::vector<char> &baseValues, const std::string &pref);
	std::string GetNumberType(std::string & token);
	std::string GetDecimalNumberType(std::string &token);

	unsigned int m_line;
	bool m_isBlockComment;
	bool m_isLineComment;
	std::vector<std::string> m_tokens;
	std::vector<std::string> m_values;
};
