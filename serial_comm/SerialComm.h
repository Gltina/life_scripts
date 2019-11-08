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
	* �򿪴���  
	*  @����ֵ
	*	true
	*	false
	*/
	bool open_port(const string port);

	/* 
	* ����DCB  
	*  @����ֵ
	*	true
	*	false
	*/
	bool setup_DCB(int rate_arg);

	/* 
	* ���ó�ʱ  
	*  @����ֵ
	*	true
	*	false
	*/
	bool setup_timeout(DWORD ReadInterval, DWORD ReadTotalMultiplier, DWORD

		ReadTotalConstant, DWORD WriteTotalMultiplier, DWORD WriteTotalConstant);   

	/*
	* �����ַ�  
	*  @����ֵ
	*	true
	*	false
	*/
	int receive(string & read_str);

	/*
	* �����ַ�
	*  @����ֵ
	*	true
	*	false
	*/
	bool send(const string & str);

	/*
	* ��ջ�����
	*/
	void flush_buffer();

private:
	HANDLE hComm;

	OVERLAPPED OverLapped;

	COMSTAT Comstat;

	DWORD dwCommEvents;
};

