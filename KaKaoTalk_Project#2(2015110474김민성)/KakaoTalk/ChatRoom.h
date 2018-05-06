#pragma once

#include "ChatMsg.h"
#include "DoublySortedLinkedList.h"

class ChatRoom
{
protected:
	string m_Name;
	DoublySortedLinkedList<string> m_MemberList;
	DoublySortedLinkedList<ChatMsg> m_MsgList;
public:

	/**
	*	@brief	Get ChattingRoom Name.
	*	@pre	ChattingRoom Name is set.
	*	@post	none.
	*	@return	ChattingRoom Name.
	*/
	string GetName() {
		return m_Name;
	}



	/**
	*	@brief	Get ChattingRoom MemberList.
	*	@pre	ChattingRoom MemberList is set.
	*	@post	none.
	*	@return	ChattingRoom MemberList.
	*/
	DoublySortedLinkedList<string>& GetMemberList() {
		return m_MemberList;
	}

	/**
	*	@brief	Get ChattingRoom MsgList.
	*	@pre	ChattingRoom MsgList is set.
	*	@post	none.
	*	@return	ChattingRoom MsgList.
	*/
	DoublySortedLinkedList<ChatMsg>& GetMsgList() {
		return m_MsgList;
	}

	/**
	*	@brief	Set ChattingRoom Name.
	*	@pre	none.
	*	@post	ChattingRoom Name is set.
	*	@param	inName ChattingRoom Name.
	*/
	void SetName(string inName) {
		m_Name = inName;
	}




	/**
	*	@brief	Set ChattingRoom MemberList.
	*	@pre	none.
	*	@post	ChattingRoom MemberList is set.
	*	@param	inMemberList ChattingRoom MemberList.
	*/
	void SetMemberList(DoublySortedLinkedList<string>& inMemberList) {
		m_MemberList = inMemberList;
	}

	/**
	*	@brief	Set ChattingRoom MsgList.
	*	@pre	none.
	*	@post	ChattingRoom Name is set.
	*	@param	inMsgList ChattingRoom MsgList.
	*/
	void SetMsgList(DoublySortedLinkedList<ChatMsg>& inMsgList) {
		m_MsgList = inMsgList;
	}

	/**
	*	@brief	Msg�� Name ���� ���Ͽ�, m_Name���� ũ�� true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator>(ChatRoom &data)
	{
		if (m_Name > data.GetName())
			return true;
		else
			return false;
	}

	/**
	*	@brief	Msg�� Name ���� ���Ͽ�, m_Name���� ������ true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator<(ChatRoom &data)
	{
		if (m_Name < data.GetName())
			return true;
		else
			return false;
	}

	/**
	*	@brief	Msg�� Name ���� ���Ͽ�, m_Name���� ������ true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator==(ChatRoom &data)
	{
		if (m_Name == data.GetName())
			return true;
		else
			return false;
	}




};