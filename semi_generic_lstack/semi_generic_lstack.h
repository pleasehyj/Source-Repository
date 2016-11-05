#ifndef __SEMI_GENERIC_lstack_H__
#define __SEMI_GENERIC_lstack_H__

/* Define the address of data */
typedef void* DataAddr_t;

/* Encapsulate node */
struct Node;
typedef struct Node* PtNode_t;
//struct Node_t;
typedef struct Node{
	DataAddr_t dataAddr;
	PtNode_t next;
}Node_t;

/* User-defined fucntions */
/* User-defined Node-Compare function */
typedef int (*UdCmp_t)(DataAddr_t,DataAddr_t);
/* User-defined Node-Free function */
typedef int (*UdFreeNode_t)(PtNode_t);
/* User-defined Node-Show function */
typedef int (*UdShowNode_t)(PtNode_t);

/* Encapsulate a linked list */
typedef struct lstack{
	PtNode_t head;
	int dataSize;
	UdFreeNode_t free_node;
}LStack_t,*PtLStack_t;

/* Initialize a linked list */
extern PtLStack_t create_lstack(int dataSize);

/* Return true if S is empty */
extern int is_empty_lstack(PtLStack_t S);

/* Insert a node at the head */
extern int push_lstack(PtLStack_t S,DataAddr_t dataAddr);

/* Delete the node at the head, 
 * the space pointed by dataAddr must be enough to contain data*/
extern int pop_lstack(PtLStack_t S,DataAddr_t dataAddr,UdFreeNode_t free_node);

/* Show data in S */
extern int show_lstack(PtLStack_t S,UdShowNode_t showNode);

/* Destroy S */
extern int destroy_lstack(PtLStack_t S,UdFreeNode_t free_node);

/* Save S to file */
extern int save_lstack_to_file(PtLStack_t S,const char* filepath,UdFreeNode_t free_node);

/* Load S from file */
extern int load_lstack_from_file(PtLStack_t S,const char* filepath);

#endif //__SEMI_GENERIC_lstack_H___











































































