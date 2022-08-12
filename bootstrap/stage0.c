#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "errno.h"
#include "ctype.h"
#include "math.h"

/***************** embed './lib/prelude.h' *****************/
#include "stdarg.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"

char* __format_string(const char* format, ...) {
  va_list args;
  va_start(args, format);

  int size = vsnprintf(NULL, 0, format, args);

  va_end(args);
  va_start(args, format);

  char* s = calloc(1, size + 1);

  vsprintf(s, format, args);
  va_end(args);
  return s;
}

/* struct declarations */
typedef struct Vector Vector;
typedef struct Location Location;
typedef struct Span Span;
typedef enum TokenType TokenType;
typedef struct Token Token;
typedef struct Lexer Lexer;
typedef struct MapNode MapNode;
typedef struct Map Map;
typedef enum BaseType BaseType;
typedef struct Type Type;
typedef enum ASTType ASTType;
typedef struct Variable Variable;
typedef struct Function Function;
typedef struct Structure Structure;
typedef struct Program Program;
typedef struct Block Block;
typedef struct Binary Binary;
typedef struct Identifier Identifier;
typedef struct FormatString FormatString;
typedef struct FuncCall FuncCall;
typedef struct Member Member;
typedef struct EnumValue EnumValue;
typedef struct VarDeclaration VarDeclaration;
typedef struct IfStatement IfStatement;
typedef struct Loop Loop;
typedef struct Cast Cast;
typedef struct MatchCase MatchCase;
typedef struct Match Match;
typedef union ASTUnion ASTUnion;
typedef struct AST AST;
typedef struct Parser Parser;
typedef struct TypeChecker TypeChecker;
typedef struct CodeGenerator CodeGenerator;

struct Vector {
  int size;
  int capacity;
  void** data;
};

struct Location {
  char* filename;
  int line;
  int col;
};

struct Span {
  Location start;
  Location end;
};

enum TokenType {
  TokenType__And,
  TokenType__As,
  TokenType__Bool,
  TokenType__Break,
  TokenType__Char,
  TokenType__Continue,
  TokenType__Def,
  TokenType__Defer,
  TokenType__Else,
  TokenType__Enum,
  TokenType__Extern,
  TokenType__False,
  TokenType__F32,
  TokenType__For,
  TokenType__Fn,
  TokenType__I32,
  TokenType__If,
  TokenType__Let,
  TokenType__Match,
  TokenType__Not,
  TokenType__Or,
  TokenType__Return,
  TokenType__SizeOf,
  TokenType__String,
  TokenType__Struct,
  TokenType__True,
  TokenType__U8,
  TokenType__UntypedPtr,
  TokenType__Union,
  TokenType__Use,
  TokenType__Void,
  TokenType__While,
  TokenType__AtSign,
  TokenType__Ampersand,
  TokenType__Backtick,
  TokenType__Caret,
  TokenType__CloseCurly,
  TokenType__CloseParen,
  TokenType__CloseSquare,
  TokenType__Colon,
  TokenType__ColonColon,
  TokenType__Comma,
  TokenType__Dot,
  TokenType__EOF,
  TokenType__Equals,
  TokenType__EqualEquals,
  TokenType__Exclamation,
  TokenType__FatArrow,
  TokenType__FloatLiteral,
  TokenType__FormatStringLiteral,
  TokenType__GreaterThan,
  TokenType__GreaterThanEquals,
  TokenType__Identifier,
  TokenType__IntLiteral,
  TokenType__LessThan,
  TokenType__LessThanEquals,
  TokenType__Line,
  TokenType__Minus,
  TokenType__MinusEquals,
  TokenType__NotEquals,
  TokenType__OpenCurly,
  TokenType__OpenParen,
  TokenType__OpenSquare,
  TokenType__Percent,
  TokenType__Plus,
  TokenType__PlusEquals,
  TokenType__Semicolon,
  TokenType__Slash,
  TokenType__SlashEquals,
  TokenType__Star,
  TokenType__StarEquals,
  TokenType__StringLiteral,
  TokenType__CharLiteral,
};

struct Token {
  TokenType type;
  Span span;
  char* text;
  bool seen_newline;
};

struct Lexer {
  char* source;
  int source_len;
  int i;
  Location loc;
  bool seen_newline;
  Vector* tokens;
};

struct MapNode {
  char* key;
  void* value;
  MapNode* next;
};

struct Map {
  MapNode** buckets;
  int num_items;
  int num_buckets;
  int num_collisions;
};

enum BaseType {
  BaseType__Char,
  BaseType__I32,
  BaseType__F32,
  BaseType__Bool,
  BaseType__U8,
  BaseType__Void,
  BaseType__Pointer,
  BaseType__Structure,
  BaseType__Function,
  BaseType__Method,
};

struct Type {
  BaseType base;
  Type* ptr;
  char* name;
  Span span;
  Structure* struct_def;
  Function* func_def;
  Type* return_type;
  Vector* params;
};

enum ASTType {
  ASTType__Assignment,
  ASTType__Address,
  ASTType__And,
  ASTType__Block,
  ASTType__BoolLiteral,
  ASTType__BitwiseAnd,
  ASTType__BitwiseOr,
  ASTType__BitwiseXor,
  ASTType__Break,
  ASTType__Call,
  ASTType__Cast,
  ASTType__CharLiteral,
  ASTType__Continue,
  ASTType__Defer,
  ASTType__Dereference,
  ASTType__Divide,
  ASTType__DivideEquals,
  ASTType__EnumValue,
  ASTType__Equals,
  ASTType__FloatLiteral,
  ASTType__FormatStringLiteral,
  ASTType__For,
  ASTType__GreaterThan,
  ASTType__GreaterThanEquals,
  ASTType__If,
  ASTType__Identifier,
  ASTType__Index,
  ASTType__IntLiteral,
  ASTType__LessThan,
  ASTType__LessThanEquals,
  ASTType__Match,
  ASTType__Member,
  ASTType__Minus,
  ASTType__MinusEquals,
  ASTType__Modulus,
  ASTType__Multiply,
  ASTType__MultiplyEquals,
  ASTType__Not,
  ASTType__NotEquals,
  ASTType__Or,
  ASTType__Plus,
  ASTType__PlusEquals,
  ASTType__Return,
  ASTType__SizeOf,
  ASTType__ScopeLookup,
  ASTType__StringLiteral,
  ASTType__UnaryMinus,
  ASTType__VarDeclaration,
  ASTType__While,
};

struct Variable {
  char* name;
  Type* type;
  Span span;
  bool is_extern;
  char* extern_name;
};

struct Function {
  char* name;
  Vector* params;
  Type* return_type;
  AST* body;
  Type* type;
  Span span;
  bool is_extern;
  char* extern_name;
  bool is_static;
  bool is_method;
  char* method_struct_name;
};

struct Structure {
  Type* type;
  char* name;
  Vector* fields;
  Span span;
  bool is_extern;
  char* extern_name;
  bool is_enum;
  bool is_union;
};

struct Program {
  Vector* functions;
  Vector* structures;
  Vector* global_vars;
  Span span;
  Map* included_files;
  Vector* c_flags;
  Vector* c_includes;
  Vector* c_embed_headers;
};

struct Block {
  Vector* statements;
};

struct Binary {
  AST* lhs;
  AST* rhs;
};

struct Identifier {
  char* name;
  Variable* var;
  bool is_function;
  Function* func;
};

struct FormatString {
  char* str;
  Vector* parts;
  Vector* exprs;
};

struct FuncCall {
  AST* callee;
  Vector* args;
  Function* func;
  bool added_method_arg;
};

struct Member {
  AST* lhs;
  char* name;
  bool is_method;
  bool is_pointer;
};

struct EnumValue {
  Structure* struct_def;
  char* name;
};

struct VarDeclaration {
  Variable* var;
  AST* init;
};

struct IfStatement {
  AST* cond;
  AST* then;
  AST* els;
};

struct Loop {
  AST* init;
  AST* cond;
  AST* incr;
  AST* body;
};

struct Cast {
  AST* lhs;
  Type* to;
};

struct MatchCase {
  AST* cond;
  AST* body;
};

struct Match {
  AST* expr;
  Vector* cases;
  AST* defolt;
  Span defolt_span;
};

union ASTUnion {
  Block block;
  Binary binary;
  Identifier ident;
  FormatString fmt_str;
  FuncCall call;
  Member member;
  EnumValue enum_val;
  VarDeclaration var_decl;
  IfStatement if_stmt;
  Loop loop;
  Cast cast;
  AST* unary;
  Match match_stmt;
  char* num_literal;
  bool bool_literal;
  char* string_literal;
  char* char_literal;
  Type* size_of_type;
};

struct AST {
  ASTType type;
  Span span;
  ASTUnion u;
  Type* etype;
  bool returns;
};

struct Parser {
  Vector* tokens;
  int curr;
};

struct TypeChecker {
  Vector* scopes;
  Map* functions;
  Map* structures;
  Map* methods;
  Function* cur_func;
  bool in_loop;
};

struct CodeGenerator {
  FILE* out;
  Vector* scopes;
};

/* function declarations */
FILE* File__open(char* path, char* mode);
char* File__slurp(FILE* this);
void File__puts(FILE* this, char* str);
bool streq(char* str1, char* str2);
char* substring(char* str, int start, int len);
Vector* Vector__new();
void Vector__resize(Vector* this, int new_capacity);
void Vector__push(Vector* this, void* val);
void Vector__push_front(Vector* this, void* val);
void* Vector__pop(Vector* this);
void* Vector__back(Vector* this);
void* Vector__at(Vector* this, int i);
bool Vector__empty(Vector* this);
void Vector__free(Vector* this);
Location Location__make(char* filename, int line, int col);
char* Location__str(Location this);
Span Span__make(Location start, Location end);
char* Span__str(Span this);
Span Span__join(Span this, Span other);
Token* Token__new(TokenType type, Span span, char* text);
Token* Token__from_type(TokenType type, Span span);
Token* Token__from_ident(char* text, Span span);
char* Token__str(Token* this);
TokenType TokenType__from_text(char* text);
char* TokenType__str(TokenType this);
Lexer Lexer__make(char* source, char* filename);
void Lexer__push(Lexer* this, Token* token);
void Lexer__push_type(Lexer* this, TokenType type, int len);
char Lexer__peek(Lexer* this, int offset);
Vector* Lexer__lex(Lexer* this);
MapNode* MapNode__new(char* key, void* value, MapNode* next);
void MapNode__free_list(MapNode* node);
Map* Map__new();
int Map__hash(Map* this, char* s);
MapNode* Map__get_node(Map* this, char* key);
void* Map__get(Map* this, char* key);
bool Map__exists(Map* this, char* key);
void Map__insert(Map* this, char* key, void* value);
void Map__resize(Map* this);
void Map__print_keys(Map* this);
void Map__free(Map* this);
Type* Type__new(BaseType base, Span span);
Type* Type__new_link(BaseType base, Type* next, Span span);
Type* Type__ptr_to(BaseType base, Span span);
bool Type__is_struct_or_ptr(Type* this);
bool Type__is_numeric(Type* this);
bool Type__eq(Type* this, Type* other);
char* Type__str(Type* this);
Type* Type__reverse(Type* this);
bool Type__is_string(Type* this);
char* ASTType__str(ASTType this);
ASTType ASTType__from_token(TokenType type);
Variable* Variable__new(char* name, Type* type, Span span);
Function* Function__new(Span span);
Structure* Structure__new(Span span);
Variable* Structure__find_field(Structure* this, char* name);
Program* Program__new();
bool Program__is_file_included(Program* this, char* filename);
void Program__add_included_file(Program* this, char* filename);
MatchCase* MatchCase__new(AST* cond, AST* body);
AST* AST__new(ASTType type, Span span);
AST* AST__new_unop(ASTType type, Span span, AST* expr);
AST* AST__new_binop(ASTType type, AST* lhs, AST* rhs);
bool AST__callee_is(AST* this, char* expected);
int min(int a, int b);
float minf(float a, float b);
int max(int a, int b);
float maxf(float a, float b);
float clampf(float x, float min, float max);
float clamp01(float x);
void error_loc(Location loc, char* msg);
void error_span(Span span, char* msg);
Parser* Parser__make(Vector* tokens);
void Parser__error(Parser* this, char* msg);
void Parser__unhandled_type(Parser* this, char* func);
Token* Parser__token(Parser* this);
bool Parser__token_is(Parser* this, TokenType type);
bool Parser__consume_if(Parser* this, TokenType type);
void Parser__consume_newline_or(Parser* this, TokenType type);
Token* Parser__consume(Parser* this, TokenType type);
Type* Parser__parse_type(Parser* this);
AST* Parser__parse_format_string(Parser* this);
AST* Parser__parse_factor(Parser* this, bool in_parens);
AST* Parser__parse_term(Parser* this, bool in_parens);
AST* Parser__parse_additive(Parser* this, bool in_parens);
AST* Parser__parse_bw_and(Parser* this, bool in_parens);
AST* Parser__parse_bw_xor(Parser* this, bool in_parens);
AST* Parser__parse_bw_or(Parser* this, bool in_parens);
AST* Parser__parse_relational(Parser* this, bool in_parens);
AST* Parser__parse_logical_and(Parser* this, bool in_parens);
AST* Parser__parse_logical_or(Parser* this, bool in_parens);
AST* Parser__parse_expression(Parser* this, bool in_parens);
AST* Parser__parse_match(Parser* this);
AST* Parser__parse_statement(Parser* this);
AST* Parser__parse_block(Parser* this);
Function* Parser__parse_function(Parser* this);
Structure* Parser__parse_enum(Parser* this);
Structure* Parser__parse_struct(Parser* this);
AST* Parser__parse_global_var(Parser* this);
void Parser__include_file(Parser* this, Program* program, char* filename);
void Parser__parse_use(Parser* this, Program* program);
void Parser__parse_compiler_option(Parser* this, Program* program);
void Parser__parse_into_program(Parser* this, Program* program);
Program* Parser__parse_program(Parser* this);
TypeChecker* TypeChecker__new();
void TypeChecker__push_scope(TypeChecker* this);
Map* TypeChecker__scope(TypeChecker* this);
void TypeChecker__pop_scope(TypeChecker* this);
void TypeChecker__push_var(TypeChecker* this, Variable* var);
Variable* TypeChecker__find_var(TypeChecker* this, char* name);
Variable* TypeChecker__get_struct_member(TypeChecker* this, char* lhs, char* rhs);
bool TypeChecker__type_is_valid(TypeChecker* this, Type* type);
void TypeChecker__check_method_call(TypeChecker* this, Type* method_type, AST* node);
Type* TypeChecker__check_call(TypeChecker* this, AST* node);
Type* TypeChecker__check_format_string(TypeChecker* this, AST* node);
Type* TypeChecker__check_pointer_arith(TypeChecker* this, AST* node, Type* lhs, Type* rhs);
Type* TypeChecker__check_expression(TypeChecker* this, AST* node);
void TypeChecker__check_match_for_enum(TypeChecker* this, Structure* struc, AST* node);
void TypeChecker__check_match(TypeChecker* this, AST* node);
void TypeChecker__check_statement(TypeChecker* this, AST* node);
void TypeChecker__check_block(TypeChecker* this, AST* node);
void TypeChecker__check_function(TypeChecker* this, Function* func);
void TypeChecker__check_all_functions(TypeChecker* this, Program* program);
void TypeChecker__dfs_structs(TypeChecker* this, Structure* struc, Vector* results, Map* done);
void TypeChecker__check_all_structs(TypeChecker* this, Program* program);
void TypeChecker__check_program(TypeChecker* this, Program* program);
CodeGenerator CodeGenerator__make(char* filename);
void CodeGenerator__indent(CodeGenerator* this, int num);
void CodeGenerator__push_scope(CodeGenerator* this);
Vector* CodeGenerator__scope(CodeGenerator* this);
void CodeGenerator__pop_scope(CodeGenerator* this);
void CodeGenerator__gen_control_body(CodeGenerator* this, AST* node, int indent);
void CodeGenerator__gen_enum_value(CodeGenerator* this, char* enum_name, char* value_name);
void CodeGenerator__gen_enum(CodeGenerator* this, Structure* struc);
void CodeGenerator__gen_struct(CodeGenerator* this, Structure* struc);
char* CodeGenerator__get_op(ASTType type);
void CodeGenerator__gen_type(CodeGenerator* this, Type* type);
void CodeGenerator__gen_expression(CodeGenerator* this, AST* node);
void CodeGenerator__gen_var_decl(CodeGenerator* this, AST* node);
void CodeGenerator__gen_match_string(CodeGenerator* this, AST* node, int indent);
void CodeGenerator__gen_match_case_body(CodeGenerator* this, AST* node, int indent);
void CodeGenerator__gen_match(CodeGenerator* this, AST* node, int indent);
void CodeGenerator__gen_statement(CodeGenerator* this, AST* node, int indent);
void CodeGenerator__gen_block(CodeGenerator* this, AST* node, int indent);
void CodeGenerator__gen_struct_decls(CodeGenerator* this, Program* program);
void CodeGenerator__gen_type_and_name(CodeGenerator* this, Type* type, char* name);
void CodeGenerator__gen_function_name(CodeGenerator* this, Function* func);
void CodeGenerator__gen_function_decls(CodeGenerator* this, Program* program);
void CodeGenerator__gen_function(CodeGenerator* this, Function* func);
void CodeGenerator__gen_global_vars(CodeGenerator* this, Program* program);
void CodeGenerator__gen_embed_headers(CodeGenerator* this, Program* program);
void CodeGenerator__gen_program(CodeGenerator* this, Program* program);
void usage(int code);
int main(int argc, char** argv);

/* global variables */

FILE* File__open(char* path, char* mode) {
  FILE* file = fopen(path, mode);
  if (file == ((FILE*)0)){
    printf("Error opening file '%s': %s" "\n", path, strerror(errno));
    exit(1);
  } 
  return file;
}

char* File__slurp(FILE* this) {
  int pos = ftell(this);
  fseek(this, 0, SEEK_END);
  int size = ftell(this);
  fseek(this, pos, SEEK_SET);
  void* buf = calloc((size + 1), sizeof(char));
  fread(buf, 1, size, this);
  fseek(this, pos, SEEK_SET);
  return ((char*)buf);
}

void File__puts(FILE* this, char* str) {
  fwrite(((void*)str), 1, strlen(str), this);
}

bool streq(char* str1, char* str2) {
  return strcmp(str1, str2) == 0;
}

char* substring(char* str, int start, int len) {
  char* new_str = ((char*)calloc((len + 1), sizeof(char)));
  strncpy(new_str, (str + start), len);
  return new_str;
}

Vector* Vector__new() {
  Vector* vec = ((Vector*)calloc(1, sizeof(Vector)));
  vec->size = 0;
  vec->capacity = 16;
  vec->data = ((void**)calloc(vec->capacity, sizeof(void*)));
  return vec;
}

void Vector__resize(Vector* this, int new_capacity) {
  this->capacity = new_capacity;
  this->data = ((void**)realloc(((void*)this->data), (this->capacity * sizeof(void*))));
}

void Vector__push(Vector* this, void* val) {
  if (this->size == this->capacity){
    Vector__resize(this, (this->capacity * 2));
  } 
  this->data[this->size] = val;
  this->size += 1;
}

void Vector__push_front(Vector* this, void* val) {
  if (this->size == this->capacity){
    Vector__resize(this, (this->capacity * 2));
  } 
  for (int i = this->size; (i > 0); i -= 1) {
    this->data[i] = this->data[(i - 1)];
  } 
  this->data[0] = val;
  this->size += 1;
}

void* Vector__pop(Vector* this) {
  if (this->size == 0){
    printf("pop on empty vector" "\n");
    exit(1);
  } 
  this->size -= 1;
  return this->data[this->size];
}

void* Vector__back(Vector* this) {
  if (this->size == 0){
    printf("back on empty vector" "\n");
    exit(1);
  } 
  return this->data[(this->size - 1)];
}

void* Vector__at(Vector* this, int i) {
  if (((i < 0) || (i >= this->size))){
    printf("at out of bounds in vector" "\n");
    exit(1);
  } 
  return this->data[i];
}

bool Vector__empty(Vector* this) {
  return this->size == 0;
}

void Vector__free(Vector* this) {
  free(((void*)this->data));
  free(((void*)this));
}

Location Location__make(char* filename, int line, int col) {
  Location loc;
  loc.filename = filename;
  loc.line = line;
  loc.col = col;
  return loc;
}

char* Location__str(Location this) {
  return __format_string("%s:%d:%d", this.filename, this.line, this.col);
}

Span Span__make(Location start, Location end) {
  Span span;
  span.start = start;
  span.end = end;
  return span;
}

char* Span__str(Span this) {
  return __format_string("%s => %s", Location__str(this.start), Location__str(this.end));
}

Span Span__join(Span this, Span other) {
  Span span;
  span.start = this.start;
  span.end = other.end;
  return span;
}

Token* Token__new(TokenType type, Span span, char* text) {
  Token* tok = ((Token*)calloc(1, sizeof(Token)));
  tok->type = type;
  tok->span = span;
  tok->text = text;
  tok->seen_newline = false;
  return tok;
}

Token* Token__from_type(TokenType type, Span span) {
  return Token__new(type, span, "");
}

Token* Token__from_ident(char* text, Span span) {
  TokenType type = TokenType__from_text(text);
  return Token__new(type, span, text);
}

char* Token__str(Token* this) {
  return __format_string("%s: %s", Span__str(this->span), TokenType__str(this->type));
}

TokenType TokenType__from_text(char* text) {
  {
    char *__match_str = text;
    if (streq(__match_str, "and")) {
      return TokenType__And;
    } else if (streq(__match_str, "as")) {
      return TokenType__As;
    } else if (streq(__match_str, "bool")) {
      return TokenType__Bool;
    } else if (streq(__match_str, "break")) {
      return TokenType__Break;
    } else if (streq(__match_str, "char")) {
      return TokenType__Char;
    } else if (streq(__match_str, "continue")) {
      return TokenType__Continue;
    } else if (streq(__match_str, "def")) {
      return TokenType__Def;
    } else if (streq(__match_str, "defer")) {
      return TokenType__Defer;
    } else if (streq(__match_str, "else")) {
      return TokenType__Else;
    } else if (streq(__match_str, "enum")) {
      return TokenType__Enum;
    } else if (streq(__match_str, "extern")) {
      return TokenType__Extern;
    } else if (streq(__match_str, "false")) {
      return TokenType__False;
    } else if (streq(__match_str, "f32")) {
      return TokenType__F32;
    } else if (streq(__match_str, "for")) {
      return TokenType__For;
    } else if (streq(__match_str, "fn")) {
      return TokenType__Fn;
    } else if (streq(__match_str, "i32")) {
      return TokenType__I32;
    } else if (streq(__match_str, "if")) {
      return TokenType__If;
    } else if (streq(__match_str, "let")) {
      return TokenType__Let;
    } else if (streq(__match_str, "match")) {
      return TokenType__Match;
    } else if (streq(__match_str, "not")) {
      return TokenType__Not;
    } else if (streq(__match_str, "or")) {
      return TokenType__Or;
    } else if (streq(__match_str, "return")) {
      return TokenType__Return;
    } else if (streq(__match_str, "sizeof")) {
      return TokenType__SizeOf;
    } else if (streq(__match_str, "string")) {
      return TokenType__String;
    } else if (streq(__match_str, "struct")) {
      return TokenType__Struct;
    } else if (streq(__match_str, "true")) {
      return TokenType__True;
    } else if (streq(__match_str, "u8")) {
      return TokenType__U8;
    } else if (streq(__match_str, "untyped_ptr")) {
      return TokenType__UntypedPtr;
    } else if (streq(__match_str, "union")) {
      return TokenType__Union;
    } else if (streq(__match_str, "use")) {
      return TokenType__Use;
    } else if (streq(__match_str, "void")) {
      return TokenType__Void;
    } else if (streq(__match_str, "while")) {
      return TokenType__While;
    } else  {
      return TokenType__Identifier;
    }
  }
}

char* TokenType__str(TokenType this) {
  switch (this) {
    case TokenType__And: {
      return "and";
    } break;
    case TokenType__As: {
      return "as";
    } break;
    case TokenType__Bool: {
      return "bool";
    } break;
    case TokenType__Break: {
      return "break";
    } break;
    case TokenType__Char: {
      return "char";
    } break;
    case TokenType__Continue: {
      return "continue";
    } break;
    case TokenType__Def: {
      return "def";
    } break;
    case TokenType__Defer: {
      return "defer";
    } break;
    case TokenType__Else: {
      return "else";
    } break;
    case TokenType__Enum: {
      return "enum";
    } break;
    case TokenType__Extern: {
      return "extern";
    } break;
    case TokenType__False: {
      return "false";
    } break;
    case TokenType__F32: {
      return "f32";
    } break;
    case TokenType__For: {
      return "for";
    } break;
    case TokenType__Fn: {
      return "fn";
    } break;
    case TokenType__I32: {
      return "i32";
    } break;
    case TokenType__If: {
      return "if";
    } break;
    case TokenType__Let: {
      return "let";
    } break;
    case TokenType__Match: {
      return "match";
    } break;
    case TokenType__Not: {
      return "not";
    } break;
    case TokenType__Or: {
      return "or";
    } break;
    case TokenType__Return: {
      return "return";
    } break;
    case TokenType__SizeOf: {
      return "sizeof";
    } break;
    case TokenType__String: {
      return "string";
    } break;
    case TokenType__Struct: {
      return "struct";
    } break;
    case TokenType__True: {
      return "true";
    } break;
    case TokenType__U8: {
      return "u8";
    } break;
    case TokenType__UntypedPtr: {
      return "untyped_ptr";
    } break;
    case TokenType__Union: {
      return "union";
    } break;
    case TokenType__Use: {
      return "use";
    } break;
    case TokenType__Void: {
      return "void";
    } break;
    case TokenType__While: {
      return "while";
    } break;
    case TokenType__AtSign: {
      return "AtSign";
    } break;
    case TokenType__Ampersand: {
      return "Ampersand";
    } break;
    case TokenType__Backtick: {
      return "Backtick";
    } break;
    case TokenType__Caret: {
      return "Caret";
    } break;
    case TokenType__CloseCurly: {
      return "CloseCurly";
    } break;
    case TokenType__CloseParen: {
      return "CloseParen";
    } break;
    case TokenType__CloseSquare: {
      return "CloseSquare";
    } break;
    case TokenType__Colon: {
      return "Colon";
    } break;
    case TokenType__ColonColon: {
      return "ColonColon";
    } break;
    case TokenType__Comma: {
      return "Comma";
    } break;
    case TokenType__Dot: {
      return "Dot";
    } break;
    case TokenType__EOF: {
      return "EOF";
    } break;
    case TokenType__Equals: {
      return "Equals";
    } break;
    case TokenType__EqualEquals: {
      return "EqualEquals";
    } break;
    case TokenType__Exclamation: {
      return "Exclamation";
    } break;
    case TokenType__FatArrow: {
      return "FatArrow";
    } break;
    case TokenType__FloatLiteral: {
      return "FloatLiteral";
    } break;
    case TokenType__FormatStringLiteral: {
      return "FormatStringLiteral";
    } break;
    case TokenType__GreaterThan: {
      return "GreaterThan";
    } break;
    case TokenType__GreaterThanEquals: {
      return "GreaterThanEquals";
    } break;
    case TokenType__Identifier: {
      return "Identifier";
    } break;
    case TokenType__IntLiteral: {
      return "IntLiteral";
    } break;
    case TokenType__LessThan: {
      return "LessThan";
    } break;
    case TokenType__LessThanEquals: {
      return "LessThanEquals";
    } break;
    case TokenType__Line: {
      return "Line";
    } break;
    case TokenType__Minus: {
      return "Minus";
    } break;
    case TokenType__MinusEquals: {
      return "MinusEquals";
    } break;
    case TokenType__NotEquals: {
      return "NotEquals";
    } break;
    case TokenType__OpenCurly: {
      return "OpenCurly";
    } break;
    case TokenType__OpenParen: {
      return "OpenParen";
    } break;
    case TokenType__OpenSquare: {
      return "OpenSquare";
    } break;
    case TokenType__Percent: {
      return "Percent";
    } break;
    case TokenType__Plus: {
      return "Plus";
    } break;
    case TokenType__PlusEquals: {
      return "PlusEquals";
    } break;
    case TokenType__Semicolon: {
      return "Semicolon";
    } break;
    case TokenType__Slash: {
      return "Slash";
    } break;
    case TokenType__SlashEquals: {
      return "SlashEquals";
    } break;
    case TokenType__Star: {
      return "Star";
    } break;
    case TokenType__StarEquals: {
      return "StarEquals";
    } break;
    case TokenType__StringLiteral: {
      return "StringLiteral";
    } break;
    case TokenType__CharLiteral: {
      return "CharLiteral";
    } break;
  }
}

Lexer Lexer__make(char* source, char* filename) {
  Lexer lexer;
  lexer.source = source;
  lexer.source_len = strlen(source);
  lexer.i = 0;
  lexer.loc = Location__make(filename, 1, 1);
  lexer.seen_newline = false;
  lexer.tokens = Vector__new();
  return lexer;
}

void Lexer__push(Lexer* this, Token* token) {
  token->seen_newline = this->seen_newline;
  Vector__push(this->tokens, ((void*)token));
  this->seen_newline = false;
}

void Lexer__push_type(Lexer* this, TokenType type, int len) {
  Location start_loc = this->loc;
  this->loc.col += len;
  this->i += len;
  Lexer__push(this, Token__from_type(type, Span__make(start_loc, this->loc)));
}

char Lexer__peek(Lexer* this, int offset) {
  if (this->source[this->i] == ((char)0)){
    return this->source[this->i];
  } 
  return this->source[(this->i + 1)];
}

Vector* Lexer__lex(Lexer* this) {
  while ((this->i < this->source_len)) {
    char c = this->source[this->i];
    switch (c) {
      case ' ':
      case '\t':
      case '\v':
      case '\r':
      case '\b': {
        this->loc.col += 1;
        this->i += 1;
      } break;
      case '\n': {
        this->loc.line += 1;
        this->loc.col = 1;
        this->i += 1;
        this->seen_newline = true;
      } break;
      case ';': {
        Lexer__push_type(this, TokenType__Semicolon, 1);
      } break;
      case ',': {
        Lexer__push_type(this, TokenType__Comma, 1);
      } break;
      case '.': {
        Lexer__push_type(this, TokenType__Dot, 1);
      } break;
      case '(': {
        Lexer__push_type(this, TokenType__OpenParen, 1);
      } break;
      case ')': {
        Lexer__push_type(this, TokenType__CloseParen, 1);
      } break;
      case '[': {
        Lexer__push_type(this, TokenType__OpenSquare, 1);
      } break;
      case ']': {
        Lexer__push_type(this, TokenType__CloseSquare, 1);
      } break;
      case '{': {
        Lexer__push_type(this, TokenType__OpenCurly, 1);
      } break;
      case '}': {
        Lexer__push_type(this, TokenType__CloseCurly, 1);
      } break;
      case '@': {
        Lexer__push_type(this, TokenType__AtSign, 1);
      } break;
      case '%': {
        Lexer__push_type(this, TokenType__Percent, 1);
      } break;
      case '^': {
        Lexer__push_type(this, TokenType__Caret, 1);
      } break;
      case '&': {
        Lexer__push_type(this, TokenType__Ampersand, 1);
      } break;
      case '|': {
        Lexer__push_type(this, TokenType__Line, 1);
      } break;
      case '!': {
        if (Lexer__peek(this, 1) == '=')
        Lexer__push_type(this, TokenType__NotEquals, 2);
         else 
        Lexer__push_type(this, TokenType__Exclamation, 1);
        
      } break;
      case ':': {
        if (Lexer__peek(this, 1) == ':')
        Lexer__push_type(this, TokenType__ColonColon, 2);
         else 
        Lexer__push_type(this, TokenType__Colon, 1);
        
      } break;
      case '=': {
        if (Lexer__peek(this, 1) == '=')
        Lexer__push_type(this, TokenType__EqualEquals, 2);
         else         if (Lexer__peek(this, 1) == '>')
        Lexer__push_type(this, TokenType__FatArrow, 2);
         else 
        Lexer__push_type(this, TokenType__Equals, 1);
        
        
      } break;
      case '*': {
        if (Lexer__peek(this, 1) == '=')
        Lexer__push_type(this, TokenType__StarEquals, 2);
         else 
        Lexer__push_type(this, TokenType__Star, 1);
        
      } break;
      case '+': {
        if (Lexer__peek(this, 1) == '=')
        Lexer__push_type(this, TokenType__PlusEquals, 2);
         else 
        Lexer__push_type(this, TokenType__Plus, 1);
        
      } break;
      case '-': {
        if (Lexer__peek(this, 1) == '=')
        Lexer__push_type(this, TokenType__MinusEquals, 2);
         else 
        Lexer__push_type(this, TokenType__Minus, 1);
        
      } break;
      case '/': {
        if (Lexer__peek(this, 1) == '/'){
          this->i += 1;
          while (((this->i < this->source_len) && (this->source[this->i] != '\n'))) {
            this->i += 1;
          } 
        }  else         if (Lexer__peek(this, 1) == '='){
          Lexer__push_type(this, TokenType__SlashEquals, 2);
        }  else {
          Lexer__push_type(this, TokenType__Slash, 1);
        } 
        
      } break;
      case '<': {
        if (Lexer__peek(this, 1) == '=')
        Lexer__push_type(this, TokenType__LessThanEquals, 2);
         else 
        Lexer__push_type(this, TokenType__LessThan, 1);
        
      } break;
      case '>': {
        if (Lexer__peek(this, 1) == '=')
        Lexer__push_type(this, TokenType__GreaterThanEquals, 2);
         else 
        Lexer__push_type(this, TokenType__GreaterThan, 1);
        
      } break;
      default: {
        Location start_loc = this->loc;
        if (isdigit(c)){
          int start = this->i;
          TokenType token_type;
          while (isdigit(this->source[this->i])) {
            this->i += 1;
          } 
          if (this->source[this->i] == '.'){
            this->i += 1;
            while (isdigit(this->source[this->i])) {
              this->i += 1;
            } 
            token_type = TokenType__FloatLiteral;
          }  else {
            token_type = TokenType__IntLiteral;
          } 
          int len = (this->i - start);
          char* text = substring(this->source, start, len);
          this->loc.col += len;
          Lexer__push(this, Token__new(token_type, Span__make(start_loc, this->loc), text));
        }  else         if ((isalpha(c) || c == '_')){
          int start = this->i;
          while ((isalnum(this->source[this->i]) || this->source[this->i] == '_')) {
            this->i += 1;
          } 
          int len = (this->i - start);
          char* text = substring(this->source, start, len);
          this->loc.col += len;
          Lexer__push(this, Token__from_ident(text, Span__make(start_loc, this->loc)));
        }  else         if (c == '\''){
          int start = (this->i + 1);
          this->i += 1;
          if (this->source[this->i] == '\\'){
            this->i += 2;
          }  else {
            this->i += 1;
          } 
          if ((this->source[this->i] != '\'')){
            this->loc.col += ((this->i - start) + 1);
            error_loc(this->loc, "Expected ' after character literal");
          } 
          int len = (this->i - start);
          char* text = substring(this->source, start, len);
          this->loc.col += (len + 2);
          this->i += 1;
          Lexer__push(this, Token__new(TokenType__CharLiteral, Span__make(start_loc, this->loc), text));
        }  else         if ((c == '"' || c == '`')){
          char end_char = c;
          int start = (this->i + 1);
          this->i += 1;
          while ((this->source[this->i] != c)) {
            if (this->source[this->i] == '\\'){
              this->i += 1;
            } 
            this->i += 1;
          } 
          int len = (this->i - start);
          char* text = substring(this->source, start, len);
          this->loc.col += (len + 2);
          this->i += 1;
          if (end_char == '`'){
            Lexer__push(this, Token__new(TokenType__FormatStringLiteral, Span__make(start_loc, this->loc), text));
          }  else {
            Lexer__push(this, Token__new(TokenType__StringLiteral, Span__make(start_loc, this->loc), text));
          } 
        }  else {
          printf("%s: Unrecognized char in lexer: '%d'" "\n", Location__str(this->loc), c);
          exit(1);
        } 
        
        
        
      } break;
    }
  } 
  Lexer__push_type(this, TokenType__EOF, 0);
  return this->tokens;
}

MapNode* MapNode__new(char* key, void* value, MapNode* next) {
  MapNode* node = ((MapNode*)calloc(1, sizeof(MapNode)));
  node->key = key;
  node->value = value;
  node->next = next;
  return node;
}

void MapNode__free_list(MapNode* node) {
  MapNode* cur = node;
  while ((cur != ((MapNode*)0))) {
    MapNode* next = cur->next;
    free(((void*)cur));
    cur = next;
  } 
}

Map* Map__new() {
  Map* map = ((Map*)calloc(1, sizeof(Map)));
  map->num_buckets = 4;
  map->buckets = ((MapNode**)calloc(map->num_buckets, sizeof(MapNode*)));
  return map;
}

int Map__hash(Map* this, char* s) {
  int hash = 5381;
  int len = strlen(s);
  for (int i = 0; (i < len); i += 1) {
    hash = ((hash * 33) ^ ((int)s[i]));
  } 
  hash = (hash % this->num_buckets);
  if ((hash < 0)){
    hash += this->num_buckets;
  } 
  return hash;
}

MapNode* Map__get_node(Map* this, char* key) {
  int hash = Map__hash(this, key);
  MapNode* node = this->buckets[hash];
  while ((node != ((MapNode*)0))) {
    if (streq(node->key, key)){
      return node;
    } 
    node = node->next;
  } 
  return ((MapNode*)0);
}

void* Map__get(Map* this, char* key) {
  MapNode* node = Map__get_node(this, key);
  if ((node != ((MapNode*)0))){
    return node->value;
  } 
  return ((void*)0);
}

bool Map__exists(Map* this, char* key) {
  return (Map__get_node(this, key) != ((MapNode*)0));
}

void Map__insert(Map* this, char* key, void* value) {
  MapNode* node = Map__get_node(this, key);
  if ((node != ((MapNode*)0))){
    node->value = value;
  }  else {
    int hash = Map__hash(this, key);
    MapNode* new_node = MapNode__new(key, value, this->buckets[hash]);
    if ((this->buckets[hash] != ((MapNode*)0))){
      this->num_collisions += 1;
    } 
    this->buckets[hash] = new_node;
    this->num_items += 1;
    if ((this->num_items > this->num_buckets)){
      Map__resize(this);
    } 
  } 
}

void Map__resize(Map* this) {
  MapNode** old_buckets = this->buckets;
  int old_num_buckets = this->num_buckets;
  int old_num_items = this->num_items;
  this->num_collisions = 0;
  this->num_buckets *= 2;
  this->buckets = ((MapNode**)calloc(this->num_buckets, sizeof(MapNode*)));
  for (int i = 0; (i < old_num_buckets); i += 1) {
    MapNode* node = old_buckets[i];
    while ((node != ((MapNode*)0))) {
      int new_hash = Map__hash(this, node->key);
      MapNode* new_node = MapNode__new(node->key, node->value, this->buckets[new_hash]);
      if ((this->buckets[new_hash] != ((MapNode*)0))){
        this->num_collisions += 1;
      } 
      this->buckets[new_hash] = new_node;
      node = node->next;
    } 
  } 
  for (int i = 0; (i < old_num_buckets); i += 1) {
    MapNode__free_list(old_buckets[i]);
  } 
  free(((void*)old_buckets));
}

void Map__print_keys(Map* this) {
  for (int i = 0; (i < this->num_buckets); i += 1) {
    MapNode* node = this->buckets[i];
    while ((node != ((MapNode*)0))) {
      printf("- '%s'\n" "\n", node->key);
      node = node->next;
    } 
  } 
}

void Map__free(Map* this) {
  for (int i = 0; (i < this->num_buckets); i += 1) {
    MapNode__free_list(this->buckets[i]);
  } 
  free(((void*)this->buckets));
}

Type* Type__new(BaseType base, Span span) {
  Type* type = ((Type*)calloc(1, sizeof(Type)));
  type->base = base;
  type->span = span;
  return type;
}

Type* Type__new_link(BaseType base, Type* next, Span span) {
  Type* type = Type__new(base, span);
  type->ptr = next;
  return type;
}

Type* Type__ptr_to(BaseType base, Span span) {
  Type* next = Type__new(base, span);
  return Type__new_link(BaseType__Pointer, next, span);
}

bool Type__is_struct_or_ptr(Type* this) {
  if (this->base == BaseType__Structure)
  return true;
  
  if ((this->base != BaseType__Pointer))
  return false;
  
  return this->ptr->base == BaseType__Structure;
}

bool Type__is_numeric(Type* this) {
  return (this->base == BaseType__I32 || this->base == BaseType__F32);
}

bool Type__eq(Type* this, Type* other) {
  if ((this == ((Type*)0) && other == ((Type*)0)))
  return true;
  
  if ((this == ((Type*)0) || other == ((Type*)0)))
  return false;
  
  if ((this->base != other->base))
  return false;
  
  if (this->base == BaseType__Method)
  return false;
  
  if (this->base == BaseType__Function){
    if ((!Type__eq(this->return_type, other->return_type)))
    return false;
    
    if ((this->params->size != other->params->size))
    return false;
    
    for (int i = 0; (i < this->params->size); i += 1) {
      Type* a = ((Type*)Vector__at(this->params, i));
      Type* b = ((Type*)Vector__at(other->params, i));
      if ((!Type__eq(a, b)))
      return false;
      
    } 
    return true;
  } 
  if (this->base == BaseType__Structure)
  return streq(this->name, other->name);
  
  if (this->base == BaseType__Pointer)
  return Type__eq(this->ptr, other->ptr);
  
  return true;
}

char* Type__str(Type* this) {
  switch (this->base) {
    case BaseType__Void: {
      return "void";
    } break;
    case BaseType__Char: {
      return "char";
    } break;
    case BaseType__I32: {
      return "i32";
    } break;
    case BaseType__F32: {
      return "f32";
    } break;
    case BaseType__Bool: {
      return "bool";
    } break;
    case BaseType__U8: {
      return "u8";
    } break;
    case BaseType__Pointer: {
      return __format_string("&%s", Type__str(this->ptr));
    } break;
    case BaseType__Structure: {
      return this->name;
    } break;
    case BaseType__Function: {
      return "<function>";
    } break;
    case BaseType__Method: {
      return "<method>";
    } break;
  }
}

Type* Type__reverse(Type* this) {
  Type* rev = ((Type*)0);
  Type* cur = this;
  while ((cur != ((Type*)0))) {
    Type* tmp = cur->ptr;
    cur->ptr = rev;
    rev = cur;
    cur = tmp;
  } 
  return rev;
}

bool Type__is_string(Type* this) {
  return (this->base == BaseType__Pointer && this->ptr->base == BaseType__Char);
}

char* ASTType__str(ASTType this) {
  switch (this) {
    case ASTType__Assignment: {
      return "Assignment";
    } break;
    case ASTType__Address: {
      return "Address";
    } break;
    case ASTType__And: {
      return "And";
    } break;
    case ASTType__Block: {
      return "Block";
    } break;
    case ASTType__BoolLiteral: {
      return "BoolLiteral";
    } break;
    case ASTType__BitwiseAnd: {
      return "BitwiseAnd";
    } break;
    case ASTType__BitwiseOr: {
      return "BitwiseOr";
    } break;
    case ASTType__BitwiseXor: {
      return "BitwiseXor";
    } break;
    case ASTType__Break: {
      return "Break";
    } break;
    case ASTType__Call: {
      return "Call";
    } break;
    case ASTType__Cast: {
      return "Cast";
    } break;
    case ASTType__CharLiteral: {
      return "CharLiteral";
    } break;
    case ASTType__Continue: {
      return "Continue";
    } break;
    case ASTType__Defer: {
      return "Defer";
    } break;
    case ASTType__Dereference: {
      return "Dereference";
    } break;
    case ASTType__Divide: {
      return "Divide";
    } break;
    case ASTType__DivideEquals: {
      return "DivideEquals";
    } break;
    case ASTType__EnumValue: {
      return "EnumValue";
    } break;
    case ASTType__Equals: {
      return "Equals";
    } break;
    case ASTType__FloatLiteral: {
      return "FloatLiteral";
    } break;
    case ASTType__FormatStringLiteral: {
      return "FormatStringLiteral";
    } break;
    case ASTType__For: {
      return "For";
    } break;
    case ASTType__GreaterThan: {
      return "GreaterThan";
    } break;
    case ASTType__GreaterThanEquals: {
      return "GreaterThanEquals";
    } break;
    case ASTType__If: {
      return "If";
    } break;
    case ASTType__Identifier: {
      return "Identifier";
    } break;
    case ASTType__Index: {
      return "Index";
    } break;
    case ASTType__IntLiteral: {
      return "IntLiteral";
    } break;
    case ASTType__LessThan: {
      return "LessThan";
    } break;
    case ASTType__LessThanEquals: {
      return "LessThanEquals";
    } break;
    case ASTType__Match: {
      return "Match";
    } break;
    case ASTType__Member: {
      return "Member";
    } break;
    case ASTType__Minus: {
      return "Minus";
    } break;
    case ASTType__MinusEquals: {
      return "MinusEquals";
    } break;
    case ASTType__Modulus: {
      return "Modulus";
    } break;
    case ASTType__Multiply: {
      return "Multiply";
    } break;
    case ASTType__MultiplyEquals: {
      return "MultiplyEquals";
    } break;
    case ASTType__Not: {
      return "Not";
    } break;
    case ASTType__NotEquals: {
      return "NotEquals";
    } break;
    case ASTType__Or: {
      return "Or";
    } break;
    case ASTType__Plus: {
      return "Plus";
    } break;
    case ASTType__PlusEquals: {
      return "PlusEquals";
    } break;
    case ASTType__Return: {
      return "Return";
    } break;
    case ASTType__SizeOf: {
      return "SizeOf";
    } break;
    case ASTType__ScopeLookup: {
      return "ScopeLookup";
    } break;
    case ASTType__StringLiteral: {
      return "StringLiteral";
    } break;
    case ASTType__UnaryMinus: {
      return "UnaryMinus";
    } break;
    case ASTType__VarDeclaration: {
      return "VarDeclaration";
    } break;
    case ASTType__While: {
      return "While";
    } break;
  }
}

ASTType ASTType__from_token(TokenType type) {
  switch (type) {
    case TokenType__Ampersand: {
      return ASTType__BitwiseAnd;
    } break;
    case TokenType__And: {
      return ASTType__And;
    } break;
    case TokenType__Caret: {
      return ASTType__BitwiseXor;
    } break;
    case TokenType__EqualEquals: {
      return ASTType__Equals;
    } break;
    case TokenType__Equals: {
      return ASTType__Assignment;
    } break;
    case TokenType__GreaterThan: {
      return ASTType__GreaterThan;
    } break;
    case TokenType__GreaterThanEquals: {
      return ASTType__GreaterThanEquals;
    } break;
    case TokenType__LessThan: {
      return ASTType__LessThan;
    } break;
    case TokenType__LessThanEquals: {
      return ASTType__LessThanEquals;
    } break;
    case TokenType__Line: {
      return ASTType__BitwiseOr;
    } break;
    case TokenType__Minus: {
      return ASTType__Minus;
    } break;
    case TokenType__MinusEquals: {
      return ASTType__MinusEquals;
    } break;
    case TokenType__NotEquals: {
      return ASTType__NotEquals;
    } break;
    case TokenType__Or: {
      return ASTType__Or;
    } break;
    case TokenType__Percent: {
      return ASTType__Modulus;
    } break;
    case TokenType__Plus: {
      return ASTType__Plus;
    } break;
    case TokenType__PlusEquals: {
      return ASTType__PlusEquals;
    } break;
    case TokenType__Slash: {
      return ASTType__Divide;
    } break;
    case TokenType__SlashEquals: {
      return ASTType__DivideEquals;
    } break;
    case TokenType__Star: {
      return ASTType__Multiply;
    } break;
    case TokenType__StarEquals: {
      return ASTType__MultiplyEquals;
    } break;
    default: {
      printf("Unhandled token type in ASTType::from_token: %s" "\n", TokenType__str(type));
      exit(1);
    } break;
  }
}

Variable* Variable__new(char* name, Type* type, Span span) {
  Variable* var = ((Variable*)calloc(1, sizeof(Variable)));
  var->name = name;
  var->type = type;
  var->span = span;
  return var;
}

Function* Function__new(Span span) {
  Function* func = ((Function*)calloc(1, sizeof(Function)));
  func->params = Vector__new();
  func->span = span;
  return func;
}

Structure* Structure__new(Span span) {
  Structure* struct_ = ((Structure*)calloc(1, sizeof(Structure)));
  struct_->fields = Vector__new();
  struct_->span = span;
  return struct_;
}

Variable* Structure__find_field(Structure* this, char* name) {
  for (int i = 0; (i < this->fields->size); i += 1) {
    Variable* field = ((Variable*)Vector__at(this->fields, i));
    if (streq(field->name, name)){
      return field;
    } 
  } 
  return ((Variable*)0);
}

Program* Program__new() {
  Program* prog = ((Program*)calloc(1, sizeof(Program)));
  prog->functions = Vector__new();
  prog->structures = Vector__new();
  prog->global_vars = Vector__new();
  prog->included_files = Map__new();
  prog->c_flags = Vector__new();
  prog->c_includes = Vector__new();
  prog->c_embed_headers = Vector__new();
  return prog;
}

bool Program__is_file_included(Program* this, char* filename) {
  int len = strlen(filename);
  if ((((len > 2) && filename[0] == '.') && filename[1] == '/')){
    filename = (&filename[2]);
  } 
  return Map__exists(this->included_files, filename);
}

void Program__add_included_file(Program* this, char* filename) {
  int len = strlen(filename);
  if ((((len > 2) && filename[0] == '.') && filename[1] == '/')){
    filename = (&filename[2]);
  } 
  Map__insert(this->included_files, filename, ((void*)filename));
}

MatchCase* MatchCase__new(AST* cond, AST* body) {
  MatchCase* _case = ((MatchCase*)calloc(1, sizeof(MatchCase)));
  _case->cond = cond;
  _case->body = body;
  return _case;
}

AST* AST__new(ASTType type, Span span) {
  AST* ast = ((AST*)calloc(1, sizeof(AST)));
  ast->type = type;
  ast->span = span;
  return ast;
}

AST* AST__new_unop(ASTType type, Span span, AST* expr) {
  AST* ast = AST__new(type, span);
  ast->u.unary = expr;
  return ast;
}

AST* AST__new_binop(ASTType type, AST* lhs, AST* rhs) {
  AST* ast = AST__new(type, Span__join(lhs->span, rhs->span));
  ast->u.binary.lhs = lhs;
  ast->u.binary.rhs = rhs;
  return ast;
}

bool AST__callee_is(AST* this, char* expected) {
  if (this == ((AST*)0))
  return false;
  
  if ((this->type != ASTType__Call))
  return false;
  
  if ((this->u.call.callee->type != ASTType__Identifier))
  return false;
  
  char* name = this->u.call.callee->u.ident.name;
  return streq(name, expected);
}

int min(int a, int b) {
  if ((a < b))
  return a;
   else 
  return b;
  
}

float minf(float a, float b) {
  if ((a < b))
  return a;
   else 
  return b;
  
}

int max(int a, int b) {
  if ((a > b))
  return a;
   else 
  return b;
  
}

float maxf(float a, float b) {
  if ((a > b))
  return a;
   else 
  return b;
  
}

float clampf(float x, float min, float max) {
  return maxf(minf(x, max), min);
}

float clamp01(float x) {
  return clampf(x, 0.0, 1.0);
}

void error_loc(Location loc, char* msg) {
  error_span(Span__make(loc, loc), msg);
}

void error_span(Span span, char* msg) {
  char* filename = span.start.filename;
  FILE* file = File__open(filename, "r");
  ;
  char* contents = File__slurp(file);
  ;
  int min_line = max((span.start.line - 2), 1);
  int max_line = (span.end.line + 2);
  printf("---------------------------------------------------------------" "\n");
  printf("%s: %s" "\n", Location__str(span.start), msg);
  printf("---------------------------------------------------------------" "\n");
  char* lines = contents;
  char* cur = strsep((&lines), "\n");
  int line_no = 1;
  while (((cur != ((char*)0)) && (line_no <= max_line))) {
    if (((line_no >= min_line) && (line_no <= max_line))){
      printf("%4d | ", line_no);
      if (line_no == span.start.line){
        int start_col = (span.start.col - 1);
        int end_col = (span.end.col - 1);
        if ((span.end.line != span.start.line)){
          end_col = strlen(cur);
        } 
        for (int i = 0; (i < start_col); i += 1) {
          printf("%c", cur[i]);
        } 
        printf("\x1b[31m");
        for (int i = start_col; (i < end_col); i += 1) {
          printf("%c", cur[i]);
        } 
        printf("\x1b[0m%s" "\n", (cur + end_col));
        printf("%*s\x1b[31m^ %s\x1b[0m" "\n", (start_col + 7), "", msg);
      }  else {
        printf("%s" "\n", cur);
      } 
    } 
    line_no += 1;
    cur = strsep((&lines), "\n");
  } 
  printf("---------------------------------------------------------------" "\n");
  exit(1);

/* defers */
  free(((void*)contents));
  fclose(file);
}

Parser* Parser__make(Vector* tokens) {
  Parser* parser = ((Parser*)calloc(1, sizeof(Parser)));
  parser->tokens = tokens;
  parser->curr = 0;
  return parser;
}

void Parser__error(Parser* this, char* msg) {
  error_span(Parser__token(this)->span, msg);
}

void Parser__unhandled_type(Parser* this, char* func) {
  Parser__error(this, __format_string("Unexpected token in %s: %s", func, TokenType__str(Parser__token(this)->type)));
}

Token* Parser__token(Parser* this) {
  return ((Token*)Vector__at(this->tokens, this->curr));
}

bool Parser__token_is(Parser* this, TokenType type) {
  return Parser__token(this)->type == type;
}

bool Parser__consume_if(Parser* this, TokenType type) {
  if (Parser__token_is(this, type)){
    this->curr += 1;
    return true;
  } 
  return false;
}

void Parser__consume_newline_or(Parser* this, TokenType type) {
  if (Parser__token_is(this, type)){
    this->curr += 1;
  }  else   if ((!Parser__token(this)->seen_newline)){
    Parser__error(this, __format_string("Expected %s or newline", TokenType__str(type)));
  } 
  
}

Token* Parser__consume(Parser* this, TokenType type) {
  if ((!Parser__consume_if(this, type))){
    Parser__error(this, __format_string("Expected TokenType::%s", TokenType__str(type)));
  } 
  return ((Token*)Vector__at(this->tokens, (this->curr - 1)));
}

Type* Parser__parse_type(Parser* this) {
  Type* type = ((Type*)0);
  Span start_span = Parser__token(this)->span;
  while (true) {
    if (Parser__token_is(this, TokenType__Ampersand)){
      type = Type__new_link(BaseType__Pointer, type, Parser__token(this)->span);
      this->curr += 1;
    }  else {
      break;
    } 
  } 
  switch (Parser__token(this)->type) {
    case TokenType__I32: {
      type = Type__new_link(BaseType__I32, type, Span__join(start_span, Parser__token(this)->span));
      this->curr += 1;
    } break;
    case TokenType__Bool: {
      type = Type__new_link(BaseType__Bool, type, Span__join(start_span, Parser__token(this)->span));
      this->curr += 1;
    } break;
    case TokenType__Char: {
      type = Type__new_link(BaseType__Char, type, Span__join(start_span, Parser__token(this)->span));
      this->curr += 1;
    } break;
    case TokenType__U8: {
      type = Type__new_link(BaseType__U8, type, Span__join(start_span, Parser__token(this)->span));
      this->curr += 1;
    } break;
    case TokenType__F32: {
      type = Type__new_link(BaseType__F32, type, Span__join(start_span, Parser__token(this)->span));
      this->curr += 1;
    } break;
    case TokenType__String: {
      Span span = Span__join(start_span, Parser__token(this)->span);
      type = Type__new_link(BaseType__Char, Type__new_link(BaseType__Pointer, type, span), span);
      this->curr += 1;
    } break;
    case TokenType__UntypedPtr: {
      Span span = Span__join(start_span, Parser__token(this)->span);
      type = Type__new_link(BaseType__Void, Type__new_link(BaseType__Pointer, type, span), span);
      this->curr += 1;
    } break;
    case TokenType__Identifier: {
      type = Type__new_link(BaseType__Structure, type, Span__join(start_span, Parser__token(this)->span));
      type->name = Parser__consume(this, TokenType__Identifier)->text;
    } break;
    case TokenType__Fn: {
      Parser__consume(this, TokenType__Fn);
      Parser__consume(this, TokenType__OpenParen);
      Vector* params = Vector__new();
      while ((!Parser__token_is(this, TokenType__CloseParen))) {
        Vector__push(params, ((void*)Parser__parse_type(this)));
        if ((!Parser__token_is(this, TokenType__CloseParen))){
          Parser__consume(this, TokenType__Comma);
        } 
      } 
      Parser__consume(this, TokenType__CloseParen);
      Type* return_type;
      if (Parser__consume_if(this, TokenType__Colon)){
        return_type = Parser__parse_type(this);
      }  else {
        return_type = Type__new(BaseType__Void, Parser__token(this)->span);
      } 
      type = Type__new_link(BaseType__Function, type, Span__join(start_span, Parser__token(this)->span));
      type->params = params;
      type->return_type = return_type;
    } break;
    default: {
      Parser__unhandled_type(this, "parse_type");
    } break;
  }
  return Type__reverse(type);
}

AST* Parser__parse_format_string(Parser* this) {
  Token* fstr = Parser__consume(this, TokenType__FormatStringLiteral);
  int fstr_len = strlen(fstr->text);
  Vector* expr_parts = Vector__new();
  Vector* expr_start = Vector__new();
  ;
  ;
  Vector* format_parts = Vector__new();
  int count = 0;
  int cur_start = 0;
  for (int i = 0; (i < fstr_len); i += 1) {
    if (fstr->text[i] == '{'){
      if (count == 0){
        char* part = substring(fstr->text, cur_start, (i - cur_start));
        Vector__push(format_parts, ((void*)part));
        cur_start = (i + 1);
      } 
      count += 1;
    }  else     if (fstr->text[i] == '}'){
      count -= 1;
      if (count == 0){
        char* part = substring(fstr->text, cur_start, (i - cur_start));
        Vector__push(expr_parts, ((void*)part));
        Vector__push(expr_start, ((void*)(fstr->text + cur_start)));
        cur_start = (i + 1);
      }  else       if ((count < 0)){
        error_span(fstr->span, "Unmatched '}' in format string");
      } 
      
    } 
    
  } 
  if ((count != 0)){
    error_span(fstr->span, "Unmatched '{' in format string");
  } 
  char* part = substring(fstr->text, cur_start, (fstr_len - cur_start));
  Vector__push(format_parts, ((void*)part));
  AST* node = AST__new(ASTType__FormatStringLiteral, fstr->span);
  node->u.fmt_str.parts = format_parts;
  Location fstr_start = fstr->span.start;
  Vector* expr_nodes = Vector__new();
  for (int i = 0; (i < expr_parts->size); i += 1) {
    char* part = ((char*)Vector__at(expr_parts, i));
    int start = (((char*)Vector__at(expr_start, i)) - fstr->text);
    Lexer lexer = Lexer__make(part, fstr_start.filename);
    lexer.loc = fstr_start;
    lexer.loc.col += start;
    Vector* tokens = Lexer__lex((&lexer));
    Parser* parser = Parser__make(tokens);
    AST* expr = Parser__parse_expression(parser, false);
    Vector__push(expr_nodes, ((void*)expr));
  } 
  node->u.fmt_str.exprs = expr_nodes;
  return node;

/* defers */
  Vector__free(expr_start);
  Vector__free(expr_parts);
}

AST* Parser__parse_factor(Parser* this, bool in_parens) {
  AST* node = ((AST*)0);
  switch (Parser__token(this)->type) {
    case TokenType__FormatStringLiteral: {
      node = Parser__parse_format_string(this);
    } break;
    case TokenType__IntLiteral: {
      node = AST__new(ASTType__IntLiteral, Parser__token(this)->span);
      Token* tok = Parser__consume(this, TokenType__IntLiteral);
      node->u.num_literal = tok->text;
    } break;
    case TokenType__FloatLiteral: {
      node = AST__new(ASTType__FloatLiteral, Parser__token(this)->span);
      Token* tok = Parser__consume(this, TokenType__FloatLiteral);
      node->u.num_literal = tok->text;
    } break;
    case TokenType__StringLiteral: {
      node = AST__new(ASTType__StringLiteral, Parser__token(this)->span);
      Token* tok = Parser__consume(this, TokenType__StringLiteral);
      node->u.string_literal = tok->text;
    } break;
    case TokenType__CharLiteral: {
      node = AST__new(ASTType__CharLiteral, Parser__token(this)->span);
      Token* tok = Parser__consume(this, TokenType__CharLiteral);
      node->u.char_literal = tok->text;
    } break;
    case TokenType__True:
    case TokenType__False: {
      Token* tok = Parser__consume(this, Parser__token(this)->type);
      node = AST__new(ASTType__BoolLiteral, tok->span);
      node->u.bool_literal = tok->type == TokenType__True;
    } break;
    case TokenType__Dot: {
      Token* op = Parser__consume(this, TokenType__Dot);
      Token* rhs = Parser__consume(this, TokenType__Identifier);
      AST* lhs = AST__new(ASTType__Identifier, op->span);
      lhs->u.ident.name = "this";
      lhs->u.ident.is_function = false;
      node = AST__new(ASTType__Member, Span__join(lhs->span, rhs->span));
      node->u.member.lhs = lhs;
      node->u.member.name = rhs->text;
    } break;
    case TokenType__Minus: {
      Token* op = Parser__consume(this, TokenType__Minus);
      AST* expr = Parser__parse_factor(this, in_parens);
      node = AST__new_unop(ASTType__UnaryMinus, Span__join(op->span, expr->span), expr);
    } break;
    case TokenType__Not: {
      Token* op = Parser__consume(this, TokenType__Not);
      AST* expr = Parser__parse_factor(this, in_parens);
      node = AST__new_unop(ASTType__Not, Span__join(op->span, expr->span), expr);
    } break;
    case TokenType__Ampersand: {
      Token* op = Parser__consume(this, TokenType__Ampersand);
      AST* expr = Parser__parse_factor(this, in_parens);
      node = AST__new_unop(ASTType__Address, Span__join(op->span, expr->span), expr);
    } break;
    case TokenType__Star: {
      Token* op = Parser__consume(this, TokenType__Star);
      AST* expr = Parser__parse_factor(this, in_parens);
      node = AST__new_unop(ASTType__Dereference, Span__join(op->span, expr->span), expr);
    } break;
    case TokenType__Identifier: {
      Token* op = Parser__consume(this, TokenType__Identifier);
      node = AST__new(ASTType__Identifier, op->span);
      node->u.ident.name = op->text;
    } break;
    case TokenType__OpenParen: {
      Token* open = Parser__consume(this, TokenType__OpenParen);
      node = Parser__parse_expression(this, true);
      Token* close = Parser__consume(this, TokenType__CloseParen);
      node->span = Span__join(open->span, close->span);
    } break;
    case TokenType__SizeOf: {
      Token* start = Parser__consume(this, TokenType__SizeOf);
      Parser__consume(this, TokenType__OpenParen);
      Type* type = Parser__parse_type(this);
      Token* close = Parser__consume(this, TokenType__CloseParen);
      node = AST__new(ASTType__SizeOf, Span__join(start->span, close->span));
      node->u.size_of_type = type;
    } break;
    default: {
      Parser__unhandled_type(this, "parse_expression");
    } break;
  }
  bool running = true;
  while (running) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    switch (Parser__token(this)->type) {
      case TokenType__OpenParen: {
        Span paren_span = Parser__consume(this, TokenType__OpenParen)->span;
        Vector* args = Vector__new();
        while ((!Parser__token_is(this, TokenType__CloseParen))) {
          AST* expr = Parser__parse_expression(this, false);
          Vector__push(args, ((void*)expr));
          if ((!Parser__token_is(this, TokenType__CloseParen))){
            Parser__consume(this, TokenType__Comma);
          } 
        } 
        Parser__consume(this, TokenType__CloseParen);
        ASTType call_type = ASTType__Call;
        AST* call = AST__new(call_type, paren_span);
        call->u.call.callee = node;
        call->u.call.args = args;
        call->u.call.added_method_arg = false;
        node = call;
      } break;
      case TokenType__OpenSquare: {
        Parser__consume(this, TokenType__OpenSquare);
        AST* index = Parser__parse_expression(this, true);
        Parser__consume(this, TokenType__CloseSquare);
        node = AST__new_binop(ASTType__Index, node, index);
      } break;
      case TokenType__Dot: {
        Parser__consume(this, TokenType__Dot);
        Token* name = Parser__consume(this, TokenType__Identifier);
        AST* member = AST__new(ASTType__Member, Span__join(node->span, name->span));
        member->u.member.lhs = node;
        member->u.member.name = name->text;
        node = member;
      } break;
      case TokenType__ColonColon: {
        Parser__consume(this, TokenType__ColonColon);
        Token* name = Parser__consume(this, TokenType__Identifier);
        AST* member = AST__new(ASTType__ScopeLookup, Span__join(node->span, name->span));
        member->u.member.lhs = node;
        member->u.member.name = name->text;
        node = member;
      } break;
      case TokenType__As: {
        Parser__consume(this, TokenType__As);
        Type* type = Parser__parse_type(this);
        AST* cast = AST__new(ASTType__Cast, Span__join(node->span, type->span));
        cast->u.cast.lhs = node;
        cast->u.cast.to = type;
        node = cast;
      } break;
      default: {
        running = false;
      } break;
    }
  } 
  return node;
}

AST* Parser__parse_term(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_factor(this, in_parens);
  while (((Parser__token_is(this, TokenType__Star) || Parser__token_is(this, TokenType__Slash)) || Parser__token_is(this, TokenType__Percent))) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_factor(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_additive(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_term(this, in_parens);
  while ((Parser__token_is(this, TokenType__Plus) || Parser__token_is(this, TokenType__Minus))) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_term(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_bw_and(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_additive(this, in_parens);
  while (Parser__token_is(this, TokenType__Ampersand)) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_additive(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_bw_xor(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_bw_and(this, in_parens);
  while (Parser__token_is(this, TokenType__Caret)) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_bw_and(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_bw_or(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_bw_xor(this, in_parens);
  while (Parser__token_is(this, TokenType__Line)) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_bw_xor(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_relational(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_bw_or(this, in_parens);
  while ((((((Parser__token_is(this, TokenType__LessThan) || Parser__token_is(this, TokenType__GreaterThan)) || Parser__token_is(this, TokenType__LessThanEquals)) || Parser__token_is(this, TokenType__GreaterThanEquals)) || Parser__token_is(this, TokenType__EqualEquals)) || Parser__token_is(this, TokenType__NotEquals))) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_bw_or(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_logical_and(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_relational(this, in_parens);
  while (Parser__token_is(this, TokenType__And)) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_relational(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_logical_or(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_logical_and(this, in_parens);
  while (Parser__token_is(this, TokenType__Or)) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_logical_and(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_expression(Parser* this, bool in_parens) {
  AST* lhs = Parser__parse_logical_or(this, in_parens);
  while (((((Parser__token_is(this, TokenType__Equals) || Parser__token_is(this, TokenType__PlusEquals)) || Parser__token_is(this, TokenType__MinusEquals)) || Parser__token_is(this, TokenType__StarEquals)) || Parser__token_is(this, TokenType__SlashEquals))) {
    if (((!in_parens) && Parser__token(this)->seen_newline))
    break;
    
    ASTType op = ASTType__from_token(Parser__token(this)->type);
    this->curr += 1;
    AST* rhs = Parser__parse_expression(this, in_parens);
    lhs = AST__new_binop(op, lhs, rhs);
  } 
  return lhs;
}

AST* Parser__parse_match(Parser* this) {
  Token* op = Parser__consume(this, TokenType__Match);
  AST* expr = Parser__parse_expression(this, false);
  AST* node = AST__new(ASTType__Match, Span__join(op->span, expr->span));
  node->u.match_stmt.expr = expr;
  Vector* cases = Vector__new();
  Parser__consume(this, TokenType__OpenCurly);
  while ((!Parser__token_is(this, TokenType__CloseCurly))) {
    if (Parser__token_is(this, TokenType__Else)){
      node->u.match_stmt.defolt_span = Parser__token(this)->span;
      Parser__consume(this, TokenType__Else);
      Parser__consume(this, TokenType__FatArrow);
      node->u.match_stmt.defolt = Parser__parse_statement(this);
    }  else {
      AST* cond = Parser__parse_factor(this, false);
      AST* body = ((AST*)0);
      if ((!Parser__consume_if(this, TokenType__Line))){
        Parser__consume(this, TokenType__FatArrow);
        body = Parser__parse_statement(this);
        if ((!Parser__token_is(this, TokenType__CloseCurly))){
          Parser__consume_newline_or(this, TokenType__Comma);
        } 
      } 
      MatchCase* _case = MatchCase__new(cond, body);
      Vector__push(cases, ((void*)_case));
    } 
  } 
  Parser__consume(this, TokenType__CloseCurly);
  node->u.match_stmt.cases = cases;
  return node;
}

AST* Parser__parse_statement(Parser* this) {
  AST* node = ((AST*)0);
  Span start_span = Parser__token(this)->span;
  switch (Parser__token(this)->type) {
    case TokenType__Match: {
      node = Parser__parse_match(this);
    } break;
    case TokenType__OpenCurly: {
      node = Parser__parse_block(this);
    } break;
    case TokenType__Return: {
      Parser__consume(this, TokenType__Return);
      AST* expr = ((AST*)0);
      if ((!Parser__token(this)->seen_newline)){
        expr = Parser__parse_expression(this, false);
      } 
      node = AST__new_unop(ASTType__Return, Span__join(start_span, Parser__token(this)->span), expr);
      Parser__consume_newline_or(this, TokenType__Semicolon);
    } break;
    case TokenType__Break: {
      node = AST__new(ASTType__Break, start_span);
      Parser__consume(this, TokenType__Break);
      Parser__consume_newline_or(this, TokenType__Semicolon);
    } break;
    case TokenType__Continue: {
      Parser__consume(this, TokenType__Continue);
      node = AST__new(ASTType__Continue, start_span);
      Parser__consume_newline_or(this, TokenType__Semicolon);
    } break;
    case TokenType__Defer: {
      Parser__consume(this, TokenType__Defer);
      AST* expr = Parser__parse_statement(this);
      node = AST__new_unop(ASTType__Defer, Span__join(start_span, expr->span), expr);
    } break;
    case TokenType__If: {
      Parser__consume(this, TokenType__If);
      AST* cond = Parser__parse_expression(this, false);
      AST* then = Parser__parse_statement(this);
      Span end_span = then->span;
      AST* els = ((AST*)0);
      if (Parser__consume_if(this, TokenType__Else)){
        els = Parser__parse_statement(this);
        end_span = els->span;
      } 
      node = AST__new(ASTType__If, Span__join(start_span, end_span));
      node->u.if_stmt.cond = cond;
      node->u.if_stmt.then = then;
      node->u.if_stmt.els = els;
    } break;
    case TokenType__While: {
      Parser__consume(this, TokenType__While);
      AST* cond = Parser__parse_expression(this, false);
      AST* body = Parser__parse_statement(this);
      node = AST__new(ASTType__While, Span__join(start_span, body->span));
      node->u.loop.cond = cond;
      node->u.loop.body = body;
    } break;
    case TokenType__For: {
      node = AST__new(ASTType__For, Parser__token(this)->span);
      Parser__consume(this, TokenType__For);
      if ((!Parser__token_is(this, TokenType__Semicolon))){
        AST* init = Parser__parse_statement(this);
        if (((init->type != ASTType__Assignment) && (init->type != ASTType__VarDeclaration))){
          error_span(init->span, "Invalid for loop initializer");
        } 
        node->u.loop.init = init;
        Token* prev = ((Token*)Vector__at(this->tokens, (this->curr - 1)));
        if (prev->type == TokenType__Semicolon){
          this->curr -= 1;
        } 
      } 
      Parser__consume(this, TokenType__Semicolon);
      if ((!Parser__token_is(this, TokenType__Semicolon)))
      node->u.loop.cond = Parser__parse_expression(this, true);
      
      Parser__consume(this, TokenType__Semicolon);
      if ((!Parser__token_is(this, TokenType__CloseCurly)))
      node->u.loop.incr = Parser__parse_expression(this, false);
      
      node->u.loop.body = Parser__parse_statement(this);
      node->span = Span__join(node->span, node->u.loop.body->span);
    } break;
    case TokenType__Let: {
      Parser__consume(this, TokenType__Let);
      Token* name = Parser__consume(this, TokenType__Identifier);
      Span end_span = name->span;
      Type* type = ((Type*)0);
      if (Parser__consume_if(this, TokenType__Colon)){
        type = Parser__parse_type(this);
        end_span = type->span;
      } 
      AST* init = ((AST*)0);
      if (Parser__consume_if(this, TokenType__Equals)){
        init = Parser__parse_expression(this, false);
        end_span = init->span;
      } 
      Parser__consume_newline_or(this, TokenType__Semicolon);
      node = AST__new(ASTType__VarDeclaration, Span__join(start_span, end_span));
      node->u.var_decl.var = Variable__new(name->text, type, name->span);
      node->u.var_decl.init = init;
    } break;
    default: {
      node = Parser__parse_expression(this, false);
      Parser__consume_newline_or(this, TokenType__Semicolon);
    } break;
  }
  return node;
}

AST* Parser__parse_block(Parser* this) {
  AST* node = AST__new(ASTType__Block, Parser__token(this)->span);
  Parser__consume(this, TokenType__OpenCurly);
  Vector* statements = Vector__new();
  while ((!Parser__token_is(this, TokenType__CloseCurly))) {
    AST* statement = Parser__parse_statement(this);
    Vector__push(statements, ((void*)statement));
  } 
  node->u.block.statements = statements;
  Parser__consume(this, TokenType__CloseCurly);
  return node;
}

Function* Parser__parse_function(Parser* this) {
  Parser__consume(this, TokenType__Def);
  char* struct_name = ((char*)0);
  bool is_method = false;
  bool is_static = false;
  Token* name = Parser__consume(this, TokenType__Identifier);
  if (Parser__consume_if(this, TokenType__ColonColon)){
    is_method = true;
    struct_name = name->text;
    name = Parser__consume(this, TokenType__Identifier);
  } 
  Function* func = Function__new(name->span);
  func->name = name->text;
  func->is_method = is_method;
  func->method_struct_name = struct_name;
  Parser__consume(this, TokenType__OpenParen);
  while ((!Parser__token_is(this, TokenType__CloseParen))) {
    bool found_amp = Parser__consume_if(this, TokenType__Ampersand);
    Token* var_name = Parser__consume(this, TokenType__Identifier);
    Type* type = ((Type*)0);
    if ((Vector__empty(func->params) && is_method)){
      if (streq(var_name->text, "this")){
        type = Type__new(BaseType__Structure, name->span);
        type->name = struct_name;
        if (found_amp){
          type = Type__new_link(BaseType__Pointer, type, name->span);
        } 
      }  else       if (found_amp){
        error_span(var_name->span, "Expected 'this' over here");
      }  else {
        is_static = true;
      } 
      
    } 
    if (type == ((Type*)0)){
      Parser__consume(this, TokenType__Colon);
      type = Parser__parse_type(this);
    } 
    Variable* var = Variable__new(var_name->text, type, var_name->span);
    Vector__push(func->params, ((void*)var));
    if ((!Parser__token_is(this, TokenType__CloseParen))){
      Parser__consume(this, TokenType__Comma);
    } 
  } 
  Parser__consume(this, TokenType__CloseParen);
  if ((is_method && func->params->size == 0)){
    is_static = true;
  } 
  func->is_static = is_static;
  if (Parser__consume_if(this, TokenType__Colon)){
    func->return_type = Parser__parse_type(this);
  }  else   if (streq(name->text, "main")){
    func->return_type = Type__new(BaseType__I32, name->span);
  }  else {
    func->return_type = Type__new(BaseType__Void, name->span);
  } 
  
  if (Parser__consume_if(this, TokenType__Extern)){
    func->is_extern = true;
    func->extern_name = func->name;
    if (Parser__consume_if(this, TokenType__OpenParen)){
      Token* name = Parser__consume(this, TokenType__StringLiteral);
      func->extern_name = name->text;
      Parser__consume(this, TokenType__CloseParen);
    } 
  }  else {
    func->is_extern = false;
    func->body = Parser__parse_block(this);
  } 
  return func;
}

Structure* Parser__parse_enum(Parser* this) {
  Span start_span = Parser__consume(this, TokenType__Enum)->span;
  Token* name = Parser__consume(this, TokenType__Identifier);
  Structure* enum_def = Structure__new(Span__join(start_span, name->span));
  enum_def->name = name->text;
  enum_def->is_enum = true;
  Type* type = Type__new(BaseType__Structure, name->span);
  enum_def->type = type;
  type->name = name->text;
  type->struct_def = enum_def;
  Parser__consume(this, TokenType__OpenCurly);
  while ((!Parser__token_is(this, TokenType__CloseCurly))) {
    Token* name = Parser__consume(this, TokenType__Identifier);
    Type* type = Type__new(BaseType__I32, name->span);
    Variable* var = Variable__new(name->text, type, name->span);
    Vector__push(enum_def->fields, ((void*)var));
    if ((!Parser__token_is(this, TokenType__CloseCurly))){
      Parser__consume_newline_or(this, TokenType__Comma);
    } 
  } 
  Parser__consume(this, TokenType__CloseCurly);
  return enum_def;
}

Structure* Parser__parse_struct(Parser* this) {
  bool is_union = false;
  Span start_span = Parser__token(this)->span;
  if (Parser__consume_if(this, TokenType__Union)){
    is_union = true;
  }  else {
    Parser__consume(this, TokenType__Struct);
  } 
  Token* name = Parser__consume(this, TokenType__Identifier);
  Structure* struc = Structure__new(Span__join(start_span, name->span));
  struc->name = name->text;
  if (Parser__consume_if(this, TokenType__Extern)){
    struc->is_extern = true;
    struc->extern_name = struc->name;
    if (Parser__consume_if(this, TokenType__OpenParen)){
      Token* name = Parser__consume(this, TokenType__StringLiteral);
      struc->extern_name = name->text;
      Parser__consume(this, TokenType__CloseParen);
    } 
  } 
  if (((!struc->is_extern) || Parser__token_is(this, TokenType__OpenCurly))){
    Parser__consume(this, TokenType__OpenCurly);
    while ((!Parser__token_is(this, TokenType__CloseCurly))) {
      Token* name = Parser__consume(this, TokenType__Identifier);
      Parser__consume(this, TokenType__Colon);
      Type* type = Parser__parse_type(this);
      Variable* var = Variable__new(name->text, type, Span__join(name->span, type->span));
      Vector__push(struc->fields, ((void*)var));
      if ((!Parser__token_is(this, TokenType__CloseCurly))){
        Parser__consume_newline_or(this, TokenType__Comma);
      } 
    } 
    Parser__consume(this, TokenType__CloseCurly);
  } 
  Type* type = Type__new(BaseType__Structure, name->span);
  type->name = name->text;
  struc->type = type;
  type->struct_def = struc;
  struc->is_union = is_union;
  return struc;
}

AST* Parser__parse_global_var(Parser* this) {
  Span start_span = Parser__consume(this, TokenType__Let)->span;
  AST* node = AST__new(ASTType__VarDeclaration, Parser__token(this)->span);
  Token* name = Parser__consume(this, TokenType__Identifier);
  Type* type = ((Type*)0);
  if (Parser__consume_if(this, TokenType__Colon)){
    type = Parser__parse_type(this);
  } 
  Variable* var = Variable__new(name->text, type, Span__join(start_span, Parser__token(this)->span));
  node->u.var_decl.var = var;
  if (Parser__consume_if(this, TokenType__Extern)){
    var->is_extern = true;
    if (Parser__consume_if(this, TokenType__OpenParen)){
      Token* name = Parser__consume(this, TokenType__StringLiteral);
      var->extern_name = name->text;
      Parser__consume(this, TokenType__CloseParen);
    }  else {
      var->extern_name = var->name;
    } 
    if (type == ((Type*)0)){
      error_span(name->span, "Extern variables must have a type");
    } 
  }  else {
    var->is_extern = false;
    if (Parser__consume_if(this, TokenType__Equals)){
      node->u.var_decl.init = Parser__parse_expression(this, false);
    } 
  } 
  Parser__consume_newline_or(this, TokenType__Semicolon);
  return node;
}

void Parser__include_file(Parser* this, Program* program, char* filename) {
  if (Program__is_file_included(program, filename))
  return;
  
  Program__add_included_file(program, filename);
  FILE* file = File__open(filename, "r");
  char* contents = File__slurp(file);
  Lexer lexer = Lexer__make(contents, filename);
  Vector* tokens = Lexer__lex((&lexer));
  Parser* parser = Parser__make(tokens);
  Parser__parse_into_program(parser, program);
}

void Parser__parse_use(Parser* this, Program* program) {
  Parser__consume(this, TokenType__Use);
  Token* name = Parser__consume(this, TokenType__StringLiteral);
  Parser__consume_newline_or(this, TokenType__Semicolon);
  Parser__include_file(this, program, name->text);
}

void Parser__parse_compiler_option(Parser* this, Program* program) {
  Parser__consume(this, TokenType__AtSign);
  Token* compiler = Parser__consume(this, TokenType__Identifier);
  if ((!streq(compiler->text, "compiler"))){
    error_span(compiler->span, "Expected 'compiler'");
  } 
  Token* name = Parser__consume(this, TokenType__Identifier);
  {
    char *__match_str = name->text;
    if (streq(__match_str, "c_include")) {
      Token* filename = Parser__consume(this, TokenType__StringLiteral);
      Vector__push(program->c_includes, ((void*)filename->text));
    } else if (streq(__match_str, "c_flag")) {
      Token* flag = Parser__consume(this, TokenType__StringLiteral);
      Vector__push(program->c_flags, ((void*)flag->text));
    } else if (streq(__match_str, "c_embed_header")) {
      Token* filename = Parser__consume(this, TokenType__StringLiteral);
      Vector__push(program->c_embed_headers, ((void*)filename->text));
    } else  {
      error_span(name->span, "Unknown compiler option");
    }
  }
}

void Parser__parse_into_program(Parser* this, Program* program) {
  while ((!Parser__token_is(this, TokenType__EOF))) {
    switch (Parser__token(this)->type) {
      case TokenType__Use: {
        Parser__parse_use(this, program);
      } break;
      case TokenType__AtSign: {
        Parser__parse_compiler_option(this, program);
      } break;
      case TokenType__Def: {
        Function* func = Parser__parse_function(this);
        Vector__push(program->functions, ((void*)func));
      } break;
      case TokenType__Let: {
        AST* node = Parser__parse_global_var(this);
        Vector__push(program->global_vars, ((void*)node));
      } break;
      case TokenType__Struct:
      case TokenType__Union: {
        Structure* structure = Parser__parse_struct(this);
        Vector__push(program->structures, ((void*)structure));
      } break;
      case TokenType__Enum: {
        Structure* structure = Parser__parse_enum(this);
        Vector__push(program->structures, ((void*)structure));
      } break;
      default: {
        Parser__unhandled_type(this, "parse_program");
      } break;
    }
  } 
}

Program* Parser__parse_program(Parser* this) {
  Program* program = Program__new();
  Parser__include_file(this, program, "./lib/prelude.ae");
  Program__add_included_file(program, Parser__token(this)->span.start.filename);
  Parser__parse_into_program(this, program);
  return program;
}

TypeChecker* TypeChecker__new() {
  TypeChecker* checker = ((TypeChecker*)calloc(1, sizeof(TypeChecker)));
  checker->scopes = Vector__new();
  checker->functions = Map__new();
  checker->structures = Map__new();
  checker->methods = Map__new();
  return checker;
}

void TypeChecker__push_scope(TypeChecker* this) {
  Map* scope = Map__new();
  Vector__push(this->scopes, ((void*)scope));
}

Map* TypeChecker__scope(TypeChecker* this) {
  return ((Map*)Vector__back(this->scopes));
}

void TypeChecker__pop_scope(TypeChecker* this) {
  Map* scope = ((Map*)Vector__pop(this->scopes));
  Map__free(scope);
}

void TypeChecker__push_var(TypeChecker* this, Variable* var) {
  Map* scope = TypeChecker__scope(this);
  if (Map__exists(scope, var->name)){
    error_span(var->span, "Variable is already defined in scope");
  } 
  Map__insert(TypeChecker__scope(this), var->name, ((void*)var));
}

Variable* TypeChecker__find_var(TypeChecker* this, char* name) {
  for (int i = (this->scopes->size - 1); (i >= 0); i -= 1) {
    Map* scope = ((Map*)Vector__at(this->scopes, i));
    Variable* var = ((Variable*)Map__get(scope, name));
    if ((var != ((Variable*)0))){
      return var;
    } 
  } 
  return ((Variable*)0);
}

Variable* TypeChecker__get_struct_member(TypeChecker* this, char* lhs, char* rhs) {
  Structure* struc = ((Structure*)Map__get(this->structures, lhs));
  return Structure__find_field(struc, rhs);
}

bool TypeChecker__type_is_valid(TypeChecker* this, Type* type) {
  switch (type->base) {
    case BaseType__Pointer: {
      return TypeChecker__type_is_valid(this, type->ptr);
    } break;
    case BaseType__Function: {
      for (int i = 0; (i < type->params->size); i += 1) {
        if ((!TypeChecker__type_is_valid(this, ((Type*)Vector__at(type->params, i))))){
          return false;
        } 
      } 
      return TypeChecker__type_is_valid(this, type->return_type);
    } break;
    case BaseType__Structure: {
      Structure* struc = ((Structure*)Map__get(this->structures, type->name));
      if ((struc != ((Structure*)0))){
        type->struct_def = struc;
        return true;
      } 
      return false;
    } break;
    default: {
      return true;
    } break;
  }
}

void TypeChecker__check_method_call(TypeChecker* this, Type* method_type, AST* node) {
  AST* callee = node->u.call.callee;
  if (((callee->type != ASTType__Member) && (callee->type != ASTType__ScopeLookup))){
    error_span(callee->span, "Method call is not to a member, internal compiler error");
  } 
  Map* s_methods = ((Map*)Map__get(this->methods, method_type->name));
  Function* method = ((Function*)Map__get(s_methods, callee->u.member.name));
  node->u.call.func = method;
  if (node->u.call.added_method_arg)
  return;
  
  node->u.call.added_method_arg = true;
  if ((callee->type != ASTType__Member))
  return;
  
  if (method->params->size == 0){
    error_span(callee->span, "Instance method should have `this` argument, internal error");
  } 
  Type* method_param = ((Variable*)Vector__at(method->params, 0))->type;
  Member member = callee->u.member;
  AST* first_arg = member.lhs;
  if ((member.is_pointer && (method_param->base != BaseType__Pointer))){
    first_arg = AST__new_unop(ASTType__Dereference, first_arg->span, first_arg);
  }  else   if (((!member.is_pointer) && method_param->base == BaseType__Pointer)){
    first_arg = AST__new_unop(ASTType__Address, first_arg->span, first_arg);
  } 
  
  Vector__push_front(node->u.call.args, ((void*)first_arg));
}

Type* TypeChecker__check_call(TypeChecker* this, AST* node) {
  AST* callee = node->u.call.callee;
  if (callee->type == ASTType__Identifier){
    callee->u.ident.is_function = false;
    char* name = callee->u.ident.name;
    if ((streq(name, "print") || streq(name, "println"))){
      for (int i = 0; (i < node->u.call.args->size); i += 1) {
        AST* arg = ((AST*)Vector__at(node->u.call.args, i));
        TypeChecker__check_expression(this, arg);
      } 
      return Type__new(BaseType__Void, node->span);
    } 
    if (streq(name, "exit")){
      node->returns = true;
    } 
  } 
  Type* func_type = TypeChecker__check_expression(this, callee);
  node->u.call.func = func_type->func_def;
  if (((func_type->base != BaseType__Function) && (func_type->base != BaseType__Method))){
    error_span(callee->span, "Cannot call a non-function type");
  } 
  if (func_type->base == BaseType__Method){
    TypeChecker__check_method_call(this, func_type, node);
  } 
  Vector* params = func_type->params;
  if ((params->size != node->u.call.args->size)){
    error_span(node->span, "Number of arguments does not match function signature");
  } 
  for (int i = 0; (i < params->size); i += 1) {
    Type* param = ((Type*)Vector__at(params, i));
    AST* arg = ((AST*)Vector__at(node->u.call.args, i));
    Type* arg_type = TypeChecker__check_expression(this, arg);
    if ((!Type__eq(param, arg_type))){
      error_span(arg->span, "Argument type does not match function parameter type");
    } 
  } 
  return func_type->return_type;
}

Type* TypeChecker__check_format_string(TypeChecker* this, AST* node) {
  Vector* parts = node->u.fmt_str.parts;
  Vector* exprs = node->u.fmt_str.exprs;
  if ((parts->size != (exprs->size + 1))){
    error_span(node->span, "Number of format string parts does not match number of expressions");
  } 
  int size = 0;
  for (int i = 0; (i < parts->size); i += 1) {
    size += (strlen(((char*)Vector__at(parts, i))) + 3);
  } 
  char* buf = ((char*)calloc((size + 1), 1));
  for (int i = 0; (i < exprs->size); i += 1) {
    char* part = ((char*)Vector__at(parts, i));
    AST* expr = ((AST*)Vector__at(exprs, i));
    strcat(buf, part);
    Type* expr_type = TypeChecker__check_expression(this, expr);
    switch (expr_type->base) {
      case BaseType__I32:
      case BaseType__U8: {
        strcat(buf, "%d");
      } break;
      case BaseType__Bool: {
        strcat(buf, "%s");
      } break;
      case BaseType__F32: {
        strcat(buf, "%f");
      } break;
      case BaseType__Char: {
        strcat(buf, "%c");
      } break;
      case BaseType__Pointer: {
        if (expr_type->ptr->base == BaseType__Char)
        strcat(buf, "%s");
         else 
        strcat(buf, "%p");
        
      } break;
      default: {
        error_span(expr->span, "Invalid type for format string");
      } break;
    }
  } 
  strcat(buf, ((char*)Vector__back(parts)));
  node->u.fmt_str.str = buf;
  return Type__ptr_to(BaseType__Char, node->span);
}

Type* TypeChecker__check_pointer_arith(TypeChecker* this, AST* node, Type* lhs, Type* rhs) {
  if ((node->type == ASTType__Plus || node->type == ASTType__Minus)){
    if ((lhs->base == BaseType__Pointer && rhs->base == BaseType__I32)){
      return lhs;
    } 
    if ((lhs->base == BaseType__I32 && rhs->base == BaseType__Pointer)){
      return rhs;
    } 
    if ((Type__eq(lhs, rhs) && lhs->base == BaseType__Pointer)){
      if (node->type == ASTType__Minus){
        return Type__new(BaseType__I32, node->span);
      } 
    } 
  } 
  error_span(node->span, "Invalid pointer arithmetic");
  return ((Type*)0);
}

Type* TypeChecker__check_expression(TypeChecker* this, AST* node) {
  Type* etype = ((Type*)0);
  switch (node->type) {
    case ASTType__Call: {
      etype = TypeChecker__check_call(this, node);
    } break;
    case ASTType__IntLiteral: {
      etype = Type__new(BaseType__I32, node->span);
    } break;
    case ASTType__FloatLiteral: {
      etype = Type__new(BaseType__F32, node->span);
    } break;
    case ASTType__BoolLiteral: {
      etype = Type__new(BaseType__Bool, node->span);
    } break;
    case ASTType__StringLiteral: {
      etype = Type__ptr_to(BaseType__Char, node->span);
    } break;
    case ASTType__CharLiteral: {
      etype = Type__new(BaseType__Char, node->span);
    } break;
    case ASTType__FormatStringLiteral: {
      etype = TypeChecker__check_format_string(this, node);
    } break;
    case ASTType__SizeOf: {
      if ((!TypeChecker__type_is_valid(this, node->u.size_of_type))){
        error_span(node->u.size_of_type->span, "Invalid type");
      } 
      etype = Type__new(BaseType__I32, node->span);
    } break;
    case ASTType__Identifier: {
      Identifier* ident = (&node->u.ident);
      Variable* var = TypeChecker__find_var(this, ident->name);
      Function* func = ((Function*)Map__get(this->functions, ident->name));
      if (ident->is_function){
        etype = ident->func->type;
      }  else       if ((var != ((Variable*)0))){
        ident->is_function = false;
        ident->var = var;
        etype = var->type;
      }  else       if ((func != ((Function*)0))){
        ident->is_function = true;
        ident->func = func;
        etype = func->type;
      }  else {
        error_span(node->span, "Unknown Identifier");
      } 
      
      
    } break;
    case ASTType__Plus:
    case ASTType__Minus:
    case ASTType__Multiply:
    case ASTType__Divide: {
      Type* lhs = TypeChecker__check_expression(this, node->u.binary.lhs);
      Type* rhs = TypeChecker__check_expression(this, node->u.binary.rhs);
      if ((lhs->base == BaseType__Pointer || rhs->base == BaseType__Pointer)){
        etype = TypeChecker__check_pointer_arith(this, node, lhs, rhs);
      }  else       if (((!Type__is_numeric(lhs)) || (!Type__is_numeric(rhs)))){
        error_span(node->span, "Operator requires numeric types");
      }  else       if ((!Type__eq(lhs, rhs))){
        error_span(node->span, "Operands must be be of the same type");
      }  else {
        etype = lhs;
      } 
      
      
    } break;
    case ASTType__LessThan:
    case ASTType__LessThanEquals:
    case ASTType__GreaterThan:
    case ASTType__GreaterThanEquals: {
      Type* lhs = TypeChecker__check_expression(this, node->u.binary.lhs);
      Type* rhs = TypeChecker__check_expression(this, node->u.binary.rhs);
      if (((!Type__is_numeric(lhs)) || (!Type__is_numeric(rhs)))){
        error_span(node->span, "Operator requires numeric types");
      } 
      if ((!Type__eq(lhs, rhs))){
        error_span(node->span, "Operands must be be of the same type");
      } 
      etype = Type__new(BaseType__Bool, node->span);
    } break;
    case ASTType__Equals:
    case ASTType__NotEquals: {
      Type* lhs = TypeChecker__check_expression(this, node->u.binary.lhs);
      Type* rhs = TypeChecker__check_expression(this, node->u.binary.rhs);
      if ((!Type__eq(lhs, rhs))){
        error_span(node->span, "Operands must be be of the same type");
      } 
      if (lhs->base == BaseType__Structure){
        Structure* struc = ((Structure*)Map__get(this->structures, lhs->name));
        if ((!struc->is_enum)){
          error_span(node->span, "Cannot compare structs directly");
        } 
      } 
      etype = Type__new(BaseType__Bool, node->span);
    } break;
    case ASTType__And:
    case ASTType__Or: {
      Type* lhs = TypeChecker__check_expression(this, node->u.binary.lhs);
      Type* rhs = TypeChecker__check_expression(this, node->u.binary.rhs);
      if (((!Type__eq(lhs, rhs)) || (lhs->base != BaseType__Bool))){
        error_span(node->span, "Operands must be boolean");
      } 
      etype = Type__new(BaseType__Bool, node->span);
    } break;
    case ASTType__Not: {
      Type* rhs = TypeChecker__check_expression(this, node->u.unary);
      if ((rhs->base != BaseType__Bool)){
        error_span(node->u.unary->span, "Expression must be boolean");
      } 
      etype = Type__new(BaseType__Bool, node->span);
    } break;
    case ASTType__Modulus:
    case ASTType__BitwiseOr:
    case ASTType__BitwiseAnd:
    case ASTType__BitwiseXor: {
      Type* lhs = TypeChecker__check_expression(this, node->u.binary.lhs);
      Type* rhs = TypeChecker__check_expression(this, node->u.binary.rhs);
      if (((lhs->base != BaseType__I32) || (rhs->base != BaseType__I32))){
        error_span(node->span, "Operator requires integer types");
      } 
      etype = lhs;
    } break;
    case ASTType__UnaryMinus: {
      etype = TypeChecker__check_expression(this, node->u.unary);
      if ((!Type__is_numeric(etype))){
        error_span(node->u.unary->span, "Expression must be a number");
      } 
    } break;
    case ASTType__Address: {
      etype = TypeChecker__check_expression(this, node->u.unary);
      etype = Type__new_link(BaseType__Pointer, etype, node->span);
    } break;
    case ASTType__Dereference: {
      Type* expr_type = TypeChecker__check_expression(this, node->u.unary);
      if ((expr_type->base != BaseType__Pointer)){
        error_span(node->u.unary->span, "Expression must be a pointer-type");
      } 
      etype = expr_type->ptr;
    } break;
    case ASTType__Index: {
      Type* expr_type = TypeChecker__check_expression(this, node->u.binary.lhs);
      if ((expr_type->base != BaseType__Pointer)){
        error_span(node->u.binary.lhs->span, "Expression must be a pointer-type");
      } 
      Type* index_type = TypeChecker__check_expression(this, node->u.binary.rhs);
      if ((index_type->base != BaseType__I32)){
        error_span(node->u.binary.rhs->span, "Index must be an integer");
      } 
      etype = expr_type->ptr;
    } break;
    case ASTType__PlusEquals:
    case ASTType__MinusEquals:
    case ASTType__DivideEquals:
    case ASTType__MultiplyEquals: {
      Type* lhs = TypeChecker__check_expression(this, node->u.binary.lhs);
      Type* rhs = TypeChecker__check_expression(this, node->u.binary.rhs);
      if (((!Type__is_numeric(lhs)) || (!Type__is_numeric(rhs)))){
        error_span(node->u.binary.lhs->span, "Operator requires numeric types");
      } 
      if ((!Type__eq(lhs, rhs))){
        error_span(node->span, "Operands must be be of the same type");
      } 
      etype = lhs;
    } break;
    case ASTType__Assignment: {
      Type* lhs = TypeChecker__check_expression(this, node->u.binary.lhs);
      Type* rhs = TypeChecker__check_expression(this, node->u.binary.rhs);
      if ((!Type__eq(lhs, rhs))){
        error_span(node->span, "Variable type does not match assignment type");
      } 
      etype = lhs;
    } break;
    case ASTType__ScopeLookup: {
      if ((node->u.member.lhs->type != ASTType__Identifier)){
        error_span(node->u.member.lhs->span, "Left hand side of `::` must be a struct name");
      } 
      char* struct_name = node->u.member.lhs->u.ident.name;
      Structure* struc = ((Structure*)Map__get(this->structures, struct_name));
      if (struc == ((Structure*)0)){
        error_span(node->u.member.lhs->span, "Unknown struct with this name");
      } 
      char* field_name = node->u.member.name;
      Variable* var = TypeChecker__get_struct_member(this, struct_name, field_name);
      Map* s_methods = ((Map*)Map__get(this->methods, struct_name));
      Function* method = ((Function*)Map__get(s_methods, field_name));
      if ((struc->is_enum && (var != ((Variable*)0)))){
        node->type = ASTType__EnumValue;
        node->u.enum_val.struct_def = struc;
        node->u.enum_val.name = field_name;
        etype = struc->type;
      }  else       if ((method != ((Function*)0))){
        etype = method->type;
      }  else {
        error_span(node->span, "Struct has no static method with this name");
      } 
      
    } break;
    case ASTType__Member: {
      Type* lhs_type = TypeChecker__check_expression(this, node->u.member.lhs);
      if ((!Type__is_struct_or_ptr(lhs_type))){
        error_span(node->u.member.lhs->span, "LHS of member access must be a (pointer to) struct");
      } 
      node->u.member.is_pointer = lhs_type->base == BaseType__Pointer;
      Type* struct_type = lhs_type;
      if (lhs_type->base == BaseType__Pointer){
        struct_type = lhs_type->ptr;
      } 
      char* struct_name = struct_type->name;
      char* field_name = node->u.member.name;
      Structure* struc = ((Structure*)Map__get(this->structures, struct_name));
      Variable* field = TypeChecker__get_struct_member(this, struct_name, field_name);
      Map* s_methods = ((Map*)Map__get(this->methods, struct_name));
      Function* method = ((Function*)Map__get(s_methods, field_name));
      if (((!struc->is_enum) && (field != ((Variable*)0)))){
        etype = field->type;
      }  else       if ((method != ((Function*)0))){
        if (method->is_static){
          error_span(node->span, "Member access requires a non-static method");
        } 
        etype = method->type;
      }  else {
        if (struc->is_enum){
          error_span(node->span, "Enum has no method with this name");
        }  else {
          error_span(node->span, "Struct has no member with this name");
        } 
      } 
      
    } break;
    case ASTType__Cast: {
      Type* lhs_type = TypeChecker__check_expression(this, node->u.cast.lhs);
      if ((!TypeChecker__type_is_valid(this, node->u.cast.to))){
        error_span(node->u.cast.to->span, "Type does not exist");
      } 
      etype = node->u.cast.to;
    } break;
    default: {
      printf("Unhandled type in check_expression: %s" "\n", ASTType__str(node->type));
      exit(1);
    } break;
  }
  node->etype = etype;
  return etype;
}

void TypeChecker__check_match_for_enum(TypeChecker* this, Structure* struc, AST* node) {
  Map* mapping = Map__new();
  ;
  Vector* cases = node->u.match_stmt.cases;
  bool always_returns = true;
  for (int i = 0; (i < cases->size); i += 1) {
    MatchCase* _case = ((MatchCase*)Vector__at(cases, i));
    AST* cond = _case->cond;
    char* name;
    if (cond->type == ASTType__Identifier){
      name = cond->u.ident.name;
      if (Structure__find_field(struc, name) == ((Variable*)0)){
        error_span(cond->span, "Enum has no field with this name");
      } 
      cond->type = ASTType__EnumValue;
      cond->u.enum_val.struct_def = struc;
      cond->u.enum_val.name = name;
      cond->etype = struc->type;
    }  else {
      Type* cond_type = TypeChecker__check_expression(this, cond);
      if ((!Type__eq(cond_type, struc->type))){
        error_span(cond->span, "Condition does not match expression type");
      } 
      name = cond->u.enum_val.name;
    } 
    if (Map__exists(mapping, name)){
      error_span(cond->span, "Duplicate condition name in match");
    } 
    Map__insert(mapping, name, ((void*)_case));
    if ((_case->body != ((AST*)0))){
      TypeChecker__check_statement(this, _case->body);
      always_returns = (always_returns && _case->body->returns);
    } 
  } 
  AST* defolt = node->u.match_stmt.defolt;
  if ((mapping->num_items != struc->fields->size)){
    if (defolt == ((AST*)0)){
      error_span(node->span, "Match does not cover all cases");
    } 
    TypeChecker__check_statement(this, node->u.match_stmt.defolt);
    always_returns = (always_returns && defolt->returns);
  }  else {
    if ((defolt != ((AST*)0))){
      error_span(node->u.match_stmt.defolt_span, "`else` case is not needed for this match");
    } 
  } 
  node->returns = always_returns;

/* defers */
  Map__free(mapping);
}

void TypeChecker__check_match(TypeChecker* this, AST* node) {
  AST* expr = node->u.match_stmt.expr;
  Type* expr_type = TypeChecker__check_expression(this, expr);
  Structure* struc;
  if (expr_type->base == BaseType__Structure){
    struc = ((Structure*)Map__get(this->structures, expr_type->name));
    if (struc->is_enum){
      TypeChecker__check_match_for_enum(this, struc, node);
      return;
    } 
  } 
  if ((((expr_type->base != BaseType__I32) && (expr_type->base != BaseType__Char)) && (!Type__is_string(expr_type)))){
    error_span(expr->span, "Match expression must be enum/integer/char/string");
  } 
  Vector* cases = node->u.match_stmt.cases;
  bool always_returns = true;
  for (int i = 0; (i < cases->size); i += 1) {
    MatchCase* _case = ((MatchCase*)Vector__at(cases, i));
    Type* cond_type = TypeChecker__check_expression(this, _case->cond);
    if ((!Type__eq(cond_type, expr_type))){
      error_span(_case->cond->span, "Condition does not match expression type");
    } 
    if ((((_case->cond->type != ASTType__IntLiteral) && (_case->cond->type != ASTType__CharLiteral)) && (_case->cond->type != ASTType__StringLiteral))){
      error_span(_case->cond->span, "Match condition must use only literals");
    } 
    if ((_case->body != ((AST*)0))){
      TypeChecker__check_statement(this, _case->body);
      always_returns = (always_returns && _case->body->returns);
    } 
  } 
  AST* defolt = node->u.match_stmt.defolt;
  if (defolt == ((AST*)0)){
    error_span(node->span, "`else` case is missing");
  } 
  TypeChecker__check_statement(this, defolt);
  always_returns = (always_returns && defolt->returns);
  node->returns = always_returns;
}

void TypeChecker__check_statement(TypeChecker* this, AST* node) {
  switch (node->type) {
    case ASTType__Block: {
      TypeChecker__check_block(this, node);
    } break;
    case ASTType__Defer: {
      TypeChecker__check_expression(this, node->u.unary);
    } break;
    case ASTType__Match: {
      TypeChecker__check_match(this, node);
    } break;
    case ASTType__Return: {
      if (this->cur_func == ((Function*)0)){
        error_span(node->span, "Return statement outside of function");
      } 
      if (node->u.unary == ((AST*)0)){
        if ((this->cur_func->return_type->base != BaseType__Void)){
          error_span(node->span, "Cannot have empty return in non-void function");
        } 
      }  else {
        if (this->cur_func->return_type->base == BaseType__Void){
          error_span(node->span, "Cannot return value in void function");
        } 
        Type* ret_type = TypeChecker__check_expression(this, node->u.unary);
        if ((!Type__eq(ret_type, this->cur_func->return_type))){
          error_span(node->span, "Return type does not match function return type");
        } 
      } 
      node->returns = true;
    } break;
    case ASTType__Break:
    case ASTType__Continue: {
      if ((!this->in_loop)){
        error_span(node->span, __format_string("%s statement outside of loop", ASTType__str(node->type)));
      } 
    } break;
    case ASTType__VarDeclaration: {
      VarDeclaration* var_decl = (&node->u.var_decl);
      if ((var_decl->init != ((AST*)0))){
        Type* init_type = TypeChecker__check_expression(this, var_decl->init);
        if (init_type->base == BaseType__Method){
          error_span(var_decl->init->span, "Cannot assign methods to variables");
        } 
        if (var_decl->var->type == ((Type*)0)){
          var_decl->var->type = init_type;
        }  else         if ((!Type__eq(var_decl->var->type, init_type))){
          error_span(var_decl->init->span, "Variable type does not match initializer type");
        } 
        
      }  else {
        if (var_decl->var->type == ((Type*)0)){
          error_span(var_decl->var->span, "Variable type cannot be inferred, specify explicitly");
        } 
        if ((!TypeChecker__type_is_valid(this, var_decl->var->type))){
          error_span(var_decl->var->type->span, "Invalid variable type");
        } 
      } 
      TypeChecker__push_var(this, var_decl->var);
    } break;
    case ASTType__While: {
      bool was_in_loop = this->in_loop;
      this->in_loop = true;
      Type* cond_type = TypeChecker__check_expression(this, node->u.loop.cond);
      if ((cond_type->base != BaseType__Bool)){
        error_span(node->u.loop.cond->span, "Condition must be boolean");
      } 
      TypeChecker__check_statement(this, node->u.loop.body);
      this->in_loop = was_in_loop;
    } break;
    case ASTType__For: {
      bool was_in_loop = this->in_loop;
      this->in_loop = true;
      TypeChecker__push_scope(this);
      if ((node->u.loop.init != ((AST*)0))){
        TypeChecker__check_statement(this, node->u.loop.init);
      } 
      if ((node->u.loop.init != ((AST*)0))){
        Type* cond_type = TypeChecker__check_expression(this, node->u.loop.cond);
        if ((cond_type->base != BaseType__Bool)){
          error_span(node->u.loop.cond->span, "Condition must be boolean");
        } 
      } 
      if ((node->u.loop.incr != ((AST*)0))){
        TypeChecker__check_statement(this, node->u.loop.incr);
      } 
      TypeChecker__check_statement(this, node->u.loop.body);
      TypeChecker__pop_scope(this);
      this->in_loop = was_in_loop;
    } break;
    case ASTType__If: {
      Type* cond_type = TypeChecker__check_expression(this, node->u.if_stmt.cond);
      if ((cond_type->base != BaseType__Bool)){
        error_span(node->u.if_stmt.cond->span, "Condition must be boolean");
      } 
      TypeChecker__check_statement(this, node->u.if_stmt.then);
      if ((node->u.if_stmt.els != ((AST*)0))){
        AST* else_stmt = node->u.if_stmt.els;
        TypeChecker__check_statement(this, else_stmt);
        if ((node->u.if_stmt.then->returns && else_stmt->returns)){
          node->returns = true;
        } 
      } 
    } break;
    default: {
      TypeChecker__check_expression(this, node);
    } break;
  }
}

void TypeChecker__check_block(TypeChecker* this, AST* node) {
  TypeChecker__push_scope(this);
  Vector* statements = node->u.block.statements;
  for (int i = 0; (i < statements->size); i += 1) {
    AST* statement = ((AST*)Vector__at(statements, i));
    TypeChecker__check_statement(this, statement);
    if (statement->returns){
      node->returns = true;
    } 
  } 
  TypeChecker__pop_scope(this);
}

void TypeChecker__check_function(TypeChecker* this, Function* func) {
  Function* prev_func = this->cur_func;
  this->cur_func = func;
  TypeChecker__push_scope(this);
  for (int i = 0; (i < func->params->size); i += 1) {
    Variable* var = ((Variable*)Vector__at(func->params, i));
    TypeChecker__push_var(this, var);
  } 
  if ((func->body != ((AST*)0))){
    TypeChecker__check_block(this, func->body);
    if (((!func->body->returns) && (func->return_type->base != BaseType__Void))){
      if ((!streq(func->name, "main"))){
        error_span(func->span, __format_string("function %s does not always return", func->name));
      } 
    } 
  } 
  TypeChecker__pop_scope(this);
  this->cur_func = prev_func;
}

void TypeChecker__check_all_functions(TypeChecker* this, Program* program) {
  for (int i = 0; (i < program->functions->size); i += 1) {
    Function* func = ((Function*)Vector__at(program->functions, i));
    char* name = func->name;
    char* struct_name = func->method_struct_name;
    Type* func_type = ((Type*)0);
    if (func->is_method){
      if ((!Map__exists(this->structures, struct_name))){
        error_span(func->span, "Type for method does not exist");
      } 
      Map* s_methods = ((Map*)Map__get(this->methods, struct_name));
      if (Map__exists(s_methods, name)){
        error_span(func->span, "Method is already defined for this type");
      } 
      Variable* var = TypeChecker__get_struct_member(this, struct_name, name);
      if ((var != ((Variable*)0))){
        error_span(func->span, "Type already has a field with this name");
      } 
      func_type = Type__new(BaseType__Method, func->span);
      func_type->name = struct_name;
    }  else {
      func_type = Type__new(BaseType__Function, func->span);
      if (Map__exists(this->functions, name)){
        error_span(func->span, "Function is already defined");
      } 
    } 
    func_type->func_def = func;
    func_type->params = Vector__new();
    for (int j = 0; (j < func->params->size); j += 1) {
      Variable* param = ((Variable*)Vector__at(func->params, j));
      if ((!TypeChecker__type_is_valid(this, param->type))){
        error_span(param->type->span, "Invalid parameter type");
      } 
      Vector__push(func_type->params, ((void*)param->type));
    } 
    if ((!TypeChecker__type_is_valid(this, func->return_type))){
      error_span(func->return_type->span, "Invalid return type");
    } 
    func_type->return_type = func->return_type;
    func->type = func_type;
    if (func->is_method){
      Map* s_methods = ((Map*)Map__get(this->methods, struct_name));
      Map__insert(s_methods, name, ((void*)func));
    }  else {
      Map__insert(this->functions, name, ((void*)func));
    } 
  } 
  for (int i = 0; (i < program->functions->size); i += 1) {
    TypeChecker__check_function(this, ((Function*)Vector__at(program->functions, i)));
  } 
}

void TypeChecker__dfs_structs(TypeChecker* this, Structure* struc, Vector* results, Map* done) {
  Map__insert(done, struc->name, ((void*)struc));
  for (int i = 0; (i < struc->fields->size); i += 1) {
    Variable* field = ((Variable*)Vector__at(struc->fields, i));
    if ((!TypeChecker__type_is_valid(this, field->type))){
      error_span(field->type->span, "Type of field is undefined");
    } 
    if (((!struc->is_extern) && field->type->base == BaseType__Structure)){
      char* neib_name = field->type->name;
      Structure* neib_struc = ((Structure*)Map__get(this->structures, neib_name));
      if ((!Map__exists(done, neib_name))){
        TypeChecker__dfs_structs(this, neib_struc, results, done);
      } 
    } 
  } 
  Vector__push(results, ((void*)struc));
}

void TypeChecker__check_all_structs(TypeChecker* this, Program* program) {
  for (int i = 0; (i < program->structures->size); i += 1) {
    Structure* struc = ((Structure*)Vector__at(program->structures, i));
    char* name = struc->name;
    if (Map__exists(this->structures, name)){
      error_span(struc->span, "Struct has already been defined");
    } 
    Map__insert(this->structures, name, ((void*)struc));
    Map__insert(this->methods, name, ((void*)Map__new()));
  } 
  Map* done = Map__new();
  Vector* results = Vector__new();
  for (int i = 0; (i < program->structures->size); i += 1) {
    Structure* struc = ((Structure*)Vector__at(program->structures, i));
    if ((!Map__exists(done, struc->name))){
      TypeChecker__dfs_structs(this, struc, results, done);
    } 
  } 
  Map__free(done);
  Vector__free(program->structures);
  program->structures = results;
}

void TypeChecker__check_program(TypeChecker* this, Program* program) {
  TypeChecker__check_all_structs(this, program);
  TypeChecker__push_scope(this);
  for (int i = 0; (i < program->global_vars->size); i += 1) {
    AST* var = ((AST*)Vector__at(program->global_vars, i));
    TypeChecker__check_statement(this, var);
  } 
  TypeChecker__check_all_functions(this, program);
  TypeChecker__pop_scope(this);
}

CodeGenerator CodeGenerator__make(char* filename) {
  CodeGenerator gen;
  gen.out = File__open(filename, "w");
  gen.scopes = Vector__new();
  return gen;
}

void CodeGenerator__indent(CodeGenerator* this, int num) {
  for (int i = 0; (i < num); i += 1) {
    File__puts(this->out, "  ");
  } 
}

void CodeGenerator__push_scope(CodeGenerator* this) {
  Vector__push(this->scopes, ((void*)Vector__new()));
}

Vector* CodeGenerator__scope(CodeGenerator* this) {
  return ((Vector*)Vector__back(this->scopes));
}

void CodeGenerator__pop_scope(CodeGenerator* this) {
  Vector* scope = ((Vector*)Vector__pop(this->scopes));
  Vector__free(scope);
}

void CodeGenerator__gen_control_body(CodeGenerator* this, AST* node, int indent) {
  if (node->type == ASTType__Block){
    CodeGenerator__gen_block(this, node, indent);
    File__puts(this->out, " ");
  }  else {
    if ((node->type != ASTType__If)){
      File__puts(this->out, "\n");
    } 
    CodeGenerator__gen_statement(this, node, indent);
    CodeGenerator__indent(this, indent);
  } 
}

void CodeGenerator__gen_enum_value(CodeGenerator* this, char* enum_name, char* value_name) {
  File__puts(this->out, __format_string("%s__%s", enum_name, value_name));
}

void CodeGenerator__gen_enum(CodeGenerator* this, Structure* struc) {
  if ((!struc->is_extern)){
    File__puts(this->out, __format_string("enum %s", struc->name));
    File__puts(this->out, " {\n");
    for (int i = 0; (i < struc->fields->size); i += 1) {
      Variable* field = ((Variable*)Vector__at(struc->fields, i));
      CodeGenerator__indent(this, 1);
      CodeGenerator__gen_enum_value(this, struc->name, field->name);
      File__puts(this->out, ",\n");
    } 
    File__puts(this->out, "};\n\n");
  } 
}

void CodeGenerator__gen_struct(CodeGenerator* this, Structure* struc) {
  if ((!struc->is_extern)){
    char* name = struc->type->name;
    if (struc->is_union){
      File__puts(this->out, "union ");
    }  else {
      File__puts(this->out, "struct ");
    } 
    File__puts(this->out, name);
    File__puts(this->out, " {\n");
    for (int i = 0; (i < struc->fields->size); i += 1) {
      Variable* field = ((Variable*)Vector__at(struc->fields, i));
      CodeGenerator__indent(this, 1);
      CodeGenerator__gen_type_and_name(this, field->type, field->name);
      File__puts(this->out, ";\n");
    } 
    File__puts(this->out, "};\n\n");
  } 
}

char* CodeGenerator__get_op(ASTType type) {
  switch (type) {
    case ASTType__Address: {
      return "&";
    } break;
    case ASTType__And: {
      return " && ";
    } break;
    case ASTType__Assignment: {
      return " = ";
    } break;
    case ASTType__BitwiseAnd: {
      return " & ";
    } break;
    case ASTType__BitwiseOr: {
      return " | ";
    } break;
    case ASTType__BitwiseXor: {
      return " ^ ";
    } break;
    case ASTType__Dereference: {
      return "*";
    } break;
    case ASTType__Divide: {
      return " / ";
    } break;
    case ASTType__DivideEquals: {
      return " /= ";
    } break;
    case ASTType__Equals: {
      return " == ";
    } break;
    case ASTType__GreaterThan: {
      return " > ";
    } break;
    case ASTType__GreaterThanEquals: {
      return " >= ";
    } break;
    case ASTType__LessThan: {
      return " < ";
    } break;
    case ASTType__LessThanEquals: {
      return " <= ";
    } break;
    case ASTType__Minus: {
      return " - ";
    } break;
    case ASTType__MinusEquals: {
      return " -= ";
    } break;
    case ASTType__Modulus: {
      return " % ";
    } break;
    case ASTType__Multiply: {
      return " * ";
    } break;
    case ASTType__MultiplyEquals: {
      return " *= ";
    } break;
    case ASTType__Not: {
      return "!";
    } break;
    case ASTType__NotEquals: {
      return " != ";
    } break;
    case ASTType__Or: {
      return " || ";
    } break;
    case ASTType__Plus: {
      return " + ";
    } break;
    case ASTType__PlusEquals: {
      return " += ";
    } break;
    case ASTType__UnaryMinus: {
      return "-";
    } break;
    default: {
      printf("Unknown op type in get_op: %s" "\n", ASTType__str(type));
      exit(1);
    } break;
  }
}

void CodeGenerator__gen_type(CodeGenerator* this, Type* type) {
  switch (type->base) {
    case BaseType__Void: {
      File__puts(this->out, "void");
    } break;
    case BaseType__Char: {
      File__puts(this->out, "char");
    } break;
    case BaseType__I32: {
      File__puts(this->out, "int");
    } break;
    case BaseType__F32: {
      File__puts(this->out, "float");
    } break;
    case BaseType__Bool: {
      File__puts(this->out, "bool");
    } break;
    case BaseType__U8: {
      File__puts(this->out, "unsigned char");
    } break;
    case BaseType__Pointer: {
      CodeGenerator__gen_type(this, type->ptr);
      File__puts(this->out, "*");
    } break;
    case BaseType__Structure: {
      if (type->struct_def->is_extern){
        File__puts(this->out, type->struct_def->extern_name);
      }  else {
        File__puts(this->out, type->struct_def->name);
      } 
    } break;
    default: {
      printf("Unknown type in gen_type: %s" "\n", Type__str(type));
      exit(1);
    } break;
  }
}

void CodeGenerator__gen_expression(CodeGenerator* this, AST* node) {
  switch (node->type) {
    case ASTType__IntLiteral: {
      File__puts(this->out, node->u.num_literal);
    } break;
    case ASTType__FloatLiteral: {
      File__puts(this->out, node->u.num_literal);
    } break;
    case ASTType__StringLiteral: {
      File__puts(this->out, __format_string("\"%s\"", node->u.string_literal));
    } break;
    case ASTType__CharLiteral: {
      File__puts(this->out, __format_string("'%s'", node->u.char_literal));
    } break;
    case ASTType__BoolLiteral: {
      if (node->u.bool_literal){
        File__puts(this->out, "true");
      }  else {
        File__puts(this->out, "false");
      } 
    } break;
    case ASTType__Identifier: {
      Identifier ident = node->u.ident;
      if (ident.is_function){
        CodeGenerator__gen_function_name(this, ident.func);
      }  else       if (ident.var->is_extern){
        File__puts(this->out, ident.var->extern_name);
      }  else {
        File__puts(this->out, ident.var->name);
      } 
      
    } break;
    case ASTType__Call: {
      bool newline_after_first = false;
      if (AST__callee_is(node, "print")){
        File__puts(this->out, "printf");
      }  else       if (AST__callee_is(node, "println")){
        File__puts(this->out, "printf");
        newline_after_first = true;
      }  else       if (node->u.call.func == ((Function*)0)){
        CodeGenerator__gen_expression(this, node->u.call.callee);
      }  else {
        CodeGenerator__gen_function_name(this, node->u.call.func);
      } 
      
      
      File__puts(this->out, "(");
      Vector* args = node->u.call.args;
      for (int i = 0; (i < args->size); i += 1) {
        if ((i > 0)){
          File__puts(this->out, ", ");
        } 
        CodeGenerator__gen_expression(this, ((AST*)Vector__at(args, i)));
        if ((i == 0 && newline_after_first)){
          File__puts(this->out, " \"\\n\"");
        } 
      } 
      File__puts(this->out, ")");
    } break;
    case ASTType__And:
    case ASTType__BitwiseAnd:
    case ASTType__BitwiseOr:
    case ASTType__BitwiseXor:
    case ASTType__Divide:
    case ASTType__GreaterThan:
    case ASTType__GreaterThanEquals:
    case ASTType__LessThan:
    case ASTType__LessThanEquals:
    case ASTType__Minus:
    case ASTType__Modulus:
    case ASTType__Multiply:
    case ASTType__NotEquals:
    case ASTType__Or:
    case ASTType__Plus: {
      File__puts(this->out, "(");
      CodeGenerator__gen_expression(this, node->u.binary.lhs);
      File__puts(this->out, CodeGenerator__get_op(node->type));
      CodeGenerator__gen_expression(this, node->u.binary.rhs);
      File__puts(this->out, ")");
    } break;
    case ASTType__Address:
    case ASTType__Dereference:
    case ASTType__Not:
    case ASTType__UnaryMinus: {
      File__puts(this->out, "(");
      File__puts(this->out, CodeGenerator__get_op(node->type));
      CodeGenerator__gen_expression(this, node->u.unary);
      File__puts(this->out, ")");
    } break;
    case ASTType__Index: {
      CodeGenerator__gen_expression(this, node->u.binary.lhs);
      File__puts(this->out, "[");
      CodeGenerator__gen_expression(this, node->u.binary.rhs);
      File__puts(this->out, "]");
    } break;
    case ASTType__Member: {
      CodeGenerator__gen_expression(this, node->u.member.lhs);
      if (node->u.member.is_pointer){
        File__puts(this->out, "->");
      }  else {
        File__puts(this->out, ".");
      } 
      File__puts(this->out, node->u.member.name);
    } break;
    case ASTType__EnumValue: {
      EnumValue enum_value = node->u.enum_val;
      CodeGenerator__gen_enum_value(this, enum_value.struct_def->name, enum_value.name);
    } break;
    case ASTType__Cast: {
      File__puts(this->out, "((");
      CodeGenerator__gen_type(this, node->u.cast.to);
      File__puts(this->out, ")");
      CodeGenerator__gen_expression(this, node->u.cast.lhs);
      File__puts(this->out, ")");
    } break;
    case ASTType__FormatStringLiteral: {
      File__puts(this->out, "__format_string(\"");
      File__puts(this->out, node->u.fmt_str.str);
      File__puts(this->out, "\"");
      Vector* exprs = node->u.fmt_str.exprs;
      for (int i = 0; (i < exprs->size); i += 1) {
        AST* expr = ((AST*)Vector__at(exprs, i));
        File__puts(this->out, ", ");
        CodeGenerator__gen_expression(this, expr);
      } 
      File__puts(this->out, ")");
    } break;
    case ASTType__Defer: {
      Vector__push(CodeGenerator__scope(this), ((void*)node->u.unary));
    } break;
    case ASTType__SizeOf: {
      File__puts(this->out, "sizeof(");
      CodeGenerator__gen_type(this, node->u.size_of_type);
      File__puts(this->out, ")");
    } break;
    case ASTType__Equals:
    case ASTType__Assignment:
    case ASTType__PlusEquals:
    case ASTType__MinusEquals:
    case ASTType__DivideEquals:
    case ASTType__MultiplyEquals: {
      CodeGenerator__gen_expression(this, node->u.binary.lhs);
      File__puts(this->out, CodeGenerator__get_op(node->type));
      CodeGenerator__gen_expression(this, node->u.binary.rhs);
    } break;
    default: {
      printf("unknown type in gen_expression: %s" "\n", ASTType__str(node->type));
      exit(1);
    } break;
  }
}

void CodeGenerator__gen_var_decl(CodeGenerator* this, AST* node) {
  Variable* var = node->u.var_decl.var;
  if (var->is_extern)
  return;
  
  CodeGenerator__gen_type_and_name(this, var->type, var->name);
  if ((node->u.var_decl.init != ((AST*)0))){
    File__puts(this->out, " = ");
    CodeGenerator__gen_expression(this, node->u.var_decl.init);
  } 
}

void CodeGenerator__gen_match_string(CodeGenerator* this, AST* node, int indent) {
  Match stmt = node->u.match_stmt;
  CodeGenerator__indent(this, indent);
  File__puts(this->out, "{\n");
  CodeGenerator__indent(this, (indent + 1));
  File__puts(this->out, "char *__match_str = ");
  CodeGenerator__gen_expression(this, stmt.expr);
  File__puts(this->out, ";\n");
  Vector* cases = stmt.cases;
  CodeGenerator__indent(this, (indent + 1));
  File__puts(this->out, "if (");
  for (int i = 0; (i < cases->size); i += 1) {
    MatchCase* _case = ((MatchCase*)Vector__at(cases, i));
    File__puts(this->out, "streq(__match_str, ");
    CodeGenerator__gen_expression(this, _case->cond);
    File__puts(this->out, ")");
    if ((_case->body != ((AST*)0))){
      File__puts(this->out, ")");
      CodeGenerator__gen_match_case_body(this, _case->body, indent);
      File__puts(this->out, " else ");
      if ((i != (cases->size - 1))){
        File__puts(this->out, "if (");
      } 
    }  else {
      File__puts(this->out, " || ");
    } 
  } 
  if ((stmt.defolt != ((AST*)0))){
    CodeGenerator__gen_match_case_body(this, stmt.defolt, indent);
  } 
  File__puts(this->out, "\n");
  CodeGenerator__indent(this, indent);
  File__puts(this->out, "}\n");
}

void CodeGenerator__gen_match_case_body(CodeGenerator* this, AST* node, int indent) {
  if (node->type == ASTType__Block){
    File__puts(this->out, " ");
    CodeGenerator__gen_block(this, node, (indent + 1));
  }  else {
    File__puts(this->out, " {\n");
    CodeGenerator__gen_statement(this, node, (indent + 2));
    CodeGenerator__indent(this, (indent + 1));
    File__puts(this->out, "}");
  } 
}

void CodeGenerator__gen_match(CodeGenerator* this, AST* node, int indent) {
  Match stmt = node->u.match_stmt;
  if (Type__is_string(stmt.expr->etype)){
    CodeGenerator__gen_match_string(this, node, indent);
    return;
  } 
  CodeGenerator__indent(this, indent);
  File__puts(this->out, "switch (");
  CodeGenerator__gen_expression(this, stmt.expr);
  File__puts(this->out, ") {\n");
  Vector* cases = stmt.cases;
  for (int i = 0; (i < cases->size); i += 1) {
    MatchCase* _case = ((MatchCase*)Vector__at(cases, i));
    CodeGenerator__indent(this, (indent + 1));
    File__puts(this->out, "case ");
    CodeGenerator__gen_expression(this, _case->cond);
    File__puts(this->out, ":");
    if ((_case->body != ((AST*)0))){
      CodeGenerator__gen_match_case_body(this, _case->body, indent);
      File__puts(this->out, " break;\n");
    }  else {
      File__puts(this->out, "\n");
    } 
  } 
  if ((stmt.defolt != ((AST*)0))){
    CodeGenerator__indent(this, (indent + 1));
    File__puts(this->out, "default:");
    CodeGenerator__gen_match_case_body(this, stmt.defolt, indent);
    File__puts(this->out, " break;\n");
  } 
  CodeGenerator__indent(this, indent);
  File__puts(this->out, "}\n");
}

void CodeGenerator__gen_statement(CodeGenerator* this, AST* node, int indent) {
  if (node->type == ASTType__Return){
    CodeGenerator__indent(this, indent);
    File__puts(this->out, "return");
    if ((node->u.unary != ((AST*)0))){
      File__puts(this->out, " ");
      CodeGenerator__gen_expression(this, node->u.unary);
    } 
    File__puts(this->out, ";\n");
  }  else   if (node->type == ASTType__Match){
    CodeGenerator__gen_match(this, node, indent);
  }  else   if (node->type == ASTType__Break){
    CodeGenerator__indent(this, indent);
    File__puts(this->out, "break;\n");
  }  else   if (node->type == ASTType__Continue){
    CodeGenerator__indent(this, indent);
    File__puts(this->out, "continue;\n");
  }  else   if (node->type == ASTType__VarDeclaration){
    CodeGenerator__indent(this, indent);
    CodeGenerator__gen_var_decl(this, node);
    File__puts(this->out, ";\n");
  }  else   if (node->type == ASTType__If){
    CodeGenerator__indent(this, indent);
    File__puts(this->out, "if (");
    CodeGenerator__gen_expression(this, node->u.if_stmt.cond);
    File__puts(this->out, ")");
    CodeGenerator__gen_control_body(this, node->u.if_stmt.then, indent);
    if ((node->u.if_stmt.els != ((AST*)0))){
      File__puts(this->out, " else ");
      CodeGenerator__gen_control_body(this, node->u.if_stmt.els, indent);
    } 
    File__puts(this->out, "\n");
  }  else   if (node->type == ASTType__While){
    CodeGenerator__indent(this, indent);
    File__puts(this->out, "while (");
    CodeGenerator__gen_expression(this, node->u.loop.cond);
    File__puts(this->out, ") ");
    CodeGenerator__gen_control_body(this, node->u.loop.body, indent);
    File__puts(this->out, "\n");
  }  else   if (node->type == ASTType__For){
    CodeGenerator__indent(this, indent);
    File__puts(this->out, "for (");
    if ((node->u.loop.init != ((AST*)0))){
      if (node->u.loop.init->type == ASTType__VarDeclaration){
        CodeGenerator__gen_var_decl(this, node->u.loop.init);
      }  else {
        CodeGenerator__gen_expression(this, node->u.loop.init);
      } 
    } 
    File__puts(this->out, "; ");
    if ((node->u.loop.cond != ((AST*)0))){
      CodeGenerator__gen_expression(this, node->u.loop.cond);
    } 
    File__puts(this->out, "; ");
    if ((node->u.loop.incr != ((AST*)0))){
      CodeGenerator__gen_expression(this, node->u.loop.incr);
    } 
    File__puts(this->out, ") ");
    CodeGenerator__gen_control_body(this, node->u.loop.body, indent);
    File__puts(this->out, "\n");
  }  else   if (node->type == ASTType__Block){
    CodeGenerator__indent(this, indent);
    CodeGenerator__gen_block(this, node, indent);
    File__puts(this->out, "\n");
  }  else {
    CodeGenerator__indent(this, indent);
    CodeGenerator__gen_expression(this, node);
    File__puts(this->out, ";\n");
  } 
  
  
  
  
  
  
  
  
}

void CodeGenerator__gen_block(CodeGenerator* this, AST* node, int indent) {
  CodeGenerator__push_scope(this);
  File__puts(this->out, "{\n");
  Vector* statements = node->u.block.statements;
  for (int i = 0; (i < statements->size); i += 1) {
    AST* statement = ((AST*)Vector__at(statements, i));
    CodeGenerator__gen_statement(this, statement, (indent + 1));
  } 
  Vector* defers = CodeGenerator__scope(this);
  if ((defers->size > 0)){
    File__puts(this->out, "\n");
    CodeGenerator__indent(this, indent);
    File__puts(this->out, "/* defers */\n");
    for (int i = (defers->size - 1); (i >= 0); i -= 1) {
      AST* node = ((AST*)Vector__at(defers, i));
      CodeGenerator__gen_statement(this, node, (indent + 1));
    } 
  } 
  CodeGenerator__indent(this, indent);
  File__puts(this->out, "}");
  CodeGenerator__pop_scope(this);
}

void CodeGenerator__gen_struct_decls(CodeGenerator* this, Program* program) {
  File__puts(this->out, "/* struct declarations */\n");
  for (int i = 0; (i < program->structures->size); i += 1) {
    Structure* struc = ((Structure*)Vector__at(program->structures, i));
    if (struc->is_extern)
    continue;
    
    char* name = struc->name;
    if (struc->is_enum){
      File__puts(this->out, "typedef enum ");
    }  else     if (struc->is_union){
      File__puts(this->out, "typedef union ");
    }  else {
      File__puts(this->out, "typedef struct ");
    } 
    
    File__puts(this->out, __format_string("%s %s;\n", name, name));
  } 
  File__puts(this->out, "\n");
}

void CodeGenerator__gen_type_and_name(CodeGenerator* this, Type* type, char* name) {
  if (type->base == BaseType__Function){
    CodeGenerator__gen_type(this, type->return_type);
    File__puts(this->out, __format_string("(*%s)(", name));
    for (int i = 0; (i < type->params->size); i += 1) {
      if ((i > 0)){
        File__puts(this->out, ", ");
      } 
      CodeGenerator__gen_type(this, ((Type*)Vector__at(type->params, i)));
    } 
    File__puts(this->out, ")");
  }  else {
    CodeGenerator__gen_type(this, type);
    File__puts(this->out, __format_string(" %s", name));
  } 
}

void CodeGenerator__gen_function_name(CodeGenerator* this, Function* func) {
  if (func->is_extern){
    File__puts(this->out, func->extern_name);
  }  else   if (func->is_method){
    File__puts(this->out, __format_string("%s__%s", func->method_struct_name, func->name));
  }  else {
    File__puts(this->out, func->name);
  } 
  
}

void CodeGenerator__gen_function_decls(CodeGenerator* this, Program* program) {
  File__puts(this->out, "/* function declarations */\n");
  for (int i = 0; (i < program->functions->size); i += 1) {
    Function* func = ((Function*)Vector__at(program->functions, i));
    if ((!func->is_extern)){
      CodeGenerator__gen_type(this, func->return_type);
      File__puts(this->out, " ");
      CodeGenerator__gen_function_name(this, func);
      File__puts(this->out, "(");
      for (int i = 0; (i < func->params->size); i += 1) {
        Variable* param = ((Variable*)Vector__at(func->params, i));
        if ((i > 0)){
          File__puts(this->out, ", ");
        } 
        CodeGenerator__gen_type_and_name(this, param->type, param->name);
      } 
      File__puts(this->out, ");\n");
    } 
  } 
  File__puts(this->out, "\n");
}

void CodeGenerator__gen_function(CodeGenerator* this, Function* func) {
  if ((!func->is_extern)){
    CodeGenerator__gen_type(this, func->return_type);
    File__puts(this->out, " ");
    CodeGenerator__gen_function_name(this, func);
    File__puts(this->out, "(");
    for (int i = 0; (i < func->params->size); i += 1) {
      if ((i > 0)){
        File__puts(this->out, ", ");
      } 
      Variable* var = ((Variable*)Vector__at(func->params, i));
      CodeGenerator__gen_type_and_name(this, var->type, var->name);
    } 
    File__puts(this->out, ") ");
    CodeGenerator__gen_block(this, func->body, 0);
    File__puts(this->out, "\n\n");
  } 
}

void CodeGenerator__gen_global_vars(CodeGenerator* this, Program* program) {
  File__puts(this->out, "/* global variables */\n");
  for (int i = 0; (i < program->global_vars->size); i += 1) {
    AST* node = ((AST*)Vector__at(program->global_vars, i));
    if ((!node->u.var_decl.var->is_extern)){
      CodeGenerator__gen_statement(this, node, 0);
    } 
  } 
  File__puts(this->out, "\n");
}

void CodeGenerator__gen_embed_headers(CodeGenerator* this, Program* program) {
  if ((!Vector__empty(program->c_embed_headers))){
    for (int i = 0; (i < program->c_embed_headers->size); i += 1) {
      char* filename = ((char*)Vector__at(program->c_embed_headers, i));
      File__puts(this->out, __format_string("/***************** embed '%s' *****************/\n", filename));
      FILE* file = File__open(filename, "r");
      ;
      char* contents = File__slurp(file);
      ;
      File__puts(this->out, contents);
      File__puts(this->out, "\n\n");

    /* defers */
      free(((void*)contents));
      fclose(file);
    } 
  } 
}

void CodeGenerator__gen_program(CodeGenerator* this, Program* program) {
  for (int i = 0; (i < program->c_includes->size); i += 1) {
    char* include = ((char*)Vector__at(program->c_includes, i));
    File__puts(this->out, __format_string("#include \"%s\"\n", include));
  } 
  File__puts(this->out, "\n");
  CodeGenerator__gen_embed_headers(this, program);
  CodeGenerator__gen_struct_decls(this, program);
  for (int i = 0; (i < program->structures->size); i += 1) {
    Structure* struc = ((Structure*)Vector__at(program->structures, i));
    if (struc->is_enum){
      CodeGenerator__gen_enum(this, struc);
    }  else {
      CodeGenerator__gen_struct(this, struc);
    } 
  } 
  CodeGenerator__gen_function_decls(this, program);
  CodeGenerator__gen_global_vars(this, program);
  for (int i = 0; (i < program->functions->size); i += 1) {
    Function* func = ((Function*)Vector__at(program->functions, i));
    CodeGenerator__gen_function(this, func);
  } 
  fclose(this->out);
}

void usage(int code) {
  printf("--------------------------------------------------------\n");
  printf("Usage: ./aecor [options] <file>\n");
  printf("Options:\n");
  printf("    -o path   Output executable (default: ./build/out)\n");
  printf("    -c path   Output C code (default: {out}.c)\n");
  printf("    -s        Silent mode (no debug output)\n");
  printf("    -n        Don't compile C code (default: false)\n");
  printf("--------------------------------------------------------\n");
  exit(code);
}

int main(int argc, char** argv) {
  char* exec_path = "./build/out";
  char* c_path = ((char*)0);
  char* filename = ((char*)0);
  bool compile_c = true;
  bool silent = false;
  for (int i = 1; (i < argc); i += 1) {
    if (streq(argv[i], "-o")){
      i += 1;
      exec_path = argv[i];
    }  else     if (streq(argv[i], "-h")){
      usage(0);
    }  else     if (streq(argv[i], "-s")){
      silent = true;
    }  else     if (streq(argv[i], "-n")){
      compile_c = false;
    }  else     if (streq(argv[i], "-c")){
      i += 1;
      c_path = argv[i];
    }  else     if (argv[i][0] == '-'){
      printf("Unknown option: %s" "\n", argv[i]);
      usage(1);
    }  else     if (filename == ((char*)0)){
      filename = argv[i];
    }  else {
      printf("Unknown option/argument: '%s'" "\n", argv[i]);
      usage(1);
    } 
    
    
    
    
    
    
  } 
  if (filename == ((char*)0)){
    printf("No file specified" "\n");
    usage(1);
  } 
  if (c_path == ((char*)0)){
    c_path = __format_string("%s.c", exec_path);
  } 
  FILE* file = File__open(filename, "r");
  char* contents = File__slurp(file);
  Lexer lexer = Lexer__make(contents, filename);
  Vector* tokens = Lexer__lex((&lexer));
  Parser* parser = Parser__make(tokens);
  Program* program = Parser__parse_program(parser);
  TypeChecker* checker = TypeChecker__new();
  TypeChecker__check_program(checker, program);
  CodeGenerator generator = CodeGenerator__make(c_path);
  CodeGenerator__gen_program((&generator), program);
  if ((!compile_c)){
    return 0;
  } 
  char* cmdbuf = ((char*)calloc(1, 1024));
  strcat(cmdbuf, __format_string("gcc -o %s %s", exec_path, c_path));
  for (int i = 0; (i < program->c_flags->size); i += 1) {
    char* flag = ((char*)Vector__at(program->c_flags, i));
    strcat(cmdbuf, " ");
    strcat(cmdbuf, flag);
  } 
  if ((!silent)){
    printf("[+] %s" "\n", cmdbuf);
  } 
  int code = system(cmdbuf);
  if ((code != 0)){
    printf("[-] Compilation failed" "\n");
    exit(code);
  } 
}

