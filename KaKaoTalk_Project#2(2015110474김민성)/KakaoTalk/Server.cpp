#include "Server.h"

// Display all records in the list on screen.
void Server::DisplayAllMembers()
{
	Member data;

	cout << "\n\tīī���� ȸ�� ���" << endl;
	cout << "------------------------------------------" << endl;


	m_MemberList.ResetList();
	int length = m_MemberList.GetLength();
	m_MemberList.GetNextItem(data);
	for (int i = 0; i < length; i++)
	{
		data.DisplayRecordOnScreen();
		m_MemberList.GetNextItem(data);
	}

	cout << "------------------------------------------" << endl;

}

// Add new record into list.

int Server::AddNewMember()
{

	if (m_MemberList.IsFull())
	{
		cout << "\n\tList is full" << endl;
		return 0;
	}

	Member item;

	while (true)
	{
		item.SetRecordFromKB();
		if (m_MemberList.Get(item) != 0) {
			cout << "\n\t�̹� �����ϴ� ID��, ������ �����Ҽ� �����ϴ�." << endl;
			cout << "\t"; system("pause");

		}
		else
			break;
	}

	int success = m_MemberList.Add(item);
	if (success) {
		cout << "\n\t" + item.GetUserId() + "���� ȸ�������� ���ϵ帳�ϴ�!" << endl;
		cout << "\t"; system("pause");
	}

	//ȸ������ ��, ���� -> Ŭ���̾�Ʈ (Ŭ���̾�Ʈ ���� ť�� ����)
	ClientType sendClient;
	sendClient.SetId(item.GetUserId());
	sendClient.SetName(item.GetUserName());
	sendClient.SetMsgList(item.GetUserChatList());

	m_pClientQueue->EnQueue(sendClient);	//ť�� Ŭ���̾�Ʈ ����
	pClient->receiveClient();				//Ŭ���̾�Ʈ ����Ʈ�� Ŭ���̾�Ʈ �߰�

	DisplayAllMembers();

	return 1;
}

//�߰��� �κ�
int Server::DeleteMember()
{
	if (m_MemberList.GetLength() == 0)
	{
		cout << "\n\tList is Empty" << endl;
		return 0;
	}

	Member data;

	data.SetIdFromKB();

	int success = m_MemberList.Delete(data);
	if (success) {
		cout << "\n\t" + data.GetUserId() + "�� ������ �����Ͽ����ϴ�." << endl;
	}
	else {
		cout << "\n\t" + data.GetUserId() + "�� ���Ե��� ���� ȸ�� �Դϴ�." << endl;
		return 0;
	}

	DisplayAllMembers();

	return 1;
}


int Server::MemberLogIn()
{
	Member itemId;
	Member itemPW;
	string checkPW;

	itemId.SetIdFromKB();

	itemPW.SetPasswordFromKB();

	int checkId = m_MemberList.Get(itemId);

	if (checkId == 0)
	{
		cout << "\n\tȸ���� ID�� �������� �ʽ��ϴ�." << endl;
		cout << "\t"; system("pause");
		return 0;
	}
	else
	{
		//Member List���� ������ ��й�ȣ�� �Է��� ��й�ȣ�� ��ġ�Ѵٸ�,
		if (!strcmp(itemId.GetUserPassword().c_str(), itemPW.GetUserPassword().c_str()))
		{
			cout << "\n\t���������� �α��ο� �����Ͽ����ϴ�." << endl << endl;
			if (itemId.GetUserAlarmMessage()) {
				PlaySound(TEXT("music\\alarm.wav"), NULL, SND_ASYNC);	//�޽��� �˶� ���
				SetTextColor(12, 1);
				cout << "\t�˶� : ���ο� �޽����� �����߽��ϴ�!!" << endl;
			}
			SetTextColor(10, 1);
			cout << endl;
			cout << "\t"; system("pause");
			itemId.SetUserLogin(true);
			m_MemberList.Replace(itemId);
			m_MemberList.Display(itemId);
			m_MemberList.Get(itemId);

			if (itemId.GetUserAlarmMessage()) {	//������ �޽����� �ִٸ�,

				itemId.SetUserAlarmMessage(false);
			}

			pClient->SetUser(itemId);
			m_Run = false;
			pClient->SetRun(true);

		}
		else
		{
			cout << "\n\tȸ���� ID �Ǵ� Password �� ��ġ���� �ʽ��ϴ�." << endl;
			cout << "\t"; system("pause");
			return 0;
		}
	}


	return 1;
}


int Server::MemberLogOut()
{

	cout << "\n\t���������� �α׾ƿ� �Ǿ����ϴ�." << endl << endl;
	cout << "\t"; system("pause");
	Member loginMember;
	loginMember = pClient->GetUser();
	loginMember.SetUserLogin(false);

	m_MemberList.Replace(loginMember);
	m_MemberList.Display(loginMember);

	m_Run = true;
	pClient->SetRun(false);


	return 1;
}


int Server::SearchMemberById()
{


	Member item;

	item.SetIdFromKB();
	cout << "\n\t--------------------��ȸ���--------------------" << endl;
	int success = m_MemberList.Display(item);
	
	cout << "\n\t------------------------------------------------" << endl;
	if (success) {
		m_MemberList.Get(item);
		//��õ ģ���� �ֱ�
		if (pClient->IsRunning() == true) {
			Member LoginMember = pClient->GetUser();
			Friend recoFriend;
			recoFriend.SetId(item.GetUserId());
			recoFriend.SetName(item.GetUserName());

			Member FriendMember;
			FriendMember.SetUserId(recoFriend.GetId());
			m_MemberList.Get(FriendMember);
			
			int check = FriendMember.GetUserRecoFriendList().Get(recoFriend);
			if (check == 0) {
				//LoginMember.GetUserRecoFriendList().Add(recoFriend);
				
				Friend loginFriend;
				loginFriend.SetId(LoginMember.GetUserId());
				loginFriend.SetName(LoginMember.GetUserName());
				
				FriendMember.GetUserRecoFriendList().Add(loginFriend);

				m_MemberList.Replace(FriendMember);
				//m_MemberList.Replace(LoginMember);
				pClient->SetUser(LoginMember);

			}
		}
		cout << "\n\t" + item.GetUserId() + "�� ������ ��ȸ�Ͽ����ϴ�." << endl;
		cout << "\t"; system("pause");
	}
	else {
		cout << "\n\t" + item.GetUserId() + "�� ���Ե��� ���� ȸ�� �Դϴ�." << endl;
		cout << "\t"; system("pause");
		return 0;
	}

	return 1;
}


int Server::UpdateMember()
{


	Member itemId;
	Member itemPW;
	string checkPW;

	itemId.SetIdFromKB();
	itemPW.SetPasswordFromKB();

	int checkId = m_MemberList.Get(itemId);
	if (checkId == -1)
	{
		cout << "\n\tȸ���� ID�� �������� �ʽ��ϴ�." << endl;
		cout << "\t"; system("pause");
		return 0;
	}
	else
	{
		//Member List���� ������ ��й�ȣ�� �Է��� ��й�ȣ�� ��ġ�Ѵٸ�,
		if (itemId.GetUserPassword() == itemPW.GetUserPassword())
		{
			bool IsRunning = true;
			int m_Command;
			while (IsRunning)
			{
				m_Command = UpdateMemberScreen();
				switch (m_Command)
				{
				case 1:	// ��й�ȣ ����
					itemId.SetPasswordFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t��й�ȣ�� ����Ǿ����ϴ�." << endl;
					break;
				case 2:	// �̸� ����
					itemId.SetNameFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t�̸��� ����Ǿ����ϴ�." << endl;
					break;
				case 3:	// ������� ����
					itemId.SetBirthdayFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t��������� ����Ǿ����ϴ�." << endl;
					break;
				case 4:	// ���� ����
					itemId.SetGenderFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t������ ����Ǿ����ϴ�." << endl;
					break;
				case 5:	// �޴�����ȣ ����
					itemId.SetPhoneFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t�޴�����ȣ�� ����Ǿ����ϴ�." << endl;
					break;
				case 6:	// ������ ����
					itemId.SetBackgroundFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t�������� ����Ǿ����ϴ�." << endl;
					break;
				case 7: // �����ʻ��� ����
					itemId.SetProfileFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t�����ʻ����� ����Ǿ����ϴ�." << endl;
					break;
				case 8:	// �̸��� ����
					itemId.SetEmailFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t�̸����� ����Ǿ����ϴ�." << endl;
					break;
				case 0:
					IsRunning = false;
					break;
				}

				cout << "\n\t--------------------����Ȯ��--------------------" << endl;
				int success = m_MemberList.Display(itemId);
				cout << "\n\t------------------------------------------------" << endl;
				cout << "\t"; system("pause");
			}
		}
		else
		{
			cout << "\n\tȸ���� ID �Ǵ� Password �� ��ġ���� �ʽ��ϴ�." << endl;
			cout << "\t"; system("pause");
			return 0;
		}
	}


	return 1;

}

// Display command on screen and get a input from keyboard.

int Server::UpdateMemberScreen()
{
	int command;
	cout << endl << endl;
	cout << "\t------- ȸ������ �����ϱ� Command ------- " << endl;
	cout << "\t   1 : ��й�ȣ ����" << endl;
	cout << "\t   2 : �̸� ����" << endl;
	cout << "\t   3 : ������� ����" << endl;
	cout << "\t   4 : ���� ����" << endl;
	cout << "\t   5 : �޴�����ȣ ����" << endl;
	cout << "\t   6 : ������ ����" << endl;
	cout << "\t   7 : �����ʻ��� ����" << endl;
	cout << "\t   8 : �̸��� ����" << endl;
	cout << "\t   0 : ������" << endl;

	cout << endl << "\t ��ɾ� �Է�--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;

	return command;
}



int Server::SerachMemberByName()
{
	Member itemName;
	itemName.SetNameFromKB();

	Member item;
	int success = 0;

	m_MemberList.ResetList();
	int searchCount = 0;
	cout << "\n\t--------------------��ȸ���--------------------" << endl;
	for (int i = 0; i < m_MemberList.GetLength(); i++)
	{
		m_MemberList.GetNextItem(item);
		if (item.GetUserName() == itemName.GetUserName())
		{
			success = m_MemberList.Display(item);
			searchCount++;
		}
		cout << endl;
	}

	if (!success)
		cout << "\n\t" << itemName.GetUserName() << "�� ���Ե��� ���� ȸ�� �Դϴ�." << endl;
	else
		cout << "\n\t" << itemName.GetUserName() << " �̸��� ����ڰ� " << searchCount << "�� �˻��Ǿ����ϴ�." << endl;

	cout << "\n\t------------------------------------------------" << endl;
	cout << "\t"; system("pause");
	if (success)
		return 1;
	else
		return 0;
}


void Server::MakeEmpty()
{
	m_MemberList.MakeEmpty();
}

void Server::receiveMessage() {

	while (!m_pMessageQueue->IsEmpty())
	{
		ChatMsg msg;
		m_pMessageQueue->DeQueue(msg);



		//�����
		//cout << " �޼����� �޾ҽ��ϴ�!!" << endl;
		//cout << "seq : " << msg.GetSeq() << endl;
		//cout << "sender : " << msg.GetSender() << endl;
		//cout << "receiver : " << msg.GetReceiver() << endl;
		//cout << "message : " << msg.GetMessage() << endl;

		//Receiver , loginMember�� ���� ���� ��������
		Member receiver;
		Member loginMember;
		loginMember = pClient->GetUser();
		receiver.SetUserId(msg.GetReceiver());
		m_MemberList.Get(receiver);


		//ä�� ����Ʈ�� �޽��� �߰�
		ChatMsg ReceiverMsg = msg;
		ChatMsg LoginMemberMsg = msg;
		ReceiverMsg.SetSeq(receiver.GetUserChatList().GetLength() + 1);
		LoginMemberMsg.SetSeq(loginMember.GetUserChatList().GetLength() + 1);
		receiver.AddMessageTtoChatList(ReceiverMsg);
		loginMember.AddMessageTtoChatList(LoginMemberMsg);

		receiver.SetUserAlarmMessage(true);	//�޴��� �޽��� �˶� On

		//Ŭ���̾�Ʈ���� �޼��� ����
		m_pClientMessageQueue->EnQueue(msg);
		pClient->receiveMessage();

		//������ ���� ������Ʈ
		m_MemberList.Replace(receiver);
		m_MemberList.Replace(loginMember);


	}
}


void Server::SaveDB()
{
	ofstream fout;

	fout.open("database\\db.txt");
	if (!fout) {
		cout << "���� ���� ����!!";
		exit(0);
	}

	fout << m_MemberList.GetLength() << ' ';



	m_MemberList.ResetList();
	for (int i = 0; i < m_MemberList.GetLength(); i++)
	{
		Member member;
		m_MemberList.GetNextItem(member);
		//�⺻ ��� ����
		fout << member.GetUserId() << ' ';
		fout << member.GetUserPassword() << ' ';
		fout << member.GetUserName() << ' ';
		fout << member.GetUserBirthday() << ' ';
		fout << member.GetUserGender() << ' ';
		fout << member.GetUserPhone() << ' ';
		fout << member.GetUserBackground() << ' ';
		fout << member.GetUserProfile() << ' ';
		fout << member.GetUserEmail() << ' ';
		fout << member.GetUserLogin() << ' ';
		fout << member.GetUserAlarmMessage() << ' ';

		//ģ�� ����Ʈ
		fout << member.GetUserFriendList().GetLength() << ' ';
		member.GetUserFriendList().ResetList();
		for (int i = 0; i < member.GetUserFriendList().GetLength(); i++)
		{
			Friend m_Friend;
			member.GetUserFriendList().GetNextItem(m_Friend);
			fout << m_Friend.GetId() << ' ';
			fout << m_Friend.GetName() << ' ';
		}

		//��õģ�� ����Ʈ
		fout << member.GetUserRecoFriendList().GetLength() << ' ';
		member.GetUserRecoFriendList().ResetList();
		for (int i = 0; i < member.GetUserRecoFriendList().GetLength(); i++)
		{
			Friend m_Friend;
			member.GetUserRecoFriendList().GetNextItem(m_Friend);
			fout << m_Friend.GetId() << ' ';
			fout << m_Friend.GetName() << ' ';
		}

		//ģ���׷� ����Ʈ
		fout << member.GetUserFriendGroupList().GetLength() << ' ';
		member.GetUserFriendGroupList().ResetList();
		for (int i = 0; i < member.GetUserFriendGroupList().GetLength(); i++)
		{
			FriendGroup m_FriendGroup;
			member.GetUserFriendGroupList().GetNextItem(m_FriendGroup);

			fout << m_FriendGroup.GetFriendList().GetLength() << ' ';
			for (int j = 0; j < m_FriendGroup.GetFriendList().GetLength(); j++)
			{
				Friend m_Friend;
				m_FriendGroup.GetFriendList().GetNextItem(m_Friend);
				fout << m_Friend.GetId() << ' ';
				fout << m_Friend.GetName() << ' ';
			}

			fout << m_FriendGroup.GetName() << ' ';
			fout << m_FriendGroup.GetGroupImage() << ' ';	
		}

		//�޽��� ����Ʈ
		fout << member.GetUserChatList().GetLength() << endl;
		member.GetUserChatList().ResetList();
		for (int i = 0; i < member.GetUserChatList().GetLength(); i++)
		{
			ChatMsg m_ChatMsg;
			member.GetUserChatList().GetNextItem(m_ChatMsg);
			fout << m_ChatMsg.GetSeq() << endl;
			fout << m_ChatMsg.GetReceiver() << endl;
			fout << m_ChatMsg.GetSender() << endl;
			fout << m_ChatMsg.GetChatRoomName() << endl;
			fout << m_ChatMsg.GetDeleteState() << endl;
			fout << m_ChatMsg.GetChatRoomMake() << endl;
			fout << m_ChatMsg.GetMessage() << endl;
		}
	}

	fout.close();
}

void Server::LoadDB()
{
	ifstream fin;
	fin.open("database\\db.txt");
	if (!fin) {
		cout << "���� ���� ����!!";
		return;
	}

	int memberList_Length;

	fin >> memberList_Length;

	Member member;
	string id, password, name, gender, phone, background, profile, email;
	int birthday;
	bool login, alarm;

	for (int i = 0; i < memberList_Length; i++)
	{

		member.GetUserFriendList().MakeEmpty();
		member.GetUserRecoFriendList().MakeEmpty();
		member.GetUserChatList().MakeEmpty();

		fin >> id;
		fin >> password;
		fin >> name;
		fin >> birthday;
		fin >> gender;
		fin >> phone;
		fin >> background;
		fin >> profile;
		fin >> email;
		fin >> login;
		fin >> alarm;

		member.SetUserId(id);
		member.SetUserPassword(password);
		member.SetUserName(name);
		member.SetUserBirthday(birthday);
		member.SetUserGender(gender);
		member.SetUserPhone(phone);
		member.SetUserBackground(background);
		member.SetUserProfile(profile);
		member.SetUserEmail(email);
		member.SetUserLogin(login);
		member.SetUserAlarmMessage(alarm);

		//ģ�� ����Ʈ
		int friendList_Length;

		fin >> friendList_Length;
		for (int i = 0; i < friendList_Length; i++)
		{

			Friend m_Friend;
			string m_id, m_name;

			fin >> m_id;
			fin >> m_name;

			m_Friend.SetId(m_id);
			m_Friend.SetName(m_name);

			member.GetUserFriendList().Add(m_Friend);
		}

		//��õģ�� ����Ʈ
		int recofriendList_Length;

		fin >> recofriendList_Length;
		for (int i = 0; i < recofriendList_Length; i++)
		{

			Friend m_recoFriend;
			string m_Recoid, m_Reconame;

			fin >> m_Recoid;
			fin >> m_Reconame;

			m_recoFriend.SetId(m_Recoid);
			m_recoFriend.SetName(m_Reconame);

			member.GetUserRecoFriendList().Add(m_recoFriend);
		}

		//ģ���׷� ����Ʈ
		int groupFriendListLength;;

		fin >> groupFriendListLength;
		for (int i = 0; i < groupFriendListLength; i++)
		{
			int FrindListLength;
			fin >> FrindListLength;
			FriendGroup m_FriendGroup;
			string GroupName;
			string GroupImage;
			for (int j = 0; j < FrindListLength; j++)
			{
				Friend GroupFriend;
				string id, name;
				fin >> id;
				fin >> name;
				GroupFriend.SetId(id);
				GroupFriend.SetName(name);
				m_FriendGroup.GetFriendList().Add(GroupFriend);
			}
			fin >> GroupName;
			fin >> GroupImage;

			m_FriendGroup.SetName(GroupName);
			m_FriendGroup.SetGroupImage(GroupImage);


			member.GetUserFriendGroupList().Add(m_FriendGroup);
		}

		//ä�� ����Ʈ
		int chatList_Length;
		char str[200];
		ChatMsg m_Chat;
		int seq;
		string receiver;
		string sender;
		string ChatRoomName;
		bool DeleteState;
		bool ChatRoomMake;
		string message;
		fin >> chatList_Length;
		//cout << "�����" << chatList_Length << endl;
		for (int i = 0; i < chatList_Length; i++)
		{
			//cout << "�����" << endl;

			string temp;
			fin >> seq;
			fin >> receiver;
			fin >> sender;
			fin >> ChatRoomName;
			fin >> DeleteState;
			fin >> ChatRoomMake;
			getline(fin, message);
			getline(fin, message);
			//message.push_back('\n');
			//fin >> message;

			//fin.clear();
			//message = str;

			m_Chat.SetSeq(seq);
			m_Chat.SetReceiver(receiver);
			m_Chat.SetSender(sender);
			m_Chat.SetChatRoomName(ChatRoomName);
			m_Chat.SetDeleteState(DeleteState);
			m_Chat.SetChatRoomMake(ChatRoomMake);
			m_Chat.SetMessage(message);
			member.GetUserChatList().Add(m_Chat);
		}
		m_MemberList.Add(member);

		//Ŭ���̾�Ʈ ����Ʈ�� Ŭ���̾�Ʈ Load
		ClientType client;
		client.SetId(member.GetUserId());
		client.SetName(member.GetUserName());
		client.SetMsgList(member.GetUserChatList());
		client.SetFriendList(member.GetUserFriendList());
		client.SetFriendGroupList(member.GetUserFriendGroupList());
		pClient->GetClientList().Add(client);

	}

	pClient->loadDB();

	fin.close();
}

void Server::SetTextColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void Server::receiveChatRoomMsg()
{
	while (!m_pMessageQueue->IsEmpty())
	{
		ChatMsg msg;
		m_pMessageQueue->DeQueue(msg);

		if (msg.GetChatRoomMake())	//ä�ù� ���� �޼���
		{

			//cout << "�޼��� ������..." << endl;
			//system("pause");

			/*cout << "seq : " << msg.GetSeq() << endl;
			cout << "sender : " << msg.GetSender() << endl;
			cout << "receiver : " << msg.GetReceiver() << endl;
			cout << "ChatRoomName : " << msg.GetChatRoomName() << endl;
			cout << "message : " << msg.GetMessage() << endl;
			cout << "ChatRoomMake : " << msg.GetChatRoomMake() << endl;

			system("pause");*/

			//������ �޼��� ���� �۾�
			Member Receiver;
			Receiver.SetUserId(msg.GetReceiver());
			m_MemberList.Get(Receiver);
			msg.SetSeq((Receiver.GetUserChatList().GetLength() + 1));

			Receiver.AddMessageTtoChatList(msg);

			m_pClientMessageQueue->EnQueue(msg);	//Ŭ���̾�Ʈ���� ���� �޼��� ������
			pClient->receiveMessage();

			m_MemberList.Replace(Receiver);


		}
		else // ä�ù� �޼��� ����
		{
			//cout << "�޼��� ������...(ä�ù� �޼���)" << endl;
			//system("pause");

			//������ �޼��� ���� �۾�
			Member Receiver;
			Receiver.SetUserId(msg.GetReceiver());
			m_MemberList.Get(Receiver);
			msg.SetSeq((Receiver.GetUserChatList().GetLength() + 1));

			Receiver.AddMessageTtoChatList(msg);

			m_pClientMessageQueue->EnQueue(msg);	//Ŭ���̾�Ʈ���� ���� �޼��� ������
			pClient->receiveMessage();

			Receiver.SetUserAlarmMessage(true);

			m_MemberList.Replace(Receiver);
		}
	}
}