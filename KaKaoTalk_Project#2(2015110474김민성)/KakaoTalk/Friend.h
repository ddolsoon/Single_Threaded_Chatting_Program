#pragma once

#include <iostream>
#include <string>


using namespace std;

class Friend
{
protected:
	string m_Id;
	string m_Name;
public:

	/**
	*	@brief	Get Friend Id.
	*	@pre	Friend Id is set.
	*	@post	none.
	*	@return	Friend Id.
	*/
	string GetId() {
		return m_Id;
	}

	/**
	*	@brief	Get Friend Name.
	*	@pre	Friend Name is set.
	*	@post	none.
	*	@return	Friend Name.
	*/
	string GetName() {
		return m_Name;
	}

	/**
	*	@brief	Set Friend Id.
	*	@pre	none.
	*	@post	Friend Id is set.
	*	@param	inId Friend Id.
	*/
	void SetId(string inId) {
		m_Id = inId;
	}


	/**
	*	@brief	Set Friend Name.
	*	@pre	none.
	*	@post	Friend Name is set.
	*	@param	inName Friend Name.
	*/
	void SetName(string inName) {
		m_Name = inName;
	}


	/**
	*	@brief	Friend�� m_Name ���� ���Ͽ�, m_Name���� ũ�� true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator>(Friend &data)
	{
		if (m_Name > data.GetName())
			return 1;
		return 0;
	}

	/**
	*	@brief	Friend�� m_Name ���� ���Ͽ�, m_Name���� ������ true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Name value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator<(Friend &data)
	{
		if (m_Name < data.GetName())
			return 1;
		return 0;
	}

	/**
	*	@brief	Friend�� m_Id ���� ���Ͽ�, m_Id���� ������ true, �׷��� �ʴٸ� false�� ��ȯ�Ѵ�.(������ �����ε�)
	*	@pre	m_Id value should be initialized.
	*	@return	true �Ǵ� false �� ��ȯ
	*/
	bool operator==(Friend &data)
	{
		if (m_Id == data.GetId())
			return 1;
		return 0;
	}

};