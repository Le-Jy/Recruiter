                                                            /* -*- C++ -*- */
// %option defines the parameters with which the reflex will be launched
%option noyywrap
// To enable compatibility with bison
%option bison-complete
%option bison-cc-parser=parser
%option bison_cc_namespace=parse
%option bison-locations

%option lex=lex
// Add a param of function lex() generate in Lexer class
%option params="::parse::TigerDriver& td"
%option namespace=parse
// Name of the class generate by reflex
%option lexer=Lexer

%top{

#define YY_EXTERN_C extern "C" // For linkage rule

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-driver.hh>

  // FIXME: Some code was deleted here (Define YY_USER_ACTION to update locations).
#define YY_USER_ACTION                          \
    do {                                        \
        td.location_.columns(yyleng);           \
    } while (false);                            \


#define TOKEN(Type)                             \
  parser::make_ ## Type(td.location_)

#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, td.location_)


# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!td.enable_extensions_p_)                       \
      td.error_ << misc::error::error_type::scan        \
                << td.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(text()) << "'\n";       \
  } while (false)


%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
id              [a-zA-Z][a-zA-Z_0-9]*
spaces          [ \t]
eol             (\n|\r|n\r|\r\n)
num             [0-3][0-7]{2}
reservedId      _[a-zA-Z0-9_]+


  /* FIXME: Some code was deleted here. */

%class{
    std::string grown_string;
    int countcom = 0;
}

%%
/* The rules.  */

  /* FIXME: Some code was deleted here. */

<SC_COMMENT>{
<<EOF>>   {
            td.error_ << misc::error::error_type::scan
                      << td.location_
                      << ": syntax error: invalid end of file: `"
                      << misc::escape(yytext) << "'\n";
            BEGIN(INITIAL);
          }
"/*"      { countcom++; }
"*/"      {
            if (countcom < 1)
            {
              countcom = 1;
              BEGIN(INITIAL);
            }
            countcom--;
          }
.         { }
}

<SC_STRING>{
<<EOF>>   {
            td.error_ << misc::error::error_type::scan
                      << td.location_
                      << ": syntax error: invalid end of file: `"
                      << misc::escape(yytext) << "'\n";
            BEGIN(INITIAL);
          }
{eol}     {
            td.location_.lines(yyleng);
            td.location_.step();
          }
// to modify -> dont have to throw an error by default
{num}     {
            td.error_ << misc::error::error_type::scan
                      << td.location_
                      << ": syntax error: octal number in string `"
                      << misc::escape(yytext) << "'\n";
            BEGIN(INITIAL);
          }
{spaces}  {
            grown_string += yytext;
            //tp.location_.step();
          }
\,        {
            td.error_ << misc::error::error_type::scan
                      << td.location_
                      << ": syntax error: \\,: `"
                      << misc::escape(yytext) << "'\n";
            BEGIN(INITIAL);
          }
"\\\""    {
            grown_string += "\"";
          }
\\n       {
            grown_string += "\n";
          }
"\\r"     {
            grown_string += "\r";
          }
\\\\      {
            grown_string += "\\";
          }
"\""      {
            BEGIN(INITIAL);
            return TOKEN_VAL(STRING, grown_string);
          }
.         {
            grown_string += yytext;
          }
}

<<EOF>>       {return TOKEN(EOF); }

"array"       { return TOKEN(ARRAY); }
"if"          { return TOKEN(IF); }
"then"        { return TOKEN(THEN); }
"else"        { return TOKEN(ELSE); }
"while"       { return TOKEN(WHILE); }
"for"         { return TOKEN(FOR); }
"to"          { return TOKEN(TO); }
"do"          { return TOKEN(DO); }
"let"         { return TOKEN(LET); }
"in"          { return TOKEN(IN); }
"end"         { return TOKEN(END); }
"of"          { return TOKEN(OF); }
"break"       { return TOKEN(BREAK); }
"nil"         { return TOKEN(NIL); }
"function"    { return TOKEN(FUNCTION); }
"var"         { return TOKEN(VAR); }
"type"        { return TOKEN(TYPE); }
"import"      { return TOKEN(IMPORT); }
"primitive"   { return TOKEN(PRIMITIVE); }
"class"       {
                if (!td.enable_object_extensions_p_)
                  td.error_ << misc::error::error_type::scan
                  << td.location_
                  << ": syntax error: class: `"
                  << misc::escape(yytext) << "'\n";
                else
                  return TOKEN(CLASS);
              }
"extends"     {
                if (!td.enable_object_extensions_p_)
                  td.error_ << misc::error::error_type::scan
                  << td.location_
                  << ": syntax error: extends: `"
                  << misc::escape(yytext) << "'\n";
                else
                  return TOKEN(EXTENDS);
              }
"method"      {
                if (!td.enable_object_extensions_p_)
                  td.error_ << misc::error::error_type::scan
                  << td.location_
                  << ": syntax error: method: `"
                  << misc::escape(yytext) << "'\n";
                else
                  return TOKEN(METHOD);
              }
"new"         {
                if (!td.enable_object_extensions_p_)
                  td.error_ << misc::error::error_type::scan
                  << td.location_
                  << ": syntax error: new: `"
                  << misc::escape(yytext) << "'\n";
                else
                  return TOKEN(NEW);
              }

"_lvalue"     {
                return TOKEN(LVALUE);
              }
"_chunks"     {
                return TOKEN(CHUNKS);
              }              
"_exp"        {
                return TOKEN(EXP);
              }
"_cast"       {
                return TOKEN(CAST);
              }
"_namety"     {
                return TOKEN(NAMETY);
              }

"_main"       {
                return TOKEN_VAL(ID, misc::symbol("_main"));
              }

","           { return TOKEN(COMMA); }
":"           { return TOKEN(COLON); }
";"           { return TOKEN(SEMI); }
"("           { return TOKEN(LPAREN); }
")"           { return TOKEN(RPAREN); }
"["           { return TOKEN(LBRACK); }
"]"           { return TOKEN(RBRACK); }
"{"           { return TOKEN(LBRACE); }
"}"           { return TOKEN(RBRACE); }
"."           { return TOKEN(DOT); }
"+"           { return TOKEN(PLUS); }
"-"           { return TOKEN(MINUS); }
"*"           { return TOKEN(TIMES); }
"/"           { return TOKEN(DIVIDE); }
"="           { return TOKEN(EQ); }
"<>"          { return TOKEN(NE); }
"<"           { return TOKEN(LT); }
"<="          { return TOKEN(LE); }
">"           { return TOKEN(GT); }
">="          { return TOKEN(GE); }
"&"           { return TOKEN(AND); }
"|"           { return TOKEN(OR); }
":="          { return TOKEN(ASSIGN); }


"\""          {
                grown_string = "";
                BEGIN(SC_STRING);
              }


"/*"          {
                BEGIN(SC_COMMENT);
              }

{int}         {
                int val = 0;
                try {
                  val = std::stoi(yytext);
                } catch (const std::out_of_range&) {
                  td.error_ << misc::error::error_type::scan
                            << td.location_
                            << ": value of out of range: `"
                            << misc::escape(yytext) << "'\n";
                }
                return TOKEN_VAL(INT, val);
              }

{id}          {
                return TOKEN_VAL(ID, misc::symbol(yytext));
              }
{reservedId}  {
                return TOKEN_VAL(ID, misc::symbol(yytext));
              }

{spaces}      {
                td.location_.step(); 
              }

{eol}         {
                td.location_.lines(yyleng);  
              }

.             { td.error_ << misc::error::error_type::scan
                          << td.location_
                          << ": syntax error : unrecognized token: `"
                          << misc::escape(yytext) << "'\n"; }
%%
