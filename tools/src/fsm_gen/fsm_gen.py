#!/usr/bin/env python

from string import Template
import datetime
import time
import sys
import os


####################

TESTING = False

####################



param_name_size  = 11
param_type_size  = 20
method_name_size = 15


# filled later, declared here
INPUTS_LIST = ''
TRANSITIONS = {}

#FSM_GEN_PATH = '/home/maiquel/develop/incubator/fsm_gen'
#FSM_GEN_PATH = '../../../'
#DHP_PATH = '../../../../../../tools/bin'
FSM_GEN_PATH = './tools/'
DHP_PATH = './tools/'


CLASSNAME = 'UNDEFINED'
NAMESPACES = ['undefined']
NESTED_NAMESPACES = ''
BEGIN_NAMESPACES = ''
END_NAMESPACES = ''

GENERATE_ON = '.'
INCLUDES = ''



#=================================================================
#  support

def get_params_string(in_params, commented): #, attr_unused):
    params = ''
    if commented:
        begin_comment = '/*'
        end_comment = '*/'
    else:
        begin_comment = ''
        end_comment = ''
    #if attr_unused  == True:
    #    unused = " __attribute__ ((unused)) "
    #else:
    #    unused = " "
    if len(in_params) > 0:
        for param in in_params:
            partial_param  = "const "
            partial_param += Template("""${p_type}&  $unused """).substitute(p_type=param["p_type"], unused = '') + begin_comment
            params        +=  ('{0:<' + str(param_type_size) +'}').format(partial_param)
            partial_param  = Template("""${p_name}""").substitute(p_name=param["p_name"]) + end_comment
            params        +=  ('{0:<' + str(param_name_size) +'}').format(partial_param)
            if param != in_params[-1]:
                params += ', '
            else :
                params += '  '
    return params


def get_params_call_as_string(in_params):
    params = ''
    if len(in_params) > 0:
        for param in in_params:
            params        +=  param["p_name"]
            if param != in_params[-1]:
                params += ', '
    return params
    



# generate actions or guard info
def get_actions_or_guards_info(TRANSITIONS, actions_or_guards):
    if actions_or_guards != 'pre_action'  and actions_or_guards!='guard'  and actions_or_guards!='post_action':
        print "error actions_or_guards != 'action'  and actions_or_guards!='guard': in get_actions_or_guards_info"
        exit(-1)
    infix = ''
    if actions_or_guards == 'pre_action' :
        infix = '_PREACT___'
    elif actions_or_guards=='guard':
        infix = '_GUARD___'
    elif actions_or_guards=='post_action':
        infix = '_POSTACT___'
    info = {}
    for transition in TRANSITIONS:
        trans_info = transition["trans_info"]
        current_key = trans_info[actions_or_guards] 
        if len(transition["trans_info"]) :
            if len(trans_info[actions_or_guards]) > 0:
                if info.get(current_key) == None:
                    info[current_key] = {}
                info[current_key]["input_name"]  = trans_info['input']
                if info[current_key].get("from_status") == None :
                    info[current_key]["from_status"] = []
                ##else:
                ##    if transition['name'] in info[current_key]["from_status"] :
                ##        print "Error, action with initial status and input repitted " + trans_info[actions_or_guards] + " " + transition['name']
                info[current_key]["from_status"].append(transition['name'])
    return info


def get_list_actions_or_guards_info_for_class(class_name, actions_or_guards):
    if actions_or_guards != 'pre_action'  and actions_or_guards!='guard'  and actions_or_guards!='post_action':
        print "error actions_or_guards != 'action'  and actions_or_guards!='guard': in get_list_actions_or_guards_info_for_class"
        exit(-1)
    info = []

    method_context = ''
    if actions_or_guards == 'pre_action' :
        method_context = '_PREACT___'
    elif actions_or_guards == 'post_action' :
        method_context = '_POSTACT___'
    elif actions_or_guards == 'guard' :
        method_context = '_GUARD___'
    else:
        method_context = '_ERROR_UNKNOWNCODE___'
    
    for transition in TRANSITIONS:
        if transition["name"] == class_name:
            trans_info = transition["trans_info"]
            if len(transition["trans_info"]) :
                if len(trans_info[actions_or_guards]) > 0:
                    info.append({"name":trans_info[actions_or_guards], 'macro': trans_info[actions_or_guards], "input":trans_info["input"], "guard":trans_info["guard"]})
    return info


def get_params_from_xxxput(xxxut_name, xxxPUTS_LIST) :
    #INPUTS_LIST = [{'name':'number', 'params':[{'p_name':'num', 'p_type':'int'}], 'visibility':'public'}, {'name':'oper', 'params':[{'p_name':'c', 'p_type':'char'}, {'p_name':'d', 'p_type':'double'}], 'visibility':'public'},{'name':'end', 'params':[]         , 'visibility':''},{'name':'foo', 'params':[]         ,'visibility':'private'},{'name':'foo2', 'params':[{'p_name':'d', 'p_type':'double'}], 'visibility':'public'}, {}] 
    result = Template("ERROR... xxxput_name $xxxut_name  not found  in $xxxPUTS_LIST").substitute(xxxut_name=xxxut_name, xxxPUTS_LIST=xxxPUTS_LIST)
    for inputoutput in xxxPUTS_LIST :
        if len(inputoutput)>0:
            if inputoutput["name"] == xxxut_name :
                result = get_params_string(inputoutput["params"], False)
    return result

#  support
#=================================================================




#//////////////////////////////////////////////////////////////////////
# templates
header_template = """#ifndef __${CLASSNAME}_h__
#define __${CLASSNAME}_h__


$AUTOGENERATED_MESSAGE

#include "support/alarm.h"
#include "support/signalslot.hpp"
#include "support/list.hpp"

$INCLUDE_LINES

namespace ${private_namespace} {
    class abstract_status;
};





${BEGIN_NAMESPACES}


class ${CLASSNAME}   : public mtk::SignalReceptor
{
    mtk::non_copyable nc;
    typedef  ${CLASSNAME}  CLASS_NAME;


public:
    ${CLASSNAME} ($CTOR_PARAMS);
    virtual ~${CLASSNAME} ();

    //  INPUT
${INPUT_METHODS}

    //  OUTPUT
${OUTPUT_SIGNALS}

    //  ACCESS
${ACCESS_METHODS}


private:
    //  current_status
    mtk::CountPtr<${private_namespace}::abstract_status>      current_status;
    void on_new_status (mtk::CountPtr<${private_namespace}::abstract_status>  new_status);

    //  keep temp status
    mtk::list<mtk::CountPtr<${private_namespace}::abstract_status> >     queue_temp_status;
    void on_keep_temp_status (void);
    void on_remove_temp_status (void);
};




$END_NAMESPACES


#endif // __${CLASSNAME}_h__


"""


# ...................................



impl_template = """$AUTOGENERATED_MESSAGE


namespace ${private_namespace} {

$COMMON_INFO_CLASS


$ABSTRACT_STATUS_CLASS

$STATUS_CLASSES


$STATUS_IMPL

};  // end   namespace ${private_namespace} {

"""

# templates
#//////////////////////////////////////////////////////////////////////









#***********************************************************************
#testing


if TESTING:


    CLASSNAME = 'FsmTesting'

NAMESPACES=['testing']
GENERATE_ON='generated'
INPUTS_LIST = [{'name':'req_key', 'params':[{'p_name':'user', 'p_type':'std::string'}], 'visibility':''}, {'name':'req_open', 'params':[{'p_name':'user', 'p_type':'std::string'}, {'p_name':'key', 'p_type':'std::string'}], 'visibility':''},{'name':'req_close', 'params':[{'p_name':'user', 'p_type':'std::string'}, {'p_name':'key', 'p_type':'std::string'}], 'visibility':''}, {}]
OUTPUTS_LIST = [{'name':'sig_opened', 'params':[]         , 'visibility':''}, {'name':'sig_closed', 'params':[]         , 'visibility':''},{}]
COMMON_STATUS_INFO = [{}]
STATUS=[]
STATUS.extend([{'name':'opened', 'properties':[]}])
STATUS.extend([{'name':'closed', 'properties':[]}])
STATUS.extend([{'name':'w_rq_open', 'properties':[]}])
STATUS.extend([{'name':'w_rq_close', 'properties':[]}])
TRANSITIONS = []
TRANSITIONS.extend([{'name':'closed', 'trans_info':{'input':'rq_key', 'guard':''              , 'pre_action':'resp_key', 'post_action':''       , 'log_error':'False'}, 'new_status':{"name":"w_rq_open", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_open', 'trans_info':{'input':'rq_open', 'guard':'valid_key', 'pre_action':'open_door', 'post_action':'sig_opened', 'log_error':'False'}, 'new_status':{"name":"opened", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'opened', 'trans_info':{'input':'rq_key', 'guard':''              , 'pre_action':'resp_key', 'post_action':''       , 'log_error':'False'}, 'new_status':{"name":"w_rq_close", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_close', 'trans_info':{'input':'rq_close', 'guard':'valid_key', 'pre_action':'close_door', 'post_action':'sig_closed', 'log_error':'False'}, 'new_status':{"name":"closed", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'closed', 'trans_info':{'input':'rq_key', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"closed", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'closed', 'trans_info':{'input':'rq_open', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"closed", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'closed', 'trans_info':{'input':'rq_close', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"closed", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_open', 'trans_info':{'input':'rq_key', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"closed", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_open', 'trans_info':{'input':'rq_open', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"closed", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_open', 'trans_info':{'input':'rq_close', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"closed", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'opened', 'trans_info':{'input':'rq_key', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"opened", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'opened', 'trans_info':{'input':'rq_open', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"opened", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'opened', 'trans_info':{'input':'rq_close', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"opened", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_close', 'trans_info':{'input':'rq_key', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"opened", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_close', 'trans_info':{'input':'rq_open', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"opened", "ctor_params":""}}])
TRANSITIONS.extend([{'name':'w_rq_close', 'trans_info':{'input':'rq_close', 'guard':''              , 'pre_action':''     , 'post_action':''       , 'log_error':'true'}, 'new_status':{"name":"opened", "ctor_params":""}}])









#testing
#***********************************************************************


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# execute_dhp()
def execute_dhp(file):
    pipe = os.popen( os.path.join(DHP_PATH, 'dhp') + ' ' 
                    + os.path.join(FSM_GEN_PATH, 'fsm_gen.gram ') +  file)
    return pipe.readlines()
    

# execute_dhp()
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~










#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#           def generate_header():


def generate_header():
    INPUT_METHODS = ''


    for input in INPUTS_LIST:
        if len(input)> 0:
            if input["visibility"] != "private":
                INPUT_METHODS +=  ('{0:<' + str(method_name_size + 9) +'}').format(Template("""    void ${name} """).substitute(name=input["name"]))
                INPUT_METHODS +=  "( "+ get_params_string(input["params"], False) + ");\n"


    OUTPUT_SIGNALS = ''
    for output in OUTPUTS_LIST:
        if len(output)> 0:
            if output["visibility"] != "private":
                OUTPUT_SIGNALS += Template("""    mtk::Signal< """ + get_params_string(output["params"], True) + """ > ${name};\n""").substitute(name=output["name"])


    ACCESS_METHODS = ''
    for csi in COMMON_STATUS_INFO:
        if len(csi)>0:
            if csi["visibility"] != "private" :
                ACCESS_METHODS += Template("""    const ${type} &  ${name} () const;\n""").substitute(name=csi["name"], type=csi["type"])


    hf = open(os.path.join(GENERATE_ON, CLASSNAME.lower()+'.h'), "wt")
    hf.write(Template(header_template).substitute(
                    CLASSNAME               = CLASSNAME,
                    classname               = CLASSNAME.lower(),
                    BEGIN_NAMESPACES         = BEGIN_NAMESPACES,
                    END_NAMESPACES           = END_NAMESPACES,
                    private_namespace       = private_namespace,
                    INPUT_METHODS           = INPUT_METHODS,
                    OUTPUT_SIGNALS          = OUTPUT_SIGNALS,
                    ACCESS_METHODS          = ACCESS_METHODS,
                    AUTOGENERATED_MESSAGE   = AUTOGENERATED_MESSAGE,
                    CTOR_PARAMS             = get_params_from_properties(COMMON_STATUS_INFO)[:-1],
                    INCLUDE_LINES           = '\n'.join(INCLUDES)
                ))

    hf.close()
#def generate_header():
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#def generate_implementation():


def get_params_from_properties(properties):
    result = ''
    # properties with initializer == '_' has to be connected on constructor
    for prop in properties:
        if len(prop)>0:
            if prop["initializer"].strip(' ') == '_':
                result += Template(""" const ${type}& _${name},""").substitute(name=prop['name'] , type=prop['type'])
    return result

def get_params_call_from_properties(properties):
    result = ''
    # properties with initializer == '_' has to be connected on constructor
    for prop in properties:
        if len(prop)>0:
            if prop["initializer"].strip(' ') == '_':
                result += Template(""" _${name},""").substitute(name=prop['name'])
    return result[:-1]
    


def get_CONSTR_INITIALIZER_from_properties(properties) :
    result = ''
    first = True
    for prop in properties:
        if len(prop)>0:
            if prop["visibility"] != 'phony':
                if first:
                    first = False
                else:
                    result += ',\n'
                if prop["initializer"].strip(' ') == '_':
                    result += Template("""        __${name}(_${name})""").substitute(name=prop['name'])
                else:
                    result += Template("""        __${name}(${initializer})""").substitute(name=prop['name'] , initializer=prop['initializer'])
    return result



def get_PROPERTIES_from_properties(properties):
    result = ''
    for prop in properties:
        if len(prop)>0:
            if prop["visibility"] != 'phony':
                result += Template("""    ${type} __${name};\n""").substitute(name=prop['name'], type=prop["type"])
                result += Template("""    virtual const ${type}&  ${name}() const {  return __${name}; };\n""").substitute(name=prop['name'], type=prop["type"])
                result += Template("""    virtual void set_${name}(const ${type}&  _prop) {  __${name} = _prop;  };\n""").substitute(name=prop['name'], type=prop["type"])
            else:
                result += Template("""    virtual const ${type} &  ${name}() const {  static ${type} result(${initializer});   return result; };\n""").substitute(name=prop['name'], type=prop["type"], initializer = prop["initializer"])
                result += Template("""    virtual void set_${name}(const ${type}& ) {  throw mtk::Alarm(MTK_HERE, "fsm_gen.set_property", "property not valid in current status", mtk::alPriorError);  };\n""").substitute(name=prop['name'], type=prop["type"])
    return result
    


def generate_impl_status_common_info_class():
    template = """
class abstract_status;

// -----------------------------------------------------------------------
//      s t a t u s _ c o m m o n _ i n f o

struct  status_common_info
{
    status_common_info ($SCI_CONSTR_PARAMS)
        :  
$SCI_CONSTR_INITALIZER
        {};
    virtual ~status_common_info(){};

    // PROPERTIES AND SIGNALS
$PROPERTIES

    mtk::Signal<mtk::CountPtr<abstract_status> > signal_new_status;
    mtk::Signal<> signal_keep_temp_status;
    mtk::Signal<> signal_remove_temp_status;

};

"""


    PROPERTIES = 'PROPERTIES ERROR_NOT DEFINED'
    SCI_CONSTR = 'SCI_CONSTR ERROR_NOT DEFINED'
    SCI_CONSTR_INITALIZER = 'SCI_CONSTR_INITALIZER ERROR_NOT DEFINED'
    
    SCI_CONSTR_PARAMS = get_params_from_properties(COMMON_STATUS_INFO)

    #public signal refs constructor params
    for output in OUTPUTS_LIST:
        if len(output) > 0:
            if output["visibility"] != 'private':
                SCI_CONSTR_PARAMS += Template(""" mtk::Signal<${type}>& _${name},""").substitute(name=output['name'] , type=get_params_string(output['params'], True))
    SCI_CONSTR_PARAMS = SCI_CONSTR_PARAMS[:-1]

    SCI_CONSTR_INITALIZER = get_CONSTR_INITIALIZER_from_properties(COMMON_STATUS_INFO) 

    # initializer
    
    # initializer for signals
    for output in OUTPUTS_LIST:
        if len(output) > 0:
            if SCI_CONSTR_INITALIZER != '':
                SCI_CONSTR_INITALIZER += ', \n'
            if output["visibility"] != 'private':
                SCI_CONSTR_INITALIZER += Template("""        ${name} (_${name})""").substitute(name=output['name'])
            else:
                SCI_CONSTR_INITALIZER += Template("""        ${name} (_${name})""").substitute(name=output['name'])
    SCI_CONSTR_INITALIZER = SCI_CONSTR_INITALIZER


    PROPERTIES = get_PROPERTIES_from_properties(COMMON_STATUS_INFO)
    # initializer for signals
    for output in OUTPUTS_LIST:
        if len(output) > 0:
            PROPERTIES += Template("""    mtk::Signal<${type}>& ${name};\n""").substitute(name=output['name'], type=get_params_string(output['params'], True))
    #PROPERTIES = SCI_CONSTR_INITALIZER[:-2]

    
    return Template(template).substitute(
                PROPERTIES = PROPERTIES,
                SCI_CONSTR_PARAMS = SCI_CONSTR_PARAMS,
                SCI_CONSTR_INITALIZER = SCI_CONSTR_INITALIZER
                )


def generate_impl_ABSTRACT_STATUS_CLASS():
    template = """
// -----------------------------------------------------------------------
//      abstract_status
class abstract_status  : public mtk::SignalReceptor
{
    mtk::non_copyable  nc;

public:
    abstract_status (mtk::CountPtr<status_common_info> _ci)
        : ci (_ci) {};
    virtual ~abstract_status() {};
    
    mtk::CountPtr<status_common_info> ci;
    
    virtual std::string  GetStatusName() = 0;

    //  INPUTS
$INPUT_METHODS

    //  ACCESS
$ACCESS_METHODS
};


"""
    INPUT_METHODS = ''
    ACCESS_METHODS= ''
    for input in INPUTS_LIST:
        if len(input)> 0:
            INPUT_METHODS +=  (Template("""    virtual void ${name} """).substitute(name=input["name"]))
            INPUT_METHODS +=  "( "+ get_params_string(input["params"], False) + ")=0;\n"

    for info in COMMON_STATUS_INFO :
        if len(info)>0:
            if info["visibility"] != 'private':
                ACCESS_METHODS +=  Template("""    virtual const $type &  ${name} (void) const { return ci->$name(); }; \n""").substitute(name=info["name"], type=info["type"])

    return Template(template).substitute(INPUT_METHODS = INPUT_METHODS, ACCESS_METHODS=ACCESS_METHODS)







def generate_impl_INPUT_METHODS():
    INPUT_METHODS = ''
    current_visibility = 'public'
    for input in INPUTS_LIST:
        if len(input) > 0:
            if input["visibility"] != current_visibility  and  input["visibility"]!= '':
                current_visibility = input["visibility"]
                if current_visibility == 'public':
                    INPUT_METHODS += 'public:\n'
                else:
                    INPUT_METHODS += 'protected:\n'
            INPUT_METHODS += Template("    void $name ($params);\n").substitute(
                            name=input["name"], 
                            params= get_params_string(input["params"], False)
                        )
    return INPUT_METHODS





def get_status_input__info(status_name, input):
    result = []
    prev_action_guard = []
    for t in TRANSITIONS:
        info = {}
        if len(t)>0:
            if t["name"] == status_name  and  input["name"] == t["trans_info"]["input"]:
                info["guard"] = t["trans_info"]["guard"]
                info["pre_action"] = t["trans_info"]["pre_action"]
                info["post_action"] = t["trans_info"]["post_action"]
                info["new_status"] = t["new_status"]
                result.append(info)
                if (info["guard"] + '**'+ info["pre_action"] + '**'+ info["post_action"]) not in prev_action_guard :
                    prev_action_guard.append(info["guard"] + '**'+ info["pre_action"] + '**'+ info["post_action"])
                else:
                    info["new_status"] = 'Error, duplicate guard action ' + (info["guard"] + '**'+ info["pre_action"] + '**'+ info["post_action"]) + ' in status ' + status_name
    return result


def get_code_from_macro(macro_name):
    if macro_name == 'LOGIC_ERROR':
        return 'ci->sig_alarm(mtk::Alarm(MTK_HERE, "fsm_gen", "logic error", mtk::alPriorError));'
        ##return 'mtk::AlarmMsg(mtk::Alarm(method_name, "logic error", mtk::alPriorError));'
    else :
        code  = '//  inserting macro: ' + macro_name + '\n'
        code += MACROS.get(macro_name)
        if code == None:
            ##return 'macro code not located ' + macro_name
            # let user to define his own macro
            return "    // MACRO to be defined by user...\n    "  + macro_name
        else:
            return code



def generate_impl_INPUT_METHODS_impl(status):
    result = ''
    m_impl_template = """
        if ($GUARD $METHOD_PARAMS) {
$PRE_ACTION
            new_status = mtk::make_cptr(new $NEW_STATUS $PARAMS);
            ci->signal_new_status.emit(new_status);
$POST_ACTION
        }
    """
    
    
    method_template = """
void $STATUS_NAME::$METHOD_NAME ( $PARAMS )
{
    //  remove unused warning
    $REMOVE_UNUSED_WARNINGS
    
	static const char* method_name = "$STATUS_NAME::$METHOD_NAME";

    $INIT_CODE

    mtk::CountPtr<abstract_status> new_status;
    ci->signal_keep_temp_status();    
    try
    {
        $IMPLEMENTATION
    }
    MTK_CATCH_RETHROW(method_name, "exception fsm, rethrowed")
    ci->signal_remove_temp_status();
}
"""
    
    for input in INPUTS_LIST:
        last_sii = []
        IMPLEMENTATION = ''
        GUARD = ''
        REMOVE_UNUSED_WARNINGS = ''
        if len(input)>0:
            INIT_CODE = input['code']
            status_input__info = get_status_input__info(status["name"], input)
            if len(status_input__info)>0:
                METHOD_PARAMS = get_params_call_as_string(input["params"])
                if len(status_input__info) == 1:
                    if status_input__info[0]["guard"] != '':
                        GUARD += "error, just one action with guard not empty " + status["name"] + ' ' +status_input__info[0]["guard"]
                for sii in status_input__info:
                    PRE_ACTION = ''
                    for pre_action in get_list_actions_or_guards_info_for_class (status["name"], 'pre_action'):
                        if pre_action["input"] == input["name"]  and pre_action["guard"]==sii["guard"]:
                            for m_name in pre_action["macro"].split(' & '):
                                m_name = m_name.strip(' ')
                                PRE_ACTION += get_code_from_macro(m_name) + '\n'

                    POST_ACTION = ''
                    for post_action in get_list_actions_or_guards_info_for_class (status["name"], 'post_action'):
                        if post_action["input"] == input["name"] and post_action["guard"]==sii["guard"]:
                            for m_name in post_action["macro"].split(' & '):
                                m_name = m_name.strip(' ')
                                POST_ACTION += get_code_from_macro(m_name) + '\n'
                            ##POST_ACTION += Template("""        $NAME (keep_ci_post_action, $METHOD_PARAMS);\n""").substitute(
                            ##                        NAME = post_action["name"],
                            ##                        METHOD_PARAMS = METHOD_PARAMS
                            ##                            )
                    
                    if sii["guard"] == '' :
                        last_sii.append(sii)
                    else:
                        GUARD_MACRO = ''
                        GUARD = ''
                        for m_name in sii['guard'].split('_&_'):
                            GUARD += get_code_from_macro(m_name)
                        
                        if sii["new_status"]["ctor_params"].strip() == "":
                            PARAMS     = "(ci)"
                        else:
                            PARAMS     = "(ci, " + sii["new_status"]["ctor_params"] + ")"
                        if IMPLEMENTATION != '':
                            IMPLEMENTATION += "else "
                        IMPLEMENTATION += Template(m_impl_template).substitute(
                                            GUARD = GUARD,
                                            METHOD_PARAMS = '',
                                            PRE_ACTION = PRE_ACTION,
                                            NEW_STATUS = sii["new_status"]["name"],
                                            PARAMS     = PARAMS,
                                            POST_ACTION = POST_ACTION
                                )
                if len(last_sii) > 1:
                    IMPLEMENTATION += "Error too many default actions (no guard)"
                elif len(last_sii) == 0:
                    IMPLEMENTATION += "Error mising default guard"
                else:
                    GUARD = "true"
                    if IMPLEMENTATION != '':
                        IMPLEMENTATION += "else "
                    if sii["new_status"]["ctor_params"].strip() == "":
                        PARAMS     = "(ci)"
                    else:
                        PARAMS     = "(ci, " + sii["new_status"]["ctor_params"] + ")"
                    IMPLEMENTATION += Template(m_impl_template).substitute(
                                        GUARD = GUARD,
                                        METHOD_PARAMS = '',
                                        PRE_ACTION = PRE_ACTION,
                                        NEW_STATUS = last_sii[0]["new_status"]["name"],
                                        PARAMS     = PARAMS,
                                        POST_ACTION = POST_ACTION
                            )
                for param in input["params"] :
                    REMOVE_UNUSED_WARNINGS += "(void) "+ param["p_name"] +";\n"
                    ##REMOVE_UNUSED_WARNINGS += "const " + param["p_type"] +"& p("+ param["p_name"] +");\n"
                    ##REMOVE_UNUSED_WARNINGS += "(void) p;"
                result += Template(method_template).substitute(
                                        STATUS_NAME = status["name"],
                                        METHOD_NAME = input["name"],
                                        PARAMS = get_params_string(input["params"], False),
                                        IMPLEMENTATION = IMPLEMENTATION,
                                        REMOVE_UNUSED_WARNINGS = REMOVE_UNUSED_WARNINGS,
                                        INIT_CODE = INIT_CODE
                                            )
    return result




def get_ctor_code(class_name) :
    #STATUS.extend([{'name':'w_rq_open', 'ctor_code':      [{ std::cout << "w_rq_open"  << std::endl;  }], 'properties':[{'name':'key', 'type':'std::string ', 'initializer':'_', "visibility":""},]}])
    CODE = ''
    result = ''
    for status in STATUS:
        if status["name"] == class_name:
            CODE = status["ctor_code"]
    if CODE != '':
        result = 	Template("""
            try
            {
                $CODE
            }
            MTK_CATCH_RETHROW("${class_name}_ctor", "rethrowed")""").substitute(CODE = CODE, class_name=class_name);

    return result;
    




def generate_impl_STATUS_CLASS(statusinfo):
    template = """
// -----------------------------------------------------------------------
//      $CLASS_NAME
class $CLASS_NAME  :   public  abstract_status
{
    mtk::non_copyable  nc;
    typedef $CLASS_NAME  CLASS_NAME;

public:
    $CLASS_NAME ($CLASS_PARAMS)
        : 
        $CLASS_INITIALIZER
        { $CTOR_CODE };
    
    std::string  GetStatusName()  {  return "$CLASS_NAME"; }

//private:   visibility ignored here
    //  specific properties (good for RAII)
$PROPERTIES

    //  INPUTS
public:
$INPUT_METHODS

};


"""
    CLASS_NAME = 'CLASS_NAME'
    CLASS_INITIALIZER = 'CLASS_INITIALIZER'
    INPUT_METHODS = 'INPUT_METHODS'
    PROPERTIES = 'PROPERTIES'
    CTOR_CODE = 'CTOR_CODE'

    CLASS_NAME = statusinfo["name"]

    CLASS_PARAMS = get_params_from_properties(statusinfo["properties"])[:-1]
    if CLASS_PARAMS.strip() == '':
        CLASS_PARAMS = 'mtk::CountPtr<status_common_info> _ci' 
    else:
        CLASS_PARAMS = 'mtk::CountPtr<status_common_info> _ci, ' + CLASS_PARAMS
        

    CLASS_INITIALIZER = get_CONSTR_INITIALIZER_from_properties(statusinfo["properties"]) 
    if statusinfo["properties"] == []:
        CLASS_INITIALIZER = 'abstract_status(_ci)\n'
    else:
        CLASS_INITIALIZER = 'abstract_status(_ci),\n' + CLASS_INITIALIZER

    
    
    INPUT_METHODS = generate_impl_INPUT_METHODS()

    PROPERTIES = get_PROPERTIES_from_properties(statusinfo["properties"])

    guards = get_list_actions_or_guards_info_for_class (statusinfo["name"], 'guard')
    GUARDS = ''

    PRE_ACTIONS = ''
    pre_actions = get_list_actions_or_guards_info_for_class (statusinfo["name"], 'pre_action')

    POST_ACTIONS = ''
    post_actions = get_list_actions_or_guards_info_for_class (statusinfo["name"], 'post_action')
    return Template(template).substitute(
                    CLASS_NAME = CLASS_NAME,
                    CLASS_PARAMS = CLASS_PARAMS,
                    CLASS_INITIALIZER = CLASS_INITIALIZER,
                    INPUT_METHODS = INPUT_METHODS,
                    PROPERTIES = PROPERTIES,
                    CTOR_CODE = get_ctor_code(CLASS_NAME)
            )





def generate_impl_STATUS_CLASSES():
    classes_code = ''
    for c in STATUS:
        classes_code += generate_impl_STATUS_CLASS(c)
    return classes_code
    



def generate_impl_INPUT_METHODS_impl_all_status():
    classes_code = ''
    for c in STATUS:
        classes_code += generate_impl_INPUT_METHODS_impl(c)
    return classes_code




def get_public_signals_names_as_string_with_commas():
    result = ''
    for out in OUTPUTS_LIST:
        if len(out)>0:
            if out['visibility'] != 'private':
                result += out["name"] + ','
    return result[:-1]



def get_main_class_implementation_public_inputs():
    result = ''
    for input in INPUTS_LIST:
        if len(input)>0:
            if input["visibility"] != 'private':
                result += Template("""void ${NESTED_NAMESPACES}$CLASSNAME::$INPUT_NAME ($PARAMS)
{
    mtk::CountPtr<${private_namespace}::abstract_status>  current_status_to_keep_alive_on_scope = current_status;
    current_status_to_keep_alive_on_scope->$INPUT_NAME($CALL_PARAMS);
}
""").substitute(
                                    CLASSNAME  = CLASSNAME,
                                    INPUT_NAME = input["name"],
                                    PARAMS = get_params_string(input["params"], False),
                                    CALL_PARAMS = get_params_call_as_string(input["params"]),
                                    NESTED_NAMESPACES = NESTED_NAMESPACES,
                                    private_namespace       = private_namespace
                                )
    
    return result


def get_main_class_implementation_access():
    result = ''
    for csi in COMMON_STATUS_INFO:
        if len(csi)>0:
            if csi["visibility"] != 'private':
                result += Template("""const $TYPE & ${NESTED_NAMESPACES}$CLASSNAME::$ACCESS_NAME (void) const
{
    return current_status->$ACCESS_NAME();
}
""").substitute(
                                    CLASSNAME  = CLASSNAME,
                                    ACCESS_NAME = csi["name"],
                                    NESTED_NAMESPACES  = NESTED_NAMESPACES,
                                    TYPE = csi["type"]
                                )
    
    return result
    


def get_main_class_implementation():
    # constructor
    
    CSI_CALL_PARAMS = get_params_call_from_properties(COMMON_STATUS_INFO)
    if CSI_CALL_PARAMS.strip() != '':
        CSI_CALL_PARAMS += ', '
    
    INITIALIZE = INIT_PARAMS_CREATING_STATUS
    if INITIALIZE != '':
        INITIALIZE = ', ' + INITIALIZE
    SIGNALS = get_public_signals_names_as_string_with_commas()
    CSI_CALL_PARAMS = get_params_call_from_properties(COMMON_STATUS_INFO)
    if SIGNALS != "" and  CSI_CALL_PARAMS  != "":
        CSI_CALL_PARAMS += ', '
    result =  Template("""${NESTED_NAMESPACES}$CLASSNAME::$CLASSNAME($PARAMS)
{
    mtk::CountPtr<$private_namespace::status_common_info> ci = mtk::make_cptr(
                            new $private_namespace::status_common_info ($CSI_CALL_PARAMS $SIGNALS));

    current_status = mtk::make_cptr(new $private_namespace::$INIT_STATUS(ci $INITIALIZE) );
    MTK_CONNECT_THIS(ci->signal_new_status, on_new_status)
    MTK_CONNECT_THIS(ci->signal_keep_temp_status, on_keep_temp_status)
    MTK_CONNECT_THIS(ci->signal_remove_temp_status, on_remove_temp_status)
}


${NESTED_NAMESPACES}$CLASSNAME::~$CLASSNAME($PARAMS)
{
}

void ${NESTED_NAMESPACES}$CLASSNAME::on_new_status (mtk::CountPtr<$private_namespace::abstract_status>  new_status)
{
    current_status = new_status;
}

void ${NESTED_NAMESPACES}$CLASSNAME::on_keep_temp_status (void)
{
    queue_temp_status.push_back(current_status);
}
void ${NESTED_NAMESPACES}$CLASSNAME::on_remove_temp_status (void)
{
    queue_temp_status.pop_front();
}


""").substitute(CLASSNAME = CLASSNAME,
                PARAMS = get_params_from_properties(COMMON_STATUS_INFO)[:-1],
                CSI_CALL_PARAMS = CSI_CALL_PARAMS,
                INIT_STATUS = TRANSITIONS[0]["name"],
                SIGNALS  = SIGNALS,
                NESTED_NAMESPACES = NESTED_NAMESPACES,
                private_namespace = private_namespace,
                INITIALIZE = INITIALIZE
            )

    # public inputs
    result += get_main_class_implementation_public_inputs()
    
    # access methods
    result += get_main_class_implementation_access()
    
    return result


def generate_implementation():
    
    

    implf = open(os.path.join(GENERATE_ON, CLASSNAME.lower()+'.impl'), "wt")


    implf.write(Template(impl_template).substitute(
                    CLASSNAME               = CLASSNAME,
                    classname               = CLASSNAME.lower(),
                    NESTED_NAMESPACES       = NESTED_NAMESPACES,
                    private_namespace       = private_namespace,
                    AUTOGENERATED_MESSAGE   = AUTOGENERATED_MESSAGE,
                    COMMON_INFO_CLASS       = generate_impl_status_common_info_class(),
                    ABSTRACT_STATUS_CLASS   = generate_impl_ABSTRACT_STATUS_CLASS(),
                    STATUS_CLASSES          = generate_impl_STATUS_CLASSES(),
                    STATUS_IMPL             = generate_impl_INPUT_METHODS_impl_all_status()
                ))

    implf.write(get_main_class_implementation())
    
    implf.close()

#def generate_implementation():
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# generate_graphviz()

def generate_graphviz():
    result = ''
    template = """digraph automata {
    node [shape = circle, fontsize=10, fixedsize=true width=0.7];
    $INIT_NODE [ style = filled, color=lightgrey ];

    $TRANS 

    //$CLASSNAME  [ shape = plaintext ];
}
"""

    TRANS = ''
    COLOR = 'blue'
    for transition in TRANSITIONS:
        if COLOR=='blue':
            COLOR = 'black'
        else:
            COLOR = 'blue'
        if len(transition) > 0 :
            if len(transition["new_status"])>0:
                if transition["hidden"]  == False:
                    INPUT    = transition["trans_info"]["input"]
                    GUARD = transition["trans_info"]["guard"]
                    PRE_ACT   = transition["trans_info"]["pre_action"]
                    POST_ACT  = transition["trans_info"]["post_action"]

                    label = 'label = "' + INPUT
                    if GUARD != '':
                        label += ' & ' + GUARD
                    if PRE_ACT.strip()!= ''  or  POST_ACT.strip() != '':
                        label += '\\n' + PRE_ACT + ', ' + POST_ACT
                    label += '"'
                    label += ', color=' +COLOR + ', fontcolor=' + COLOR
                    label += ', fontsize=10, fixedsize=true'
                    TRANS += Template('    $FROM_STATUS  ->  $TO_STATUS  [ $label ];\n').substitute(
                                                FROM_STATUS  = transition["name"],
                                                TO_STATUS    = transition["new_status"]["name"],
                                                label    = label
                                        )


    result = Template(template).substitute(
            INIT_NODE = TRANSITIONS[0]["name"],
            TRANS = TRANS,
            CLASSNAME = CLASSNAME
            )

    FILE = open(os.path.join(GENERATE_ON, CLASSNAME.lower()+'.dot'), 'wt')
    FILE.writelines(result)
    FILE.close()
    
    return

# def generate_implementation():
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~




#  -----------------------------------------------------------------------

#  MAIN    


##if TESTING == False:
for file in sys.argv[1:] :
    ORIG_FILE = file
    exec('\n'.join(execute_dhp(file)))
    CLASSNAME = os.path.splitext(os.path.split(file)[-1:][0])[0]
    GENERATE_ON = os.path.join(os.path.split(ORIG_FILE)[0], GENERATE_ON)

    NESTED_NAMESPACES = ''
    BEGIN_NAMESPACES = ''
    END_NAMESPACES = ''
    for ns in NAMESPACES:
        NESTED_NAMESPACES += ns + '::'
        BEGIN_NAMESPACES += 'namespace ' + ns + '{'
        END_NAMESPACES   += '\n};   //  namespace ' + ns
    NESTED_NAMESPACES= NESTED_NAMESPACES


    ## verify that input_list and output_list has not duplicated values for name







    private_namespace = "fsmgen_" + CLASSNAME.lower();
    AUTOGENERATED_MESSAGE = ("""//  code generated by fsm_gen
// generated automatically
// coded last modification:        $CODED_LAST_MODIF  desactivated, lots of false notifications
// pythonscript last modification: $SCRIPT_LAST_MODIF
""")##.substitute(CODED_LAST_MODIF=str(time.ctime(os.path.getmtime(ORIG_FILE))), SCRIPT_LAST_MODIF=str(time.ctime(os.path.getmtime(sys.argv[0]))))

    PRE_ACTIONS_INFO = get_actions_or_guards_info(TRANSITIONS, 'pre_action')
    POST_ACTIONS_INFO = get_actions_or_guards_info(TRANSITIONS, 'post_action')
    GUARDS_INFO  =  get_actions_or_guards_info(TRANSITIONS, 'guard')



    generate_header()
    generate_implementation()
    generate_graphviz()