#include "Server.h"

// Display all records in the list on screen.
void Server::DisplayAllMembers()
{
	Member data;

	cout << "\n\t카카오톡 회원 명단" << endl;
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
			cout << "\n\t이미 존재하는 ID라서, 계정을 생성할수 없습니다." << endl;
			cout << "\t"; system("pause");

		}
		else
			break;
	}

	int success = m_MemberList.Add(item);
	if (success) {
		cout << "\n\t" + item.GetUserId() + "님의 회원가입을 축하드립니다!" << endl;
		cout << "\t"; system("pause");
	}

	//회원가입 시, 서버 -> 클라이언트 (클라이언트 정보 큐로 전달)
	ClientType sendClient;
	sendClient.SetId(item.GetUserId());
	sendClient.SetName(item.GetUserName());
	sendClient.SetMsgList(item.GetUserChatList());

	m_pClientQueue->EnQueue(sendClient);	//큐로 클라이언트 전송
	pClient->receiveClient();				//클라이언트 리스트에 클라이언트 추가

	DisplayAllMembers();

	return 1;
}

//추가된 부분
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
		cout << "\n\t" + data.GetUserId() + "의 정보를 삭제하였습니다." << endl;
	}
	else {
		cout << "\n\t" + data.GetUserId() + "는 가입되지 않은 회원 입니다." << endl;
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
		cout << "\n\t회원의 ID가 존재하지 않습니다." << endl;
		cout << "\t"; system("pause");
		return 0;
	}
	else
	{
		//Member List에서 가져온 비밀번호가 입력한 비밀번호와 일치한다면,
		if (!strcmp(itemId.GetUserPassword().c_str(), itemPW.GetUserPassword().c_str()))
		{
			cout << "\n\t정상적으로 로그인에 성공하였습니다." << endl << endl;
			if (itemId.GetUserAlarmMessage()) {
				PlaySound(TEXT("music\\alarm.wav"), NULL, SND_ASYNC);	//메시지 알람 재생
				SetTextColor(12, 1);
				cout << "\t알람 : 새로운 메시지가 도착했습니다!!" << endl;
			}
			SetTextColor(10, 1);
			cout << endl;
			cout << "\t"; system("pause");
			itemId.SetUserLogin(true);
			m_MemberList.Replace(itemId);
			m_MemberList.Display(itemId);
			m_MemberList.Get(itemId);

			if (itemId.GetUserAlarmMessage()) {	//도착한 메시지가 있다면,

				itemId.SetUserAlarmMessage(false);
			}

			pClient->SetUser(itemId);
			m_Run = false;
			pClient->SetRun(true);

		}
		else
		{
			cout << "\n\t회원의 ID 또는 Password 가 일치하지 않습니다." << endl;
			cout << "\t"; system("pause");
			return 0;
		}
	}


	return 1;
}


int Server::MemberLogOut()
{

	cout << "\n\t정상적으로 로그아웃 되었습니다." << endl << endl;
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
	cout << "\n\t--------------------조회결과--------------------" << endl;
	int success = m_MemberList.Display(item);
	
	cout << "\n\t------------------------------------------------" << endl;
	if (success) {
		m_MemberList.Get(item);
		//추천 친구로 넣기
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
		cout << "\n\t" + item.GetUserId() + "의 정보를 조회하였습니다." << endl;
		cout << "\t"; system("pause");
	}
	else {
		cout << "\n\t" + item.GetUserId() + "는 가입되지 않은 회원 입니다." << endl;
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
		cout << "\n\t회원의 ID가 존재하지 않습니다." << endl;
		cout << "\t"; system("pause");
		return 0;
	}
	else
	{
		//Member List에서 가져온 비밀번호가 입력한 비밀번호와 일치한다면,
		if (itemId.GetUserPassword() == itemPW.GetUserPassword())
		{
			bool IsRunning = true;
			int m_Command;
			while (IsRunning)
			{
				m_Command = UpdateMemberScreen();
				switch (m_Command)
				{
				case 1:	// 비밀번호 변경
					itemId.SetPasswordFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t비밀번호가 변경되었습니다." << endl;
					break;
				case 2:	// 이름 변경
					itemId.SetNameFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t이름이 변경되었습니다." << endl;
					break;
				case 3:	// 생년월일 변경
					itemId.SetBirthdayFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t생년월일이 변경되었습니다." << endl;
					break;
				case 4:	// 성별 변경
					itemId.SetGenderFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t성별이 변경되었습니다." << endl;
					break;
				case 5:	// 휴대폰번호 변경
					itemId.SetPhoneFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t휴대폰번호가 변경되었습니다." << endl;
					break;
				case 6:	// 배경사진 변경
					itemId.SetBackgroundFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t배경사진이 변경되었습니다." << endl;
					break;
				case 7: // 프로필사진 변경
					itemId.SetProfileFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t프로필사진이 변경되었습니다." << endl;
					break;
				case 8:	// 이메일 변경
					itemId.SetEmailFromKB();
					m_MemberList.Replace(itemId);
					cout << "\n\t이메일이 변경되었습니다." << endl;
					break;
				case 0:
					IsRunning = false;
					break;
				}

				cout << "\n\t--------------------변경확인--------------------" << endl;
				int success = m_MemberList.Display(itemId);
				cout << "\n\t------------------------------------------------" << endl;
				cout << "\t"; system("pause");
			}
		}
		else
		{
			cout << "\n\t회원의 ID 또는 Password 가 일치하지 않습니다." << endl;
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
	cout << "\t------- 회원정보 수정하기 Command ------- " << endl;
	cout << "\t   1 : 비밀번호 변경" << endl;
	cout << "\t   2 : 이름 변경" << endl;
	cout << "\t   3 : 생년월일 변경" << endl;
	cout << "\t   4 : 성별 변경" << endl;
	cout << "\t   5 : 휴대폰번호 변경" << endl;
	cout << "\t   6 : 배경사진 변경" << endl;
	cout << "\t   7 : 프로필사진 변경" << endl;
	cout << "\t   8 : 이메일 변경" << endl;
	cout << "\t   0 : 나가기" << endl;

	cout << endl << "\t 명령어 입력--> ";
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
	cout << "\n\t--------------------조회결과--------------------" << endl;
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
		cout << "\n\t" << itemName.GetUserName() << "는 가입되지 않은 회원 입니다." << endl;
	else
		cout << "\n\t" << itemName.GetUserName() << " 이름의 사용자가 " << searchCount << "명 검색되었습니다." << endl;

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



		//디버깅
		//cout << " 메세지를 받았습니다!!" << endl;
		//cout << "seq : " << msg.GetSeq() << endl;
		//cout << "sender : " << msg.GetSender() << endl;
		//cout << "receiver : " << msg.GetReceiver() << endl;
		//cout << "message : " << msg.GetMessage() << endl;

		//Receiver , loginMember에 대한 정보 가져오기
		Member receiver;
		Member loginMember;
		loginMember = pClient->GetUser();
		receiver.SetUserId(msg.GetReceiver());
		m_MemberList.Get(receiver);


		//채팅 리스트에 메시지 추가
		ChatMsg ReceiverMsg = msg;
		ChatMsg LoginMemberMsg = msg;
		ReceiverMsg.SetSeq(receiver.GetUserChatList().GetLength() + 1);
		LoginMemberMsg.SetSeq(loginMember.GetUserChatList().GetLength() + 1);
		receiver.AddMessageTtoChatList(ReceiverMsg);
		loginMember.AddMessageTtoChatList(LoginMemberMsg);

		receiver.SetUserAlarmMessage(true);	//받는이 메시지 알람 On

		//클라이언트에게 메세지 전송
		m_pClientMessageQueue->EnQueue(msg);
		pClient->receiveMessage();

		//서버에 내용 업데이트
		m_MemberList.Replace(receiver);
		m_MemberList.Replace(loginMember);


	}
}


void Server::SaveDB()
{
	ofstream fout;

	fout.open("database\\db.txt");
	if (!fout) {
		cout << "파일 오픈 실패!!";
		exit(0);
	}

	fout << m_MemberList.GetLength() << ' ';



	m_MemberList.ResetList();
	for (int i = 0; i < m_MemberList.GetLength(); i++)
	{
		Member member;
		m_MemberList.GetNextItem(member);
		//기본 멤버 정보
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

		//친구 리스트
		fout << member.GetUserFriendList().GetLength() << ' ';
		member.GetUserFriendList().ResetList();
		for (int i = 0; i < member.GetUserFriendList().GetLength(); i++)
		{
			Friend m_Friend;
			member.GetUserFriendList().GetNextItem(m_Friend);
			fout << m_Friend.GetId() << ' ';
			fout << m_Friend.GetName() << ' ';
		}

		//추천친구 리스트
		fout << member.GetUserRecoFriendList().GetLength() << ' ';
		member.GetUserRecoFriendList().ResetList();
		for (int i = 0; i < member.GetUserRecoFriendList().GetLength(); i++)
		{
			Friend m_Friend;
			member.GetUserRecoFriendList().GetNextItem(m_Friend);
			fout << m_Friend.GetId() << ' ';
			fout << m_Friend.GetName() << ' ';
		}

		//친구그룹 리스트
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

		//메시지 리스트
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
		cout << "파일 오픈 실패!!";
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

		//친구 리스트
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

		//추천친구 리스트
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

		//친구그룹 리스트
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

		//채팅 리스트
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
		//cout << "디버깅" << chatList_Length << endl;
		for (int i = 0; i < chatList_Length; i++)
		{
			//cout << "디버깅" << endl;

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

		//클라이언트 리스트에 클라이언트 Load
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

		if (msg.GetChatRoomMake())	//채팅방 생성 메세지
		{

			//cout << "메세지 생성됨..." << endl;
			//system("pause");

			/*cout << "seq : " << msg.GetSeq() << endl;
			cout << "sender : " << msg.GetSender() << endl;
			cout << "receiver : " << msg.GetReceiver() << endl;
			cout << "ChatRoomName : " << msg.GetChatRoomName() << endl;
			cout << "message : " << msg.GetMessage() << endl;
			cout << "ChatRoomMake : " << msg.GetChatRoomMake() << endl;

			system("pause");*/

			//서버에 메세지 저장 작업
			Member Receiver;
			Receiver.SetUserId(msg.GetReceiver());
			m_MemberList.Get(Receiver);
			msg.SetSeq((Receiver.GetUserChatList().GetLength() + 1));

			Receiver.AddMessageTtoChatList(msg);

			m_pClientMessageQueue->EnQueue(msg);	//클라이언트에게 받은 메세지 재전송
			pClient->receiveMessage();

			m_MemberList.Replace(Receiver);


		}
		else // 채팅방 메세지 전송
		{
			//cout << "메세지 생성됨...(채팅방 메세지)" << endl;
			//system("pause");

			//서버에 메세지 저장 작업
			Member Receiver;
			Receiver.SetUserId(msg.GetReceiver());
			m_MemberList.Get(Receiver);
			msg.SetSeq((Receiver.GetUserChatList().GetLength() + 1));

			Receiver.AddMessageTtoChatList(msg);

			m_pClientMessageQueue->EnQueue(msg);	//클라이언트에게 받은 메세지 재전송
			pClient->receiveMessage();

			Receiver.SetUserAlarmMessage(true);

			m_MemberList.Replace(Receiver);
		}
	}
}