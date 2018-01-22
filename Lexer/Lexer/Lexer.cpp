#include "stdafx.h"
#include "Lexer.h"

CLexer::CLexer()
	:m_isBlockComment(false)
	, m_line(++m_line)
	, m_isLineComment(false)
{

}

void CLexer::FindTokens(std::string line)
{
	m_tokens.clear();
	m_values.clear();
	bool isError = false;
	size_t it = 0;

	while (it < line.length())
	{
		std::string element = GetToken(it, line);
		if (!element.empty())
		{
			std::string type = GetTokenType(element);
			if (type == STRING_TOKEN || type == CHAR_TOKEN)
			{
				element.erase(0, 1);
				element.erase(element.length() - 1, 1);
			}
			if (type == LINE_COMMENT || m_isBlockComment)
			{
				return;
			}
			if (type == OPEN_BLOCK_COMMENT)
			{
				SkipComment(it, line);
				continue;
			}
			m_tokens.push_back(type);
			m_values.push_back(element);
		}
	}
}

std::vector<std::string> CLexer::GetTokens()
{
	return m_values;
}

std::vector<std::string> CLexer::GetTokenTypes()
{
	return m_tokens;
}

std::string CLexer::GetToken(size_t & it, std::string & line)
{
	std::string result = "";
	if (std::find(SEPARATOR_VALUES.begin(), SEPARATOR_VALUES.end(), line[it]) == SEPARATOR_VALUES.end() && line[it] != DOT_VALUE)
	{
		if (line[it] != WHITESPACE)
		{
			result = isdigit(line[it]) ? GetNumber(line, it) : GetIdentificator(line, it);
		}
		else
		{
			++it;
		}
	}
	else
	{
		result = (line[it] == CHAR_QUOTE_VALUE || line[it] == STRING_QUOTE_VALUE) ? GetChars(line[it], line, it) : GetOperator(line, it);
	}
	return result;
}


std::string CLexer::GetChars(char quote, std::string & line, size_t &it)
{
	std::string value = "";
	value += quote;
	++it;
	while (it < line.length() && ((line[it - 1] == SCREENING_VALUE && line[it] == quote) || line[it] != quote))
	{
		value += line[it];
		++it;
	}
	value += quote;
	++it;
	return value;
}

std::string CLexer::GetIdentificator(std::string & line, size_t & it)
{
	std::string value = "";
	while (it < line.length() && (find(SEPARATOR_VALUES.begin(), SEPARATOR_VALUES.end(), line[it]) == SEPARATOR_VALUES.end() && line[it] != DOT_VALUE) && line[it] != WHITESPACE)
	{
		value += line[it];
		++it;
	}
	return value;
}

std::string CLexer::GetNumber(std::string & line, size_t & it)
{
	std::string value = "";
	while (it < line.length() && find(SEPARATOR_VALUES.begin(), SEPARATOR_VALUES.end(), line[it]) == SEPARATOR_VALUES.end() && line[it] != WHITESPACE)
	{
		value += line[it];
		++it;
	}
	return value;
}

std::string CLexer::GetOperator(std::string & line, size_t & it)
{
	std::string value = "";
	while (it < line.length() && (find(SEPARATOR_VALUES.begin(), SEPARATOR_VALUES.end(), line[it]) != SEPARATOR_VALUES.end() || line[it] == DOT_VALUE) && TOKENS.find(value + line[it]) != TOKENS.end()
		&& line[it] != WHITESPACE)
	{
		value += line[it];
		++it;
	}
	return value;
}

std::string CLexer::GetTokenType(std::string & token)
{
	if (TOKENS.find(token) != TOKENS.end())
	{
		return TOKENS.find(token)->second;
	}
	if (IsString(token))
	{
		return STRING_TOKEN;
	}
	if (IsChar(token))
	{
		return CHAR_TOKEN;
	}
	if (IsIdentificator(token))
	{
		return ID_TOKEN;
	}
	if (IsNumber(token))
	{
		return GetNumberType(token);
	}
	return ERROR;
}

void CLexer::SkipComment(size_t & it, std::string & line)
{
	size_t nextPos = line.find(CLOSE_BLOCK_COMMENT_VALUE, it);
	m_isBlockComment = (nextPos == std::string::npos) ? true : false;
	it = nextPos + 2;
}

bool CLexer::IsString(std::string & token)
{
	return (*token.begin() == STRING_QUOTE_VALUE && *(token.rbegin()) == STRING_QUOTE_VALUE);
}

bool CLexer::IsChar(std::string & token)
{
	return (*token.begin() == CHAR_QUOTE_VALUE && *(token.rbegin()) == CHAR_QUOTE_VALUE);
}

bool CLexer::IsIdentificator(std::string & token)
{
	for (size_t it = 0; it < token.length(); ++it)
	{
		if ((it == 0 && !isalpha(token[it])) || (!isalpha(token[it]) && !isdigit(token[it])))
		{
			return false;
		}
	}
	return true;
}

bool CLexer::IsNumber(std::string & token)
{
	for (size_t it = 0; it < token.length(); ++it)
	{
		if (it == 0 && !IsStartsLikeNumber(it, token))
		{
			return false;
		}
		else if (!IsValidNumberSymbol(it, token) && !HaveOtherBase(it, token))
		{
			return false;
		}
	}
	return true;
}

bool CLexer::IsStartsLikeNumber(size_t it, std::string & token)
{
	return it == 0 && isdigit(token[it]);
}

bool CLexer::HaveOtherBase(size_t it, std::string & token)
{
	return it == 1 && (token.find(HEX_NUMBER_PREF) == 0 || token.find(BIN_NUMBER_PREF) == 0 || token.find(OCT_NUMBER_PREF) == 0)
		|| find(AVALIABLE_FOR_HEX.begin(), AVALIABLE_FOR_HEX.end(), toupper(token[it])) != AVALIABLE_FOR_HEX.end();
}

bool CLexer::IsValidNumberSymbol(size_t it, std::string & token)
{
	return (it == token.length() - 1 && (token[it] == FLOAT_END || token[it] == DOUBLE_END))
		|| (token[it] == DOT_VALUE) || isdigit(token[it]);
}

std::string CLexer::GetNumberType(std::string & token)
{
	if (CheckBase(token, AVALIABLE_FOR_BIN, BIN_NUMBER_PREF))
	{
		return BIN_NUMBER_TOKEN;
	}

	if (CheckBase(token, AVALIABLE_FOR_OCT, OCT_NUMBER_PREF))
	{
		return OCT_NUMBER_TOKEN;
	}

	if (CheckBase(token, AVALIABLE_FOR_HEX, HEX_NUMBER_PREF))
	{
		return HEX_NUMBER_TOKEN;
	}

	return GetDecimalNumberType(token);
}

bool CLexer::CheckBase(std::string & token, const std::vector<char> &baseValues, const std::string &pref)
{
	int delimeterCounter = 0;
	if (token.find(pref) == 0)
	{
		for (size_t it = 2; it < token.length(); ++it)
		{
			if (token[it] == DOT_VALUE)
			{
				++delimeterCounter;
			}
			if (find(baseValues.begin(), baseValues.end(), toupper(token[it])) == baseValues.end() || delimeterCounter > 1)
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

std::string CLexer::GetDecimalNumberType(std::string &token)
{
	int delimeterCounter = 0;

	for (size_t it = 0; it < token.length(); ++it)
	{
		if (!isdigit(token[it]))
		{
			if (token[it] == DOT_VALUE)
			{
				++delimeterCounter;
			}
			else if (it == token.size() - 1 && token[it] == FLOAT_END)
			{
				return FLOAT_TOKEN;
			}
			else if (it == token.size() - 1 && token[it] == DOUBLE_END)
			{
				return DOUBLE_TOKEN;
			}
			else
			{
				return ERROR;
			}
			if (delimeterCounter > 1)
			{
				return ERROR;
			}
		}
	}
	return (delimeterCounter == 0) ? INT_TOKEN : FLOAT_TOKEN;
}

