#include "Application.h"

/**
*	@mainpage	프로젝트#2 구현 내용 <br>
*				1. 전체적인 구조는 Application (컨트롤러 역할) Server(모델 역할) Client(뷰 역할) <br>
*				2. Message List는 클라이언트로 옮기되, Server에서도 Message List는 유지한다. <br>
*				(실제 모델에서도 서버 / 클라이언트 모두 메세지 리스트를 가짐) <br>
*				3. 서버에서 클라이언트를 전송하기 위한 클라이언트 큐 추가 <br>
*				4. 또한, 서버에서 클라이언트로 전송하기위한 서버 메세지큐 추가 <br>
*				5. 즉, 큐는 3가지 큐가 존재 ( 서버 메시지 큐 / 클라이언트 메시지 큐 / 클라이언트 큐) <br>
*				6. 각각의 run() 보다는 Application class가 Controller 역할을 수행하므로, 로그인/로그아웃에 따라서, <br>
*				서버와 클라이언트의 m_Run State를 확인하여 Server UI 와 Client UI를 구분지어서 출력한다. (IsRunning() 함수 사용) <br>
*               7. loadDB() 에서는 memberList 뿐만아니라, ClientList도 같이 Load 시킨다. <br>
*               8. 채팅방(단체 채팅) 기능 추가, 친구 그룹 기능 추가, 메세지 복사/삭제/검색 기능 추가 <br>
*               9. 카카오톡  채팅기능 추가(채팅방,멤버를 이용한 채팅방 검색)
*               10. 메세지 파일 첨부 기능 추가(추가기능)
*				실행환경 : Visual Studio 2017 <br>
*	@date	2017.12.03
*	@author	김민성
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