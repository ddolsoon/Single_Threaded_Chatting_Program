#pragma once

#define LINE	cout << "-----------------------------------------------------------------------"<<endl;

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>

#include "LinkedList.h"
#include "DoublySortedLinkedList.h"
#include "ChatRoom.h"
#include "Friend.h"
#include "FriendGroup.h"


using namespace std;

/**
*	item information class.
*/
class Member
{
protected:
	string m_UserId;
	string m_UserPassword;
	string m_UserName;
	int m_UserBirthday;
	string m_UserGender;
	string m_UserPhone;
	string m_UserBackground;
	string m_UserProfile;
	string m_UserEmail;
	DoublySortedLinkedList<Friend> m_UserFriendList;
	DoublySortedLinkedList<Friend> m_UserRecoFriendList;
	DoublySortedLinkedList<FriendGroup> m_UserFriendGroupList;
	DoublySortedLinkedList<ChatMsg> m_UserChatList;
	

	bool m_UserLogin;
	bool m_UserAlarmMessage;
public:
	/**
	*	default constructor
	*/
	Member()
	{
		m_UserId = "";
		m_UserPassword = "";
		m_UserName = "";
		m_UserBirthday = 0;
		m_UserGender = "";
		m_UserPhone = "";
		m_UserBackground = "";
		m_UserProfile = "";
		m_UserEmail = "";
		m_UserLogin = false;
		m_UserAlarmMessage = false;
	}

	/**
	*	destructor
	*/
	~Member() {}

	/**
	*	@brief	Get User id.
	*	@pre	User id is set.
	*	@post	none.
	*	@return	User id.
	*/
	string GetUserId()
	{
		return m_UserId;
	}

	/**
	*	@brief	Get User Password.
	*	@pre	User Password is set.
	*	@post	none.
	*	@return	User PassWord.
	*/
	string GetUserPassword()
	{
		return m_UserPassword;
	}

	/**
	*	@brief	Get User name.
	*	@pre	User name is set.
	*	@post	none.
	*	@return	User name.
	*/
	string GetUserName()
	{
		return m_UserName;
	}

	/**
	*	@brief	Get User Birthday.
	*	@pre	User Birthday is set.
	*	@post	none.
	*	@return	User Birthday.
	*/
	int GetUserBirthday()
	{
		return m_UserBirthday;
	}

	/**
	*	@brief	Get User Gender.
	*	@pre	User Gender is set.
	*	@post	none.
	*	@return	User Gender.
	*/
	string GetUserGender()
	{
		return m_UserGender;
	}


	/**
	*	@brief	Get User Phone.
	*	@pre	User Phone is set.
	*	@post	none.
	*	@return	User Phone.
	*/
	string GetUserPhone()
	{
		return m_UserPhone;
	}

	/**
	*	@brief	Get User Background.
	*	@pre	User Background is set.
	*	@post	none.
	*	@return	User Background.
	*/
	string GetUserBackground()
	{
		return m_UserBackground;
	}

	/**
	*	@brief	Get User Profile.
	*	@pre	User Profile is set.
	*	@post	none.
	*	@return	User Profile.
	*/
	string GetUserProfile()
	{
		return m_UserProfile;
	}

	/**
	*	@brief	Get User Email.
	*	@pre	User Email is set.
	*	@post	none.
	*	@return	User Email.
	*/
	string GetUserEmail()
	{
		return m_UserEmail;
	}


	/**
	*	@brief	Get User Login.
	*	@pre	User Login is set.
	*	@post	none.
	*	@return	User Login.
	*/
	bool GetUserLogin()
	{
		return m_UserLogin;
	}

	/**
	*	@brief	Get User AlarmMessage.
	*	@pre	User AlarmMessage is set.
	*	@post	none.
	*	@return	User AlarmMessage.
	*/
	bool GetUserAlarmMessage()
	{
		return m_UserAlarmMessage;
	}

	/**
	*	@brief	Get User RecoFriendList.
	*	@pre	User RecoFriendList is set.
	*	@post	none.
	*	@return	User RecoFriendList.
	*/
	DoublySortedLinkedList<Friend>& GetUserRecoFriendList()
	{
		return m_UserRecoFriendList;
	}

	/**
	*	@brief	Get User FriendList.
	*	@pre	User FriendList is set.
	*	@post	none.
	*	@return	User FriendList.
	*/
	DoublySortedLinkedList<Friend>& GetUserFriendList()
	{
		return m_UserFriendList;
	}

	/**
	*	@brief	Get User ChatList.
	*	@pre	User ChatList is set.
	*	@post	none.
	*	@return	User ChatList.
	*/
	DoublySortedLinkedList<ChatMsg>& GetUserChatList()
	{
		return m_UserChatList;
	}

	/**
	*	@brief	Get User FriendGroupList.
	*	@pre	User FriendGroupList is set.
	*	@post	none.
	*	@return	User FriendGroupList.
	*/
	DoublySortedLinkedList<FriendGroup>& GetUserFriendGroupList()
	{
		return m_UserFriendGroupList;
	}

	/**
	*	@brief	Set User Id.
	*	@pre	none.
	*	@post	User Id is set.
	*	@param	inId	User Id.
	*/
	void SetUserId(string inId)
	{
		m_UserId = inId;
	}

	/**
	*	@brief	Set User Password.
	*	@pre	none.
	*	@post	User Password is set.
	*	@param	inPassword  User Password.
	*/
	void SetUserPassword(string inPassword)
	{
		m_UserPassword = inPassword;
	}


	/**
	*	@brief	Set User Name.
	*	@pre	none.
	*	@post	User Name is set.
	*	@param	inName	User Name.
	*/
	void SetUserName(string inName)
	{
		m_UserName = inName;
	}

	/**
	*	@brief	Set User Birthday.
	*	@pre	none.
	*	@post	User Birthday is set.
	*	@param	inBirthday	User Birthday.
	*/
	void SetUserBirthday(int inBirthday)
	{
		m_UserBirthday = inBirthday;
	}

	/**
	*	@brief	Set User Gender.
	*	@pre	none.
	*	@post	User Gender is set.
	*	@param	inGender  User Gender.
	*/
	void SetUserGender(string inGender)
	{
		m_UserGender = inGender;
	}


	/**
	*	@brief	Set User Phone.
	*	@pre	none.
	*	@post	User Phone is set.
	*	@param	inPhone  User Phone.
	*/
	void SetUserPhone(string inPhone)
	{
		m_UserPhone = inPhone;
	}

	/**
	*	@brief	Set User Background.
	*	@pre	none.
	*	@post	User Background is set.
	*	@param	inBackground  User Background.
	*/
	void SetUserBackground(string inBackground)
	{
		m_UserBackground = inBackground;
	}

	/**
	*	@brief	Set User Profile.
	*	@pre	none.
	*	@post	User Profile is set.
	*	@param	inProfile  User Profile.
	*/
	void SetUserProfile(string inProfile)
	{
		m_UserProfile = inProfile;
	}

	/**
	*	@brief	Set User Email.
	*	@pre	none.
	*	@post	User Email is set.
	*	@param	inEmail  User Email.
	*/
	void SetUserEmail(string inEmail)
	{
		m_UserEmail = inEmail;
	}

	/**
	*	@brief	Set User Login.
	*	@pre	none.
	*	@post	User Login is set.
	*	@param	inLogin  User Login.
	*/
	void SetUserLogin(bool inLogin)
	{
		m_UserLogin = inLogin;
	}

	/**
	*	@brief	Set User AlarmMessage.
	*	@pre	none.
	*	@post	User AlarmMessage is set.
	*	@param	inAlarmMessage  User AlarmMessage.
	*/
	void SetUserAlarmMessage(bool inAlarmMessage)
	{
		m_UserAlarmMessage = inAlarmMessage;
	}

	/**
	*	@brief	Set User FriendList.
	*	@pre	none.
	*	@post	User FriendList is set.
	*	@param	inFriendList  User FriendList.
	*/
	void SetUserFriendList(DoublySortedLinkedList<Friend>& inFriendList)
	{
		m_UserFriendList = inFriendList;
	}


	/**
	*	@brief	Set User RecoFriendList.
	*	@pre	none.
	*	@post	User RecoFriendList is set.
	*	@param	inRecoFriendList  User RecoFriendList.
	*/
	void SetUserRecoFriendList(DoublySortedLinkedList<Friend>& inRecoFriendList)
	{
		m_UserRecoFriendList = inRecoFriendList;
	}

	/**
	*	@brief	Set User ChatList.
	*	@pre	none.
	*	@post	User ChatList is set.
	*	@param	inChatList  User ChatList.
	*/
	void SetUserChatList(DoublySortedLinkedList<ChatMsg>& inChatList)
	{
		m_UserChatList = inChatList;
	}

	/**
	*	@brief	Set User FriendGroupList.
	*	@pre	none.
	*	@post	User FriendGroupList is set.
	*	@param	inFriendGroupList  User FriendGroupList.
	*/
	void SetUserFriendGroupList(DoublySortedLinkedList<FriendGroup>& inFriendGroupList)
	{
		m_UserFriendGroupList = inFriendGroupList;
	}

	/**
	*	@brief	Set User record.
	*	@pre	none.
	*	@post	User record is set.
	*	@param	inId	User Id.
	*	@param	inName	User Name.
	*	@param	inBirthday	User Birthday.
	*   @param  inGender User Gender
	*/
	void SetRecord(string inId, string inPassword, string inName, int inBirthday, string inGender, string inPhone, string inBackground,string inProfile, string inEmail, bool inLogin)
	{
		SetUserId(inId);
		SetUserPassword(inPassword);
		SetUserName(inName);
		SetUserBirthday(inBirthday);
		SetUserGender(inGender);
		SetUserPhone(inPhone);
		SetUserBackground(inBackground);
		SetUserProfile(inProfile);
		SetUserEmail(inEmail);
		SetUserLogin(inLogin);
	}

	/**
	*	@brief	Display User Id on screen.
	*	@pre	User Id is set.
	*	@post	User Id is on screen.
	*/
	void DisplayIdOnScreen()
	{
		cout << "\tUser ID   : " << m_UserId << endl;
	};

	/**
	*	@brief	Display User Password on screen.
	*	@pre	User Password is set.
	*	@post	User Password is on screen.
	*/
	void DisplayPasswordOnScreen()
	{
		cout << "\tUser Password   : " << m_UserPassword << endl;	//보안상 출력 X
	};

	/**
	*	@brief	Display User Name on screen.
	*	@pre	User Name is set.
	*	@post	User Name is on screen.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tUser Name : " << m_UserName << endl;
	};

	/**
	*	@brief	Display User Birthday on screen.
	*	@pre	User Birthday is set.
	*	@post	User Birthday is on screen.
	*/
	void DisplayBirthdayOnScreen()
	{
		cout << "\tUser Birthday : " << m_UserBirthday << endl;
	};


	/**
	*	@brief	Display User Gender on screen.
	*	@pre	User Gender is set.
	*	@post	User Gender is on screen.
	*/
	void DisplayGenderOnScreen()
	{
		cout << "\tUser Gender : " << m_UserGender << endl;
	};

	/**
	*	@brief	Display User Phone on screen.
	*	@pre	User Phone is set.
	*	@post	User Phone is on screen.
	*/
	void DisplayPhoneOnScreen()
	{
		cout << "\tUser Phone   : " << m_UserPhone << endl;
	};

	/**
	*	@brief	Display User Background on screen.
	*	@pre	User Background is set.
	*	@post	User Background is on screen.
	*/
	void DisplayBackgroundOnScreen()
	{
		cout << "\tUser Background   : " << m_UserBackground << endl;
	};

	/**
	*	@brief	Display User Profile on screen.
	*	@pre	User Profile is set.
	*	@post	User Profile is on screen.
	*/
	void DisplayProfileOnScreen()
	{
		cout << "\tUser Profile   : " << m_UserProfile << endl;
	};

	/**
	*	@brief	Display User Email on screen.
	*	@pre	User Email is set.
	*	@post	User Email is on screen.
	*/
	void DisplayEmailOnScreen()
	{
		cout << "\tUser Email   : " << m_UserEmail << endl;
	};

	/**
	*	@brief	Display User Login on screen.
	*	@pre	User Login is set.
	*	@post	User Login is on screen.
	*/
	void DisplayLoginOnScreen()
	{
		if (m_UserLogin)
			cout << "\tLogin State : 로그인" << endl;
		else
			cout << "\tLogin State : 로그아웃" << endl;
	};

	/**
	*	@brief	Display an User record on screen.
	*	@pre	User record is set.
	*	@post	User record is on screen.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayPasswordOnScreen();
		DisplayNameOnScreen();
		DisplayBirthdayOnScreen();
		DisplayGenderOnScreen();
		DisplayPhoneOnScreen();
		//DisplayBackgroundOnScreen();
		DisplayProfileOnScreen();
		DisplayEmailOnScreen();
		//DisplayLoginOnScreen();
		//DisplayFriendListOnScreen();
		cout << endl;
	};

	/**
	*	@brief	Set User Id from keyboard.
	*	@pre	none.
	*	@post	User Id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set User Password from keyboard.
	*	@pre	none.
	*	@post	User Password is set.
	*/
	void SetPasswordFromKB();

	/**
	*	@brief	Set User Name from keyboard.
	*	@pre	none.
	*	@post	User Name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set User Birthday from keyboard.
	*	@pre	none.
	*	@post	User Birthday is set.
	*/
	void SetBirthdayFromKB();

	/**
	*	@brief	Set User Gender from keyboard.
	*	@pre	none.
	*	@post	User Gender is set.
	*/
	void SetGenderFromKB();

	/**
	*	@brief	Set User Phone from keyboard.
	*	@pre	none.
	*	@post	User Phone is set.
	*/
	void SetPhoneFromKB();

	/**
	*	@brief	Set User Background from keyboard.
	*	@pre	none.
	*	@post	User Background is set.
	*/
	void SetBackgroundFromKB();

	/**
	*	@brief	Set User Profile from keyboard.
	*	@pre	none.
	*	@post	User Profile is set.
	*/
	void SetProfileFromKB();

	/**
	*	@brief	Set User Email from keyboard.
	*	@pre	none.
	*	@post	User Email is set.
	*/
	void SetEmailFromKB();

	/**
	*	@brief	Set User record from keyboard.
	*	@pre	none.
	*	@post	User record is set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	Member의 Id 값을 비교하여, m_UserId 값이 더 크면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_UserId value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator>(Member &data)
	{
		if (m_UserId > data.GetUserId())
			return 1;
		return 0;
	}

	/**
	*	@brief	Member의 Id 값을 비교하여, m_UserId 값이 더 작다면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_UserId value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator<(Member &data)
	{
		if (m_UserId < data.GetUserId())
			return 1;
		return 0;
	}

	/**
	*	@brief	Member의 Id 값을 비교하여, m_UserId 값이 같다면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_UserId value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator==(Member &data)
	{
		if (m_UserId == data.GetUserId())
			return 1;
		return 0;
	}

	/**
	*	@brief	Display User FriendList on screen.
	*	@pre	User FriendList is set.
	*	@post	User FriendList is on screen.
	*/
	void DisplayFriendListOnScreen()
	{
		m_UserFriendList.ResetList();
		int searchCount = 0;
		Friend item;
		cout << "\n\t--------------------친구목록--------------------" << endl;
		for (int i = 0; i < m_UserFriendList.GetLength(); i++)
		{
			m_UserFriendList.GetNextItem(item);
			searchCount++;
			cout << "\n\t" << searchCount << ". " << item.GetId() << "(" << item.GetName() << ")" << endl;
		}

		if (searchCount == 0)
		{
			cout << "\n\t친구가 존재하지 않습니다." << endl;
		}

		cout << "\n\t------------------------------------------------" << endl;
	};

	/**
	*	@brief	Display User ChatList on screen.
	*	@pre	User ChatList is set.
	*	@post	User ChatList is on screen.
	*/
	void DisplayChatListOnScreen(string Receiver)
	{
		system("cls");
		
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
		cout << endl;
		SetTextColor(14, 1);	//노란색
		cout << "\t    ID : " << GetUserId() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
		SetTextColor(14, 1);	//노란색

		m_UserChatList.ResetList();
		int searchCount = 0;
		ChatMsg item;
		Friend receiver;
		for (int i = 0; i < m_UserChatList.GetLength(); i++)
		{
			m_UserChatList.GetNextItem(item);
			if (item.GetDeleteState())
				continue;
			if (((Receiver == item.GetSender() && GetUserId() == item.GetReceiver() )
					|| (Receiver == item.GetReceiver() && GetUserId() == item.GetSender())) && (item.GetChatRoomName() == "-1"))	//선택한 친구와의 채팅만 출력
			{
				searchCount++;

				if (item.GetSender() == m_UserId) {
					SetTextColor(14, 1);
					cout << "\n\t\t\t\t\t\t" << item.GetSeq() << ". " << m_UserId << "(" << m_UserName << ")" << endl;
					cout << "\n\t\t\t\t\t\t" << item.GetMessage() << endl;
					SetTextColor(10, 1);

				}
				else {

					Friend m_Friend;
					m_Friend.SetId(item.GetSender());
					m_UserFriendList.Get(m_Friend);
					SetTextColor(13, 1);
					cout << "\n\t" << item.GetSeq() << ". " << m_Friend.GetId() << "(" << m_Friend.GetName() << ")" << endl;
					cout << "\n\t" << item.GetMessage() << endl;
					SetTextColor(10, 1);
				}

			}
		}

		if (searchCount == 0)
		{
			SetTextColor(14, 1);
			cout << "\n\t대화가 존재하지 않습니다.." << endl;
			
		}

		SetTextColor(10, 1);
		LINE

		
	};

	/**
	*	@brief  파라미터를 통해서 전달받은 msg를 자신의 ChatList에 저장한다.
	*	@pre	msg value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	int AddMessageTtoChatList(ChatMsg msg)
	{
		int success = m_UserChatList.Add(msg);
		if (success)
			return 1;
		else
			return 0;
	}

	/**
	*	@brief  콘솔창의 폰트 색을 변경한다.
	*	@pre	none.
	*	@return none.
	*/
	void SetTextColor(unsigned short text, unsigned short back);
};
