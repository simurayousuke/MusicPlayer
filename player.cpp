/***********************************************
* Copyright(c) 2016 Yang Zhizhuang
* 
* 文件名称：player.c
* 创建日期：2016-6-27
* 说明：mci函数部分修改自老师的函数,添加了路径参数
* 
* 作者：杨志庄
* 班级：软1514班
* 学号：201592354
*
* 修改日期：2016-6-28
* 说明：解决了初始版本的两个问题
*		1.没有修改音量的功能
*		2.没有获取播放列表的功能，只播放路径下的test.mp3
*
* 已知问题：暂未发现
* 
***********************************************/
//目录控制
#include <conio.h>
//获取目录下音乐文件
#include <vector>
#include<iostream>   
#include<string>   
#include<io.h> 
using namespace std;
//mci
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>	// mci库头文件
#pragma comment(lib, "winmm.lib")	// 指定MCI库，mciSendString函数的定义在winmm.lib中
//多线程监控播放结束
//#include <process.h>

// 播放当前曲，曲号由curno记录
void play(const char* path,const char *name)          //播放音乐
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};

	// 加路径
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(pathname, pathname, MAX_PATH);


	// 定义发往MCI的命令，cmd指定命令存储的数组，后面参数跟printf()相同
	sprintf(cmd, "open %s", pathname);
	// 发送命令。
	// 一、存储命令的数组首地址，二、接受MCI返回的信息，三、接受数组的长度，四、没用，NULL
	mciSendString(cmd, "", 0, NULL);
	sprintf(cmd, "play %s", pathname);
	mciSendString(cmd, "", 0, NULL);
}


// 暂停当前曲，曲号由curno记录
void pause(const char* path,const char *name)        // 暂停播放
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// 加路径
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "pause %s", pathname);
	mciSendString(cmd,"",0,NULL);
}

// 停止当前曲，曲号由curno记录
void stop(const char* path,const char *name)         
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// 加路径
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "stop %s", pathname);
	mciSendString(cmd,"",0,NULL); 
	sprintf(cmd, "close %s", pathname);
	mciSendString(cmd,"",0,NULL); 
}

void setvol(const char* path,const char* name,int vol)
{
	char pathname[MAX_PATH] = {0};

	// 加路径
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName用来转换短名，要求被转换的歌名必须能在指定目录下找到文件，否则转换失败。
	// 第一个参数：源文件名，第二个参数：目的文件名，第三个参数：目的数组长度。
	GetShortPathName(pathname, pathname, MAX_PATH);
	char cmd[MAX_PATH] = {0};
	sprintf(cmd, "setaudio %s volume to %d", pathname,vol);
	mciSendString(cmd,"",0,NULL); 
}

 int   filesearch(string path,int layer,vector<string>& file)   
  {   
          struct _finddata_t   filefind;   
          string  curr=path+"\\*.*";   
          int   done=0,i,handle;   
		  int size=0;
          if((handle=_findfirst(curr.c_str(),&filefind))==-1)
		  	return 0; 			    
          while(!(done=_findnext(handle,&filefind)))   
          {   
                  if(!strcmp(filefind.name,".."))
                   		continue;      
                  for(i=0;i<layer;i++)
				  		cout<<"     "; 			    	    			    	
                  if   ((_A_SUBDIR==filefind.attrib))   
                  {           
					  //递归遍历子目录，这里不需要
					  //printf("----------%s\n",filefind.name);
					  //cout<<filefind.name<<"(dir)"<<endl;
					  //curr=path+"\\"+filefind.name; 
					  //filesearch(curr,layer+1);   
                  }   
                  else     
                  {   
					  string temp(filefind.name);
					   if (temp.find(".mp3") >= temp.length())
						   if (temp.find(".wav") >= temp.length())
								continue;
					  file.push_back(temp);
					  size++;
                          cout<<temp<<endl;   
                  }   
          }           
          _findclose(handle);     
          return size;
  }   
 void waitforstop()
 {

 }

int main(int argc,char* argv[])
{
	// 变量定义
	char Path[MAX_PATH] = {0};
	char button;
	int state=0; // 0停止，1播放，2暂停
	int curno=1;// 歌曲序号
	int vol=600;// 音量
	int size=0;// 文件数
	vector<string> files;// 所有文件
	// 页面1
	printf("请输入MP3媒体路径：\n");
	scanf("%s",Path);
	printf("path = %s\n\n",Path);
	size=filesearch(Path,0,files);
	printf("\n共%d首歌，已添加到播放列表\n\n",size);
	//setvol(vol);
	
	system("pause");
	//页面2
page2:
	system("cls");
	switch(state)
	{
	case 0:default:
		printf("当前为停止状态,\n");
		break;
	case 1:
		printf("正在播放第%d曲：%s\n",curno,files[curno-1].c_str());
		break;
	case 2:
		printf("正在暂停第%d曲：%s\n",curno,files[curno-1].c_str());
		break;
	}
	printf("音量：%d/10\n",vol/100);
	printf("1.播放控制\n");
	printf("2.音量调节\n");
	printf("0.退出\n");
	printf("请输入操作类型：\n");
	button=getch();
	switch(button)
	{
		//页面 播放控制
page3:
	case '1':
		system("cls");
		switch(state)
	{
	case 0:default:
		printf("当前为停止状态,\n");
		break;
	case 1:
		printf("正在播放第%d曲：%s\n",curno,files[curno-1].c_str());
		break;
	case 2:
		printf("正在暂停第%d曲：%s\n",curno,files[curno-1].c_str());
		break;
	}
		printf("音量：%d/10\n",vol/100);
		printf("1.播放/暂停\n");
		printf("2.停止\n");
		printf("3.上一曲\n");
		printf("4.下一曲\n");
		printf("0.退出\n");
		printf("请输入操作类型：\n");
		button=getch();
		switch(button)
		{
		case '1':
			//正在播放/暂停第x曲
			if(state==1)
			{
				// 播放至暂停
				state=2;
				pause(Path,files[curno-1].c_str());//需要取曲号对应歌名
			}
			else
			{
				// 停止、暂停至播放
				state=1;
				play(Path,files[curno-1].c_str());//需要取曲号对应歌名
				setvol(Path,files[curno-1].c_str(),vol);
			}
			//需要重写屏幕		
			button='1';
			goto page3;
		case '2':
			//当前为停止状态
			if(state==1||state==2)
			{
				//播放、暂停至停止
				state=0;
				stop(Path,files[curno-1].c_str());//需要取曲号对应歌名	
			}
			//需要重写屏幕		
			button='1';
			goto page3;
		case '3':
			//正在播放/暂停第x曲，暂停或停止时改int但不播放
			stop(Path,files[curno-1].c_str());
			if(curno!=1)
				curno--;
			else
				curno=size;
			state=1;
			play(Path,files[curno-1].c_str());
			setvol(Path,files[curno-1].c_str(),vol);
			//需要重写屏幕		
			button='1';
			goto page3;
		case '4':
			//正在播放/暂停第x曲，暂停或停止时改int但不播放
			stop(Path,files[curno-1].c_str());
			if(curno!=size)
				curno++;
			else
				curno=1;
			state=1;
			play(Path,files[curno-1].c_str());
			setvol(Path,files[curno-1].c_str(),vol);
			//需要重写屏幕		
			button='1';
			goto page3;
		case '0':
			goto page2;
		default:
			//错误输入处理
			button='1';
			goto page3;
		}
		break;
	case '2':
		//页面 音量控制
page4:
		system("cls");
		switch(state)
	{
	case 0:default:
		printf("当前为停止状态,\n");
		break;
	case 1:
		printf("正在播放第%d曲：%s\n",curno,files[curno-1].c_str());
		break;
	case 2:
		printf("正在暂停第%d曲：%s\n",curno,files[curno-1].c_str());
		break;
	}
		printf("音量：%d/10\n",vol/100);
		printf("1.音量增大\n");
		printf("2.音量减小\n");
		printf("0.退出\n");
		printf("请输入操作类型：\n");
		button=getch();
		switch(button)
		{
		case '1':
			if(vol!=1000)
				vol+=100;
			setvol(Path,files[curno-1].c_str(),vol);
			//需要重写屏幕		
			button='2';
			goto page4;
		case '2':
			if(vol!=0)
				vol-=100;
			setvol(Path,files[curno-1].c_str(),vol);
			//需要重写屏幕		
			button='2';
			goto page4;
		case '0':
			goto page2;
		default:
			//错误输入处理
			button='2';
			goto page4;
		}
		break;
	case '0':
		exit(1);
		break;
	default:
		//错误输入处理
		goto page2;
	}
	return 1;
}