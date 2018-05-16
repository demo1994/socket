
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

	SOCKET ClistSock = socket(AF_INET, SOCK_DGRAM, 0);//创建套接字类型  

	SOCKADDR_IN SrvAddr;
	SrvAddr.sin_family = AF_INET;//选择地址族  
	SrvAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//服务端的IP地址  
	SrvAddr.sin_port = htons(6001);//服务端的端口号  

	sendto(ClistSock, "hello", strlen("hello") + 1, 0, (SOCKADDR*)&SrvAddr, sizeof(SOCKADDR));//往服务端发送"hello"消息  
	closesocket(ClistSock);//关闭套接字  
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
		printf("socket() failed, Error Code:%d/n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	char        buf[BUF_SIZE];  // 接受数据  
	SOCKADDR_IN servAddr;       // 服务器套接字地址  
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

	// 设置服务器地址  
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(5000);

	// 向服务器发送数据  
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

	// 打印来自服务端发送来的数据  
	printf("Recv From Server:%s/n", buf);
	closesocket(s);
	WSACleanup();
	return 0;
}