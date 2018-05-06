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
	*	@brief	Program Driver(���� ���α׷�)
	*	@pre	���α׷��� ���۵Ǿ������Ѵ�.
	*	@post	���α׷��� ����Ǿ�����..
	*/
	void Run();

	/**
	*	@brief	��ɾ���� ��ũ���� �����ְ� Ű����κ��� �Է��� �޴´�.
	*	@pre	none.
	*	@post	none.
	*	@return	����ڰ� �Է��� Ŀ�ǵ��� ��ȣ�� return�Ѵ�.
	*/
	int MainScreen();

	void SetTextColor(unsigned short text, unsigned short back);
private:
	int m_Command;
	Server m_Server;
	Client m_Client;
	CircularQueueType<ChatMsg> m_MessageQueue;	// Ŭ���̾�Ʈ -> ���� (Ŭ���̾�Ʈ�� ���� �޼��� ó���� ���� ť)
	CircularQueueType<ChatMsg> m_ClientMessageQueue; // ���� -> Ŭ���̾�Ʈ (�޼��� ���� ť)
	CircularQueueType<ClientType> m_ClientQueue;	//���� -> Ŭ���̾�Ʈ (Ŭ���̾�Ʈ ��ü ���� ť)
	
};

