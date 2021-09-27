#include <iostream>
#include <stdlib.h>

const int START_SIZE = 10;
const int UNDEFINED = -1;
const int WRONG_VALUE = 12324567890;
const int DAMAGED_STACK = -888;

typedef struct {
	int max_size;
	int size;
	int* element;
} Stack;

bool is_damaged(int* error) {
	if (*error == DAMAGED_STACK) {
		printf("Stack is damaged. You can't access it. Please use other stack\n");
		return true;
	}
	return false;
}

void create(Stack* st) {
	st->max_size = START_SIZE;
	st->size = 0;
	st->element = (int*)calloc(st->max_size, sizeof(int));
}

void destruct(Stack* st) {
	for (int i = 0; i < st->max_size; ++i)
		st->element[i] = WRONG_VALUE;
	st->max_size = UNDEFINED;
	st->size = UNDEFINED;
	//free(st->element);
}

void push(Stack* st, int value, int* error) {
	if (is_damaged(error))
		return;
	if (st->size == st->max_size) {
		st->max_size *= 2;
		st->element = (int*)realloc(st->element, sizeof(int) * st->max_size);
	}
	st->element[st->size] = value;
	st->size++;
}

int pop(Stack* st, int* error = NULL) {
	if (is_damaged(error))
		return DAMAGED_STACK;
	if (st->size == 0) {
		printf("Error. Stack is empty. There is no elements.\n");
		*error = DAMAGED_STACK;
		return DAMAGED_STACK;
	}
	int value = st->element[--st->size];
	if (st->max_size > START_SIZE && st->max_size / st->size >= 4) {
		st->max_size /= 2;
		st->element = (int*)realloc(st->element, sizeof(int) * st->max_size / 2);
	}
	return value;
}

void clear(Stack* st, int* error) {
	if (is_damaged(error))
		return;
	st->max_size = START_SIZE;
	st->size = 0;
	st->element = NULL;
	st->element = (int*)realloc(st->element, st->max_size * sizeof(char));
}

int size(Stack* st) {
	return st->size;
}

int main() {
	Stack st;
	create(&st);
	int error = 0;
	for (int i = 0; i < 20; ++i) {
		push(&st, i, &error);
	}
	printf("Size of stack is %d\n", size(&st));
	for (int i = 0; i < 30; ++i) {
		printf("%d\n", pop(&st, &error));
		if (i % 10 == 0)
			printf("Size of stack is %d\n", size(&st));
	}
	clear(&st, &error);
	printf("Size of stack after clearing - %d", size(&st));
	destruct(&st);
	


	return 0;
}