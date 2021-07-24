#include "sorting_bst.h"
#include <stdio.h>
/*
There are no negative numbers in our sample so -1s represent empty nodes
This function are required for initialization of a tree
*/
void nodation(int bst[], int size)
{
	for (int i = 0; i < size; i++)
	{
		bst[i] = -1; // Empty nodes represented as -1s
	}
}
/*
Clears all -1s
tmp_array will be inorder traversal of bst
*/
void bst_to_array(int bst[], int tmp_array[])
{
	int tmp_arr_ind = 0;
	for (int i = 0; i < 16383; i++)
	{
		if (bst[i] != -1)
		{
			tmp_array[tmp_arr_ind] = bst[i];
			tmp_arr_ind++;
		}
	}

}
/*
When the tree height goes to 14(any deepest child node filled) we need to balance the tree
This function will balance the tree by re-inserting from sorted array
Re-insertion order is: preorder traversal
*/
void balance_bst(int bst[])
{
	int tmp_array[1000];
	nodation(tmp_array, 1000);
	bst_to_array(bst, tmp_array);
	nodation(bst, 16383);
	fill_bst(bst, tmp_array, 0, 1000);
}

/*
Recursively insert elements
Recursion will perform for bst
*/
void insert_element(int e, int bst[], int lb, int ub)
{
	int sub_size = ub - lb;
	int sub_bst_mid_ind = (sub_size / 2) + lb;
	int sub_root = bst[sub_bst_mid_ind];
	if (sub_bst_mid_ind % 2 == 0) // When height goes to 14
	{
		balance_bst(bst);
		insert_element(e, bst, 0, 16383);
	}
	else if (sub_root == -1) // Node empty
	{
		bst[sub_bst_mid_ind] = e;
	}
	else if (e < sub_root) // Element smaller than current sub-root
	{
		insert_element(e, bst, lb, sub_bst_mid_ind);
	}
	else if (e > sub_root) // Element bigger than current sub-root
	{
		insert_element(e, bst, sub_bst_mid_ind + 1, ub);
	}
}

/*
Fills the bst with help of insert_element function
Recursion will perform for numbers array not bst
*/
void fill_bst(int bst[], int numbers[], int lb, int ub)
{
	int bst_size = 16383;
	int sub_size = ub - lb;
	if (sub_size == 0) // Recursion must end when trimmed array'size 0(like array == NULL)
	{
		return;
	}
	int sub_mid_ind = (sub_size / 2) + lb;
	int e = numbers[sub_mid_ind];
	insert_element(e, bst, 0, bst_size);
	fill_bst(bst, numbers, lb, sub_mid_ind);
	fill_bst(bst, numbers, sub_mid_ind + 1, ub);
}
/*
A simple driver function
Creates final balanced bst for numbers array
*/
void finalize_bst(int bst[], int numbers[])
{
	int size = 16383;
	nodation(bst, size);
	fill_bst(bst, numbers, 0, 1000);
}


