#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <string>
#include <random>
#include <Wininet.h>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#pragma comment(lib, "wininet.lib")
using namespace std;

typedef struct player {
	string name;
	double high_score;
	double playing_time;
}pr;

pr p[300];

bool cmp(pr a, pr b) {
	if (a.high_score == b.high_score) {
		return a.playing_time < b.playing_time;
	}
	return a.high_score > b.high_score;
}

struct CursorPosition { //커서 위치
	int x;
	int y;
};

enum KEYBOARD { //키보드 값
	IS_ARROW = 224,
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,
	SPACE = 32,
};

enum COLOR
{
	GREEN = 10,
	MINT,
	RED,
	PINK,
	YELLOW,
	WHITE,
};

void download() {
	WinExec("FILE\\dist\\download_card\\download_card.exe", SW_SHOW);
}

void upload() {
	WinExec("FILE\\dist\\upload_card\\upload_card.exe", SW_SHOW);
}

void caution_download() {
	WinExec(".\\caution_download.exe", SW_HIDE);
}

bool isFolder() {
	char usrName[260] = { 0 };
	DWORD length = 260;
	GetUserName(usrName, &length);
	string username(usrName);
	string s = "C:\\Users\\" + username + "\\.aws";
	wstring dir = wstring(s.begin(), s.end());
	const wchar_t* dir_result = dir.c_str();

	int t = 0;
	t = _waccess_s(dir_result, 0); // 폴더가 열리면 성공 시 0을 반환
	if (t == 0) { return true; }
	else return false;
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void connectInternet() {
	system("cls");
	DWORD flag;
	TCHAR name[256];
	bool Internet = ::InternetGetConnectedStateEx(&flag, name, 256, 0);
	if (Internet) {
		printf("Connected\n");
		system("cls");
		Sleep(1000);
		download();
	}
	else {
		printf("Not connected.\n게임 종료.");
		Sleep(1000);
		exit(1);
	}
}

void GotoXY(int x, int y) {
	COORD position = { x,y };
	position.X = 2 * x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int GetKeyDown() {
	if (_kbhit() != 0) {
		return _getch();
	}
	return 0;
}

class CardGameManager {
public:
	CardGameManager() {
		Screen();
	}
	void Screen() {
		system("cls");
		printf("======INCOM CARD MATCH======\n");
		cout << "1. 게임 시작" << endl;
		cout << "2. 온라인 순위 보기" << endl;
		cout << "3. 게임 방법 보기" << endl;
		cout << "4. 온라인 순위 갱신하기" << endl;
		cout << "5. 게임 끝내기" << endl;
		printf("============================\n");
		cout << "INPUT : ";

		int input;
		while (1) {
			cin >> input;
			if (1 <= input && input <= 5)break;
			else {
				cout << "다시 입력해주세요\nINPUT : ";
			}
		}
		Input(input);
	}
	void Input(int x) {
		if (x == 1) {
			system("cls");
			// 게임 클래스에 이름 저장
			printf("자신을 드러내는 별명 혹은 이름을 입력해주세요.(띄어쓰기X)\n");
			printf("INPUT : ");
			cin >> name;
			printf("게임을 시작합니다.\n");
			printf("3..\n"); Sleep(1000);
			printf("2..\n"); Sleep(1000);
			printf("1..\n"); Sleep(1000);
			StartGame();
		}
		else if (x == 2) {
			system("cls");
			Rank();
			cout << "\n이전 화면으로 돌아가고 싶다면 Enter 키를 누르세요.";
			int key;
			while (true) {
				if (_kbhit()) { //키 입력 대기
					key = _getch(); //엔터키가 들어오면 메인화면(InitialScreen)으로 이동
					if (key == 13) {
						system("cls");
						Screen();
						return;
					}
				}
			}
		}
		else if (x == 3) {
			system("cls");
			ShowHowtoPlay();
			cout << "이전 화면으로 돌아가고 싶다면 Enter 키를 누르세요.";
			int key;
			while (true) {
				if (_kbhit()) { //키 입력 대기
					key = _getch(); //엔터키가 들어오면 메인화면(InitialScreen)으로 이동
					if (key == 13) {
						system("cls");
						Screen();
						return;
					}
				}
			}
		}
		else if (x == 4) {
			system("cls");
			download();
			FileReader();
			printf("업데이트 완료.\n");
			Sleep(1000);
			printf("이전 창으로 되돌아갑니다.\n");
			Sleep(1500);
			Screen();
		}
		else exit(0);
	}
	void FileReader() {
		cnt = 0;
		int x = 0;
		ifstream f;
		f.open("score.dll", ios::in);
		f >> cnt;
		while (x < cnt) {
			f >> p[x].name >> p[x].high_score >> p[x].playing_time;
			x++;
		}
		f.close();
	}
	void Rank() {
		cout << "잠시만 기다려주세요...";
		download();
		FileReader();

		sort(p, p + cnt, cmp);

		system("cls");
		for (int i = 0; i < cnt; i++)
		{
			cout << i + 1 << "위 " << p[i].name << " " << p[i].high_score << "점" << endl;
		}
	}
	void ShowHowtoPlay() {
		printf("****************************게임 방법****************************\n\n");
		printf("1. 4×4 배열판에서 똑같은 카드를 맞추는 게임입니다.\n");
		printf("2. 알파벳 a~z 중 임의의 문자가 한 쌍으로 들어갑니다.\n");
		printf("3. 카드를 뒤집은 횟수 기준으로 점수가 측정됩니다.\n");
		printf("4. 게임을 claer해야만 점수가 등록됩니다.\n");
		printf("5. 카드를 뒤집은 횟수가 동일할 경우, 풀은 시간을 기준으로 등수가 올라갑니다.\n\n");
	}
	void StartGame() {
		system("cls");
		Initialize();
		
		start = clock();
		int key = 0;
		while (1) {
			key = GetKeyDown();
			if (key == KEYBOARD::IS_ARROW) {
				MoveCursor();
			}
			else if (key == KEYBOARD::SPACE) {
				FlipCard();
			}
			DrawBoard();
			Sleep(50);
			CheckCard();
		}
	}
	void TextColor(int COLOR) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR);
	}
	void MoveCursor() {
		GotoXY(1 + (Player.x * 3), 1 + (Player.y * 2) + 1);
		printf("  ");
		switch (_getch()) {
		case KEYBOARD::UP:
			--Player.y;
			if (Player.y <= 0) {
				Player.y = 0;
			}
			break;

		case KEYBOARD::DOWN:
			++Player.y;
			if (Player.y >= 3) {
				Player.y = 3;
			}
			break;

		case KEYBOARD::LEFT:
			--Player.x;
			if (Player.x <= 0) {
				Player.x = 0;
			}
			break;

		case KEYBOARD::RIGHT:
			++Player.x;
			if (Player.x >= 3) {
				Player.x = 3;
			}
			break;
		}
	}
	void FlipCard() {
		FlipPosition[FlipCount].x = Player.x;
		FlipPosition[FlipCount].y = Player.y;
		if (visited[Player.y][Player.x] == 1) {
			isVisit = true;
			return;
		}
		QuestionMap[Player.y][Player.x] = OriginalMap[Player.y][Player.x] + '0';
		++FlipCount;
	}
	void DrawBoard() {
		if (isVisit == true) {
			isVisit = false;
			return;
		}
		for (int i = 0; i < 4; i++) {
			GotoXY(1, 1 + (2 * i));
			for (int j = 0; j < 4; j++) {
				TextColor(YELLOW);
				if (QuestionMap[i][j] != '?') {
					TextColor(MINT);
				}
				printf("[%c]   ", QuestionMap[i][j]);
			}
			cout << endl;
		}
		GotoXY(1 + (Player.x * 3), 1 + (Player.y * 2) + 1);
		printf(" ^");
		GotoXY(14, 1);
		TextColor(WHITE);
		cout << "카드를 뒤집은 횟수 : " << Count;
		GotoXY(14, 2);
		cout << "카드를 맞춘 짝의 수 : " << MatchCount;
		isVisit = false;
	}
	void CheckCard() {
		if (FlipCount == 2)
		{
			char c = '?';
			if ((OriginalMap[FlipPosition[0].y][FlipPosition[0].x] == OriginalMap[FlipPosition[1].y][FlipPosition[1].x]) &&
				((FlipPosition[0].y != FlipPosition[1].y) || (FlipPosition[0].x != FlipPosition[1].x))) //뒤집은 위치의 숫자가 같으면
			{
				if (visited[FlipPosition[0].y][FlipPosition[0].x] == 0 &&
					visited[FlipPosition[1].y][FlipPosition[1].x] == 0) {
					c = ' '; //바꾸고 
					++MatchCount; //올라감
					visited[FlipPosition[0].y][FlipPosition[0].x] = 1;
					visited[FlipPosition[1].y][FlipPosition[1].x] = 1;
				}
				else { Sleep(200); }
			}
			else
			{
				Sleep(200); //짝이 안맞을 경우 Sleep
			}
			QuestionMap[FlipPosition[0].y][FlipPosition[0].x] = c; //보드에 업데이트 해줌
			QuestionMap[FlipPosition[1].y][FlipPosition[1].x] = c;
			FlipCount = 0;
			++Count;
			if (Count >= 100) {
				system("cls");
				GameOver();
			}
			if (MatchCount >= 8) //8이상이면 다 맞춘것이므로
			{
				end = clock();
				system("cls");
				SaveScore(Count);
				GameClear();
				return;
			}
		}
	}
	void SaveScore(int count) {
		system("cls");
		cout << "잠시만 기다려주세요...\n\n";
		score = 108 - count;
		
		download();
		FileReader();

		bool isNew = true;
		for (int i = 0; i < cnt; i++) { // 기존 사용자
			if (p[i].name == name) { 
				cout << "기존 사용자이셨군요!\n";
				if (score >= p[i].high_score) {
					p[i].high_score = score;
					p[i].playing_time = 0.001 * (double(end) - double(start));
				}
				isNew = false;
				break;
			}
		}

		if (isNew == true) { // 신규 사용자
			cout << "신규 사용자이시군요!\n";
			p[cnt].name = name;
			p[cnt].high_score = score;
			p[cnt].playing_time = 0.001 * (double(end) - double(start));
			cnt++;
		}
		WriteFile();
		upload();
		return;
	}
	void WriteFile() {
		ofstream f;
		f.open("score.dll", ios::out|ios::trunc);
		f << cnt << " ";
		for (int i = 0; i < cnt; i++) {
			f << p[i].name << " " << p[i].high_score << " " << p[i].playing_time << " ";
		}
		f.close();
	}
	void GameOver() {
		TextColor(RED);
		GotoXY(10, 2);
		cout << "====================================";
		GotoXY(10, 3);
		cout << "====================================";
		GotoXY(10, 4);
		cout << "=============GAME OVER==============";
		GotoXY(10, 5);
		cout << "====================================";
		GotoXY(10, 6);
		cout << "====================================";
		Sleep(3000);
		system("cls");
		
		TextColor(WHITE);
		OneMoreTime();
	}
	void GameClear() {
		system("cls");
		TextColor(MINT);
		GotoXY(10, 2);
		cout << "====================================";
		GotoXY(10, 3);
		cout << "====================================";
		GotoXY(10, 4);
		cout << "=============GAME CLEAR=============";
		GotoXY(10, 5);
		cout << "====================================";
		GotoXY(10, 6);
		cout << "====================================";
		GotoXY(10, 8);
		cout << name << "의 점수는 " << score << "입니다!\n";
		Sleep(5000);
		system("cls");

		TextColor(WHITE);
		OneMoreTime();
	}
	void OneMoreTime() {
		char input;
		cout << "메뉴로 돌아가시겠습니까? Y/N\n";
		while (1) {
			cout << "INPUT : ";
			cin >> input;
			if (input == 'Y' || input == 'N' || input == 'y' || input == 'n') {
				break;
			}
			else {
				cout << "Y랑 N 중에 다시 입력하세요.\n";
			}
		}
		if (input == 'Y' || input == 'y') {
			system("cls");
			Screen();
		}
		else {
			cout << "게임을 다시 시작합니다.\n";
			Sleep(1000);
			cout << "3..\n"; Sleep(1000);
			cout << "2..\n"; Sleep(1000);
			cout << "1..\n"; Sleep(1000);
			system("cls");
			StartGame();
			return;
		}
		
	}
	void Initialize() {
		for (int i = 0; i < 16; i += 2) { //랜덤
			for (int j = 0; j < 2; j++) {
				TempOriginalMap[i + j] = temp;
			}
			temp++;
		}
		for (int i = 0; i < 4; i++) { //? 채워넣기
			for (int j = 0; j < 4; j++) {
				QuestionMap[i][j] = '?';
			}
		}
		srand((unsigned int)time(NULL)); //랜덤
		for (int i = 0; i < 100; i++) { //랜덤화 집어넣기
			index1 = rand() % 16;
			index2 = rand() % 16;
			temp_index = TempOriginalMap[index1];
			TempOriginalMap[index1] = TempOriginalMap[index2];
			TempOriginalMap[index2] = temp_index;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				OriginalMap[i][j] = TempOriginalMap[i * 4 + j] + '0';
			}
		}
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				QuestionMap[i][j] = '?';
			}
		}
		Player.x = 0;
		Player.y = 0;
		FlipCount = 0;
		Count = 0;
		MatchCount = 0;
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				visited[i][j] = 0;
			}
		}
		start = 0; end = 0;
		isVisit = false;
	}
private:
	int TempOriginalMap[16] = {};
	int OriginalMap[4][4] = {};
	char QuestionMap[4][4] = {};  // 게임에 보여지는 값들
	int FlipCount = 0; //뒤집은 횟수( 두번 뒤집었는지 확인용)
	int Count = 0; //뒤집은 횟수
	int MatchCount = 0; //짝 맞은 횟수 
	int temp = 1;
	int index1 = 0, index2 = 0, temp_index = 0;
	int tempX, tempY;

	bool isVisit = false;
	clock_t start, end;
	
	int visited[4][4] = {};
	
	string name;
	double score;
	int cnt = 0;

	CursorPosition Player;
	CursorPosition FlipPosition[2];
};

int main() {
	SetConsoleTitle(TEXT("CARDMATCH"));
	CursorView();
	caution_download();

	if (isFolder()) {
		cout << ".aws 폴더 확인 완료.\n\n";
		Sleep(1000);
	}
	else {
		cout << ".aws 폴더가 없습니다.\n\nInstaller를 실행합니다.\n\n잠시만 기다려주세요.\n\n";
		WinExec(".\\install.exe", SW_HIDE);
		Sleep(5000);
	}

	connectInternet();
	caution_download();
	CardGameManager game;

	return 0;
}