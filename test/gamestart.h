#include <time.h>
void set2menu(IMAGE* img)
{
	putimage(0,0,img);
	settextstyle(40, 0, _T("宋体"));
	outtextxy(0.3*window_length,0.1*window_width,"请选择数字针对已设题目进行操作");
	outtextxy(0.3*window_length,0.2*window_width,"1.增加题目");
	outtextxy(0.3*window_length,0.3*window_width,"2.修改题目(若设置增加多道题目，默认修改最后一道题目)");
	outtextxy(0.3*window_length,0.4*window_width,"3.删除题目(若设置增加多道题目，默认修改最后一道题目)");
	outtextxy(0.3*window_length,0.5*window_width,"4.查找改题目是否与之前已设题目重复");
	outtextxy(0.3*window_length,0.6*window_width,"5.不对题目进行继续设置");
}
void startmenu(IMAGE* img){
	putimage(0,0,img);
	settextstyle(40, 0, _T("宋体"));
	outtextxy(0.3*window_length,0.1*window_width,"请按对应数字选择难度");
	outtextxy(0.3*window_length,0.2*window_width,"1.easy");
	outtextxy(0.3*window_length,0.3*window_width,"2.intermediate");
	outtextxy(0.3*window_length,0.4*window_width,"3.expert");
	outtextxy(0.3*window_length,0.5*window_width,"4.用户设置题目");
}
void gamestart(IMAGE* img){
	char diag[1000];
	int x,y,num,n;
	clock_t start_time,end_time;
	cleardevice();
	board* brd=initboard();
	assert(brd);//若申请内存失败则程序终止
	putimage(0,0,&img[0]);
	drawboard(&img[1]);
	char bank1[300][82]={0},bank2[300][82]={0},bank3[300][82]={0},bank4[300][82]={0},bank5[300][82]={0};
	FILE *fp1=fopen("题库\\easy.txt","r");
	for(n=0;!feof(fp1);n++){
		fgets(bank1[n],82,fp1);
		bank1[n][81]='\0';}
	fclose(fp1);
	FILE *fp2=fopen("题库\\intermediate.txt","r");
	for(n=0;!feof(fp2);n++){
		fgets(bank2[n],82,fp2);
		bank2[n][81]='\0';}
	fclose(fp2);
	FILE *fp3=fopen("题库\\expert.txt","r");
	for(n=0;!feof(fp3);n++){
		fgets(bank3[n],82,fp3);
		bank3[n][81]='\0';}
	fclose(fp3);
	FILE *fp4=fopen("题库\\set.txt","r");
	for(n=0;!feof(fp4);n++){
		fgets(bank4[n],82,fp4);
		bank4[n][81]='\0';}
	fclose(fp4);
	srand((unsigned)time(NULL));
	int t=rand()%200,i,a;
	char input='-';
	while(input!='+')
	{
		startmenu(&img[0]);
		while(!_kbhit());
		input=_getch();
		fflush(stdin);
		//brd变量 二维数组[9][9] 随机生成一个数 任意取bank的一行  放到9×9数组里面
		switch(input)
		{
			case '1':
				{
					    for(i=0;i<9;i++)
							for(a=0;a<9;a++)
							    sscanf_s(&bank1[t][n++],"%d",&brd->data[i][a]);			
		        }break;
			case '2':
				{
					    for(i=0;i<9;i++)
							for(a=0;a<9;a++)
							  sscanf_s(&bank2[t][n++],"%d",&brd->data[i][a]);	
		        }break;
			case '3':
				{
					    for(i=0;i<9;i++)
							for(a=0;a<9;a++)
							   sscanf_s(&bank3[t][n++],"%d",&brd->data[i][a]);	
		        }break;
			case '4':
				{
					    for(i=0;i<9;i++)
							for(a=0;a<9;a++)
							     sscanf_s(&bank4[t][n++],"%d",&brd->data[i][a]);	
		        }break;
			default:break;
	}
	drawnumber(brd);
	start_time=clock();
	here:
	while(1){//持续监听输入事件
		InputBox(diag, 10, "请输入行，列和要填入的值，0表示清空，中间用空格隔开,\n,“0 0 0”表示终止输入","输入数据","",0,0,false);
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
				drawwrongnumber(img+1,brd,x-1,y-1);
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
	settextcolor(WHITE);
	outtextxy(0.4*window_length,0.9*window_width,"按R可恢复输入，k键查看已用时间，其他键结束输入");
	settextcolor(RED);
	char input;
	while(!_kbhit());
	input=_getch();
	if (input=='r')goto here;
	if (input=='k'){
		clock_t current=clock();
		int curtime=current-start_time;
		double curi=curtime*1.0/1000;
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
			setbkcolor(WHITE);
			cleardevice();
			if (finish(brd)){
				outtextxy(0.5*window_length,0.09*window_width,"恭喜大佬，您已通关。");
			}else{
				outtextxy(0.5*window_length,0.09*window_width,"很遗憾，您未完成。");
			}
			outtextxy(0.5*window_length,0.2*window_width,"您所用的时间为：（s）");
			outtextxy(0.5*window_length,0.5*window_width,s);
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