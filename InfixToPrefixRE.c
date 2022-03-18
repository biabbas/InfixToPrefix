
/******************************************************************************************
*   Visit https://github.com/the10minoverview/InfixToPrefix for all files.             *
*                                                                                          *
*                                                                                          *
*                                                                                          *
*                                                                                          *
*                                                                                          *                                                                                         
*   Created by B I                                                                                       *
******************************************************************************************/      
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    char a;
    struct node* ptr;
} * Node;
Node attach(Node f, Node l);
int ip(char x);
Node getNode(char x);
void prefix(char in[]);
int main(int argc, const char * argv[]) {
    char in[20];

    
    printf("Enter the valid expression:\n");
    scanf("%s",in);
    in[strlen(in)]='\0';

    prefix(in);

 
    return 0;
}
Node attach(Node f, Node l){
    Node temp = f;
    while(temp->ptr!= NULL)
    temp = temp->ptr;
    temp->ptr = l;
return f;
}
int ip(char x){
    switch (x) {
        case '#' :
        case '(' : return 0;
        case '+' :
        case '-' : return 1;
        case '*' :
        case '/' : return 2;
        case '$' :
        case '^' : return 3;
        default: return 0;
    }
}
Node getNode(char x){
    Node temp = (Node)malloc(sizeof(struct node));
    temp->a = x;
    temp->ptr = NULL;
    return temp;
}
void prefix(char in[]){
        int to = 0, tn = -1,i =0;
    Node OpStk[10], Stk[10],temp;
    OpStk[to] = getNode('#');
        while(in[i]!= '\0'){
        temp = getNode(in[i++]);
        
        if(isalnum(temp->a)){
            Stk[++tn] = temp;
        }
        else if (temp->a=='(')
          OpStk[++to]=temp;
        else if (temp->a==')'){
                while(OpStk[to]->a != '('){
                    Stk[tn-1] = attach(Stk[tn-1],Stk[tn]);
                    tn--;
                    Stk[tn] = attach(OpStk[to--],Stk[tn]);
                }
                free(temp);
                free(OpStk[to--]);
        
        }
        else{
            if(ip(OpStk[to]->a) < ip(temp->a))
                OpStk[++to] = temp;
            else{
                while(ip(OpStk[to]->a) >= ip(temp->a)){
                    Stk[tn-1] = attach(Stk[tn-1],Stk[tn]);
                    tn--;
                    Stk[tn] = attach(OpStk[to--],Stk[tn]);
                    
                }
                OpStk[++to] = temp;
            }
        }

    }
     while(to!=0){
       Stk[tn-1] = attach(Stk[tn-1],Stk[tn]);
       tn--;
       Stk[tn] = attach(OpStk[to],Stk[tn]);
       to--;
                    
    }
    free(OpStk[to]);
    printf("\n");
    temp = Stk[tn];
    while(temp!= NULL){
        printf("%c", temp->a);
       temp = temp->ptr;
    }
printf("\n");
}
