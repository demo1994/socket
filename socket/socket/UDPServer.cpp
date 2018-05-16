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

	SOCKET SrvSock = socket(AF_INET, SOCK_DGRAM, 0);//�����׽���  
	SOCKADDR_IN SrvAddr;
	SrvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//�󶨷����IP��ַ  
	SrvAddr.sin_family = AF_INET;//����˵�ַ��  
	SrvAddr.sin_port = htons(6001);//�󶨷���˶˿ں�  

	bind(SrvSock, (SOCKADDR*)&SrvAddr, sizeof(SOCKADDR));

	int len = sizeof(SOCKADDR);
	char buff[100];
	SOCKADDR ClistAddr;

	recvfrom(SrvSock, buff, 100, 0, (SOCKADDR*)&ClistAddr, &len);//�ȴ����տͻ��˵�������  
	printf("%s\n", buff);//�ѿͻ��˷�������buff��Ϣ��ӡ����  

	closesocket(SrvSock);//�ر��׽���  
	WSACleanup();


	system("pause");
	return 0;
}*/
//////////////////////////////////////////////////////////////////////////  
// UDPServer.cpp  

//////////////////////////////////////////////////////////////////////////  
// UDPServer.cpp  

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
	int     nRet;

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
		printf("socket() failed ,Error Code:%d/n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	SOCKET      socketSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	SOCKADDR_IN addrClient;
	char        buf[BUF_SIZE];
	char        buf2[BUF_SIZE];
	int         len = sizeof(SOCKADDR);

	// ���÷�������ַ  
	ZeroMemory(buf, BUF_SIZE);
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5000);

	// ���׽���  
	nRet = bind(socketSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nRet)
	{
		printf("bind failed !/n");
		closesocket(s);
		WSACleanup();
		return -1;
	}

	// �ӿͻ��˽�������  
	nRet = recvfrom(socketSrv, buf, BUF_SIZE, 0, (SOCKADDR*)&addrClient, &len);
	if (SOCKET_ERROR == nRet)
	{
		printf("recvfrom failed !/n");
		closesocket(s);
		WSACleanup();
		return -1;
	}
	// ��ӡ���Կͻ��˷�����������  
	printf("Recv From Client:%s/n", buf);

	ZeroMemory(buf2, BUF_SIZE);
	char c;
	std::string str;
	std::cout << "please send your message to client" << std::endl;
	while (std::cin >> c)
		str.push_back(c);
	const char *t = str.data();
	strcpy(buf2, t);

	// ��ͻ��˷�������  
	if (sendto(socketSrv, buf2, BUF_SIZE, 0, (SOCKADDR*)&addrClient, len) == SOCKET_ERROR)
	{
		printf("recvfrom() failed:%d/n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}
	return 0;
}




