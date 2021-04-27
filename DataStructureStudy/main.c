#include "BSTree.h"
#include <stdio.h>


int main()
{
	BST_pointer ptr = RNodeInit(40);
	insert_node(ptr, 20);
	insert_node(ptr, 60);
	insert_node(ptr, 10);
	insert_node(ptr, 30);
	insert_node(ptr, 50);
	insert_node(ptr, 70);
	insert_node(ptr, 45);
	insert_node(ptr, 55);
	insert_node(ptr, 52);

	level_orderTraverseBST(ptr);
	putchar('\n');
	delete_node(ptr, 60);
	level_orderTraverseBST(ptr);
}