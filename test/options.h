void set(IMAGE* img){
	setbkcolor(WHITE);
	cleardevice();
	putimage(0,0,img+2);
	char input;
	while(1){
	outtextxy(0.3*window_length,0.1*window_width,"1.����ͼƬ");
	outtextxy(0.3*window_length,0.3*window_width,"2.��������");
	outtextxy(0.3*window_length,0.5*window_width,"3.��������");
	outtextxy(0.3*window_length,0.7*window_width,"0.�˳�");
	outtextxy(0.3*window_length,0.9*window_width,"����Ӧ���ּ�����");
	while(!_kbhit());
	input=_getch();
	}
	while(!_kbhit());
	_getch();
}