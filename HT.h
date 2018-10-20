#ifndef __HT_H_
#define __HT_H_

#include<stdio.h>
#include<stdlib.h>
#include"LL.h"

typedef struct H_Node{ // tree node
    int val;
    char ch;
    struct H_Node *left;
    struct H_Node *right;
} H_Node;


typedef struct Hl_Node { // list node
    struct H_Node *tree;
    struct Hl_Node *next;
}Hl_Node;


Hl_Node *construct_Hlnode(Hl_Node *list,int val,char ch);
Hl_Node *sorted_list(LL_list *sorted , Hl_Node *sort);
Hl_Node *loop_sorted_list(LL_list *sorted_list ,Hl_Node *huf_list);
Hl_Node *add_huff_list(Hl_Node *list , int val, int ch);
Hl_Node *Huf_list(LL_list *sorted_list , Hl_Node *Hl_sorted);
void Print_Hlist(Hl_Node *list);
Hl_Node *Make_huf_tree( Hl_Node *tree);
Hl_Node *sort_treelist(Hl_Node *tree);
Hl_Node *add_to_head(Hl_Node *tree,Hl_Node *unslist);
Hl_Node *add_middle_or_last(Hl_Node *tree,Hl_Node *unslist);
void Print_Tree(H_Node *list_nodes);
void Find_node(H_Node *list_nodes,char c );


#endif

