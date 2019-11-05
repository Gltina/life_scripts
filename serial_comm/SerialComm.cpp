#include "SerialComm.h"



SerialComm::SerialComm()
{
}

SerialComm::~SerialComm()
{
}

void SerialComm::flush_buffer()
{
	PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
}

bool SerialComm::open_port(const string port)
{
	std::wstring w_port(port.size(),L' ');
	std::copy(port.begin(), port.end(), w_port.begin());
	hComm = CreateFile(w_port.c_str(),

		GENERIC_READ | GENERIC_WRITE,

		0,

		0,

		OPEN_EXISTING,

		FILE_FLAG_OVERLAPPED,

		0);

	if (hComm == INVALID_HANDLE_VALUE)

		return FALSE;

	else

		return true;

}

bool SerialComm::setup_DCB(int rate_arg)

{

	DCB dcb;

	memset(&dcb, 0, sizeof(dcb));

	if (!GetCommState(hComm, &dcb))//获取当前DCB配置  

	{

		return FALSE;

	}

	dcb.DCBlength = sizeof(dcb);

	/* ---------- Serial Port Config ------- */

	dcb.BaudRate = rate_arg;

	dcb.Parity = NOPARITY;

	dcb.fParity = 0;

	dcb.StopBits = ONESTOPBIT;

	dcb.ByteSize = 8;

	dcb.fOutxCtsFlow = 0;

	dcb.fOutxDsrFlow = 0;

	dcb.fDtrControl = DTR_CONTROL_DISABLE;

	dcb.fDsrSensitivity = 0;

	dcb.fRtsControl = RTS_CONTROL_DISABLE;

	dcb.fOutX = 0;

	dcb.fInX = 0;

	dcb.fErrorChar = 0;

	dcb.fBinary = 1;

	dcb.fNull = 0;

	dcb.fAbortOnError = 0;

	dcb.wReserved = 0;

	dcb.XonLim = 2;

	dcb.XoffLim = 4;

	dcb.XonChar = 0x13;

	dcb.XoffChar = 0x19;

	dcb.EvtChar = 0;

	if (!SetCommState(hComm, &dcb))

	{

		return false;

	}

	else

		return true;

}

bool SerialComm::setup_timeout(DWORD ReadInterval, DWORD ReadTotalMultiplier, DWORD

	ReadTotalConstant, DWORD WriteTotalMultiplier, DWORD WriteTotalConstant)

{

	COMMTIMEOUTS timeouts;

	timeouts.ReadIntervalTimeout = ReadInterval;

	timeouts.ReadTotalTimeoutConstant = ReadTotalConstant;

	timeouts.ReadTotalTimeoutMultiplier = ReadTotalMultiplier;

	timeouts.WriteTotalTimeoutConstant = WriteTotalConstant;

	timeouts.WriteTotalTimeoutMultiplier = WriteTotalMultiplier;

	if (!SetCommTimeouts(hComm, &timeouts))

	{

		return false;

	}

	else

		return true;

}

int SerialComm::receive(string & str)
{
	bool bRead = TRUE;
	bool bResult = TRUE;
	DWORD dwError = 0;
	DWORD BytesRead = 0;

	char RXBuff;
	//for (;;)
	//{
		bResult = ClearCommError(hComm, &dwError, &Comstat);
		if (Comstat.cbInQue == 0)
			//continue;
			return 0;
		if (bRead)
		{
			bResult = ReadFile(hComm,  //通信设备（此处为串口）句柄，由CreateFile()返回值得到  

				&RXBuff,  //指向接收缓冲区  

				1,  //指明要从串口中读取的字节数  

				&BytesRead,   //  

				&OverLapped);  //OVERLAPPED结构  

			//std::cout << RXBuff << std::endl;

			str += RXBuff;

			if (!bResult)
			{
				switch (dwError == GetLastError())
				{
				case ERROR_IO_PENDING:

					bRead = FALSE;

					break;

				default:

					break;
				}
			}
		}
		else
		{
			bRead = TRUE;
		}
	//}

	if (!bRead)
	{
		bRead = TRUE;

		bResult = GetOverlappedResult(hComm,

			&OverLapped,

			&BytesRead,

			TRUE);
	}
	return str.size();
}

bool SerialComm::send(const string & str)
{
	bool bWrite = TRUE;

	bool bResult = TRUE;

	DWORD BytesSent = 0;

	HANDLE hWriteEvent = NULL;

	ResetEvent(hWriteEvent);

	if (bWrite)

	{

		OverLapped.Offset = 0;

		OverLapped.OffsetHigh = 0;

		bResult = WriteFile(hComm,  //通信设备句柄，CreateFile()返回值得到  

			str.c_str(),  //指向写入数据缓冲区  

			str.size(),  //设置要写的字节数  

			&BytesSent,  //  

			&OverLapped);  //指向异步I/O数据  

		if (!bResult)

		{

			DWORD dwError = GetLastError();

			switch (dwError)

			{

			case ERROR_IO_PENDING:

				BytesSent = 0;

				bWrite = FALSE;

				break;

			default:

				break;

			}

		}

	}

	if (!bWrite)

	{

		bWrite = TRUE;

		bResult = GetOverlappedResult(hComm,

			&OverLapped,

			&BytesSent,

			TRUE);

		if (!bResult)

		{

			std::cout << "GetOverlappedResults() in WriteFile()" << std::endl;

		}

	}

	if (BytesSent != str.size())

	{

		std::cout << "WARNING: WriteFile() error.. Bytes Sent:" << BytesSent << "; Message Length: " << str.size() << std::endl;

	}

	return TRUE;

}
