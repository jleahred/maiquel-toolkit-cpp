BEGIN_INIT

INCLUDES = [ ]
NAMESPACES = ['tree_server2', 'msg']

END_INIT



//---------------------------------------------------------------------
//
//
//---------------------------------------------------------------------


sub_path_grants [< KEY:paths >]
{

    paths [<  LessOP:1 >]
    {
        re_path                (path)  :       string       //  regular expresion
        re_child               (child) :       string       //  regular expresion
    }

    [users]                (users) :       string       //  regular expresion
}



