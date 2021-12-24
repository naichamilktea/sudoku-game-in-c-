void initwindow(IMAGE* img){
	putimage(0,0,img);
	settextstyle(40, 0, _T("华文新魏"));
	settextcolor(RED);
	outtextxy(0.6*window_length,0.17*window_width,"1.开始游戏");
	outtextxy(0.6*window_length,0.295*window_width,"2.求解程序");
	outtextxy(0.6*window_length,0.420*window_width,"3.排行榜");
	outtextxy(0.6*window_length,0.540*window_width,"4.帮助");
	outtextxy(0.6*window_length,0.655*window_width,"5.增加题目");
	outtextxy(0.6*window_length,0.780*window_width,"0.退出");
	}