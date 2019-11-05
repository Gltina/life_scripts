#include "SerialComm.h"

int main()
{
	SerialComm serial_comm;
	

	if (serial_comm.open_port("COM2"))

		std::cout << "Open port success" << std::endl;

	if (serial_comm.setup_DCB(9600))

		std::cout << "Set DCB success" << std::endl;

	if (serial_comm.setup_timeout(0, 0, 0, 0, 0))

		std::cout << "Set timeout success" << std::endl;

	serial_comm.flush_buffer();

	serial_comm.send("test data");// WriteChar(string("Please send data:").c_str(), 20);

	string receive_str;

	while (true)
	{
		int count = serial_comm.receive(receive_str);
		if (receive_str.find('#') != string::npos)
		{
			std::cout << "received string:" << receive_str << " receive_str.size()" << receive_str.size() << std::endl;
			receive_str.clear();
		}
	}

	return EXIT_SUCCESS;
}