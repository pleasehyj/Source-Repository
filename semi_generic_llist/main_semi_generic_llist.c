#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"semi_generic_llist.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct{
	int n;
	char c;
	char arr[10];
}S;

int myEqual(void*x,void* y){
	return ((S*)x)->n==((S*)y)->n&&((S*)x)->c==((S*)y)->c&&!strcmp(((S*)x)->arr,((S*)y)->arr);
}
int myFree(PtNode_t node){
	free(node);
	return 0;
}

int myShow(PtNode_t node){
	int i;
	printf ("____%d__%c__%s___\n",(((S*)(node->dataAddr))->n),(((S*)(node->dataAddr))->c), (((S*)(node->dataAddr))->arr));
	return 0;
}

int main(int argc, const char *argv[])
{
	int i=0;
	S s1={1,'a',"123"};
	S s2={2,'d',"456"};
	S s3={3,'h',"780"};
	S s4={4,'w',"fge"};
	S s5={5,'j',"wedc"};
	S s6={6,'q',"vre"};
	PtLList_t L=create_llist(sizeof(S));

	puts("-----------------insert_head_llist--------------");
	insert_head_llist(L,&s1);
	insert_head_llist(L,&s2);
	insert_head_llist(L,&s3);
	insert_head_llist(L,&s4);

	insert_head_llist(L,&s2);
	insert_head_llist(L,&s3);
	insert_head_llist(L,&s4);
	insert_head_llist(L,&s5);
	insert_head_llist(L,&s6);
	show_llist(L,myShow);
	putchar(10);
	printf("%d\n",is_empty_llist(L));
	puts("-----------------delete_head_llist--------------");
	S tmp;
	delete_head_llist(L,&tmp,myFree);
	delete_head_llist(L,&tmp,myFree);
	delete_head_llist(L,&tmp,myFree);
	show_llist(L,myShow);
	putchar(10);
	puts("---------------insert_tail_llist---------------");
	insert_tail_llist(L,&s6);
	insert_tail_llist(L,&s6);
	insert_tail_llist(L,&s6);
	insert_tail_llist(L,&s6);
	show_llist(L,myShow);
	putchar(10);

	puts("--------------delete_tail_llist-----------------");
	delete_tail_llist(L,&tmp,myFree);
	delete_tail_llist(L,&tmp,myFree);
	show_llist(L,myShow);
	putchar(10);

	puts("------------insert_node_llist-------------------");
	insert_node_llist(L,&s6,&s1,myEqual);
	insert_node_llist(L,&s6,&s1,myEqual);
	insert_node_llist(L,&s6,&s1,myEqual);
	insert_node_llist(L,&s6,&s1,myEqual);
	show_llist(L,myShow);
	putchar(10);


	puts("-----------delete_node_llist--------------------");
	delete_node_llist(L,&s1,myEqual,myFree);
	delete_node_llist(L,&s1,myEqual,myFree);
	show_llist(L,myShow);
	putchar(10);

	puts("--------------modify_node_llist-----------------");
	S s7={7,'z',"ew"};
	modify_node_llist(L,&s2,&s7,myEqual);
	show_llist(L,myShow);

	puts("--------------destroy_llist-----------------");
#if 0
	destroy_llist(L,myFree);
	show_llist(L,myShow);
#endif
	puts("--------------save_llist_to_file-----------------");
	save_llist_to_file(L,"./database",myFree);
	show_llist(L,myShow);
	printf("sizeof data:%d\n",sizeof(S));


	puts("--------------load_llist_from_file-----------------");
	S* stmp=(S*)malloc(sizeof(stmp));
	load_llist_from_file(L,"./database");
	show_llist(L,myShow);
	return 0;
}
















