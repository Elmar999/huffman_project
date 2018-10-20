#include"HT.h"
#include"LL.h"

Hl_Node *construct_Hlnode(Hl_Node *list,int val , char ch){
    list = (Hl_Node*)malloc(sizeof(Hl_Node));
    list->tree = (H_Node*)malloc(sizeof(H_Node));
    list->tree->val = val;
    list->tree->ch = ch;
    list->tree->left = NULL;
    list->tree->right = NULL;
    list->next = NULL;

    return list;
}

//--------------MAKES HUFMANN SORTED LIST ------------
Hl_Node *Huf_list(LL_list *sorted_list , Hl_Node *Hl_sorted){
    while(sorted_list){
        if(Hl_sorted == NULL){
            Hl_sorted = construct_Hlnode(Hl_sorted,sorted_list->val,sorted_list->ch);
        }
        else {
            Hl_sorted = add_huff_list(Hl_sorted,sorted_list->val , sorted_list->ch);        
        }

        sorted_list = sorted_list->next;
    }
    return Hl_sorted;
}


//ADD TO LAST IN HUFMAN LIST
Hl_Node *add_huff_list(Hl_Node *list , int val, int ch){
    Hl_Node *temp = list;
    while(temp){
        if(temp->next == NULL){
            temp->next = construct_Hlnode(temp->next,val,ch);
            return list;
        }
        temp = temp->next;
    }

    return list;
}

void Print_Hlist(Hl_Node *list){
    while(list){
        printf("[%d,%c]-> ",list->tree->val,list->tree->ch);
        list=list->next;
    }

}

Hl_Node *Make_huf_tree(Hl_Node *tree){
    Hl_Node *temp = tree;
    while(temp){
        if(temp->next == NULL)
            return tree;
        Hl_Node *new = (Hl_Node*)malloc(sizeof(Hl_Node));
        new->tree = (H_Node*)malloc(sizeof(H_Node));
        new->tree->val = temp->tree->val + temp->next->tree->val;
        new->tree->ch = '$';
        new->tree->left = temp->tree;
        new->tree->right = temp->next->tree;
        temp = temp->next->next;
        new->next = temp;
        tree = new;
        temp = tree;
        //Print_Hlist(tree);
        tree = sort_treelist(tree);
        temp = tree;
       // printf("\nafter sorting ... : ");
        Print_Hlist(tree);
        printf("\n");
    }
    return tree;
}


/*
Hl_Node *sort_treelist(Hl_Node *unslist){
    int count = 0;
    Hl_Node *temp = unslist;
    Hl_Node *temp2 = temp->next;
    while(temp){
        if(temp2 == NULL){
            return unslist;
        }
        if(temp->tree->val > temp2->tree->val) {
                temp->next = temp2->next;
                temp2->next = temp;
                if(count == 0){
                    unslist = temp2;
                    count = 1;
                }
                temp2 = temp->next;
        }
        else 
            return unslist;
    }
    return unslist;
}
*/

Hl_Node *sort_treelist(Hl_Node *unslist){
    Hl_Node *sort_list = NULL;
    while(unslist){
        if(sort_list == NULL){
                  sort_list = (Hl_Node*)malloc(sizeof(Hl_Node));
                  sort_list->tree = (H_Node*)malloc(sizeof(H_Node));
                  sort_list->tree->val = unslist->tree->val;
                  sort_list->tree->ch = unslist->tree->ch;
                  sort_list->tree->left = unslist->tree->left;
                  sort_list->tree->right = unslist->tree->right;
                  sort_list->next = NULL;
        }
        else{
            if(unslist->tree->val < sort_list->tree->val)
                sort_list = add_to_head(sort_list,unslist);
            else
                sort_list = add_middle_or_last(sort_list,unslist);
        }

        unslist = unslist->next;
    }
return sort_list;
}



Hl_Node *add_to_head(Hl_Node *tree,Hl_Node *unslist){
    Hl_Node *temp = (Hl_Node*)malloc(sizeof(Hl_Node));
    temp->tree = (H_Node*)malloc(sizeof(H_Node));
    temp->tree->val = unslist->tree->val;
    temp->tree->ch = unslist->tree->ch;
    temp->tree->left = unslist->tree->left;
    temp->tree->right = unslist->tree->right; 
    temp->next = tree;
    tree = temp;
    return tree;
}

Hl_Node *add_middle_or_last(Hl_Node *tree,Hl_Node *unslist){
    Hl_Node *temp = tree;
    while(temp){
        //------IF NEEDED TO ADD TO LAST-----
        if(temp->next == NULL){
            temp->next = (Hl_Node*)malloc(sizeof(Hl_Node));
            temp->next->tree = (H_Node*)malloc(sizeof(H_Node));
            temp->next->tree->ch = unslist->tree->ch;
            temp->next->tree->val = unslist->tree->val;
            temp->next->tree->left = unslist->tree->left;
            temp->next->tree->right = unslist->tree->right; 
            temp->next->next = NULL;
            return tree;
        }
        //-----IF NEEDED TO ADD TO MIDDLE-----
        else if(unslist->tree->val <= temp->next->tree->val){
            Hl_Node *temp2 = temp->next;
            temp->next = (Hl_Node*)malloc(sizeof(Hl_Node));
            temp->next->tree = (H_Node*)malloc(sizeof(H_Node));
            temp->next->tree->val = unslist->tree->val;
            temp->next->tree->ch = unslist->tree->ch;
            temp->next->tree->left = unslist->tree->left;
            temp->next->tree->right = unslist->tree->right; 
            temp->next->next = temp2;
            return tree;          
        }
    temp=temp->next;
    }
}

void Print_Tree(H_Node *list_nodes){
    if(list_nodes == NULL){
        return;
    }
    Print_Tree(list_nodes->left);
    printf("%c  ",list_nodes->ch);
    Print_Tree(list_nodes->right);
    return;

}

int i=0;
void Find_node(H_Node *list_nodes,char c){
    if(list_nodes == NULL)
        return;
    if(list_nodes->ch == c){
        printf(" tapildi %c\n" , list_nodes->ch);  
        return ;
    }
    Find_node(list_nodes->left,c);
    Find_node(list_nodes->right,c);

    return ;

}




