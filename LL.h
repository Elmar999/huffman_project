#ifndef __LL_H_
#define __LL_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct LL_list{
    int val;
    char ch;
    struct LL_list *next;

}LL_list;


LL_list *read_file(LL_list *uns_list,char *filename);
LL_list *make_list_sorted(LL_list *uns_list,LL_list *sort_list);
LL_list *add_list(LL_list *uns_list,char ch);//adds to head if needed
LL_list *cons_list(LL_list *uns_list,char ch);
LL_list *search(LL_list *list,char ch);
void print_list(LL_list *unsorted_list);
LL_list *add_sorted_list(LL_list *sorted,char ch,int value);//adds if needed to add to middle or last
float find_entropy(LL_list *sorted_list);


#endif

