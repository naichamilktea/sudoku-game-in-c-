void set(IMAGE* img){
	setbkcolor(WHITE);
	cleardevice();
	putimage(0,0,img+2);
	char input;
	while(1){
	outtextxy(0.3*window_length,0.1*window_width,"1.设置图片");
	outtextxy(0.3*window_length,0.3*window_width,"2.设置声音");
	outtextxy(0.3*window_length,0.5*window_width,"3.设置音量");
	outtextxy(0.3*window_length,0.7*window_width,"0.退出");
	outtextxy(0.3*window_length,0.9*window_width,"按对应数字键进入");
	while(!_kbhit());
	input=_getch();
	}
	while(!_kbhit());
	_getch();
}