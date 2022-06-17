/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%{
#include <stdint.h>
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */
%}

/*
 * Define names for regular expressions here.
 */

INT_CONST           [0-9]+
TYPEID    			[A-Z][a-zA-Z0-9_]*
OBJECTID     		[a-z][a-zA-Z0-9_]*
SPECIALS			[.@~*/+-<=(){}:,;]

NEW_LINE			\n
WHITESPACE			[ \n\f\r\t\v]+

NULL_CHAR           \0

%x COMMENT STRING
%option stack

%%

(?i:class)	    { return CLASS; }
(?i:else)	    { return ELSE; }
(?i:fi)		    { return FI; }
(?i:if)		    { return IF; }
(?i:in)		    { return IN; }
(?i:inherits)	{ return INHERITS; }
(?i:isvoid)	    { return ISVOID; }
(?i:let)	    { return LET; }
(?i:loop)	    { return LOOP; }
(?i:pool)	    { return POOL; }
(?i:then)	    { return THEN; }
(?i:while)	    { return WHILE; }
(?i:case)	    { return CASE; }
(?i:esac)	    { return ESAC; }
(?i:of)		    { return OF; }
(?i:not)	    { return NOT; }
    
f(?i:alse) {
    cool_yylval.boolean = false;
    return BOOL_CONST;
}

t(?i:rue) {
    cool_yylval.boolean = true;
    return BOOL_CONST;
}

"=>"		{ return DARROW; }
"<="		{ return LE; }
"<-"		{ return ASSIGN; }

{INT_CONST} {
    cool_yylval.symbol = inttable.add_string(yytext);
    return INT_CONST;
}

{TYPEID} {
    cool_yylval.symbol = idtable.add_string(yytext);
    return TYPEID;
}

{OBJECTID} {
    cool_yylval.symbol = idtable.add_string(yytext);
    return OBJECTID;
}

{WHITESPACE}    {}
{SPECIALS}	    { return yytext[0]; }
{NEW_LINE}      { ++curr_lineno; }

--.* {}

"(*" yy_push_state(COMMENT);
"*)" {
    cool_yylval.error_msg = "Unmatched *)";
    return ERROR;
}

<COMMENT>{
    "(*"    yy_push_state(COMMENT);
    "*)"    yy_pop_state();
    .|\n       {}
    <<EOF>> {
        cool_yylval.error_msg = "EOF in comment";
        BEGIN(INITIAL);
        return ERROR;
    }
}

\" {
    string_buf_ptr = string_buf;
    BEGIN STRING;      
}

<STRING>{
    \" {
        *string_buf_ptr = '\0';
        cool_yylval.symbol = stringtable.add_string(string_buf);
        BEGIN INITIAL;
        return (STR_CONST);
    }

    \n {
        cool_yylval.error_msg = "Unterminated string constant";
        ++curr_lineno;
        return (ERROR);
    }

    \\n             *string_buf_ptr++ = '\n';
    \\t             *string_buf_ptr++ = '\t';
    \\f             *string_buf_ptr++ = '\f';
    \\b             *string_buf_ptr++ = '\b';

    \\(.|\n)        *string_buf_ptr++ = yytext[1];

    [^\\\n\"]+    {
        char *ptr = yytext;
        while (*ptr) {
            *string_buf_ptr++ = *ptr++;
        }
    }

    <<EOF>> {
        cool_yylval.error_msg = "EOF in string constant";
        BEGIN(INITIAL);
        return ERROR;
    }
}

. {
    cool_yylval.error_msg = yytext;
    return ERROR;
}


%%