//Sofya_Sellak
#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct _node{
    char key;
    struct _node* left;
    struct _node* right;
}node;

node* atree(char* postfix);
void transfer(char* infix, char* postfix);
void inorder(node* root);
void preorder(node* root);
void postorder(node* root);
int priority(char top, char c);
void menu(void);


int main(){
node*root;
char input[MAX];
char infix[MAX];
char postfix[MAX];
int i,j,el;

menu();
scanf("%d",&el);

 do
  {

  switch(el){
  case 1:
    printf("enter inorder expression\n");
    gets(input);
    j = 0;
    for(i = 0;i< strlen(input);i++)
     {
        if(input[i] != ' ')
          {
            infix[j] = input[i];
            j++;
           }
        infix[j]= '\0';
     }
    transfer(infix, postfix);
    root= atree(postfix);

      break;
  case 2:
      inorder(root);
      printf("\n");

      break;
  case 3:
      preorder(root);
      printf("\n");

      break;
  case 4:
      postorder(root);
      printf("\n");

      break;
    default :
    printf("Error\n");
  }
  menu();
  scanf("%d",&el);
  } while(el!= 5);
       printf("End\n");
}

void transfer (char* infix, char* postfix){
    char operators[MAX];
    int top = -1;
    int i, j = 0;

    for(i = 0;i< strlen(infix);i++){
        if( isalpha (infix[i]) != 0){
            postfix[j++] = infix[i];
        }
        else{
            if(top == -1 || priority(operators[top],infix[i]) == 1){
                operators[++top] = infix[i];
            }
            else if(priority(operators[top],infix[i]) == 2 || priority(operators[top],infix[i]) ==  0){
                while(priority(operators[top],infix[i]) != 1){
                    postfix[j++] = operators[top--];
                    if(top == -1)
                        break;
                }
                operators[++top] = infix[i];
            }
        }
    }
    while(top != -1){
        postfix[j++] = operators[top--];
    }
    postfix[j] = '\0';
}

int priority(char top, char c){
    if(top == '-' || top == '+'){
       if(c == '*' || c == '/'){
        return 1;
       }
    }
    if(top == '*' || top == '/'){
       if (c == '+' || c == '-'){
         return 2;
       }
    }
    else{
         return 0;
        }
 }

node* atree(char* postfix){
    node* operators[MAX];
    node *new1,*ptr1, *ptr2;
    int top = -1, i;

    for(i = 0;i< strlen(postfix);i++){
        if(isalpha (postfix[i]) != 0){
            new1 = (node*)malloc(sizeof(node));
            new1->key = postfix[i];
            new1->left = NULL;
            new1->right = NULL;
            operators[++top] = new1;
        }
        else{
            new1 = (node*)malloc(sizeof(node));
            ptr1 = (node*)malloc(sizeof(node));
            ptr2 = (node*)malloc(sizeof(node));
            ptr1 = operators[top--];
            ptr2 = operators[top--];
            new1->key = postfix[i];
            new1->left = ptr2;
            new1->right = ptr1;
            operators[++top] = new1;
        }
    }
    return(new1);
}


void inorder(node* root){
    if(root == NULL)
        return;
    else{
        inorder(root->left);
        printf("%c", root->key);
        inorder(root->right);
    }
}


void preorder(node* root){
    if(root == NULL)
        return;
    else{
        printf("%c", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}


void postorder(node* root){
    if(root == NULL)
        return;
    else{
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->key);
    }
}

void menu(void){
printf("***************Menu*************\n");
printf("1- Enter Inorder Expression\n");
printf("2- 'Inorder' traversal\n");
printf("3- 'Preorder' traversal\n");
printf("4- 'Postorder' traversal\n");
printf("5- Quit\n");
}
