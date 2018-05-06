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
	*	@brief	User를 반환
	*	@pre	none.
	*	@post	User가 반환된다.
	*	@param	none.
	*/
	Member GetUser();

	/**
	*	@brief	Set User.
	*	@pre	none.
	*	@post	User가 set 된다.
	*	@param	inUser	Client Member.
	*/
	void SetUser(Member inUser);

	/**
	*	@brief	Set Server.
	*	@pre	none.
	*	@post	Server 포인터 초기화되어짐..
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
	*	@brief	ClipBoard를 반환
	*	@pre	none.
	*	@post	ClipBoard가 반환된다.
	*	@param	none.
	*/
	string GetClipBoard() {
		return m_ClipBoard;
	}

	/**
	*	@brief	Set ClipBoard.
	*	@pre	none.
	*	@post	ClipBoard가 set 된다.
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
	*	@brief	채팅리스트를 출력한다.
	*	@pre	none.
	*	@post	Server Run is set.
	*	@param	none.
	*/
	int DisplayChattingRoomList();


	/**
	*	@brief	카카오친구를 검색한다.
	*	@pre	none.
	*	@post	검색된 친구의 ID를 이용하여, 멤버리스트에서 세부정보를 가져와서 출력
	*	@param	none.
	*/
	int SearchKakaoFriend();

	/**
	*	@brief	카카오 친구를 삭제한다.
	*	@pre	none.
	*	@post	친구리스트로 부터 카카오친구가 제거되어진다.
	*	@param	none.
	*/
	int DeleteKakaoFriend();

	/**
	*	@brief	카카오친구를 추가한다.
	*	@pre	none.
	*	@post	카카오친구가 추가된다.
	*	@param	none.
	*/
	int AddKakaoFriend();

	/**
	*	@brief	카카오친구에게 메세지를 전달한다.
	*	@pre	메세지큐가 초기화되어져있어야 한다.
	*	@post	메세지큐로 카카오친구의 정보와 메세지내용을 저장하여 전송한다.
	*	@param	none.
	*/
	void sendMessage();

	/**
	*	@brief	카카오 프로필 사진을 그림판을 통해서, 보여준다.
	*	@pre	프로필 사진이 image 파일내에 있어야한다.
	*	@post	해당 이미지의 경로를 이용하여 그림판으로 이미지 출력.
	*	@param	none.
	*/
	void PrintProfileImage();

	/**
	*	@brief	카카오톡 친구 관련 메뉴를 출력하고, 명령어를 입력받음.
	*	@pre	none.
	*	@post	입력받은 명령어의 숫자를 반환.
	*	@param	none.
	*/
	int KakaoFriendScreen();

	/**
	*	@brief	입력받은 명령어로부터, 카카오톡 친구기능관련 함수 호출
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoFriendRun();

	/**
	*	@brief	카카오톡 채팅 관련 메뉴를 출력하고, 명령어를 입력받음.
	*	@pre	none.
	*	@post	입력받은 명령어의 숫자를 반환.
	*	@param	none.
	*/
	int KakaoChatScreen();

	/**
	*	@brief	입력받은 명령어로부터, 카카오톡 채팅기능관련 함수 호출
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoChatRun();

	/**
	*	@brief	카카오톡 친구 리스트를 보여준다.
	*	@pre	none.
	*	@post	콘솔창에 카카오톡 친구 목록 출력.
	*	@param	none.
	*/
	int DisplayKakaoFriend();

	/**
	*	@brief	카카오톡 추천친구 리스트를 보여준다.
	*	@pre	none.
	*	@post	콘솔창에 카카오톡 추천친구 목록 출력.
	*	@param	none.
	*/
	int DisplayKakaoRecoFriend();

	/**
	*	@brief  콘솔창의 폰트 색을 변경한다.
	*	@pre	none.
	*	@return none.
	*/
	void SetTextColor(unsigned short text, unsigned short back);

	/**
	*	@brief	서버에서 온 클라이언트정보를 받아온다.
	*	@pre	클라이언트 큐가 초기화되어져 있어야한다.
	*	@post	클라이언트 큐로 부터 클라이언트정보를 꺼내서, 클라이언트 리스트에 추가.
	*	@param	none.
	*/
	void receiveClient();

	/**
	*	@brief	서버에서 온 메시지를 받아온다.
	*	@pre	클라이언트메시지 큐가 초기화되어져 있어야한다.
	*	@post	클라이언트메시지 큐로 부터 메시지를 꺼내서, 클라이언트 메시지리스트에 추가.
	*	@param	none.
	*/
	void receiveMessage();

	/**
	*	@brief	입력받은 명령어로부터, 카카오톡 단체채팅 기능관련 함수 호출
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoTeamChatRun();

	/**
	*	@brief	카카오톡 단체채팅 관련 메뉴를 출력하고, 명령어를 입력받음.
	*	@pre	none.
	*	@post	입력받은 명령어의 숫자를 반환.
	*	@param	none.
	*/
	int KakaoTeamChatScreen();

	/**
	*	@brief	카카오톡 채팅방을 생성한다.
	*	@pre	none.
	*	@post	카카오톡 단체 채팅방이 생성 되어진다.
	*	@param	none.
	*/
	void createTeamChatRoom();

	/**
	*	@brief	카카오톡 단체 채팅방 목록을 출력한다.
	*	@pre	none.
	*	@post	카카오톡 단체 채팅방 목록이 출력 되어진다.
	*	@param	none.
	*/
	void displayTeamChatRoom();

	
	/**
	*	@brief	채팅방 정보를 load 한다.
	*	@pre	none.
	*	@pos	none
	*	@param	none.
	*/
	void loadDB();

	/**
	*	@brief	입력된 메세지 번호에 해당하는 이미지를 load한다.
	*	@pre	none.
	*	@post	그림판을 통해서, 이미지가 load 되어진다.
	*	@param	none.
	*/
	void DisplayImage(string name);

	/**
	*	@brief	카카오톡 검색기능(채팅방,멤버 검색)을 수행한다.
	*	@pre	none.
	*	@post	검색된 채팅방이 출력 되어진다.
	*	@param	none.
	*/
	void searchTeamChatRoom();


	/**
	*	@brief	입력받은 명령어로부터, 카카오톡 친구그룹 기능관련 함수 호출
	*	@pre	none.
	*	@post	none.
	*	@param	none.
	*/
	void KakaoFriendGroupRun();
	
	/**
	*	@brief	카카오톡 친구그룹 관련 메뉴를 출력하고, 명령어를 입력받음.
	*	@pre	none.
	*	@post	입력받은 명령어의 숫자를 반환.
	*	@param	none.
	*/
	int KakaoFriendGroupScreen();

	/**
	*	@brief	카카오톡 친구그룹을 생성한다.
	*	@pre	none.
	*	@post	카카오톡 친구그룹이 생성 되어진다.
	*	@param	none.
	*/
	void createFriendGroup();

	/**
	*	@brief	카카오톡 친구그룹이 삭제된다.
	*	@pre	none.
	*	@post	입력한 친구그룹이 삭제되어진다.
	*	@param	none.
	*/
	void deleteFriendGroup();

	/**
	*	@brief	카카오톡 친구 그룹 목록을 출력한다.
	*	@pre	none.
	*	@post	카카오톡 친구 그룹 목록이 출력 되어진다.
	*	@param	none.
	*/
	void displayFriendGroup();
	
};

