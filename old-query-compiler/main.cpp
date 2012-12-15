#include <stdio.h>
#include <iostream>

#include "include/exp_tree.h"
#include "include/query_code.h"

int main()
{

	build_exp_tree();
	printf("%s:%d\n", __func__,__LINE__);

	generate_query_code();

	return 0;
}