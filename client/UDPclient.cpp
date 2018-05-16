
/*#include "Winsock2.h"  
#include "stdio.h"  
#pragma comment(lib,"WS2_32.lib")  
int main()
{

	////////////////////////////////////////�����׽���////////////////////////////////////////////////////  
	WORD wVersionRequested;//�׽��ֿ�汾��  
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);//�����׽��ֵİ汾��  

	err = WSAStartup(wVersionRequested, &wsaData);//�����׽���  
	if (err != 0) {
		return 0;
	}
	///�����׽���ʧ�ܴ���  
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return 0;
	}

	SOCKET ClistSock = socket(AF_INET, SOCK_DGRAM, 0);//�����׽�������  

	SOCKADDR_IN SrvAddr;
	SrvAddr.sin_family = AF_INET;//ѡ���ַ��  
	SrvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//����˵�IP��ַ  
	SrvAddr.sin_port = htons(6001);//����˵Ķ˿ں�  

	sendto(ClistSock, "hello", strlen("hello") + 1, 0, (SOCKADDR*)&SrvAddr, sizeof(SOCKADDR));//������˷���"hello"��Ϣ  
	closesocket(ClistSock);//�ر��׽���  
	WSACleanup();//  

	return 0;
}*/
//////////////////////////////////////////////////////////////////////////  
// UDPClient.cpp  

//////////////////////////////////////////////////////////////////////////  
// UDPClient.cpp  

#include <stdio.h>  
#include <WINSOCK2.H>  
#include <iostream>
#include <string>
#pragma comment(lib,"WS2_32.lib")  
#define BUF_SIZE    64  

int main(void)
{
	WSADATA wsd;
	SOCKET  s;

	// ��ʼ���׽��ֶ�̬��  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed !/n");
		return 1;
	}

	// �����׽���  
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == INVALID_SOCKET)
	{
		printf("socket() failed, Error Code:%d/n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	char        buf[BUF_SIZE];  // ��������  
	SOCKADDR_IN servAddr;       // �������׽��ֵ�ַ  
	SOCKET      sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	int         nRet;

	ZeroMemory(buf, BUF_SIZE);
	char c;
	std::string str;
	std::cout << "please send your message to server" << std::endl;
	while (std::cin >> c)
		str.push_back(c);
	const char *t = str.data();
	strcpy(buf, t);
	//strcpy(buf, "UDP Hello World !");

	// ���÷�������ַ  
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(5000);

	// ���������������  
	int nServAddLen = sizeof(servAddr);
	if (sendto(sockClient, buf, BUF_SIZE, 0, (sockaddr *)&servAddr, nServAddLen) == SOCKET_ERROR)
	{
		printf("recvfrom() failed:%d/n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}
	nRet = recvfrom(sockClient, buf, BUF_SIZE, 0, (sockaddr *)&servAddr, &nServAddLen);
	if (SOCKET_ERROR == nRet)
	{
		printf("recvfrom failed !/n");
		closesocket(s);
		WSACleanup();
		return -1;
	}

	// ��ӡ���Է���˷�����������  
	printf("Recv From Server:%s/n", buf);
	closesocket(s);
	WSACleanup();
	return 0;
}