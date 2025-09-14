#define _POSIX_C_SOURCE 200809L

#include "lexer.h"

#include <ctype.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../expansion/expand_word.h"
#include "../expansion/variables.h"
#include "../io/io.h"
#include "../options/verbose.h"
#include "token.h"

/*
 * Char array to check if the word is reserved.
 * */
static char *check_word[] = {
    [TOKEN_IF] = "if",     [TOKEN_THEN] = "then", [TOKEN_ELIF] = "elif",
    [TOKEN_ELSE] = "else", [TOKEN_FI] = "fi",     [TOKEN_WHILE] = "while",
    [TOKEN_FOR] = "for",   [TOKEN_IN] = "in",     [TOKEN_UNTIL] = "until",
    [TOKEN_DO] = "do",     [TOKEN_DONE] = "done", [TOKEN_CASE] = "case",
    [TOKEN_ESAC] = "esac", [TOKEN_NOT] = "!",     [TOKEN_LBRACE] = "{",
    [TOKEN_RBRACE] = "}",  [TOKEN_LPAR] = "(",    [TOKEN_RPAR] = ")"
};

static char *verbose_token[] = {
    [TOKEN_IF] = "if",       [TOKEN_THEN] = "then",
    [TOKEN_ELIF] = "elif",   [TOKEN_ELSE] = "else",
    [TOKEN_FI] = "fi",       [TOKEN_WHILE] = "while",
    [TOKEN_FOR] = "for",     [TOKEN_IN] = "in",
    [TOKEN_UNTIL] = "until", [TOKEN_DO] = "do",
    [TOKEN_DONE] = "done",   [TOKEN_NOT] = "not",
    [TOKEN_SEMICOLON] = ";", [TOKEN_NEWLINE] = "NEWLINE",
    [TOKEN_RBRACE] = "{",    [TOKEN_LBRACE] = "}",
    [TOKEN_LPAR] = "(",      [TOKEN_RPAR] = ")",
    [TOKEN_EOF] = "EOF"
};

static enum token_type check_delimiter[] = { ['\n'] = TOKEN_NEWLINE,
                                             [';'] = TOKEN_SEMICOLON,
                                             ['('] = TOKEN_LPAR,
                                             [')'] = TOKEN_RPAR };

static bool is_special(struct recognition_info *info)
{
    return (info->escape || info->double_quoted || info->quoted
            || info->is_variable || info->backquoted);
}

static inline void verbose_lex(struct token *new_token)
{
    if (new_token->type != TOKEN_WORD && new_token->type != TOKEN_OPERATOR
        && new_token->type != TOKEN_IONUMBER
        && new_token->type != TOKEN_ASSIGNMENT_WORD)
        verbose("\033[0;37mToken found: \033[1;36m%s\n\033[0;37m",
                verbose_token[new_token->type]);
    else
        verbose(
            "\033[0;37mToken found: \033[0;37mword : \033[1;36m%s\n\033[0;37m",
            new_token->value);
}

static inline void create_token_value(struct token *new_token,
                                      struct lexer *lexer, size_t word_size)
{
    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    new_token->value = calloc(word_size + 2, sizeof(char));
    new_token->value[word_size] = io_pop(fd);
}

static inline void increase_token_value(struct token *new_token,
                                        struct lexer *lexer, size_t *word_size)
{
    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    (*word_size)++;
    new_token->value = realloc(new_token->value, *word_size + 2);
    new_token->value[*word_size] = io_pop(fd);
}

static inline void skip_line(struct lexer *lexer)
{
    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    while (io_peek(fd) != '\n' && io_peek(fd) != '\0')
        io_pop(fd);
}

/**
 * @brief Token recognition algorithm (SCL).
 *
 * @param Current lexer, token currently recognized, boolean to determine
 * if the token is a word.
 *
 * @return The size of the word if it is a word.
 */

static void lex_operator_token(struct lexer *lexer, struct token *new_token,
                               struct recognition_info *info)
{
    if (new_token->type == TOKEN_OPERATOR && !is_special(info)
        && (info->c == '>' || info->c == '&' || info->c == '|'))
    {
        increase_token_value(new_token, lexer, &(info->word_size));
        info->pass_loop = true;
    }
    else if (new_token->type == TOKEN_OPERATOR && !info->quoted
             && !info->double_quoted)
    {
        new_token->value[info->word_size + 1] = '\0';
        info->exit_loop = true;
    }
}

static void lex_quotes(struct recognition_info *info)
{
    if (info->pass_loop || info->exit_loop)
        return;

    if (info->c == '\'' || info->c == '\"' || info->c == '`')
    {
        if (!info->double_quoted && !info->escape)
            info->quoted = info->c == '\'' ? !info->quoted : info->quoted;

        if (!info->quoted && !info->escape)
        {
            info->double_quoted =
                info->c == '\"' ? !info->double_quoted : info->double_quoted;
        }

        if (!info->quoted && !info->escape)
        {
            info->backquoted =
                info->c == '`' ? !info->backquoted : info->backquoted;
        }

        info->is_reserved = false; // to check
    }
}

static void lex_word_operator(struct lexer *lexer, struct token *new_token,
                              bool *word, struct recognition_info *info)
{
    if (info->pass_loop || info->exit_loop)
        return;

    if (!is_special(info)
        && (info->c == '<' || info->c == '>' || info->c == '|'
            || info->c == '&'))
    {
        if (*word)
        {
            info->exit_loop = true;
            return;
        }
        new_token->type = TOKEN_OPERATOR;
        create_token_value(new_token, lexer, info->word_size);
        info->pass_loop = true;
    }
}

static void lex_delimiter(struct lexer *lexer, struct token *new_token,
                          bool *word, struct recognition_info *info)
{
    if (info->pass_loop || info->exit_loop)
        return;

    if (info->c == ')' && !info->nb_tomatch)
    {
        info->is_variable = false;
        return;
    }

    if (info->c == '(' && info->is_variable)
        info->nb_tomatch++;
    if (info->c == ')' && info->nb_tomatch)
        info->nb_tomatch--;

    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    if (!is_special(info)
        && (info->c == '\n' || info->c == ';'
            || ((info->c == '(' || info->c == ')') && !info->is_variable)))
    {
        if (!(*word))
            new_token->type = check_delimiter[(int)io_pop(fd)];
        if (new_token->type == TOKEN_SEMICOLON && io_peek(fd) == ';')
        {
            increase_token_value(new_token, lexer, &info->word_size);
            new_token->value[0] = ';';
            new_token->type = TOKEN_OPERATOR;
        }
        info->exit_loop = true;
    }
    else if (info->escape && (info->c == '\n'))
    {
        io_pop(fd);
        if (info->word_size > 0)
            info->word_size--;
        else
            *word = false;
        info->pass_loop = true;
    }
}

static void lex_blank(struct lexer *lexer, bool *word,
                      struct recognition_info *info)
{
    if (info->pass_loop || info->exit_loop)
        return;

    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    if (!is_special(info) && isblank(info->c))
    {
        if (!(*word))
        {
            io_pop(fd);
            info->pass_loop = true;
            return;
        }
        info->exit_loop = true;
        return;
    }
}

static void lex_current_word(bool *word, struct token *new_token,
                             struct lexer *lexer, struct recognition_info *info)
{
    if (info->pass_loop || info->exit_loop)
        return;

    if (*word)
        increase_token_value(new_token, lexer, &info->word_size);
}

static void lex_comments(bool *word, struct lexer *lexer,
                         struct recognition_info *info)
{
    if (info->pass_loop || info->exit_loop)
        return;

    if (!*word && !is_special(info) && info->c == '#')
    {
        skip_line(lexer);
        info->pass_loop = true;
    }
}

static void lex_start_word(bool *word, struct token *new_token,
                           struct lexer *lexer, struct recognition_info *info)
{
    if (info->pass_loop || info->exit_loop)
        return;

    if (!(*word))
    {
        *word = true;
        create_token_value(new_token, lexer, info->word_size);
    }
}

static void lex_backslash(bool *word, struct token *new_token,
                          struct lexer *lexer, struct recognition_info *info)
{
    if (info->quoted || info->c != '\\' || info->exit_loop || info->pass_loop)
        return;

    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    lex_current_word(word, new_token, lexer, info);
    lex_start_word(word, new_token, lexer, info);
    info->c = io_peek(fd);
    info->escape = !info->escape;
}

static void lex_variable(bool *word, struct token *new_token,
                         struct lexer *lexer, struct recognition_info *info)
{
    if (info->quoted || info->escape || info->c != '$' || info->exit_loop
        || info->pass_loop)
        return;

    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    info->is_reserved = false;
    lex_current_word(word, new_token, lexer, info);
    lex_start_word(word, new_token, lexer, info);

    if (io_peek(fd) == '(')
        info->is_variable = true;
    info->pass_loop = true;
}

static int exit_token_recognition(struct token *new_token,
                                  struct recognition_info *info,
                                  struct lexer *lexer)
{
    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    info->is_variable = false;
    if (is_special(info) && !isatty(fileno(fd)))
    {
        new_token->value[info->word_size + 1] = '\0';
        free(info);
        return -1;
    }
    size_t res = info->word_size;
    free(info);

    return res;
}

inline static struct recognition_info *create_recognition_info(char c)
{
    struct recognition_info *info = calloc(1, sizeof(struct recognition_info));
    info->c = c;
    info->is_reserved = true;
    info->is_variable = false;
    info->nb_tomatch = -1;
    return info;
}

static int token_recognition(struct lexer *lexer, struct token *new_token,
                             bool *word, bool *is_reserved)
{
    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    struct recognition_info *info = create_recognition_info(io_peek(lexer->fd));
    while (!info->exit_loop && (info->c = io_peek(fd)) > 0)
    {
        info->pass_loop = false;
        lex_operator_token(lexer, new_token, info);
        lex_quotes(info);
        lex_backslash(word, new_token, lexer, info);
        lex_word_operator(lexer, new_token, word, info);
        lex_variable(word, new_token, lexer, info);
        lex_delimiter(lexer, new_token, word, info);
        lex_blank(lexer, word, info);
        lex_current_word(word, new_token, lexer, info);
        lex_comments(word, lexer, info);
        lex_start_word(word, new_token, lexer, info);
        info->escape = false;
    }
    *is_reserved = info->is_reserved;
    return exit_token_recognition(new_token, info, lexer);
}

static bool check_assignement_word(char *string)
{
    if (*string != '_' && (*string < 'a' || *string > 'z')
        && (*string < 'A' || *string > 'Z'))
        return false;

    size_t i = 0;
    char c = string[i];
    while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
           || (c >= '0' && c <= '9') || (c == '_'))
    {
        i++;
        c = string[i];
    }
    return string[i] == '=';
}

static void set_assignement_word(struct token *token)
{
    if (strstr(token->value, "=") && *token->value != '=')
    {
        if (check_assignement_word(token->value))
            token->type = TOKEN_ASSIGNMENT_WORD;
    }
    return;
}

static bool is_eof(struct token *token)
{
    return token->type != TOKEN_NEWLINE && token->type != TOKEN_SEMICOLON
        && token->type != TOKEN_OPERATOR && token->type != TOKEN_LPAR
        && token->type != TOKEN_RPAR;
}

static struct token *lex_token(struct lexer *lexer);
static struct token *check_unalias(struct token *token, struct lexer *lexer)
{
    if (!strcmp(token->value, "unalias"))
    {
        token_free(token);
        lexer->unalias = true;
        struct token *unassignement = lex_token(lexer);
        if (unassignement->type != TOKEN_WORD)
            return unassignement;

        if (!hash_map_get(lexer->aliases, unassignement->value))
        {
            struct special_var current_var = { .key = "?", .value = "1" };
            modify_special_var(&current_var);
            fprintf(stderr, "unalias not found: %s", unassignement->value);
        }

        hash_map_remove(lexer->aliases, unassignement->value);
        token_free(unassignement);

        lexer->unalias = false;
        return lex_token(lexer);
    }
    return NULL;
}

static struct token *split_alias(struct lexer *lexer)
{
    struct token *assignment = lex_token(lexer);
    if (assignment->type != TOKEN_ASSIGNMENT_WORD)
        return assignment;

    char *string = assignment->value;
    char *start = string;

    while (*string != '=')
        string++;

    size_t len = string - start;
    char *key = calloc(len + 1, sizeof(char));
    strncpy(key, string - len, len);

    // checker si la key est valable

    string++;
    char *value = calloc(strlen(string) + 1, sizeof(char));
    strcpy(value, string);

    char *res = calloc(1, sizeof(char));
    char *start_value = value;
    expand_word(value, &res);
    free(start_value);
    value = res ? res : "";

    hash_map_insert(lexer->aliases, key, value);
    free(key);
    if (res)
        free(value);
    token_free(assignment);

    return lex_token(lexer);
}

static struct token *check_aliase(struct token *token, struct lexer *lexer)
{
    if (token->type != TOKEN_WORD)
        return token;

    char *alias_val = hash_map_get(lexer->aliases, token->value);
    if (alias_val)
    {
        lexer->alias_fd = get_stream_from_string(alias_val);
        if (!lexer->alias_fd)
            exit(1);
        token_free(token);
        return lex_token(lexer);
    }
    struct token *unalias_res = check_unalias(token, lexer);
    if (unalias_res)
        return unalias_res;

    if (strcmp(token->value, "alias"))
        return token;

    token_free(token);

    return split_alias(lexer);
}

/**
 * @brief Parse the next token following the token recognition (SCL).
 *
 * @param Current lexer.
 *
 * @return The next token.
 */
static struct token *lex_token(struct lexer *lexer)
{
    struct token *new_token = calloc(1, sizeof(struct token));
    FILE *fd = lexer->alias_fd ? lexer->alias_fd : lexer->fd;
    bool word = false, is_reserved = true;
    ssize_t word_size =
        token_recognition(lexer, new_token, &word, &is_reserved);

    if (word_size == -1)
    {
        new_token->type = TOKEN_ERROR;
        return new_token;
    }

    if (!word && is_eof(new_token))
        new_token->type = TOKEN_EOF;
    else if (word)
    {
        word_size++;
        new_token->value = realloc(new_token->value, word_size + 1);
        new_token->value[word_size] = '\0';

        char *end = new_token->value;
        if (io_peek(fd) == '>' || io_peek(fd) == '<')
            strtol(new_token->value, &end, 10);
        else if (isblank(io_peek(fd)))
            io_pop(fd);

        new_token->type = (*end == '\0') ? TOKEN_IONUMBER : TOKEN_WORD;

        if (is_reserved)
            for (int i = TOKEN_IF; i < TOKEN_NEWLINE; i++)
                if (!strcmp(new_token->value, check_word[i]))
                {
                    new_token->type = i;
                    break;
                }

        if (new_token->type == TOKEN_WORD)
            set_assignement_word(new_token);

        if (!lexer->unalias)
            new_token = check_aliase(new_token, lexer);
    }
    else if (new_token->type == TOKEN_OPERATOR)
    {
        word_size++;
        new_token->value = realloc(new_token->value, word_size + 1);
        new_token->value[word_size] = '\0';
    }

    verbose_lex(new_token);

    if (fd == lexer->alias_fd && io_peek(fd) <= 0)
    {
        fclose(lexer->alias_fd);
        lexer->alias_fd = NULL;
    }

    return new_token;
}

struct lexer *new_lexer(FILE *file)
{
    struct lexer *lexer = calloc(1, sizeof(struct lexer));
    if (!lexer)
        return NULL;

    lexer->aliases = hash_map_init(42);
    lexer->fd = file;
    lexer->next_token = lex_token(lexer);
    if (!lexer->next_token)
    {
        free_lexer(lexer);
        return NULL;
    }

    lexer->look_ahead = NULL;

    return lexer;
}

void free_lexer(struct lexer *lexer)
{
    hash_map_free(lexer->aliases);
    free(lexer);
}

struct token *peek_token(struct lexer *lexer)
{
    return lexer->next_token;
}

struct token *look_ahead(struct lexer *lexer)
{
    if (!lexer->look_ahead)
        lexer->look_ahead = lex_token(lexer);
    return lexer->look_ahead;
}

struct token *eat_token(struct lexer *lexer)
{
    struct token *curr_token = lexer->next_token;
    if (curr_token->type != TOKEN_EOF)
    {
        if (lexer->look_ahead)
        {
            lexer->next_token = lexer->look_ahead;
            lexer->look_ahead = NULL;
        }
        else
            lexer->next_token = lex_token(lexer);
    }
    return curr_token;
}
