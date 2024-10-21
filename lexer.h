typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASSIGN,
    TOKEN_EOF,
    TOKEN_INVALID,
    TOKEN_STRING_LITERAL
} TokenType;

typedef union {
    int intValue;
    char strValue[50];
} TokenValue;

typedef struct {
    TokenType type;
    TokenValue value;
} Token;

Token get_next_token(const char **input);