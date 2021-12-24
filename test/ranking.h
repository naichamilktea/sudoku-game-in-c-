#include <stdio.h>
#include <string.h>
char dia[1000];
void findper(char* s,person* easy,person* medium,person* expert);
int numofeasy=0,numofmedium=0,numofexpert=0;
void displayrank(IMAGE* img,person* easy,person* medium,person* expert){
	cleardevice();
	putimage(0,0,&img[1]);
	settextcolor(RED);
	settextstyle(20, 0, _T("宋体"));
	int i=0;
	outtextxy(0.1*window_length,0.1*window_width,"easy");
	outtextxy(0.4*window_length,0.1*window_width,"intermediate");
	outtextxy(0.7*window_length,0.1*window_width,"hard");
	for (i=0;i<numofeasy;++i){
		char di[10000]={0};
		sprintf(di,"%s %.1lf",easy[i].name,easy[i].score);
		outtextxy(0.1*window_length,(0.2+i*1.0/10)*window_width,di);
	}
	for (i=0;i<numofmedium;++i){
		char di[10000]={0};
		sprintf(di,"%s %.1lf",medium[i].name,medium[i].score);
		outtextxy(0.4*window_length,(0.2+i*1.0/10)*window_width,di);
	}
	for (i=0;i<numofexpert;++i){
		char di[10000]={0};
		sprintf(di,"%s %.1lf",expert[i].name,expert[i].score);
		outtextxy(0.7*window_length,(0.2+i*1.0/10)*window_width,di);
	}
	while(!_kbhit());
	_getch();
}
void rank(IMAGE* img,person* easy,person* medium,person* expert){
	putimage(0,0,img+6);
	int i;
	char c;
	FILE* fp=NULL,*fp1=NULL;
	fp=fopen("排行榜\\rating_easy.txt","r");
	if (fp==NULL){
		outtextxy(0,0,"failed!");
		_getch();
		return;
	}
	for (i=0;!feof(fp);++i){
		fscanf(fp,"%s %lf",easy[i].name,&easy[i].score);
		++numofeasy;
	}
	fp=fopen("排行榜\\rating_intermediate.txt","r");
	for (i=0;!feof(fp);++i){
		fscanf(fp,"%s %lf",medium[i].name,&medium[i].score);
		++numofmedium;
	}
	fp=fopen("排行榜\\rating_expert.txt","r");
	for (i=0;!feof(fp);++i){
		fscanf(fp,"%s %lf",expert[i].name,&expert[i].score);
		++numofexpert;
	}
	fclose(fp);
	while(1){
		settextstyle(40, 0, _T("华文新魏"));
		settextcolor(BLACK);
		outtextxy(0.3*window_length,0.1*window_width,"1.显示");
		outtextxy(0.3*window_length,0.2*window_width,"2.查询");
		outtextxy(0.3*window_length,0.6*window_width,"0.退出");
		outtextxy(0.3*window_length,0.7*window_width,"按对应数字键进入");
		while(!_kbhit());
		c=_getch();
		switch(c){
				case '1':{
				displayrank(img+7,easy,medium,expert); break;
				}
				case '2':{
					InputBox(dia, 10, "请输入查询的人信息","输入人名","",0,0,false);
					findper(dia,easy,medium,expert);
					break;
				 }
				default :{
						 goto hh;
				}
		}
		cleardevice();
		putimage(0,0,img+6);
	}
	hh:
	fp1=fopen("排行榜\\rating_easy.txt","w");
	for (i=0;i<numofeasy;++i){
		fprintf(fp1,"%s %lf\n",easy[i].name,easy[i].score);
	}
	fclose(fp1);
	fp1=fopen("排行榜\\rating_intermediate.txt","w");
	for (i=0;i<numofmedium;++i){
		fprintf(fp1,"%s %lf\n",medium[i].name,medium[i].score);
	}
	fclose(fp1);
	fp1=fopen("排行榜\\rating_expert.txt","w");
	for (i=0;i<numofexpert;++i){
		fprintf(fp1,"%s %lf\n",expert[i].name,expert[i].score);
	}
	fclose(fp1);
}
void findper(char* s,person* easy,person* medium,person* expert){
	int i;
	double sco=0;int findp=0;
	for (i=0;i<numofeasy;++i){
		if (strcmp(s,(easy+i)->name)==0){
			sco=(easy+i)->score;
			findp=1;
		}
	}
	if (!findp){
		HWND hwnd=GetHWnd();
		int id=MessageBox(hwnd,"未找到信息","",MB_OKCANCEL);
		while(!_kbhit());
		_getch();
	}else{
		cleardevice();
		setcolor(RED);
		setbkcolor(GREEN);
		char t[1000]={0};
		sprintf(t,"%.1lf",sco);
		char st[1000]={0};
		strcpy(st,s);
		strcat(st," : ");
		strcat(st,t);
		outtextxy(0.3*window_length,0.5*window_width,st);
		while(!_kbhit());
		_getch();
	}
	return;
}