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
	*	@brief	Friend의 m_Name 값을 비교하여, m_Name값이 크면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Name value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator>(Friend &data)
	{
		if (m_Name > data.GetName())
			return 1;
		return 0;
	}

	/**
	*	@brief	Friend의 m_Name 값을 비교하여, m_Name값이 작으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Name value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator<(Friend &data)
	{
		if (m_Name < data.GetName())
			return 1;
		return 0;
	}

	/**
	*	@brief	Friend의 m_Id 값을 비교하여, m_Id값이 같으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Id value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator==(Friend &data)
	{
		if (m_Id == data.GetId())
			return 1;
		return 0;
	}

};