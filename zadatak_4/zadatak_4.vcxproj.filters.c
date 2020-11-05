#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define foreach(p,head) \
	for (Position p = head; p != NULL; p = p->next) 

struct _node;

typedef struct _node* Position;

typedef struct _node {
	int coef;
	size_t exp;
	Position next;
}Node;


Position create(int, size_t);
Position getLast(Position);
int insertAfter(Position, Position);
int printList(Position);
int sortOut(Position, Position, Position);
int unosIzDatoteke(Position, Position, char*);

int main(void) {

	Node pHead;
	pHead.next = NULL;

	Node qHead;
	qHead.next = NULL;

	Node rHead;
	rHead.next = NULL;


	unosIzDatoteke(&pHead, &qHead, "polinom.txt");
	
	insertAfter(getLast(&pHead), create(3,2));
	insertAfter(getLast(&pHead), create(7, 5));
	insertAfter(getLast(&pHead), create(2, 10));

	insertAfter(getLast(&qHead), create(1, 1));
	insertAfter(getLast(&qHead), create(2, 3));
	insertAfter(getLast(&qHead), create(9, 5));
	insertAfter(getLast(&qHead), create(8, 8));
	insertAfter(getLast(&qHead), create(-2, 10));

	sortOut(&pHead, &qHead, &rHead);

	printf("\np lista...");
	printList(&pHead);
	printf("\nq lista...");
	printList(&qHead);
	printf("\nr lista...");
	printList(&rHead);


	system("pause");

	return EXIT_SUCCESS;
}
int unosIzDatoteke(Position p, Position r, char* file) {
	FILE* fp = NULL;
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		puts("Neuspjesno otvaranje datoteke!");
		return -1;
	}
	/*int a, b, c, e;
	sscanf(fp, "%d %u %d %u %n", &coeff, &exp, &n);
	fp += n;
	);
	*/

}

int sortOut(Position p, Position q, Position r) {

	p = p->next;
	q = q->next;

	while (p->next != NULL && q->next != NULL) {

		if (p->exp == q->exp) {
			insertAfter(getLast(r), create((p->coef + q->coef), p->exp));
			p = p->next;
			q = q->next;
		}
		else if (p->exp > q->exp) {
			insertAfter(getLast(r), create((q->coef), q->exp));
			q = q->next;
		}
		else if (p->exp < q->exp) {
			insertAfter(getLast(r), create((p->coef), p->exp));
			p = p->next;
		}

	}

	if (p->next != NULL)
		foreach(g, p->next)
		insertAfter(getLast(r), create((p->coef), p->exp));

	else if (q->next != NULL)
		foreach(g, q->next)
		insertAfter(getLast(r), create((q->coef), q->exp));

	return 0;
}

Position getLast(Position head) {

	Position temp = NULL;

	foreach(p, head)
		temp = p;

	return temp;
}

int insertAfter(Position where, Position what) {
	what->next = where->next;
	where->next = what;
	return 0;
}

Position create(int k, size_t e) {

	Position el = NULL;

	el = (Position)malloc(sizeof(Node));

	if (NULL == el) {
		printf("Memory allocation failed!\r\n");
		return NULL;
	}

	el->coef = k;
	el->exp = e;
	el->next = NULL;

	return el;
}

int printList(Position head) {

	printf("\r\n\rLIST CONTENT:\r\n");

	foreach(p, head->next)
		printf(" %d^(%u) ->", p->coef, p->exp);

	puts(" NULL\n");

	return 0;
}