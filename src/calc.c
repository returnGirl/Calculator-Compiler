/**
 * @author 王镇佳
 * @studentId 14331275
 * @description LL(1)文法实现的简易计算器
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//256 is END, 257 is REAL. Other Symbol is its ASCII value.
enum Tag { END = 256, REAL };

struct token {
	int tag;
	double val;  // store the token's value.
};

typedef struct token Token;

char inputWord = ' ';
Token ahead;

Token getOneToken(void);
void getNextToken(void);
double expr(void);
double expr_(void); // means E'
double term(void);
double term_(void); // means T'
double factor(void);
void errorHandler(void);

int main() {

  while (1) {

    printf("(Your expression) >> ");
    // get First Token as ahead
    ahead = getOneToken();
    // from CFG's Start E
    double calc = expr();

    printf("(Answer) == %.2lf\n", calc);

  }

}


Token getOneToken(void) {
	Token tok = { END, 0 };

  while (inputWord != '\n' && isspace(inputWord)) {
    inputWord = getchar();
  }

	if (inputWord == '\n') {
    inputWord = ' ';
    return tok;
  }

  // if the input is digit
	if (isdigit(inputWord) || inputWord == '.') {

		for (tok.val = 0; isdigit(inputWord); inputWord = getchar())
			tok.val = 10 * tok.val + (inputWord - '0');

    // handle the decimal point input.
    if (inputWord == '.') {
			double decplace = 1;
			while (isdigit(inputWord = getchar()))
				tok.val += (inputWord - '0') * (decplace /= 10);
		}

		tok.tag = REAL;
		return tok;
	}
	// else if the input is SYMBOL.
	// tok.tag will store its ASCII value.
	tok.tag = inputWord;
	inputWord = ' ';
	return tok;
}

// E -> TE’
double expr(void) {

	switch (ahead.tag) {
		case REAL:
		case '(':
		case '-':
			return term() + expr_(); // because E' is + or -, so here we need to add it's value.
		default:
	    errorHandler();
			return 0;
	}

}

// E’ -> + TE’ | -TE’ | ϵ
double expr_(void) {
	int tag = ahead.tag;

	switch (tag) {
		case ')':
		case END:
			return 0;

		case '+':
		case '-':
			getNextToken();
			return ((tag == '+') ? term() : -term()) + expr_(); // also use add here.
		default:
	    errorHandler();
			return 0;
	}

}

// F -> -F | R | (E)
double factor(void) {
	int tag = ahead.tag;
	double val = ahead.val;

	if (tag != END) getNextToken(); // F is finished, need to input next token.

	switch (tag) {
		case REAL:
			return val;
		case '(':
			val = expr();
			getNextToken();
			return val;
		case '-':
			return -factor();
		default:
	    errorHandler();
			return 0;
	}

}

// T -> FT’
double term(void) {

	switch (ahead.tag) {
		case REAL:
		case '(':
		case '-':
			return factor() * term_(); // because T' is * or /, so here we need to multiply it's value.
		default:
	    errorHandler();
			return 0;
	}

}

// T’ -> * FT’ | / FT’ | ϵ
double term_(void) {
	int tag = ahead.tag;

	switch (tag) {
		case '+':
		case '-':
		case ')':
		case END:
			return 1;	

		case '*':
		case '/':
			getNextToken();
			return ((tag == '*') ? factor() : 1 / factor()) * term_(); // also use multiply here.
		default:
	    errorHandler();
			return 1;
	}

}

void getNextToken(void) {
	ahead = getOneToken();
}

void errorHandler(void) {
  fprintf(stderr, "Can not match your expr, please check your input\n");
  exit(0);
}
