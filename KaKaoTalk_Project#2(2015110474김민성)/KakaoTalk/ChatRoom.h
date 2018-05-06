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
	*	@brief	Msg의 Name 값을 비교하여, m_Name값이 크면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Name value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator>(ChatRoom &data)
	{
		if (m_Name > data.GetName())
			return true;
		else
			return false;
	}

	/**
	*	@brief	Msg의 Name 값을 비교하여, m_Name값이 작으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Name value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator<(ChatRoom &data)
	{
		if (m_Name < data.GetName())
			return true;
		else
			return false;
	}

	/**
	*	@brief	Msg의 Name 값을 비교하여, m_Name값이 같으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Name value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator==(ChatRoom &data)
	{
		if (m_Name == data.GetName())
			return true;
		else
			return false;
	}




};