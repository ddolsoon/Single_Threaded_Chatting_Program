#pragma once
#pragma comment(lib,"winmm.lib")

#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

#include "LinkedList.h"
#include "DoublySortedLinkedList.h"

#include "Client.h"

#include "ChatRoom.h"
#include "ClientType.h"

#include "Member.h"

#include "CircularQueueType.h"


class Client;

class Server
{
protected:
	CircularQueueType<ChatMsg> * m_pMessageQueue;
	CircularQueueType<ChatMsg> * m_pClientMessageQueue;
	
	CircularQueueType<ClientType> * m_pClientQueue;

	DoublySortedLinkedList<Member> m_MemberList;
	Client * pClient;

	bool m_Run;
public:

	/**
	*	default constructor
	*/
	Server() { m_Run = true; }


	/**
	*	@brief	Set Server m_pMessageQueue.
	*	@pre	none.
	*	@post	Server m_pMessageQueue is set.
	*	@param	m_pMessageQueueIn	Server m_pMessageQueue.
	*/
	void SetMessageQueue(CircularQueueType<ChatMsg> * m_pMessageQueueIn)
	{
		m_pMessageQueue = m_pMessageQueueIn;
	}

	/**
	*	@brief	Set Server m_pClientMessageQueue.
	*	@pre	none.
	*	@post	Server m_pClientMessageQueue is set.
	*	@param	m_pClientMessageQueueIn	Server m_pClientMessageQueue.
	*/
	void SetClientMessageQueue(CircularQueueType<ChatMsg> * m_pClientMessageQueueIn)
	{
		m_pClientMessageQueue = m_pClientMessageQueueIn;
	}

	/**
	*	@brief	Set Server m_pClientQueue.
	*	@pre	none.
	*	@post	Server m_pClientQueue is set.
	*	@param	m_pClientQueueIn	Server m_pClientQueue.
	*/
	void SetClientQueue(CircularQueueType<ClientType> * m_pClientQueueIn)
	{
		m_pClientQueue = m_pClientQueueIn;
	}

	DoublySortedLinkedList<Member>& GetMemberList()
	{
		return m_MemberList;
	}

	/**
	*	@brief	Set Server pClient.
	*	@pre	none.
	*	@post	Server pClient is set.
	*	@param	pClientIn	Server pClient.
	*/
	void SetClient(Client * pClientIn)
	{
		pClient = pClientIn;
	}

	/**
	*	@brief	������ ���¸� ��ȯ�Ѵ�.
	*	@pre	none.
	*	@post	Server Run is set.
	*	@return true �Ǵ� false�� ��ȯ
	*/
	bool IsRunning()
	{
		if (m_Run)
			return true;
		else 
			return false;
	}

	/**
	*	@brief	Set Server Run.
	*	@pre	none.
	*	@post	Server Run is set.
	*	@param	m_RunIn	Server Run.
	*/
	void SetRun(bool m_RunIn)
	{
		m_Run = m_RunIn;
	}


	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddNewMember();

	/**
	*	@brief	Enter the User ID and User Password from the user and make the login status.
	*	@pre	User ID and User Password must be correctly entered.
	*	@post	Changes the login state of the matching User in the List to the LOGIN.
	*/
	int MemberLogIn();

	/**
	*	@brief	Enter the User ID and User Password from the user and make the logout status.
	*	@pre	User ID and User Password must be correctly entered.
	*	@post	Changes the login state of the matching User in the List to the LOGOUT.
	*/
	int MemberLogOut();

	/**
	*	@brief	Delete record in the list that matches UserID input from the user.
	*	@pre	list should be initialized.
	*	@post	record in the list that matches UserID input from the user is deleted.
	*/
	int DeleteMember();

	/**
	*	@brief	Update record in the list that matches UserID input from the user.
	*	@pre	list should be initialized.
	*	@post	record in the list that matches UserID input from the user is deleted.
	*/
	int UpdateMember();

	/**
	*	@brief	Display record in the list that matches UserName input from the user.
	*	@pre	list should be initialized.
	*	@post	record in the list that matches UserName input from the user is displayed.
	*/
	int SerachMemberByName();


	/**
	*	@brief	Display record in the list that matches UserID input from the user.
	*	@pre	list should be initialized.
	*	@post	record in the list that matches UserID input from the user is displayed.
	*/
	int SearchMemberById();
	

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllMembers();


	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	����� ȸ�� �������� �޴��� ����Ѵ�.
	*	@pre	none.
	*	@post	none.
	*/
	int UpdateMemberScreen();

	

	
	/**
	*	destructor.
	*/
	~Server() { MakeEmpty(); }

	/**
	*	@brief	Ŭ���̾�Ʈ�κ��� �޽����� �޾Ƽ�, ���ù����� �޼����� �����Ѵ�.
	*	@pre	�޽���ť �ʱ�ȭ�Ǿ����־���Ѵ�.
	*	@post	�޽���ť �������.
	*/
	void receiveMessage();

	/**
	*	@brief  db.txt ���Ͽ� īī���� ȸ������,ģ�����,ä�� ����� �����Ѵ�.
	*	@pre	none.
	*	@return none.
	*/
	void SaveDB();

	/**
	*	@brief  db.txt ���Ϸκ���, īī���� ȸ������,ģ�����,ä�� ����� �����´�.
	*	@pre	none.
	*	@return none.
	*/
	void LoadDB();

	/**
	*	@brief	Ŭ���̾�Ʈ�κ��� �޽����� �޾Ƽ�, ���ù����� �޼����� �����Ѵ�.
	*	@pre	�޽���ť �ʱ�ȭ�Ǿ����־���Ѵ�.
	*	@post	�޽���ť �������.
	*/
	void receiveChatRoomMsg();

	/**
	*	@brief  �ܼ�â�� ��Ʈ ���� �����Ѵ�.
	*	@pre	none.
	*	@return none.
	*/
	void SetTextColor(unsigned short text, unsigned short back);
};

