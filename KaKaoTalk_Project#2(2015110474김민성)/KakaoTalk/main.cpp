#include "Application.h"

/**
*	@mainpage	������Ʈ#2 ���� ���� <br>
*				1. ��ü���� ������ Application (��Ʈ�ѷ� ����) Server(�� ����) Client(�� ����) <br>
*				2. Message List�� Ŭ���̾�Ʈ�� �ű��, Server������ Message List�� �����Ѵ�. <br>
*				(���� �𵨿����� ���� / Ŭ���̾�Ʈ ��� �޼��� ����Ʈ�� ����) <br>
*				3. �������� Ŭ���̾�Ʈ�� �����ϱ� ���� Ŭ���̾�Ʈ ť �߰� <br>
*				4. ����, �������� Ŭ���̾�Ʈ�� �����ϱ����� ���� �޼���ť �߰� <br>
*				5. ��, ť�� 3���� ť�� ���� ( ���� �޽��� ť / Ŭ���̾�Ʈ �޽��� ť / Ŭ���̾�Ʈ ť) <br>
*				6. ������ run() ���ٴ� Application class�� Controller ������ �����ϹǷ�, �α���/�α׾ƿ��� ����, <br>
*				������ Ŭ���̾�Ʈ�� m_Run State�� Ȯ���Ͽ� Server UI �� Client UI�� ������� ����Ѵ�. (IsRunning() �Լ� ���) <br>
*               7. loadDB() ������ memberList �Ӹ��ƴ϶�, ClientList�� ���� Load ��Ų��. <br>
*               8. ä�ù�(��ü ä��) ��� �߰�, ģ�� �׷� ��� �߰�, �޼��� ����/����/�˻� ��� �߰� <br>
*               9. īī����  ä�ñ�� �߰�(ä�ù�,����� �̿��� ä�ù� �˻�)
*               10. �޼��� ���� ÷�� ��� �߰�(�߰����)
*				����ȯ�� : Visual Studio 2017 <br>
*	@date	2017.12.03
*	@author	��μ�
*/

/**
*	program main function for data structures course.
*/
int main()
{
	Application app;	// Program application
	app.Run();			// run program

	return 0;
}