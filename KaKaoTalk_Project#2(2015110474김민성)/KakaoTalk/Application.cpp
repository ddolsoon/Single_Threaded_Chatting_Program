#include "Application.h"
#include "Server.h"


// Program driver.
void Application::Run()
{
	m_Server.LoadDB();

	while (1)
	{
		m_Command = MainScreen();
		if (m_Server.IsRunning())
		{
			switch (m_Command)
			{
			case 1:	//  카카오톡 로그인
				m_Server.MemberLogIn();
				break;
			case 2:	// 회원ID를 입력받아 회원정보를 검색하여 화면 출력
				m_Server.SearchMemberById();
				break;
			case 3:	// 회원이름을 입력받아 회원정보를 검색하여 화면 출력 (동일 이름 모두)
				m_Server.SerachMemberByName();
				break;
			case 4:	// 카카오톡 회원가입
				m_Server.AddNewMember();
				break;
			//case 9: //디버깅 (메세지 보내기)
			//	m_Client.sendMessage();	//디버깅
			//	break;
			case 0:
				m_Server.SaveDB();
				return;
			}
		}
		else if(m_Client.IsRunning())
		{

			switch (m_Command)
			{
			case 1:	// 회원ID를 입력받아 회원정보를 검색하여 화면 출력
				m_Server.SearchMemberById();
				break;
			case 2: // 회원이름을 입력받아 회원정보를 검색하여 화면 출력 (동일 이름 모두)
				m_Server.SerachMemberByName();
				break;
			case 3:	// 회원정보 수정하기
				m_Server.UpdateMember();
				break;
			case 4:	// 카카오톡 친구 관리
				m_Client.KakaoFriendRun();
				break;
			case 5:	// 카카오톡 채팅 관리
				m_Client.KakaoChatRun();
				break;
			case 6:	// 카카오톡 프로필 사진조회
				m_Client.PrintProfileImage();
				break; 
			case 7:	// 카카오톡 회원 탈퇴
				m_Server.DeleteMember();
				break;
			case 8: //카카오톡 친구그룹 관리
				m_Client.KakaoFriendGroupRun();
				break;
			case 0:	// 멤버 Logout
				m_Server.MemberLogOut();
				break;
			}

		}
	}
}

int Application::MainScreen()
{
	int command;

	if (m_Server.IsRunning())
	{
		system("cls");
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
		SetTextColor(14, 1);	//노란색
		cout << endl;
		cout << "\t\t    카카오톡 채팅프로그램" << endl;
		SetTextColor(12, 1);
		cout << "\t\t\t Verison 2.0" << endl;
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
		SetTextColor(13, 1);	//분홍색
		cout << "\t   1 : 로그인" << endl;
		cout << "\t   2 : 회원 ID 검색" << endl;
		cout << "\t   3 : 회원 이름 검색" << endl;
		cout << "\t   4 : 회원가입" << endl;
		//cout << "\t   9 : 디버깅 메시지보내기 " << endl; //디버깅
		cout << "\t   0 : 나가기" << endl;
	}
	else if (m_Client.IsRunning())
	{
		system("cls");
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE		
		cout << endl;
		SetTextColor(14, 1);	//노란색
		cout << "\t    ID : " << m_Client.GetUser().GetUserId() << "님 카카오톡 채팅 프로그램 (로그인)" << endl;
		cout << endl;
		SetTextColor(10, 1);	//초록색
		LINE
		SetTextColor(14, 1);	//노란색
		m_Client.GetUser().DisplayRecordOnScreen();
		SetTextColor(10, 1);	//초록색
		LINE
		SetTextColor(13, 1);	//분홍색

		cout << "\t   1 : 회원 ID 검색" << endl;
		cout << "\t   2 : 회원 이름 검색" << endl;
		cout << "\t   3 : 회원 정보 수정하기" << endl;
		cout << "\t   4 : 카카오톡 친구 관리" << endl;
		cout << "\t   5 : 카카오톡 채팅 관리" << endl;
		cout << "\t   6 : 카카오톡 프로필 사진조회" << endl;
		cout << "\t   7 : 회원 탈퇴하기" << endl;
		cout << "\t   8 : 카카오톡 친구그룹 관리" << endl;
		cout << "\t   0 : 로그아웃" << endl;
	}

	SetTextColor(10, 1);
	cout << endl << "\t 명령어 입력--> ";
	cin >> command;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << endl;


	return command;
}

void Application::SetTextColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
