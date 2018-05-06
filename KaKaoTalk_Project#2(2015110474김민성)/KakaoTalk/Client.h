#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <windows.h> 
using namespace std;

#include "LinkedList.h"
#include "DoublySortedLinkedList.h"

#include "Server.h"
#include "Member.h"
#include "ChatRoom.h"
#include "ClientType.h"

#include "CircularQueueType.h"
#define LINE	cout << "----------------------------------------------------------------"<<endl;

class Server;

class Client
{
protected:
	
	CircularQueueType<ChatMsg> * m_pMessageQueue;
	CircularQueueType<ChatMsg> * m_pClientMessageQueue;
	CircularQueueType<ClientType> * m_pClientQueue;

	DoublySortedLinkedList<ClientType> m_ClientList;

	Member m_User;
	Server * pServer;
	bool m_Run;
	string m_ClipBoard;
	
public:
	/**
	*	default constructor
	*/
	Client() {
		m_Run = false;
	}

	/**
	*	@brief	User�� ��ȯ
	*	@pre	none.
	*	@post	User�� ��ȯ�ȴ�.
	*	@param	none.
	*/
	Member GetUser();

	/**
	*	@brief	Set User.
	*	@pre	none.
	*	@post	User�� set �ȴ�.
	*	@param	inUser	Client Member.
	*/
	void SetUser(Member inUser);

	/**
	*	@brief	Set Server.
	*	@pre	none.
	*	@post	Server ������ �ʱ�ȭ�Ǿ���..
	*	@param	pServerIn	Client pServer.
	*/
	void SetServer(Server * pServerIn)
	{
		pServer = pServerIn;
	}

	/**
	*	@brief	Set Client m_pMessageQueue.
	*	@pre	none.
	*	@post	Client m_pMessageQueue is set.
	*	@param	m_pMessageQueueIn	Client m_pMessageQueue.
	*/
	void SetMessageQueue(CircularQueueType<ChatMsg> * m_pMessageQueueIn)
	{
		m_pMessageQueue = m_pMessageQueueIn;
	}

	/**
	*	@brief	Set Client m_pClientMessageQueue.
	*	@pre	none.
	*	@post	Client m_pClientMessageQueue is set.
	*	@param	m_pClientMessageQueueIn	Client m_pClientMessageQueue.
	*/
	void SetClientMessageQueue(CircularQueueType<ChatMsg> * m_pClientMessageQueueIn)
	{
		m_pClientMessageQueue = m_pClientMessageQueueIn;
	}

	/**
	*	@brief	Set Client m_pClientQueue.
	*	@pre	none.
	*	@post	Client m_pClientQueue is set.
	*	@param	m_pClientQueueIn	Client m_pClientQueue.
	*/
	void SetClientQueue(CircularQueueType<ClientType> * m_pClientQueueIn)
	{
		m_pClientQueue = m_pClientQueueIn;
	}

	/**
	*	@brief	Get  ClientList.
	*	@pre	Client ClientList is set.
	*	@post	none.
	*	@return	Client ClientList.
	*/
	DoublySortedLinkedList<ClientType>& GetClientList()
	{
		return m_ClientList;
	}

	/**
	*	@brief	ClipBoard�� ��ȯ
	*	@pre	none.
	*	@post	ClipBoard�� ��ȯ�ȴ�.
	*	@param	none.
	*/
	string GetClipBoard() {
		return m_ClipBoard;
	}

	/**
	*	@brief	Set ClipBoard.
	*	@pre	none.
	*	@post	ClipBoard�� set �ȴ�.
	*	@param	inClipBoard	ClipBoard Member.
	*/
	void SetClipBoard(string inClipBoard) {
		m_ClipBoard = inClipBoard;
	}

	/**
	*	@brief	Set Server Run.
	*	@pre	none.
	*	@post	Server Run is set.
	*	@param	m_RunIn	Server Run.
	*/
	bool IsRunning()
	{
		if (m_Run)
			return true;
		else 
			return false;
	}

	/**
	*	@brief	Set Client Run.
	*	@pre	none.
	*	@post	Client Run is set.
	*	@param	m_RunIn	Client Run.
	*/
	void SetRun(bool m_RunIn)
	{
		m_Run = m_RunIn;
	}

	/**
	*	@brief	ä�ø���Ʈ�� ����Ѵ�.
	*	@pre	none.
	*	@post	Server Run is set.
	*	@param	none.
	*/
	int DisplayChattingRoomList();


	/**
	*	@brief	īī��ģ���� �˻��Ѵ�.
	*	@pre	none.
	*	@post	�˻��� ģ���� ID�� �̿��Ͽ�, �������Ʈ���� ���������� �����ͼ� ���
	*	@param	none.
	*/
	int SearchKakaoFriend();

	/**
	*	@brief	īī�� ģ���� �����Ѵ�.
	*	@pre	none.
	*	@post	ģ������Ʈ�� ���� īī��ģ���� ���ŵǾ�����.
	*	@param	none.
	*/
	int DeleteKakaoFriend();

	/**
	*	@brief	īī��ģ���� �߰��Ѵ�.
	*	@pre	none.
	*	@post	īī��ģ���� �߰��ȴ�.
	*	@param	none.
	*/
	int AddKakaoFriend();

	/**
	*	@brief	īī��ģ������ �޼����� �����Ѵ�.
	*	@pre	�޼���ť�� �ʱ�ȭ�Ǿ����־�� �Ѵ�.
	*	@post	�޼���ť�� īī��ģ���� ������ �޼��������� �����Ͽ� �����Ѵ�.
	*	@param	none.
	*/
	void sendMessage();

	/**
	*	@brief	īī�� ������ ������ �׸����� ���ؼ�, �����ش�.
	*	@pre	������ ������ image ���ϳ��� �־���Ѵ�.
	*	@post	�ش� �̹����� ��θ� �̿��Ͽ� �׸������� �̹��� ���.
	*	@param	none.
	*/
	void PrintProfileImage();

	/**
	*	@brief	īī���� ģ�� ���� �޴��� ����ϰ�, ��ɾ �Է¹���.
	*	@pre	none.
	*	@post	�Է¹��� ��ɾ��� ���ڸ� ��ȯ.
	*	@param	none.
	*/
	int KakaoFriendScreen();

	/**
	*	@brief	�Է¹��� ��ɾ�κ���, īī���� ģ����ɰ��� �Լ� ȣ��
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoFriendRun();

	/**
	*	@brief	īī���� ä�� ���� �޴��� ����ϰ�, ��ɾ �Է¹���.
	*	@pre	none.
	*	@post	�Է¹��� ��ɾ��� ���ڸ� ��ȯ.
	*	@param	none.
	*/
	int KakaoChatScreen();

	/**
	*	@brief	�Է¹��� ��ɾ�κ���, īī���� ä�ñ�ɰ��� �Լ� ȣ��
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoChatRun();

	/**
	*	@brief	īī���� ģ�� ����Ʈ�� �����ش�.
	*	@pre	none.
	*	@post	�ܼ�â�� īī���� ģ�� ��� ���.
	*	@param	none.
	*/
	int DisplayKakaoFriend();

	/**
	*	@brief	īī���� ��õģ�� ����Ʈ�� �����ش�.
	*	@pre	none.
	*	@post	�ܼ�â�� īī���� ��õģ�� ��� ���.
	*	@param	none.
	*/
	int DisplayKakaoRecoFriend();

	/**
	*	@brief  �ܼ�â�� ��Ʈ ���� �����Ѵ�.
	*	@pre	none.
	*	@return none.
	*/
	void SetTextColor(unsigned short text, unsigned short back);

	/**
	*	@brief	�������� �� Ŭ���̾�Ʈ������ �޾ƿ´�.
	*	@pre	Ŭ���̾�Ʈ ť�� �ʱ�ȭ�Ǿ��� �־���Ѵ�.
	*	@post	Ŭ���̾�Ʈ ť�� ���� Ŭ���̾�Ʈ������ ������, Ŭ���̾�Ʈ ����Ʈ�� �߰�.
	*	@param	none.
	*/
	void receiveClient();

	/**
	*	@brief	�������� �� �޽����� �޾ƿ´�.
	*	@pre	Ŭ���̾�Ʈ�޽��� ť�� �ʱ�ȭ�Ǿ��� �־���Ѵ�.
	*	@post	Ŭ���̾�Ʈ�޽��� ť�� ���� �޽����� ������, Ŭ���̾�Ʈ �޽�������Ʈ�� �߰�.
	*	@param	none.
	*/
	void receiveMessage();

	/**
	*	@brief	�Է¹��� ��ɾ�κ���, īī���� ��üä�� ��ɰ��� �Լ� ȣ��
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoTeamChatRun();

	/**
	*	@brief	īī���� ��üä�� ���� �޴��� ����ϰ�, ��ɾ �Է¹���.
	*	@pre	none.
	*	@post	�Է¹��� ��ɾ��� ���ڸ� ��ȯ.
	*	@param	none.
	*/
	int KakaoTeamChatScreen();

	/**
	*	@brief	īī���� ä�ù��� �����Ѵ�.
	*	@pre	none.
	*	@post	īī���� ��ü ä�ù��� ���� �Ǿ�����.
	*	@param	none.
	*/
	void createTeamChatRoom();

	/**
	*	@brief	īī���� ��ü ä�ù� ����� ����Ѵ�.
	*	@pre	none.
	*	@post	īī���� ��ü ä�ù� ����� ��� �Ǿ�����.
	*	@param	none.
	*/
	void displayTeamChatRoom();

	
	/**
	*	@brief	ä�ù� ������ load �Ѵ�.
	*	@pre	none.
	*	@pos	none
	*	@param	none.
	*/
	void loadDB();

	/**
	*	@brief	�Էµ� �޼��� ��ȣ�� �ش��ϴ� �̹����� load�Ѵ�.
	*	@pre	none.
	*	@post	�׸����� ���ؼ�, �̹����� load �Ǿ�����.
	*	@param	none.
	*/
	void DisplayImage(string name);

	/**
	*	@brief	īī���� �˻����(ä�ù�,��� �˻�)�� �����Ѵ�.
	*	@pre	none.
	*	@post	�˻��� ä�ù��� ��� �Ǿ�����.
	*	@param	none.
	*/
	void searchTeamChatRoom();


	/**
	*	@brief	�Է¹��� ��ɾ�κ���, īī���� ģ���׷� ��ɰ��� �Լ� ȣ��
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoFriendGroupRun();
	
	/**
	*	@brief	īī���� ģ���׷� ���� �޴��� ����ϰ�, ��ɾ �Է¹���.
	*	@pre	none.
	*	@post	�Է¹��� ��ɾ��� ���ڸ� ��ȯ.
	*	@param	none.
	*/
	int KakaoFriendGroupScreen();

	/**
	*	@brief	īī���� ģ���׷��� �����Ѵ�.
	*	@pre	none.
	*	@post	īī���� ģ���׷��� ���� �Ǿ�����.
	*	@param	none.
	*/
	void createFriendGroup();

	/**
	*	@brief	īī���� ģ���׷��� �����ȴ�.
	*	@pre	none.
	*	@post	�Է��� ģ���׷��� �����Ǿ�����.
	*	@param	none.
	*/
	void deleteFriendGroup();

	/**
	*	@brief	īī���� ģ�� �׷� ����� ����Ѵ�.
	*	@pre	none.
	*	@post	īī���� ģ�� �׷� ����� ��� �Ǿ�����.
	*	@param	none.
	*/
	void displayFriendGroup();
	
};

