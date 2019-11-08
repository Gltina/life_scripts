#pragma once
#include <iostream>  
#include <cstdlib>  
#include <windows.h> 
#include <string>
#include <vector>
using namespace std;

class SerialComm
{
public:
	SerialComm();
	~SerialComm();

public:
	/* 
	* 打开串口  
	*  @返回值
	*	true
	*	false
	*/
	bool open_port(const string port);

	/* 
	* 设置DCB  
	*  @返回值
	*	true
	*	false
	*/
	bool setup_DCB(int rate_arg);

	/* 
	* 设置超时  
	*  @返回值
	*	true
	*	false
	*/
	bool setup_timeout(DWORD ReadInterval, DWORD ReadTotalMultiplier, DWORD

		ReadTotalConstant, DWORD WriteTotalMultiplier, DWORD WriteTotalConstant);   

	/*
	* 接收字符  
	*  @返回值
	*	true
	*	false
	*/
	int receive(string & read_str);

	/*
	* 接收字符
	*  @返回值
	*	true
	*	false
	*/
	bool send(const string & str);

	/*
	* 清空缓冲区
	*/
	void flush_buffer();

private:
	HANDLE hComm;

	OVERLAPPED OverLapped;

	COMSTAT Comstat;

	DWORD dwCommEvents;
};

