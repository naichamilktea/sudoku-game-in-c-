void initwindow(IMAGE* img){
	putimage(0,0,img);
	settextstyle(40, 0, _T("������κ"));
	settextcolor(RED);
	outtextxy(0.6*window_length,0.17*window_width,"1.��ʼ��Ϸ");
	outtextxy(0.6*window_length,0.295*window_width,"2.������");
	outtextxy(0.6*window_length,0.420*window_width,"3.���а�");
	outtextxy(0.6*window_length,0.540*window_width,"4.����");
	outtextxy(0.6*window_length,0.655*window_width,"5.������Ŀ");
	outtextxy(0.6*window_length,0.780*window_width,"0.�˳�");
	}