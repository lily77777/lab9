/*
 * binary.c
 *
 *  Created on: 2020. 5. 19.
 *      Author: user
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
void freeB(Node* ptr);

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("sunyilin 2016039102 software");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{//printf("daoda");
	if (ptr) {
		//printf("daoda");
		inorderTraversal(ptr->left);//lvr
		printf("[%d]  ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf("[%d]  ",ptr->key);//vrl
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);//lrv
		postorderTraversal(ptr->right);
		printf("[%d]  ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* ptr=NULL;
	Node* inkey = (Node*)malloc(sizeof(Node));
	inkey->key = key;
	inkey->left = inkey->right = NULL;
	//head=head->left;
	if (head->left == NULL) {
		head->left = inkey;
		return 0;
	}
	ptr=head=head->left;;
	while (head) {
		if(key== head->key) {
			printf("이미 있습니다");
			return 0;
		}
		if (key > head->key) {
			ptr=head;
			head = head->right;//오른쪽>root
		}
		else {//왼쪽<root
			ptr=head;
			head = head->left;
		}
	}
	if(key== ptr->key) {
		printf("이미 있습니다");
	}
	if (key > ptr->key) {
		//ptr=head;
		ptr->right=inkey;//오른쪽>root
	}
	else {//왼쪽<root
		ptr->left=inkey;
	}
	//head->left=inkey;
	return 0;
}

int deleteLeafNode(Node* head, int key)
{

	Node*ptr;
	Node*ptr1=NULL;

	if (head->left->key == key) {
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}
	//head=head->left;
	while (head->left) {
		if (head->left->key == key) {
			if(head->left->left==NULL&&head->left->right==NULL){
				free(head->left);
				head->left=NULL;

			}
			else if(head->left->left==NULL&&head->left->right!=NULL){
//right child 있음
				ptr=head->left;
				head->left=head->left->right;
				free(ptr);
				ptr=NULL;
			}
			else if(head->left->right==NULL&&head->left->left!=NULL){
//left child 있음
				ptr=head->left;
				head->left=head->left->left;
				free(ptr);
				ptr=NULL;
			}
			else if(head->left->right!=NULL&&head->left->left!=NULL){
//양쪽 다 있음
				ptr=head->left->right;
				head=head->left;
				while(ptr){

					//ptr2=ptr1;
					ptr1=ptr;

					ptr=ptr->left;
				}

				head->key=ptr1->key;

				free(ptr1);
				ptr1=NULL;

			}
			return 0;
		}

		head = head->left;//left node
	}
	printf("\n Cannot find the node [%d]\n", key);
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (!ptr) {
		return NULL;
	}
	if (key == ptr->key) {
		return ptr;
	}
	if (key < ptr->key )
		return searchRecursive(ptr->left, key);//search recursive

	return searchRecursive(ptr->right, key);//search recursive

}

Node* searchIterative(Node* head, int key)
{
	head =head->left;
	while (head) {
		if (key == head->key) {
			return head;
		}
		if (key < head->key) {
			head = head->left;//왼쪽<root iterative
		}
		else {
			head = head->right;//오른쪽<root  iterative
		}
	}
	return NULL;
}

int freeBST(Node* head)
{
	if (head->left == NULL) {
		printf("memories=NULL");
		free(head);
		return 0;
	}
	else  {
		freeB(head->left);//postorder Recursive
		free(head);
	}
	return 0;
}
void freeB(Node* ptr) {
	if (ptr) {

		freeB(ptr->left);
		freeB(ptr->right);
		free(ptr);
	}
}


