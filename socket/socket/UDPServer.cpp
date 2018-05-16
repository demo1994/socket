/*#include "Winsock2.h"  
#include "stdio.h"  
#pragma comment(lib,"WS2_32.lib")  
int main()
{

	////////////////////////////////////////加载套接字////////////////////////////////////////////////////  
	WORD wVersionRequested;//套接字库版本号  
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);//定义套接字的版本号  

	err = WSAStartup(wVersionRequested, &wsaData);//创建套接字  
	if (err != 0) {
		return 0;
	}
	///创建套接字失败处理  
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return 0;
	}

	SOCKET SrvSock = socket(AF_INET, SOCK_DGRAM, 0);//创建套接字  
	SOCKADDR_IN SrvAddr;
	SrvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//绑定服务端IP地址  
	SrvAddr.sin_family = AF_INET;//服务端地址族  
	SrvAddr.sin_port = htons(6001);//绑定服务端端口号  

	bind(SrvSock, (SOCKADDR*)&SrvAddr, sizeof(SOCKADDR));

	int len = sizeof(SOCKADDR);
	char buff[100];
	SOCKADDR ClistAddr;

	recvfrom(SrvSock, buff, 100, 0, (SOCKADDR*)&ClistAddr, &len);//等待接收客户端的请求到来  
	printf("%s\n", buff);//把客户端发送来的buff信息打印出来  

	closesocket(SrvSock);//关闭套接字  
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

	// 初始化套接字动态库  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("WSAStartup failed !/n");
		return 1;
	}

	// 创建套接字  
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

	// 设置服务器地址  
	ZeroMemory(buf, BUF_SIZE);
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5000);

	// 绑定套接字  
	nRet = bind(socketSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (SOCKET_ERROR == nRet)
	{
		printf("bind failed !/n");
		closesocket(s);
		WSACleanup();
		return -1;
	}

	// 从客户端接收数据  
	nRet = recvfrom(socketSrv, buf, BUF_SIZE, 0, (SOCKADDR*)&addrClient, &len);
	if (SOCKET_ERROR == nRet)
	{
		printf("recvfrom failed !/n");
		closesocket(s);
		WSACleanup();
		return -1;
	}
	// 打印来自客户端发送来的数据  
	printf("Recv From Client:%s/n", buf);

	ZeroMemory(buf2, BUF_SIZE);
	char c;
	std::string str;
	std::cout << "please send your message to client" << std::endl;
	while (std::cin >> c)
		str.push_back(c);
	const char *t = str.data();
	strcpy(buf2, t);

	// 向客户端发送数据  
	if (sendto(socketSrv, buf2, BUF_SIZE, 0, (SOCKADDR*)&addrClient, len) == SOCKET_ERROR)
	{
		printf("recvfrom() failed:%d/n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}
	return 0;
}




