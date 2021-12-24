void show1(IMAGE* img);//显示游戏介绍
void show2(IMAGE* img);//显示操作帮助
void helpwindow(IMAGE* img){
	cleardevice();
	settextstyle(45, 0, _T("宋体"));
	char c=0;
	while(c!='0'){
	putimage(0,0,img+2);
		outtextxy(0.3*window_length,0.1*window_width,"1.游戏玩法");
		outtextxy(0.3*window_length,0.3*window_width,"2.操作规则");
		outtextxy(0.3*window_length,0.7*window_width,"0.退出");
		outtextxy(0.3*window_length,0.5*window_width,"按对应数字键进入");
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
	settextstyle(25, 0, _T("宋体"));
	settextcolor(GREEN);
	outtextxy(0.1*window_length,0.1*window_width,"数独(shudu)是缘自18世纪瑞士的一种数字游戏。是一种运用纸");
	outtextxy(0.1*window_length,0.2*window_width,"、笔进行演算的逻辑游戏。玩家需要根据9*9盘面上的已知数字");
	outtextxy(0.1*window_length,0.3*window_width,"，推理出所有剩余空格的数字，并满足每一行，每一列，每一");
	outtextxy(0.1*window_length,0.4*window_width,"，个粗线宫（3*3）内的数字均含1-9，不重复。数独盘面是个");
	outtextxy(0.1*window_length,0.5*window_width,"九宫，每一宫又分为九个小格。在这81格中给出一定的已知数字");
	outtextxy(0.1*window_length,0.6*window_width,"和解题条件，利用逻辑和推理，在其他的空格上填入1-9的数字");
	outtextxy(0.1*window_length,0.7*window_width,"，使1-9每个数字在每一行、每一列和每一宫中都只出现一次，所");
	outtextxy(0.1*window_length,0.8*window_width,"以又称“九宫格”。");
	settextcolor(RED);
	_getch();
}
void show2(IMAGE* img){
	cleardevice();
	settextstyle(25, 0, _T("宋体"));
	settextcolor(GREEN);
	putimage(0,0,img+2);
	outtextxy(0.1*window_length,0.1*window_width,"R:开始输入");
	outtextxy(0.1*window_length,0.2*window_width,"1-9：输入数字1-9");
	outtextxy(0.1*window_length,0.3*window_width,"回车：结束本次输入");
	outtextxy(0.1*window_length,0.4*window_width,"K：查看已用时间");
	outtextxy(0.1*window_length,0.5*window_width,"目前在模式1里采用对话框的形式输入，在模式2里采用鼠标-键盘");
	outtextxy(0.1*window_length,0.6*window_width,"的方式读入数据");
	outtextxy(0.1*window_length,0.7*window_width,"每次打开程序时，要重新调整图像设置。");
	_getch();
}