#include "consoleshell.h"
char shell_s[]="\nshell> ";
/**
**
**控制台
**
*/
void get_line(char *cmd);
void * consoleshell(){
	int count=0;
	int i;
	char cmd[256]={0,};	
//char cmd_sub[20]={0,};	
//	int rc = sqliteDB_open();
  char name[40],id[40];
  int price = 0;//demo中只做整型的，浮点型的转换可以参考网上实现
	
	//printf("\n<miniprint control shell>");
	//printf("\n [1]  select all the records in table merchandise");
	//printf("\n [2]  select the the record which you known its name");
	//printf("\n [3]  select the record by the BarCode Scanner");
	//printf("\n [4]  delete record");
	//printf("\n [5]  add record");
	//printf("\n [**] help menu");
	//printf("\n [0]  print the end of the context an exit");
	while(1){
		printf(shell_s);
		fflush(stdout);
	//	get_line(cmd);
//		printf("\r\nwe get it!!!!!!!!!!!!");				//显示必要的输出

		
	  		fflush(stdin);//刷新缓冲区
	  		tty_fflush();//2007-3-23刷新缓存
	  		printf("\nenter the id:");
	  		fflush(stdout);
	  		count = tty_read(id,40);
	  		printf("\nread:%d   ",count);
				if(count <= 0){
						printf("\nread null or error happened");
						continue;
				}
				tty_fflush();//2007-3-23
				printf("%s\n",id);
				for(i=0;i<40;i++)
				   printf("%x",id[i]);
				//sqliteDB_opt_select_by_id(id);
	}
}
void get_line(char *cmd){
	int i=0;
	while(1){
		cmd[i]=getchar();
		if(cmd[i]==10){
			cmd[i]=0;
			break;
		}
		fflush(stdout);
		i++;
	}
}

