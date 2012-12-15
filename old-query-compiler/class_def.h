/*
 * trial program to see how virtual inheritance works.
 */

#include <stdio.h>

#define NAME_MAX 20

class person {
	char *name;

public:
	person *father;
	person *mother;

	char name[NAME_MAX];

	//void print_gender();
	person();
	void print_name();
	void print_parents();
};

class male {
public:
	void print_gender();
	//void print_name();
};

class female {
public:
	void print_gender();
	//void print_name();
};


void male::print_gender() {
	printf("Male\n");
}

void female::print_gender() {
	printf("Female\n");
}

void person::person() {
	father = NULL;
	mother = NULL;
}

void person::print_name() {
	printf("%s\n", name);
}

void person::print_parents() {
	if(father != NULL) {
		printf("Father of \n");
		print_name();
		printf("is\n");
		father->print_name();

		printf("Mother of \n");
		print_name();
		printf("is\n");
		mother->print_name();
	}
}