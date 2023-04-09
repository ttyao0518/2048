#include <iostream>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

#define  N 5
int grid[N][N] = {0}, D = 0, M = 2048, a_sum = 0;
bool restart = false;
int maxsum = 0;

//��ʾ
void showdata(){
	maxsum = max(maxsum, a_sum);
	int i, j;
	system("CLS");
	for(i = 0;i < N + 2;i ++){
		printf("%5c", '+');
	}
	printf("\n\n");
	for(i = 0; i < N; i++){
		printf("%5c", '+');
		for(j = 0; j < N; j++){
			if(grid[i][j] != 0){
				printf("%5d", grid[i][j]);
			}
			else{
				printf("%5c", ' ');
			}
		}
	    printf("%5c", '+');
		printf("\n\n");
	}
	for(i = 0; i < N + 2; i++){
		printf("%5c", '+');
	}
	cout<< endl<< "             Score:"<< a_sum;
	cout << endl << "          Max score: " << maxsum;
}

//�ж��Ƿ��п�λ
int isNotFull(){
    int i, j, k = 0;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(grid[i][j] == 0){
				k = 1;
				break;
			}
		}
	}
	return k;
}

//�������
void randomdata(){
	int r, c, x;
	x = rand()%2*2+2;
	do{
		r = rand()%N;
	    c = rand()%N;
	}while(grid[r][c] != 0);
	grid[r][c] = x;
}

//��ȡ���ֵ
int getMax(){
    int i, j, max = 0;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(max < grid[i][j]){
				max = grid[i][j];
			}
		}
	}
	return max;
}

//�ƶ����,����1��ʾ���ƶ�,����0��ʾ���ƶ�
int add(){
	int i, j, cr, w, F = 0;
	if(D == 1){//top
		for(i = 1; i < N; i++){
			for(j = 0; j < N; j++){
				cr = i;
				w = 0;//0:δ�ϲ�  1:�ϲ���
				while((cr >= 1) && (grid[cr][j] != 0)){
					if(grid[cr - 1][j] == 0){//�Ϸ��п�λ,����
					    grid[cr - 1][j] = grid[cr][j];
						grid[cr][j] = 0;
						F = 1;
					}
					else{//�Ϸ��޿�λ
						if((grid[cr - 1][j] == grid[cr][j]) && (w == 0)){//���,���
						    a_sum += grid[cr - 1][j] * 2;
							grid[cr - 1][j] = grid[cr - 1][j] * 2;
							grid[cr][j] = 0;
							w = 1;
							F = 1;
						}
						else{//����
							break;
						}
					}
					cr--;
				}
			}
		}
	}
	if(D == 2){//down
		for(i = N - 2; i >= 0; i--){
			for(j = 0;j < N; j++){
				cr = i;
				w = 0;
				while((cr <= N - 2) && (grid[cr][j] != 0)){
					if(grid[cr + 1][j] == 0){//�·��п�λ,����
					    grid[cr + 1][j] = grid[cr][j];
						grid[cr][j] = 0;
						F = 1;
					}
					else{//�·��޿�λ
						if((grid[cr + 1][j] == grid[cr][j]) && (w == 0)){//���,���
							a_sum += grid[cr + 1][j] * 2;
						    grid[cr + 1][j] = grid[cr + 1][j] * 2;
							grid[cr][j] = 0;
							w = 1;
							F = 1;
						}
						else{//����
							break;
						}
					}
					cr++;
				}
			}
		}
	}
	if(D == 3){//left
		for(i = 0; i < N; i++){
			for(j = 1; j < N; j++){
				cr = j;
				w = 0;
				while((cr >= 1) && (grid[i][cr] != 0)){
					if(grid[i][cr - 1] == 0){//���п�λ,����
					    grid[i][cr - 1] = grid[i][cr];
						grid[i][cr] = 0;
						F = 1;
					}
					else{//���޿�λ
						if((grid[i][cr - 1] == grid[i][cr]) && (w == 0)){//���,���
							a_sum += grid[i][cr - 1] * 2;
						    grid[i][cr - 1] = grid[i][cr - 1] * 2;
							grid[i][cr] = 0;
							w = 1;
							F = 1;
						}
						else{//����
							break;
						}
					}
					cr--;
				}
			}
		}
	}
	if(D == 4){//right
		for(i = 0; i < N; i++){
			for(j = N - 2; j >= 0; j--){
				cr = j;
				w = 0;
				while((cr <= N - 2) && (grid[i][cr] != 0)){
					if(grid[i][cr + 1] == 0){//�ҷ��п�λ,����
					    grid[i][cr + 1] = grid[i][cr];
						grid[i][cr] = 0;
						F = 1;
					}
					else{//�ҷ��޿�λ
						if((grid[i][cr + 1] == grid[i][cr])&&(w == 0)){//���,���
							a_sum  += grid[i][cr + 1] * 2;
						    grid[i][cr + 1] = grid[i][cr + 1] * 2;
							grid[i][cr] = 0;
							w = 1;
							F = 1;
						}
						else{//����
							break;
						}
					}
					cr++;
				}
			}
		}
	}
	return F;
}

int getKey(){
   int k = 0;
   char c = getch();
   if(c < 0){//c<0Ϊ�����,��Ҫ�ٶ���һ���ֽ��ж�Ϊ�μ�
		k = 1;
		c = getch();
		if(c == 72 || c == 87){//top
			D = 1;
		}
		if(c == 80 || c == 83){//down
			D = 2;
			k = 1;
		}
		if(c == 75 || c == 65){//left
			D = 3;
			k = 1;
		}
		if(c == 77 || c == 68){//right
			D = 4;
			k = 1;
		}
		if (c == 82)
		{
			restart = true;
		}
   }
   return k;
}

//������ȫ����,����Ƿ��кϲ��Ŀ���,���򷵻�1
int canAdd()
{
	int i, j, k, F = 0;
	for(i = 0; i < N; i++){
		for(j = 0; j < N - 1; j++){
			if(grid[i][j] == grid[i][j + 1]){
				F = 1;
			}
		}
	}

	for(j = 0; j < N; j++){
		for(i = 0; i < N - 1; i++){
			if(grid[i][j] == grid[i + 1][j]){
				F = 1;
			}
		}
	}
	return F;
}

int main(){
	char c;
	int mov, key, isf;
	//����״̬
	srand(time(NULL));
	while (1)
	{
		start: a_sum = 0;
		memset(grid, 0, sizeof grid);
		randomdata();//�����һ����
		randomdata();//����ڶ�����
		showdata();
		do{
			maxsum = max(maxsum, a_sum);
			key = getKey();//��ȡ������
			if(key == 0){
				continue;//�����������Ҽ�,���¶�ȡ����
			}
			if (restart)
				goto start;
			mov = add();//���ݷ�����ϲ����,����1��ʾ���ƶ�
			if(mov == 1){
				showdata();//��ʾ
			}
			if(getMax() == M){//�ж��Ƿ�ʤ��
				printf("Win!\n");
				break;
			}
			isf = isNotFull();//����1��ʾ���п�λ
			if((isf == 1)&&(mov == 1)){//�п�λ�����ƶ������
				randomdata();//�����
				showdata();//��ʾ
			}
			if(isf == 0){//û�пռ�����Ϸ����
				if(canAdd() != 1){
					break;
				}
			}
	   }while(1);
	   maxsum = max(maxsum, a_sum);
	   system("cls");
	   cout<< "Game Over!\n";
	   printf("���ķ���: %d\n", a_sum);
	   system("pause");
	}
   return 0;
}
