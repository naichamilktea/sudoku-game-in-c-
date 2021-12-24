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
	settextstyle(40, 0, _T("������κ"));
	outtextxy(0.6*window_length,0.3*window_width,"1.easy");
	outtextxy(0.6*window_length,0.45*window_width,"2.intermediate");
	outtextxy(0.6*window_length,0.6*window_width,"3.expert");
	outtextxy(0.6*window_length,0.75*window_width,"4.�û�������Ŀ");
}
void gamestart(IMAGE* img){
	char diag[1000],name[1000];
	int x,y,num,n,f=0;
	double curi;
	clock_t start_time,end_time;
	cleardevice();
	board* brd=initboard();
	assert(brd);//�������ڴ�ʧ���������ֹ
	putimage(0,0,&img[0]);
	char bank1[300][82]={0},bank2[300][82]={0},bank3[300][82]={0},bank4[300][82]={0},bank5[300][82]={0};
	FILE *fp1=fopen("���\\easy.txt","r");
	for(n=0;!feof(fp1);n++){
		fgets(bank1[n],83,fp1);
		bank1[n][81]='\0';}
	fclose(fp1);
	FILE *fp2=fopen("���\\intermediate.txt","r");
	for(n=0;!feof(fp2);n++){
		fgets(bank2[n],83,fp2);
		bank2[n][81]='\0';}
	fclose(fp2);
	FILE *fp3=fopen("���\\expert.txt","r");
	for(n=0;!feof(fp3);n++){
		fgets(bank3[n],83,fp3);
		bank3[n][81]='\0';}
	fclose(fp3);
	FILE *fp4=fopen("���\\set.txt","r");
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
		fflush(stdin);//brd���� ��ά����[9][9] �������һ���� ����ȡbank��һ��  �ŵ�9��9��������
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
	while(1){//�������������¼�
		InputBox(diag, 10, "�����������У��к�Ҫ�����ֵ��0��ʾ��գ��м��ÿո����,\n,��0 0 0����ʾ��ֹ����","��������","",0,0,false);
		sscanf_s(diag,"%d %d %d",&x,&y,&num);
		if (x==0&&y==0&&num==0){
			break;
		}
		if (x<1||x>9||y<1||y>9||num<0||num>9){
			HWND hwnd=GetHWnd();
			int id=MessageBox(hwnd,"���벻�Ϸ����Ƿ��������룿","",MB_OKCANCEL);
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
				int id=MessageBox(hwnd,"�����������������ֳ�ͻ�����Ƿ���������?","",MB_OKCANCEL);
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
	outtextxy(0.2*window_length,0.85*window_width,"��R�ɻָ����룬k���鿴����ʱ�䣬��������������");
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
		sprintf(s,"����ǰ��ʱ��Ϊ��%lf�룬�Ƿ������Ϸ��",curi);
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
		int finish_id=MessageBox(hwnd,"ȷ��������ɣ�","",MB_OKCANCEL);
		if (finish_id==IDOK){
			end_time=clock();
			int t=end_time-start_time;
			double ti=t*1.0/1000;
			cleardevice();
			char s[10];
			sprintf(s,"%lf",ti);
			if (finish(brd)){
				putimage(0,0,&img[11]);
				outtextxy(0.5*window_length,0.09*window_width,"��ϲ���У�����ͨ�ء�");
				InputBox(name, 10, "���մ�����","name","",0,0,false);
				outtextxy(0.5*window_length,0.2*window_width,"�����õ�ʱ��Ϊ����s��");
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
				outtextxy(0.5*window_length,0.09*window_width,"���ź�����δ��ɡ�");
				outtextxy(0.5*window_length,0.2*window_width,"�����õ�ʱ��Ϊ����s��");
				outtextxy(0.5*window_length,0.5*window_width,s);
			}
			while(!_kbhit());
			_getch();
			HWND again=GetHWnd();
			int i=MessageBox(hwnd,"�Ƿ�����һ�֣�","",MB_OKCANCEL);
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
	InputBox(dg, 100, "������81�����֣����������ȵ�˳�����룺","��������","",0,0,false);
	FILE *fp4=fopen("���\\set.txt","a+");
	fprintf(fp4,"\n%s",dg);
	fclose(fp4);
	HWND hwnd=GetHWnd();
	MessageBox(hwnd,"��⵼��ɹ���","",MB_OKCANCEL);
}
int main(){
	
    initgraph(window_length, window_width);   // ������ͼ���ڣ���СΪ 1000*600 ����,������board.h���޸�
	setbkmode(TRANSPARENT);
	cleardevice();
	loadimage(&img[0], _T("ͼƬ\\mainmenu.jpg"),window_length,window_width,true);
	loadimage(&img[1], _T("ͼƬ\\board.jpg"),window_length/2,window_length/2,true);
	loadimage(&img[2], _T("ͼƬ\\help.jpg"),window_length,window_width,true);//����ͼ��
	loadimage(&img[3], _T("ͼƬ\\bg3.jpg"),window_length,window_width,true);
	loadimage(&img[4], _T("ͼƬ\\rank.jpg"),window_length,window_width,true);
	loadimage(&img[5], _T("ͼƬ\\board.jpg"),window_length,window_width,true);
	loadimage(&img[6], _T("ͼƬ\\rank.jpg"),window_length,window_width,true);
	loadimage(&img[7], _T("ͼƬ\\ffff.jpg"),window_length,window_width,true);
	loadimage(&img[8], _T("ͼƬ\\rank.jpg"),window_length,window_width,true);
	loadimage(&img[9], _T("ͼƬ\\set.jpg"),window_length,window_width,true);
	loadimage(&img[10], _T("ͼƬ\\ffff.jpg"),window_length,window_width,true);
	loadimage(&img[11], _T("ͼƬ\\success.jpg"),window_length,window_width,true);
	loadimage(&img[12], _T("ͼƬ\\conflict.jpg"),window_length,window_width,true);
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
			int i=MessageBox(hwnd,"���Ҫ���ˣ�","Confirm",MB_OKCANCEL);
			if (i==IDOK){
				closegraph();
				return 0;
			}else{
				continue;
			}
		}
	}
	while(!_kbhit());
    _getch();         // �����������
    closegraph();
	return 0;// �رջ�ͼ����
}