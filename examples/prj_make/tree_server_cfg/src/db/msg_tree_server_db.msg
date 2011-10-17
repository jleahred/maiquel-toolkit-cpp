BEGIN_INIT

INCLUDES = [ ]
NAMESPACES = ['tree_server2', 'msg']

END_INIT



//---------------------------------------------------------------------
//        
//
//---------------------------------------------------------------------


sub_path_grants [< KEY:re_path >]
{
    re_path                (path)  :       string       //  regular expresion

    [users]                (users) :       string       //  regular expresion
}



