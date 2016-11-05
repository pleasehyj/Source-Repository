#ifndef __SEMI_GENERIC_LINK_LIST_H__
#define __SEMI_GENERIC_LINK_LIST_H__

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
typedef struct LList{
	PtNode_t head;
	int dataSize;
	UdFreeNode_t free_node;
}LList_t,*PtLList_t;

/* Initialize a linked list */
//extern PtLList_t create_llist(int dataSize,UdFreeNode_t free_node);
extern PtLList_t create_llist(int dataSize);

/* Return true if L is empty */
extern int is_empty_llist(PtLList_t L);

/* Return true if pos i*/

/* Insert a node at the head */
extern int insert_head_llist(PtLList_t L,DataAddr_t dataAddr);

/* Delete the node at the head, 
 * the space pointed by dataAddr must be enough to contain data*/
extern int delete_head_llist(PtLList_t L,DataAddr_t dataAddr,UdFreeNode_t free_node);

/* Return the address of the node at tail */
extern PtNode_t find_tail_llist(PtLList_t L/*,DataAddr_t dataAddr,UdCmp_t is_equal_node*/);

/* Insert a node at the tail */
extern int insert_tail_llist(PtLList_t L,DataAddr_t dataAddr);

/* Return the address of the previous node at tail */
extern PtNode_t find_pretail_llist(PtLList_t L);

/* Delete the node at the tail */
extern int delete_tail_llist(PtLList_t L,DataAddr_t dataAddr,UdFreeNode_t free_node);

/* Return the address of the node containing the data given */
extern PtNode_t find_node_llist(PtLList_t L,DataAddr_t dataAddr,UdCmp_t is_equal_node);

/* Insert a node with a data given */
extern int insert_node_llist(PtLList_t L,DataAddr_t dataAddr_obj,DataAddr_t dataAddr_new,UdCmp_t is_equal_node);

/* Modify a node with a data given */
extern int modify_node_llist(PtLList_t L, DataAddr_t dataAddr_obj,DataAddr_t dataAddr_new,UdCmp_t is_equal_node);

/* Return the address of the previous node of the node given */
extern PtNode_t find_prenode_llist(PtLList_t L,DataAddr_t dataAddr,UdCmp_t is_equal_node);

/* Delete a node with a data given */
extern int delete_node_llist(PtLList_t L,DataAddr_t dataAddr,UdCmp_t is_equal_node,UdFreeNode_t free_node);

/* Show data in L */
extern int show_llist(PtLList_t L,UdShowNode_t showNode);

/* Destroy L */
extern int destroy_llist(PtLList_t L,UdFreeNode_t free_node);

/* Save L to file */
extern int save_llist_to_file(PtLList_t L,const char* filepath,UdFreeNode_t free_node);

/* Load L from file */
extern int load_llist_from_file(PtLList_t L,const char* filepath);

#endif //__SEMI_GENERIC_LINK_LIST_H__











































































