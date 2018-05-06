#include "Client.h"

Member Client::GetUser()
{
	return m_User;
}

void Client::SetUser(Member inUser)
{
	m_User = inUser;
}


int Client::DisplayChattingRoomList()
{

	m_User.DisplayFriendListOnScreen();

	sendMessage();


	return 0;
}



int Client::SearchKakaoFriend()
{
	string id;
	Friend friend_ID;
	Member Mfriend_ID;

	cout << "\n\t�˻� �Ϸ��� ģ��ID�� �Է��ϼ��� : ";
	cin >> id;
	friend_ID.SetId(id);
	Mfriend_ID.SetUserId(id);

	if (m_User.GetUserFriendList().Get(friend_ID) == 0)
	{
		cout << "\n\tģ������Ʈ�� ��ϵ��� ���� ID �Դϴ�.." << endl;
		m_User.DisplayFriendListOnScreen();
		cout << '\t';  system("pause");

		return 0;
	}
	cout << "\n\tģ�� ��ȸ ����!" << endl;

	pServer->GetMemberList().Get(Mfriend_ID);
	Mfriend_ID.DisplayRecordOnScreen();

	return 1;
}

int Client::DeleteKakaoFriend()
{
	string id;
	Friend friend_ID;

	cout << "\n\t���� �Ϸ��� ģ��ID�� �Է��ϼ��� : ";
	cin >> id;
	friend_ID.SetId(id);

	if (m_User.GetUserFriendList().Delete(friend_ID) == 0)
	{
		cout << "\n\tģ������Ʈ�� ��ϵ��� ���� ID �Դϴ�." << endl;
		cout << '\t' << system("pause");
		return 0;
	}

	cout << "\n\tģ������ �Ϸ�!" << endl;
	m_User.DisplayFriendListOnScreen();

	cout << '\t' << system("pause");

	return 1;
}


int Client::AddKakaoFriend()
{

	string id;
	Friend friend_ID;
	Member Mfriend_ID;

	cout << "\n\t�߰��Ϸ��� ģ��ID�� �Է��ϼ��� : ";
	cin >> id;
	friend_ID.SetId(id);
	Mfriend_ID.SetUserId(id);

	/**
	����ó��
	case 1 : �̹� ģ�� �߰����ִ��� ID ó��
	case 2 : �������� �ʴ� ID ó��
	case 3 : �ڱ��ڽ��� ģ���߰� �Ұ���
	*/
	if (m_User.GetUserFriendList().Get(friend_ID) == 1) {
		cout << "\n\t�̹� ��ϵ� ģ���Դϴ�." << endl;
		cout << '\t'; system("pause");
		return 0;
	}
	else if (pServer->GetMemberList().Get(Mfriend_ID) == 0) {
		cout << "\n\t�������� �ʴ� ID �Դϴ�." << endl;
		cout << '\t'; system("pause");
		return 0;
	}
	else if (m_User.GetUserId() == id) {
		cout << "\n\t�ڱ��ڽ��� ģ���� ����Ҽ� �����ϴ�." << endl;
		cout << '\t'; system("pause");
		return 0;
	}
	else {
		friend_ID.SetName(Mfriend_ID.GetUserName());
		cout << "\n\tģ����Ͽ� �����Ͽ����ϴ�." << endl;
		cout << '\t'; system("pause");
		m_User.GetUserFriendList().Add(friend_ID);
		m_User.DisplayFriendListOnScreen();

	}



	return 1;
}

void Client::sendMessage() {

	ChatMsg msg;

	//int seq;
	//string id;
	string receiver;

	msg.SetSeq(m_User.GetUserChatList().GetLength() + 1);
	msg.SetSender(m_User.GetUserId());

	do {
		cout << "\n\t1:1 ä���� ģ�� �Է� (0 : ������) >>";
		cin >> receiver;
		if (receiver == "0")
			return;

		Friend friend_recevier;
		friend_recevier.SetId(receiver);
		if (m_User.GetUserFriendList().Get(friend_recevier) == 1)
			break;
		else
		{
			cout << "\n\tģ���� ID�� �߸� �ԷµǾ����ϴ�." << endl;
			cout << '\t'; system("pause");
			return;
		}

	} while (1);

	while (1)
	{
		m_User.DisplayChatListOnScreen(receiver);

		char message[200];
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "\n\t���� �޽��� �Է�(1 : ���� , 0 : ���) >> ";
		cin.getline(message, 200, '\n');
		string sendMessage = message;
		if (sendMessage == "0")
			return;
		if (sendMessage == "1") {
			int seq;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "\n\t������ �޽��� ��ȣ �Է�(0 : ���) >> ";
			cin >> seq;
			if (seq == 0) {
				continue;
			}
			ChatMsg msg;
			msg.SetSeq(seq);
			if (m_User.GetUserChatList().Get(msg) == 1) {
				msg.SetDeleteState(true);
				m_User.GetUserChatList().Replace(msg);
				cout << "\n\t�޽��� ������ �����Ͽ����ϴ�." << endl;
				cout << '\t'; system("pause");
				return;
			}
			else {
				cout << "\n\t�޽��� ��ȣ�� ���������ʽ��ϴ�." << endl;
				cout << '\t'; system("pause");
				return;
			}

		}


		msg.SetMessage(sendMessage);
		msg.SetReceiver(receiver);
		msg.SetDeleteState(false);

		m_pMessageQueue->EnQueue(msg);	//�޼���ť enqueue
		pServer->receiveMessage();		//������ �޼��� ������

		//�α��� ���� ���� ����
		Member loginMember;
		loginMember.SetUserId(m_User.GetUserId());
		pServer->GetMemberList().Get(loginMember);
		SetUser(loginMember);
	}
}

void Client::PrintProfileImage()
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = (long)_findfirst(".\\images\\*.*", &fd);  //���� ���� �� ��� ������ ã�´�.


	while (result != -1)
	{
		if (fd.name == m_User.GetUserProfile())	//image ���� ���� �̹����� �����Ѵٸ�,
		{
			string image = "mspaint.exe images\\";
			image += m_User.GetUserProfile();
			system(image.c_str());	//�׸����� ���ؼ�, ������ ���
			break;
		}

		result = _findnext(handle, &fd);
	}

	_findclose(handle);

	if (result == -1)	// image ���Ͽ� �ش� �̹��� �����ٸ�,
	{
		string image = "mspaint.exe images\\none.jpg";
		system(image.c_str());
	}

	cout << endl;
}


int Client::KakaoFriendScreen()
{
	int command;

	system("cls");
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(14, 1);//�����
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "�� īī���� ä�� ���α׷� (�α���)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(13, 1);	//��ȫ��

	cout << "\t   1 : ģ�� �߰�" << endl;
	cout << "\t   2 : ģ�� �˻�" << endl;
	cout << "\t   3 : ģ�� ���" << endl;
	cout << "\t   4 : ģ�� ����" << endl;
	cout << "\t   5 : ��õģ�� ��ȸ" << endl;
	cout << "\t   0 : ������" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t ��ɾ� �Է�--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;


	return command;

}

void Client::KakaoFriendRun()
{
	bool IsRunning = true;
	int m_Command;
	while (IsRunning)
	{
		m_Command = KakaoFriendScreen();
		switch (m_Command)
		{
		case 1:	// ģ�� �߰�
			AddKakaoFriend();
			break;
		case 2:	// ģ�� �˻�
			SearchKakaoFriend();
			break;
		case 3:	// ģ�� ���
			DisplayKakaoFriend();
			break;
		case 4:	// ģ�� ����
			DeleteKakaoFriend();
			break;
		case 5:	// ��õģ�� ��ȸ
			DisplayKakaoRecoFriend();
			break;
		case 0:
			IsRunning = false;
			break;
		}
	}
}

int Client::DisplayKakaoRecoFriend()
{
	m_User.GetUserRecoFriendList().ResetList();
	int searchCount = 0;
	Friend item;
	cout << "\n\t--------------------��õ�ϴ� ģ��--------------------" << endl;
	for (int i = 0; i < m_User.GetUserRecoFriendList().GetLength(); i++)
	{
		m_User.GetUserRecoFriendList().GetNextItem(item);
		searchCount++;
		cout << "\n\t" << searchCount << ". " << item.GetId() << "(" << item.GetName() << ")" << endl;
	}

	if (searchCount == 0)
	{
		cout << "\n\t��õ�� ģ���� �����ϴ�." << endl;
	}

	cout << "\n\t-----------------------------------------------------" << endl;


	cout << "\t"; system("pause");

	return 0;
}

int Client::DisplayKakaoFriend()
{
	m_User.DisplayFriendListOnScreen();
	cout << "\t"; system("pause");
	return 0;
}


int Client::KakaoChatScreen()
{
	int command;

	system("cls");
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(14, 1);	//�����
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "�� īī���� ä�� ���α׷� (�α���)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(13, 1);	//��ȫ��

	cout << "\t   1 : 1:1 ä���ϱ�" << endl;
	cout << "\t   2 : ��ü ä���ϱ�" << endl;
	cout << "\t   0 : ������" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t ��ɾ� �Է�--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;


	return command;

}

void Client::KakaoChatRun()
{
	bool IsRunning = true;
	int m_Command;
	while (IsRunning)
	{
		m_Command = KakaoChatScreen();
		switch (m_Command)
		{
		case 1:	// 1:1ä���ϱ�
			DisplayChattingRoomList();
			break;
		case 2: // ��ü ä���ϱ� 
			KakaoTeamChatRun();
			break;
		case 0:
			IsRunning = false;
			break;
		}
	}
}

void Client::SetTextColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}


void Client::receiveClient()
{
	while (!m_pClientQueue->IsEmpty())
	{
		ClientType client;
		m_pClientQueue->DeQueue(client);

		//�����
		//cout << " Ŭ���̾�Ʈ�� �޾ҽ��ϴ�!!" << endl;
		//cout << "id : " << client.GetId() << endl;
		//cout << "name : " << client.GetName() << endl;
		//cout << "chatList : " << endl;

		client.GetMsgList().ResetList();
		ChatMsg item;


		for (int i = 0; i < client.GetMsgList().GetLength(); i++) {
			client.GetMsgList().GetNextItem(item);

			cout << item.GetReceiver() << endl;
			cout << item.GetSender() << endl;
			cout << item.GetMessage() << endl;
		}


		m_ClientList.Add(client);

		//cout << "Ŭ���̾�Ʈ ���� ����" << endl;
		//system("pause");

	}
}

void Client::receiveMessage()
{
	while (!m_pClientMessageQueue->IsEmpty())
	{
		ChatMsg msg;
		m_pClientMessageQueue->DeQueue(msg);

		if (msg.GetChatRoomMake())	//ä�ù� ���� �޼���
		{


			ClientType receiver;
			receiver.SetId(msg.GetReceiver());
			m_ClientList.Get(receiver);

			receiver.GetMsgList().Add(msg);

			if (msg.GetReceiver() == msg.GetSender()) // ä�ù� �����϶�,
			{
				//cout << "ä�ù��� �����Ǿ����ϴ�." << endl;
				ChatRoom room;
				room.SetName(msg.GetChatRoomName());

				receiver.GetChatRoomList().Add(room);

				//system("pause");

			}
			else	// ä�ù� �ʴ��� �߰�,
			{
				//cout << msg.GetSender() << "ģ���� �߰��Ǿ����ϴ�." << endl;
				ChatRoom room;
				room.SetName(msg.GetChatRoomName());
				receiver.GetChatRoomList().Get(room);
				room.GetMemberList().Add(msg.GetSender());

				receiver.GetChatRoomList().Replace(room);


				//system("pause");

			}

			if (m_User.GetUserId() == msg.GetReceiver()) {
				m_User.AddMessageTtoChatList(msg);

			}


			m_ClientList.Replace(receiver); //������Ʈ




		}
		else if (msg.GetChatRoomName() != "-1") //ä�ù����� ���� �� �޼���
		{
			//cout << "ä�ù����κ��� �޼��� ����" << endl;
			//system("pause");
			ClientType loginClient;
			loginClient.SetId(msg.GetReceiver());
			m_ClientList.Get(loginClient);

			ChatRoom loginRoom;
			loginRoom.SetName(msg.GetChatRoomName());

			loginClient.GetChatRoomList().Get(loginRoom);
			msg.SetSeq(loginRoom.GetMsgList().GetLength() + 1);

			/*cout << "seq : " << msg.GetSeq() << endl;
			cout << "sender : " << msg.GetSender() << endl;
			cout << "receiver : " << msg.GetReceiver() << endl;
			cout << "ChatRoomName : " << msg.GetChatRoomName() << endl;
			cout << "message : " << msg.GetMessage() << endl;
			cout << "ChatRoomMake : " << msg.GetChatRoomMake() << endl;
			system("pause");*/

			loginRoom.GetMsgList().Add(msg);

			loginClient.GetChatRoomList().Replace(loginRoom);
			m_ClientList.Replace(loginClient);

		}
		else // ���θ޼���
		{

			//�����
			//cout << " �޼����� �޾ҽ��ϴ�!!" << endl;
			//cout << "seq : " << msg.GetSeq() << endl;
			//cout << "sender : " << msg.GetSender() << endl;
			//cout << "receiver : " << msg.GetReceiver() << endl;
			//cout << "message : " << msg.GetMessage() << endl;

			//Receiver , loginMember�� ���� ���� ��������
			ClientType receiver;
			ClientType loginMember;

			Member m_loginMember;
			m_loginMember = GetUser();

			loginMember.SetId(m_loginMember.GetUserId());
			loginMember.SetName(m_loginMember.GetUserName());
			loginMember.SetMsgList(m_loginMember.GetUserChatList());
			receiver.SetId(msg.GetReceiver());
			m_ClientList.Get(receiver);


			//ä�� ����Ʈ�� �޽��� �߰�
			ChatMsg ReceiverMsg = msg;
			ChatMsg LoginMemberMsg = msg;
			ReceiverMsg.SetSeq(receiver.GetMsgList().GetLength() + 1);
			LoginMemberMsg.SetSeq(loginMember.GetMsgList().GetLength() + 1);
			receiver.GetMsgList().Add(ReceiverMsg);
			loginMember.GetMsgList().Add(LoginMemberMsg);

			//Ŭ���̾�Ʈ ����Ʈ�� �̸� ������Ʈ
			m_ClientList.Replace(receiver);
			m_ClientList.Replace(loginMember);


			//Ŭ���̾�Ʈ����Ʈ�� �� ������Ʈ �Ǿ��ִ��� �����
			/*m_ClientList.ResetList();
			for (int i = 0; i < m_ClientList.GetLength(); i++)
			{
				ClientType client;
				m_ClientList.GetNextItem(client);
				cout << "client ID : " << client.GetId() << endl;
				cout << "client Name : " << client.GetName() << endl;

				cout << "Client Message : " << endl;

				client.GetMsgList().ResetList();
				for (int j = 0; j < client.GetMsgList().GetLength(); j++) {
					ChatMsg msg;

					client.GetMsgList().GetNextItem(msg);
					cout << "receiver : " <<msg.GetReceiver() << endl;
					cout << "sender : " << msg.GetReceiver() << endl;
					cout << "content : " << msg.GetMessage() << endl;
				}
				system("pause");
			}*/


		}

	}
}

void Client::KakaoTeamChatRun()
{
	bool IsRunning = true;
	int m_Command;
	while (IsRunning)
	{
		m_Command = KakaoTeamChatScreen();
		switch (m_Command)
		{
		case 1:	// ����� ����
			createTeamChatRoom();
			break;
		case 2: // ����� ���
			displayTeamChatRoom();
			break;
		case 3: // īī���� �˻����
			searchTeamChatRoom();
			break;
		case 0:
			IsRunning = false;
			break;
		}
	}

}

int Client::KakaoTeamChatScreen()
{
	int command;

	system("cls");
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(14, 1);	//�����
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "�� īī���� ä�� ���α׷� (�α���)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(13, 1);	//��ȫ��

	cout << "\t   1 : ����� ����" << endl;
	cout << "\t   2 : ����� ���" << endl;
	cout << "\t   3 : īī���� �˻����" << endl;
	cout << "\t   0 : ������" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t ��ɾ� �Է�--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;


	return command;

}

/**
*	@brief	īī���� ä�ù��� �����Ѵ�.
*	@pre	none.
*	@post	īī���� ��ü ä�ù��� ���� �Ǿ�����.
*	@param	none.
*/
void Client::createTeamChatRoom()
{

	string ChatRoomName;

	Member m_loginMember;
	m_loginMember = GetUser();



	cout << "\t������ ����� �̸� : ";
	cin >> ChatRoomName;

	ChatMsg ChatRoomMsg;	//Ư�� �޼��� ����(����� ���� �޼���)
	ChatRoomMsg.SetSeq(m_loginMember.GetUserChatList().GetLength() + 1);		//�޼��� ��ȣ
	ChatRoomMsg.SetSender(m_loginMember.GetUserId());							//���� ���
	ChatRoomMsg.SetReceiver(m_loginMember.GetUserId());							//�޴� ���
	ChatRoomMsg.SetChatRoomName(ChatRoomName);									//ä�ù� ����
	ChatRoomMsg.SetDeleteState(false);											//�޼��� ���� State
	ChatRoomMsg.SetChatRoomMake(true);											//ä�ù� ���� State



	string FriendName[100];
	int FriendNameLength = 0;

	Friend FriendSearch;

	while (true)
	{

		cout << "\t�ʴ��� ģ�� �̸�(0. ������, 1.ä�ù� ����) : ";
		cin >> FriendName[FriendNameLength];
		if (FriendName[FriendNameLength] == "0")
			return;
		else if (FriendName[FriendNameLength] == "1")
			break;

		//���� ó��
		FriendSearch.SetId(FriendName[FriendNameLength]);
		if (!m_loginMember.GetUserFriendList().Get(FriendSearch)) {
			cout << "\tģ���� �������� �ʽ��ϴ�." << endl;
			continue;
		}


		FriendNameLength++;
	}

	//�ڽ��� ä�ù� ����
	m_pMessageQueue->EnQueue(ChatRoomMsg);	//�޼���ť enqueue(ä�ù� ���� �޼��� ����)
	pServer->receiveChatRoomMsg();

	//ģ������ ä�ù浵 ����
	for (int i = 0; i < FriendNameLength; i++)
	{
		ChatRoomMsg.SetSender(FriendName[i]);
		ChatRoomMsg.SetReceiver(FriendName[i]);	//�޴� ���(ģ���� ����)
		m_pMessageQueue->EnQueue(ChatRoomMsg);	//�޼���ť enqueue(ä�ù� ���� �޼��� ����)
	}
	pServer->receiveChatRoomMsg();

	FriendName[FriendNameLength] = m_loginMember.GetUserId();
	FriendNameLength++;

	//ä�ù� ��Ͽ� ģ���߰�
	for (int i = 0; i < FriendNameLength; i++)
	{
		ChatRoomMsg.SetReceiver(FriendName[i]);	//�޴� ���
		for (int j = 0; j < FriendNameLength; j++)
		{
			if (j == i)
				continue;
			else
				ChatRoomMsg.SetSender(FriendName[j]);

			m_pMessageQueue->EnQueue(ChatRoomMsg);	//�޼���ť enqueue(ä�ù� ���� �޼��� ����)
		}
	}
	pServer->receiveChatRoomMsg();

}

/**
*	@brief	īī���� ��ü ä�ù� ����� ����Ѵ�.
*	@pre	none.
*	@post	īī���� ��ü ä�ù� ����� ��� �Ǿ�����.
*	@param	none.
*/
void Client::displayTeamChatRoom()
{
	ClientType loginClient;

	loginClient.SetId(m_User.GetUserId());
	m_ClientList.Get(loginClient);


	int RoomsearchCount = 0;

	cout << "\n\t--------------------ä�ù� ���--------------------" << endl;
	loginClient.GetChatRoomList().ResetList();
	for (int i = 0; i < loginClient.GetChatRoomList().GetLength(); i++)
	{
		ChatRoom item;
		loginClient.GetChatRoomList().GetNextItem(item);
		RoomsearchCount++;
		cout << "\n\t" << RoomsearchCount << ". " << item.GetName() << "(";

		//��� ���
		item.GetMemberList().ResetList();
		for (int j = 0; j < item.GetMemberList().GetLength(); j++)
		{
			string Member;
			item.GetMemberList().GetNextItem(Member);
			cout << Member;
			if (j != item.GetMemberList().GetLength() - 1)
				cout << ", ";
		}
		cout << ")";
	}

	if (RoomsearchCount == 0)
	{
		cout << "\n\t������ ä�ù��� �����ϴ�." << endl;
	}

	cout << "\n\t------------------------------------------------" << endl;

	string EnterChatRoom;
	cout << "\n\t������ ä�ù� �̸� �Է� (0. ������) :";
	cin >> EnterChatRoom;
	if (EnterChatRoom == "0")
		return;

	ChatRoom room;
	room.SetName(EnterChatRoom);

	//ä�ù� ��������
	int success = loginClient.GetChatRoomList().Get(room);
	if (success == 0) {
		cout << "\t�������� �ʴ� ä�ù��Դϴ�.." << endl;
		system("pause");
		return;
	}



	//ä�� �Է�
	while (1)
	{
		system("cls");

		ClientType loginClient;

		loginClient.SetId(m_User.GetUserId());
		m_ClientList.Get(loginClient);

		ChatRoom room;
		room.SetName(EnterChatRoom);

		//ä�ù� ��������
		int success = loginClient.GetChatRoomList().Get(room);
		if (success == 0) {
			cout << "\t�������� �ʴ� ä�ù��Դϴ�.." << endl;
			system("pause");
			return;
		}

		cout << endl;
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
			cout << endl;
		SetTextColor(14, 1);	//�����
		cout << "\t    ID : " << loginClient.GetName() << "�� īī���� ä�� ���α׷� (�α���)" << endl;
		cout << "\t    ä�ù� �̸� : " << room.GetName() << endl;
		cout << endl;
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
			SetTextColor(14, 1);	//�����

		DoublySortedLinkedList<ChatMsg> m_UserChatList = room.GetMsgList();
		int searchCount = 0;
		ChatMsg item;
		Friend receiver;
		for (int i = 0; i < m_UserChatList.GetLength(); i++)
		{

			m_UserChatList.GetNextItem(item);
			if (item.GetDeleteState())
				continue;

			searchCount++;

			if (item.GetSender() == loginClient.GetId()) {
				SetTextColor(14, 1);
				cout << "\n\t\t\t\t\t\t" << item.GetSeq() << ". " << loginClient.GetId() << "(" << loginClient.GetName() << ")" << endl;
				cout << "\n\t\t\t\t\t\t" << item.GetMessage() << endl;
				SetTextColor(10, 1);

			}
			else {

				Friend m_Friend;
				m_Friend.SetId(item.GetSender());
				m_User.GetUserFriendList().Get(m_Friend);
				SetTextColor(13, 1);
				cout << "\n\t" << item.GetSeq() << ". " << m_Friend.GetId() << "(" << m_Friend.GetName() << ")" << endl;
				cout << "\n\t" << item.GetMessage() << endl;
				SetTextColor(10, 1);
			}


		}

		if (searchCount == 0)
		{
			SetTextColor(14, 1);
			cout << "\n\t��ȭ�� �������� �ʽ��ϴ�.." << endl;

		}

		SetTextColor(10, 1);
		LINE


			//system("pause");

		char message[200];
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "\n\t(0:���, 1:����, 2:����, 3:�˻�, 4:�ٿ��ֱ�, 5:�̹�������) " << endl;
		cout << "\n\t���� �޽��� �Է� >> ";

		cin.getline(message, 200, '\n');
		string sendMessage = message;
		if (sendMessage == "0")
			return;
		if (sendMessage == "1") {	//�޼��� ���� ó��
			int seq;
			//cin.clear();
			//cin.ignore(INT_MAX, '\n');
			cout << "\n\t������ �޽��� ��ȣ �Է�(0 : ���) >> ";
			cin >> seq;
			if (seq == 0) {
				continue;
			}
			ChatMsg msg;
			msg.SetSeq(seq);
			if (room.GetMsgList().Get(msg) == 1) {
				msg.SetDeleteState(true);
				room.GetMsgList().Replace(msg);
				loginClient.GetChatRoomList().Replace(room);
				m_ClientList.Replace(loginClient);

				cout << "\n\t�޽��� ������ �����Ͽ����ϴ�." << endl;
				cout << '\t'; system("pause");
				continue;
			}
			else {
				cout << "\n\t�޽��� ��ȣ�� ���������ʽ��ϴ�." << endl;
				cout << '\t'; system("pause");
				continue;
			}

		}
		else if (sendMessage == "2") {	//�޼��� ���� ó��
			int seq;
			cout << "\n\t������ �޽��� ��ȣ �Է�(0 : ���) >> ";
			cin >> seq;
			if (seq == 0) {
				continue;
			}
			ChatMsg msg;
			msg.SetSeq(seq);
			if (room.GetMsgList().Get(msg) == 1) {

				m_ClipBoard = msg.GetMessage();
				cout << "\n\t�޼��� ���翡 �����Ͽ����ϴ�." << endl;
				cout << '\t'; system("pause");
				continue;
			}
			else {
				cout << "\n\t�޽��� ��ȣ�� ���������ʽ��ϴ�." << endl;
				cout << '\t'; system("pause");
				continue;
			}

		}
		else if (sendMessage == "3") {	//�޼��� �˻� ó��
			string SearchContent;
			cout << "\n\t�˻��� �޽��� ���� �Է�(0 : ���) >> ";
			cin >> SearchContent;
			if (SearchContent == "0") {
				continue;
			}

			int searchCount = 0;

			cout << "\n\t--------------------�޼��� �˻����--------------------" << endl;
			room.GetMsgList().ResetList();
			for (int i = 0; i < room.GetMsgList().GetLength(); i++)
			{
				ChatMsg SearchItem;
				room.GetMsgList().GetNextItem(SearchItem);

				if (SearchItem.GetMessage().find(SearchContent) != string::npos) {
					searchCount++;
					Friend SenderName;
					SenderName.SetId(SearchItem.GetSender());
					loginClient.GetFriendList().Get(SenderName);
					if (loginClient.GetId() == SearchItem.GetSender()) {
						SenderName.SetName(loginClient.GetName());
					}
					cout << "\n\t" << searchCount << ". " << SearchItem.GetSender() << "(" << SenderName.GetName() << ")" << endl;
					cout << "\n\t" << SearchItem.GetMessage() << endl << endl;
				}
			}

			if (searchCount == 0)
			{
				cout << "\n\t�˻��� �޼����� �������� �ʽ��ϴ�." << endl;
			}

			cout << "\n\t-------------------------------------------------------" << endl;
			cout << '\t'; system("pause");
			continue;

		}
		else if (sendMessage == "4") { //�޼��� �ٿ��ֱ� ó��
			if (m_ClipBoard == "") {
				cout << "\n\tŬ�����忡 ������ �����ϴ�." << endl;
				cout << '\t'; system("pause");
				continue;

			}
			sendMessage = m_ClipBoard;

		}
		else if (sendMessage == "5") { //�̹������� ó��
			int seq;
			cout << "\n\t�̹����� ��� �޽��� ��ȣ �Է�(0 : ���) >> ";
			cin >> seq;
			if (seq == 0) {
				continue;
			}
			ChatMsg msg;
			msg.SetSeq(seq);
			if (room.GetMsgList().Get(msg) == 1) {

				DisplayImage(msg.GetMessage());
				cout << "\n\t�̹��� ���⿡ �����Ͽ����ϴ�." << endl;
				cout << '\t'; system("pause");
				continue;
			}
			else {
				cout << "\n\t�޽��� ��ȣ�� ���������ʽ��ϴ�." << endl;
				cout << '\t'; system("pause");
				continue;
			}
		}

		//�޼��� ���� ó��
		ChatMsg TeamMsg;
		TeamMsg.SetMessage(sendMessage);
		TeamMsg.SetSender(loginClient.GetId());
		TeamMsg.SetChatRoomName(EnterChatRoom);
		TeamMsg.SetReceiver(loginClient.GetId());

		m_pMessageQueue->EnQueue(TeamMsg);	//�޼���ť enqueue
		pServer->receiveChatRoomMsg();		//������ �޼��� ������

		////�α��� ���� ���� ����								
		Member loginMember;
		loginMember.SetUserId(m_User.GetUserId());
		pServer->GetMemberList().Get(loginMember);
		SetUser(loginMember);

		room.GetMemberList().ResetList();
		//ä�ù� ��� ��ο��� �޼��� ����
		for (int i = 0; i < room.GetMemberList().GetLength(); i++)
		{
			string m_RoomMember;
			room.GetMemberList().GetNextItem(m_RoomMember);

			TeamMsg.SetReceiver(m_RoomMember);

			m_pMessageQueue->EnQueue(TeamMsg);	//�޼���ť enqueue
			pServer->receiveChatRoomMsg();		//������ �޼��� ������

			////�α��� ���� ���� ����								
			Member loginMember;
			loginMember.SetUserId(m_User.GetUserId());
			pServer->GetMemberList().Get(loginMember);
			SetUser(loginMember);
		}
	}


}

void Client::loadDB()
{
	m_ClientList.ResetList();
	for (int i = 0; i < m_ClientList.GetLength(); i++)
	{
		ClientType client;
		m_ClientList.GetNextItem(client);
		client.GetMsgList().ResetList();
		for (int j = 0; j < client.GetMsgList().GetLength(); j++)
		{
			ChatMsg msg;
			client.GetMsgList().GetNextItem(msg);
			if (msg.GetChatRoomMake()) {

				if (msg.GetReceiver() == msg.GetSender()) // ä�ù� �����϶�,
				{
					//cout << "ä�ù��� �����Ǿ����ϴ�." << endl;
					ChatRoom room;
					room.SetName(msg.GetChatRoomName());

					client.GetChatRoomList().Add(room);

					//system("pause");

				}
				else	// ä�ù� �ʴ��� �߰�,
				{
					//cout << msg.GetSender() << "ģ���� �߰��Ǿ����ϴ�." << endl;
					ChatRoom room;
					room.SetName(msg.GetChatRoomName());
					client.GetChatRoomList().Get(room);
					room.GetMemberList().Add(msg.GetSender());

					client.GetChatRoomList().Replace(room);


					//system("pause");

				}



			}
			else if (msg.GetChatRoomName() != "-1") {
				ChatRoom room;
				room.SetName(msg.GetChatRoomName());
				client.GetChatRoomList().Get(room);
				msg.SetSeq(room.GetMsgList().GetLength() + 1);
				room.GetMsgList().Add(msg);

				client.GetChatRoomList().Replace(room);

			}

			m_ClientList.Replace(client); //������Ʈ
		}

	}
}

void Client::DisplayImage(string name)
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = (long)_findfirst(".\\images\\*.*", &fd);  //���� ���� �� ��� ������ ã�´�.


	while (result != -1)
	{
		if (fd.name == name)	//image ���� ���� �̹����� �����Ѵٸ�,
		{
			string image = "mspaint.exe images\\";
			image += name;
			system(image.c_str());	//�׸����� ���ؼ�, ������ ���
			break;
		}

		result = _findnext(handle, &fd);
	}

	_findclose(handle);

	if (result == -1)	// image ���Ͽ� �ش� �̹��� �����ٸ�,
	{
		string image = "mspaint.exe images\\none.jpg";
		system(image.c_str());
	}

	cout << endl;
}

void Client::searchTeamChatRoom()
{
	string searchName;
	ChatRoom searchChatRoom;
	string searchChatMember;;

	cout << "\n\tä�ù� �̸�,������ �˻� >> ";
	cin >> searchName;

	ClientType LoginClient;
	LoginClient.SetId(m_User.GetUserId());
	m_ClientList.Get(LoginClient);

	LoginClient.GetChatRoomList().ResetList();

	int RoomsearchCount = 0;
	cout << "\n\t--------------------īī���� �˻����--------------------" << endl;

	//ä�ù� �˻�
	for (int i = 0; i < LoginClient.GetChatRoomList().GetLength(); i++)
	{
		LoginClient.GetChatRoomList().GetNextItem(searchChatRoom);

		if (searchChatRoom.GetName() == searchName)	//�˻��� ä�ù��̸��� ��ġ�Ѵٸ�,
		{
			RoomsearchCount++;
			cout << "\n\t" << RoomsearchCount << ". " << searchChatRoom.GetName() << "(";

			//��� ���
			searchChatRoom.GetMemberList().ResetList();
			for (int k = 0; k < searchChatRoom.GetMemberList().GetLength(); k++)
			{
				string Member;
				searchChatRoom.GetMemberList().GetNextItem(Member);
				cout << Member;
				if (k != searchChatRoom.GetMemberList().GetLength() - 1)
					cout << ", ";
			}
			cout << ")";

			continue;
		}

		//ä�ù� �� ��� �˻�
		searchChatRoom.GetMemberList().ResetList();
		for (int j = 0; j < searchChatRoom.GetMemberList().GetLength(); j++)
		{
			searchChatRoom.GetMemberList().GetNextItem(searchChatMember);

			if (searchChatMember == searchName) { //�˻��� ����̸��� ��ġ�Ѵٸ�,

				RoomsearchCount++;
				cout << "\n\t" << RoomsearchCount << ". " << searchChatRoom.GetName() << "(";

				//��� ���
				searchChatRoom.GetMemberList().ResetList();
				for (int k = 0; k < searchChatRoom.GetMemberList().GetLength(); k++)
				{
					string Member;
					searchChatRoom.GetMemberList().GetNextItem(Member);
					cout << Member;
					if (k != searchChatRoom.GetMemberList().GetLength() - 1)
						cout << ", ";
				}
				cout << ")";

				break;
			}
		}
	}

	if (RoomsearchCount == 0)
	{
		cout << "\n\t�˻��� ä�ù��� �������� �ʽ��ϴ�." << endl;
	}

	cout << "\n\t-------------------------------------------------------" << endl;
	cout << '\t'; system("pause");


}

/**
*	@brief	�Է¹��� ��ɾ�κ���, īī���� ģ���׷� ��ɰ��� �Լ� ȣ��
*	@pre	none.
*	@post	none.
*	@param	none.
*/
void Client::KakaoFriendGroupRun()
{
	bool IsRunning = true;
	int m_Command;
	while (IsRunning)
	{
		m_Command = KakaoFriendGroupScreen();
		switch (m_Command)
		{
		case 1:	// �׷� ����
			createFriendGroup();
			break;
		case 2: // �׷� ���
			displayFriendGroup();
			break;
		case 3: // �׷� ����
			deleteFriendGroup();
			break;
		case 0:
			IsRunning = false;
			break;
		}
	}

}

int Client::KakaoFriendGroupScreen()
{
	int command;

	system("cls");
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(14, 1);	//�����
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "�� īī���� ä�� ���α׷� (�α���)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//�ʷϻ�
	LINE
		SetTextColor(13, 1);	//��ȫ��

	cout << "\t   1 : ģ���׷� ����" << endl;
	cout << "\t   2 : ģ���׷� ���" << endl;
	cout << "\t   3 : ģ���׷� ����" << endl;
	cout << "\t   0 : ������" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t ��ɾ� �Է�--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;


	return command;

}

/**
*	@brief	īī���� ģ���׷��� �����Ѵ�.
*	@pre	none.
*	@post	īī���� ģ���׷��� ���� �Ǿ�����.
*	@param	none.
*/
void Client::createFriendGroup()
{
	string GroupName;
	string GroupImage;

	Member m_loginMember;
	m_loginMember = GetUser();

	ClientType loginClient;
	loginClient.SetId(GetUser().GetUserId());
	m_ClientList.Get(loginClient);

	FriendGroup group;


	cout << "\t������ �׷� �̸� : ";
	cin >> GroupName;
	group.SetName(GroupName);
	cout << "\t�׷� �̹��� �Է� : ";
	cin >> GroupImage;
	group.SetGroupImage(GroupImage);

	m_loginMember.GetUserFriendGroupList().Add(group);
	loginClient.GetFriendGroupList().Add(group);

	pServer->GetMemberList().Replace(m_loginMember);
	m_ClientList.Replace(loginClient);
	m_User = m_loginMember;

	cout << "\t�׷� ���� �Ϸ�" << endl;

	cout << '\t'; system("pause");


}

/**
*	@brief	īī���� ģ�� �׷� ����� ����Ѵ�.
*	@pre	none.
*	@post	īī���� ģ�� �׷� ����� ��� �Ǿ�����.
*	@param	none.
*/
void Client::displayFriendGroup()
{
	Member m_loginMember;
	m_loginMember = GetUser();

	ClientType loginClient;

	loginClient.SetId(m_User.GetUserId());
	m_ClientList.Get(loginClient);


	int GroupsearchCount = 0;

	cout << "\n\t--------------------�׷� ���--------------------" << endl;
	loginClient.GetFriendGroupList().ResetList();
	for (int i = 0; i < loginClient.GetFriendGroupList().GetLength(); i++)
	{
		FriendGroup item;
		loginClient.GetFriendGroupList().GetNextItem(item);
		GroupsearchCount++;
		cout << "\n\t" << GroupsearchCount << ". " << item.GetName() << endl;

		//��� ���
		item.GetFriendList().ResetList();
		int MembmerCount = 0;
		for (int j = 0; j < item.GetFriendList().GetLength(); j++)
		{
			Friend Member;
			item.GetFriendList().GetNextItem(Member);
			MembmerCount++;
			cout << "\n\t\t" << MembmerCount << ") " << Member.GetId() << "(" << Member.GetName() << ")" << endl;
			if (MembmerCount == 0)
			{
				cout << "\n\t\t�׷쿡 ģ���� �����ϴ�." << endl;
			}
		}

	}

	if (GroupsearchCount == 0)
	{
		cout << "\n\t������ �׷��� �����ϴ�." << endl;
	}

	cout << "\n\t------------------------------------------------" << endl;

	string EnterFriendGroup;
	cout << "\n\tģ�� �߰��� �׷� �̸� �Է� (0. ������) :";
	cin >> EnterFriendGroup;
	if (EnterFriendGroup == "0")
		return;

	FriendGroup friendGroup;
	friendGroup.SetName(EnterFriendGroup);

	//ģ���׷� ��������
	int success = loginClient.GetFriendGroupList().Get(friendGroup);
	if (success == 0) {
		cout << "\t�������� �ʴ� �׷��Դϴ�." << endl;
		system("pause");
		return;
	}

	//ä�� �Է�
	while (1)
	{
		system("cls");

		cout << endl;
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
			SetTextColor(14, 1);	//�����
		cout << endl;
		cout << "\t    ID : " << m_User.GetUserId() << "�� īī���� ä�� ���α׷� (�α���)" << endl;
		cout << endl;
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
		SetTextColor(13, 1);	//��ȫ��

		SetTextColor(10, 1);
		LINE


		cout << "\n\t--------------------�׷��� ���--------------------" << endl;

		//��� ���
		friendGroup.GetFriendList().ResetList();
		int MembmerCount = 0;
		for (int j = 0; j < friendGroup.GetFriendList().GetLength(); j++)
		{
			Friend Member;
			friendGroup.GetFriendList().GetNextItem(Member);
			MembmerCount++;
			cout << "\n\t\t" << MembmerCount << ") " << Member.GetId() << "(" << Member.GetName() << ")" << endl;
			if (MembmerCount == 0)
			{
				cout << "\n\t\t�׷쿡 ģ���� �����ϴ�." << endl;
			}
		}

		cout << "\n\t------------------------------------------------------" << endl;


		cin.clear();
		cin.ignore(INT_MAX, '\n');
		string AddFriendName;
		cout << "\n\t�߰��� ģ�� �̸� �Է�(0. ������, 1.�׷���� ��ȸ) >> ";
		cin >> AddFriendName;
		if (AddFriendName == "0")
			return;
		if (AddFriendName == "1") {	//�׷���� ��ȸ
			DisplayImage(friendGroup.GetGroupImage());

		}
		else { //�׷쿡 ģ���߰�
			Friend AddFriend;
			AddFriend.SetId(AddFriendName);
			int success = loginClient.GetFriendList().Get(AddFriend);
			if (success == 1) {

				int check = friendGroup.GetFriendList().Get(AddFriend);
				if (check == 1) {
					cout << "\n\t�̹� ��ϵ� ģ���Դϴ�." << endl;
					cout << '\t'; system("pause");
					continue;
				}
				else {
					friendGroup.GetFriendList().Add(AddFriend);
					m_loginMember.GetUserFriendGroupList().Add(friendGroup);

					
					loginClient.GetFriendGroupList().Replace(friendGroup);

					m_loginMember.GetUserFriendGroupList().Replace(friendGroup);
					pServer->GetMemberList().Replace(m_loginMember);
					m_ClientList.Replace(loginClient);
					m_User = m_loginMember;

					cout << "\n\t�׷쿡 ģ���� ��ϵǾ����ϴ�." << endl;
					cout << '\t'; system("pause");
					continue;
				}

			}
			else {
				cout << "\n\t�������� �ʴ�ģ���Դϴ�." << endl;
				cout << '\t'; system("pause");
				continue;
			}
		}

	}

}

/**
*	@brief	īī���� ģ���׷��� �����ȴ�.
*	@pre	none.
*	@post	�Է��� ģ���׷��� �����Ǿ�����.
*	@param	none.
*/
void Client::deleteFriendGroup()
{
	Member m_loginMember;
	m_loginMember = GetUser();

	ClientType loginClient;

	loginClient.SetId(m_User.GetUserId());
	m_ClientList.Get(loginClient);


	int GroupsearchCount = 0;

	cout << "\n\t--------------------�׷� ���--------------------" << endl;
	loginClient.GetFriendGroupList().ResetList();
	for (int i = 0; i < loginClient.GetFriendGroupList().GetLength(); i++)
	{
		FriendGroup item;
		loginClient.GetFriendGroupList().GetNextItem(item);
		GroupsearchCount++;
		cout << "\n\t" << GroupsearchCount << ". " << item.GetName() << endl;

		//��� ���
		item.GetFriendList().ResetList();
		int MembmerCount = 0;
		for (int j = 0; j < item.GetFriendList().GetLength(); j++)
		{
			Friend Member;
			item.GetFriendList().GetNextItem(Member);
			MembmerCount++;
			cout << "\n\t\t" << MembmerCount << ") " << Member.GetId() << "(" << Member.GetName() << ")" << endl;
			if (MembmerCount == 0)
			{
				cout << "\n\t\t�׷쿡 ģ���� �����ϴ�." << endl;
			}
		}

	}

	if (GroupsearchCount == 0)
	{
		cout << "\n\t������ �׷��� �����ϴ�." << endl;
	}

	cout << "\n\t------------------------------------------------" << endl;

	string EnterFriendGroup;
	cout << "\n\t���� �׷� �̸� �Է� (0. ������) :";
	cin >> EnterFriendGroup;
	if (EnterFriendGroup == "0")
		return;

	FriendGroup friendGroup;
	friendGroup.SetName(EnterFriendGroup);

	//ģ���׷� ��������
	int success = loginClient.GetFriendGroupList().Get(friendGroup);
	if (success == 0) {
		cout << "\t�������� �ʴ� �׷��Դϴ�." << endl;
		system("pause");
		return;
	}
	else { //�׷� �����ϱ�
		
		m_loginMember.GetUserFriendGroupList().Delete(friendGroup);
		loginClient.GetFriendGroupList().Delete(friendGroup);
		
		m_loginMember.GetUserFriendGroupList().Replace(friendGroup);
		pServer->GetMemberList().Replace(m_loginMember);
		m_ClientList.Replace(loginClient);
		m_User = m_loginMember;

		cout << "\n\t�׷��� ���� �Ǿ����ϴ�." << endl;
		cout << '\t'; system("pause");
		
	}
}

