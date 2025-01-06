int N;  //һ���ж��ٻʺ�
int q[N+1];  //ÿ�лʺ��Ӧ���к� 
bool col[N+1];  //���ڵ��кŵļ�֦ 
bool diag1[N*2+1]; //���Խ��ߵļ�֦ 
bool diag2[N*2+1]; //���Խ��ߵļ�֦ 

//������Է��ûʺ�
bool randomplace(int n){
	
	
	for(int i=1;i<=n;i++){
		
		//�������кϷ��е�λ��
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
//���ûʺ�������
void place(int k,int n)  
{
	if(k>n)
		print(n);
	else
	{
		for(int j=1;j<=n;j++)   //��̽��k�е�ÿһ����
		{
			if(!col[j] && !diag1[k+j] && !diag2[k-j+n])
			{
				q[k] = j;
				col[j]=true;  //����б�ռ�� 
				diag1[k+j]=true;  //������Խ��߱�ռ��
				diag2[k-j+n]=true;  //��Ǹ��Խ��߱�ռ�� 
				place(k+1,n);  //�ݹ������ڳɹ�������ϴε������ʱ�������һ������
				
				//�س����
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
		
		cout<<"������ѡ�����"<<endl;
	}
	print(n);
	
	return 0; 
}
 
