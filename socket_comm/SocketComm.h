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

	// ������µ�client ������
	SOCKET m_server_client_socket;

	// ������µİ󶨼�����ַ
	SOCKADDR_IN 
		server_addr, 
		server_client_addr;

	// ����������ip
	string m_server_ip;

	// ����˼����˿�
	int m_server_port;

	// ����˽��ջ�����
	char m_server_buf[255];


	/*client paraments*/
	// �ͻ��˽�Ҫ���ӵ�������
	SOCKET m_client_socket;

	SOCKADDR_IN m_client_addr;

	string m_client_ip;

	// �ͻ��˼����˿�
	int m_client_port;
	
	// �ͻ��˷������ݻ��� 
	const char * m_client_buf;
};

