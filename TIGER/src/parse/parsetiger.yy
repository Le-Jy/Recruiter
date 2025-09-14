                                                                // -*- C++ -*-
%require "3.8"
%language "c++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.namespace {parse}
%define api.parser.class {parser}
%define api.value.type variant
%define api.token.constructor

// We use a GLR parser because it is able to handle Shift-Reduce and
// Reduce-Reduce conflicts by forking and testing each way at runtime. GLR
// permits, by allowing few conflicts, more readable and maintainable grammars.
%glr-parser
%skeleton "glr2.cc"

// In TC, we expect the GLR to resolve one Shift-Reduce and zero Reduce-Reduce
// conflict at runtime. Use %expect and %expect-rr to tell Bison about it.
  // COMPLETED
%expect 1
%expect-rr 0

%define parse.error verbose
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define api.filename.type {const std::string}
%locations

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>

  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

// The parsing context.
%param { ::parse::TigerDriver& td }
%parse-param { ::parse::Lexer& lexer }

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"


/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/chunk.hh>
# include <ast/chunk-list.hh>
}

  // FIXME: Some code was deleted here (Printers and destructors).
%destructor {delete $$;} <ast::Exp*> <ast::TypeChunk*> <ast::TypeDec*> <ast::NameTy*> <ast::Ty*> <ast::Field*> <ast::fields_type*> <ast::ChunkList*> <ast::MethodChunk*> <ast::VarChunk*> <ast::exps_type*> <ast::fieldinits_type*> <ast::FunctionChunk*> <ast::FunctionDec*> <ast::VarDec*> <ast::Var*>


/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>
# include <parse/tiger-factory.hh>

  namespace
  {

    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerDriver& td, unsigned key)
    {
      parse::Tweast* input = td.input_;
      return input->template take<T>(key);
    }

  }
}

%code
{
  #include <parse/scantiger.hh>  // header file generated with reflex --header-file
  #undef yylex
  #define yylex lexer.lex  // Within bison's parse() we should invoke lexer.lex(), not the global lex()
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       CAST         "_cast"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       MINUS        "-"
       METHOD       "method"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"

%type <ast::Exp*>             exp
%type <ast::ChunkList*>       chunks

%type <ast::TypeChunk*>       tychunk
%type <ast::TypeDec*>         tydec
%type <ast::NameTy*>          typeid
%type <ast::Ty*>              ty

%type <ast::Field*>           tyfield
%type <ast::fields_type*>     tyfields tyfields.1
  // FIXME: Some code was deleted here (More %types).
%type <ast::exps_type*>       exps
%type <ast::exps_type*>       exps.1
%type <ast::fieldinits_type*> exp.1
%type <ast::fieldinits_type*> exp.1.1
%type <ast::exps_type*>       exp.2
%type <ast::exps_type*>       exp.2.1

%type <ast::VarChunk*>        varchunk
%type <ast::FunctionChunk*>   funchunk
%type <ast::FunctionDec*>     funcdec
%type <ast::NameTy*>          funcdec.1
%type <ast::VarChunk*>        funcfields
%type <ast::VarChunk*>        funcfields.1
%type <ast::VarDec*>          funcfield
%type <ast::VarDec*>          vardec
%type <ast::NameTy*>          vardec.1
%type <ast::Var*>             lvalue

%type <ast::ChunkList*>       classfields
%type <ast::VarChunk*>        classfield
%type <ast::MethodChunk*>     classfield.1

  // COMPLETED

%precedence THEN
%precedence ELSE DO OF ASSIGN

%left OR
%left AND
%nonassoc GE LE EQ NE LT GT
%left PLUS MINUS
%left TIMES DIVIDE

// Solving conflicts on:
// let type foo = bar
//     type baz = bat
// which can be understood as a list of two TypeChunk containing
// a unique TypeDec each, or a single TypeChunk containing two TypeDec.
// We want the latter.
%precedence CHUNKS
%precedence TYPE
//%precedence VAR
%precedence FUNCTION
%precedence PRIMITIVE
%precedence CLASS
%precedence METHOD

  // COMPLETED

%start program

%%
program:
  /* Parsing a source program.  */
  exp
   { td.ast_ = $1; }
| /* Parsing an imported file.  */
  chunks
   { td.ast_ = $1; }
;

exps:
  %empty { $$ = make_exps_type(); }
| exps.1 { $$ = $1; }
;

exps.1:
  exps.1 SEMI exp { $$ = $1; $$->emplace_back($3); }
| exp { $$ = make_exps_type(); $$->emplace_back($1); }
;

%token EXP "_exp";
exp:
  INT { $$ = make_IntExp(@$, $1); } // FIXME: Some code was deleted here (More rules).
   
//COMPLETED

// (* Literals. *)
| NIL { $$ = make_NilExp(@$); }
| STRING { $$ = make_StringExp(@$, $1); }

// (* Array and record creations. *)
| ID LBRACK exp RBRACK OF exp { $$ = make_ArrayExp(@$, make_NameTy(@$, $1), $3, $6); }
| typeid LBRACE exp.1 RBRACE { $$ = make_RecordExp(@$, $1, $3); }

// (* Variables, field, elements of an array. *)
| lvalue { $$ = $1; }

// (* Function call. *)
| ID LPAREN exp.2 RPAREN { $$ = make_CallExp(@$, $1, $3); }

// (* Operations. *)
| MINUS exp { $$ = make_OpExp(@$, make_IntExp(@$, 0), ast::OpExp::Oper::sub, $2); }
| exp PLUS exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
| exp MINUS exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
| exp TIMES exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::mul, $3); }
| exp DIVIDE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::div, $3); }
| exp EQ exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::eq, $3); }
| exp NE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::ne, $3); }
| exp GT exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::gt, $3); }
| exp LT exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::lt, $3); }
| exp GE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::ge, $3); }
| exp LE exp { $$ = make_OpExp(@$, $1, ast::OpExp::Oper::le, $3); }
| exp AND exp { Tweast in; $$ = td.parse(in << "if " << $1 << "then " << $3 << "<> 0 else 0"); }
| exp OR exp { Tweast in; $$ = td.parse(in << "if " << $1 << "then " << "1 " << "else " << $3); }
| LPAREN exps RPAREN { $$ = make_SeqExp(@$, $2); }

// (* Assignment. *)
| lvalue ASSIGN exp { $$ = make_AssignExp(@$, $1, $3); }

// (* Control structures. *)
| IF exp THEN exp ELSE exp { $$ = make_IfExp(@$, $2, $4, $6); }
| IF exp THEN exp { $$ = make_IfExp(@$, $2, $4); }
| WHILE exp DO exp { $$ = make_WhileExp(@$, $2, $4); }
| FOR ID ASSIGN exp TO exp DO exp { $$ = make_ForExp(@$, make_VarDec(@$, $2, nullptr, $4), $6, $8); }
| BREAK { $$ = make_BreakExp(@$); }
| LET chunks IN exps END { $$ = make_LetExp(@$, $2, make_SeqExp(@$, $4)); }

// (* Cast of an expression to a given type *)
| CAST LPAREN exp COMMA ty RPAREN { $$ = make_CastExp(@$, $3, $5); }
// (* An expression metavariable *)
| EXP LPAREN INT RPAREN { $$ = metavar<ast::Exp>(td, $3); }

// (* Object creation. *)
| NEW typeid { $$ = make_ObjectExp(@$, $2); }

// (* Method call. *)
| lvalue DOT ID LPAREN exp.2 RPAREN { $$ = make_MethodCallExp(@$, $3, $5, $1); }
;

%token LVALUE "_lvalue";
lvalue:
  ID { $$ = make_SimpleVar(@$, $1); }

// (* Record field access. *)
| lvalue DOT ID { $$ = make_FieldVar(@$, $1, $3); }

// (* Array subscript. *)
| lvalue LBRACK exp RBRACK { $$ = make_SubscriptVar(@$, $1, $3); }

//(* A l-value metavariable *)
| LVALUE LPAREN INT RPAREN { $$ = metavar<ast::Var>(td, $3); }
;

exp.1:
  %empty { $$ = make_fieldinits_type(); }
| exp.1.1 { $$ = $1; }
;

exp.1.1:
  exp.1.1 COMMA ID EQ exp { $$ = $1; $$->emplace_back(make_FieldInit(@1, $3, $5)); }
| ID EQ exp { $$ = make_fieldinits_type() ; $$->emplace_back(make_FieldInit(@1, $1, $3)); }
;

exp.2:
  %empty { $$ = make_exps_type(); }
| exp.2.1 { $$ = $1; }
;

exp.2.1:
  exp.2.1 COMMA exp { $$ = $1; $$->emplace_back($3); }
| exp { $$ = make_exps_type($1); }
;


/*---------------.
| Declarations.  |
`---------------*/

%token CHUNKS "_chunks";
chunks:
  /* Chunks are contiguous series of declarations of the same type
     (TypeDec, FunctionDec...) to which we allow certain specfic behavior like
     self referencing.
     They are held by a ChunkList, that can be empty, like in this case:
        let
        in
            ..
        end
     which is why we end the recursion with a %empty. */
  %empty { $$ = make_ChunkList(@$); }
// COMPLETED
| tychunk   chunks  { $$ = $2; $$->push_front($1); }
  // FIXME: Some code was deleted here (More rules).
| funchunk   chunks { $$ = $2; $$->push_front($1); }       
| varchunk   chunks { $$ = $2; $$->push_front($1); }
| CHUNKS LPAREN INT RPAREN chunks { ast::ChunkList* ch = metavar<ast::ChunkList>(td, $3); $5->splice_front(*ch); $$ = $5; }
| IMPORT STRING chunks 
{ 
  ast::ChunkList* ch = td.parse_import($2, @$); 
  if (ch)
    $3->splice_front(*ch);
  $$ = $3;
}
;

/*------------------------.
| Variable Declarations.  |
`------------------------*/

varchunk:
  vardec %prec CHUNKS { $$ = make_VarChunk(@1); $$->push_front(*$1); }
//| vardec varchunk
;

vardec: VAR ID vardec.1 ASSIGN exp { $$ = make_VarDec(@$, $2, $3, $5); };

vardec.1:
  %empty { $$ = nullptr; }
| COLON typeid { $$ = $2; }
;

/*------------------------.
| Function Declarations.  |
`------------------------*/

funchunk:
  funcdec %prec CHUNKS { $$ = make_FunctionChunk(@1); $$->push_front(*$1); }
| funcdec funchunk { $$ = $2; $$->push_front(*$1); }
;

funcdec:
  FUNCTION ID LPAREN funcfields RPAREN funcdec.1 EQ exp { $$ = make_FunctionDec(@$, $2, $4, $6, $8); }
| PRIMITIVE ID LPAREN funcfields RPAREN funcdec.1 { $$ = make_FunctionDec(@$, $2, $4, $6, nullptr); }
;

funcdec.1:
  %empty { $$ = nullptr; }
| COLON typeid { $$ = $2; }
;

funcfields:
  %empty               { $$ = make_VarChunk(@$); }
| funcfields.1           { $$ = $1; }
;

funcfields.1:
  funcfields.1 "," funcfield { $$ = $1; $$->emplace_back(*$3); }
| funcfield                { $$ = make_VarChunk(@1); $$->emplace_back(*$1); }
;

funcfield:
  ID ":" typeid     { $$ = make_VarDec(@$, $1, $3, nullptr); }
;

/*--------------------.
| Type Declarations.  |
`--------------------*/

tychunk:
  /* Use `%prec CHUNKS' to do context-dependent precedence and resolve a
     shift-reduce conflict. */
  tydec %prec CHUNKS  { $$ = make_TypeChunk(@1); $$->push_front(*$1); }
| tydec tychunk       { $$ = $2; $$->push_front(*$1); }
;

tydec:
  "type" ID "=" ty { $$ = make_TypeDec(@$, $2, $4); }
// (* Class definition (alternative form). *)
| CLASS ID LBRACE classfields RBRACE { $$ = make_TypeDec(@$, $2, make_ClassTy(@$, make_NameTy(@$, misc::symbol("Object")), $4)); }
| CLASS ID EXTENDS typeid LBRACE classfields RBRACE { $$ = make_TypeDec(@$, $2, make_ClassTy(@$, $4, $6)); }
;


classfields:
// (* Class fields. *)
  %empty { $$ = make_ChunkList(@$); }
| classfield classfields { $$ = $2; $$->push_front($1); }
| classfield.1 classfields  { $$ = $2; $$->push_front($1); }
;

classfield:
// (* Attribute declaration (varchunk). *)
  vardec %prec CLASS { $$ = make_VarChunk(@1); $$->push_front(*$1); }
;

classfield.1:
  METHOD ID LPAREN funcfields RPAREN EQ exp classfield.1 { $$ = $8; $$->push_front(*make_MethodDec(@$, $2, $4, nullptr, $7)); }
| METHOD ID LPAREN funcfields RPAREN EQ exp { $$ = make_MethodChunk(@$); $$->push_front(*make_MethodDec(@$, $2, $4, nullptr, $7)); }
| METHOD ID LPAREN funcfields RPAREN ":" typeid EQ exp classfield.1 { $$ = $10; $$->push_front(*make_MethodDec(@$, $2, $4, $7, $9)); }
| METHOD ID LPAREN funcfields RPAREN ":" typeid EQ exp { $$ = make_MethodChunk(@$); $$->push_front(*make_MethodDec(@$, $2, $4, $7, $9)); }
;

ty:
  typeid               { $$ = $1; }
| "{" tyfields "}"     { $$ = make_RecordTy(@$, $2); }
| "array" "of" typeid  { $$ = make_ArrayTy(@$, $3); }
// (* Class definition (canonical form). *)
| CLASS LBRACE classfields RBRACE { $$ = make_ClassTy(@$, make_NameTy(@$, misc::symbol("Object")), $3); } //inherits from superclass Object
| CLASS EXTENDS typeid LBRACE classfields RBRACE { $$ = make_ClassTy(@$, $3, $5); }
;


tyfields:
  %empty               { $$ = make_fields_type(); }
| tyfields.1           { $$ = $1; }
;

tyfields.1:
  tyfields.1 "," tyfield { $$ = $1; $$->emplace_back($3); }
| tyfield                { $$ = make_fields_type($1); }
;

tyfield:
  ID ":" typeid     { $$ = make_Field(@$, $1, $3); }
;

%token NAMETY "_namety";
typeid:
  ID                    { $$ = make_NameTy(@$, $1); }
  /* This is a metavariable. It it used internally by TWEASTs to retrieve
     already parsed nodes when given an input to parse. */
| NAMETY "(" INT ")"    { $$ = metavar<ast::NameTy>(td, $3); }
;

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  // COMPLETED
  //std::cerr << l << ": " << m << "\n";
  td.error_ << misc::error::error_type::parse << l << ": " << m << "\n";
}
