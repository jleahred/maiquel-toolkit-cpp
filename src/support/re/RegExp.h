#ifndef _PcreTest_RegExp_h_
#define _PcreTest_RegExp_h_




//  esto está adaptado del plugin de pcre de ultimate++
//  10/12/2008
//  se han realizado modificaciones en la librería pcre
//  no se utiliza el nuevo warper c++ oficial de pcre (desarrollado por google)
//  puede que se utilice en el futuro


#define PCRE_STATIC
#include "pcre/pcre.h"


#include "support/vector.hpp"


#include <string>






namespace mtk {


class RegExp /*: public Moveable<RegExp> */ {
public:
	enum
	{
		PARTIAL   = PCRE_PARTIAL,
		/* compile options */
		UNICODE   = PCRE_UTF8,
		CASELESS  = PCRE_CASELESS,
		MULTILINE = PCRE_MULTILINE,
		UNGREEDY  = PCRE_UNGREEDY
	};

private:
	std::string pattern;
	std::string text;
	pcre * cpattern;
	const char * error_string;
	int error_offset;
	int error_code;
	int pos[30];
	int rc;
	bool first;
	int compile_options;
	int execute_options;

public:
	RegExp(int options = UNICODE);
	RegExp(const char * p, int options = UNICODE);
	RegExp(const std::string &p, int options = UNICODE);
	~RegExp();

	void Clear(bool freemem = false);
	void SetOptions(int options);
	void SetPattern(const char * p);
	void SetPattern(const std::string &p);
	bool Compile(bool recompile = false);
	int  Execute(const std::string &t, int offset = 0);
	bool Match(const std::string &t, bool copy = true);
	bool FastMatch(const std::string &t);
	bool GlobalMatch(const std::string &t);
	std::string operator[](const int i);
	int GetCount()  const;
	mtk::vector<std::string> GetStrings();
	std::string GetString(int i);

	bool IsError() const { return error_code != 0; }
	const char * GetError() const { return error_string; }
	int GetErrorCode()      const { return error_code; }
};



};      //  namespace mtk {

#endif
