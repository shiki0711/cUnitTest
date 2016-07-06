
import re


TOKEN_TYPE_TEXT = 0
TOKEN_TYPE_VARIABLE = 1
TOKEN_TYPE_BLOCK = 2
TOKEN_TYPE_BLOCK_IF = 3
TOKEN_TYPE_BLOCK_ELSE = 4
TOKEN_TYPE_BLOCK_ENDIF = 5
TOKEN_TYPE_BLOCK_LOOP = 6
TOKEN_TYPE_BLOCK_ENDLOOP = 7
TOKEN_TYPE_BLOCK_INCLUDE = 8

PARSE_STATUS_ROOT = 0
PARSE_STATUS_IF = 1
PARSE_STATUS_ELSE = 2
PARSE_STATUS_LOOP = 3


class ParseError(RuntimeError):
    def __init__(self, arg):
        self.args = arg


class Token(object):
    def __init__(self, token_string, token_type):
        self.token_string = token_string
        self.token_type = token_type


BLOCK_TAG_START = '{% '
BLOCK_TAG_END = ' %}'
VARIABLE_TAG_START = '{{ '
VARIABLE_TAG_END = ' }}'

class Lexer(object):
    def __init__(self, template_string):
        self.template_string = template_string

    def tokenize(self):
        result = []
        s = 0
        status = 'TEXT'
        for index in range(0, len(self.template_string)):
            if self.template_string[index:].startswith(VARIABLE_TAG_START):
                if status == 'TEXT':
                    status = 'VAR_START'
                    result.append(Token(self.template_string[s:index], TOKEN_TYPE_TEXT))
                    s = index
                else:
                    errmsg = 'tokenize error: index=' + str(index) + ' token: ' + self.template_string[index:index+30] + '...'
                    raise ParseError(errmsg)
            elif self.template_string[index:].startswith(VARIABLE_TAG_END):
                if status == 'VAR_START':
                    status = 'TEXT'
                    result.append(Token(self.template_string[s:index+3], TOKEN_TYPE_VARIABLE))
                    s = index+3
                else:
                    errmsg = 'tokenize error: index=' + str(index) + ' token: ' + self.template_string[index:index+30] + '...'
                    raise ParseError(errmsg)
            elif self.template_string[index:].startswith(BLOCK_TAG_START):
                if status == 'TEXT':
                    status = 'BLOCK_START'
                    result.append(Token(self.template_string[s:index], TOKEN_TYPE_TEXT))
                    s = index
                else:
                    errmsg = 'tokenize error: index=' + str(index) + ' token: ' + self.template_string[index:index+30] + '...'
                    raise ParseError(errmsg)
            elif self.template_string[index:].startswith(BLOCK_TAG_END):
                if status == 'BLOCK_START':
                    status = 'TEXT'
                    result.append(Token(self.template_string[s:index+3], TOKEN_TYPE_BLOCK))
                    s = index+3
                else:
                    errmsg = 'tokenize error: index=' + str(index) + ' token: ' + self.template_string[index:index+30] + '...'
                    raise ParseError(errmsg)
            else:
                pass
        result.append(Token(self.template_string[s:index], TOKEN_TYPE_TEXT))
        #for item in result:
        #    print 'token: '+item.token_string+' type: '+str(item.token_type)
        return result


class NodeList(object):
    def __init__(self):
        self.container = []
    
    def append(self, node):
        self.container.append(node)

class Node(object):
    def __init__(self):
        self.parent = None

    def render(self, context):
        pass
    
    def resolve(self, variable):
        node = self
        while node:
            if node.context.has_key(variable):
                return node.context[variable]
            else:
                node = node.parent
        errmsg = 'resolve not found: '+variable
        raise ParseError(errmsg)
        return None

class RootNode(Node):
    def __init__(self):
        Node.__init__(self)
        self.child_nodelist = NodeList()
        self.context = {}
        
    def addNode(self, node):
        self.child_nodelist.append(node)
        node.parent = self

    def render(self, context):
        self.context = context
        result = ''
        for node in self.child_nodelist.container:
            r = node.render(context)
            result += node.render({})
        return result
        


class TextNode(Node):
    def __init__(self, s):
        Node.__init__(self)
        self.s = s

    def render(self, context):
        self.context = context
        return self.s


class VariableNode(Node):
    def __init__(self, var_string):
        Node.__init__(self)
        self.var_string = var_string

    def render(self, context):
        self.context = context
        resolved_var = self.resolve(self.var_string)
        if resolved_var:
            return resolved_var
        else:
            return ''


class ConditionNode(Node):
    def __init__(self, condition_var_string):
        Node.__init__(self)
        self.condition_var_string = condition_var_string
        self.true_nodelist = NodeList()
        self.false_nodelist = NodeList()

    def render(self, context):
        self.context = context
        resolved_var = self.resolve(self.condition_var_string)
        if resolved_var:
            self.context[self.condition_var_string] = resolved_var
            if int(resolved_var) > 0:
                condition = True
            else:
                condition = False
        else:
            condition = False
        if condition:
            nodelist = self.true_nodelist.container
        else:
            nodelist = self.false_nodelist.container
        result = ''
        for node in nodelist:
            result += node.render({})
        return result

    def addTrueNode(self, node):
        self.true_nodelist.append(node)
        node.parent = self

    def addFalseNode(self, node):
        self.false_nodelist.append(node)
        node.parent = self


class LoopNode(Node):
    def __init__(self, loop_vars_list):
        Node.__init__(self)
        self.loop_vars_list = loop_vars_list
        self.loop_nodelist = NodeList()

    def render(self, context):
        self.context = context
        result = ''
        separator = ''
        resolved_list = self.resolve(self.loop_vars_list[1])
        if resolved_list:
            for item in resolved_list:
                result += separator
                if self.loop_vars_list[0] == '_':
                    for (k,v) in item.items():
                        self.context[k] = v
                else:
                    self.context[self.loop_vars_list[0]] = item
                for node in self.loop_nodelist.container:
                    result += node.render({})
                separator = self.loop_vars_list[2]
        return result

    def addLoopNode(self, node):
        self.loop_nodelist.container.append(node)
        node.parent = self


class Parser(object):
    def __init__(self, tokens):
        self.tokens = tokens
        self.parse_stack = []
        self.root = RootNode()
        self.parse_stack_init(self.root)

    def parse(self):
        while self.tokens:
            token = self.next_token()
            if token.token_type == TOKEN_TYPE_TEXT:
                self.append(token.token_string, TOKEN_TYPE_TEXT)
            elif token.token_type == TOKEN_TYPE_VARIABLE:
                if token.token_string:
                    regex_req = ur"\{\{\s([a-zA-Z_][a-zA-Z_0-9]*)\s\}\}"
                    m = re.match(regex_req, token.token_string)
                    if m:
                        var_string = m.group(1)
                        self.append(var_string, TOKEN_TYPE_VARIABLE)
                    else:
                        errmsg = 'parse error: ' + token.token_string
                        raise ParseError(errmsg)
            elif token.token_type == TOKEN_TYPE_BLOCK:
                if token.token_string:
                    regex_req_if = ur"\{%\sif\s([a-zA-Z_][a-zA-Z_0-9]*)\s%\}"
                    regex_req_else = ur"\{%\selse\s%\}"
                    regex_req_endif = ur"\{%\sendif\s%\}"
                    regex_req_loop = ur"\{%\sfor\s([a-zA-Z_][a-zA-Z_0-9]*)\sin\s([a-zA-Z_][a-zA-Z_0-9]*)\s%\}"
                    regex_req_loop_with = ur"\{%\sfor\s([a-zA-Z_][a-zA-Z_0-9]*)\sin\s([a-zA-Z_][a-zA-Z_0-9]*)\swith\s([^\s]+)\s%\}"
                    regex_req_endloop = ur"\{%\sendfor\s%\}"
                    regex_req_include = ur"\{%\sinclude\s([^\s]+)\s%\}"
                m = re.match(regex_req_if, token.token_string)
                if m:
                    if_var_string = m.group(1)
                    self.append(if_var_string, TOKEN_TYPE_BLOCK_IF)
                    continue
                m = re.match(regex_req_else, token.token_string)
                if m:
                    self.append('', TOKEN_TYPE_BLOCK_ELSE)
                    continue
                m = re.match(regex_req_endif, token.token_string)
                if m:
                    self.append('', TOKEN_TYPE_BLOCK_ENDIF)
                    continue
                m = re.match(regex_req_loop, token.token_string)
                if m:
                    loop_item_string = m.group(1)
                    loop_list_string = m.group(2)
                    self.append([loop_item_string, loop_list_string, ''], TOKEN_TYPE_BLOCK_LOOP)
                    continue
                m = re.match(regex_req_loop_with, token.token_string)
                if m:
                    loop_item_string = m.group(1)
                    loop_list_string = m.group(2)
                    loop_with_string = m.group(3)
                    self.append([loop_item_string, loop_list_string, loop_with_string], TOKEN_TYPE_BLOCK_LOOP)
                    continue
                m = re.match(regex_req_endloop, token.token_string)
                if m:
                    self.append('', TOKEN_TYPE_BLOCK_ENDLOOP)
                    continue
                m = re.match(regex_req_include, token.token_string)
                if m:
                    sub_template_file = m.group(1)
                    self.append(sub_template_file, TOKEN_TYPE_BLOCK_INCLUDE)
                    continue
                errmsg = 'parse error: ' + token.token_string
                raise ParseError(errmsg)
            else:
                errmsg = 'parse error: ' + token.token_string
                raise ParseError(errmsg)
        return self.root
    
    def append(self, parsed_content, type):
        current = self.parse_stack[-1]
        current_node = current['node']
        current_status = current['status']
        if type == TOKEN_TYPE_TEXT or type == TOKEN_TYPE_VARIABLE:
            if type == TOKEN_TYPE_TEXT:
                node = TextNode(parsed_content)
            else:
                node = VariableNode(parsed_content)
            self.insert_node(current_node, current_status, node)
        elif type == TOKEN_TYPE_BLOCK_IF:
            node = ConditionNode(parsed_content)
            self.insert_node(current_node, current_status, node)
            self.parse_stack.append({'node':node, 'status':PARSE_STATUS_IF})
        elif type == TOKEN_TYPE_BLOCK_ELSE:
            if current_status != PARSE_STATUS_IF:
                raise ParseError(parsed_content)
            else:
                current['status'] = PARSE_STATUS_ELSE
        elif type == TOKEN_TYPE_BLOCK_ENDIF:
            if current_status != PARSE_STATUS_IF and current_status != PARSE_STATUS_ELSE:
                self.print_parse_stack()
                raise ParseError(parsed_content)
            else:
                self.parse_stack.pop()
        elif type == TOKEN_TYPE_BLOCK_LOOP:
            node = LoopNode(parsed_content)
            self.insert_node(current_node, current_status, node)
            self.parse_stack.append({'node':node, 'status':PARSE_STATUS_LOOP})
        elif type == TOKEN_TYPE_BLOCK_ENDLOOP:
            if current_status != PARSE_STATUS_LOOP:
                raise ParseError(parsed_content)
            else:
                self.parse_stack.pop()
        elif type == TOKEN_TYPE_BLOCK_INCLUDE:
            t = Templete(TEMPLATE_FROM_FILE, parsed_content)
            node = t.compile()
            self.insert_node(current_node, current_status, node)
        else:
            raise ParseError(parsed_content)
            
    
    def parse_stack_init(self, root):
        self.parse_stack = []
        self.parse_stack.append({'node':root, 'status':PARSE_STATUS_ROOT})
        
    def insert_node(self, parent_node, parent_status, node):
        if parent_status == PARSE_STATUS_IF:
            parent_node.addTrueNode(node)
        elif parent_status == PARSE_STATUS_ELSE:
            parent_node.addFalseNode(node)
        elif parent_status == PARSE_STATUS_LOOP:
            parent_node.addLoopNode(node)
        else:
            parent_node.addNode(node)

    def next_token(self):
        return self.tokens.pop(0)
    
    def print_parse_stack(self):
        for item in self.parse_stack:
            print 'status: '+str(item['status'])

TEMPLATE_FROM_FILE = 0
TEMPLATE_FROM_STRING = 1
class Templete(object):
    def __init__(self, source, content):
        self.parse_node = None
        self.generated_string = None
        if source == TEMPLATE_FROM_FILE:
            try:
                fp = open(content, 'r')
            except Exception:
                errmsg = 'Open template file '+str(content) + ' error!'
                raise ParseError(errmsg)
            self.template_string = fp.read()
            fp.close()
        else:
            self.template_string = content
    
    def compile(self):
        lex = Lexer(self.template_string)
        tokens = lex.tokenize()
        
        parser = Parser(tokens)
        self.parse_node = parser.parse()
        return self.parse_node 
    
    def render(self, context):
        self.generated_string = self.parse_node.render(context)
        return self.generated_string
    
    def to_file(self, filepath):
        try:
            fp = open(filepath, 'w')
        except Exception:
            errmsg = 'Open output file '+str(filepath) + ' error!'
            raise ParseError(errmsg)
        fp.write(self.generated_string)
        fp.close()


def main():
    t = Templete(TEMPLATE_FROM_FILE, 'cmock_mock.template')
    t.compile()
    function_settings = []
    for i in range(0, 20):
        argrange = range(1, i+1)
        argrange_str = map(lambda x: str(x), argrange)
        function_settings.append({'noret':1, 'args':str(i), 'argrange':argrange_str})
        function_settings.append({'noret':0, 'args':str(i), 'argrange':argrange_str})
    t.render({'function_settings':function_settings})
    t.to_file('../cmock_mock.h')

if __name__ == '__main__':
    main()
    print 'done.'
    
    
