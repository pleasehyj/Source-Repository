#ifndef __SEMI_GENERIC_LQUEUE_H__
#define __SEMI_GENERIC_LQUEUE_H__

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
typedef struct lqueue{
	PtNode_t head;
	int dataSize;
	UdFreeNode_t free_node;
}LQu_t,*PtLQu_t;

/* Initialize a linked list */
extern PtLQu_t create_lqueue(int dataSize);

/* Return true if Q is empty */
extern int is_empty_lqueue(PtLQu_t Q);

/* Output a node in the queue, 
 * the space pointed by dataAddr must be enough to contain data*/
extern int out_lqueue(PtLQu_t Q,DataAddr_t dataAddr,UdFreeNode_t free_node);

/* Insert a node to the queue */
extern int in_lqueue(PtLQu_t Q,DataAddr_t dataAddr);

/* Show data in Q */
extern int show_lqueue(PtLQu_t Q,UdShowNode_t showNode);

/* Destroy Q */
extern int destroy_lqueue(PtLQu_t Q,UdFreeNode_t free_node);

/* Save Q to file */
extern int save_lqueue_to_file(PtLQu_t Q,const char* filepath,UdFreeNode_t free_node);

/* Load Q from file */
extern int load_lqueue_from_file(PtLQu_t Q,const char* filepath);

#endif //__SEMI_GENERIC_LQUEUE_H__











































































