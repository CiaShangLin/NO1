#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int poko[4][13];
const char num[]={'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
const char c[][10]={"�®�","����","���","����"};

struct poko{
	int point;
	int color;
};

void init(int poko[4][13]){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<13;j++){
			poko[i][j]=j+1;
		}
	}
}

void deal(struct poko ptr[],int n){
	int p=rand()%13,c=rand()%4;
	if(poko[c][p]!=0){
	    ptr[n].point=poko[c][p];
	    ptr[n].color=c;	
	    poko[c][p]=0;
	}else{
		deal(ptr,n);
	}
}

void firstDeal(struct poko player[],struct poko banker[]){
	printf("�o�P�����a\n");
	deal(player,0);
    printf("�o�P�����a\n");
    deal(banker,0);
    printf("�o�P�����a\n");
    deal(player,1); 
    printf("�o�P�����a\n");
    deal(banker,1);
}

void printPlayer(struct poko player[],int p){
	int i;
	printf("�ثe���a���P\n");
	for(i=0;i<p;i++){
		printf("%s %c\n",c[player[i].color],num[player[i].point-1]);
	}
}

void printBanker(struct poko banker[],int b,int k){
	int i;
	printf("�ثe���a���P\n");
	if(k==1){          //��ܷt�P 
		printf("�t�P\n");
		printf("%s%c\n",c[banker[1].color],num[banker[1].point-1]);
	}else{             //����� 
		for(i=0;i<b;i++){
			printf("%s%c\n",c[banker[i].color],num[banker[i].point-1]);
		}
	}
}

int countPoint(struct poko ptr[],int c){
	int i,time=0,total=0;
	int p[2];
	for(i=0;i<c;i++){
		if(ptr[i].point==1){
			time++;
		}else{
			total+=ptr[i].point>=10?10:ptr[i].point;
		}
	}
	p[0]=total;
	p[1]=total;
	switch(time){
		case 1:
			p[0]+=1;
			p[1]+=11;
			break;
		case 2:
			p[0]+=1+1;
			p[1]+=11+1;
			break;
		case 3:
			p[0]+=1+1+1;
			p[1]+=11+1+1;
			break;
		case 4:
			p[0]+=1+1+1+1;
			p[1]+=11+1+1+1;
			break;
	}
	if(p[1]<=21 && p[1]>p[0]){
		return p[1];
	}else{
		return p[0];
	}

}

void showResult(int point){
	if(point==21){
		printf("��n21�I\n");
	}else if(point>21){
		printf("�z�}\n");
	}else{
		printf("�٨S�z�}\n");
	}
}

int showMatch(int p,int b){
	int i;
	if(p>21 && b>21){
		printf("����\n");
		i=0;
	}else if(p<=21 && b>21){
		printf("���aĹ\n");
		i=1;
	}else if(p>21 && b<=21){
		printf("���aĹ\n");
		i=-1;
	}else if(p>b){
		printf("���aĹ\n");
		i=1;
	}else if(p<b){
		printf("���aĹ\n");
		i=-1;
	}else if(p==21 && b==21){
		printf("���aĹ\n");
		i=-1;
	}else{
		printf("����\n");
		i=0;
	}
	return i;
}


int main(int argc, char *argv[]) {
	srand(time(NULL));
	int again=1,money=500,m;
	while(again==1){
		init(poko);
		struct poko player[15];
		struct poko banker[15];
		int p=2,b=2,tw=0;
		int playerPoint=0,bankerPoint=0;
		
		firstDeal(player,banker);
		
		printPlayer(player,p);                          //�٭n�B�z��n21�I 
		playerPoint=countPoint(player,p);
		printf("���a�I��:%d\n",playerPoint);
		//tw=playerPoint==21?1:0;
		
		printBanker(banker,b,1);
		bankerPoint=countPoint(banker,b);
		
		printf("�n��h�ֱm��:");
		scanf("%d",&m);
		money-=m;
		
		char ch='Y';
		while(playerPoint<21){
			printf("���a�٭n�P��?Y/N:");
			scanf(" %c",&ch);
			if(ch=='Y'){
				deal(player,p++);
			}else{
				break;
			} 
			printPlayer(player,p);
			playerPoint=countPoint(player,p);
			printf("���a�I��:%d\n",playerPoint);
			showResult(playerPoint);
		}
		
		printf("\n\n");
		
		printBanker(banker,b,2);
		printf("���a�I��:%d\n",bankerPoint);
		while(bankerPoint<21){
			printf("���a�p��17�I��?���a�٭n�P��?Y/N:");
			if(bankerPoint<17){
				printf("\n");
				deal(banker,b++);
				printBanker(banker,b,2);
				bankerPoint=countPoint(banker,b);
				printf("���a�I��:%d\n",bankerPoint);
				showResult(bankerPoint);
			}else{
			    scanf("  %c",&ch);
				if(ch=='Y'){
					deal(banker,b++);
					printBanker(banker,b,2);
					bankerPoint=countPoint(banker,b);
		            printf("���a�I��:%d\n",bankerPoint);
					showResult(bankerPoint);
				}
				else{
					break;
				}
			}
		}
		
		int showmatch=showMatch(playerPoint,bankerPoint);
		if(showmatch==1){
			money+=m*2;
		}else if(showmatch==-1){
			m=0;
		}else{
			money+=m;
		}
		printf("�ثe���a�m��:%d\n",money);
		printf("�٭n�~���?1(�n)/0(���n):");
	    scanf("%d",&again);
	    printf("\n");
	}
	return 0;
}
