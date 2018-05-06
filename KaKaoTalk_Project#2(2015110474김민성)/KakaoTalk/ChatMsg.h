#pragma once


#include <string>

using namespace std;

class ChatMsg
{
protected:
	int m_Seq;
	string m_Sender;
	string m_Receiver;
	string m_Message;
	string m_ChatRoomName;
	bool m_DeleteState;
	bool m_ChatRoomMake;
public:

	/**
	*	default constructor
	*/
	ChatMsg() {
		m_ChatRoomName = "-1";
		m_DeleteState = false;
		m_ChatRoomMake = false;
		m_Message = "-1";
	}

	/**
	*	@brief	Get ChatMsg Seq.
	*	@pre	ChatMsg Seq is set.
	*	@post	none.
	*	@return	ChatMsg Seq.
	*/
	int GetSeq() {
		return m_Seq;
	}

	

	/**
	*	@brief	Get ChatMsg Sender.
	*	@pre	ChatMsg Sender is set.
	*	@post	none.
	*	@return	ChatMsg Sender.
	*/
	string GetSender() {
		return m_Sender;
	}

	/**
	*	@brief	Get ChatMsg Receiver.
	*	@pre	ChatMsg Receiver is set.
	*	@post	none.
	*	@return	ChatMsg Receiver.
	*/
	string GetReceiver() {
		return m_Receiver;
	}

	/**
	*	@brief	Get ChatMsg Message.
	*	@pre	ChatMsg Message is set.
	*	@post	none.
	*	@return	ChatMsg Message.
	*/
	string GetMessage() {
		return m_Message;
	}

	/**
	*	@brief	Get ChatMsg ChatRoomName.
	*	@pre	ChatMsg ChatRoomName is set.
	*	@post	none.
	*	@return	ChatMsg ChatRoomName.
	*/
	string GetChatRoomName() {
		return m_ChatRoomName;
	}

	/**
	*	@brief	Get ChatMsg DeleteState.
	*	@pre	ChatMsg DeleteState is set.
	*	@post	none.
	*	@return	ChatMsg DeleteState.
	*/
	bool GetDeleteState() {
		return m_DeleteState;
	}


	/**
	*	@brief	Get ChatMsg ChatRoom.
	*	@pre	ChatMsg ChatRoom is set.
	*	@post	none.
	*	@return	ChatMsg ChatRoom.
	*/
	bool GetChatRoomMake() {
		return m_ChatRoomMake;
	}

	/**
	*	@brief	Set ChatMsg Seq.
	*	@pre	none.
	*	@post	ChatMsg Seq is set.
	*	@param	inSeq ChatMsg Seq.
	*/
	void SetSeq(int inSeq) {
		m_Seq = inSeq;
	}



	/**
	*	@brief	Set ChatMsg Sender.
	*	@pre	none.
	*	@post	ChatMsg Sender is set.
	*	@param	inSender ChatMsg Sender.
	*/
	void SetSender(string inSender) {
		m_Sender = inSender;
	}

	/**
	*	@brief	Set ChatMsg Receiver.
	*	@pre	none.
	*	@post	ChatMsg Receiver is set.
	*	@param	inReceiver ChatMsg Id.
	*/
	void SetReceiver(string inReceiver) {
		m_Receiver = inReceiver;
	}

	/**
	*	@brief	Set ChatMsg Message.
	*	@pre	none.
	*	@post	ChatMsg Message is set.
	*	@param	inMessage ChatMsg Message.
	*/
	void SetMessage(string inMessage) {
		m_Message = inMessage;
	}

	/**
	*	@brief	Set ChatMsg ChatRoomName.
	*	@pre	none.
	*	@post	ChatMsg ChatRoomName is set.
	*	@param	inChatRoomName ChatMsg Id.
	*/
	void SetChatRoomName(string inChatRoomName) {
		m_ChatRoomName = inChatRoomName;
	}

	/**
	*	@brief	Set ChatMsg DeleteState.
	*	@pre	none.
	*	@post	ChatMsg DeleteState is set.
	*	@param	inDeleteState ChatMsg DeleteState.
	*/
	void SetDeleteState(bool inDeleteState) {
		m_DeleteState = inDeleteState;
	}

	/**
	*	@brief	Set ChatMsg ChatRoomMake.
	*	@pre	none.
	*	@post	ChatMsg ChatRoomMake is set.
	*	@param	inChatRoomMake ChatMsg ChatRoomMake.
	*/
	void SetChatRoomMake(bool inChatRoomMake) {
		m_ChatRoomMake = inChatRoomMake;
	}

	/**
	*	@brief	ChatMsg의 seq 값을 비교하여, m_Seq값이 더크면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Seq value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator>(ChatMsg &data)
	{
		// Debugging
		//cout << m_Seq << " > " << data.GetSeq() << endl;
		if (m_Seq > data.GetSeq())
			return true;
		else
			return false;
	}

	/**
	*	@brief	ChatMsg의 seq 값을 비교하여, m_Seq값이 더 작으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Seq value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator<(ChatMsg &data)
	{
		// Debugging
		//cout << m_Seq << " < " << data.GetSeq() << endl;
		if (m_Seq < data.GetSeq())
			return true;
		return false;
	}

	/**
	*	@brief	ChatMsg의 seq 값을 비교하여, m_Seq값이 같으면 true, 그렇지 않다면 false를 반환한다.(연산자 오버로딩)
	*	@pre	m_Seq value should be initialized.
	*	@return	true 또는 false 를 반환
	*/
	bool operator==(ChatMsg &data)
	{
		// Debugging
		//cout << m_Seq << " < " << data.GetSeq() << endl;
		if (m_Seq == data.GetSeq())
			return true;
		return false;
	}




};