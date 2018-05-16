
#include <stdio.h>  
#include <WINSOCK2.H>  

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
	strcpy_s(buf, "UDP Hello World !");

	// 设置服务器地址  
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.1.254");
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