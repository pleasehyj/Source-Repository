#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"semi_generic_llist.h"
#include "debug.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Initialize a linked list */
PtLList_t create_llist(int dataSize){//,UdFreeNode_t free_node){
	PtLList_t L=(PtLList_t)malloc(sizeof(LList_t));
	if(NULL==L){
		debug("malloc error\n");
		return NULL;
	}
	L->head=(PtNode_t)malloc(sizeof(Node_t));
	if(NULL==L){
		debug("malloc error\n");
		return NULL;
	}
	L->head->next=NULL;
	L->dataSize=dataSize;
	//L->free_node=free_node;
}
/* Return true if L is empty */
int is_empty_llist(PtLList_t L){
	return NULL==L->head->next;
}

/* Insert a node at the head */
int insert_head_llist(PtLList_t L,DataAddr_t dataAddr){

	/* Encapsulate a node */
	PtNode_t tmp=(PtNode_t)malloc(sizeof(Node_t));
	if(NULL==tmp){
		debug("malloc error\n");
		return -1;
	}
	tmp->dataAddr=(DataAddr_t)malloc(L->dataSize);	
	if(NULL==tmp->dataAddr){
		debug("malloc error\n");
		return -1;
	}
	memcpy(tmp->dataAddr,dataAddr,L->dataSize);

	/* Relink */
	tmp->next=L->head->next;
	L->head->next=tmp;
	return 0;
}

/* Delete the node at the head, 
 * the space pointed by dataAddr must be enough to contain data*/
int delete_head_llist(PtLList_t L,DataAddr_t dataAddr,UdFreeNode_t free_node){
	if(is_empty_llist(L)){
		debug("list is empty\n");
		return -1;
	}
	PtNode_t tmp=L->head->next;
	L->head->next=L->head->next->next;
	memcpy(dataAddr,tmp->dataAddr,L->dataSize);
	free_node(tmp);
	return 0;
}

/* Return the address of the node at tail */
PtNode_t find_tail_llist(PtLList_t L){
	PtNode_t tmp=L->head;
	while(tmp){
		if(NULL==tmp->next){
			return tmp;
		}
		tmp=tmp->next;
	}
	return NULL;	//没找到
}

/* Insert a node at the tail */
int insert_tail_llist(PtLList_t L,DataAddr_t dataAddr){
	PtNode_t tmp=(PtNode_t)malloc(sizeof(Node_t));
	if(NULL==tmp){
		debug("malloc error\n");
		return -1;
	}
	tmp->dataAddr=(DataAddr_t)malloc(L->dataSize);
	if(NULL==dataAddr){
		debug("malloc error\n");
		return -1;
	}
	memcpy(tmp->dataAddr,dataAddr,L->dataSize);
	PtNode_t tail=find_tail_llist(L);

	/* Relink */
	tmp->next=NULL;
	tail->next=tmp;
	return 0;
}
/* Return the address of the previous node at tail */
PtNode_t find_pretail_llist(PtLList_t L){
	if(is_empty_llist(L)){
		debug("list is empty\n");
		return NULL;
	}
	PtNode_t tmp=L->head->next;
	while(tmp){
		if(NULL==tmp->next->next){
			return tmp;
		}
		tmp=tmp->next;
	}

	debug("no such node\n");
	return NULL;	//没找到

}

/* Delete the node at the tail */
int delete_tail_llist(PtLList_t L,DataAddr_t dataAddr,UdFreeNode_t free_node){

	if(is_empty_llist(L)){
		debug("list is empty\n");
		return -1;
	}
	PtNode_t prevTail=find_pretail_llist(L);
	memcpy(dataAddr,prevTail->next->dataAddr,L->dataSize);
	free_node(prevTail->next);
	prevTail->next=NULL;
	return 0;
}

/* Return the address of the node containing the data given */
PtNode_t find_node_llist(PtLList_t L,DataAddr_t dataAddr,UdCmp_t is_equal_node){
	if(is_empty_llist(L)){
		debug("list is empty\n");
		return NULL;
	}
	PtNode_t tmp=L->head->next;
	int test=0;
	while(tmp){
		if(is_equal_node(tmp->dataAddr,dataAddr)){
			return tmp;
		}
		test++;
		tmp=tmp->next;
	}
	debug("no such node\n");
	return NULL;	//没找到
}

/* Insert a node with a data given */
int insert_node_llist(PtLList_t L,DataAddr_t dataAddr_obj,DataAddr_t dataAddr_new,UdCmp_t is_equal_node){
	PtNode_t tmp=(PtNode_t)malloc(sizeof(Node_t));
	if(NULL==tmp){
		return -1;
	}
	tmp->dataAddr=(DataAddr_t)malloc(L->dataSize);
	if(NULL==tmp->dataAddr){
		debug("malloc error\n");
		return -1;
	}
	memcpy(tmp->dataAddr,dataAddr_new,L->dataSize);
	PtNode_t node=find_node_llist(L,dataAddr_obj,is_equal_node);
	tmp->next=node->next;
	node->next=tmp;
	return 0;
}
/* Modify a node with a data given */
int modify_node_llist(PtLList_t L, DataAddr_t dataAddr_obj,DataAddr_t dataAddr_new,UdCmp_t is_equal_node){
	PtNode_t node=find_node_llist(L,dataAddr_obj,is_equal_node);
	memcpy(node->dataAddr,dataAddr_new,L->dataSize);
	return 0;
}
#if 1
/* Return the address of the previous node of the node given */
PtNode_t find_prenode_llist(PtLList_t L,DataAddr_t dataAddr,UdCmp_t is_equal_node){
	if(is_empty_llist(L)){
		debug("list is empty\n");
		return NULL;
	}
	PtNode_t tmp=L->head->next;
	while(tmp){
		if(is_equal_node(dataAddr,tmp->next->dataAddr)){
			return tmp;
		}
		tmp=tmp->next;
	}
	return NULL;
}

/* Delete a node with a data given */
int delete_node_llist(PtLList_t L,DataAddr_t dataAddr,UdCmp_t is_equal_node,UdFreeNode_t free_node){
	if(is_empty_llist(L)){
		debug("list is empty\n");
		//fprintf(stderr,"%s:%d:list is empty\n",__FILE__,__LINE__);
		return -1;
	}
	PtNode_t tmp=find_prenode_llist(L,dataAddr,is_equal_node);
	PtNode_t node=tmp->next;
	tmp->next=tmp->next->next;
	free_node(node);
}

#endif
/* Show data in L */
int show_llist(PtLList_t L,UdShowNode_t showNode){
	if(is_empty_llist(L)){
		debug("list is empty\n");
		//fprintf(stderr,"%s:%d:list is empty\n",__FILE__,__LINE__);
		return -1;
	}
	PtNode_t tmp=L->head->next;
	while(tmp){
		showNode(tmp);
		tmp=tmp->next;
	}
	return 0;
}

/* Destroy L */
int destroy_llist(PtLList_t L,UdFreeNode_t free_node){
	if(is_empty_llist(L)){
		debug("list is empty\n");
		return -1;
	}
	PtNode_t tmp=NULL;
	while(L->head->next){
		tmp=L->head->next;
		L->head->next=L->head->next->next;
		free_node(tmp);
	}
	return 0;
}
/* Save L to file */
#if 1
int save_llist_to_file(PtLList_t L,const char* filepath,UdFreeNode_t free_node){

	int fd=open(filepath,O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(is_empty_llist(L)){
		debug("list is empty\n");
		return -1;
	}
	DataAddr_t tmp=(DataAddr_t)malloc(L->dataSize);
	if(NULL==tmp){
		debug("malloc error\n");
		return -2;
	}
	while(!is_empty_llist(L)){
		delete_head_llist(L,tmp,free_node);
		write(fd,tmp,L->dataSize);
	}
	destroy_llist(L,free_node);
	close(fd);
	free(tmp);
	tmp=NULL;
}

/* Load L from file */
int load_llist_from_file(PtLList_t L,const char* filepath){
	int fd=open(filepath,O_RDONLY|O_CREAT,0666);
	DataAddr_t tmpData=(DataAddr_t)malloc(L->dataSize);
	if(NULL==tmpData){
		debug("malloc error\n");
		return -1;
	}
	int i=0;
	while(0<read(fd,tmpData,L->dataSize)){
		insert_tail_llist(L,tmpData);
	}
	close(fd);
	free(tmpData);
	tmpData=NULL;
	ftruncate(fd,0);
}

#endif

