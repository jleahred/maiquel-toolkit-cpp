#!/usr/bin/env python

from string import Template
import datetime
import sys
import os
import time
import re



TOOLS_PATH = './tools/'



NAME_TAG = {}
TAG_NAME = {}
MSG_FIELDS = {}
MSG_FIELDS__NAMES_WITHOUT_NAMESPACES = {}




def fill_tag_field_name():
    for class_name, class_info, __class_properties, send_code  in MESSAGES:
        for ci in class_info :
            tag = ''
            field_name = ''
            if ci.has_key('FIELD_TAG'):
                tag = ci['FIELD_TAG']
                field_name = ci['FIELD_NAME']
            elif ci.has_key('IN_SUB_MSG'):
                tag = ''
                field_name = 'IC_' + class_name
            else:
                tag = '???'
                
            if TAG_NAME.has_key(tag) == False:
                TAG_NAME[tag] = {field_name: 0}
            if TAG_NAME[tag].has_key(field_name) == False:
                TAG_NAME[tag][field_name] = 0
            TAG_NAME[tag][field_name] = TAG_NAME[tag][field_name]+1
##            if TAG_NAME.has_key(tag) == False:
##                TAG_NAME[tag] = []
##            TAG_NAME[tag].append(field_name)

            if NAME_TAG.has_key(field_name) == False:
                NAME_TAG[field_name] = {tag: 0}
            if NAME_TAG[field_name].has_key(tag) == False:
                NAME_TAG[field_name][tag] = 0
            NAME_TAG[field_name][tag] = NAME_TAG[field_name][tag]+1




def fill_msg_fields():
    for class_name, class_info, __class_properties, send_code  in MESSAGES:
        msg_full_name = msg_full_name = '::'.join(NAMESPACES) + '::' + class_name
        
        if __class_properties.has_key('I'):
            field_name = '_inheritance_'
            field_type__or__sub_msg_type = __class_properties['I']
            __class_properties = 'pending'
            if MSG_FIELDS.has_key(msg_full_name) == False:
                MSG_FIELDS[msg_full_name] = []
            MSG_FIELDS[msg_full_name].append({'fn':field_name, 'ft':field_type__or__sub_msg_type, 'cp':__class_properties })
            if MSG_FIELDS__NAMES_WITHOUT_NAMESPACES.has_key(class_name) == False:
                MSG_FIELDS__NAMES_WITHOUT_NAMESPACES[class_name] = []
            MSG_FIELDS__NAMES_WITHOUT_NAMESPACES[class_name].append({'fn':field_name, 'ft':field_type__or__sub_msg_type, 'cp':__class_properties})
            
        for ci in class_info :
            field_type__or__sub_msg_type = ''
            field_name = ''
            if ci.has_key('field_type'):
                field_type__or__sub_msg_type = ci['field_type']
                field_name = ci['FIELD_NAME']
            elif ci.has_key('sub_msg_type'):
                field_type__or__sub_msg_type = ci['sub_msg_type']
                field_name = ci['FIELD_NAME']
            else:
                field_type__or__sub_msg_type = '????'
            
            if MSG_FIELDS.has_key(msg_full_name) == False:
                MSG_FIELDS[msg_full_name] = []
            MSG_FIELDS[msg_full_name].append({'fn':field_name, 'ft':field_type__or__sub_msg_type, 'cp':__class_properties })
            if MSG_FIELDS__NAMES_WITHOUT_NAMESPACES.has_key(class_name) == False:
                MSG_FIELDS__NAMES_WITHOUT_NAMESPACES[class_name] = []
            MSG_FIELDS__NAMES_WITHOUT_NAMESPACES[class_name].append({'fn':field_name, 'ft':field_type__or__sub_msg_type, 'cp':__class_properties})
            
    



def print_map(map) :
    print """[cols="1, 2" , options=""]
|==========================================================
    """
    for k in sorted(map.iterkeys()):
        v = map[k]
        if k != '' :
            if len(v) > 1:
                print '|  [red]#'  +  k  + '#  |  ' + str(v)
            else:
                print '|  '  +  k  + '  |  ' + str(v)
    print """|========================================================
    """
##    for k, v in map.items():
##        if k != '' :
##            if len(v) > 1:
##                print '|  [red]#'  +  k  + '#  |  ' + str(v)
##            else:
##                print '|  '  +  k  + '  |  ' + str(v)
##    print """|========================================================
##    """



last_type_printed = ''
def print_msg_fields_enumeration(msg_name, msg_fields, stars_depht) :
    if stars_depht == '':
        global last_type_printed
        last_type_printed = ''
        print msg_name + '::'
        print '+'
        print """[]
|========================================="""
        
    for field_info in msg_fields :
        field_name = field_info['fn']
        field_type = field_info['ft']
        
        if field_name != '':
            if MSG_FIELDS.has_key(field_type) :
                ##print stars_depht +  '* __' + field_name + '  <-  ' + field_type + '__'
                print_msg_fields_enumeration(field_type, MSG_FIELDS[field_type], stars_depht + ' ' + msg_name)
            elif MSG_FIELDS__NAMES_WITHOUT_NAMESPACES.has_key(field_type) :
                ##print stars_depht + '* __' + field_name + '  <-  ' + field_type + '__'
                print_msg_fields_enumeration(field_type, MSG_FIELDS__NAMES_WITHOUT_NAMESPACES[field_type], stars_depht + ' ' + msg_name)
            else:
                new_last_type_printed = stars_depht + ' ' + msg_name
                if last_type_printed != new_last_type_printed :
                    print '|' + field_name  + ' | ' +  field_type + ' |' + new_last_type_printed
                    last_type_printed = new_last_type_printed
                else :
                    print '|' + field_name  + ' | ' +  field_type + ' |  '

    if stars_depht == '':
        print """|========================================="""




def print_msg_fields(msg_name, msg_fields, stars_depht) :
    if stars_depht == '':
        print msg_name + '::'
        
    for field_info in msg_fields :
        field_name = field_info['fn']
        field_type = field_info['ft']
        
        if field_name != '':
            new_start_depth = ''
            if field_name == '_inheritance_':
                new_start_depth = stars_depht
            else:
                new_start_depth = stars_depht + '*'
            if new_start_depth == '':
                new_start_depth = '*'
            if MSG_FIELDS.has_key(field_type) :
                print stars_depht + '* ' + field_name + '  <-  _' + field_type + '_'
                print_msg_fields(field_type, MSG_FIELDS[field_type], new_start_depth)
            elif MSG_FIELDS__NAMES_WITHOUT_NAMESPACES.has_key(field_type) :
                print stars_depht + '* ' + field_name + '  <-  _' + field_type + '_'
                print_msg_fields(field_type, MSG_FIELDS__NAMES_WITHOUT_NAMESPACES[field_type], new_start_depth)
            else:
                print stars_depht + '* ' + field_name





#   main


## TESTING  -------------------------------------------------
## TESTING  -------------------------------------------------

##INCLUDES = ['#include "support/mtk_string.h"', '#include "msg_common_support.h"' ]
##NAMESPACES = ['mtk', 'msg']
##
##
##MESSAGES=[ 
##  ('sub_location', [ {'FIELD_NAME':'client_code', 'FIELD_TAG':'cc', 'field_type':'std::string', 'OPTIONS':[] }, {'FIELD_NAME':'machine', 'FIELD_TAG':'mc', 'field_type':'std::string', 'OPTIONS':[] }, ], {'V':'0'} , '' ) ,
##  ('sub_process_info', [ {'FIELD_NAME':'location', 'FIELD_TAG':'l', 'sub_msg_type':'sub_location', 'OPTIONS':[] }, {'FIELD_NAME':'process_name', 'FIELD_TAG':'pn', 'field_type':'std::string', 'OPTIONS':[] }, {'FIELD_NAME':'process_uuid', 'FIELD_TAG':'pi', 'field_type':'std::string', 'OPTIONS':[] }, {'FIELD_NAME':'version', 'FIELD_TAG':'pv', 'field_type':'std::string', 'OPTIONS':[] }, ], {'V':'0'} , '' ) ,
##  ('sub_control_fluct', [ {'FIELD_NAME':'key', 'FIELD_TAG':'k', 'field_type':'std::string', 'OPTIONS':[] }, {'FIELD_NAME':'datetime', 'FIELD_TAG':'dt', 'field_type':'mtk::DateTime', 'OPTIONS':[] }, ], {'V':'0'} , '  const_cast<sub_control_fluct*>(this)->datetime = mtk::dtNowLocal();    ' ) ,
##  ('sub_request_id', [ {'FIELD_NAME':'sess_id', 'FIELD_TAG':'sid', 'field_type':'std::string', 'OPTIONS':[] }, {'FIELD_NAME':'req_code', 'FIELD_TAG':'rqc', 'field_type':'std::string', 'OPTIONS':[] }, ], {'V':'0'} , '' ) ,
##  ('sub_request_info', [ {'FIELD_NAME':'req_id', 'FIELD_TAG':'rid', 'sub_msg_type':'sub_request_id', 'OPTIONS':[] }, {'FIELD_NAME':'process_info', 'FIELD_TAG':'pi', 'sub_msg_type':'sub_process_info', 'OPTIONS':[] }, ], {'V':'0'} , '' ) ,
##  ('sub_r_response', [ {'FIELD_NAME':'request_info', 'FIELD_TAG':'ri', 'sub_msg_type':'sub_request_info', 'OPTIONS':[] }, {'FIELD_NAME':'sec_number', 'FIELD_TAG':'sq', 'field_type':'int16_t', 'OPTIONS':[] }, {'FIELD_NAME':'is_last_response', 'FIELD_TAG':'lr', 'sub_msg_type':'bool', 'OPTIONS':[] }, ], {'V':'0'} , '' ) ,
##  ('sub_product_code', [ {'FIELD_NAME':'market', 'FIELD_TAG':'mk', 'field_type':'std::string', 'OPTIONS':[] }, {'FIELD_NAME':'product', 'FIELD_TAG':'pr', 'field_type':'std::string', 'OPTIONS':[] }, ], {'V':'0'} , '' ) , ]
##
##
##fill_tag_field_name();
##fill_msg_fields();
##
##
##print '=== TAG -> NAME'
##print_map(TAG_NAME)
##print
##
##print '=== NAME -> TAG'
##print_map(NAME_TAG)
##print
##
##print '=== MESSAGES WITH ALL FIELDS'
##for msg_name, msg_fields in MSG_FIELDS.items():
##    print_msg_fields(msg_name, msg_fields, '')


## TESTING  -------------------------------------------------
## TESTING  -------------------------------------------------



for file in sys.argv[1:] :
    ORIG_FILE = file
    FOLDER_DESTINATION = os.path.split(ORIG_FILE)[0]
    FILE_NAME = os.path.splitext(os.path.split(file)[-1])[0]
    DEST_FILE_ADOC = os.path.join(FOLDER_DESTINATION, FILE_NAME +'.adoc')


    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    # execute_dhp()
    def execute_dhp():
        pipe = os.popen( os.path.join(TOOLS_PATH, 'dhp') + ' ' 
                        + os.path.join(TOOLS_PATH, 'build_msg.gram ') +  ORIG_FILE)
        return pipe.readlines()
        

    # execute_dhp()
    #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



    exec('\n'.join(execute_dhp()))


    fill_tag_field_name();
    fill_msg_fields();


print '=== TAG -> NAME'
print_map(TAG_NAME)
print

print '=== NAME -> TAG'
print_map(NAME_TAG)
print

##print '=== MESSAGES WITH ALL FIELDS (brief)'
##for msg_name, msg_fields in MSG_FIELDS.items():
##    print_msg_fields(msg_name, msg_fields, '')
##
##
##print '=== MESSAGES WITH ALL FIELDS  enumeration'
##for msg_name, msg_fields in MSG_FIELDS.items():
##    print_msg_fields_enumeration(msg_name, msg_fields, '')