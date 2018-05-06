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
			case 1:	//  īī���� �α���
				m_Server.MemberLogIn();
				break;
			case 2:	// ȸ��ID�� �Է¹޾� ȸ�������� �˻��Ͽ� ȭ�� ���
				m_Server.SearchMemberById();
				break;
			case 3:	// ȸ���̸��� �Է¹޾� ȸ�������� �˻��Ͽ� ȭ�� ��� (���� �̸� ���)
				m_Server.SerachMemberByName();
				break;
			case 4:	// īī���� ȸ������
				m_Server.AddNewMember();
				break;
			//case 9: //����� (�޼��� ������)
			//	m_Client.sendMessage();	//�����
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
			case 1:	// ȸ��ID�� �Է¹޾� ȸ�������� �˻��Ͽ� ȭ�� ���
				m_Server.SearchMemberById();
				break;
			case 2: // ȸ���̸��� �Է¹޾� ȸ�������� �˻��Ͽ� ȭ�� ��� (���� �̸� ���)
				m_Server.SerachMemberByName();
				break;
			case 3:	// ȸ������ �����ϱ�
				m_Server.UpdateMember();
				break;
			case 4:	// īī���� ģ�� ����
				m_Client.KakaoFriendRun();
				break;
			case 5:	// īī���� ä�� ����
				m_Client.KakaoChatRun();
				break;
			case 6:	// īī���� ������ ������ȸ
				m_Client.PrintProfileImage();
				break; 
			case 7:	// īī���� ȸ�� Ż��
				m_Server.DeleteMember();
				break;
			case 8: //īī���� ģ���׷� ����
				m_Client.KakaoFriendGroupRun();
				break;
			case 0:	// ��� Logout
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
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
		SetTextColor(14, 1);	//�����
		cout << endl;
		cout << "\t\t    īī���� ä�����α׷�" << endl;
		SetTextColor(12, 1);
		cout << "\t\t\t Verison 2.0" << endl;
		cout << endl;
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
		SetTextColor(13, 1);	//��ȫ��
		cout << "\t   1 : �α���" << endl;
		cout << "\t   2 : ȸ�� ID �˻�" << endl;
		cout << "\t   3 : ȸ�� �̸� �˻�" << endl;
		cout << "\t   4 : ȸ������" << endl;
		//cout << "\t   9 : ����� �޽��������� " << endl; //�����
		cout << "\t   0 : ������" << endl;
	}
	else if (m_Client.IsRunning())
	{
		system("cls");
		cout << endl;
		SetTextColor(10, 1);	//�ʷϻ�
		LINE		
		cout << endl;
		SetTextColor(14, 1);	//�����
		cout << "\t    ID : " << m_Client.GetUser().GetUserId() << "�� īī���� ä�� ���α׷� (�α���)" << endl;
		cout << endl;
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
		SetTextColor(14, 1);	//�����
		m_Client.GetUser().DisplayRecordOnScreen();
		SetTextColor(10, 1);	//�ʷϻ�
		LINE
		SetTextColor(13, 1);	//��ȫ��

		cout << "\t   1 : ȸ�� ID �˻�" << endl;
		cout << "\t   2 : ȸ�� �̸� �˻�" << endl;
		cout << "\t   3 : ȸ�� ���� �����ϱ�" << endl;
		cout << "\t   4 : īī���� ģ�� ����" << endl;
		cout << "\t   5 : īī���� ä�� ����" << endl;
		cout << "\t   6 : īī���� ������ ������ȸ" << endl;
		cout << "\t   7 : ȸ�� Ż���ϱ�" << endl;
		cout << "\t   8 : īī���� ģ���׷� ����" << endl;
		cout << "\t   0 : �α׾ƿ�" << endl;
	}

	SetTextColor(10, 1);
	cout << endl << "\t ��ɾ� �Է�--> ";
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
