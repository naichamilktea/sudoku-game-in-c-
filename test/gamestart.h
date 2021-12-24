#include <time.h>
void set2menu(IMAGE* img)
{
	putimage(0,0,img);
	settextstyle(40, 0, _T("����"));
	outtextxy(0.3*window_length,0.1*window_width,"��ѡ���������������Ŀ���в���");
	outtextxy(0.3*window_length,0.2*window_width,"1.������Ŀ");
	outtextxy(0.3*window_length,0.3*window_width,"2.�޸���Ŀ(���������Ӷ����Ŀ��Ĭ���޸����һ����Ŀ)");
	outtextxy(0.3*window_length,0.4*window_width,"3.ɾ����Ŀ(���������Ӷ����Ŀ��Ĭ���޸����һ����Ŀ)");
	outtextxy(0.3*window_length,0.5*window_width,"4.���Ҹ���Ŀ�Ƿ���֮ǰ������Ŀ�ظ�");
	outtextxy(0.3*window_length,0.6*window_width,"5.������Ŀ���м�������");
}
void startmenu(IMAGE* img){
	putimage(0,0,img);
	settextstyle(40, 0, _T("����"));
	outtextxy(0.3*window_length,0.1*window_width,"�밴��Ӧ����ѡ���Ѷ�");
	outtextxy(0.3*window_length,0.2*window_width,"1.easy");
	outtextxy(0.3*window_length,0.3*window_width,"2.intermediate");
	outtextxy(0.3*window_length,0.4*window_width,"3.expert");
	outtextxy(0.3*window_length,0.5*window_width,"4.�û�������Ŀ");
}
void gamestart(IMAGE* img){
	char diag[1000];
	int x,y,num,n;
	clock_t start_time,end_time;
	cleardevice();
	board* brd=initboard();
	assert(brd);//�������ڴ�ʧ���������ֹ
	putimage(0,0,&img[0]);
	drawboard(&img[1]);
	char bank1[300][82]={0},bank2[300][82]={0},bank3[300][82]={0},bank4[300][82]={0},bank5[300][82]={0};
	FILE *fp1=fopen("���\\easy.txt","r");
	for(n=0;!feof(fp1);n++){
		fgets(bank1[n],82,fp1);
		bank1[n][81]='\0';}
	fclose(fp1);
	FILE *fp2=fopen("���\\intermediate.txt","r");
	for(n=0;!feof(fp2);n++){
		fgets(bank2[n],82,fp2);
		bank2[n][81]='\0';}
	fclose(fp2);
	FILE *fp3=fopen("���\\expert.txt","r");
	for(n=0;!feof(fp3);n++){
		fgets(bank3[n],82,fp3);
		bank3[n][81]='\0';}
	fclose(fp3);
	FILE *fp4=fopen("���\\set.txt","r");
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
		//brd���� ��ά����[9][9] �������һ���� ����ȡbank��һ��  �ŵ�9��9��������
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
	while(1){//�������������¼�
		InputBox(diag, 10, "�������У��к�Ҫ�����ֵ��0��ʾ��գ��м��ÿո����,\n,��0 0 0����ʾ��ֹ����","��������","",0,0,false);
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
				drawwrongnumber(img+1,brd,x-1,y-1);
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
	settextcolor(WHITE);
	outtextxy(0.4*window_length,0.9*window_width,"��R�ɻָ����룬k���鿴����ʱ�䣬��������������");
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
			setbkcolor(WHITE);
			cleardevice();
			if (finish(brd)){
				outtextxy(0.5*window_length,0.09*window_width,"��ϲ���У�����ͨ�ء�");
			}else{
				outtextxy(0.5*window_length,0.09*window_width,"���ź�����δ��ɡ�");
			}
			outtextxy(0.5*window_length,0.2*window_width,"�����õ�ʱ��Ϊ����s��");
			outtextxy(0.5*window_length,0.5*window_width,s);
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