#include <graphics.h>  //���ļ��洢������ز���    
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
const int window_length=1000;
const int window_width=600;
class num_map{
public: 
	int data[9][9];
};
typedef class num_map board;
board* initboard(void){//��ʼ������
	int i,j;
	board* newboard=(board*)malloc(sizeof(board));
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			(newboard->data)[i][j]=0;
		}
	}
	return newboard;
}
void freeboard(board* bd){free(bd);}//�ͷ��ڴ�
void drawboard(IMAGE* img){//������
	putimage(0,0,img);
	setlinecolor(RED);
	setlinestyle(PS_SOLID,1,NULL,0);
	int i,gap=window_length/2/9;
	for (i=0;i!=10;++i){
		line(0,0+i*gap,0+9*gap,0+i*gap);
		line(0+i*gap,0,0+i*gap,0+9*gap);
	}
	gap*=3;
	setlinestyle(PS_SOLID,3,NULL,0);
	for (i=0;i!=4;++i){
		line(0,0+i*gap,0+3*gap,0+i*gap);
		line(0+i*gap,0,0+i*gap,0+3*gap);
	}
}
void drawnumber(board *brd){//��������ϵ���������
	settextstyle(25, 0, _T("����"));
	settextcolor(RED);
	int i,j;
	int gap=window_length/2/9;
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			if (brd->data[i][j]==0)continue;
			setfillcolor(YELLOW);
			solidrectangle(0+i*gap+3,0+j*gap+3,(i+1)*gap-3,(j+1)*gap-3);
			outtextxy(gap/2+i*gap-5,gap/2+j*gap-10,'0'+brd->data[i][j]);
		}
	}
}
void drawwrongnumber(IMAGE* img,board* brd,int x,int y){//����������������ʾ���������
	drawboard(img);
	settextstyle(25, 0, _T("����"));
	settextcolor(RED);
	int i,j;
	int gap=window_length/2/9;
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			if (brd->data[i][j]==0)continue;
			if (i==x&&j==y){
				settextcolor(GREEN);
				setfillcolor(RED);
				solidrectangle(0+i*gap+3,0+j*gap+3,(i+1)*gap-1-3,(j+1)*gap-3);
				outtextxy(gap/2+i*gap-5,gap/2+j*gap-10,'0'+brd->data[i][j]);
				settextcolor(RED);
				setfillcolor(YELLOW);
				settextcolor(RED);
				continue;
			};
			solidrectangle(0+i*gap+3,0+j*gap+3,(i+1)*gap-3,(j+1)*gap-3);
			outtextxy(gap/2+i*gap-5,gap/2+j*gap-10,'0'+brd->data[i][j]);
		}
	}
}