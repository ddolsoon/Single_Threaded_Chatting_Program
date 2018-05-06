#include "Member.h"


// Set User id from keyboard.
void Member::SetIdFromKB()
{
	cout << "\tUser ID : ";
	cin >> m_UserId;
}

// Set Uer Password from keyboard.
void Member::SetPasswordFromKB()
{
	char password[255];
	cout << "\tUser Password : ";


	char ch = ' ';
	int i = 0;
	while (ch != '\r')//EnterŰ�� �Է¹��� ������ ���ڿ��� �Է¹���(_getch ���� '\r'�� �����ν�)
	{
		ch = _getch();
		if (ch == '\b' && i >= 1) //Backspace �Է�
		{
			cout << "\b \b";	//Ŀ�� �� ��������.
			i--;
			continue;
		}
		else if (ch == '\b' && i == 0) //Backspace �Է� & �ƹ��͵� �Է� X
		{
			continue;
		}

		password[i] = ch;

		if (ch != '\r')
			cout << '*'; //��й�ȣ�� * ǥ��(���Ȼ� ��� X)

		i++;
	}
	cout << endl;


	password[i-1] = '\0';

	i = 0;
	m_UserPassword = "";
	while (password[i] != '\0') {
		m_UserPassword += password[i];
		i++;
	}
	
}


// Set User name from keyboard.
void Member::SetNameFromKB()
{
	cout << "\tUser Name : ";
	cin >> m_UserName;
}


// Set User Birthday from keyboard.
void Member::SetBirthdayFromKB()
{
	while (true)
	{
		cout << "\tUser Birthday : ";
		cin >> m_UserBirthday;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		if (m_UserBirthday >= 19000101 && m_UserBirthday <= 21000101)
			break;
		else
			cout << "\n\t�ùٸ� ��������� �ƴմϴ�.(8�ڸ��� �Է�) Ex)20100215" << endl;
	}
}

// Set User Gender from keyboard.
void Member::SetGenderFromKB()
{
	cout << "\tUser Gender : ";
	cin >> m_UserGender;
}

// Set User Phone from keyboard.
void Member::SetPhoneFromKB()
{
	cout << "\tUser Phone : ";
	cin >> m_UserPhone;
}

// Set User Background from keyboard.
void Member::SetBackgroundFromKB()
{
	cout << "\tUser Background : ";
	cin >> m_UserBackground;
}

// Set User Profile from keyboard.
void Member::SetProfileFromKB()
{
	cout << "\tUser Profile : ";
	cin >> m_UserProfile;
}

// Set User Email from keyboard.
void Member::SetEmailFromKB()
{
	cout << "\tUser Email : ";
	cin >> m_UserEmail;
}


// Set User Record from keyboard.
void Member::SetRecordFromKB()
{
	SetIdFromKB();
	SetPasswordFromKB();
	SetNameFromKB();
	SetBirthdayFromKB();
	SetGenderFromKB();
	SetPhoneFromKB();
	SetBackgroundFromKB();
	SetProfileFromKB();
	SetEmailFromKB();
}




void Member::SetTextColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}