void backtrack(board* brd,int num_of_blank,int start,int hang[9][9],int lie[9][9],int gong[9][9],int blank[81][2],int* find){
	if (start==num_of_blank){
		*find=1;
		return;
	}
	int x=blank[start][0],y=blank[start][1],i;
	for (i=1;i<=9&&!(*find);++i){
		if (hang[x][i-1]||lie[y][i-1]||gong[x/3*3+y/3][i-1])continue;
		brd->data[x][y]=i;
		hang[x][i-1]=1;
		lie[y][i-1]=1;
		gong[x/3*3+y/3][i-1]=1;
		backtrack(brd,num_of_blank,start+1,hang,lie,gong,blank,find);
		if (*find)return;
		brd->data[x][y]=0;
		hang[x][i-1]=0;
		lie[y][i-1]=0;
		gong[x/3*3+y/3][i-1]=0;
	}
}
void solve(board* brd){
	int hang[9][9]={0};//行[i][j]表示第i+1行出现过数字j+1,下面以此类推
	int lie[9][9]={0};
	int gong[9][9]={0};
	int blank[100][2];//记录第i个空格xy坐标，储存在blank[i-1][0]和blank[i-1][i]中
	int num_of_blank=0;
	int i,j;
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			if (brd->data[i][j]){
				hang[i][brd->data[i][j]-1]=1;
				lie[j][brd->data[i][j]-1]=1;
				gong[i/3*3+j/3][brd->data[i][j]-1]=1;
			}else{
				blank[num_of_blank][0]=i;
				blank[num_of_blank++][1]=j;
			}
		}
	}
	int find=0;
	backtrack(brd,num_of_blank,0,hang,lie,gong,blank,&find);
}
int valid(board* brd){	//检查是否有效
	int hang[9][9]={0};//行[i][j]表示第i+1行出现过数字j+1,下面以此类推
	int lie[9][9]={0};
	int gong[9][9]={0};
	int i,j,num;
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			num=brd->data[i][j];
			if (num==0)continue;
			++hang[i][num-1];
			++lie[j][num-1];
			++gong[i/3*3+j/3][num-1];
		}
	}
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			if (hang[i][j]>=2||lie[i][j]>=2||gong[i][j]>=2){
				return 0;
			}
		}
	}
	return 1;
}
int finish(board* brd){	//检查是否完成
	int hang[9][9]={0};//行[i][j]表示第i+1行出现过数字j+1,下面以此类推
	int lie[9][9]={0};
	int gong[9][9]={0};
	int i,j,num;
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			num=brd->data[i][j];
			if (num==0)return 0;
			++hang[i][num-1];
			++lie[j][num-1];
			++gong[i/3*3+j/3][num-1];
		}
	}
	for (i=0;i!=9;++i){
		for (j=0;j!=9;++j){
			if (hang[i][j]!=1||lie[i][j]!=1||gong[i][j]!=1){
				return 0;
			}
		}
	}
	return 1;
}