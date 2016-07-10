from clang.cindex import Cursor
from clang.cindex import CursorKind
from clang.cindex import TypeKind
from clang.cindex import TranslationUnit

import sys

def mock_type_str(funcname,argno,cursor_type):
    result = ['','']
    if cursor_type.kind == TypeKind.INCOMPLETEARRAY or cursor_type.kind == TypeKind.CONSTANTARRAY or cursor_type.kind == TypeKind.VARIABLEARRAY or cursor_type.kind == TypeKind.DEPENDENTSIZEDARRAY:
        result = ['', '*']
        nresult = mock_type_str(funcname,argno,cursor_type.element_type)
        result = [nresult[0]+result[0], nresult[1]+result[1]]
    elif cursor_type.kind == TypeKind.POINTER:
        if cursor_type.get_pointee().kind == TypeKind.UNEXPOSED:
            decl = cursor_type.spelling
            #TODO: exactly match a funcptr declaration
            p = decl.find(')')
            if p == -1:
                result = ['', cursor_type.spelling]
            else:
                typename = 'T_'+funcname+'_arg'+str(argno)
                result[0] += 'typedef '
                result[0] += decl[0:p]
                result[0] += typename
                result[0] += decl[p:]
                result[0] += ';\n'
                result[1] += typename
        else:
            result = ['', cursor_type.spelling]
    else:
        result = ['', cursor_type.spelling]
    return result

def mock_cursor_str(funcname,argno,cursor):
    result = mock_type_str(funcname, argno,cursor.type)
    #print result
    return result

if __name__ == '__main__':
    filepath = sys.argv[1]
    tu = TranslationUnit.from_source(filepath, ['-Wall'])
    for fc in tu.cursor.get_children():
        if fc.kind.is_declaration():
            if fc.kind == CursorKind.FUNCTION_DECL:
                func_name = fc.spelling
                ret_type = mock_type_str(func_name,0,fc.result_type)
                arg_types = []
                idx = 1
                for dc in fc.get_arguments():
                    arg_types.append(mock_cursor_str(func_name,idx,dc))
                    idx += 1
                typedef_str = ''
                mocker_str = ''

                typedef_str += ret_type[0]
                args = len(arg_types)
                if ret_type[1] == 'void':
                    mocker_str += 'CMOCK_NORET_FUNC'
                else:
                    mocker_str += 'CMOCK_FUNC'
                mocker_str += str(args)
                mocker_str += '('
                mocker_str += func_name
                mocker_str += ','
                mocker_str += ret_type[1]
                for arg_type in arg_types:
                    typedef_str += arg_type[0]
                    mocker_str += ','
                    mocker_str += arg_type[1]
                mocker_str += ');'
                print typedef_str
                print mocker_str

    


