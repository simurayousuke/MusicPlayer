/***********************************************
* Copyright(c) 2016 Yang Zhizhuang
* 
* �ļ����ƣ�player.c
* �������ڣ�2016-6-27
* ˵����mci���������޸�����ʦ�ĺ���,�����·������
* 
* ���ߣ���־ׯ
* �༶����1514��
* ѧ�ţ�201592354
*
* �޸����ڣ�2016-6-28
* ˵��������˳�ʼ�汾����������
*		1.û���޸������Ĺ���
*		2.û�л�ȡ�����б�Ĺ��ܣ�ֻ����·���µ�test.mp3
*
* ��֪���⣺��δ����
* 
***********************************************/
//Ŀ¼����
#include <conio.h>
//��ȡĿ¼�������ļ�
#include <vector>
#include<iostream>   
#include<string>   
#include<io.h> 
using namespace std;
//mci
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>	// mci��ͷ�ļ�
#pragma comment(lib, "winmm.lib")	// ָ��MCI�⣬mciSendString�����Ķ�����winmm.lib��
//���̼߳�ز��Ž���
//#include <process.h>

// ���ŵ�ǰ����������curno��¼
void play(const char* path,const char *name)          //��������
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};

	// ��·��
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
	GetShortPathName(pathname, pathname, MAX_PATH);


	// ���巢��MCI�����cmdָ������洢�����飬���������printf()��ͬ
	sprintf(cmd, "open %s", pathname);
	// �������
	// һ���洢����������׵�ַ����������MCI���ص���Ϣ��������������ĳ��ȣ��ġ�û�ã�NULL
	mciSendString(cmd, "", 0, NULL);
	sprintf(cmd, "play %s", pathname);
	mciSendString(cmd, "", 0, NULL);
}


// ��ͣ��ǰ����������curno��¼
void pause(const char* path,const char *name)        // ��ͣ����
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// ��·��
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "pause %s", pathname);
	mciSendString(cmd,"",0,NULL);
}

// ֹͣ��ǰ����������curno��¼
void stop(const char* path,const char *name)         
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// ��·��
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "stop %s", pathname);
	mciSendString(cmd,"",0,NULL); 
	sprintf(cmd, "close %s", pathname);
	mciSendString(cmd,"",0,NULL); 
}

void setvol(const char* path,const char* name,int vol)
{
	char pathname[MAX_PATH] = {0};

	// ��·��
	sprintf(pathname, "%s%s",path, name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
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
					  //�ݹ������Ŀ¼�����ﲻ��Ҫ
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
	// ��������
	char Path[MAX_PATH] = {0};
	char button;
	int state=0; // 0ֹͣ��1���ţ�2��ͣ
	int curno=1;// �������
	int vol=600;// ����
	int size=0;// �ļ���
	vector<string> files;// �����ļ�
	// ҳ��1
	printf("������MP3ý��·����\n");
	scanf("%s",Path);
	printf("path = %s\n\n",Path);
	size=filesearch(Path,0,files);
	printf("\n��%d�׸裬����ӵ������б�\n\n",size);
	//setvol(vol);
	
	system("pause");
	//ҳ��2
page2:
	system("cls");
	switch(state)
	{
	case 0:default:
		printf("��ǰΪֹͣ״̬,\n");
		break;
	case 1:
		printf("���ڲ��ŵ�%d����%s\n",curno,files[curno-1].c_str());
		break;
	case 2:
		printf("������ͣ��%d����%s\n",curno,files[curno-1].c_str());
		break;
	}
	printf("������%d/10\n",vol/100);
	printf("1.���ſ���\n");
	printf("2.��������\n");
	printf("0.�˳�\n");
	printf("������������ͣ�\n");
	button=getch();
	switch(button)
	{
		//ҳ�� ���ſ���
page3:
	case '1':
		system("cls");
		switch(state)
	{
	case 0:default:
		printf("��ǰΪֹͣ״̬,\n");
		break;
	case 1:
		printf("���ڲ��ŵ�%d����%s\n",curno,files[curno-1].c_str());
		break;
	case 2:
		printf("������ͣ��%d����%s\n",curno,files[curno-1].c_str());
		break;
	}
		printf("������%d/10\n",vol/100);
		printf("1.����/��ͣ\n");
		printf("2.ֹͣ\n");
		printf("3.��һ��\n");
		printf("4.��һ��\n");
		printf("0.�˳�\n");
		printf("������������ͣ�\n");
		button=getch();
		switch(button)
		{
		case '1':
			//���ڲ���/��ͣ��x��
			if(state==1)
			{
				// ��������ͣ
				state=2;
				pause(Path,files[curno-1].c_str());//��Ҫȡ���Ŷ�Ӧ����
			}
			else
			{
				// ֹͣ����ͣ������
				state=1;
				play(Path,files[curno-1].c_str());//��Ҫȡ���Ŷ�Ӧ����
				setvol(Path,files[curno-1].c_str(),vol);
			}
			//��Ҫ��д��Ļ		
			button='1';
			goto page3;
		case '2':
			//��ǰΪֹͣ״̬
			if(state==1||state==2)
			{
				//���š���ͣ��ֹͣ
				state=0;
				stop(Path,files[curno-1].c_str());//��Ҫȡ���Ŷ�Ӧ����	
			}
			//��Ҫ��д��Ļ		
			button='1';
			goto page3;
		case '3':
			//���ڲ���/��ͣ��x������ͣ��ֹͣʱ��int��������
			stop(Path,files[curno-1].c_str());
			if(curno!=1)
				curno--;
			else
				curno=size;
			state=1;
			play(Path,files[curno-1].c_str());
			setvol(Path,files[curno-1].c_str(),vol);
			//��Ҫ��д��Ļ		
			button='1';
			goto page3;
		case '4':
			//���ڲ���/��ͣ��x������ͣ��ֹͣʱ��int��������
			stop(Path,files[curno-1].c_str());
			if(curno!=size)
				curno++;
			else
				curno=1;
			state=1;
			play(Path,files[curno-1].c_str());
			setvol(Path,files[curno-1].c_str(),vol);
			//��Ҫ��д��Ļ		
			button='1';
			goto page3;
		case '0':
			goto page2;
		default:
			//�������봦��
			button='1';
			goto page3;
		}
		break;
	case '2':
		//ҳ�� ��������
page4:
		system("cls");
		switch(state)
	{
	case 0:default:
		printf("��ǰΪֹͣ״̬,\n");
		break;
	case 1:
		printf("���ڲ��ŵ�%d����%s\n",curno,files[curno-1].c_str());
		break;
	case 2:
		printf("������ͣ��%d����%s\n",curno,files[curno-1].c_str());
		break;
	}
		printf("������%d/10\n",vol/100);
		printf("1.��������\n");
		printf("2.������С\n");
		printf("0.�˳�\n");
		printf("������������ͣ�\n");
		button=getch();
		switch(button)
		{
		case '1':
			if(vol!=1000)
				vol+=100;
			setvol(Path,files[curno-1].c_str(),vol);
			//��Ҫ��д��Ļ		
			button='2';
			goto page4;
		case '2':
			if(vol!=0)
				vol-=100;
			setvol(Path,files[curno-1].c_str(),vol);
			//��Ҫ��д��Ļ		
			button='2';
			goto page4;
		case '0':
			goto page2;
		default:
			//�������봦��
			button='2';
			goto page4;
		}
		break;
	case '0':
		exit(1);
		break;
	default:
		//�������봦��
		goto page2;
	}
	return 1;
}