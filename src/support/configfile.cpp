#include "configfile.h"
#include "support/mtk_string.h"
#include "support/alarm.h"
#include "support/re/RegExp.h"


#include <iostream>  // I/O
#include <fstream>   // file I/O
#include <iomanip>   // format manipulation

#define NOVALUE_SYMBOL   "~"

namespace mtk {


bool VerifyID(const std::string& id)
{
        mtk::RegExp re ("^([a-zA-Z0-9\\-_\\.]+)$");

        if (re.Match(id))
            return true;
        else
            return false;
}

bool VerifyValue(const std::string& val)
{
        if (    val.find_first_of("\n")!=std::string::npos  ||
                val.find_first_of("\r")!=std::string::npos  )
            return false;
        else
            return true;
}


std::string GetString2ParseFromFile(const std::string& fileName)
{
    char buffer[4096];
    std::ifstream fText2Transform(fileName.c_str(), std::ios::in);
    if (fText2Transform.is_open() == false)
        throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("problem opening file "), mtk::alPriorError);

    std::ostringstream ostext4parse;
    bool first = true;
    while (fText2Transform.getline(buffer, 4096))
    {
        if (!first)
            ostext4parse   << std::endl;
        first = false;
        //ostext4parse << std::string(buffer);
        ostext4parse << s_normalizeUTF8(std::string(buffer));
    }
    fText2Transform.close();

    return std::string(ostext4parse.str());
}



std::string ReplaceVariable (const std::string& value, const ConfigFile& cf)
{
	static int recdepth=0;		//	sé que no deben utilizar variables estáticas, aún así la utilizo y asumo toda responsabilidad

	++recdepth;
	std::string result = value;

	try
	{
		if (recdepth > 10)
		{
			throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("too depth recursion (" << recdepth <<")  " << value << " on file " << cf.GetFileName_current()), mtk::alPriorError);
		}

		mtk::RegExp re ("^([^$(]*)\\$\\(([^)]+)\\)(.*)$");

		while (re.Match(result))
		{
			mtk::Nullable<std::string> replaced = cf.GetValue(re.GetString(1));
			if (replaced.HasValue() == false)
				throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("value to replace " << re.GetString(1) << "doesn't exist"), mtk::alPriorError);
			else
				result = MTK_SS(re.GetString(0) << replaced.Get() << re.GetString(2));
		}
	}
	catch(...)
	{
		--recdepth;
		throw;
	}

	--recdepth;
	return result;
}






ConfigFile::ConfigFile(const std::string& _filename)
    : filename(_filename), is_loaded(false)
{
    try
    {
        const char* rules[] = {

            //"MAIN ",

            "MAIN     ::=  SECTION*   ",


            "SECTION  ::=  sep NAME sep { sep  INFO_SECTION*  sep }  sep       ##transf2->  $(NAME) ",


            "INFO_SECTION ::=  PROPERTY    endl ",
            "INFO_SECTION ::=  PROPERTY    endl ",
            "INFO_SECTION ::=  COMMENT     endl ",
            "INFO_SECTION ::=  BLANK_LINE  endl ",
            "INFO_SECTION ::=  SECTION        ",


            "PROPERTY ::= _ NAME _ : _ LIST  COMMENT ",
            "PROPERTY ::= _ NAME _ : _ LIST _   ",

            "PROPERTY ::= _ NAME _ : _ VALUE  COMMENT ",
            "PROPERTY ::= _ NAME _ : _ VALUE _   ",


            "VALUE  ::= !endl_or_#*   ",


            "LIST ::= sep [ sep LIST_ITEM* sep ] ",


            "LIST_ITEM ::= _ !endl_or_] !endl_or_]* endl   ##transf2->$(!endl_or_])$(!endl_or_]*) ",
            "LIST_ITEM ::= _ !endl_or_] !endl_or_]*        ##transf2->$(!endl_or_])$(!endl_or_]*) ",


            "BLANK_LINE  ::=  _   ",


            "NAME ::= id   ",
            "id        ::=  ([a-zA-Z0-9\\-_]+)   ",



            "COMMENT   ::=   _ # TILL_ENDL ",



            "TILL_ENDL ::=  !endl*   ",



            "{   ::= '{'   ",
            "}   ::= '}'   ",
            ":   ::= ':'   ",
            "#   ::= '#'   ",
            "_   ::= ([ \\t]*)   ",
            "[   ::= '[' ",
            "]   ::= ']' ",
            "sep ::= __isspace*__   ",


            "space           ::= __isspace__   ",
            "!endl_or_#       ::=  !([\\n\\r#])   ",
            "endl            ::=  __endl__   ",
            "!endl            ::=  !([\\n\\r])   ",
            "!endl_or_]       ::=  !([\\n\\r\\]])   ",





            "__END_RULES__"
        };


        //  cargar reglas
        for (int contador=0; rules[contador] != std::string("__END_RULES__"); ++contador)
        {
            bool result;
            std::string resultText;

            hParser.AddLine(rules[contador]).assign(result, resultText);
            if (result == false)
            {
                throw mtk::Alarm(MTK_HERE, "configfile", resultText, mtk::alPriorError);
            }

        }

        if (filename != "")
            LoadFromFile(filename);
    }
    MTK_CATCH_RETHROW("ConfigFile_ctor", MTK_SS("on file " << filename))
}


void ConfigFile::LoadFromFile(const std::string& _filename)
{
    try
    {
        is_loaded = false;
        filename = _filename;
        astConfigFile =  mtk::make_cptr(new mtk::AST_Node_Item(""));

        std::string text2parse = GetString2ParseFromFile(filename);

        //  parsing and transform
        bool parsingResult;
        std::string parsingResultText;
        hParser.Parse(text2parse, "MAIN").assign(parsingResult, parsingResultText, *astConfigFile);
        if (parsingResult == false)
            throw mtk::Alarm(MTK_HERE, "configfile", parsingResultText, mtk::alPriorError);

        //  rellenamos los nodos del árbol AST
        astConfigFile->ExecReplace();

        //  podamos los nodos del árbol y nos quedamos sólo con los siguientes
        mtk::list<std::string> lnodes2mantein;
        lnodes2mantein.push_back("SECTION*");
        lnodes2mantein.push_back("SECTION");
        lnodes2mantein.push_back("INFO_SECTION*");
        lnodes2mantein.push_back("INFO_SECTION");
        lnodes2mantein.push_back("PROPERTY");
        lnodes2mantein.push_back("COMMENT");
        lnodes2mantein.push_back("BLANK_LINE");
        lnodes2mantein.push_back("NAME");
        lnodes2mantein.push_back("VALUE");
        lnodes2mantein.push_back("LIST");
        lnodes2mantein.push_back("LIST_ITEM*");
        lnodes2mantein.push_back("LIST_ITEM");

        astConfigFile->RemoveNodesManteining(lnodes2mantein);
        is_loaded = true;
    } MTK_CATCH_RETHROW("CF_LoadFromFile", MTK_SS("on file " << filename))
}



mtk::tuple<bool, mtk::CountPtr<AST_Node_Item> > FindSectionFromKey (mtk::CountPtr<AST_Node_Item>  ast,   const std::string& key)
{
    if (ast->name == "MAIN")
    {
        ast = ast->down;
    }

    if (ast->name == "SECTION*")
    {
        ast = ast->down;
    }

    if (ast->name == "INFO_SECTION*")
    {
        ast = ast->down;
    }

    while (ast.isValid())
    {
        if (ast->name == "SECTION")
        {
            if(ast->down->name == "NAME"  &&  ast->down->value == key)
                return mtk::make_tuple(true, ast);
        }
        else if (ast->name == "INFO_SECTION")
        {
            if(ast->down->name == "SECTION")
            {
                if(ast->down->down->name == "NAME"  &&  ast->down->down->value == key)
                    return mtk::make_tuple(true, ast->down);
            }
        }
        ast = ast->next;
    }

    return make_tuple(false, ast);
}


mtk::tuple<bool, mtk::CountPtr<AST_Node_Item> > FindPropertyFromKey (mtk::CountPtr<AST_Node_Item>  ast,   const std::string& key)
{
    if (ast->name == "INFO_SECTION*")
    {
        ast = ast->down;
    }


    while (true)
    {
        if (ast->down->name == "PROPERTY")
        {
            if(ast->down->down->name == "NAME"  &&  ast->down->down->value == key)
                return mtk::make_tuple(true, ast->down);
        }
        if (ast->next.isValid()==false)
            break;
        ast = ast->next;
    }

    return make_tuple(false, ast);
}


mtk::tuple<bool, mtk::CountPtr<AST_Node_Item> > FindSectionFromKeys (mtk::CountPtr<AST_Node_Item> astNode,   const mtk::vector<std::string>& vsubkeys)
{
    for(unsigned i=0; i< vsubkeys.size(); ++i)
    {
        bool result = false;
        //  buscamos la sección
        FindSectionFromKey(astNode, vsubkeys[i]).assign(result, astNode);
        if (!result)
            return make_tuple(false, astNode);
        astNode = astNode->down->next;
    }
    return make_tuple(true, astNode);
}



/*
 * Los nodos tienen que estar.
 * Lo que puede no estar es la propiedad buscada
 *
 */
mtk::tuple<bool, mtk::CountPtr<AST_Node_Item> > FindPropertyFromKeys (mtk::CountPtr<AST_Node_Item> astNode,   const std::string& keys)
{
    mtk::vector<std::string>  vsubkeys = s_split(keys, ".");
    std::string               property = vsubkeys.back();
    vsubkeys.pop_back();

    bool result;
    FindSectionFromKeys(astNode, vsubkeys).assign(result, astNode);
    if (!result)
        return make_tuple(false, astNode);

    FindPropertyFromKey(astNode, property).assign(result, astNode);
    if(result)
        return make_tuple(true, astNode);
    else
        return make_tuple(false, astNode);
}


mtk::Nullable<std::string> ConfigFile::GetValue(const std::string& keys) const
{
    try
    {
        if (VerifyID(keys))
        {
            bool result;
            mtk::CountPtr<AST_Node_Item>  resultNode;
            FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

            if (result && resultNode->down->next->name != "VALUE")
                throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("it's not a value " << resultNode->down->next->name << "  on " << keys), mtk::alPriorError);

            if (result && (resultNode->down->next->value != ""))
            {
                if (resultNode->down->next->value==NOVALUE_SYMBOL)
                    return mtk::Nullable<std::string>("");
                else
                {
                    //  ponemos aquí el trim, porque no es práctico que se encargue el parser
                    return mtk::Nullable<std::string>(
                                    mtk::s_trim(ReplaceVariable (
                                                        resultNode->down->next->value, *this),
                                            " \t"));
                }
            }
        }
        return mtk::Nullable<std::string>();
    } MTK_CATCH_RETHROW("CF_GetValue", MTK_SS("on file " << filename << "  path:" << keys))
}

mtk::Nullable<mtk::list<std::string> > ConfigFile::GetList (const std::string& keys) const
{
    try
    {
        mtk::list<std::string> result_list;
        if (VerifyID(keys))
        {
            bool result;
            mtk::CountPtr<AST_Node_Item>  resultNode;
            FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

            if (result==false || (resultNode->down->next->value == ""))
                return mtk::Nullable<mtk::list<std::string> >();


            if (resultNode->down->next->name != "LIST")
                throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("it's not a value " << resultNode->down->next->name << "  on " << keys), mtk::alPriorError);

            {
                mtk::CountPtr<AST_Node_Item>  current_item = resultNode->down->next->down->down;
                while (current_item.isValid())
                {
                    result_list.push_back(mtk::s_trim(current_item->value, " \t"));
                    current_item = current_item->next;
                }
                if (result_list.size() == 1 && *result_list.begin() == NOVALUE_SYMBOL)
                    result_list.clear();
            }
        }
        return mtk::Nullable< mtk::list<std::string> >(result_list);
    } MTK_CATCH_RETHROW("CF_GetList", MTK_SS("on file " << filename<< "  path:" << keys))
}



void VerifModifParams(const std::string& keys, const std::string& value, const std::string& comment, const std::string& from)
{
    if (VerifyID(keys) == false)
        throw Alarm(MTK_HERE, from, MTK_SS("invalid id " << keys), mtk::alPriorError);
    if (VerifyValue(value) == false)
        throw Alarm(MTK_HERE, from, MTK_SS("invalid value " << value), mtk::alPriorError);
    if (VerifyValue(comment) == false)
        throw Alarm(MTK_HERE, from, MTK_SS("invalid comment " << comment), mtk::alPriorError);
}


void ModifListOfNode(const std::string& keys, mtk::CountPtr<AST_Node_Item> node, const mtk::list<std::string>& list)
{
    if (node->down->next->name != "LIST")
        throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("it's not a list " << node->down->next->name << " on " << keys), mtk::alPriorError);
    else
    {
        mtk::CountPtr<AST_Node_Item>  firstItem;
        mtk::CountPtr<AST_Node_Item>  lastItem;
        if (list.size() == 0)
            firstItem = make_cptr(new AST_Node_Item("LIST_ITEM", NOVALUE_SYMBOL));
        else
        {
            for(auto itItemList=list.begin(); itItemList!=list.end(); ++itItemList)
            {
                if (!firstItem.isValid())
                {
                    firstItem = make_cptr(new AST_Node_Item("LIST_ITEM", *itItemList));
                    lastItem = firstItem;
                }
                else
                {
                    lastItem->next = make_cptr(new AST_Node_Item("LIST_ITEM", *itItemList));
                    lastItem = lastItem->next;
                }
            }
        }
        node->down->next->down->down = firstItem;
    }
}



void ConfigFile::ModifList(const std::string& keys, const mtk::list<std::string>& list)
{
    try
    {
        VerifModifParams(keys, "", "cf::ModifList", "");

        bool result;
        mtk::CountPtr<AST_Node_Item>  resultNode;
        FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

        if (result== false)
            throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Doesn't exist property on  [" << keys << "]"), mtk::alPriorError);
        else
        {
            ModifListOfNode(keys, resultNode, list);
    //        if (resultNode->down->next->name != "LIST")
    //            throw mtk::Alarm("cf::ModifList", MTK_SS("it's not a list " << resultNode->down->next->name << " on " << keys), mtk::alPriorError);
    //        else
    //        {
    //            mtk::CountPtr<AST_Node_Item>  firstItem;
    //            mtk::CountPtr<AST_Node_Item>  lastItem;
    //            if (list.size() == 0)
    //                firstItem = make_cptr(new AST_Node_Item("LIST_ITEM", NOVALUE_SYMBOL));
    //            else
    //            {
    //                MTK_FOREACH_CONST_ITERATOR (itItemList, list)
    //                {
    //                    if (!firstItem.isValid())
    //                    {
    //                        firstItem = make_cptr(new AST_Node_Item("LIST_ITEM", *itItemList));
    //                        lastItem = firstItem;
    //                    }
    //                    else
    //                    {
    //                        lastItem->next = make_cptr(new AST_Node_Item("LIST_ITEM", *itItemList));
    //                        lastItem = lastItem->next;
    //                    }
    //                }
    //            }
    //            resultNode->down->next->down->down = firstItem;
    //        }
        }
    } MTK_CATCH_RETHROW("CF_ModifList", MTK_SS("on file " << filename << "  path:" << keys))
}




void ConfigFile::Modif(const std::string& keys, const std::string& value, const std::string& comment)
{
    try
    {
        VerifModifParams(keys, value, comment, "cf::Modif");

        bool result;
        mtk::CountPtr<AST_Node_Item>  resultNode;
        FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

        if (result== false)
            throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Doesn't exist property on  [" << keys << "]"), mtk::alPriorError);
        else
            if (value=="")
                resultNode->down->next->value = NOVALUE_SYMBOL;
            else
                resultNode->down->next->value = value;

    } MTK_CATCH_RETHROW("CF_Modif", MTK_SS("on file " << filename << "  path:" << keys))
}


void ConfigFile::ModifOrCreate(const std::string& keys, const std::string& value, const std::string& comment)
{
    try
    {
        VerifModifParams(keys, value, comment, "cf::ModifOrCreate");

        bool result;
        mtk::CountPtr<AST_Node_Item>  resultNode;
        FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

        if (result== false)
            if (value=="")
                Create(keys, NOVALUE_SYMBOL, comment);
            else
                Create(keys, value, comment);
        else
            if (value=="")
                resultNode->down->next->value = NOVALUE_SYMBOL;
            else
                resultNode->down->next->value = value;
    } MTK_CATCH_RETHROW("CF_ModifOrCreate", MTK_SS("on file " << filename << "  path:" << keys))
}


void ConfigFile::ModifOrCreateList(const std::string& keys, const mtk::list<std::string>& list)
{
    try
    {
        VerifModifParams(keys, "", "", "cf::ModifOrCreateList");

        bool result;
        mtk::CountPtr<AST_Node_Item>  resultNode;
        FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

        if (result== false)
            CreateList(keys, list);
        else
            ModifListOfNode(keys, resultNode, list);
    } MTK_CATCH_RETHROW("CF_ModifOrCreateList", MTK_SS("on file " << filename << "  path:" << keys))
}



void ConfigFile::Delete(const std::string& keys)
{
    try
    {
        if (VerifyID(keys))
        {
            bool result;
            mtk::CountPtr<AST_Node_Item>  resultNode;
            FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

            if (result  &&  resultNode->down->next->value!= "")
                resultNode->down->next->value = "";
            else
                throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Cannot delete on keys.property [" << keys << "]"), mtk::alPriorError);
        }
    } MTK_CATCH_RETHROW("CF_Delete", MTK_SS("on file " << filename<< "  path:" << keys))
}


void   ConfigFile::Create          (const std::string& keys, const std::string& value, const std::string& comment)
{
    try
    {
        if (value=="")
            throw mtk::Alarm(MTK_HERE, "configfile", "Emtpy value", mtk::alPriorError);

        VerifModifParams(keys, value, comment, "cf::Create");

        bool result;
        mtk::CountPtr<AST_Node_Item>  resultNode;
        FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

        if (result==false)
        {
            mtk::vector<std::string>  vsubkeys = s_split(keys, ".");
            //  comprobamos que no tratamos de escribir en una propiedad
            if (FindSectionFromKeys(astConfigFile, vsubkeys)._0 == true)
                throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Cannot write a property on a node [" << keys << "] "), mtk::alPriorError, mtk::alTypeNoPermisions);


            //  separamos nos nodos de la propiedad buscada
            std::string               key = vsubkeys.back();
            vsubkeys.pop_back();

            //  comprobamos que los nodos existen y sólo falta añadir la propiedad
            if (FindSectionFromKeys(astConfigFile, vsubkeys)._0 == false)
                throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Cannot create property with a node key [" << keys << "]   node doesn't exists"), mtk::alPriorError, mtk::alTypeNoPermisions);

            //  creamos la propiedad
            resultNode->next = make_cptr(new AST_Node_Item("INFO_SECTION"));

            resultNode->next->down = make_cptr(new AST_Node_Item("PROPERTY"));
            resultNode->next->down->down = make_cptr(new AST_Node_Item("NAME", key));

            if (value=="")
                resultNode->next->down->down->next = make_cptr(new AST_Node_Item("VALUE", NOVALUE_SYMBOL));
            else
                resultNode->next->down->down->next = make_cptr(new AST_Node_Item("VALUE", value));
        }
        else
            throw mtk::Alarm(MTK_HERE, "configfile", "On existing value", mtk::alPriorError);
    } MTK_CATCH_RETHROW("CF_Create", MTK_SS("on file " << filename << "  path:" << keys))
}



void   ConfigFile::CreateList   (const std::string& keys, const mtk::list<std::string>& list)
{
    try
    {
        VerifModifParams(keys, "", "", "cf::CreateList");

        bool result;
        mtk::CountPtr<AST_Node_Item>  resultNode;
        FindPropertyFromKeys(astConfigFile, keys).assign(result, resultNode);

        if (result==false)
        {
            mtk::vector<std::string>  vsubkeys = s_split(keys, ".");
            std::string               key = vsubkeys.back();

            if (FindSectionFromKeys(astConfigFile, vsubkeys)._0 == true)
                throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Cannot create property with a node key [" << keys << "]"), mtk::alPriorError, mtk::alTypeNoPermisions);

            resultNode->next = make_cptr(new AST_Node_Item("INFO_SECTION"));

            resultNode->next->down = make_cptr(new AST_Node_Item("PROPERTY"));
            resultNode->next->down->down = make_cptr(new AST_Node_Item("NAME", key));
            resultNode->next->down->down->next = make_cptr(new AST_Node_Item("LIST"));
            resultNode->next->down->down->next->down = make_cptr(new AST_Node_Item("LIST_ITEM*"));

            mtk::CountPtr<AST_Node_Item>  firstItem;
            mtk::CountPtr<AST_Node_Item>  lastItem;
            if (list.size() == 0)
                firstItem = make_cptr(new AST_Node_Item("LIST_ITEM", NOVALUE_SYMBOL));
            else
            {
                for(auto itItemList=list.begin();itItemList!=list.end(); ++itItemList)
                {
                    if (!firstItem.isValid())
                    {
                        firstItem = make_cptr(new AST_Node_Item("LIST_ITEM", *itItemList));
                        lastItem = firstItem;
                    }
                    else
                    {
                        lastItem->next = make_cptr(new AST_Node_Item("LIST_ITEM", *itItemList));
                        lastItem = lastItem->next;
                    }
                }
            }
            resultNode->next->down->down->next->down->down = firstItem;
        }
        else
            throw mtk::Alarm(MTK_HERE, "configfile", "On existing value", mtk::alPriorError);
    } MTK_CATCH_RETHROW("CF_CreateList", MTK_SS("on file " << filename << "  path:" << keys))
}




mtk::list<std::string>  ConfigFile::GetNodes      (const std::string& keys) const
{
    try
    {
        mtk::list<std::string>  result;
        mtk::CountPtr<AST_Node_Item> astNode;

        if(keys!="")
        {
            if (VerifyID(keys) == false)
                throw Alarm(MTK_HERE, "configfile", MTK_SS("invalid id " << keys), mtk::alPriorError);

            mtk::vector<std::string>  vsubkeys = s_split(keys, ".");

            bool bresult;
            FindSectionFromKeys(astConfigFile, vsubkeys).assign(bresult, astNode);
            if (!bresult)
                return result;

            astNode = astNode->down;        //  siempre tenemos que estar apuntando a un INFO_SECTION*
            //  ahora recorremos todos los INFO_SECTION
            while(astNode.isValid())
            {
                if (astNode->down->name == "SECTION")
                    result.push_back(astNode->down->value);
                astNode = astNode->next;
            }
        }
        else
        {
            astNode = astConfigFile->down->down;  //  apunta debajo de SECTION*   la lista de secciones
            //  ahora recorremos todos los SECTION
            while(astNode.isValid())
            {
                if (astNode->name == "SECTION")
                    result.push_back(astNode->down->value);
                astNode = astNode->next;
            }
        }
        return result;
    } MTK_CATCH_RETHROW("CF_GetNodes", MTK_SS("on file " << filename << "  path:" << keys))
}


mtk::list< mtk::tuple<std::string, ConfigFile::enPropertyType> >  ConfigFile::GetProperties (const std::string& keys) const
{
    try
    {
        mtk::list<mtk::tuple<std::string, ConfigFile::enPropertyType> >  result;
        mtk::CountPtr<AST_Node_Item> astNode;


        if(keys!="")
        {
            if (VerifyID(keys) == false)
                throw Alarm(MTK_HERE, "configfile", MTK_SS("invalid id " << keys), mtk::alPriorError);

            mtk::vector<std::string>  vsubkeys = s_split(keys, ".");

            bool bresult;
            FindSectionFromKeys(astConfigFile, vsubkeys).assign(bresult, astNode);
            if (!bresult)
                return result;

            astNode = astNode->down;        //  siempre tenemos que estar apuntando a un INFO_SECTION*
            //  ahora recorremos todos los INFO_SECTION
            while(astNode.isValid())
            {
                if (astNode->down->name == "PROPERTY")
                {
                    if (astNode->down->down->next->name == "VALUE")
                    {
                        if(astNode->down->down->next->value != "")
                            result.push_back( mtk::make_tuple(astNode->down->down->value, ptValue));  //   vamos hasta name
                    }
                    else if (astNode->down->down->next->name == "LIST")
                    {
                        result.push_back( mtk::make_tuple(astNode->down->down->value, ptList));  //   vamos hasta name
                    }
                    else
                        throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Invalid node type  " << astNode->down->down->next->name), mtk::alPriorError);
                }
                astNode = astNode->next;
            }
        }

        return result;
    } MTK_CATCH_RETHROW("CF_GetProperties", MTK_SS("on file " << filename << "  path:" << keys))
}




// void ConfigFile::debug_print(void)
// {

// }



std::string spaces(int number)
{
    std::string result;
    for(int i=0; i<number; i++)
        result += " ";
    return result;
}


void WriteNode(std::ostream& out, mtk::CountPtr<AST_Node_Item> node, int depth)
{
    if(node.isValid()==false)   return;

    if (node->name == "MAIN")
        WriteNode(out, node->down, depth);
    else if (node->name == "SECTION*")
    {
        node = node -> down;
        while (node.isValid())
        {
            WriteNode(out, node, depth);
            node = node->next;
        }
    }
    else if (node->name == "INFO_SECTION*")
    {
        node = node -> down;
        while (node.isValid())
        {
            WriteNode(out, node, depth);
            node = node->next;
        }
    }
    else if (node->name == "INFO_SECTION")
        WriteNode(out, node->down, depth);
    else if (node->name == "PROPERTY")
    {
        if (node->down->next->name =="VALUE")
        {
            if (node->down->next->value != "" )
            {
                out << spaces(depth) << node->down->value
                    << ":" << node->down->next->value;
                if (node->down->next->next.isValid())
                    out << node->down->next->next->value;
                out << std::endl;
            }
        }
        else if (node->down->next->name =="LIST")
        {
            mtk::CountPtr<AST_Node_Item> current_item = node->down->next->down->down;

            out << spaces(depth) << node->down->value << ":" << std::endl;
            out << spaces(depth) << "[" << std::endl;
            while (current_item.isValid())
            {
                out << spaces(depth) << "    "  <<  current_item->value << std::endl;
                current_item = current_item->next;
            }
            out << spaces(depth) << "]" << std::endl;
        }
        else
            throw mtk::Alarm(MTK_HERE, "configfile", MTK_SS("Invalid node type  " << node->down->next->name), mtk::alPriorError);
    }
    else if (node->name == "BLANK_LINE")
    {
        out << std::endl;
    }
    else if (node->name == "COMMENT")
    {
        out << node->value << std::endl;
    }
    else if (node->name == "SECTION")
    {
        out << spaces(depth) << node->down->value << std::endl << spaces(depth) << "{" << std::endl;
        WriteNode(out, node->down, depth + 4);
        WriteNode(out, node->down->next, depth + 4);
        out << spaces(depth) << "}" << std::endl << std::endl;
    }

}


void ConfigFile::SaveToFile  (const std::string&  _filename) const
{
    try
    {
        std::ofstream outfile;
        if(_filename!="")
            outfile.open(_filename.c_str());
        else
            outfile.open(filename.c_str());

        WriteNode(outfile, astConfigFile, 0);

        outfile.close();
    } MTK_CATCH_RETHROW("CF_SaveToFile", MTK_SS("on file " << filename))
}

std::string ConfigFile::GetStringConfigFileLines(void) const
{
    try
    {
        std::ostringstream out;

        WriteNode(out, astConfigFile, 0);

        return out.str().substr(0,5000);
    } MTK_CATCH_RETHROW("CF_GetStringConfigFileLines", MTK_SS("on file " << filename))
}


};  //  end namespace mtk

