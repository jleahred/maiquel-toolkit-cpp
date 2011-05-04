#!/usr/bin/env python

from string import Template
import datetime
import sys
import os
import time
import re


####################

TESTING = False

####################



#param_name_size  = 11
#param_type_size  = 20
#method_name_size = 15


TOOLS_PATH = './tools/'



NAMESPACES =['unkown']
INCLUDES = ''

if TESTING:
    MESSAGES={ 
      'LimitPosition': [ {'FIELD_NAME':'buy_sell', 'FIELD_TAG':'bs', 'field_type':'std::string', 'OPTIONS':['optional'] }, {'FIELD_NAME':'price', 'FIELD_TAG':'pr', 'field_type':'mtk::FixedNumber', 'OPTIONS':['recomended'] }, {'FIELD_NAME':'quantity', 'FIELD_TAG':'qt', 'field_type':'mtk::FixedNumber', 'OPTIONS':['mandatory'] }, ] , }



def is_message_not_submessage(class_properties) :
    if class_properties.has_key('SUBJ'):
        return True
    elif class_properties.has_key('I'):
        for class_name, class_info, __class_properties, send_code  in ALL_MESSAGES:
            if class_name == class_properties['I']:
                return is_message_not_submessage (__class_properties)
        return False
    else:
        return False



def get_constructor_params(class_name, class_info, class_properties, send_code) :
    CONSTRUCTOR_PARAMS_DEBUG_DECL = ''
    
    if class_properties.has_key('I'):
        CONSTRUCTOR_PARAMS_DEBUG_DECL += ' const ' + class_properties['I'] + '&' + '  parent,'
    
    for field in class_info:
        if field.has_key('field_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0:
                CONSTRUCTOR_PARAMS_DEBUG_DECL += Template("   const mtk::nullable<$FIELD_TYPE>&  _$FIELD_NAME,").substitute(
                                                        FIELD_TYPE = field['field_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            else :
                CONSTRUCTOR_PARAMS_DEBUG_DECL += Template("   const $FIELD_TYPE&  _$FIELD_NAME,").substitute(
                                                        FIELD_TYPE = field['field_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
        elif field.has_key('sub_msg_type') :
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0 :
                CONSTRUCTOR_PARAMS_DEBUG_DECL += Template("   const mtk::nullable<$FIELD_TYPE>&  _$FIELD_NAME,").substitute(
                                                        FIELD_TYPE = field['sub_msg_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            else :
                CONSTRUCTOR_PARAMS_DEBUG_DECL += Template("   const $FIELD_TYPE&  _$FIELD_NAME,").substitute(
                                                        FIELD_TYPE = field['sub_msg_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
        elif field.has_key('sub_msg_type_not_nested'):
            CONSTRUCTOR_PARAMS_DEBUG_DECL += Template("   const $FIELD_TYPE&  _$FIELD_NAME,").substitute(
                                                        FIELD_TYPE = field['sub_msg_type_not_nested'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
        elif field.has_key('IN_MSG'):
            CONSTRUCTOR_PARAMS_DEBUG_DECL += Template("   const $FIELD_TYPE&  _$FIELD_NAME,").substitute(
                                                        FIELD_TYPE = 'IC_' + field['IN_MSG'][0],
                                                        FIELD_NAME = field['IN_MSG'][0]
                                                        )
        elif field.has_key('IN_SUB_MSG'):
            CONSTRUCTOR_PARAMS_DEBUG_DECL += Template("   const $FIELD_TYPE&  _$FIELD_NAME,").substitute(
                                                        FIELD_TYPE = 'IC_' + field['IN_SUB_MSG'][0],
                                                        FIELD_NAME = field['IN_SUB_MSG'][0]
                                                        )
        else:
            print "error 1  ---------------------\n" +  str(field)
    return CONSTRUCTOR_PARAMS_DEBUG_DECL







def generate_class(class_name, class_info, class_properties, send_code):
    CLASS_FIELDS = ''
    CONSTRUCTOR_PARAMS_DEBUG_DECL = ''
    INNER_CLASSES = ''
    SUBJECT_METHODS = ''
    
    INHERITS_FROM = ''
    if class_properties.has_key('I') :
        INHERITS_FROM = '   :  public  ' +  class_properties['I']
    
    CLASS_TEMPLATE = """

//-------------------------------
//      ${CLASS_NAME}
//-------------------------------    
class ${CLASS_NAME}     $INHERITS_FROM
{
public:
    //  inner classes
$INNER_CLASSES
    
    // constructor
    explicit ${CLASS_NAME} ( $CONSTRUCTOR_PARAMS_DEBUG_DECL );
    explicit ${CLASS_NAME} ( const qpid::messaging::Message& message );
    virtual ~${CLASS_NAME} (){};
    virtual std::string get_message_type_as_string       (void) const  { return "${CLASS_NAME}"; };
    static  std::string static_get_message_type_as_string(void)        { return "${CLASS_NAME}"; };
    $CODE_AS_QPID_MESSAGE
    

    // fields
$CLASS_FIELDS


    //  subject info
    $SUBJECT_METHODS
    
    
    $POINTER_TO_CONTROL_FIELDS
    
    void        before_send(void) const;
    
private:
    std::string check_recomended(void) const;
};


"""
    #   constructor params
            
    CONSTRUCTOR_PARAMS_DEBUG_DECL = get_constructor_params(class_name, class_info, class_properties, send_code)[:-1]

    #   member definitions
    for field in class_info:
        if field.has_key('field_type'):
            if field['OPTIONS'].count('optional') > 0   or  field['OPTIONS'].count('recomended') > 0:
                CLASS_FIELDS += '    {0:<40}  {1}; \n'.format( 'mtk::nullable<' + field['field_type']+'>', field['FIELD_NAME'])
            else :
                CLASS_FIELDS += '    {0:<40}  {1}; \n'.format( field['field_type'], field['FIELD_NAME'])
        elif field.has_key('sub_msg_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0:
                CLASS_FIELDS += '    {0:<40}  {1}; \n'.format( 'mtk::nullable<' + field['sub_msg_type']+'>', field['FIELD_NAME'])
            else :
                CLASS_FIELDS += '    {0:<40}  {1}; \n'.format( field['sub_msg_type'], field['FIELD_NAME'])
        elif field.has_key('sub_msg_type_not_nested'):
            CLASS_FIELDS += '    {0:<40}  {1}; \n'.format(field['sub_msg_type_not_nested'], field['FIELD_NAME'])
        elif field.has_key('IN_MSG'):
            CLASS_FIELDS += '    {0:<40}  {1}; \n'.format( 'IC_' + field['IN_MSG'][0], field['IN_MSG'][0])
        elif field.has_key('IN_SUB_MSG'):
            CLASS_FIELDS += '    {0:<40}  {1}; \n'.format( 'IC_' + field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][0])
        else:
            print "error 3--------------------------------\n" +  str(field)

    # INNER CLASSES
    for field in class_info:
        if field.has_key('IN_MSG'):
            INNER_CLASSES += generate_class('IC_' + field['IN_MSG'][0], field['IN_MSG'][1], field['IN_MSG'][2], field['IN_MSG'][3])
    for field in class_info:
        if field.has_key('IN_SUB_MSG'):
            INNER_CLASSES += generate_class('IC_' + field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][1], field['IN_SUB_MSG'][2], field['IN_SUB_MSG'][3])
    INNER_CLASSES = INNER_CLASSES.replace('\n', '\n    ')


    pointer_to_control_fields = ''
    code_as_qpid_message = ''
    # SUBJECT_METHODS
    if class_properties.has_key('SUBJ'):
        SUBJECT_METHODS += get_qpidmsg_get_in_subject_forward(class_name, class_info, class_properties, send_code)   
        SUBJECT_METHODS += Template("""virtual std::string  get_out_subject (void) const;\n""").substitute(class_name=class_name)
    if is_message_not_submessage(class_properties):
        pointer_to_control_fields = 'mtk::msg::sub_control_fields*   __internal_warning_control_fields;'
        code_as_qpid_message = 'qpid::messaging::Message qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const;'

    return Template(CLASS_TEMPLATE).substitute(   CLASS_NAME = class_name, 
                                                    CLASS_FIELDS = CLASS_FIELDS,
                                                    CONSTRUCTOR_PARAMS_DEBUG_DECL = CONSTRUCTOR_PARAMS_DEBUG_DECL,
                                                    INNER_CLASSES = INNER_CLASSES,
                                                    INHERITS_FROM = INHERITS_FROM,
                                                    SUBJECT_METHODS = SUBJECT_METHODS,
                                                    POINTER_TO_CONTROL_FIELDS = pointer_to_control_fields,
                                                    CODE_AS_QPID_MESSAGE = code_as_qpid_message
                                                )



def generate_class_in_impl(class_name, class_info, class_properties, send_code):
    CONSTRUCTOR_PARAMS_DEBUG_INIT = ''
    CHECK_RECOMENDED = ''
    CONSTRUCTOR_PARAMS_DEBUG_DECL = ''
    CLASS_NAME_NOT_NESTED = class_name.split('::')[-1]
    IMPL_TEMPLATE = """

${CLASS_NAME}::${CLASS_NAME_NOT_NESTED} ($CONSTRUCTOR_PARAMS_DEBUG_DECL)
    :  $CONSTRUCTOR_PARAMS_DEBUG_INIT 
       $CONTROL_FIELD_INITIALIZER
    {  
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                    MTK_SS(cr<<*this), mtk::alPriorError));
    }



std::string ${CLASS_NAME}::check_recomended(void) const
{
    std::string result;
$CHECK_RECOMENDED
    return result;
}

void ${CLASS_NAME}::before_send(void) const
{
$SEND_CODE
}


"""

    if class_properties.has_key('I'):
        CONSTRUCTOR_PARAMS_DEBUG_INIT += class_properties['I']+'(parent),'

    CONSTRUCTOR_PARAMS_DEBUG_DECL = get_constructor_params (class_name, class_info, class_properties, send_code)
    CONSTRUCTOR_PARAMS_DEBUG_DECL = CONSTRUCTOR_PARAMS_DEBUG_DECL[:-1]

    #CONSTRUCTOR_PARAMS_DEBUG_INIT
    for field in class_info:
        if field.has_key('field_type'):
            CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(_$FIELD_NAME),").substitute(
                                                    FIELD_TYPE = field['field_type'],
                                                    FIELD_NAME = field['FIELD_NAME']
                                                    )
        elif field.has_key('sub_msg_type'):
            CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(_$FIELD_NAME),").substitute(
                                                    FIELD_TYPE = field['sub_msg_type'],
                                                    FIELD_NAME = field['FIELD_NAME']
                                                    )
        elif field.has_key('sub_msg_type_not_nested'):
            CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(_$FIELD_NAME),").substitute(
                                                    FIELD_TYPE = field['sub_msg_type_not_nested'],
                                                    FIELD_NAME = field['FIELD_NAME']
                                                    )
        elif field.has_key('IN_MSG'):
            CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(_$FIELD_NAME),").substitute(
                                                    FIELD_TYPE = 'IC_' + field['IN_MSG'][0],
                                                    FIELD_NAME = field['IN_MSG'][0]
                                                    )
        elif field.has_key('IN_SUB_MSG'):
            CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(_$FIELD_NAME),").substitute(
                                                    FIELD_TYPE = 'IC_' + field['IN_SUB_MSG'][0],
                                                    FIELD_NAME = field['IN_SUB_MSG'][0]
                                                    )
        else:
            print "error 4--------------------------------\n" +  str(field)
            
    CONSTRUCTOR_PARAMS_DEBUG_INIT = CONSTRUCTOR_PARAMS_DEBUG_INIT[:-1]

    CHECK_RECOMENDED = ''
    # CHECK_RECOMENDED
    for field in class_info:
        if field.has_key('OPTIONS'):
            if field['OPTIONS'].count('recomended') > 0:
                CHECK_RECOMENDED += Template("""
    MTK_EXEC_MAX_FREC_S(mtk::dtSeconds(10)) // I know it's for all instances
        if ($FIELD_NAME.HasValue() == false)
            result += "$class_name::check_recomended  missing recomended field **$FIELD_NAME** on $class_name";
    MTK_END_EXEC_MAX_FREC
""").substitute(
                                                    FIELD_NAME = field['FIELD_NAME'],
                                                    class_name = class_name
                                                    )

    control_field_initializer = ''
    if is_message_not_submessage(class_properties):
        control_field_initializer = ', __internal_warning_control_fields(0)'
    

    return Template(IMPL_TEMPLATE).substitute(
            CLASS_NAME = class_name, 
            CONSTRUCTOR_PARAMS_DEBUG_INIT = CONSTRUCTOR_PARAMS_DEBUG_INIT,
            CHECK_RECOMENDED = CHECK_RECOMENDED,
            CONSTRUCTOR_PARAMS_DEBUG_DECL = CONSTRUCTOR_PARAMS_DEBUG_DECL,
            CLASS_NAME_NOT_NESTED = CLASS_NAME_NOT_NESTED,
            CONTROL_FIELD_INITIALIZER = control_field_initializer,
            SEND_CODE = send_code
        )


def look_for_type(type):
    for class_name, class_info, class_properties, send_code in ALL_MESSAGES:
        if class_name == type:
            return class_name, class_info, class_properties, send_code
    return None



def qpid_generate__internal_get_default_forward(class_name, class_info, class_properties, send_code):
    INITIALITATION = ''
    template = """
    $class_name  __internal_get_default($class_name *);
    """
    return Template(template).substitute(class_name=class_name)
    
    
def qpid_generate__internal_get_default(class_name, class_info, class_properties, send_code):
    CLASS_NAME_NOT_NESTED = class_name
    INITIALITATION = ''
    template = """
    $class_name  __internal_get_default($class_name*)
    {
        return $class_name(
$INITIALITATION
            );
    }
    """

    #INITIALITATION
    if class_properties.has_key('I'):
        INITIALITATION += Template("__internal_get_default((${PARENT}*)0), ").substitute(PARENT = class_properties['I'])
    for field in class_info:
        mandatory = True
        if field.has_key('OPTIONS'):
            if field['OPTIONS'].count('optional') > 0   or  field['OPTIONS'].count('recomended') > 0:
                mandatory = False
        if mandatory:
            if field.has_key('field_type'):
                INITIALITATION +=  '//   field_type\n'
                INITIALITATION += Template('   __internal_get_default ((${field_type}*)0),\n').substitute(
                                                        field_type = field['field_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('sub_msg_type'):
                INITIALITATION +=  '//   sub_msg_type\n'
                INITIALITATION += Template('   __internal_get_default((${sub_msg_type}*)0),\n').substitute(
                                                        sub_msg_type = field['sub_msg_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('sub_msg_type_not_nested'):
                INITIALITATION +=  '//   sub_msg_type_not_nested\n'
                INITIALITATION += Template("   __internal_get_default((${sub_msg_type_not_nested}*)0),\n").substitute(
                                                        sub_msg_type_not_nested = field['sub_msg_type_not_nested'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('IN_MSG'):
                INITIALITATION +=  '//   IN_MSG\n'
                INITIALITATION += Template("   __internal_get_default((${FIELD_TYPE}*)0),\n").substitute(
                                                        FIELD_TYPE = CLASS_NAME_NOT_NESTED + '::IC_' + field['IN_MSG'][0],
                                                        FIELD_NAME = field['IN_MSG'][0]
                                                        )
            elif field.has_key('IN_SUB_MSG'):
                INITIALITATION +=  '//   IN_SUB_MSG\n'
                INITIALITATION += Template("   __internal_get_default((${FIELD_TYPE}*)0),\n").substitute(
                                                        FIELD_TYPE = CLASS_NAME_NOT_NESTED + '::IC_' + field['IN_SUB_MSG'][0],
                                                        FIELD_NAME = field['IN_SUB_MSG'][0]
                                                        )
            else:
                print "error 4--------------------------------\n" +  str(field)
        else:
            if field.has_key('field_type'):
                INITIALITATION +=  '//   field_type\n'
                INITIALITATION += Template('   mtk::nullable<${field_type}>(),\n').substitute(
                                                        field_type = field['field_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('sub_msg_type'):
                INITIALITATION +=  '//   sub_msg_type\n'
                INITIALITATION += Template('   mtk::nullable<${sub_msg_type}>(),\n').substitute(
                                                        sub_msg_type = field['sub_msg_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('sub_msg_type_not_nested'):
                INITIALITATION +=  '//   sub_msg_type_not_nested\n'
                INITIALITATION += Template("   mtk::nullable<${sub_msg_type_not_nested}>(),\n").substitute(
                                                        sub_msg_type_not_nested = field['sub_msg_type_not_nested'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('IN_MSG'):
                INITIALITATION +=  '//   IN_MSG\n'
                INITIALITATION += Template("   mtk::nullable<${FIELD_TYPE}>(),\n").substitute(
                                                        FIELD_TYPE = CLASS_NAME_NOT_NESTED + '::IC_' + field['IN_MSG'][0],
                                                        FIELD_NAME = field['IN_MSG'][0]
                                                        )
            elif field.has_key('IN_SUB_MSG'):
                INITIALITATION +=  '//   IN_SUB_MSG\n'
                INITIALITATION += Template("   mtk::nullable<${FIELD_TYPE}>(),\n").substitute(
                                                        FIELD_TYPE = CLASS_NAME_NOT_NESTED + '::IC_' + field['IN_SUB_MSG'][0],
                                                        FIELD_NAME = field['IN_SUB_MSG'][0]
                                                        )
            else:
                print "error 4--------------------------------\n" +  str(field)
        
                
    INITIALITATION = INITIALITATION[:-2]
    return Template(template).substitute( CLASS_NAME_NOT_NESTED=CLASS_NAME_NOT_NESTED, INITIALITATION=INITIALITATION, class_name=class_name)



def ctor_conversion_from_qpid_msg(class_name, class_info, class_properties, send_code):
    CONSTRUCTOR_PARAMS_DEBUG_INIT = ''
    CLASS_NAME_NOT_NESTED = class_name.split('::')[-1]
    IMPL_TEMPLATE = """

${CLASS_NAME}::${CLASS_NAME_NOT_NESTED} (const qpid::messaging::Message& msg)
    :  $CONSTRUCTOR_PARAMS_DEBUG_INIT 
    {
        qpid::types::Variant::Map mv;
        qpid::messaging::decode(msg, mv);
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> map = mv;
        copy(*this, map);
        std::string cr = check_recomended ();  
        if (cr!= "")
            mtk::AlarmMsg(mtk::Alarm(MTK_HERE, "msg_build", 
                MTK_SS(cr<<*this), mtk::alPriorError));
    }

"""

    if class_properties.has_key('I'):
        CONSTRUCTOR_PARAMS_DEBUG_INIT += class_properties['I']+'(msg), '


    #CONSTRUCTOR_PARAMS_DEBUG_INIT
    for field in class_info:
        mandatory = True
        if field.has_key('OPTIONS'):
            if field['OPTIONS'].count('optional') > 0   or  field['OPTIONS'].count('recomended') > 0:
                mandatory = False
        if mandatory:
            if field.has_key('field_type'):
                CONSTRUCTOR_PARAMS_DEBUG_INIT +=  '//   field_type\n'
                CONSTRUCTOR_PARAMS_DEBUG_INIT += Template('   ${FIELD_NAME}(__internal_get_default((${field_type}*)0)),\n').substitute(
                                                        field_type = field['field_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('sub_msg_type'):
                CONSTRUCTOR_PARAMS_DEBUG_INIT +=  '//   sub_msg_type\n'
                CONSTRUCTOR_PARAMS_DEBUG_INIT += Template('   ${FIELD_NAME}(__internal_get_default((${sub_msg_type}*)0)),\n').substitute(
                                                        sub_msg_type = field['sub_msg_type'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('sub_msg_type_not_nested'):
                CONSTRUCTOR_PARAMS_DEBUG_INIT +=  '//   sub_msg_type_not_nested\n'
                CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(__internal_get_default((${sub_msg_type_not_nested}*)0)),\n").substitute(
                                                        sub_msg_type_not_nested = field['sub_msg_type_not_nested'],
                                                        FIELD_NAME = field['FIELD_NAME']
                                                        )
            elif field.has_key('IN_MSG'):
                CONSTRUCTOR_PARAMS_DEBUG_INIT +=  '//   IN_MSG\n'
                CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(__internal_get_default((${FIELD_TYPE}*)0)),\n").substitute(
                                                        FIELD_TYPE = CLASS_NAME_NOT_NESTED + '::IC_' + field['IN_MSG'][0],
                                                        FIELD_NAME = field['IN_MSG'][0]
                                                        )
            elif field.has_key('IN_SUB_MSG'):
                CONSTRUCTOR_PARAMS_DEBUG_INIT +=  '//   IN_SUB_MSG\n'
                CONSTRUCTOR_PARAMS_DEBUG_INIT += Template("   ${FIELD_NAME}(__internal_get_default((${FIELD_TYPE}*)0)),\n").substitute(
                                                        FIELD_TYPE = CLASS_NAME_NOT_NESTED + '::IC_' + field['IN_SUB_MSG'][0],
                                                        FIELD_NAME = field['IN_SUB_MSG'][0]
                                                        )
            else:
                print "error 4--------------------------------\n" +  str(field)
            
    CONSTRUCTOR_PARAMS_DEBUG_INIT = CONSTRUCTOR_PARAMS_DEBUG_INIT[:-2]
    
    
    return Template(IMPL_TEMPLATE).substitute(
            CLASS_NAME = class_name, 
            CONSTRUCTOR_PARAMS_DEBUG_INIT = CONSTRUCTOR_PARAMS_DEBUG_INIT,
            CLASS_NAME_NOT_NESTED = CLASS_NAME_NOT_NESTED
        )









def generate__internal_qpid_fill(class_name, class_info, class_properties, send_code):
    CLASS_NAME_NOT_NESTED = class_name.split('::')[-1]
    PARENT = ''
    if class_properties.has_key('I'):
        PARENT = Template('copy(static_cast<${parent}&>(c), v);').substitute(parent=class_properties['I'])
    IMPL_TEMPLATE = """

//void  __internal_qpid_fill (${CLASS_NAME}& c, std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv)
void  copy (${CLASS_NAME}& c, const qpid::types::Variant& v)
    {  
        const std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> mv = v.asMap();
$PARENT
        std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant>::const_iterator it;
$FILL_FIELDS
    }

"""
    
    FILL_FIELDS = ''
    # FILL_FIELDS
    for field in class_info:
        mandatory = True
        preMorph, postMorph = "", ""
        if field.has_key('OPTIONS'):
            if field['OPTIONS'].count('optional') > 0   or  field['OPTIONS'].count('recomended') > 0:
                mandatory = False
        if field.has_key('field_type'):
            FILL_FIELDS +=  '//   field_type\n'
            if mandatory:
                FILL_FIELDS += Template("""
                    it = mv.find("$FIELD_TAG");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ${FIELD_NAME} on message ${CLASS_NAME}::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.${FIELD_NAME}, it->second);
                        //c.${FIELD_NAME} = ${preMorph}it->second${postMorph};\n""").substitute(
                                                        FIELD_TAG = field['FIELD_TAG'],
                                                        FIELD_NAME = field['FIELD_NAME'],
                                                        preMorph = preMorph,
                                                        postMorph = postMorph,
                                                        CLASS_NAME=class_name
                                                        )
            else:
                FILL_FIELDS += Template("""
                    it = mv.find("$FIELD_TAG");
                    if (it!= mv.end())
                        copy(c.${FIELD_NAME}, it->second);
                        //c.${FIELD_NAME} = ${preMorph}it->second${postMorph};\n""").substitute(
                                                        FIELD_TAG = field['FIELD_TAG'],
                                                        FIELD_NAME = field['FIELD_NAME'],
                                                        preMorph = preMorph,
                                                        postMorph = postMorph,
                                                        CLASS_NAME=class_name
                                                        )
        elif field.has_key('sub_msg_type'):
            FILL_FIELDS +=  '//   sub_msg_type\n'
            preMorph, postMorph = '', ''
            if mandatory:
                FILL_FIELDS += Template("""
                    it = mv.find("$FIELD_TAG");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ${FIELD_NAME} on message ${CLASS_NAME}::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.${FIELD_NAME}, it->second);
                        //__internal_qpid_fill(c.${FIELD_NAME}, ${preMorph}it->second.asMap()${postMorph});\n""").substitute(
                                                        FIELD_TAG = field['FIELD_TAG'],
                                                        FIELD_NAME = field['FIELD_NAME'],
                                                        preMorph = preMorph,
                                                        postMorph = postMorph,
                                                        CLASS_NAME=class_name
                                                        )
            else:
                FILL_FIELDS += Template("""
                    it = mv.find("$FIELD_TAG");
                    if (it!= mv.end())
                        copy(c.${FIELD_NAME}, it->second);
                        //__internal_qpid_fill(c.${FIELD_NAME}, ${preMorph}it->second.asMap()${postMorph});\n""").substitute(
                                                        FIELD_TAG = field['FIELD_TAG'],
                                                        FIELD_NAME = field['FIELD_NAME'],
                                                        preMorph = preMorph,
                                                        postMorph = postMorph,
                                                        CLASS_NAME=class_name
                                                        )
        elif field.has_key('sub_msg_type_not_nested'):
            FILL_FIELDS +=  '//   sub_msg_type_not_nested\n'
            preMorph, postMorph = '',''
            FILL_FIELDS += Template("""
                copy(c.${FIELD_NAME}, mv);
                //__internal_qpid_fill(c.${FIELD_NAME}, ${preMorph}mv${postMorph});\n""").substitute(
                                                    FIELD_NAME = field['FIELD_NAME'],
                                                    preMorph = preMorph,
                                                    postMorph = postMorph,
                                                    CLASS_NAME=class_name
                                                    )
        elif field.has_key('IN_MSG'):
            FILL_FIELDS +=  '//   IN_MSG\n'
            preMorph, postMorph = '',''
            FILL_FIELDS += Template("""
                copy(c.${FIELD_NAME}, mv);
                //__internal_qpid_fill(c.${FIELD_NAME}, ${preMorph}mv${postMorph});\n""").substitute(
                                                    FIELD_NAME = field['IN_MSG'][0],
                                                    preMorph = preMorph,
                                                    postMorph = postMorph,
                                                    CLASS_NAME=class_name
                                                    )
        elif field.has_key('IN_SUB_MSG'):
            FILL_FIELDS +=  '//   IN_SUB_MSG\n'
            preMorph, postMorph = '',''
            if mandatory:
                FILL_FIELDS += Template("""
                    it = mv.find("$FIELD_TAG");
                    if (it== mv.end())
                        throw mtk::Alarm(MTK_HERE, "msg_build", "missing mandatory field ${FIELD_NAME} on message ${CLASS_NAME}::__internal_qpid_fill", mtk::alPriorCritic);
                    else
                        copy(c.${FIELD_NAME}, it->second);
                        //__internal_qpid_fill(c.${FIELD_NAME}, ${preMorph}it->second.asMap()${postMorph});\n""").substitute(
                                                        FIELD_TAG = field['IN_SUB_MSG'][4],
                                                        FIELD_NAME = field['IN_SUB_MSG'][0],
                                                        preMorph = preMorph,
                                                        postMorph = postMorph,
                                                        CLASS_NAME=class_name
                                                        )
            else:
                FILL_FIELDS += Template("""
                    it = mv.find("$FIELD_TAG");
                    if (it!= mv.end())
                        copy(c.${FIELD_NAME}, it->second);
                        //__internal_qpid_fill(c.${FIELD_NAME}, ${preMorph}it->second.asMap()${postMorph});\n""").substitute(
                                                        FIELD_TAG = field['IN_SUB_MSG'][4],
                                                        FIELD_NAME = field['IN_SUB_MSG'][0],
                                                        preMorph = preMorph,
                                                        postMorph = postMorph,
                                                        CLASS_NAME=class_name
                                                        )
            
        else:
            print "error 4--------------------------------\n" +  str(field)

    
    return Template(IMPL_TEMPLATE).substitute(
            CLASS_NAME = class_name, 
            FILL_FIELDS = FILL_FIELDS,
            PARENT = PARENT
        )


def generate_output_stream_operator_forward(class_name, class_info, class_properties, send_code) :
    METHOD = """    std::ostream& operator<< (std::ostream& o, const $class_name & c);\n"""
    METHOD += """   YAML::Emitter& operator << (YAML::Emitter&    o, const $class_name & c);\n"""
    METHOD += """   void           operator >> (const YAML::Node& n,       $class_name & c);\n"""
    return Template(METHOD).substitute(class_name=class_name)

def generate_output_stream_operator(class_name, class_info, class_properties, send_code) :
    OUPUT_PER_FIELD = ''
    RECURSION_OUTPUT = ''
    OUTPUT_PARENT = ''

    if class_properties.has_key('I'):
        OUTPUT_PARENT = '    << "("  <<  static_cast<const ' + class_properties['I'] + '&>(c)  << ")" '
    
    METHOD = """
std::ostream& operator<< (std::ostream& o, const $class_name & c)
{
    o << "{ "
$OUTPUT_PARENT
$OUPUT_PER_FIELD
        << " }";
    return o;
};

"""
    for field in class_info:
        if field.has_key('field_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0 :
                OUPUT_PER_FIELD += '        << "'+field['FIELD_NAME']+':"<<   c.' + field['FIELD_NAME'] + ' << "  "'
            else :
                OUPUT_PER_FIELD += '        << "'+field['FIELD_NAME']+':"<<   c.' + field['FIELD_NAME'] + ' << "  "'
        elif field.has_key('sub_msg_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0 :
                OUPUT_PER_FIELD += '        << "'+field['FIELD_NAME']+':"<< c.' + field['FIELD_NAME'] + '<<"  "'
            else :
                OUPUT_PER_FIELD += '        << "'+field['FIELD_NAME']+':"<< c.' + field['FIELD_NAME'] + '<<"  "'
        elif field.has_key('sub_msg_type_not_nested'):
            OUPUT_PER_FIELD += '        << "'+field['FIELD_NAME']+':"<< c.' + field['FIELD_NAME'] + '<<"  "'
        elif field.has_key('IN_MSG'):
            OUPUT_PER_FIELD += '        << "'+field['IN_MSG'][0]+':"<< c.' + field['IN_MSG'][0] + '<<"  "'
            RECURSION_OUTPUT += generate_output_stream_operator(class_name+'::IC_'+field['IN_MSG'][0], field['IN_MSG'][1], class_properties, send_code)
        elif field.has_key('IN_SUB_MSG'):
            OUPUT_PER_FIELD += '        << "'+field['IN_SUB_MSG'][0]+':"<< c.' + field['IN_SUB_MSG'][0] + '<<"  "'
            RECURSION_OUTPUT += generate_output_stream_operator(class_name+'::IC_'+field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][1], class_properties, send_code)
        else:
            print "error 7--------------------------------\n" +  str(field)
    return RECURSION_OUTPUT + Template(METHOD).substitute(class_name=class_name, OUPUT_PER_FIELD=OUPUT_PER_FIELD, OUTPUT_PARENT=OUTPUT_PARENT)


def generate_output_yaml_operator(class_name, class_info, class_properties, send_code) :
    OUPUT_PER_FIELD = ''
    RECURSION_OUTPUT = ''
    OUTPUT_PARENT = ''

    if class_properties.has_key('I'):
        OUTPUT_PARENT = '    << YAML::Key << "'+class_properties['I'] +'" <<  YAML::Value << static_cast<const ' + class_properties['I'] + '&>(c)  '
    
    METHOD = """

YAML::Emitter& operator << (YAML::Emitter& o, const $class_name & c)
{
    o << YAML::BeginMap
$OUTPUT_PARENT
$OUPUT_PER_FIELD
        << YAML::EndMap;
    return o;
};

"""
    for field in class_info:
        if field.has_key('field_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0 :
                OUPUT_PER_FIELD += '        << YAML::Key << "'+field['FIELD_NAME']+'"  << YAML::Value <<   c.' + field['FIELD_NAME']
            else :
                OUPUT_PER_FIELD += '        << YAML::Key << "'+field['FIELD_NAME']+'"  << YAML::Value <<   c.' + field['FIELD_NAME']
        elif field.has_key('sub_msg_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0 :
                OUPUT_PER_FIELD += '        << YAML::Key << "'+field['FIELD_NAME']+'"  << YAML::Value << c.' + field['FIELD_NAME']
            else :
                OUPUT_PER_FIELD += '        << YAML::Key << "'+field['FIELD_NAME']+'"  << YAML::Value << c.' + field['FIELD_NAME']
        elif field.has_key('sub_msg_type_not_nested'):
            OUPUT_PER_FIELD += '        << YAML::Key << "'+field['FIELD_NAME']+'"    << YAML::Value << c.' + field['FIELD_NAME']
        elif field.has_key('IN_MSG'):
            OUPUT_PER_FIELD += '        << YAML::Key << "'+field['IN_MSG'][0]+'"   << YAML::Value << c.' + field['IN_MSG'][0]
            RECURSION_OUTPUT += generate_output_yaml_operator(class_name+'::IC_'+field['IN_MSG'][0], field['IN_MSG'][1], class_properties, send_code)
        elif field.has_key('IN_SUB_MSG'):
            OUPUT_PER_FIELD += '        << YAML::Key << "'+field['IN_SUB_MSG'][0]+'"   << YAML::Value << c.' + field['IN_SUB_MSG'][0]
            RECURSION_OUTPUT += generate_output_yaml_operator(class_name+'::IC_'+field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][1], class_properties, send_code)
        else:
            print "error 7--------------------------------\n" +  str(field)
    return RECURSION_OUTPUT + Template(METHOD).substitute(class_name=class_name, OUPUT_PER_FIELD=OUPUT_PER_FIELD, OUTPUT_PARENT=OUTPUT_PARENT)


def generate_input_yaml_operator(class_name, class_info, class_properties, send_code) :
    OUPUT_PER_FIELD = ''
    RECURSION_OUTPUT = ''
    OUTPUT_PARENT = ''

    if class_properties.has_key('I'):
        OUTPUT_PARENT = '    node["'+class_properties['I'] +'"]   >>   static_cast<' + class_properties['I'] + '&>(c)  ;\n'
    
    METHOD = """

void  operator >> (const YAML::Node& node, $class_name & c)
{

$OUTPUT_PARENT
$OUPUT_PER_FIELD

};

"""
    for field in class_info:
        if field.has_key('field_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0 :
                OUPUT_PER_FIELD += '        node["'+field['FIELD_NAME']+'"]  >> c.' + field['FIELD_NAME'] + ";\n"
            else :
                OUPUT_PER_FIELD += '        node["'+field['FIELD_NAME']+'"]  >> c.' + field['FIELD_NAME'] + ";\n"
        elif field.has_key('sub_msg_type'):
            if field['OPTIONS'].count('optional') > 0  or  field['OPTIONS'].count('recomended') > 0 :
                OUPUT_PER_FIELD += '        node["'+field['FIELD_NAME']+'"]  >> c.' + field['FIELD_NAME'] + ";\n"
            else :
                OUPUT_PER_FIELD += '        node["'+field['FIELD_NAME']+'"]  >> c.' + field['FIELD_NAME'] + ";\n"
        elif field.has_key('sub_msg_type_not_nested'):
            OUPUT_PER_FIELD     += '        node["'+field['FIELD_NAME']+'"]  >> c.' + field['FIELD_NAME'] + ";\n"
        elif field.has_key('IN_MSG'):
            OUPUT_PER_FIELD += '            node["'+field['IN_MSG'][0]+'"]   >> c.' + field['IN_MSG'][0] + ";\n"
            RECURSION_OUTPUT += generate_input_yaml_operator(class_name+'::IC_'+field['IN_MSG'][0], field['IN_MSG'][1], class_properties, send_code)
        elif field.has_key('IN_SUB_MSG'):
            OUPUT_PER_FIELD += '            node["'+field['IN_SUB_MSG'][0]+'"] >>  c.' + field['IN_SUB_MSG'][0] + ";\n"
            RECURSION_OUTPUT += generate_input_yaml_operator(class_name+'::IC_'+field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][1], class_properties, send_code)
        else:
            print "error 7--------------------------------\n" +  str(field)
    return RECURSION_OUTPUT + Template(METHOD).substitute(class_name=class_name, OUPUT_PER_FIELD=OUPUT_PER_FIELD, OUTPUT_PARENT=OUTPUT_PARENT)



def generate_equal_operator_forward_declaration(class_name, class_info, class_properties, send_code) :
    OUPUT_PER_FIELD = ''
    RECURSION_OUTPUT = ''
    OUTPUT_PARENT = ''

    if class_properties.has_key('I'):
        OUTPUT_PARENT = '(static_cast<const ' + class_properties['I'] + '&>(a)   ==  static_cast<const ' + class_properties['I'] + '&>(b))  &&  '
    
    METHOD = """
bool operator== (const $class_name& a, const $class_name& b);
bool operator!= (const $class_name& a, const $class_name& b);

"""
    for field in class_info:
        if field.has_key('field_type'):
            OUPUT_PER_FIELD += '        a.'+field['FIELD_NAME']+' ==  b.' + field['FIELD_NAME']  + '  &&  '
        elif field.has_key('sub_msg_type'):
            OUPUT_PER_FIELD += '        a.'+field['FIELD_NAME']+' ==  b.' + field['FIELD_NAME']  + '  &&  '
        elif field.has_key('sub_msg_type_not_nested'):
            OUPUT_PER_FIELD += '        a.'+field['FIELD_NAME']+' ==  b.' + field['FIELD_NAME']  + '  &&  '
        elif field.has_key('IN_MSG'):
            OUPUT_PER_FIELD += '        a.'+field['IN_MSG'][0] +' ==  b.' + field['IN_MSG'][0]   + '  &&  '
            RECURSION_OUTPUT += generate_equal_operator_forward_declaration(class_name+'::IC_'+field['IN_MSG'][0], field['IN_MSG'][1], class_properties, send_code)
        elif field.has_key('IN_SUB_MSG'):
            OUPUT_PER_FIELD += '        a.'+field['IN_SUB_MSG'][0]+'  ==  b.' + field['IN_SUB_MSG'][0] + '  &&  '
            RECURSION_OUTPUT += generate_equal_operator_forward_declaration(class_name+'::IC_'+field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][1], class_properties, send_code)
        else:
            print "error 7--------------------------------\n" +  str(field)
    OUPUT_PER_FIELD += ' true '
    return RECURSION_OUTPUT + Template(METHOD).substitute(class_name=class_name, OUPUT_PER_FIELD=OUPUT_PER_FIELD, OUTPUT_PARENT=OUTPUT_PARENT)


def generate_equal_operator(class_name, class_info, class_properties, send_code) :
    OUPUT_PER_FIELD = ''
    RECURSION_OUTPUT = ''
    OUTPUT_PARENT = ''

    if class_properties.has_key('I'):
        OUTPUT_PARENT = '(static_cast<const ' + class_properties['I'] + '&>(a)   ==  static_cast<const ' + class_properties['I'] + '&>(b))  &&  '
    
    METHOD = """
bool operator== (const $class_name& a, const $class_name& b)
{
    return ( $OUTPUT_PARENT $OUPUT_PER_FIELD );
};

bool operator!= (const $class_name& a, const $class_name& b)
{
    return !(a==b);
};


"""
    for field in class_info:
        if field.has_key('field_type'):
            OUPUT_PER_FIELD += '        a.'+field['FIELD_NAME']+' ==  b.' + field['FIELD_NAME']  + '  &&  '
        elif field.has_key('sub_msg_type'):
            OUPUT_PER_FIELD += '        a.'+field['FIELD_NAME']+' ==  b.' + field['FIELD_NAME']  + '  &&  '
        elif field.has_key('sub_msg_type_not_nested'):
            OUPUT_PER_FIELD += '        a.'+field['FIELD_NAME']+' ==  b.' + field['FIELD_NAME']  + '  &&  '
        elif field.has_key('IN_MSG'):
            OUPUT_PER_FIELD += '        a.'+field['IN_MSG'][0] +' ==  b.' + field['IN_MSG'][0]   + '  &&  '
            RECURSION_OUTPUT += generate_equal_operator(class_name+'::IC_'+field['IN_MSG'][0], field['IN_MSG'][1], class_properties, send_code)
        elif field.has_key('IN_SUB_MSG'):
            OUPUT_PER_FIELD += '        a.'+field['IN_SUB_MSG'][0]+'  ==  b.' + field['IN_SUB_MSG'][0] + '  &&  '
            RECURSION_OUTPUT += generate_equal_operator(class_name+'::IC_'+field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][1], class_properties, send_code)
        else:
            print "error 7--------------------------------\n" +  str(field)
    OUPUT_PER_FIELD += ' true '
    return RECURSION_OUTPUT + Template(METHOD).substitute(class_name=class_name, OUPUT_PER_FIELD=OUPUT_PER_FIELD, OUTPUT_PARENT=OUTPUT_PARENT)




def generate_qpid_coding___fill_qpid_Map (class_name, class_info, class_properties, send_code) :
    OUPUT_PER_FIELD = ''
    RECURSION_OUTPUT = ''
    OUTPUT_PARENT = ''

    METHOD = """
void __internal_add2map (qpid::types::Variant::Map& map, const $class_name& a)
{

    a.before_send();

$OUTPUT_PARENT
$OUPUT_PER_FIELD

};


void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<$class_name>& a, const std::string& field)
{
    if(a.HasValue())
        __internal_add2map(map, a.Get(), field);
}



"""

    if class_properties.has_key('I'):
        OUTPUT_PARENT = '//  parent\n'
        OUTPUT_PARENT += '__internal_add2map(map, static_cast<const '+ class_properties['I'] + '&>(a));\n'
    for field in class_info:
        get_optional = ''
        if field.has_key('OPTIONS'):
            if field['OPTIONS'].count('optional') or  field['OPTIONS'].count('recomended'):
                OUPUT_PER_FIELD += 'if (a.'+field['FIELD_NAME']+'.HasValue())\n'
        if field.has_key('field_type'):
            preMorph, postMorph = '',''
        if field.has_key('field_type'):
            OUPUT_PER_FIELD += '//  field_type\n'
            OUPUT_PER_FIELD += '        __internal_add2map(map, a.' +field['FIELD_NAME'] + ', std::string("'+ field['FIELD_TAG'] +'"));\n'
        elif field.has_key('sub_msg_type'):
            OUPUT_PER_FIELD += '//  sub_msg_type\n'
            OUPUT_PER_FIELD += '        __internal_add2map(map, a.' +field['FIELD_NAME'] + ', std::string("'+ field['FIELD_TAG'] +'"));\n'
        elif field.has_key('sub_msg_type_not_nested'):
            OUPUT_PER_FIELD += '//  sub_msg_type_not_nested\n'
            OUPUT_PER_FIELD += '        __internal_add2map(map, ' + 'a.' +field['FIELD_NAME'] + get_optional  + ');\n'
        elif field.has_key('IN_MSG'):
            OUPUT_PER_FIELD += '//  IN_MSG\n'
            OUPUT_PER_FIELD += '        __internal_add2map(map, ' + 'a.' + field['IN_MSG'][0] + get_optional  + ');\n'
        elif field.has_key('IN_SUB_MSG'):
            OUPUT_PER_FIELD += '//  IN_SUB_MSG\n'
            OUPUT_PER_FIELD += '//        map["'+ field['IN_SUB_MSG'][4] +'"] =  qpidmsg_coded_as_qpid_Map(' + 'a.' + field['IN_SUB_MSG'][0] + get_optional + ');\n'
            OUPUT_PER_FIELD += '        __internal_add2map(map, ' + 'a.' + field['IN_SUB_MSG'][0] + ');\n'
        else:
            print "error 7--------------------------------\n" +  str(field)
    return RECURSION_OUTPUT + Template(METHOD).substitute(class_name=class_name, OUPUT_PER_FIELD=OUPUT_PER_FIELD, OUTPUT_PARENT=OUTPUT_PARENT)




def generate_qpid_coding___codded_as_qpid_message (class_name, class_info, class_properties, send_code) :
    if is_message_not_submessage(class_properties) == False:
        return ''
    
    OUPUT_PER_FIELD = ''
    RECURSION_OUTPUT = ''
    OUTPUT_PARENT = ''

    METHOD = """
qpid::messaging::Message ${class_name}::qpidmsg_codded_as_qpid_message (const std::string& control_fluct_key) const
{
    qpid::messaging::Message __message;
    qpid::types::Variant::Map content;

$OUTPUT_PARENT
$OUPUT_PER_FIELD

    mtk::msg::sub_control_fields control_fields(static_get_message_type_as_string(), control_fluct_key, mtk::dtNowLocal());
    //content["_cf_"] =  qpidmsg_coded_as_qpid_Map(control_fields);
    __internal_add2map(content, control_fields, std::string("_cf_"));

    
    qpid::messaging::encode(content, __message);
    return __message;
};



"""

    if class_properties.has_key('I'):
        OUTPUT_PARENT = '//  parent\n'
        OUTPUT_PARENT += '__internal_add2map(content, static_cast<const '+ class_properties['I'] + '&>(*this));\n'
    for field in class_info:
        get_optional = ''
        if field.has_key('OPTIONS'):
            if field['OPTIONS'].count('optional') or  field['OPTIONS'].count('recomended'):
                OUPUT_PER_FIELD += '//if (this->'+field['FIELD_NAME']+'.HasValue())\n'
        if field.has_key('field_type'):
            pre_morph, post_morph = '',''
        if field.has_key('field_type'):
            OUPUT_PER_FIELD += '//  field_type\n'
            OUPUT_PER_FIELD += '//        content["'+ field['FIELD_TAG'] +'"] = '+pre_morph + 'this->'+field['FIELD_NAME'] + get_optional + post_morph +';\n'
            OUPUT_PER_FIELD += '        __internal_add2map(content, this->'+field['FIELD_NAME'] + ', std::string("'+ field['FIELD_TAG'] +'"));\n'
        elif field.has_key('sub_msg_type'):
            OUPUT_PER_FIELD += '//  sub_msg_type\n'
            OUPUT_PER_FIELD += '//        content["'+ field['FIELD_TAG'] +'"] =  qpidmsg_coded_as_qpid_Map('+'this->' + field['FIELD_NAME'] + get_optional + ');\n'
            OUPUT_PER_FIELD += '        __internal_add2map(content, this->'+field['FIELD_NAME'] + ', std::string("'+ field['FIELD_TAG'] +'"));\n'
        elif field.has_key('sub_msg_type_not_nested'):
            OUPUT_PER_FIELD += '//  sub_msg_type_not_nested\n'
            OUPUT_PER_FIELD += '        __internal_add2map(content, '+'this->' + field['FIELD_NAME'] + get_optional + ');\n'
        elif field.has_key('IN_MSG'):
            OUPUT_PER_FIELD += '//  IN_MSG\n'
            OUPUT_PER_FIELD += '        __internal_add2map(content, '+'this->' + field['IN_MSG'][0] + get_optional+ ');\n'
        elif field.has_key('IN_SUB_MSG'):
            OUPUT_PER_FIELD += '//  IN_SUB_MSG\n'
            OUPUT_PER_FIELD += '//        content["'+ field['IN_SUB_MSG'][4] +'"] =  qpidmsg_coded_as_qpid_Map('+ 'this->' + field['IN_SUB_MSG'][0] + get_optional+ ');\n'
            OUPUT_PER_FIELD += '        __internal_add2map(content, this->'+field['IN_SUB_MSG'][0] + ', std::string("'+ field['IN_SUB_MSG'][4] +'"));\n'
        else:
            print "error 7--------------------------------\n" +  str(field)
    return RECURSION_OUTPUT + Template(METHOD).substitute(class_name=class_name, OUPUT_PER_FIELD=OUPUT_PER_FIELD, OUTPUT_PARENT=OUTPUT_PARENT)






def generate_msg_to_qpid() :
    
    result = ''
    
    
    # implementation
    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES :
        result += generate__internal_qpid_fill(class_name, class_info, class_properties, send_code)
        result += generate_qpid_coding___fill_qpid_Map(class_name, class_info, class_properties, send_code)
        
    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES :
        result += '//generate_qpid_coding___coded_as_qpid_Map(class_name, class_info, class_properties, send_code)\n'


    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        result += generate_qpid_coding___codded_as_qpid_message(class_name, class_info, class_properties, send_code)
    return result



def get_inner_classes(class_name, class_info, class_properties, send_code) :
    result =[]
    result.append((class_name, class_info, class_properties, send_code))
    # INNER CLASSES
    for field in class_info:
        if field.has_key('IN_MSG'):
            result += get_inner_classes(class_name + '::IC_' + field['IN_MSG'][0], field['IN_MSG'][1], field['IN_MSG'][2], field['IN_MSG'][3])
    for field in class_info:
        if field.has_key('IN_SUB_MSG'):
            result += get_inner_classes(class_name + '::IC_' + field['IN_SUB_MSG'][0], field['IN_SUB_MSG'][1], field['IN_SUB_MSG'][2], field['IN_SUB_MSG'][3])
    return result

def get_all_classes_included_inner() :
    result =[]
    for class_name, class_info, class_properties, send_code  in MESSAGES:
        result += get_inner_classes (class_name, class_info, class_properties, send_code)
    return result



def get_qpidmsg_get_in_subject_forward(class_name, class_info, class_properties, send_code) :
    result = ''
    qpidmsg_get_in_subject_params = []
    if class_properties.has_key('SUBJ'):
        for p in re.findall('[^\$\{]*\$\{([^\}]*)', class_properties["SUBJ"]):
            param_name = p.replace('.', '_').replace('(','').replace(')','')
            qpidmsg_get_in_subject_params.append("const std::string& "+ param_name)
        result += Template("""static std::string  get_in_subject ($PARAMS);\n""").substitute(class_name=class_name, PARAMS=','.join(qpidmsg_get_in_subject_params))
    return result

def get_qpidmsg_get_in_subject(class_name, class_info, class_properties, send_code) :
    result = ''
    qpidmsg_get_in_subject_params = []
    if class_properties.has_key('SUBJ'):
        subject = class_properties["SUBJ"]
        for p in re.findall('[^\$\{]*\$\{([^\}]*)', class_properties["SUBJ"]):
            param_name = p.replace('.', '_').replace('(','').replace(')','')
            qpidmsg_get_in_subject_params.append("const std::string& "+ param_name)
            subject = subject.replace(p, p.replace('.', '_'))
        result += Template("""std::string  ${class_name}::get_in_subject ($PARAMS)
    {
        return MTK_SS("$BUILD_STRING");
    }
    """).substitute(class_name=class_name, PARAMS=','.join(qpidmsg_get_in_subject_params), BUILD_STRING=subject.replace('${','" << ').replace('}',' << "').replace('(','').replace(')',''))
    return result

def get_qpidmsg_get_out_subject(class_name, class_info, class_properties, send_code) :
    result = ''
    if class_properties.has_key('SUBJ'):
        result += Template("""std::string  ${class_name}::get_out_subject (void) const
    {
        return MTK_SS("$BUILD_STRING");
    }
    """).substitute(class_name=class_name, 
                    BUILD_STRING=class_properties["SUBJ"].replace('${','" << this->').replace('}',' << "'))
    return result






for file in sys.argv[1:] :
    ORIG_FILE = file
    FOLDER_DESTINATION = os.path.split(ORIG_FILE)[0]
    FILE_NAME = os.path.splitext(os.path.split(file)[-1])[0]
    DEST_FILE_H = os.path.join(FOLDER_DESTINATION, FILE_NAME +'.h')
    DEST_FILE_CPP = os.path.join(FOLDER_DESTINATION, FILE_NAME +'.cpp')


    # check files dates
    if os.path.exists(DEST_FILE_H):
        if time.ctime(os.path.getmtime(ORIG_FILE)) <= time.ctime(os.path.getmtime(DEST_FILE_H))  and time.ctime(os.path.getmtime(sys.argv[0])) <= time.ctime(os.path.getmtime(DEST_FILE_H)):
            print DEST_FILE_H + " already updated"
            ##exit(0)
    if os.path.exists(DEST_FILE_CPP):
        if time.ctime(os.path.getmtime(ORIG_FILE)) <= time.ctime(os.path.getmtime(DEST_FILE_CPP))  and time.ctime(os.path.getmtime(sys.argv[0])) <= time.ctime(os.path.getmtime(DEST_FILE_CPP)):
            print DEST_FILE_CPP + " already updated"



    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # execute_dhp()
    def execute_dhp():
        pipe = os.popen( os.path.join(TOOLS_PATH, 'dhp') + ' ' 
                        + os.path.join(TOOLS_PATH, 'build_msg.gram ') +  ORIG_FILE)
        return pipe.readlines()
        

    # execute_dhp()
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



    if TESTING == False:
        exec('\n'.join(execute_dhp()))

    ALL_MESSAGES = get_all_classes_included_inner()

    BEGIN_NAMESPACE = '\n\n'
    END_NAMESPACE = '\n\n'
    for namespace in NAMESPACES:
        BEGIN_NAMESPACE += 'namespace '+ namespace + ' { \n'
        END_NAMESPACE   += '};   //namespace ' + namespace + ' {\n'
    BEGIN_NAMESPACE += '\n\n'
    END_NAMESPACE += '\n\n'


    NOT_CONTROL_FIELDS = ''
    if os.path.basename(ORIG_FILE) != 'msg_control_fields.msg':
        NOT_CONTROL_FIELDS = '#include "mtk_qpid/mtk_qpid.hpp"'
        # control fields has no register messages
        # this is necessary to break loops on include definitions
    content_file_h = Template("""
#ifndef  $HEADER_GUARD
#define  $HEADER_GUARD


// generated automatically
// coded last modification:        _CODED_LAST_MODIF


#include "yaml/yaml.h"
#include "support/nullable.hpp"
#include "support/fixed_number.h"
#include "support/date_time.h"
#include "support/list.hpp"
#include "support/alarm.h"
#include "support/exec_max_frec.h"
#include "mtk_qpid/qpid_msg_support.hpp"
#include "support/mtk_string.h"
#include <qpid/messaging/Message.h>
#include "mtk_qpid/msg_control_fields.h"

$NOT_CONTROL_FIELDS


""").substitute(HEADER_GUARD = '__' +FILE_NAME + '__', 
            ##CODED_LAST_MODIF=str(time.ctime(os.path.getmtime(ORIG_FILE))),   ##SCRIPT_LAST_MODIF=str(time.ctime(os.path.getmtime(sys.argv[0]))),
            NOT_CONTROL_FIELDS = NOT_CONTROL_FIELDS)

    content_file_h += '\n'.join(INCLUDES)

    content_file_h += BEGIN_NAMESPACE    


    for class_name, class_info, class_properties, send_code in MESSAGES:
        content_file_h += generate_class(class_name, class_info, class_properties, send_code)
        

    # public forward declarations
    content_file_h += """
    
    
    
//  fordward declarations-----------------------------------------------------------\n"""
    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        content_file_h += generate_output_stream_operator_forward(class_name, class_info, class_properties, send_code)
        content_file_h += generate_equal_operator_forward_declaration(class_name, class_info, class_properties, send_code)

    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        content_file_h += Template("""qpid::messaging::Message      qpidmsg_codded_as_qpid_message (const $class_name& a);\n""").substitute(class_name=class_name)
        content_file_h += Template("""void __internal_add2map (qpid::types::Variant::Map& map, const $class_name& a);\n""").substitute(class_name=class_name)
        content_file_h += Template("""void __internal_add2map (qpid::types::Variant::Map& map, const mtk::nullable<$class_name>& a, const std::string& field);\n""").substitute(class_name=class_name)
        content_file_h += Template("""void copy ($class_name& a, const qpid::types::Variant& map);\n""").substitute(class_name=class_name)

    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        content_file_h += qpid_generate__internal_get_default_forward(class_name, class_info, class_properties, send_code)

    content_file_h +=  END_NAMESPACE 
    
    content_file_h += '\n\n'
    content_file_h += """
    
template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v);


"""
    
    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        if is_message_not_submessage(class_properties):
            ##if class_name != 'sub_control_fields' :
            content_file_h += 'MTK_QPID_REGISTER_FACTORY_HANDLE_QPID_EXCHANGE(' + '::'.join(NAMESPACES) + '::' + class_name +')\n'
    content_file_h += '\n\n'

    content_file_h +=  '\n\n#endif\n'
    
    
    
    
    


    content_file_cpp = ("""
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

""")##.substitute(CODED_LAST_MODIF=str(time.ctime(os.path.getmtime(ORIG_FILE))))##, SCRIPT_LAST_MODIF=str(time.ctime(os.path.getmtime(sys.argv[0]))))

    content_file_cpp += '#include "' + os.path.basename(DEST_FILE_H) + '"'



    
    content_file_cpp += BEGIN_NAMESPACE    
    content_file_cpp += """




    inline std::string  __internal_get_default(std::string*)
    {
        return std::string();
    }

    inline mtk::Double __internal_get_default(mtk::Double*)
    {
        return mtk::Double(0.0);
    }
    inline mtk::FixedNumber __internal_get_default(mtk::FixedNumber*)
    {
        return mtk::FixedNumber(mtk::fnDouble(0), mtk::fnDec(0), mtk::fnInc(1));
    }
    
    inline mtk::DateTime __internal_get_default(mtk::DateTime*)
    {
        return mtk::DateTime(mtk::dtYear(2000), mtk::dtMonth(1), mtk::dtDay(1));
    }
    inline mtk::dtTimeQuantity __internal_get_default(mtk::dtTimeQuantity*)
    {
        return mtk::dtTimeQuantity(mtk::dtHours(0), mtk::dtMinutes(0), mtk::dtSeconds(0), mtk::dtMilliseconds(0));
    }
    inline bool __internal_get_default(bool*)
    {
        return false;
    }
    inline int8_t __internal_get_default(int8_t*)
    {
        return 0;
    }
    inline int16_t  __internal_get_default(int16_t*)
    {
        return 0;
    }
    inline int32_t  __internal_get_default(int32_t*)
    {
        return 0;
    }

    template<typename T>
    mtk::list<T>  __internal_get_default(mtk::list<T>*)
    {
        return mtk::list<T>();
    }


	template <typename T>
	inline void  operator >> (const YAML::Node& seq, mtk::list <T>& v) 
    {
        for(unsigned i=0; i<seq.size(); ++i)
        {
            T t = __internal_get_default((T*)0);
            seq[i] >> t;
            v.push_back(t);
        }
	}

	template <typename T>
	inline void  operator >> (const YAML::Node& n, mtk::nullable <T>& nv) 
    {
        if(n.size()!=0)
        {
            T t = __internal_get_default((T*)0);
            n >> t;
            nv = t;
        }
	}




    
template<typename T>
std::ostream& operator<< (std::ostream& o, const mtk::list<T>& list)
{
    typename mtk::list<T>::const_iterator it = list.begin();
    o << "[";
    while (it!= list.end())
    {
        o << *it << ", ";
        ++it;
    }
    o << "]";
    return o;
}



template<typename T>
bool operator== (const mtk::list<T>& l1, const mtk::list<T>& l2)
{
    if (l1.size() != l2.size())     return false;
    
    typename mtk::list<T>::const_iterator it1 = l1.begin();
    typename mtk::list<T>::const_iterator it2 = l2.begin();
    while (it1!= l1.end())
    {
        if (*it1 != *it2)       return false;
        ++it1;
        ++it2;
    }
    return true;
}



inline void  copy(mtk::FixedNumber& result, const qpid::types::Variant& v)
{
    result = ({   std::map<qpid::types::Variant::Map::key_type, qpid::types::Variant> ifn = /*it->second*/v.asMap();
                    mtk::FixedNumber(mtk::fnIntCode(ifn["n"].asInt32()), mtk::fnDec(ifn["d"].asInt8()), mtk::fnInc(ifn["i"].asInt8()));
            });
}

inline void   copy(std::string& result, const qpid::types::Variant& v)
{
    result = v.asString();
}



inline void   copy(char& result, const qpid::types::Variant& v)
{
    result = v.asInt8();
}


inline void copy(mtk::DateTime& result, const qpid::types::Variant& v)
{
    result =  WARNING_do_not_use_it__I_coul_kill_you_for_it__get_DateTime_from_time_quantity(mtk::dtTimeQuantity(mtk::dtTimeQuantitySerialNumber(v.asDouble())));
}

inline void copy(mtk::dtTimeQuantity& result, const qpid::types::Variant& v)
{
    result =  mtk::dtTimeQuantity(mtk::dtTimeQuantitySerialNumber(v.asDouble()));
}

inline void copy(int8_t& result, const qpid::types::Variant& v)
{
    result =  v.asInt8();
}

inline void copy(int16_t& result, const qpid::types::Variant& v)
{
    result =  v.asInt16();
}

inline void copy(int32_t& result, const qpid::types::Variant& v)
{
    result =  v.asInt32();
}

inline void copy(bool& result, const qpid::types::Variant& v)
{
    result =  v.asBool();
}

inline void copy(mtk::Double& result, const qpid::types::Variant& v)
{
    result =  v.asDouble();
}


template<typename T>
void   copy(mtk::nullable<T>& result, const qpid::types::Variant& v)
{
    T temp(__internal_get_default((T*)0));
    copy(temp, v);
    result = temp;
}


template<typename T>
void  copy (mtk::list<T>& result, const qpid::types::Variant& v)
{
    const qpid::types::Variant::List& l = v.asList();
    std::list<qpid::types::Variant>::const_iterator it = l.begin();
    while (it!= l.end())
    {
        T temp(__internal_get_default((T*)0));
        copy(temp, *it);
        result.push_back(temp);
        ++it;
    }
}



    inline void __internal_add2map (qpid::types::Variant::Map& map, const std::string& a, const std::string& key)
    {
        map[key] = a;
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::FixedNumber& a, const std::string& key)
    {
        map[key] = QPID_DESCOMPOSE_FIXED_NUMBER(a);
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::Double& a, const std::string& key)
    {
        map[key] = a.get()._0;
    }


    #define REGISTER_LIST_BASIC_TYPE(__TYPE__) \
        inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<__TYPE__>& l, const std::string& key)    \
        {    \
            qpid::types::Variant::List list;    \
                \
            mtk::list<__TYPE__>::const_iterator it = l.begin();    \
            while (it != l.end())    \
            {    \
                list.push_back(*it);    \
                ++it;    \
            }    \
                \
            map[key] = list;    \
        }    

    REGISTER_LIST_BASIC_TYPE(std::string)
    
    

    //-----------------------------------------------------
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<mtk::DateTime>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<mtk::DateTime>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(double(it->__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber().WarningDontDoThisGetInternal()));
            ++it;
        }
        
        map[key] = list;
    }
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<mtk::dtTimeQuantity>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<mtk::dtTimeQuantity>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(double(it->GetQuantitySerialNumber().WarningDontDoThisGetInternal()));
            ++it;
        }
        
        map[key] = list;
    }
    
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int32_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int32_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }

    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int16_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int16_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }

    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int8_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int8_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }
    
    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<int64_t>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<int64_t>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }

    inline void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<bool>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        mtk::list<bool>::const_iterator it = l.begin();
        while (it != l.end())
        {
            list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }
    
    //  for composed types
    template<typename T>
    void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::list<T>& l, const std::string& key)
    {
        qpid::types::Variant::List list;
        
        typename mtk::list<T>::const_iterator it = l.begin();
        while (it != l.end())
        {
            qpid::types::Variant::Map m;
            __internal_add2map(m, *it);
            //list.push_back(*it);
            ++it;
        }
        
        map[key] = list;
    }


    template<typename T>
    void  __internal_add2map  (qpid::types::Variant::Map& map, const mtk::nullable<T>& n, const std::string& key)
    {
        if (n.HasValue())
            __internal_add2map(map, n.Get(), key);
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::DateTime& a, const std::string& key)
    {
        map[key] = double(a.__WARNING_NOT_CALL_IT_internal_use_GetTimeQuantitySerialNumber().WarningDontDoThisGetInternal());
    }
    inline void __internal_add2map (qpid::types::Variant::Map& map, const mtk::dtTimeQuantity& a, const std::string& key)
    {
        map[key] = double(a.GetQuantitySerialNumber().WarningDontDoThisGetInternal());
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const int32_t& a, const std::string& key)
    {
        map[key] = int32_t(a);
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const int16_t& a, const std::string& key)
    {
        map[key] = int16_t(a);
    }

    inline void __internal_add2map (qpid::types::Variant::Map& map, const int8_t& a, const std::string& key)
    {
        map[key] = int8_t(a);
    }
    inline void __internal_add2map (qpid::types::Variant::Map& map, const int64_t& a, const std::string& key)
    {
        map[key] = int64_t(a);
    }
    inline void __internal_add2map (qpid::types::Variant::Map& map, const bool& a, const std::string& key)
    {
        map[key] = bool(a);
    }


    //  for composed types
    template<typename T>
    void  __internal_add2map(qpid::types::Variant::Map& map, const T& t, const std::string& key)
    {
        qpid::types::Variant::Map m;
        __internal_add2map(m, t);
        map[key] = m;
    }




//========================================================================
//------------------------------------------------------------------------
//  I M P L E M E N T A T I O N
"""
    #internal forward declaration
    content_file_cpp += '//  internal fordward declarations\n'
    

    
    for class_name, class_info, class_properties, send_code in ALL_MESSAGES:
        content_file_cpp += generate_class_in_impl(class_name, class_info, class_properties, send_code)

    for class_name, class_info, class_properties, send_code  in MESSAGES:
        content_file_cpp += generate_output_stream_operator(class_name, class_info, class_properties, send_code)
        content_file_cpp += generate_output_yaml_operator(class_name, class_info, class_properties, send_code)
        content_file_cpp += generate_input_yaml_operator(class_name, class_info, class_properties, send_code)
        

    for class_name, class_info, class_properties, send_code  in MESSAGES:
        content_file_cpp += generate_equal_operator(class_name, class_info, class_properties, send_code)

    content_file_cpp += generate_msg_to_qpid()

    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        content_file_cpp += qpid_generate__internal_get_default(class_name, class_info, class_properties, send_code)

    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        content_file_cpp += ctor_conversion_from_qpid_msg(class_name, class_info, class_properties, send_code)

    for class_name, class_info, class_properties, send_code  in ALL_MESSAGES:
        content_file_cpp += get_qpidmsg_get_in_subject(class_name, class_info, class_properties, send_code)   
        content_file_cpp += get_qpidmsg_get_out_subject(class_name, class_info, class_properties, send_code)   
    content_file_cpp +=  END_NAMESPACE








    if TESTING == False:
        FILE = open(DEST_FILE_H, 'wt')
        FILE.writelines(content_file_h)
        FILE.close()
    else:
        print content_file
    if TESTING == False:
        FILE = open(DEST_FILE_CPP, 'wt')
        FILE.writelines(content_file_cpp)
        FILE.close()
    else:
        print content_file
