#include "RegExp.h"




namespace mtk {


RegExp::RegExp(int options)
{
	Clear();
	SetOptions(options);
}

RegExp::RegExp(const char * p, int options)
{
	Clear();
	SetOptions(options);
	SetPattern(p);
}

RegExp::RegExp(const std::string &p, int options)
{
	Clear();
	SetOptions(options);
	SetPattern(p);
}

RegExp::~RegExp()
{
	Clear(true);
}

void RegExp::Clear(bool freemem)
{
	if(freemem && cpattern)
		pcre_free(cpattern);

	first = false;
	cpattern = NULL;
	rc = 0;
	compile_options = 0;
	execute_options = 0;
	error_code = 0;
}

void RegExp::SetOptions(int options)
{
	if(options & UNICODE)
		compile_options |= UNICODE;
	if(options & CASELESS)
		compile_options |= CASELESS;
	if(options & UNGREEDY)
		compile_options |= UNGREEDY;
	if(options & MULTILINE)
		compile_options |= MULTILINE;
	if(options & PARTIAL)
		execute_options = PARTIAL;
}

void RegExp::SetPattern(const char * p)
{
	pattern = p;
}

void RegExp::SetPattern(const std::string &p)
{
	pattern = p;
}

bool RegExp::Compile(bool recompile)
{
	if(cpattern)
	{
		if(recompile)
			pcre_free(cpattern);
		else
			return true;
	}
	cpattern = pcre_compile2(pattern.c_str(), compile_options, &error_code, &error_string, &error_offset, NULL);
	return error_code == 0;
}

int RegExp::Execute(const std::string &t, int offset)
{
    rc = pcre_exec(cpattern, NULL, t.c_str(), int(t.size()), offset, execute_options, pos, 30);
    if(rc <= 0)
	first = false;
    return rc;
}

bool RegExp::Match(const std::string &t, bool copy)
{
	if(copy)
		text = t;
	if(!Compile())
		return false;
	return Execute(t) > 0;
}

bool RegExp::FastMatch(const std::string &t)
{
	return Match(t, false);
}

bool RegExp::GlobalMatch(const std::string &t)
{
	if(!first)
	{
		first = true;
		return Match(t);
	}
	int offset = pos[1];
	if(pos[0] == pos[1])
	{
		if(unsigned(pos[0]) == t.size())
		{
			first = false;
			return false;
		}
		execute_options |= PCRE_NOTEMPTY | PCRE_ANCHORED;
	}
	return Execute(t, offset) > 0;
}

std::string RegExp::operator[](const int i)
{
	return GetString(i);
}

int RegExp::GetCount() const
{
	return rc - 1;
}

mtk::vector<std::string> RegExp::GetStrings()
{
	mtk::vector<std::string> subs;
	for(int i = 0; i < GetCount(); i++)
		subs.push_back(GetString(i));
	return subs;
}

std::string RegExp::GetString(int i)
{
	i = 2 * (i + 1);
	return text.substr(pos[i], pos[i + 1] - pos[i]);
}



};      //  namespace mtk {
