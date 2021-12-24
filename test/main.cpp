#include "board.h"
#include <stdlib.h>
struct person{
	char name[1000];
	double score;
};
person r_easy[100],r_medium[100],r_expert[100];
IMAGE img[100];
#include "help.h"
#include "solution.h"
#include <assert.h>
#include "ranking.h"
#pragma warning(disable:4244)
#pragma warning(disable:4996)
#include "initwindow.h"
#include "calculator.h"
typedef struct person person;
void startmenu(IMAGE* img){
	putimage(0,0,img);
	settextstyle(40, 0, _T("华文新魏"));
	outtextxy(0.6*window_length,0.3*window_width,"1.easy");
	outtextxy(0.6*window_length,0.45*window_width,"2.intermediate");
	outtextxy(0.6*window_length,0.6*window_width,"3.expert");
	outtextxy(0.6*window_length,0.75*window_width,"4.用户设置题目");
}
void gamestart(IMAGE* img){
	char diag[1000],name[1000];
	int x,y,num,n,f=0;
	double curi;
	clock_t start_time,end_time;
	cleardevice();
	board* brd=initboard();
	assert(brd);//若申请内存失败则程序终止
	putimage(0,0,&img[0]);
	char bank1[300][82]={0},bank2[300][82]={0},bank3[300][82]={0},bank4[300][82]={0},bank5[300][82]={0};
	FILE *fp1=fopen("题库\\easy.txt","r");
	for(n=0;!feof(fp1);n++){
		fgets(bank1[n],83,fp1);
		bank1[n][81]='\0';}
	fclose(fp1);
	FILE *fp2=fopen("题库\\intermediate.txt","r");
	for(n=0;!feof(fp2);n++){
		fgets(bank2[n],83,fp2);
		bank2[n][81]='\0';}
	fclose(fp2);
	FILE *fp3=fopen("题库\\expert.txt","r");
	for(n=0;!feof(fp3);n++){
		fgets(bank3[n],83,fp3);
		bank3[n][81]='\0';}
	fclose(fp3);
	FILE *fp4=fopen("题库\\set.txt","r");
	for(n=0;!feof(fp4);n++){
		fgets(bank4[n],83,fp4);
		bank4[n][81]='\0';}
	fclose(fp4);
	srand((unsigned)time(NULL));
	int t =rand()%200,i,a;
	char input='-';
	while(input!='+')
	{
		startmenu(&img[9]);
		while(!_kbhit());
		input=_getch();
		fflush(stdin);//brd变量 二维数组[9][9] 随机生成一个数 任意取bank的一行  放到9×9数组里面
		switch(input)
		{
			case '1':
				{f=1;
					    for(i=0;i<9;i++){
							for(a=0;a<9;a++){
								brd->data[i][a]=bank1[t][i*9+a]-'0';
							}}	break;	
		        }
			case '2':
				{f=2;
					    for(i=0;i<9;i++){
							for(a=0;a<9;a++){
								brd->data[i][a]=bank2[t][i*9+a]-'0';
							}}	break;
		        }
			case '3':
				{f=3;
					    for(i=0;i<9;i++){
							for(a=0;a<9;a++){
								brd->data[i][a]=bank3[t][i*9+a]-'0';
							}}	break;
		        }
			case '4':
				{t=0;
					    for(i=0;i<9;i++){
							for(a=0;a<9;a++){
								brd->data[i][a]=bank4[t][i*9+a]-'0';
							}}		break;
		        }
			default:break;
		}
		break;
	}
	drawboard(&img[1]);
	drawnumber(brd);
	start_time=clock();
	here:
	while(1){//持续监听输入事件
		InputBox(diag, 10, "请依次输入列，行和要填入的值，0表示清空，中间用空格隔开,\n,“0 0 0”表示终止输入","输入数据","",0,0,false);
		sscanf_s(diag,"%d %d %d",&x,&y,&num);
		if (x==0&&y==0&&num==0){
			break;
		}
		if (x<1||x>9||y<1||y>9||num<0||num>9){
			HWND hwnd=GetHWnd();
			int id=MessageBox(hwnd,"输入不合法。是否重新输入？","",MB_OKCANCEL);
			if (id==IDOK)
			continue;
			else{
				break;}
		}else{
			brd->data[x-1][y-1]=num;
			if (valid(brd)){
				drawnumber(brd);
			}else{
				drawwrongnumber(img+12,brd,x-1,y-1);
				HWND hwnd=GetHWnd();
				int id=MessageBox(hwnd,"输入数字与已有数字冲突！，是否重新输入?","",MB_OKCANCEL);
				if (id==IDOK){
					brd->data[x-1][y-1]=0;
					continue;
				}
			}
		}
		drawboard(&img[1]);
		drawnumber(brd);
	}
	settextcolor(BLACK);
	outtextxy(0.2*window_length,0.85*window_width,"按R可恢复输入，k键查看已用时间，其他键结束输入");
	settextcolor(RED);
	char inp;
	while(!_kbhit());
	inp=_getch();
	if (inp=='r')goto here;
	if (inp=='k'){
		clock_t current=clock();
		int curtime=current-start_time;
		curi=curtime*1.0/1000;
		char s[100];
		sprintf(s,"您当前的时间为：%lf秒，是否继续游戏？",curi);
		HWND hwnd=GetHWnd();
		int id=MessageBox(hwnd,s,"",MB_OKCANCEL);
		if (id==IDOK){
			goto here;
		}else{
			return;
		}
	}
	else{
		HWND hwnd=GetHWnd();
		int finish_id=MessageBox(hwnd,"确认输入完成？","",MB_OKCANCEL);
		if (finish_id==IDOK){
			end_time=clock();
			int t=end_time-start_time;
			double ti=t*1.0/1000;
			cleardevice();
			char s[10];
			sprintf(s,"%lf",ti);
			if (finish(brd)){
				putimage(0,0,&img[11]);
				outtextxy(0.5*window_length,0.09*window_width,"恭喜大佬，您已通关。");
				InputBox(name, 10, "尊姓大名？","name","",0,0,false);
				outtextxy(0.5*window_length,0.2*window_width,"您所用的时间为：（s）");
				outtextxy(0.5*window_length,0.5*window_width,s);
				switch(f){
				case 1:{
					r_easy[numofeasy].score=curi;strcpy(r_easy[numofeasy++].name,name);
					break;
					   }
				case 2:{
					r_medium[numofmedium].score=curi;strcpy(r_medium[numofmedium++].name,name);
					break;
					   }
				case 3:{
					r_expert[numofexpert].score=curi;strcpy(r_expert[numofexpert++].name,name);
					break;
					   }
				}
			}else{
				putimage(0,0,&img[7]);
				outtextxy(0.5*window_length,0.09*window_width,"很遗憾，您未完成。");
				outtextxy(0.5*window_length,0.2*window_width,"您所用的时间为：（s）");
				outtextxy(0.5*window_length,0.5*window_width,s);
			}
			while(!_kbhit());
			_getch();
			HWND again=GetHWnd();
			int i=MessageBox(hwnd,"是否再来一局？","",MB_OKCANCEL);
			if (i==IDOK){
				gamestart(img);
			}else{
				return;
			}
		}else{
			goto here;
		}
	}
	freeboard(brd);
}
void set(IMAGE* img){
	char dg[100];
	InputBox(dg, 100, "请输入81个数字，按照行优先的顺序输入：","输入数据","",0,0,false);
	FILE *fp4=fopen("题库\\set.txt","a+");
	fprintf(fp4,"\n%s",dg);
	fclose(fp4);
	HWND hwnd=GetHWnd();
	MessageBox(hwnd,"题库导入成功。","",MB_OKCANCEL);
}
int main(){
	
    initgraph(window_length, window_width);   // 创建绘图窗口，大小为 1000*600 像素,可以在board.h中修改
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(&img[0], _T("图片\\mainmenu.jpg"),window_length,window_width,true);
	loadimage(&img[1], _T("图片\\board.jpg"),window_length/2,window_length/2,true);
	loadimage(&img[2], _T("图片\\help.jpg"),window_length,window_width,true);//加载图像
	loadimage(&img[3], _T("图片\\bg3.jpg"),window_length,window_width,true);
	loadimage(&img[4], _T("图片\\rank.jpg"),window_length,window_width,true);
	loadimage(&img[5], _T("图片\\board.jpg"),window_length,window_width,true);
	loadimage(&img[6], _T("图片\\rank.jpg"),window_length,window_width,true);
	loadimage(&img[7], _T("图片\\ffff.jpg"),window_length,window_width,true);
	loadimage(&img[8], _T("图片\\rank.jpg"),window_length,window_width,true);
	loadimage(&img[9], _T("图片\\set.jpg"),window_length,window_width,true);
	loadimage(&img[10], _T("图片\\ffff.jpg"),window_length,window_width,true);
	loadimage(&img[11], _T("图片\\success.jpg"),window_length,window_width,true);
	loadimage(&img[12], _T("图片\\conflict.jpg"),window_length,window_width,true);
	char input='-';
	while(input!='+'){
		initwindow(&img[0]);
		while(!_kbhit());
		input=_getch();
		fflush(stdin);
		switch(input){
			case '1':gamestart(img);break;
			case '2':read(img);break;
			case '3':rank(img,r_easy,r_medium,r_expert);break;
			case '4':helpwindow(img);break;
			case '5':set(img);break;
			default:break;
		}
		if (input=='0'){//exit
			HWND hwnd=GetHWnd();
			int i=MessageBox(hwnd,"真的要走了？","Confirm",MB_OKCANCEL);
			if (i==IDOK){
				closegraph();
				return 0;
			}else{
				continue;
			}
		}
	}
	while(!_kbhit());
    _getch();         // 按任意键继续
    closegraph();
	return 0;// 关闭绘图窗口
}