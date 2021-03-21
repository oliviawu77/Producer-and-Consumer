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
			ProducerAmount=0; //初始的生產者數量為0 
			ComsumerAmount=0; //初始的消費者數量為0 
			for(int i=0;i<80;i++) //初始把紀錄位置是否有生產者/消費者的陣列全部都設為0，移動次數也都是設為0; 
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
		void setProducer(int x); //設定生產者的數量 
		void setConsumer(int x); //設定消費者的數量
		void InitialPositionsProducerAt(); //設定生產者的初始位置 
		void InitialPositionsConsumerAt(); //設定消費者初始的位置
		void ShowThePositionsProducersAt(); //展示生產者的位置 
		void ShowThePositionsConsumersAt(); //展示消費者的位置
		/*---------------------已經移動過n次的消費者的移動--------------------------------------*/
		void movingOfConsumerZeroTimes(); //決定已經移動過0次的消費者要如何移動
		void movingOfConsumerOneTimes(); //決定已經移動過1次的消費者要如何移動
		void movingOfConsumerTwoTimes(); //決定已經移動過2次的消費者要如何移動 
		void movingOfConsumerThreeTimes(); //決定已經移動過3次的消費者要如何移動
		int deathOfConsumer(int x,int y); //消費者死掉  
		/*-------------------生產者的複製方式-----------------------------------*/
		void checkWhetherProducersCanCopy(); //確認生產者是否能複製(在unitTime==4的時候才能複製)
		void copyOfProducer(); //決定生產者要如何複製 
		void copyToOtherPositions0OfProducer(int x,int y);
		void copyToOtherPositions1OfProducer(int x,int y);
		void copyToOtherPositions2OfProducer(int x,int y);
		void copyToOtherPositions3OfProducer(int x,int y);
		void copyToOtherPositions4OfProducer(int x,int y);
		void copyToOtherPositions5OfProducer(int x,int y);
		void copyToOtherPositions6OfProducer(int x,int y);
		void copyToOtherPositions7OfProducer(int x,int y);
		/*-------------------消費者的移動方式-----------------------------------*/
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
 
		void addUnitTime(); //增加單位時間
		
	private:
		int ComsumerAmount; //消費者數量 
		int ProducerAmount;  //生產者數量 
		int PositionsProducersAt[80][24]; //紀錄該位置是否有"生產者"的二維陣列
		int unitTime; //當unitTime==4，生產者則可以進行複製的動作 
		//int agesOfComsumer[80][24]; //用二維陣列去紀錄每個消費者的壽命，等於4時會死亡，而吃到生產者時可以回歸1
		int PositionsConsumersAtMoveZeroTimes[80][24]; //消費者移動零次後就必須把該位置資料丟進這個陣列
		int PositionsConsumersAtMoveOneTimes[80][24]; //消費者移動一次後就必須把該位置資料丟進這個陣列 
		int PositionsConsumersAtMovetwoTimes[80][24]; //消費者移動兩次後就必須把該位置資料丟進這個陣列 
		int PositionsConsumersAtMovethreeTimes[80][24]; //消費者移動三次後就必須把該位置資料丟進這個陣列
		//消費者移動第四次就死了 
		 
};

void ConsumerAndProducer::addUnitTime()
{
	unitTime++;
}
void ConsumerAndProducer::setProducer(int x) //設定生產者的數量 
{
	ProducerAmount=x;	
} 
void ConsumerAndProducer::setConsumer(int x) //設定消費者的數量
{
	ComsumerAmount=x;
}
void ConsumerAndProducer::InitialPositionsProducerAt() //設定生產者初始的位置 
{
	int PositionX;
	int PositionY;
	srand(time(0));
	for(int i=0;i<ProducerAmount;i++)
	{
		bool check=false;
		while(!check)
			{
				PositionX=rand()%79+1; //亂數抽取生產者的X和Y座標位置，然後把該位置的陣列設為2，表示那個位置有生產者的存在
				PositionY=rand()%23+1; //座標軸範圍 x=1~79,y=1~23; (x=0跟x=80是牆，y=0跟y=24是牆) 
				if(!(checkWhetherThePositionHaveProducers(PositionX,PositionY)||checkWhetherThePositionHaveConsumers(PositionX,PositionY)))  
				{ //首先必須確認那個位置本來沒有生產者或消費者才能放
					PositionsProducersAt[PositionX][PositionY]=2;
					check=true;                                  //確定"生產者放成功"後才能結束while迴圈 
				}
				else	 //但若是那個位置已經有生產者的存在，則需要重新再抽 
					continue;
			}
	}		
}
		
void ConsumerAndProducer::InitialPositionsConsumerAt() //設定消費者初始的位置
{
	int PositionX;
	int PositionY;
	srand(time(0));
	for(int i=0;i<ComsumerAmount;i++)
	{
		bool check=false;
		while(!check)
			{
				PositionX=rand()%79+1; //亂數抽取消費者的X和Y座標位置，然後把該位置的陣列設為1，表示那個位置有消費者的存在
				PositionY=rand()%23+1; //座標軸範圍 x=1~79,y=1~23; (x=0跟x=80是牆，y=0跟y=24是牆) 
				if(!(checkWhetherThePositionHaveProducers(PositionX,PositionY)||checkWhetherThePositionHaveConsumers(PositionX,PositionY))) //首先必須確認那個位置本來沒有消費者或生產者才能放 
				{
					PositionsConsumersAtMoveZeroTimes[PositionX][PositionY]=1; //消費者位置要放到"已經移動0次的陣列資料裡面去" 
					check=true;                                  //確定"消費者放成功"後才能結束while迴圈 
				}
				else	 //但若是那個位置已經有消費者/生產者的存在，則需要重新再抽 
					continue;
			}
	}	
}
void ConsumerAndProducer::ShowThePositionsProducersAt() //展示生產者的位置
{
	for(int i=0;i<80;i++) 
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsProducersAt[i][j]==2) //若是該陣列位置資料為2，則代表那邊有生產者者
			{	
				mvaddch(j,i,'|'); //|:生產者的標誌 
			} 
		}
	}
} 
void ConsumerAndProducer::ShowThePositionsConsumersAt() //展示消費者的位置 
{
	for(int i=0;i<80;i++) 
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMoveZeroTimes[i][j]==1||PositionsConsumersAtMoveOneTimes[i][j]==1||PositionsConsumersAtMovetwoTimes[i][j]==1||PositionsConsumersAtMovethreeTimes[i][j]==1)
			{   //若是該陣列位置資料為1，則代表那邊有消費者	
				mvaddch(j,i,'&'); //&:消費者的標誌 
			} 
		}
	}
	Sleep(100);
   	refresh(); 
   	clear();
}
void ConsumerAndProducer::checkWhetherProducersCanCopy() //確認生產者是否可以複製 
{
	if(unitTime==4)
	{
		copyOfProducer();
	} 
}
void ConsumerAndProducer::copyOfProducer() //決定生產者要如何複製
{
	int copyToOtherPositions;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsProducersAt[i][j]==2)//陣列從頭找到尾，若有找到記錄2的陣列位置，則該位置必須做"生產者複製"的動作 
			{
				copyToOtherPositions=rand()%8+0; //有0~7的移動位置可能 

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
	unitTime=1; //將unitTime初始化為1	
} 

void ConsumerAndProducer::movingOfConsumerZeroTimes() //決定移動0次的消費者要如何移動 
{														//做完這個動作等於移動了一次 
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMoveZeroTimes[i][j]==1)//已經移動過0次的消費者從頭找到尾，若有找到記錄1的陣列位置，則該位置必須做"消費者移動"的動作 
			{
				PositionsConsumersAtMoveZeroTimes[i][j]=0;//不管複製成功或失敗，都算是做一次動作，因此動作數會加一，原本的動作數則要歸零 
				initialPositionX=i;
				initialPositionY=j;
				moveToOtherPositions=rand()%8+0; //有0~7的移動位置可能 
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
				if(PositionsProducersAt[i][j]==2) //如果吃到生產者
				{
					PositionsProducersAt[i][j]=0;
					PositionsConsumersAtMoveZeroTimes[i][j]=1; //生產者的那個位置複製一隻新的 
					PositionsConsumersAtMoveOneTimes[initialPositionX][initialPositionY]=1; //原本的位置有一隻原本的 
				}
				else //沒吃到生產者就移動到別的地方去 
				{ 
					PositionsConsumersAtMoveOneTimes[i][j]=1;
				}			
			}
		}
	}
}
void ConsumerAndProducer::movingOfConsumerOneTimes()  //決定已經移動1次的消費者要如何移動 
{
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMoveOneTimes[i][j]==1)//已經移動1次的消費者陣列從頭找到尾，若有找到記錄1的陣列位置，則該位置必須做"消費者移動"的動作 
			{
				PositionsConsumersAtMoveOneTimes[i][j]=0;
				initialPositionX=i;
				initialPositionY=j;
				moveToOtherPositions=rand()%8+0; //有0~7的移動位置可能 
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
				if(PositionsProducersAt[i][j]==2) //如果吃到生產者
				{
					PositionsProducersAt[i][j]=0; //生產者的位置陣列資料變成0 
					PositionsConsumersAtMoveZeroTimes[i][j]=1; //生產者的那個位置複製一隻 
					PositionsConsumersAtMovetwoTimes[initialPositionX][initialPositionY]=1; //原本的位置也有一隻舊的 
				}
				else //沒吃到生產者就往別的地方移動 
				{
					PositionsConsumersAtMovetwoTimes[i][j]=1;
				}
			}
		}
	}	
} 
void ConsumerAndProducer::movingOfConsumerTwoTimes()  //決定已經移動2次的消費者要如何移動
{
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMovetwoTimes[i][j]==1)//已經移動2次的消費者陣列從頭找到尾，若有找到記錄1的陣列位置，則該位置必須做"消費者移動"的動作 
			{
				PositionsConsumersAtMovetwoTimes[i][j]=0;
				moveToOtherPositions=rand()%8+0; //有0~7的移動位置可能 
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
				if(PositionsProducersAt[i][j]==2) //如果吃到生產者
				{
					PositionsProducersAt[i][j]=0; //生產者的位置陣列資料變成0 
					PositionsConsumersAtMoveZeroTimes[i][j]=1;
					PositionsConsumersAtMovethreeTimes[initialPositionX][initialPositionY]=1; //原本的位置也有一隻舊的 
	
				}
				else
				{
					PositionsConsumersAtMovethreeTimes[i][j]=1;
				}
			}
		}
	}
}
void ConsumerAndProducer::movingOfConsumerThreeTimes()  //決定已經移動3次的消費者要如何移動 //注意 如果跑到這個函式裡面
{                                         //，做完動作後還沒吃到生產者，就會進入死亡函式歸零 
	int moveToOtherPositions;
	int initialPositionX,initialPositionY;
	for(int i=0;i<80;i++)
	{
		for(int j=0;j<24;j++)
		{
			if(PositionsConsumersAtMovethreeTimes[i][j]==1)//已經移動3次的消費者陣列從頭找到尾，若有找到記錄1的陣列位置，則該位置必須做"消費者移動"的動作 
			{
				PositionsConsumersAtMovethreeTimes[i][j]=0;
				moveToOtherPositions=rand()%8+0; //有0~7的移動位置可能 
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
				if(PositionsProducersAt[i][j]!=2) //沒吃到生產者就死了 
				{
					deathOfConsumer(i,j);
				}
				else //吃到生產者 
				{
					PositionsProducersAt[i][j]=0; //生產者的位置陣列資料變成0 
					PositionsConsumersAtMoveZeroTimes[i][j]=1;					
				} 
			}
		}
	}
}
int ConsumerAndProducer::deathOfConsumer(int x,int y)  //該死掉的消費者會進到這裡被處死，讓該位置陣列資料=0
{
	PositionsConsumersAtMovethreeTimes[x][y]=0;	
}
void ConsumerAndProducer::copyToOtherPositions0OfProducer(int x,int y) //左上 //必須有兩個前提才能成功複製 1.沒超過邊界 2.該位置沒有東
{
	x=x-1;
	y=y-1;
	if(x>=1&&y>=1) //沒有超過邊界 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y)))  //那個位置沒有東西 
		{
			PositionsProducersAt[x][y]=2; //生產者 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions0OfConsumer(int &x,int &y)
{
	if(x-1>=1&&y-1>=1) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x-1,y-1)) //並且該位置沒有消費者 
		x=x-1;
		y=y-1;
	}	
}
void ConsumerAndProducer::copyToOtherPositions1OfProducer(int x,int y) //上 
{
	x=x;
	y=y-1;
	if(y>=1) //沒有超過邊界 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //那個位置沒有東西 
		{
			PositionsProducersAt[x][y]=2;  
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions1OfConsumer(int &x,int &y)
{
	if(y>=1) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x,y-1)) //並且該位置沒有消費者
		{	
			x=x;
			y=y-1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions2OfProducer(int x,int y) //右上
{
	x=x+1;
	y=y-1;
	if(x<=79&&y>=1) //沒有超過邊界 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //那個位置沒有東西 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions2OfConsumer(int &x,int &y)
{
	if(x+1<=79&&y-1>=1) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x+1,y-1)) //並且該位置沒有消費者
		{
			x=x+1;
			y=y-1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions3OfProducer(int x,int y) //右
{
	x=x+1;
	y=y;
	if(x<=79) //沒有超過邊界 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //那個位置沒有東西 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions3OfConsumer(int &x,int &y)
{
	if(x+1<=79) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x+1,y)) //並且該位置沒有消費者
		{
			x=x+1;
			y=y;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions4OfProducer(int x,int y) //右下
{
	x=x+1;
	y=y+1;
	if(x<=79&&y<=23) //沒有超過邊界 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //那個位置沒有東西 
		{
			PositionsProducersAt[x][y]=2;
		} 
	}			
}
void ConsumerAndProducer::moveToOtherPositions4OfConsumer(int &x,int &y)
{
	if(x+1<=79&&y+1<=23) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x+1,y+1)) //並且該位置沒有消費者
		{
			x=x+1;
			y=y+1;
		}
	}		
}
void ConsumerAndProducer::copyToOtherPositions5OfProducer(int x,int y) //下 
{
	if(y+1<=23) //沒有超過邊界 
	{
		x=x;
		y=y+1;		
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //那個位置沒有東西 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
} 
void ConsumerAndProducer::moveToOtherPositions5OfConsumer(int &x,int &y) 
{

	if(y+1<=23) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x,y+1)) //並且該位置沒有消費者
		{
			x=x;
			y=y+1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions6OfProducer(int x,int y) //左下 
{
	x=x-1;
	y=y+1;
	if(x>=1&&y<=23) //沒有超過邊界 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //那個位置沒有東西 
		{
			PositionsProducersAt[x][y]=2; 
		} 
	}		
}
void ConsumerAndProducer::moveToOtherPositions6OfConsumer(int &x,int &y)
{
	if(x-1>=1&&y+1<=23) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x-1,y+1)) //並且該位置沒有消費者
		{
			x=x-1;
			y=y+1;
		}
	}	
}
void ConsumerAndProducer::copyToOtherPositions7OfProducer(int x,int y) //左
{
	x=x-1;
	y=y;
	if(x>=1) //沒有超過邊界 
	{
		while(!(checkWhetherThePositionHaveProducers(x,y)||checkWhetherThePositionHaveConsumers(x,y))) //那個位置沒有東西 
		{
				PositionsProducersAt[x][y]=2; 
		} 
	}		
} 
void ConsumerAndProducer::moveToOtherPositions7OfConsumer(int &x,int &y)
{
	if(x-1>=1) //沒有超過邊界 
	{
		if(!checkWhetherThePositionHaveConsumers(x-1,y)) //並且該位置沒有消費者
		{
			x=x-1;
			y=y;
		}
	}	
}
bool ConsumerAndProducer::checkWhetherThePositionHaveProducers(int x,int y)
{
	if(PositionsProducersAt[x][y]==2) //確認該位置有沒有生產者 
		return true;
	else
		return false;	
}
bool ConsumerAndProducer::checkWhetherThePositionHaveConsumers(int x,int y)
{
	if(PositionsConsumersAtMoveZeroTimes[x][y]==1||PositionsConsumersAtMoveOneTimes[x][y]==1||PositionsConsumersAtMovetwoTimes[x][y]==1||PositionsConsumersAtMovethreeTimes[x][y]==1) //確認該位置有沒有消費者 
		return true;
	else
		return false;
}

void createAWindow() //建立方框 
{
	for(int i=0;i<=24;i++) //建立縱框 
	{
		mvaddch(i,0,'#'); //左邊
		mvaddch(i,80,'#');//右邊 
	}
	for(int i=0;i<80;i++) //建立橫框 
	{
		mvaddch(0,i,'#');
		mvaddch(24,i,'#');
	}
}

int main()
{
	ConsumerAndProducer MyConsumer;
	int ThisIsAmountOfComsumer,ThisIsAmountOfProducer;
	cout<<"請輸入生產者數量"<<endl;
	cin>>ThisIsAmountOfProducer;
	cout<<"請輸入消費者數量"<<endl;
	cin>>ThisIsAmountOfComsumer;
	while(ThisIsAmountOfComsumer+ThisIsAmountOfProducer>=78*22) //消費者加上生產者數量不可超過78*22
	{
		cout<<"有錯誤！請重新輸入消費者和生產者的數量:"<<endl;
		cout<<"請輸入生產者數量"<<endl;
		cin>>ThisIsAmountOfProducer;
		cout<<"請輸入消費者數量"<<endl;
		cin>>ThisIsAmountOfComsumer;
	}
	initscr();
		createAWindow(); //先建立視窗 
		MyConsumer.setProducer(ThisIsAmountOfProducer); //設定生產者的數量		
		MyConsumer.setConsumer(ThisIsAmountOfComsumer); //設定消費者的數量
		MyConsumer.InitialPositionsProducerAt(); //初始亂數抽取生產者的所在位置 
		MyConsumer.InitialPositionsConsumerAt(); //初始亂數抽取消費者的所在位置
		MyConsumer.ShowThePositionsProducersAt(); //展示出生產者的位置
		MyConsumer.ShowThePositionsConsumersAt(); //展示出消費者的位置
		while(1)
		{
			createAWindow(); //視窗
			MyConsumer.checkWhetherProducersCanCopy(); //確定生產者可以複製，這個函式會負責呼叫複製生產者的函式 
			MyConsumer.movingOfConsumerThreeTimes(); //決定已經移動3次的消費者要如何移動
			MyConsumer.movingOfConsumerTwoTimes(); //決定已經移動2次的消費者要如何移動
			MyConsumer.movingOfConsumerOneTimes(); //決定已經移動1次的消費者要如何移動
			MyConsumer.movingOfConsumerZeroTimes(); //決定已經移動0次的消費者要如何移動	
			MyConsumer.ShowThePositionsProducersAt(); //展示出生產者的位置 
			MyConsumer.ShowThePositionsConsumersAt(); //展示出消費者的位置			

			MyConsumer.addUnitTime(); //增加一單位時間 
		}
	endwin();
  
	return 0;
	system("pause");
}

