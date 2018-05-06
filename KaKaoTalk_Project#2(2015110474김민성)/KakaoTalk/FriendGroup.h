#pragma once

#include "DoublySortedLinkedList.h"
#include "Friend.h"
#include <iostream>
#include <string>

using namespace std;

class FriendGroup
{
protected:
	DoublySortedLinkedList<Friend> m_FriendList;
	string m_Name;
	string m_GroupImage;
public:

	/**
	*	@brief	Get FriendGroup Name.
	*	@pre	FriendGroup Name is set.
	*	@post	none.
	*	@return	FriendGroup Name.
	*/
	string GetName() {
		return m_Name;
	}

	
	/**
	*	@brief	Set FriendGroup Name.
	*	@pre	none.
	*	@post	FriendGroup Name is set.
	*	@param	inName FriendGroup Name.
	*/
	void SetName(string inName) {
		m_Name = inName;
	}

	/**
	*	@brief	Get FriendGroup GroupImage.
	*	@pre	FriendGroup GroupImage is set.
	*	@post	none.
	*	@return	FriendGroup GroupImage.
	*/
	string GetGroupImage() {
		return m_GroupImage;
	}


	/**
	*	@brief	Set FriendGroup GroupImage.
	*	@pre	none.
	*	@post	FriendGroup Name is set.
	*	@param	inGroupImage FriendGroup GroupImage.
	*/
	void SetGroupImage(string inGroupImage) {
		m_GroupImage = inGroupImage;
	}

	/**
	*	@brief	Get FriendGroup FriendList.
	*	@pre	FriendGroup FriendList  is set.
	*	@post	none.
	*	@return	FriendGroup FriendList .
	*/
	DoublySortedLinkedList<Friend>& GetFriendList() {
		return m_FriendList;
	}

	/**
	*	@brief	Set FriendGroup inFriendList.
	*	@pre	none.
	*	@post	FriendGroup Name is set.
	*	@param	inFriendList FriendGroup FriendList .
	*/
	void SetFriendList(DoublySortedLinkedList<Friend>& inFriendList) {
		m_FriendList = inFriendList;
	}


	/**
	*	@brief	FriendGroup�� m_Name ���� ���Ͽ�, m_Name���� ũ�� true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator>(FriendGroup &data)
	{
		if (m_Name > data.GetName())
			return 1;
		return 0;
	}

	/**
	*	@brief	FriendGroup�� m_Name ���� ���Ͽ�, m_Name���� ������ true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator<(FriendGroup &data)
	{
		if (m_Name < data.GetName())
			return 1;
		return 0;
	}

	/**
	*	@brief	FriendGroup�� m_Name ���� ���Ͽ�, m_Name���� ������ true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator==(FriendGroup &data)
	{
		if (m_Name == data.GetName())
			return 1;
		return 0;
	}


};