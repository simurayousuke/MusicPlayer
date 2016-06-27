#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>	// mci��ͷ�ļ�
#pragma comment(lib, "winmm.lib")	// ָ��MCI�⣬mciSendString�����Ķ�����winmm.lib��


// ���ŵ�ǰ����������curno��¼
void play(const char *name)          //��������
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};

	// ��·��
	sprintf(pathname, ".\\music\\%s", name);
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
void pause(const char *name)        // ��ͣ����
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// ��·��
	sprintf(pathname, ".\\music\\%s", name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "pause %s", pathname);
	mciSendString(cmd,"",0,NULL);
}

// ֹͣ��ǰ����������curno��¼
void stop(const char *name)         
{
	char cmd[MAX_PATH] = {0};
	char pathname[MAX_PATH] = {0};
	
	// ��·��
	sprintf(pathname, ".\\music\\%s", name);
	// GetShortPathName����ת��������Ҫ��ת���ĸ�����������ָ��Ŀ¼���ҵ��ļ�������ת��ʧ�ܡ�
	// ��һ��������Դ�ļ������ڶ���������Ŀ���ļ�����������������Ŀ�����鳤�ȡ�
	GetShortPathName(pathname, pathname, MAX_PATH);

	sprintf(cmd, "stop %s", pathname);
	mciSendString(cmd,"",0,NULL); 
	sprintf(cmd, "close %s", pathname);
	mciSendString(cmd,"",0,NULL); 
}