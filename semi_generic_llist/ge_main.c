#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"semi_generic_llist.h"
       #include <unistd.h>

       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

#if 0	//int 
int myEqual(void* x,void* y){
	return *(int*)x==*(int*)y;
}
int myFree(PtNode_t node){
	free(node);
	return 0;
}
int myShow(PtNode_t node){
	printf("%d ",*(int*)(node->dataAddr));
	return 0;
}
#endif 
#if 1
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
	//printf("___%d__%c__%s___\n",node->(S*)dataAddr->n, node->(S*)dataAddr->c, node->(S*)dataAddr->arr);
	return 0;
}

#endif
#if 0	//指针数组

//typedef char* arr[3] array;
int myEqual(void* x,void* y){
	return !strcmp(*(char**)x,*(char**)y); 
}

#endif





int main(int argc, const char *argv[])
{
#if 0	//int
	int tmp=0,i=0,j=0;
	PtLList_t L=create_llist(sizeof(int),myFree);
	printf("%d\n",is_empty_llist(L));
	for(i=0;i<10;i++){
		insert_head_llist(L,&i);
		putchar(10);
		show_llist(L,myShow);
	}
	putchar(10);
	puts("-------------------------------");
	for(i=5;i>0;i--){
		delete_head_llist(L,&tmp,myFree);
		show_llist(L,myShow);
		putchar(10);
	}
	puts("-------------------------------");
	for(i=0;i<10;i++){
		insert_tail_llist(L,&i);
		show_llist(L,myShow);
		putchar(10);
	}
	
	puts("-------------------------------");
	for(i=0;i<4;i++){
		delete_tail_llist(L,&tmp,myFree);
		show_llist(L,myShow);
		putchar(10);

	}
	puts("-------------------------------");
	i=100;
	j=2;
	insert_node_llist(L,&j,&i,myEqual);
	insert_node_llist(L,&j,&i,myEqual);
	insert_node_llist(L,&j,&i,myEqual);
	insert_node_llist(L,&j,&i,myEqual);
	insert_node_llist(L,&j,&i,myEqual);
	insert_node_llist(L,&j,&i,myEqual);
	insert_node_llist(L,&j,&i,myEqual);
	show_llist(L,myShow);
	putchar(10);


	puts("-------------------------------");
	delete_node_llist(L,&i,myEqual,myFree);
	i=3;
	delete_node_llist(L,&i,myEqual,myFree);



	show_llist(L,myShow);
	putchar(10);

#endif
#if 1	//struct
	int i=0;
	S s1={1,'a',"123"};
	S s2={2,'d',"456"};
	S s3={3,'h',"780"};
	S s4={4,'w',"fge"};
	S s5={5,'j',"wedc"};
	S s6={6,'q',"vre"};
	PtLList_t L=create_llist(sizeof(S));//,myFree);
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
	//putchar(10);
	putchar(10);
	printf("%d\n",is_empty_llist(L));
	puts("-------------------------------");
	S tmp;
		delete_head_llist(L,&tmp,myFree);
		delete_head_llist(L,&tmp,myFree);
		delete_head_llist(L,&tmp,myFree);
		//myShow(&tmp);
		show_llist(L,myShow);
		putchar(10);
	puts("-------------------------------");



		insert_tail_llist(L,&s6);
		insert_tail_llist(L,&s6);
		insert_tail_llist(L,&s6);
		insert_tail_llist(L,&s6);
		show_llist(L,myShow);
		putchar(10);
	
	puts("-------------------------------");
		delete_tail_llist(L,&tmp,myFree);
		delete_tail_llist(L,&tmp,myFree);
		show_llist(L,myShow);
		putchar(10);

	puts("-------------------------------");
	insert_node_llist(L,&s6,&s1,myEqual);
	insert_node_llist(L,&s6,&s1,myEqual);
	insert_node_llist(L,&s6,&s1,myEqual);
	insert_node_llist(L,&s6,&s1,myEqual);
	show_llist(L,myShow);
	putchar(10);


	puts("-------------------------------");
	delete_node_llist(L,&s1,myEqual,myFree);
	delete_node_llist(L,&s1,myEqual,myFree);
	show_llist(L,myShow);
	putchar(10);
	
	puts("--------------mod-----------------");
	S s7={7,'z',"ew"};
	modify_node_llist(L,&s2,&s7,myEqual);
	show_llist(L,myShow);

	puts("--------------des-----------------");
#if 0
	destroy_llist(L,myFree);
	show_llist(L,myShow);
#endif
	puts("--------------save-----------------");
	//int fd=open("./test",O_RDWR|O_CREAT,0666);
	save_llist_to_file(L,"./test",myFree);
	show_llist(L,myShow);
	printf("sizeof data:%d\n",sizeof(S));
	
	//close(fd);
	
	puts("--------------load-----------------");
	S* stmp=(S*)malloc(sizeof(stmp));
	//int fd_test=open("./test_read",O_RDWR);
	//int num=read(fd_test,stmp,1);
	//fd=open("./test",O_RDWR|O_CREAT,0666);
#if 0
	int num=read(fd,stmp,1);
	fprintf(stderr,"%s:%s:%d:read num:%d\n",__FILE__,__func__,__LINE__,num);
#endif
	load_llist_from_file(L,"./test");
	show_llist(L,myShow);
//	close(fd);
#endif
	return 0;
}
















