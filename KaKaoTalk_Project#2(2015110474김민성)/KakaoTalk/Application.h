#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> 
using namespace std;

#include "LinkedList.h"
#include "DoublySortedLinkedList.h"

#include "Server.h"
#include "Client.h"

#include "CircularQueueType.h"


#define FILENAMESIZE 1024
#define LINE	cout << "-----------------------------------------------------------------------"<<endl;


/**
*	application class for item management simply.
*/
class Application
{
public:
	/**
	*	default constructor.
	*/
	Application()
	{
		m_Command = 0; 
		m_Server.SetClient(&m_Client);
		m_Client.SetServer(&m_Server);

		m_Server.SetMessageQueue(&m_MessageQueue);
		m_Client.SetMessageQueue(&m_MessageQueue);

		m_Server.SetClientMessageQueue(&m_ClientMessageQueue);
		m_Client.SetClientMessageQueue(&m_ClientMessageQueue);

		m_Server.SetClientQueue(&m_ClientQueue);
		m_Client.SetClientQueue(&m_ClientQueue);
	}

	/**
	*	destructor.
	*/
	~Application() {}

	/**
	*	@brief	Program Driver(구동 프로그램)
	*	@pre	프로그램이 시작되어져야한다.
	*	@post	프로그램이 종료되어진다..
	*/
	void Run();

	/**
	*	@brief	명령어들을 스크린에 보여주고 키보드로부터 입력을 받는다.
	*	@pre	none.
	*	@post	none.
	*	@return	사용자가 입력한 커맨드의 번호를 return한다.
	*/
	int MainScreen();

	void SetTextColor(unsigned short text, unsigned short back);
private:
	int m_Command;
	Server m_Server;
	Client m_Client;
	CircularQueueType<ChatMsg> m_MessageQueue;	// 클라이언트 -> 서버 (클라이언트와 서버 메세지 처리를 위한 큐)
	CircularQueueType<ChatMsg> m_ClientMessageQueue; // 서버 -> 클라이언트 (메세지 전송 큐)
	CircularQueueType<ClientType> m_ClientQueue;	//서버 -> 클라이언트 (클라이언트 객체 전송 큐)
	
};

