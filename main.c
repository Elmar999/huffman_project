#include<string.h>
#include <math.h>
#include "LL.h"
#include "HT.h"

int getCode(char character, H_Node* hTree, char* code);
void clearString(char* string);



int main(){
    
    //read from file to list (unsorted)
    LL_list *unsorted_list = NULL;
    char *filename = "test1.txt";
    unsorted_list = read_file(unsorted_list,filename);
    printf("unsorted-list - >");
    print_list(unsorted_list);
    printf("\n");
    //--------------------------

    //copy from unsorted to sorted list
    printf("sorted-list - >");
    LL_list *sorted_list = NULL;
    sorted_list = make_list_sorted(unsorted_list,sorted_list);
    print_list(sorted_list);

    //---------------------------

    //find entropy
    float entrop = find_entropy(sorted_list);
    printf("\nEntropy of a file is : %f\nHufman_sorted_list: ",entrop);

    //----------------------------

    //HUFMANN PART  
    Hl_Node *Hl_sorted = NULL;//SORTED LIST
    Hl_sorted = Huf_list(sorted_list , Hl_sorted);
    Print_Hlist(Hl_sorted);
    printf("\n");
    

    Hl_Node *make_tree = NULL;
    make_tree = Make_huf_tree(Hl_sorted);
    Hl_Node *temp = make_tree;

	char code[256]={'\0'};
    
    unsigned char buf;
    unsigned char tmp;
    int count = 0;
    int check_bytes = 0;
    int numOfRemainBytes = 0;
    int nextChar = 0;

    FILE *wrt = fopen("compressedFile","wb");
    Hl_Node *temporalList = Hl_sorted;


    //char tsf[]={'1','1','2','3'};
    //fwrite(&tsf,1,1,wrt);


    // --------- write dictionary to file ---------
    for(;temporalList;temporalList=temporalList->next){
        fwrite(&temporalList->tree->ch,1,1,wrt);
        getCode(temporalList->tree->ch,make_tree->tree,code);
        char tmp[strlen(code)];
        strcpy(tmp,code);
        fwrite(&tmp,strlen(tmp),1,wrt);
        clearString(code);

    }



    // ------------- shifting part ----------------
    for(;Hl_sorted;Hl_sorted=Hl_sorted->next){
        getCode(Hl_sorted->tree->ch,make_tree->tree,code);
        int k = strlen(code);
        printf("[%c] - %s\n",Hl_sorted->tree->ch,code);
        ////shifting part 
        for(int i=0,j=7;i<k;i++,j--){
            if(check_bytes == 8){
                //printf("final result for 8 bits is %d --- %d\n",buf,i);
                count = 0; j = 7; check_bytes = 0; 
            //write buf to file
            fwrite(&buf,1,1,wrt);
            buf = 0;
            //make buf empty
            //continue
        }
            if(count == 1){
                if(nextChar == 1){
                    j = 8 - check_bytes-1;  nextChar = 0;
                }
                tmp=code[i] - '0';
                tmp=tmp << j;
                buf = buf|tmp;  check_bytes++;
            }
            else{
                buf = code[i] - '0';
                buf = buf<<j; count = 1;  check_bytes++;
            }

            if(Hl_sorted->next == NULL){
               // printf("final result for first 8 bits is %d --- %d\n",buf,i);
                 fwrite(&buf,1,1,wrt); break;
            }

        }
        nextChar = 1;
        clearString(code);
    }

    return 0;


}



int getCode(char character, H_Node* hTree, char* code)
{
	if(hTree==NULL)
		return 0;
	if(hTree->left==NULL && hTree->ch==character) // or hTree->right==NULL
		return 1;
	if(getCode(character, hTree->left, code+1))
	{
		code[0]='0';
		return 1;
	}
	else if(getCode(character, hTree->right, code+1))
	{
		code[0]='1';
		return 1;
	}
	else
		return 0;
}

void clearString(char* string)
{
	for(unsigned int i=0; string[i]; i++)
		string[i]='\0';
}


