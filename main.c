#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct{
    char data[25];
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *newNode(char *data){
//Allocate Memory For New Node
    Node *node = (Node*)malloc(sizeof(Node));
//Assign Date To This Node
    strcpy(node -> data,data);
//Iniatialize Left & Right Children as NULL
    node -> left = NULL;
    node -> right = NULL;
    node -> parent = NULL;

    return node;
};

Node *insert(Node *root,char *data){
    if(root == NULL)
    {
        root = newNode(data);
    }
    else
    {
        Node *val;
        if(strcmp(data,root -> data) > 0)
        {
            val = insert(root -> right,data);
            root -> right = val;
            val -> parent = root;
        }
        else if(strcmp(data,root -> data) < 0)
        {
            val = insert(root -> left,data);
            root -> left = val;
            val -> parent = root;
        }
        return root;
    }

}

Node *read(Node *root){
    FILE *p;
    char data[30];
    p = fopen("random5.txt","r");
    if(p == NULL)
    {
        printf("Error in Reading The File");
    }
    else
    {
        while(!feof(p))
        {
            fscanf(p,"%s",data);
            root = insert(root,data);

        }
    }
    fclose(p);
    return root;
}

Node *front(Node *root){

    assert(root != NULL);
    Node *p = root;
    while(p -> left != NULL)
        p = p -> left;
    return p;
}

Node *back(Node *root){
    assert(root != NULL);
    Node *p = root;
    while(p -> right != NULL)
        p = p -> right;
    return p;
}

Node *search(Node *ptr,char *val){
    if(ptr == NULL)
        return ptr;
    else
    {
        if(strcmp(val,ptr -> data) == 0)
        {
            return ptr;
        }
        else if(strcmp(val,ptr -> data) < 0)
        {
            if(ptr -> left == NULL)
                return ptr;
            return search(ptr -> left,val);
        }
        else if(strcmp(val,ptr -> data) > 0)
        {
            if(ptr -> right == NULL)
                return ptr;
            return search(ptr -> right,val);

        }
    }
}

Node *success(Node *root,Node *node){

    if( node -> right != NULL )
        return front(node -> right);

    Node *p = node -> parent;

    while(node == p -> right)
    {
        node = p;
        p = p -> parent;
    }

    return p;
}

Node *predecess(Node *root,Node *node){
    if( node -> left != NULL )
        return back(node -> left);

    Node *p = node -> parent;

    while(node == p -> left)
    {
        node = p;
        p = p -> parent;
    }

    return p;
}

void check(Node *root,char *val){
Node *t , *s , *p1;
Node *p = search(root,val);
 if(strcmp(p -> data, val) == 0)
    {
        printf(" *** %s *** ",p -> data);
        printf("Correct Word\n");
    }
     else
    {
        Node *t = p;
        s = success(root, t);
        p1 = predecess(root, t);
        printf("*** %s ***  %s,%s,%s\n",val,t -> data,s -> data,p1 -> data);
    }

}

void tokenize(Node *root,char *value){
    char delimetter[] = " ";
    char *val = strtok(value,delimetter);
    while(val != NULL)
    {
        check(root,val);
        val = strtok(NULL,delimetter);
    }
}

Node *next(Node *node,char *d){

    if(node == NULL)
    {
        return d;
    }
    else if(d > node -> data)
    {

        if(node -> right != NULL)
        {
            return front(node -> right);
        }
    }
    else if(d < node -> data)
    {
        if(node -> left != NULL)
        {
            return back(node -> left);
        }
    }
}

int size(Node *root){
    return(root == NULL)?0:
          1 + size(root -> left) + size(root -> right);

}

int maxs(int x,int y){
    if(x > y)
    {
        return x;
    }
    else
        return y;

}

int height (Node *root){
    return(root == NULL)?-1:
          1 + maxs(height(root -> left),height(root -> right));
}

int main(){
    Node *root = NULL;
    char *val[40];
    root = read(root);
    printf("height = %d",height(root));
    printf("\nsize = %d",size(root));

     while(1){
        printf("\n\nEnter Input:\n");
        gets(val);
        tokenize(root,val);
    }
    return 0;
}
