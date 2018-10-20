#include"LL.h"
#include<math.h>


//-------read to unsorted list-------
LL_list *read_file(LL_list *uns_list,char *filename){
    FILE *fp=fopen(filename,"r");

    char c;
    
    while(fscanf(fp,"%c",&c) != EOF){
        if(uns_list == NULL){
            uns_list = cons_list(uns_list,c);
        }
        else{
            uns_list = search(uns_list,c);
        }
    }
    return uns_list;
}

//-----copy from unsorted to sorted-----
LL_list *make_list_sorted(LL_list *unsorted,LL_list *sorted){
        while(unsorted){
            if(sorted == NULL)
                sorted = cons_list(sorted,unsorted->ch);
            else{
                if(unsorted->val <= sorted->val)
                    sorted = add_list(sorted,unsorted->ch);
                else 
                    sorted = add_sorted_list(sorted,unsorted->ch,unsorted->val);
            }
            unsorted = unsorted->next;
        }
        return sorted;
}

//-----CONSTRUCT LIST------
LL_list *cons_list(LL_list *list,char ch){
    list = (LL_list*)malloc(sizeof(LL_list));
    list->ch = ch;
    list->val = 1;
    list->next = NULL;

    return list;

}

//-----SEARCH IF CHARACTER EXIST IN THE LIST , IF NOT ADD TO HEAD...(WILL BE UNSORTED LIST)
LL_list *search(LL_list *list,char c){
    LL_list *temp = list;
    while(list){
        if(list->ch == c){
            list->val++;
            return temp;
        }
        else
            list = list->next;
    }
        temp = add_list(temp,c);
        return temp;

}

//-------ADDS TO HEAD-----
LL_list *add_list(LL_list *list , char ch){
    LL_list *temp = (LL_list*)malloc(sizeof(LL_list));
    temp->ch=ch;
    temp->val=1;
    temp->next=list;
    list = temp;
    return list;

}

// ------ PRINTS LIST -------
void print_list(LL_list *list){
    LL_list *temp = list;
    while(temp){
        printf("[%c,%d]->",temp->ch,temp->val);
        temp = temp->next;
    }
}

//---------COPIES FROM UNSORTED LIST TO NEW SORTED LIST
LL_list *add_sorted_list(LL_list *sorted,char c,int value){
    LL_list *temp = sorted;
    while(temp){
        //------IF NEEDED TO ADD TO LAST-----
        if( temp->next == NULL){
            temp->next=(LL_list*)malloc(sizeof(LL_list));
            temp->next->ch = c;
            temp->next->val = value;
            temp->next->next = NULL;
            return sorted;
        }
        //-----IF NEEDED TO ADD TO MIDDLE-----
        else if(value <= temp->next->val) {
            LL_list *temp2 = temp->next;            
            temp->next = (LL_list*)malloc(sizeof(LL_list));
            temp->next->ch = c;
            temp->next->val=value;
            temp->next->next = temp2;
            return sorted;
        }
        temp = temp->next;
    }
}


//------ENTROPY------

float find_entropy(LL_list *sorted){
    float numb_of_elements = 0;
    LL_list *temp = sorted;
    while(temp){
        numb_of_elements = numb_of_elements +  temp->val;
        temp = temp->next;
    }

    temp = sorted;
    float entrop = 0;
    while(temp){
        entrop = entrop - (float)temp->val/(numb_of_elements)*log2((float)temp->val/(numb_of_elements));     
        temp = temp->next;
    }
    return entrop;
}


