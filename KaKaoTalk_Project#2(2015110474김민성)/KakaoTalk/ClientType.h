#pragma once

#include "ChatMsg.h"
#include "Friend.h"
#include "FriendGroup.h"
#include "DoublySortedLinkedList.h"

class ClientType
{
protected:
	string m_Id;
	string m_Name;
	DoublySortedLinkedList<ChatMsg> m_MsgList;
	DoublySortedLinkedList<ChatRoom> m_ChatRoomList;
	DoublySortedLinkedList<Friend> m_FriendList;
	DoublySortedLinkedList<FriendGroup> m_FriendGroupList;
public:

	/**
	*	@brief	Get ClientType Id.
	*	@pre	ClientType Id is set.
	*	@post	none.
	*	@return	ClientType Id.
	*/
	string GetId() {
		return m_Id;
	}

	/**
	*	@brief	Get ClientType Name.
	*	@pre	ClientType Name is set.
	*	@post	none.
	*	@return	ClientType Name.
	*/
	string GetName() {
		return m_Name;
	}

	/**
	*	@brief	Set ClientType Id.
	*	@pre	none.
	*	@post	ClientType Id is set.
	*	@param	inId ClientType Id.
	*/
	void SetId(string inId) {
		m_Id = inId;
	}


	/**
	*	@brief	Set ClientType Name.
	*	@pre	none.
	*	@post	ClientType Name is set.
	*	@param	inName ClientType Name.
	*/
	void SetName(string inName) {
		m_Name = inName;
	}

	/**
	*	@brief	Get ClientType MsgList.
	*	@pre	ClientType MsgList is set.
	*	@post	none.
	*	@return	ClientType MsgList.
	*/
	DoublySortedLinkedList<ChatMsg>& GetMsgList() {
		return m_MsgList;
	}

	/**
	*	@brief	Set ClientType MsgList.
	*	@pre	none.
	*	@post	ClientType Name is set.
	*	@param	inMsgList ClientType MsgList.
	*/
	void SetMsgList(DoublySortedLinkedList<ChatMsg>& inMsgList) {
		m_MsgList = inMsgList;
	}

	/**
	*	@brief	Get ClientType ChatRoomList.
	*	@pre	ClientType ChatRoomList is set.
	*	@post	none.
	*	@return	ClientType ChatRoomList.
	*/
	DoublySortedLinkedList<ChatRoom>& GetChatRoomList() {
		return m_ChatRoomList;
	}

	/**
	*	@brief	Set ClientType ChatRoomList.
	*	@pre	none.
	*	@post	ClientType Name is set.
	*	@param	inChatRoomList ClientType ChatRoomList.
	*/
	void SetMsgList(DoublySortedLinkedList<ChatRoom>& inChatRoomList) {
		m_ChatRoomList = inChatRoomList;
	}

	/**
	*	@brief	Get ClientType FriendList.
	*	@pre	ClientType FriendList is set.
	*	@post	none.
	*	@return	ClientType FriendList.
	*/
	DoublySortedLinkedList<Friend>& GetFriendList() {
		return m_FriendList;
	}

	/**
	*	@brief	Set ClientType FriendList.
	*	@pre	none.
	*	@post	ClientType FriendList is set.
	*	@param	inFriendList ClientType FriendList.
	*/
	void SetFriendList(DoublySortedLinkedList<Friend>& inFriendList) {
		m_FriendList = inFriendList;
	}

	/**
	*	@brief	Get ClientType FriendGroupList.
	*	@pre	ClientType FriendGroupList is set.
	*	@post	none.
	*	@return	ClientType FriendGroupList.
	*/
	DoublySortedLinkedList<FriendGroup>& GetFriendGroupList() {
		return m_FriendGroupList;
	}

	/**
	*	@brief	Set ClientType FriendGroupList.
	*	@pre	none.
	*	@post	ClientType FriendGroupList is set.
	*	@param	inFriendGroupList ClientType FriendGroupList.
	*/
	void SetFriendGroupList(DoublySortedLinkedList<FriendGroup>& inFriendGroupList) {
		m_FriendGroupList = inFriendGroupList;
	}

	/**
	*	@brief	ClientType의 id 값을 비교하여, m_Id값이 크면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Id value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator>(ClientType &data)
	{
		if (m_Id > data.GetId())
			return true;
		else
			return false;
	}

	/**
	*	@brief	ClientType의 id 값을 비교하여, m_Id값이 작으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Id value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator<(ClientType &data)
	{
		if (m_Id < data.GetId())
			return true;
		else
			return false;
	}

	/**
	*	@brief	ClientType의 id 값을 비교하여, m_Id값이 같으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Id value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator==(ClientType &data)
	{
		if (m_Id == data.GetId())
			return true;
		else
			return false;
	}




};