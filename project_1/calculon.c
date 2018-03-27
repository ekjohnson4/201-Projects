#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "scanner.h"
#include "stack.h"

void Fatal(char *,...);

static value *readValue(FILE *);
static void printValue(FILE *,char *,value *);
static void freeValue(value *);

int optionV = 0;
int optionD = 0;
int st = 0;
int h = 0;
int size = 0;
int dat = 0;
char *per;
int w = 0;
TreeNode *root;

void
Fatal(char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "An error occured: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(-1);
}

static value *
readValue(FILE *fp)
    {
    value *v;
    if (stringPending(fp))
        v = newStringValue(readString(stdin));
    else
        {
        char *token = readToken(fp);
				if (token==NULL){
					exit(0);
				}

        if (strchr(token,'.') != 0) // dot found!
            v = newRealValue(atof(token));
        else if (isdigit(*token))
            v = newIntegerValue(atoi(token));
        else if (strchr(token,'+') != 0 || strchr(token,'*') != 0 || strchr(token,'/') != 0 || strchr(token,'-') != 0
        || strchr(token,'=') != 0 || strchr(token,'%') != 0 || strchr(token,'^') != 0)
            v = newOperatorValue(token);
				else if (token[0] == 'v' && token[1] == 'a' && token[2] == 'r')
						v = newVarValue(token);
        else if (strchr(token,'a') != 0 || strchr(token,'b') != 0 || strchr(token,'c') != 0 || strchr(token,'d') != 0
        || strchr(token,'e') != 0 || strchr(token,'f') != 0 || strchr(token,'g') != 0 || strchr(token,'h') != 0
        || strchr(token,'i') != 0 || strchr(token,'j') != 0 || strchr(token,'k') != 0 || strchr(token,'l') != 0
        || strchr(token,'m') != 0 || strchr(token,'n') != 0 || strchr(token,'o') != 0 || strchr(token,'p') != 0
        || strchr(token,'q') != 0 || strchr(token,'r') != 0 || strchr(token,'s') != 0 || strchr(token,'t') != 0
        || strchr(token,'u') != 0 || strchr(token,'v') != 0 || strchr(token,'w') != 0 || strchr(token,'x') != 0
        || strchr(token,'y') != 0 || strchr(token,'z') != 0)
            v = newVariableValue(token);
        else if (strchr(token,';') != 0)
            v = newSemicolonValue(token);
				else if (strchr(token,'(') != 0)
            v = newLeftPValue(token);
				else if (strchr(token,')') != 0)
            v = newRightPValue(token);
        else
            Fatal("The token %s is not a value\n",token);
        }
    return v;
    }

static void
freeValue(value *v)
    {
    if (v->type == STRING) free(v->sval);
    free(v);
    }

static void
insertQueue(Queue *Q, value *v)
  {
		if (v->type == STRING){
			st++;
		}
  	enqueue(Q,v);
}

Queue *
infixToPostfix(Queue *Q,int l,int p)
{
		Queue *pre = createQueue();
		value *x;

    // Create a stack of capacity equal to expression size
    struct Stack* stack = createStack(l+1);
    if(!stack) // See if stack was created successfully
        printf("Stack creation failed.");

		while(!(isQueueEmpty(Q))){
				if (Q->head->data->type == VARIABLE){
					TreeNode *x = Find(root,Q->head->data->sval,size);

					if (x->type == INTEGER){
						Q->head->data->ival = x->val;
						Q->head->data->type = INTEGER;
					}
				}

        // If the scanned character is an operand, add it to output.
        if (Q->head->data->type == INTEGER || Q->head->data->type == REAL){
            enqueue(pre,Q->head->data);
						dequeue(Q);
					}

				// If the scanned character is an ‘(‘, push it to the stack.
				else if (Q->head->data->type == LEFTP){
					push(stack, Q->head->data);
					dequeue(Q);
					l--;
					}

				//  If the scanned character is an ‘)’, pop and output from the stack
				// until an ‘(‘ is encountered.
				else if (Q->head->data->type == RIGHTP){

					while (isEmpty(stack) == 0 && top(stack)->type != LEFTP)
							enqueue(pre,pop(stack));
					if (isEmpty(stack) == 0 && top(stack)->type != LEFTP)
							printf("Invalid expression..."); // invalid expression
					else{
							pop(stack);
							dequeue(Q);
							l--;
						}
				}

				// an operator is encountered
				else
        {
          while (isEmpty(stack) == 0 && Prec(Q->head->data) <= Prec(top(stack)))
              enqueue(pre,pop(stack));
          push(stack, Q->head->data);
					dequeue(Q);
        }
    }
    // pop all the operators from the stack
    while (isEmpty(stack) == 0)
        enqueue(pre,pop(stack));

		if (p==2){
			while(l>0){
				if (pre->head->data->type == INTEGER){
					printf("%d ",pre->head->data->ival);
					dequeue(pre);
					l--;
				}
				else if (pre->head->data->type == REAL){
					printf("%f ",pre->head->data->rval);
					dequeue(pre);
					l--;
				}
				else if (pre->head->data->type == OPERATOR){
					printf("%s ",pre->head->data->sval);
					dequeue(pre);
					l--;
				}
			}
			printf("\n");
		}
	return pre;
}

void
convert(Queue *post,int l) {
	value *op1;
	value *op2;
	int flag = 0;

	// Create a stack of capacity equal to expression size
	struct Stack* stack = createStack(l);
	if(!stack) // See if stack was created successfully
			printf("Stack creation failed.");

	while(isQueueEmpty(post) == 0)
		{
			/* Push the operand */
			if(post->head->data->type == INTEGER || post->head->data->type == REAL){
				push(stack,post->head->data);
			}

			else{
				/* Operator,pop two  operands */
				value *ch = post->head->data;
				op2=pop(stack);
				op1=pop(stack);

				if(op1->type == REAL && op2->type == INTEGER){
					flag = 1;
					double x1,x2;
					x1 = op1->rval;
					x2 = op2->ival;
					op2->rval = x2;

					double ex = op2->rval;
					long long result = 1;

					//Temp value node to hold processed answer. Resets up completetion of single calculation.
					value *temp = newRealValue(0.0);

					per = "real";

					switch(*ch->sval)
					{
					case '+':temp->rval = op1->rval+op2->rval;push(stack,temp);break;
					case '-':temp->rval = op1->rval-op2->rval;push(stack,temp);break;
					case '*':temp->rval = op1->rval*op2->rval;push(stack,temp);break;
					case '/':temp->rval = op1->rval/op2->rval;push(stack,temp);break;
					case '^':
						while (ex != 0)
							{
								result *= op1->rval;
								--ex;
							}
						temp->rval = result;
						push(stack,temp);
						break;
					}
				}

				else if(op2->type == REAL && op1->type == INTEGER){
					flag = 1;
					double x1,x2;
					x1 = op1->ival;
					x2 = op2->rval;
					op1->rval = x1;

					double ex = op2->rval;
					long long result = 1;

					//Temp value node to hold processed answer. Resets up completetion of single calculation.
					value *temp = newRealValue(0.0);

					per = "real";

					switch(*ch->sval)
					{
					case '+':temp->rval = op1->rval+op2->rval;push(stack,temp);break;
					case '-':temp->rval = op1->rval-op2->rval;push(stack,temp);break;
					case '*':temp->rval = op1->rval*op2->rval;push(stack,temp);break;
					case '/':temp->rval = op1->rval/op2->rval;push(stack,temp);break;
					case '^':
						while (ex != 0)
							{
								result *= op1->rval;
								--ex;
							}
						temp->rval = result;
						push(stack,temp);
						break;
					}
				}

				else if(op1->type == REAL && op2->type == REAL){
					flag = 1;

					double ex = op2->rval;
					long long result = 1;

					//Temp value node to hold processed answer. Resets up completetion of single calculation.
					value *temp = newRealValue(0.0);

					per = "real";

					switch(*ch->sval)
					{
					case '+':temp->rval = op1->rval+op2->rval;push(stack,temp);break;
					case '-':temp->rval = op1->rval-op2->rval;push(stack,temp);break;
					case '*':temp->rval = op1->rval*op2->rval;push(stack,temp);break;
					case '/':temp->rval = op1->rval/op2->rval;push(stack,temp);break;
					case '^':
						while (ex != 0)
							{
								result *= op1->rval;
								--ex;
							}
						temp->rval = result;
						push(stack,temp);
						break;
					}
				}

				else{
					flag = 0;
					int ex = op2->ival;
					long long result = 1;

					//Temp value node to hold processed answer. Resets up completetion of single calculation.
					value *temp = newIntegerValue(0);

					per = "integer";

					switch(*ch->sval)
					{
					case '+':temp->ival = op1->ival+op2->ival;push(stack,temp);break;
					case '-':temp->ival = op1->ival-op2->ival;push(stack,temp);break;
					case '*':temp->ival = op1->ival*op2->ival;push(stack,temp);break;
					case '/':temp->ival = op1->ival/op2->ival;push(stack,temp);break;
					case '^':
						while (ex != 0)
							{
								result *= op1->ival;
								--ex;
							}
						temp->ival = result;
						push(stack,temp);
						break;
					case '%':temp->ival = op1->ival%op2->ival;push(stack,temp);break;
					}
				}
			}
		dequeue(post);
	}

	if (flag == 0){
		printf("%d\n",topI(stack));
		dat = topI(stack);
	}
	else if (flag == 1){
		printf("%f\n",topR(stack));
		dat = topR(stack);
	}
}

int
ProcessOptions(int argc, char **argv)
{
	int argIndex = -1;
	int argUsed = -1;
	int separateArg = -1;

	argIndex = 1;

	while (argIndex < argc && *argv[argIndex] == '-')
	{
		/* check if stdin, represented by "-" is an argument */
		/* if so, the end of options has been reached */
		if (argv[argIndex][1] == '\0') return argIndex;

		separateArg = 0;
		argUsed = 0;

		switch (argv[argIndex][1])
		{

		case 'v': /* give the author's name and immediately exit */
			optionV = 1;
      printf("Ethan Johnson");
      exit(0);
			break;
		case 'd': /* print the postfix conversion of the last infix expression */
			optionD = 1;
			break;
		default:

			Fatal("option %s not understood\n", argv[argIndex]);
		}

		if (separateArg && argUsed)
			++argIndex;
		++argIndex;
	}

	return argIndex;
}

int
main(int argc,char **argv) {
	int y = ProcessOptions(argc, argv);
	if (argc == 3 || (argc == 2 && (y != 2))){
		value *v[1000];
		int i = 0;
		int x = 0;
		int a = 0;
		int p = 0;

		if (argc == 3){
			a = 2;
			p = 2;

		}
		else if (argc == 2){
			a = 1;
		}

		FILE* file = fopen (argv[a], "r");
		while (!feof(file)){
				i = 0;

				// read in values from stdin
				v[i] = readValue(file);

				while(v[i]->type != SEMICOLON){
					i++;
					v[i] = readValue(file);
				}

				//Create queue
				Queue *Q = createQueue();

				//insert values into queue
				while(x != i){
					insertQueue(Q,v[x]);
					x++;
				}

				int l = getLength(Q);

				if (st == 2){
					char *a = front(Q)->sval;
					char *b = Q->head->next->next->data->sval;
					char *c = malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
					if (c == 0) Fatal("out of memory\n");
					sprintf(c,"%s%s",a,b);
					printf("%s",c);
				}

				else if (st == 1){
					if(front(Q)->type==STRING){
						char *a = front(Q)->sval;
						if(Q->head->next->next->data->type == INTEGER){
							int num = atoi(a);
							Q->head->data->type = INTEGER;
							Q->head->data->ival = num;
						}
						else if(Q->head->next->next->data->type == REAL){
							double num = atof(a);
							Q->head->data->type = REAL;
							Q->head->data->ival = num;
						}
					}

					else{
						char *a = Q->head->next->next->data->sval;
						if(Q->head->data->type == INTEGER){
							int num = atoi(a);
							Q->head->next->next->data->type = INTEGER;
							Q->head->next->next->data->ival = num;
						}
						else if(Q->head->data->type == REAL){
							double num = atof(a);
							Q->head->next->next->data->type = REAL;
							Q->head->next->next->data->ival = num;
						}
					}

					//Convert in-fix expression to post-fix
					Queue *post = infixToPostfix(Q,l,y);

					if (y==2){
						x = 0;
						while(x != i){
							freeValue(v[x]);
							x++;
						}
						continue;
					}

					//Process post-fix equation to produce result
					convert(post,l);

					x = 0;
					while(x != i){
						freeValue(v[x]);
						x++;
					}
				}

				else if(front(Q)->type == VAR){
					dequeue(Q);
					TreeNode *temp = NewTreeNode(front(Q));

					Q->head->data->val = Q->head->next->next->data->ival;

					if (h == 0){
						//Store value into a bst
						TreeNode *x = NewTreeNode(front(Q));
						root = x;
						temp = x;
						h++;
						size++;
						while(l>1){
							dequeue(Q);
							l--;
						}
					}

					else{
						TreeNode *y = insertElement(root,front(Q));
						size++;
						while(l>1){
							dequeue(Q);
							l--;
						}
					}
				}

				else if (Q->head->data->type == VARIABLE && l == 1){
					TreeNode *o = Find(root,Q->head->data->sval,size);
					printf("%d\n",o->val);

					int x = 0;
					while(x != i){
						freeValue(v[x]);
						dequeue(Q);
						x++;
					}
				}

				else if (Q->head->data->type == VARIABLE && Q->head->next->data->sval[0] == '='){
					TreeNode *check = Check(root,front(Q),size);
					value *temp = front(Q);
					dequeue(Q);
					dequeue(Q);

					//Convert in-fix expression to post-fix
					Queue *post = infixToPostfix(Q,l,y);

					if (y==2){
						int p = 0;
						while(x != i){
							freeValue(v[x]);
							p++;
						}
						continue;
					}

					//Process post-fix equation to produce result
					convert(post,l);

					TreeNode *done = Change(root,temp,size,dat);

					int p = 0;
					while(x != i){
						freeValue(v[x]);
						p++;
					}
				}

				else{
				//Convert in-fix expression to post-fix
				Queue *post = infixToPostfix(Q,l,p);

				if (argc==3){
					continue;

					int p = 1;
					while(x != i){
						freeValue(v[x]);
						p++;
					}
				}

				//Process post-fix equation to produce result
				convert(post,l);

				int p = 0;
				while(x != i){
			    freeValue(v[x]);
					p++;
				}
		  }
		}
		return 0;
	}

	while(!feof(stdin)){
	  //No file
	  if (argc == 2 || argc == 1){
			value *v[1000];
			int i = 0;
			int x = 0;

			// read in values from stdin
			v[i] = readValue(stdin);
			while(v[i]->type != SEMICOLON){
				i++;
				v[i] = readValue(stdin);
			}

			//Create queue
			Queue *Q = createQueue();

			//insert values into queue
			while(x != i){
				insertQueue(Q,v[x]);
				x++;
			}

			int l = getLength(Q);

			if (st == 2){
				char *a = front(Q)->sval;
				char *b = Q->head->next->next->data->sval;
				char *c = malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
				if (c == 0) Fatal("out of memory\n");
				sprintf(c,"%s%s",a,b);
				printf("%s\n",c);
			}

			else if (st == 1){
				if(front(Q)->type==STRING){
					char *a = front(Q)->sval;
					if(Q->head->next->next->data->type == INTEGER){
						int num = atoi(a);
						Q->head->data->type = INTEGER;
						Q->head->data->ival = num;
					}
					else if(Q->head->next->next->data->type == REAL){
						double num = atof(a);
						Q->head->data->type = REAL;
						Q->head->data->ival = num;
					}
				}

				else{
					char *a = Q->head->next->next->data->sval;
					if(Q->head->data->type == INTEGER){
						int num = atoi(a);
						Q->head->next->next->data->type = INTEGER;
						Q->head->next->next->data->ival = num;
					}
					else if(Q->head->data->type == REAL){
						double num = atof(a);
						Q->head->next->next->data->type = REAL;
						Q->head->next->next->data->ival = num;
					}
				}

				//Convert in-fix expression to post-fix
				Queue *post = infixToPostfix(Q,l,y);

				if (y==2){
					x = 0;
					while(x != i){
						freeValue(v[x]);
						x++;
					}
					continue;
				}

				//Process post-fix equation to produce result
				convert(post,l);

				x = 0;
				while(x != i){
					freeValue(v[x]);
					x++;
				}
			}

			else if(front(Q)->type == VAR){
				dequeue(Q);
				TreeNode *temp = NewTreeNode(front(Q));

				Q->head->data->val = Q->head->next->next->data->ival;

				if (h == 0){
					//Store value into a bst
					TreeNode *x = NewTreeNode(front(Q));
					root = x;
					temp = x;
					h++;
					size++;
					while(l>1){
						dequeue(Q);
						l--;
					}
				}

				else{
					TreeNode *y = insertElement(root,front(Q));
					size++;
					while(l>1){
						dequeue(Q);
						l--;
					}
				}
			}

			else if (Q->head->data->type == VARIABLE && l == 1){
				TreeNode *o = Find(root,Q->head->data->sval,size);
				printf("%d\n",o->val);

				x = 0;
				while(x != i){
					freeValue(v[x]);
					dequeue(Q);
					x++;
				}
			}

			else if (Q->head->data->type == VARIABLE && Q->head->next->data->sval[0] == '='){
				TreeNode *check = Check(root,front(Q),size);
				value *temp = front(Q);
				dequeue(Q);
				dequeue(Q);

				//Convert in-fix expression to post-fix
				Queue *post = infixToPostfix(Q,l,y);

				if (y==2){
					x = 0;
					while(x != i){
						freeValue(v[x]);
						x++;
					}
					continue;
				}

				//Process post-fix equation to produce result
				convert(post,l);

				TreeNode *done = Change(root,temp,size,dat);

				x = 0;
				while(x != i){
			    freeValue(v[x]);
					x++;
				}
			}

			else{
				//Convert in-fix expression to post-fix
				Queue *post = infixToPostfix(Q,l,y);

				if (y==2){
					x = 0;
					while(x != i){
						freeValue(v[x]);
						x++;
					}
					continue;
				}

				//Process post-fix equation to produce result
				convert(post,l);

				x = 0;
				while(x != i){
			    freeValue(v[x]);
					x++;
				}
			}
	  }
	}
	printf("%d",dat);
	return 0;
}
