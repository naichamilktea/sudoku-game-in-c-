void show1(IMAGE* img);//��ʾ��Ϸ����
void show2(IMAGE* img);//��ʾ��������
void helpwindow(IMAGE* img){
	cleardevice();
	settextstyle(45, 0, _T("����"));
	char c=0;
	while(c!='0'){
	putimage(0,0,img+2);
		outtextxy(0.3*window_length,0.1*window_width,"1.��Ϸ�淨");
		outtextxy(0.3*window_length,0.3*window_width,"2.��������");
		outtextxy(0.3*window_length,0.7*window_width,"0.�˳�");
		outtextxy(0.3*window_length,0.5*window_width,"����Ӧ���ּ�����");
		while(!_kbhit());
		c=_getch();
		switch(c){
		case '1':{
			show1(img);
				 break;}
		case '2':{
			show2(img);break;
				 }
		case '0':{
				 return;}
		}
	}
	while(!_kbhit());
	_getch();
}
void show1(IMAGE* img){
	cleardevice();
	putimage(0,0,img+2);
	settextstyle(25, 0, _T("����"));
	settextcolor(GREEN);
	outtextxy(0.1*window_length,0.1*window_width,"����(shudu)��Ե��18������ʿ��һ��������Ϸ����һ������ֽ");
	outtextxy(0.1*window_length,0.2*window_width,"���ʽ���������߼���Ϸ�������Ҫ����9*9�����ϵ���֪����");
	outtextxy(0.1*window_length,0.3*window_width,"�����������ʣ��ո�����֣�������ÿһ�У�ÿһ�У�ÿһ");
	outtextxy(0.1*window_length,0.4*window_width,"�������߹���3*3���ڵ����־���1-9�����ظ������������Ǹ�");
	outtextxy(0.1*window_length,0.5*window_width,"�Ź���ÿһ���ַ�Ϊ�Ÿ�С������81���и���һ������֪����");
	outtextxy(0.1*window_length,0.6*window_width,"�ͽ��������������߼��������������Ŀո�������1-9������");
	outtextxy(0.1*window_length,0.7*window_width,"��ʹ1-9ÿ��������ÿһ�С�ÿһ�к�ÿһ���ж�ֻ����һ�Σ���");
	outtextxy(0.1*window_length,0.8*window_width,"���ֳơ��Ź��񡱡�");
	settextcolor(RED);
	_getch();
}
void show2(IMAGE* img){
	cleardevice();
	settextstyle(25, 0, _T("����"));
	settextcolor(GREEN);
	putimage(0,0,img+2);
	outtextxy(0.1*window_length,0.1*window_width,"R:��ʼ����");
	outtextxy(0.1*window_length,0.2*window_width,"1-9����������1-9");
	outtextxy(0.1*window_length,0.3*window_width,"�س���������������");
	outtextxy(0.1*window_length,0.4*window_width,"K���鿴����ʱ��");
	outtextxy(0.1*window_length,0.5*window_width,"Ŀǰ��ģʽ1����öԻ������ʽ���룬��ģʽ2��������-����");
	outtextxy(0.1*window_length,0.6*window_width,"�ķ�ʽ��������");
	outtextxy(0.1*window_length,0.7*window_width,"ÿ�δ򿪳���ʱ��Ҫ���µ���ͼ�����á�");
	_getch();
}