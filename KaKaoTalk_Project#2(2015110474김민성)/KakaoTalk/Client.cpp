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

	cout << "\n\t검색 하려는 친구ID를 입력하세요 : ";
	cin >> id;
	friend_ID.SetId(id);
	Mfriend_ID.SetUserId(id);

	if (m_User.GetUserFriendList().Get(friend_ID) == 0)
	{
		cout << "\n\t친구리스트에 등록되지 않은 ID 입니다.." << endl;
		m_User.DisplayFriendListOnScreen();
		cout << '\t';  system("pause");

		return 0;
	}
	cout << "\n\t친구 조회 성공!" << endl;

	pServer->GetMemberList().Get(Mfriend_ID);
	Mfriend_ID.DisplayRecordOnScreen();

	return 1;
}

int Client::DeleteKakaoFriend()
{
	string id;
	Friend friend_ID;

	cout << "\n\t삭제 하려는 친구ID를 입력하세요 : ";
	cin >> id;
	friend_ID.SetId(id);

	if (m_User.GetUserFriendList().Delete(friend_ID) == 0)
	{
		cout << "\n\t친구리스트에 등록되지 않은 ID 입니다." << endl;
		cout << '\t' << system("pause");
		return 0;
	}

	cout << "\n\t친구삭제 완료!" << endl;
	m_User.DisplayFriendListOnScreen();

	cout << '\t' << system("pause");

	return 1;
}


int Client::AddKakaoFriend()
{

	string id;
	Friend friend_ID;
	Member Mfriend_ID;

	cout << "\n\t추가하려는 친구ID를 입력하세요 : ";
	cin >> id;
	friend_ID.SetId(id);
	Mfriend_ID.SetUserId(id);

	/**
	예외처리
	case 1 : 이미 친구 추가되있는지 ID 처리
	case 2 : 존재하지 않는 ID 처리
	case 3 : 자기자신은 친구추가 불가능
	*/
	if (m_User.GetUserFriendList().Get(friend_ID) == 1) {
		cout << "\n\t이미 등록된 친구입니다." << endl;
		cout << '\t'; system("pause");
		return 0;
	}
	else if (pServer->GetMemberList().Get(Mfriend_ID) == 0) {
		cout << "\n\t존재하지 않는 ID 입니다." << endl;
		cout << '\t'; system("pause");
		return 0;
	}
	else if (m_User.GetUserId() == id) {
		cout << "\n\t자기자신은 친구로 등록할수 없습니다." << endl;
		cout << '\t'; system("pause");
		return 0;
	}
	else {
		friend_ID.SetName(Mfriend_ID.GetUserName());
		cout << "\n\t친구등록에 성공하였습니다." << endl;
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
		cout << "\n\t1:1 채팅할 친구 입력 (0 : 나가기) >>";
		cin >> receiver;
		if (receiver == "0")
			return;

		Friend friend_recevier;
		friend_recevier.SetId(receiver);
		if (m_User.GetUserFriendList().Get(friend_recevier) == 1)
			break;
		else
		{
			cout << "\n\t친구의 ID가 잘못 입력되었습니다." << endl;
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
		cout << "\n\t보낼 메시지 입력(1 : 삭제 , 0 : 취소) >> ";
		cin.getline(message, 200, '\n');
		string sendMessage = message;
		if (sendMessage == "0")
			return;
		if (sendMessage == "1") {
			int seq;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "\n\t삭제할 메시지 번호 입력(0 : 취소) >> ";
			cin >> seq;
			if (seq == 0) {
				continue;
			}
			ChatMsg msg;
			msg.SetSeq(seq);
			if (m_User.GetUserChatList().Get(msg) == 1) {
				msg.SetDeleteState(true);
				m_User.GetUserChatList().Replace(msg);
				cout << "\n\t메시지 삭제에 성공하였습니다." << endl;
				cout << '\t'; system("pause");
				return;
			}
			else {
				cout << "\n\t메시지 번호가 존재하지않습니다." << endl;
				cout << '\t'; system("pause");
				return;
			}

		}


		msg.SetMessage(sendMessage);
		msg.SetReceiver(receiver);
		msg.SetDeleteState(false);

		m_pMessageQueue->EnQueue(msg);	//메세지큐 enqueue
		pServer->receiveMessage();		//서버가 메세지 꺼내기

		//로그인 유저 정보 갱신
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
	handle = (long)_findfirst(".\\images\\*.*", &fd);  //현재 폴더 내 모든 파일을 찾는다.


	while (result != -1)
	{
		if (fd.name == m_User.GetUserProfile())	//image 폴더 내에 이미지가 존재한다면,
		{
			string image = "mspaint.exe images\\";
			image += m_User.GetUserProfile();
			system(image.c_str());	//그림판을 통해서, 배경사진 출력
			break;
		}

		result = _findnext(handle, &fd);
	}

	_findclose(handle);

	if (result == -1)	// image 파일에 해당 이미지 가없다면,
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
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(14, 1);//노란색
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(13, 1);	//분홍색

	cout << "\t   1 : 친구 추가" << endl;
	cout << "\t   2 : 친구 검색" << endl;
	cout << "\t   3 : 친구 목록" << endl;
	cout << "\t   4 : 친구 삭제" << endl;
	cout << "\t   5 : 추천친구 조회" << endl;
	cout << "\t   0 : 나가기" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t 명령어 입력--> ";
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
		case 1:	// 친구 추가
			AddKakaoFriend();
			break;
		case 2:	// 친구 검색
			SearchKakaoFriend();
			break;
		case 3:	// 친구 목록
			DisplayKakaoFriend();
			break;
		case 4:	// 친구 삭제
			DeleteKakaoFriend();
			break;
		case 5:	// 추천친구 조회
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
	cout << "\n\t--------------------추천하는 친구--------------------" << endl;
	for (int i = 0; i < m_User.GetUserRecoFriendList().GetLength(); i++)
	{
		m_User.GetUserRecoFriendList().GetNextItem(item);
		searchCount++;
		cout << "\n\t" << searchCount << ". " << item.GetId() << "(" << item.GetName() << ")" << endl;
	}

	if (searchCount == 0)
	{
		cout << "\n\t추천할 친구가 없습니다." << endl;
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
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(14, 1);	//노란색
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(13, 1);	//분홍색

	cout << "\t   1 : 1:1 채팅하기" << endl;
	cout << "\t   2 : 단체 채팅하기" << endl;
	cout << "\t   0 : 나가기" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t 명령어 입력--> ";
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
		case 1:	// 1:1채팅하기
			DisplayChattingRoomList();
			break;
		case 2: // 단체 채팅하기 
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

		//디버깅
		//cout << " 클라이언트를 받았습니다!!" << endl;
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

		//cout << "클라이언트 삽입 성공" << endl;
		//system("pause");

	}
}

void Client::receiveMessage()
{
	while (!m_pClientMessageQueue->IsEmpty())
	{
		ChatMsg msg;
		m_pClientMessageQueue->DeQueue(msg);

		if (msg.GetChatRoomMake())	//채팅방 생성 메세지
		{


			ClientType receiver;
			receiver.SetId(msg.GetReceiver());
			m_ClientList.Get(receiver);

			receiver.GetMsgList().Add(msg);

			if (msg.GetReceiver() == msg.GetSender()) // 채팅방 생성일때,
			{
				//cout << "채팅방이 생성되었습니다." << endl;
				ChatRoom room;
				room.SetName(msg.GetChatRoomName());

				receiver.GetChatRoomList().Add(room);

				//system("pause");

			}
			else	// 채팅방 초대대상 추가,
			{
				//cout << msg.GetSender() << "친구가 추가되었습니다." << endl;
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


			m_ClientList.Replace(receiver); //업데이트




		}
		else if (msg.GetChatRoomName() != "-1") //채팅방으로 부터 온 메세지
		{
			//cout << "채팅방으로부터 메세지 받음" << endl;
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
		else // 개인메세지
		{

			//디버깅
			//cout << " 메세지를 받았습니다!!" << endl;
			//cout << "seq : " << msg.GetSeq() << endl;
			//cout << "sender : " << msg.GetSender() << endl;
			//cout << "receiver : " << msg.GetReceiver() << endl;
			//cout << "message : " << msg.GetMessage() << endl;

			//Receiver , loginMember에 대한 정보 가져오기
			ClientType receiver;
			ClientType loginMember;

			Member m_loginMember;
			m_loginMember = GetUser();

			loginMember.SetId(m_loginMember.GetUserId());
			loginMember.SetName(m_loginMember.GetUserName());
			loginMember.SetMsgList(m_loginMember.GetUserChatList());
			receiver.SetId(msg.GetReceiver());
			m_ClientList.Get(receiver);


			//채팅 리스트에 메시지 추가
			ChatMsg ReceiverMsg = msg;
			ChatMsg LoginMemberMsg = msg;
			ReceiverMsg.SetSeq(receiver.GetMsgList().GetLength() + 1);
			LoginMemberMsg.SetSeq(loginMember.GetMsgList().GetLength() + 1);
			receiver.GetMsgList().Add(ReceiverMsg);
			loginMember.GetMsgList().Add(LoginMemberMsg);

			//클라이언트 리스트에 이를 업데이트
			m_ClientList.Replace(receiver);
			m_ClientList.Replace(loginMember);


			//클라이언트리스트가 잘 업데이트 되어있는지 디버깅
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
		case 1:	// 단톡방 생성
			createTeamChatRoom();
			break;
		case 2: // 단톡방 목록
			displayTeamChatRoom();
			break;
		case 3: // 카카오톡 검색기능
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
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(14, 1);	//노란색
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(13, 1);	//분홍색

	cout << "\t   1 : 단톡방 생성" << endl;
	cout << "\t   2 : 단톡방 목록" << endl;
	cout << "\t   3 : 카카오톡 검색기능" << endl;
	cout << "\t   0 : 나가기" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t 명령어 입력--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;


	return command;

}

/**
*	@brief	카카오톡 채팅방을 생성한다.
*	@pre	none.
*	@post	카카오톡 단체 채팅방이 생성 되어진다.
*	@param	none.
*/
void Client::createTeamChatRoom()
{

	string ChatRoomName;

	Member m_loginMember;
	m_loginMember = GetUser();



	cout << "\t생성할 단톡방 이름 : ";
	cin >> ChatRoomName;

	ChatMsg ChatRoomMsg;	//특수 메세지 생성(단톡방 생성 메세지)
	ChatRoomMsg.SetSeq(m_loginMember.GetUserChatList().GetLength() + 1);		//메세지 번호
	ChatRoomMsg.SetSender(m_loginMember.GetUserId());							//보낸 사람
	ChatRoomMsg.SetReceiver(m_loginMember.GetUserId());							//받는 사람
	ChatRoomMsg.SetChatRoomName(ChatRoomName);									//채팅방 제목
	ChatRoomMsg.SetDeleteState(false);											//메세지 삭제 State
	ChatRoomMsg.SetChatRoomMake(true);											//채팅방 생성 State



	string FriendName[100];
	int FriendNameLength = 0;

	Friend FriendSearch;

	while (true)
	{

		cout << "\t초대할 친구 이름(0. 나가기, 1.채팅방 생성) : ";
		cin >> FriendName[FriendNameLength];
		if (FriendName[FriendNameLength] == "0")
			return;
		else if (FriendName[FriendNameLength] == "1")
			break;

		//예외 처리
		FriendSearch.SetId(FriendName[FriendNameLength]);
		if (!m_loginMember.GetUserFriendList().Get(FriendSearch)) {
			cout << "\t친구가 존재하지 않습니다." << endl;
			continue;
		}


		FriendNameLength++;
	}

	//자신의 채팅방 생성
	m_pMessageQueue->EnQueue(ChatRoomMsg);	//메세지큐 enqueue(채팅방 생성 메세지 전송)
	pServer->receiveChatRoomMsg();

	//친구들의 채팅방도 생성
	for (int i = 0; i < FriendNameLength; i++)
	{
		ChatRoomMsg.SetSender(FriendName[i]);
		ChatRoomMsg.SetReceiver(FriendName[i]);	//받는 사람(친구로 설정)
		m_pMessageQueue->EnQueue(ChatRoomMsg);	//메세지큐 enqueue(채팅방 생성 메세지 전송)
	}
	pServer->receiveChatRoomMsg();

	FriendName[FriendNameLength] = m_loginMember.GetUserId();
	FriendNameLength++;

	//채팅방 목록에 친구추가
	for (int i = 0; i < FriendNameLength; i++)
	{
		ChatRoomMsg.SetReceiver(FriendName[i]);	//받는 사람
		for (int j = 0; j < FriendNameLength; j++)
		{
			if (j == i)
				continue;
			else
				ChatRoomMsg.SetSender(FriendName[j]);

			m_pMessageQueue->EnQueue(ChatRoomMsg);	//메세지큐 enqueue(채팅방 생성 메세지 전송)
		}
	}
	pServer->receiveChatRoomMsg();

}

/**
*	@brief	카카오톡 단체 채팅방 목록을 출력한다.
*	@pre	none.
*	@post	카카오톡 단체 채팅방 목록이 출력 되어진다.
*	@param	none.
*/
void Client::displayTeamChatRoom()
{
	ClientType loginClient;

	loginClient.SetId(m_User.GetUserId());
	m_ClientList.Get(loginClient);


	int RoomsearchCount = 0;

	cout << "\n\t--------------------채팅방 목록--------------------" << endl;
	loginClient.GetChatRoomList().ResetList();
	for (int i = 0; i < loginClient.GetChatRoomList().GetLength(); i++)
	{
		ChatRoom item;
		loginClient.GetChatRoomList().GetNextItem(item);
		RoomsearchCount++;
		cout << "\n\t" << RoomsearchCount << ". " << item.GetName() << "(";

		//멤버 출력
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
		cout << "\n\t생성된 채팅방이 없습니다." << endl;
	}

	cout << "\n\t------------------------------------------------" << endl;

	string EnterChatRoom;
	cout << "\n\t입장할 채팅방 이름 입력 (0. 나가기) :";
	cin >> EnterChatRoom;
	if (EnterChatRoom == "0")
		return;

	ChatRoom room;
	room.SetName(EnterChatRoom);

	//채팅방 가져오기
	int success = loginClient.GetChatRoomList().Get(room);
	if (success == 0) {
		cout << "\t존재하지 않는 채팅방입니다.." << endl;
		system("pause");
		return;
	}



	//채팅 입력
	while (1)
	{
		system("cls");

		ClientType loginClient;

		loginClient.SetId(m_User.GetUserId());
		m_ClientList.Get(loginClient);

		ChatRoom room;
		room.SetName(EnterChatRoom);

		//채팅방 가져오기
		int success = loginClient.GetChatRoomList().Get(room);
		if (success == 0) {
			cout << "\t존재하지 않는 채팅방입니다.." << endl;
			system("pause");
			return;
		}

		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
			cout << endl;
		SetTextColor(14, 1);	//노란색
		cout << "\t    ID : " << loginClient.GetName() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
		cout << "\t    채팅방 이름 : " << room.GetName() << endl;
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
			SetTextColor(14, 1);	//노란색

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
			cout << "\n\t대화가 존재하지 않습니다.." << endl;

		}

		SetTextColor(10, 1);
		LINE


			//system("pause");

		char message[200];
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "\n\t(0:취소, 1:삭제, 2:복사, 3:검색, 4:붙여넣기, 5:이미지열기) " << endl;
		cout << "\n\t보낼 메시지 입력 >> ";

		cin.getline(message, 200, '\n');
		string sendMessage = message;
		if (sendMessage == "0")
			return;
		if (sendMessage == "1") {	//메세지 삭제 처리
			int seq;
			//cin.clear();
			//cin.ignore(INT_MAX, '\n');
			cout << "\n\t삭제할 메시지 번호 입력(0 : 취소) >> ";
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

				cout << "\n\t메시지 삭제에 성공하였습니다." << endl;
				cout << '\t'; system("pause");
				continue;
			}
			else {
				cout << "\n\t메시지 번호가 존재하지않습니다." << endl;
				cout << '\t'; system("pause");
				continue;
			}

		}
		else if (sendMessage == "2") {	//메세지 복사 처리
			int seq;
			cout << "\n\t복사할 메시지 번호 입력(0 : 취소) >> ";
			cin >> seq;
			if (seq == 0) {
				continue;
			}
			ChatMsg msg;
			msg.SetSeq(seq);
			if (room.GetMsgList().Get(msg) == 1) {

				m_ClipBoard = msg.GetMessage();
				cout << "\n\t메세지 복사에 성공하였습니다." << endl;
				cout << '\t'; system("pause");
				continue;
			}
			else {
				cout << "\n\t메시지 번호가 존재하지않습니다." << endl;
				cout << '\t'; system("pause");
				continue;
			}

		}
		else if (sendMessage == "3") {	//메세지 검색 처리
			string SearchContent;
			cout << "\n\t검색할 메시지 내용 입력(0 : 취소) >> ";
			cin >> SearchContent;
			if (SearchContent == "0") {
				continue;
			}

			int searchCount = 0;

			cout << "\n\t--------------------메세지 검색결과--------------------" << endl;
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
				cout << "\n\t검색된 메세지가 존재하지 않습니다." << endl;
			}

			cout << "\n\t-------------------------------------------------------" << endl;
			cout << '\t'; system("pause");
			continue;

		}
		else if (sendMessage == "4") { //메세지 붙여넣기 처리
			if (m_ClipBoard == "") {
				cout << "\n\t클립보드에 내용이 없습니다." << endl;
				cout << '\t'; system("pause");
				continue;

			}
			sendMessage = m_ClipBoard;

		}
		else if (sendMessage == "5") { //이미지열기 처리
			int seq;
			cout << "\n\t이미지를 열어볼 메시지 번호 입력(0 : 취소) >> ";
			cin >> seq;
			if (seq == 0) {
				continue;
			}
			ChatMsg msg;
			msg.SetSeq(seq);
			if (room.GetMsgList().Get(msg) == 1) {

				DisplayImage(msg.GetMessage());
				cout << "\n\t이미지 열기에 성공하였습니다." << endl;
				cout << '\t'; system("pause");
				continue;
			}
			else {
				cout << "\n\t메시지 번호가 존재하지않습니다." << endl;
				cout << '\t'; system("pause");
				continue;
			}
		}

		//메세지 전송 처리
		ChatMsg TeamMsg;
		TeamMsg.SetMessage(sendMessage);
		TeamMsg.SetSender(loginClient.GetId());
		TeamMsg.SetChatRoomName(EnterChatRoom);
		TeamMsg.SetReceiver(loginClient.GetId());

		m_pMessageQueue->EnQueue(TeamMsg);	//메세지큐 enqueue
		pServer->receiveChatRoomMsg();		//서버가 메세지 꺼내기

		////로그인 유저 정보 갱신								
		Member loginMember;
		loginMember.SetUserId(m_User.GetUserId());
		pServer->GetMemberList().Get(loginMember);
		SetUser(loginMember);

		room.GetMemberList().ResetList();
		//채팅방 멤버 모두에게 메세지 전송
		for (int i = 0; i < room.GetMemberList().GetLength(); i++)
		{
			string m_RoomMember;
			room.GetMemberList().GetNextItem(m_RoomMember);

			TeamMsg.SetReceiver(m_RoomMember);

			m_pMessageQueue->EnQueue(TeamMsg);	//메세지큐 enqueue
			pServer->receiveChatRoomMsg();		//서버가 메세지 꺼내기

			////로그인 유저 정보 갱신								
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

				if (msg.GetReceiver() == msg.GetSender()) // 채팅방 생성일때,
				{
					//cout << "채팅방이 생성되었습니다." << endl;
					ChatRoom room;
					room.SetName(msg.GetChatRoomName());

					client.GetChatRoomList().Add(room);

					//system("pause");

				}
				else	// 채팅방 초대대상 추가,
				{
					//cout << msg.GetSender() << "친구가 추가되었습니다." << endl;
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

			m_ClientList.Replace(client); //업데이트
		}

	}
}

void Client::DisplayImage(string name)
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = (long)_findfirst(".\\images\\*.*", &fd);  //현재 폴더 내 모든 파일을 찾는다.


	while (result != -1)
	{
		if (fd.name == name)	//image 폴더 내에 이미지가 존재한다면,
		{
			string image = "mspaint.exe images\\";
			image += name;
			system(image.c_str());	//그림판을 통해서, 배경사진 출력
			break;
		}

		result = _findnext(handle, &fd);
	}

	_findclose(handle);

	if (result == -1)	// image 파일에 해당 이미지 가없다면,
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

	cout << "\n\t채팅방 이름,참여자 검색 >> ";
	cin >> searchName;

	ClientType LoginClient;
	LoginClient.SetId(m_User.GetUserId());
	m_ClientList.Get(LoginClient);

	LoginClient.GetChatRoomList().ResetList();

	int RoomsearchCount = 0;
	cout << "\n\t--------------------카카오톡 검색결과--------------------" << endl;

	//채팅방 검색
	for (int i = 0; i < LoginClient.GetChatRoomList().GetLength(); i++)
	{
		LoginClient.GetChatRoomList().GetNextItem(searchChatRoom);

		if (searchChatRoom.GetName() == searchName)	//검색된 채팅방이름과 일치한다면,
		{
			RoomsearchCount++;
			cout << "\n\t" << RoomsearchCount << ". " << searchChatRoom.GetName() << "(";

			//멤버 출력
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

		//채팅방 내 멤버 검색
		searchChatRoom.GetMemberList().ResetList();
		for (int j = 0; j < searchChatRoom.GetMemberList().GetLength(); j++)
		{
			searchChatRoom.GetMemberList().GetNextItem(searchChatMember);

			if (searchChatMember == searchName) { //검색된 멤버이름과 일치한다면,

				RoomsearchCount++;
				cout << "\n\t" << RoomsearchCount << ". " << searchChatRoom.GetName() << "(";

				//멤버 출력
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
		cout << "\n\t검색된 채팅방이 존재하지 않습니다." << endl;
	}

	cout << "\n\t-------------------------------------------------------" << endl;
	cout << '\t'; system("pause");


}

/**
*	@brief	입력받은 명령어로부터, 카카오톡 친구그룹 기능관련 함수 호출
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
		case 1:	// 그룹 생성
			createFriendGroup();
			break;
		case 2: // 그룹 목록
			displayFriendGroup();
			break;
		case 3: // 그룹 삭제
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
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(14, 1);	//노란색
	cout << endl;
	cout << "\t    ID : " << m_User.GetUserId() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
	cout << endl;
	SetTextColor(10, 1);	//초록색
	LINE
		SetTextColor(13, 1);	//분홍색

	cout << "\t   1 : 친구그룹 생성" << endl;
	cout << "\t   2 : 친구그룹 목록" << endl;
	cout << "\t   3 : 친구그룹 해제" << endl;
	cout << "\t   0 : 나가기" << endl;

	SetTextColor(10, 1);
	cout << endl << "\t 명령어 입력--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;


	return command;

}

/**
*	@brief	카카오톡 친구그룹을 생성한다.
*	@pre	none.
*	@post	카카오톡 친구그룹이 생성 되어진다.
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


	cout << "\t생성할 그룹 이름 : ";
	cin >> GroupName;
	group.SetName(GroupName);
	cout << "\t그룹 이미지 입력 : ";
	cin >> GroupImage;
	group.SetGroupImage(GroupImage);

	m_loginMember.GetUserFriendGroupList().Add(group);
	loginClient.GetFriendGroupList().Add(group);

	pServer->GetMemberList().Replace(m_loginMember);
	m_ClientList.Replace(loginClient);
	m_User = m_loginMember;

	cout << "\t그룹 생성 완료" << endl;

	cout << '\t'; system("pause");


}

/**
*	@brief	카카오톡 친구 그룹 목록을 출력한다.
*	@pre	none.
*	@post	카카오톡 친구 그룹 목록이 출력 되어진다.
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

	cout << "\n\t--------------------그룹 목록--------------------" << endl;
	loginClient.GetFriendGroupList().ResetList();
	for (int i = 0; i < loginClient.GetFriendGroupList().GetLength(); i++)
	{
		FriendGroup item;
		loginClient.GetFriendGroupList().GetNextItem(item);
		GroupsearchCount++;
		cout << "\n\t" << GroupsearchCount << ". " << item.GetName() << endl;

		//멤버 출력
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
				cout << "\n\t\t그룹에 친구가 없습니다." << endl;
			}
		}

	}

	if (GroupsearchCount == 0)
	{
		cout << "\n\t생성된 그룹이 없습니다." << endl;
	}

	cout << "\n\t------------------------------------------------" << endl;

	string EnterFriendGroup;
	cout << "\n\t친구 추가할 그룹 이름 입력 (0. 나가기) :";
	cin >> EnterFriendGroup;
	if (EnterFriendGroup == "0")
		return;

	FriendGroup friendGroup;
	friendGroup.SetName(EnterFriendGroup);

	//친구그룹 가져오기
	int success = loginClient.GetFriendGroupList().Get(friendGroup);
	if (success == 0) {
		cout << "\t존재하지 않는 그룹입니다." << endl;
		system("pause");
		return;
	}

	//채팅 입력
	while (1)
	{
		system("cls");

		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
			SetTextColor(14, 1);	//노란색
		cout << endl;
		cout << "\t    ID : " << m_User.GetUserId() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
		SetTextColor(13, 1);	//분홍색

		SetTextColor(10, 1);
		LINE


		cout << "\n\t--------------------그룹멤버 목록--------------------" << endl;

		//멤버 출력
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
				cout << "\n\t\t그룹에 친구가 없습니다." << endl;
			}
		}

		cout << "\n\t------------------------------------------------------" << endl;


		cin.clear();
		cin.ignore(INT_MAX, '\n');
		string AddFriendName;
		cout << "\n\t추가할 친구 이름 입력(0. 나가기, 1.그룹사진 조회) >> ";
		cin >> AddFriendName;
		if (AddFriendName == "0")
			return;
		if (AddFriendName == "1") {	//그룹사진 조회
			DisplayImage(friendGroup.GetGroupImage());

		}
		else { //그룹에 친구추가
			Friend AddFriend;
			AddFriend.SetId(AddFriendName);
			int success = loginClient.GetFriendList().Get(AddFriend);
			if (success == 1) {

				int check = friendGroup.GetFriendList().Get(AddFriend);
				if (check == 1) {
					cout << "\n\t이미 등록된 친구입니다." << endl;
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

					cout << "\n\t그룹에 친구가 등록되었습니다." << endl;
					cout << '\t'; system("pause");
					continue;
				}

			}
			else {
				cout << "\n\t존재하지 않는친구입니다." << endl;
				cout << '\t'; system("pause");
				continue;
			}
		}

	}

}

/**
*	@brief	카카오톡 친구그룹이 삭제된다.
*	@pre	none.
*	@post	입력한 친구그룹이 삭제되어진다.
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

	cout << "\n\t--------------------그룹 목록--------------------" << endl;
	loginClient.GetFriendGroupList().ResetList();
	for (int i = 0; i < loginClient.GetFriendGroupList().GetLength(); i++)
	{
		FriendGroup item;
		loginClient.GetFriendGroupList().GetNextItem(item);
		GroupsearchCount++;
		cout << "\n\t" << GroupsearchCount << ". " << item.GetName() << endl;

		//멤버 출력
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
				cout << "\n\t\t그룹에 친구가 없습니다." << endl;
			}
		}

	}

	if (GroupsearchCount == 0)
	{
		cout << "\n\t생성된 그룹이 없습니다." << endl;
	}

	cout << "\n\t------------------------------------------------" << endl;

	string EnterFriendGroup;
	cout << "\n\t해제 그룹 이름 입력 (0. 나가기) :";
	cin >> EnterFriendGroup;
	if (EnterFriendGroup == "0")
		return;

	FriendGroup friendGroup;
	friendGroup.SetName(EnterFriendGroup);

	//친구그룹 가져오기
	int success = loginClient.GetFriendGroupList().Get(friendGroup);
	if (success == 0) {
		cout << "\t존재하지 않는 그룹입니다." << endl;
		system("pause");
		return;
	}
	else { //그룹 삭제하기
		
		m_loginMember.GetUserFriendGroupList().Delete(friendGroup);
		loginClient.GetFriendGroupList().Delete(friendGroup);
		
		m_loginMember.GetUserFriendGroupList().Replace(friendGroup);
		pServer->GetMemberList().Replace(m_loginMember);
		m_ClientList.Replace(loginClient);
		m_User = m_loginMember;

		cout << "\n\t그룹이 해제 되었습니다." << endl;
		cout << '\t'; system("pause");
		
	}
}

