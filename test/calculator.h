#include<stdio.h>
#include<math.h>
#include <time.h>
#include<stdlib.h>
int find=0;
int check(board* b, int i, int j, int num);
void soduku(int n,board* b);
void output(board* b,IMAGE* img,double time);
int max=9;
int gap=window_length/2/9;
char diag[1000];
int read(IMAGE* img)
{
	cleardevice();
	double time;
	clock_t start,end;
	putimage(0,0,&img[4]);
	drawboard(&img[5]);
	board* b=initboard();
    int i, j;
    int temp;
	settextstyle(25, 0, _T("宋体"));
	settextcolor(GREEN);
	solidrectangle(0.6*window_length-10,0.1*window_width-5,window_length,window_width*0.3);
	outtextxy(0.6*window_length,0.1*window_width,"请输入要求解的数");
	settextcolor(RED);
	setfillcolor(YELLOW);
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	solidrectangle(0.6*window_length-10,0.7*window_width-5,0.72*window_length,window_width*0.7+30);
	outtextxy(0.6*window_length,0.7*window_width,"输入完成");
	while(1){
		m=GetMouseMsg();
		if (m.mkLButton==true){
			if (m.x<0.72*window_length&&m.x>0.6*window_length-10&&m.y>0.7*window_width-5&&m.y<window_width*0.7+30){
				HWND hwnd=GetHWnd();
				int id=MessageBox(hwnd,"确认完成？","",MB_OKCANCEL);
				if (id==IDOK){
					break;
				}else{
					continue;
				}
			}else if (m.x>0&&m.x<9*gap&&m.y>0&&m.y<9*gap){
				int curx=m.x/gap,cury=m.y/gap;
				InputBox(diag, 10, "请输入:","",0,0,false);
				sscanf_s(diag,"%d",&b->data[curx][cury]);
				if (!valid(b)){
					drawwrongnumber(img+1,b,curx-1,cury-1);
					HWND hwnd=GetHWnd();
					int id=MessageBox(hwnd,"输入数字与已有数字冲突！，是否重新输入?","",MB_OKCANCEL);
					if (id==IDOK){
						b->data[curx-1][cury-1]=0;
						continue;
					}
				}
				drawboard(img+5);
				drawnumber(b);
				solidrectangle(0.6*window_length-10,0.7*window_width-5,0.72*window_length,window_width*0.7+30);
				outtextxy(0.6*window_length,0.7*window_width,"输入完成");
			}
		}
	}
	start=clock();
	solve(b);
	end=clock();
	time=(end-start)*1.0/1000;
	output(b,img,time);
	while(!_kbhit());
	_getch();
	cleardevice();
	return 0;
}
void output(board* b ,IMAGE* img,double time)
{ 
	drawboard(img+5);
	drawnumber(b);
	char s[100];
	sprintf(s,"您计算所用时间为：%.6f秒，是否重新计算？",time);
	HWND hwnd=GetHWnd();
	int id=MessageBox(hwnd,s,"",MB_OKCANCEL);
	if (id==IDOK){
			read(img);
	}else{
		return;
	}
}