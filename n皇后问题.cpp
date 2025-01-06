int N;  //一共有多少皇后
int q[N+1];  //每行皇后对应的列号 
bool col[N+1];  //所在的列号的剪枝 
bool diag1[N*2+1]; //主对角线的剪枝 
bool diag2[N*2+1]; //副对角线的剪枝 

//随机尝试放置皇后
bool randomplace(int n){
	
	
	for(int i=1;i<=n;i++){
		
		//生成所有合法列的位置
		int candidates[N+1];
		int count=0;
		for(int k=1;k<=n;k++){
			
			if(!col[k] && !diag1[i+k] && !diag2[i-k+n]){
				
				candidates[++count]=k;
			}
		} 
		if(count==0) return false;
		
		int randomindex=rand()%count;
		int chosencol=candidates[randomindex+1];
		q[i]=chosencol;
		col[chosencol]=true;
		diag1[i+chosencol]=true;
		diag2[i-chosencol+n]=true;
	}
	return true;
} 
//放置皇后到棋盘上
void place(int k,int n)  
{
	if(k>n)
		print(n);
	else
	{
		for(int j=1;j<=n;j++)   //试探第k行的每一个列
		{
			if(!col[j] && !diag1[k+j] && !diag2[k-j+n])
			{
				q[k] = j;
				col[j]=true;  //标记列被占用 
				diag1[k+j]=true;  //标记主对角线被占用
				diag2[k-j+n]=true;  //标记副对角线被占用 
				place(k+1,n);  //递归总是在成功完成了上次的任务的时候才做下一个任务
				
				//回撤标记
				col[j]=false;
				diag1[k+j]=false;
				diag2[k-j+n]=false; 
			}
		}
	}
}
int main(){
	
	srand(time(0));
	while(!randomplace(N)){
		
		cout<<"输出随机选择错误"<<endl;
	}
	print(n);
	
	return 0; 
}
 
