#include <pthread.h>

#include "SocketComm.h"

SocketComm socket_comm;

void *server(void* args)
{
	cout <<"[start] thread server"<<endl;

	if (!socket_comm.server_init("127.0.0.1", 19919))
	{
		cout <<"server_init done"<<endl;
	}

	string receive_str;
	while (true)
	{
		socket_comm.server_receive(receive_str);
		if (receive_str.size() > 0)
		{
			cout << "[server]receive_str:" << receive_str << endl;
		}
		Sleep(100);
	}
}

void *client(void* args)
{
	cout << "[start] thread client" << endl;
	if (!socket_comm.client_init("127.0.0.1", 19919))
	{
		cout << "client_init done" << endl;
	}
	int count = 0;
	string send_str;
	while (true)
	{
		send_str = "test data" + std::to_string(count);
		socket_comm.client_send(send_str);
		cout << "[client]" << "sent:" << send_str << endl;
		Sleep(1000);
		count++;
	}
}

int main()
{
	pthread_t server_th, client_th;

	int ret = pthread_create(&server_th, NULL, server, NULL);
	if (ret != 0)
	{
		cout << "pthread_create error: error_code=" << ret << endl;
	}

	ret = pthread_create(&client_th, NULL, client, NULL);
	if (ret != 0)
	{
		cout << "pthread_create error: error_code=" << ret << endl;
	}


	pthread_join(server_th, nullptr);
	pthread_join(client_th, nullptr);

	return 0;
}