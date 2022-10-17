#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include "get_key.h"
#include "keyboard.h"
#include "dcm.h"
char shell_s[]="\nCount: %d, Total Cost: %d >";
void get_line(char *cmd);

pthread_mutex_t CartMutex;
int totalcost = 0, totalcnt = 0, cnt = 0, gcnt = 0;
struct good{
    char id[40];
    char name[10];
    int prize;
};
struct good goodlist[100];
int cart[100], num[100], cost[100];

pthread_t motor;
pthread_t uart;
pthread_t key;

void loadData(){
	FILE *fp = fopen("./goods.csv", "r");
//	printf("%d\n", gcnt);
	printf("loading data...\n");
	char buff[256];
	while(fgets(buff, 255, fp)){
		//printf("%s\n", buff);
		int n = strlen(buff);
		int i = 0, last = 0, t = 0;
		for (i = 0; i < n; i++) {
			if (buff[i] == ',' || buff[i] == '\n'){
                if (t == 0) memcpy(goodlist[gcnt].id, buff + last, i - last);
				if (t == 1) {
					memcpy(goodlist[gcnt].name, buff + last, i - last);
				}
				if (t == 2){
					int j, prize = 0;
					for (j = last; j < i - 1; j++) {
						prize = prize * 10 + buff[j] - '0';
						//printf("%d ", buff[j]);
					}
					goodlist[gcnt].prize = prize;
				}
				last = i + 1; t++;
            }
		}
		gcnt++;
	}
	int i;
    printf("%d goods loaded\n", gcnt);
	for (i = 0; i < gcnt; i++) {
		printf("%s %s %d\n", goodlist[i].id, goodlist[i].name,goodlist[i].prize);
	}
	fclose(fp);
}

void showcart(){
    printf("==========  Market Cart ==========\n"); 
	int i =0;
	if (cnt == 0){
		printf("The cart is empty!\n");	
		return;	
	}
	for (i = 1; i <= cnt; i++) {
		printf("%s %d %d\n", goodlist[cart[i]].name, cost[i], num[i]);
	}
	printf("=========== Statistics ===========\n");
	printf("Total Cost: %d\n", totalcost);
	printf("Goods Count: %d\n", totalcnt);
	printf("==================================\n");
	fflush(stdout);
}
void * consoleshell(){
	int count = 0;
	int i;
	char cmd[256] = {0,};
	char name[40], id[40];
	int price = 0;
	
	while(1){
		printf(shell_s, totalcnt, totalcost);
		fflush(stdout);
		fflush(stdin);
		tty_fflush();
		count = tty_read(id,40);
		if(count <= 0){
			printf("\nread null or error happened");
			continue;
		}
		tty_fflush();
		pthread_mutex_lock(&CartMutex);
		printf("%s\n",id);
		for(i = 0; i < gcnt; i++){
			if (id[0] ==  goodlist[i].id[0] && id[1] == goodlist[i].id[1] && id[2] == goodlist[i].id[2]) {
				cnt++;
				cart[cnt] = i;
				cost[cnt] = goodlist[i].prize;
				num[cnt] = 1;
				totalcost += cost[cnt] * num[cnt];
				totalcnt += num[cnt];
			}
		}
		showcart();
		pthread_mutex_unlock(&CartMutex);
	}
}

void *keyboard(){
	while (1) {
        char x = get_key();
        //printf("%d\n",x);
        if (x == 9) {
			pthread_mutex_lock(&CartMutex);
			char x = get_key();
			//printf("%c\n",x);
			int w = 0;
			while (x != 13){
				if (x >= '0' && x <= '9') putchar(x), w = w * 10 + x - '0', fflush(stdout);
				x = get_key();
			}
			putchar('\n');
			totalcost -= num[cnt] * cost[cnt];
			totalcnt -= num[cnt];
			num[cnt] = w;
			totalcost += num[cnt] * cost[cnt];
			totalcnt += num[cnt]; 
			showcart();
			pthread_mutex_unlock(&CartMutex);
		}
		if (x == 13) {
			pthread_mutex_lock(&CartMutex);
			if (totalcnt == 0){
				puts("You must add some goods before settlement");
			}else{
				puts("paying");
				pthread_create(&motor, NULL, start_motor, 0);
				int i = 0;
				for (i = 0; i < 1000000; i++);
				cnt = totalcnt = totalcost = 0;
				printf(shell_s, totalcnt, totalcost);
				fflush(stdout);
			}
			pthread_mutex_unlock(&CartMutex);
		}
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

int main(){
	kbd_init();
	tty_init();
	cnt = gcnt = totalcnt = totalcost = 0;
	loadData();
	pthread_create(&uart, NULL, consoleshell, 0);
	pthread_create(&key, NULL, keyboard, 0);
	while(1);
	kbd_close();
	tty_end();

}
