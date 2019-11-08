#pragma once
#include <WinSock2.h>
#include <iostream>
#include <string>
using namespace std;

#pragma  comment(lib,"ws2_32.lib")

class SocketComm
{
public:
	SocketComm();

	~SocketComm();

public:
	/*server*/
	int server_init(const string & ip, const int port);

	int server_receive(string & str);

	int server_close();

	/*client*/

	int client_init(const string & ip, const int port);

	int client_send(string & str);

	int client_close();

private:
	/*server paraments*/
	SOCKET m_server_socket;

	// 服务端下的client 描述符
	SOCKET m_server_client_socket;

	// 服务端下的绑定监听地址
	SOCKADDR_IN 
		server_addr, 
		server_client_addr;

	// 服务器本地ip
	string m_server_ip;

	// 服务端监听端口
	int m_server_port;

	// 服务端接收缓冲区
	char m_server_buf[255];


	/*client paraments*/
	// 客户端将要连接的描述符
	SOCKET m_client_socket;

	SOCKADDR_IN m_client_addr;

	string m_client_ip;

	// 客户端监听端口
	int m_client_port;
	
	// 客户端发送数据缓冲 
	const char * m_client_buf;
};

