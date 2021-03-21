#include<iostream>
#include<curses.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
using namespace std;

class ConsumerAndProducer
{
	public:
		ConsumerAndProducer()
		{
			ProducerAmount=0; //��l���Ͳ��̼ƶq��0 
			ComsumerAmount=0; //��l�����O�̼ƶq��0 
			for(int i=0;i<80;i++) //��l�������m�O�_���Ͳ���/���O�̪��}�C�������]��0�A���ʦ��Ƥ]���O�]��0; 
			{
				for(int j=0;j<24;j++)
				{
					PositionsProducersAt[i][j]=0;
					PositionsConsumersAtMoveZeroTimes[i][j]=0;
					PositionsConsumersAtMoveOneTimes[i][j]=0;
					PositionsConsumersAtMovetwoTimes[i][j]=0;
					PositionsConsumersAtMovethreeTimes[i][j]=0;
				}
			}
			unitTime=1;
		}
		void setProducer(int x); //�]�w�Ͳ��̪��ƶq 
		void setConsumer(int x); //�]�w���O�̪��ƶq
		void InitialPositionsProducerAt(); //�]�w�Ͳ��̪���l��m 
		void InitialPositionsConsumerAt(); //�]�w���O�̪�l����m
		void ShowThePositionsProducersAt(); //�i�ܥͲ��̪���m 
		void ShowThePositionsConsumersAt(); //�i�ܮ��O�̪���m
		/*---------------------�w�g���ʹLn�������O�̪�����--------------------------------------*/
		void movingOfConsumerZeroTimes(); //�M�w�w�g���ʹL0�������O�̭n�p�󲾰�
		void movingOfConsumerOneTimes(); //�M�w�w�g���ʹL1�������O�̭n�p�󲾰�
		void movingOfConsumerTwoTimes(); //�M�w�w�g���ʹL2�������O�̭n�p�󲾰� 
		void movingOfConsumerThreeTimes(); //�M�w�w�g���ʹL3�������O�̭n�p�󲾰�
		int deathOfConsumer(int x,int y); //���O�̦���  
		/*-------------------�Ͳ��̪��ƻs�覡-----------------------------------*/
		void checkWhetherProducersCanCopy(); //�T�{�Ͳ��̬O�_��ƻs(�bunitTime==4���ɭԤ~��ƻs)
		void copyOfProducer(); //�M�w�Ͳ��̭n�p��ƻs 
		void copyToOtherPositions0OfProducer(int x,int y);
		void copyToOtherPositions1OfProducer(int x,int y);
		void copyToOtherPositions2OfProducer(int x,int y);
		void copyToOtherPositions3OfProducer(int x,int y);
		void copyToOtherPositions4OfProducer(int x,int y);
		void copyToOtherPositions5OfProducer(int x,int y);
		void copyToOtherPositions6OfProducer(int x,int y);
		void copyToOtherPositions7OfProducer(int x,int y);
		/*-------------------���O�̪����ʤ覡-----------------------------------*/
		void moveToOtherPositions0OfConsumer(int &x,int &y);
		void moveToOtherPositions1OfConsumer(int &x,int &y);
		void moveToOtherPositions2OfConsumer(int &x,int &y);
		void moveToOtherPositions3OfConsumer(int &x,int &y);
		void moveToOtherPositions4OfConsumer(int &x,int &y);
		void moveToOtherPositions5OfConsumer(int &x,int &y);
		void moveToOtherPositions6OfConsumer(int &x,int &y);
		void moveToOtherPositions7OfConsumer(int &x,int &y);
		/*----------------------------------------------------------------------*/ 
		bool checkWhetherThePositionHaveConsumers(int x,int y);
		bool checkWhetherThePositionHaveProducers(int x,int y);
 
		void addUnitTime(); //�W�[���ɶ�
		
	private:
		int ComsumerAmount; //���O�̼ƶq 
		int ProducerAmount;  //�Ͳ��̼ƶq 
		int PositionsProducersAt[80][24]; //�����Ӧ�m�O�_��"�Ͳ���"���G���}�C
		int unitTime; //��unitTime==4�A�Ͳ��̫h�i�H�i��ƻs���ʧ@ 
		//int agesOfComsumer[80][24]; //�ΤG���}�C�h�����C�Ӯ��O�̪��ةR�A����4�ɷ|���`�A�ӦY��Ͳ��̮ɥi�H�^�k1
		int PositionsConsumersAtMoveZeroTimes[80][24]; //���O�̲��ʹs����N������Ӧ�m��ƥ�i�o�Ӱ}�C
		int PositionsConsumersAtMoveOneTimes[80][24]; //���O�̲��ʤ@����N������Ӧ�m��ƥ�i�o�Ӱ}�C 
		int PositionsConsumersAtMovetwoTimes[80][24]; //���O�̲��ʨ⦸��N������Ӧ�m��ƥ�i�o�Ӱ}�C 
		int PositionsConsumersAtMovethreeTimes[80][24]; //���O�̲��ʤT����N������Ӧ�m��ƥ�i�o�Ӱ}�C
		//���O�̲��ʲĥ|���N���F 
		 
};

void ConsumerAndProducer::addUnitTime()
{
	unitTime++;
}
void ConsumerAndProducer::setProducer(int x) //�]�w�Ͳ��̪��ƶq 
{
	ProducerAmount=x;	
} 
void ConsumerAndProducer::setConsumer(int x) //�]�w���O�̪��ƶq
{
	ComsumerAmount=x;
}
void ConsumerAndProducer::InitialPositionsProducerAt() //�]�w�Ͳ��̪�l����m 
{
	int PositionX;
	int PositionY;
	srand(time(0));
	for(int i=0;i<ProducerAmount;i++)
	{
		bool check=false;
		while(!check)
			{
				PositionX=rand()%79+1; //�üƩ���Ͳ��̪�X�MY�y�Ц�m�A�M���Ӧ�m���}�C�]��2�A��ܨ��Ӧ�m���Ͳ��̪��s�b
				PositionY=rand()%23+1; //�y�жb�d�� x=1~79,y=1~23; (x=0��x=80�O��Ay=0��y=24�O��) 
				if(!(checkWhetherThePositionHaveProducers(PositionX,PositionY)||checkWhetherThePositionHaveConsumers(PositionX,PositionY)))  
				{ //���������T�{���Ӧ�m���ӨS���Ͳ��̩ή��O�̤~���
					PositionsProducersAt[PositionX][PositionY]=2;
					check=true;                                  //�T�w"�Ͳ��̩񦨥\"��~�൲��while�j�� 
				}
				else	 //���Y�O���Ӧ�m�w�g���Ͳ��̪��s�b�A�h�ݭn���s�A�� 
					continue;
			}
	}		
}
		
void ConsumerAndProducer::InitialPositionsConsumerAt() //�]�w���O�̪�l����m
{
	int PositionX;
	int PositionY;
	srand(time(0));
	for(int i=0;i<ComsumerAmount;i++)
	{
		bool check=false;
		while(!check)
			{
				PositionX=rand()%79+1; //�üƩ�����O�̪�X�MY�y�Ц�m�A�M���Ӧ�m���}�C�]��1�A��ܨ��Ӧ�m�����O�̪��s�b
				PositionY=rand()%23+1; //�y�жb�d�� x=1~79,y=1~23; (x=0��x=80�O��Ay=0��y=24�O��) 
				if(!(checkWhetherThePositionHaveProducers(PositionX,PositionY)||checkWhetherThePositionHaveConsumers(PositionX,PositionY))) //���������T�{���Ӧ�m���ӨS�����O�̩ΥͲ��̤~��� 
				{
					PositionsConsumersAtMoveZeroTimes[PositionX][PositionY]=1; //���O�̦�m�n���"�w�g����0�����}�C��Ƹ̭��h" 
					check=true;                                  //�T�w"���O�̩񦨥\"��~�൲��while�j�� 
				}
				else	 //���Y�O���Ӧ�m�w�g�����O��/�Ͳ��̪��s�b�A�h�ݭn���s�A�� 
					continue;
			}
	}	
}
void ConsumerAndProducer::ShowThePositionsProducersAt() //�i�ܥͲ��̪���m
{
	for(int i=0;i<80;i++) 
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsProducersAt[i][j]==2) //�Y�O�Ӱ}�C��m��Ƭ�2�A�h�N���䦳�Ͳ��̪�
			{	
				mvaddch(j,i,'|'); //|:�Ͳ��̪��лx 
			} 
		}
	}
} 
void ConsumerAndProducer::ShowThePositionsConsumersAt() //�i�ܮ��O�̪���m 
{
	for(int i=0;i<80;i++) 
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMoveZeroTimes[i][j]==1||PositionsConsumersAtMoveOneTimes[i][j]==1||PositionsConsumersAtMovetwoTimes[i][j]==1||PositionsConsumersAtMovethreeTimes[i][j]==1)
			{   //�Y�O�Ӱ}�C��m��Ƭ�1�A�h�N���䦳���O��	
				mvaddch(j,i,'&'); //&:���O�̪��лx 
			} 
		}
	}
	Sleep(100);
   	refresh(); 
   	clear();
}
void ConsumerAndProducer::checkWhetherProducersCanCopy() //�T�{�Ͳ��̬O�_�i�H�ƻs 
{
	if(unitTime==4)
	{
		copyOfProducer();
	} 
}
void ConsumerAndProducer::copyOfProducer() //�M�w�Ͳ��̭n�p��ƻs
{
	int copyToOtherPositions;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsProducersAt[i][j]==2)//�}�C�q�Y�����A�Y�����O��2���}�C��m�A�h�Ӧ�m������"�Ͳ��̽ƻs"���ʧ@ 
			{
				copyToOtherPositions=rand()%8+0; //��0~7�����ʦ�m�i�� 

				switch(copyToOtherPositions)
				{
					case 0:
						copyToOtherPositions0OfProducer(i,j);
						break;
				
					case 1:						
						copyToOtherPositions1OfProducer(i,j);
						break;

					case 2:
						copyToOtherPositions2OfProducer(i,j);
						break; 				
		
					case 3:
						copyToOtherPositions3OfProducer(i,j);
						break; 
						
					case 4:
						copyToOtherPositions4OfProducer(i,j);
						break; 					
					
					case 5:
						copyToOtherPositions5OfProducer(i,j);
						break; 			
					
					case 6:
						copyToOtherPositions6OfProducer(i,j);
						break;
						
					case 7:
						copyToOtherPositions7OfProducer(i,j);
						break;  		
					}
				}
		}

	}
	unitTime=1; //�NunitTime��l�Ƭ�1	
} 

void ConsumerAndProducer::movingOfConsumerZeroTimes() //�M�w����0�������O�̭n�p�󲾰� 
{														//�����o�Ӱʧ@���󲾰ʤF�@�� 
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMoveZeroTimes[i][j]==1)//�w�g���ʹL0�������O�̱q�Y�����A�Y�����O��1���}�C��m�A�h�Ӧ�m������"���O�̲���"���ʧ@ 
			{
				PositionsConsumersAtMoveZeroTimes[i][j]=0;//���޽ƻs���\�Υ��ѡA����O���@���ʧ@�A�]���ʧ@�Ʒ|�[�@�A�쥻���ʧ@�ƫh�n�k�s 
				initialPositionX=i;
				initialPositionY=j;
				moveToOtherPositions=rand()%8+0; //��0~7�����ʦ�m�i�� 
				switch(moveToOtherPositions)
				{
					case 0:
						moveToOtherPositions0OfConsumer(i,j);
						break;
				
					case 1:						
						moveToOtherPositions1OfConsumer(i,j);
						break;

					case 2:
						moveToOtherPositions2OfConsumer(i,j);
						break; 				
		
					case 3:
						moveToOtherPositions3OfConsumer(i,j);
						break; 
						
					case 4:
						moveToOtherPositions4OfConsumer(i,j);
						break; 					
					
					case 5:
						moveToOtherPositions5OfConsumer(i,j);
						break; 			
					
					case 6:
						moveToOtherPositions6OfConsumer(i,j);
						break;
						
					case 7:
						moveToOtherPositions7OfConsumer(i,j);
						break;  		
				}
				if(PositionsProducersAt[i][j]==2) //�p�G�Y��Ͳ���
				{
					PositionsProducersAt[i][j]=0;
					PositionsConsumersAtMoveZeroTimes[i][j]=1; //�Ͳ��̪����Ӧ�m�ƻs�@���s�� 
					PositionsConsumersAtMoveOneTimes[initialPositionX][initialPositionY]=1; //�쥻����m���@���쥻�� 
				}
				else //�S�Y��Ͳ��̴N���ʨ�O���a��h 
				{ 
					PositionsConsumersAtMoveOneTimes[i][j]=1;
				}			
			}
		}
	}
}
void ConsumerAndProducer::movingOfConsumerOneTimes()  //�M�w�w�g����1�������O�̭n�p�󲾰� 
{
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMoveOneTimes[i][j]==1)//�w�g����1�������O�̰}�C�q�Y�����A�Y�����O��1���}�C��m�A�h�Ӧ�m������"���O�̲���"���ʧ@ 
			{
				PositionsConsumersAtMoveOneTimes[i][j]=0;
				initialPositionX=i;
				initialPositionY=j;
				moveToOtherPositions=rand()%8+0; //��0~7�����ʦ�m�i�� 
				switch(moveToOtherPositions)
				{
					case 0:
						moveToOtherPositions0OfConsumer(i,j);
						break;
				
					case 1:						
						moveToOtherPositions1OfConsumer(i,j);
						break;

					case 2:
						moveToOtherPositions2OfConsumer(i,j);
						break; 				
		
					case 3:
						moveToOtherPositions3OfConsumer(i,j);
						break; 
						
					case 4:
						moveToOtherPositions4OfConsumer(i,j);
						break; 					
					
					case 5:
						moveToOtherPositions5OfConsumer(i,j);
						break; 			
					
					case 6:
						moveToOtherPositions6OfConsumer(i,j);
						break;
						
					case 7:
						moveToOtherPositions7OfConsumer(i,j);
						break;  		
				}
				if(PositionsProducersAt[i][j]==2) //�p�G�Y��Ͳ���
				{
					PositionsProducersAt[i][j]=0; //�Ͳ��̪���m�}�C����ܦ�0 
					PositionsConsumersAtMoveZeroTimes[i][j]=1; //�Ͳ��̪����Ӧ�m�ƻs�@�� 
					PositionsConsumersAtMovetwoTimes[initialPositionX][initialPositionY]=1; //�쥻����m�]���@���ª� 
				}
				else //�S�Y��Ͳ��̴N���O���a�貾�� 
				{
					PositionsConsumersAtMovetwoTimes[i][j]=1;
				}
			}
		}
	}	
} 
void ConsumerAndProducer::movingOfConsumerTwoTimes()  //�M�w�w�g����2�������O�̭n�p�󲾰�
{
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMovetwoTimes[i][j]==1)//�w�g����2�������O�̰}�C�q�Y�����A�Y�����O��1���}�C��m�A�h�Ӧ�m������"���O�̲���"���ʧ@ 
			{
				PositionsConsumersAtMovetwoTimes[i][j]=0;
				moveToOtherPositions=rand()%8+0; //��0~7�����ʦ�m�i�� 
				switch(moveToOtherPositions)
				{
					case 0:
						moveToOtherPositions0OfConsumer(i,j);
						break;
				
					case 1:						
						moveToOtherPositions1OfConsumer(i,j);
						break;

					case 2:
						moveToOtherPositions2OfConsumer(i,j);
						break; 				
		
					case 3:
						moveToOtherPositions3OfConsumer(i,j);
						break; 
						
					case 4:
						moveToOtherPositions4OfConsumer(i,j);
						break; 					
					
					case 5:
						moveToOtherPositions5OfConsumer(i,j);
						break; 			
					
					case 6:
						moveToOtherPositions6OfConsumer(i,j);
						break;
						
					case 7:
						moveToOtherPositions7OfConsumer(i,j);
						break;  		
				}
				if(PositionsProducersAt[i][j]==2) //�p�G�Y��Ͳ���
				{
					PositionsProducersAt[i][j]=0; //�Ͳ��̪���m�}�C����ܦ�0 
					PositionsConsumersAtMoveZeroTimes[i][j]=1;
					PositionsConsumersAtMovethreeTimes[initialPositionX][initialPositionY]=1; //�쥻����m�]���@���ª� 
	
				}
				else
				{
					PositionsConsumersAtMovethreeTimes[i][j]=1;
				}
			}
		}
	}
}
void ConsumerAndProducer::movingOfConsumerThreeTimes()  //�M�w�w�g����3�������O�̭n�p�󲾰� //�`�N �p�G�]��o�Ө禡�̭�
{                                         //�A�����ʧ@���٨S�Y��Ͳ��̡A�N�|�i�J���`�禡�k�s 
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMovethreeTimes[i][j]==1)//�w�g����3�������O�̰}�C�q�Y�����A�Y�����O��1���}�C��m�A�h�Ӧ�m������"���O�̲���"���ʧ@ 
			{
				PositionsConsumersAtMovethreeTimes[i][j]=0;
				moveToOtherPositions=rand()%8+0; //��0~7�����ʦ�m�i�� 
				switch(moveToOtherPositions)
				{
					case 0:
						moveToOtherPositions0OfConsumer(i,j);
						break;
				
					case 1:						
						moveToOtherPositions1OfConsumer(i,j);
						break;

					case 2:
						moveToOtherPositions2OfConsumer(i,j);
						break; 				
		
					case 3:
						moveToOtherPositions3OfConsumer(i,j);
						break; 
						
					case 4:
						moveToOtherPositions4OfConsumer(i,j);
						break; 					
					
					case 5:
						moveToOtherPositions5OfConsumer(i,j);
						break; 			
					
					case 6:
						moveToOtherPositions6OfConsumer(i,j);
						break;
						
					case 7:
						moveToOtherPositions7OfConsumer(i,j);
						break;		
				}
				if(PositionsProducersAt[i][j]!=2) //�S�Y��Ͳ��̴N���F 
				{
					deathOfConsumer(i,j);
				}
				else //�Y��Ͳ��� 
				{
					PositionsProducersAt[i][j]=0; //�Ͳ��̪���m�}�C����ܦ�0 
					PositionsConsumersAtMoveZeroTimes[i][j]=1;					
				} 
			}
		}
	}
}
int ConsumerAndProducer::deathOfConsumer(int x,int y)  //�Ӧ��������O�̷|�i��o�̳Q�B���A���Ӧ�m�}�C���=0
{
	PositionsConsumersAtMovethreeTimes[x][y]=0;	
}
void ConsumerAndProducer::copyToOtherPositions0OfProducer(int x,int y) //���W //��������ӫe���~�ন�\�ƻs 1.�S�W�L��� 2.�Ӧ�m�S���F
{
	x=x-1;
	y=y-1;
	if(x>=1&&y>=1) //�S���W�L��� 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y)))  //���Ӧ�m�S���F�� 
		{
			PositionsProducersAt[x][y]=2; //�Ͳ��� 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions0OfConsumer(int &x,int &y)
{
	if(x-1>=1&&y-1>=1) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x-1,y-1)) //�åB�Ӧ�m�S�����O�� 
		x=x-1;
		y=y-1;
	}	
}
void ConsumerAndProducer::copyToOtherPositions1OfProducer(int x,int y) //�W 
{
	x=x;
	y=y-1;
	if(y>=1) //�S���W�L��� 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //���Ӧ�m�S���F�� 
		{
			PositionsProducersAt[x][y]=2;  
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions1OfConsumer(int &x,int &y)
{
	if(y>=1) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x,y-1)) //�åB�Ӧ�m�S�����O��
		{	
			x=x;
			y=y-1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions2OfProducer(int x,int y) //�k�W
{
	x=x+1;
	y=y-1;
	if(x<=79&&y>=1) //�S���W�L��� 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //���Ӧ�m�S���F�� 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions2OfConsumer(int &x,int &y)
{
	if(x+1<=79&&y-1>=1) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x+1,y-1)) //�åB�Ӧ�m�S�����O��
		{
			x=x+1;
			y=y-1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions3OfProducer(int x,int y) //�k
{
	x=x+1;
	y=y;
	if(x<=79) //�S���W�L��� 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //���Ӧ�m�S���F�� 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions3OfConsumer(int &x,int &y)
{
	if(x+1<=79) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x+1,y)) //�åB�Ӧ�m�S�����O��
		{
			x=x+1;
			y=y;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions4OfProducer(int x,int y) //�k�U
{
	x=x+1;
	y=y+1;
	if(x<=79&&y<=23) //�S���W�L��� 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //���Ӧ�m�S���F�� 
		{
			PositionsProducersAt[x][y]=2;
		} 
	}			
}
void ConsumerAndProducer::moveToOtherPositions4OfConsumer(int &x,int &y)
{
	if(x+1<=79&&y+1<=23) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x+1,y+1)) //�åB�Ӧ�m�S�����O��
		{
			x=x+1;
			y=y+1;
		}
	}		
}
void ConsumerAndProducer::copyToOtherPositions5OfProducer(int x,int y) //�U 
{
	if(y+1<=23) //�S���W�L��� 
	{
		x=x;
		y=y+1;		
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //���Ӧ�m�S���F�� 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
} 
void ConsumerAndProducer::moveToOtherPositions5OfConsumer(int &x,int &y) 
{

	if(y+1<=23) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x,y+1)) //�åB�Ӧ�m�S�����O��
		{
			x=x;
			y=y+1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions6OfProducer(int x,int y) //���U 
{
	x=x-1;
	y=y+1;
	if(x>=1&&y<=23) //�S���W�L��� 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //���Ӧ�m�S���F�� 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions6OfConsumer(int &x,int &y)
{
	if(x-1>=1&&y+1<=23) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x-1,y+1)) //�åB�Ӧ�m�S�����O��
		{
			x=x-1;
			y=y+1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions7OfProducer(int x,int y) //��
{
	x=x-1;
	y=y;
	if(x>=1) //�S���W�L��� 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //���Ӧ�m�S���F�� 
		{
				PositionsProducersAt[x][y]=2; 
		} 
	}		
} 
void ConsumerAndProducer::moveToOtherPositions7OfConsumer(int &x,int &y)
{
	if(x-1>=1) //�S���W�L��� 
	{
		if(!checkWhetherThePositionHaveConsumers(x-1,y)) //�åB�Ӧ�m�S�����O��
		{
			x=x-1;
			y=y;
		}
	}	
}
bool ConsumerAndProducer::checkWhetherThePositionHaveProducers(int x,int y)
{
	if(PositionsProducersAt[x][y]==2) //�T�{�Ӧ�m���S���Ͳ��� 
		return true;
	else
		return false;	
}
bool ConsumerAndProducer::checkWhetherThePositionHaveConsumers(int x,int y)
{
	if(PositionsConsumersAtMoveZeroTimes[x][y]==1||PositionsConsumersAtMoveOneTimes[x][y]==1||PositionsConsumersAtMovetwoTimes[x][y]==1||PositionsConsumersAtMovethreeTimes[x][y]==1) //�T�{�Ӧ�m���S�����O�� 
		return true;
	else
		return false;
}

void createAWindow() //�إߤ�� 
{
	for(int i=0;i<=24;i++) //�إ��a�� 
	{
		mvaddch(i,0,'#'); //����
		mvaddch(i,80,'#');//�k�� 
	}
	for(int i=0;i<80;i++) //�إ߾�� 
	{
		mvaddch(0,i,'#');
		mvaddch(24,i,'#');
	}
}

int main()
{
	ConsumerAndProducer MyConsumer;
	int ThisIsAmountOfComsumer,ThisIsAmountOfProducer;
	cout<<"�п�J�Ͳ��̼ƶq"<<endl;
	cin>>ThisIsAmountOfProducer;
	cout<<"�п�J���O�̼ƶq"<<endl;
	cin>>ThisIsAmountOfComsumer;
	while(ThisIsAmountOfComsumer+ThisIsAmountOfProducer>=78*22) //���O�̥[�W�Ͳ��̼ƶq���i�W�L78*22
	{
		cout<<"�����~�I�Э��s��J���O�̩M�Ͳ��̪��ƶq:"<<endl;
		cout<<"�п�J�Ͳ��̼ƶq"<<endl;
		cin>>ThisIsAmountOfProducer;
		cout<<"�п�J���O�̼ƶq"<<endl;
		cin>>ThisIsAmountOfComsumer;
	}
	initscr();
		createAWindow(); //���إߵ��� 
		MyConsumer.setProducer(ThisIsAmountOfProducer); //�]�w�Ͳ��̪��ƶq		
		MyConsumer.setConsumer(ThisIsAmountOfComsumer); //�]�w���O�̪��ƶq
		MyConsumer.InitialPositionsProducerAt(); //��l�üƩ���Ͳ��̪��Ҧb��m 
		MyConsumer.InitialPositionsConsumerAt(); //��l�üƩ�����O�̪��Ҧb��m
		MyConsumer.ShowThePositionsProducersAt(); //�i�ܥX�Ͳ��̪���m
		MyConsumer.ShowThePositionsConsumersAt(); //�i�ܥX���O�̪���m
		while(1)
		{
			createAWindow(); //����
			MyConsumer.checkWhetherProducersCanCopy(); //�T�w�Ͳ��̥i�H�ƻs�A�o�Ө禡�|�t�d�I�s�ƻs�Ͳ��̪��禡 
			MyConsumer.movingOfConsumerThreeTimes(); //�M�w�w�g����3�������O�̭n�p�󲾰�
			MyConsumer.movingOfConsumerTwoTimes(); //�M�w�w�g����2�������O�̭n�p�󲾰�
			MyConsumer.movingOfConsumerOneTimes(); //�M�w�w�g����1�������O�̭n�p�󲾰�
			MyConsumer.movingOfConsumerZeroTimes(); //�M�w�w�g����0�������O�̭n�p�󲾰�	
			MyConsumer.ShowThePositionsProducersAt(); //�i�ܥX�Ͳ��̪���m 
			MyConsumer.ShowThePositionsConsumersAt(); //�i�ܥX���O�̪���m			

			MyConsumer.addUnitTime(); //�W�[�@���ɶ� 
		}
	endwin();
  
	return 0;
	system("pause");
}

