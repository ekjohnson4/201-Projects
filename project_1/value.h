typedef struct valueobject
    {
    char *type;

    int ival;
    double rval;
    char *sval;
    int val;
    } value;

extern value *newIntegerValue(int v);
extern value *newRealValue(double v);
extern value *newStringValue(char *v);
extern value *newVariableValue(char *v);
extern value *newVarValue(char *v);
extern value *newOperatorValue(char *v);
extern value *newSemicolonValue(char *v);
extern value *newLeftPValue(char *v);
extern value *newRightPValue(char *v);
extern void displayValue(FILE *fp,value *v);

extern char *INTEGER;
extern char *REAL;
extern char *STRING;
extern char *VARIABLE;
extern char *VAR;
extern char *OPERATOR;
extern char *SEMICOLON;
extern char *LEFTP;
extern char *RIGHTP;
