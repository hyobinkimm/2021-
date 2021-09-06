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

struct CursorPosition { //Ŀ�� ��ġ
	int x;
	int y;
};

enum KEYBOARD { //Ű���� ��
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
	t = _waccess_s(dir_result, 0); // ������ ������ ���� �� 0�� ��ȯ
	if (t == 0) { return true; }
	else return false;
}

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
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
		printf("Not connected.\n���� ����.");
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
		cout << "1. ���� ����" << endl;
		cout << "2. �¶��� ���� ����" << endl;
		cout << "3. ���� ��� ����" << endl;
		cout << "4. �¶��� ���� �����ϱ�" << endl;
		cout << "5. ���� ������" << endl;
		printf("============================\n");
		cout << "INPUT : ";

		int input;
		while (1) {
			cin >> input;
			if (1 <= input && input <= 5)break;
			else {
				cout << "�ٽ� �Է����ּ���\nINPUT : ";
			}
		}
		Input(input);
	}
	void Input(int x) {
		if (x == 1) {
			system("cls");
			// ���� Ŭ������ �̸� ����
			printf("�ڽ��� �巯���� ���� Ȥ�� �̸��� �Է����ּ���.(����X)\n");
			printf("INPUT : ");
			cin >> name;
			printf("������ �����մϴ�.\n");
			printf("3..\n"); Sleep(1000);
			printf("2..\n"); Sleep(1000);
			printf("1..\n"); Sleep(1000);
			StartGame();
		}
		else if (x == 2) {
			system("cls");
			Rank();
			cout << "\n���� ȭ������ ���ư��� �ʹٸ� Enter Ű�� ��������.";
			int key;
			while (true) {
				if (_kbhit()) { //Ű �Է� ���
					key = _getch(); //����Ű�� ������ ����ȭ��(InitialScreen)���� �̵�
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
			cout << "���� ȭ������ ���ư��� �ʹٸ� Enter Ű�� ��������.";
			int key;
			while (true) {
				if (_kbhit()) { //Ű �Է� ���
					key = _getch(); //����Ű�� ������ ����ȭ��(InitialScreen)���� �̵�
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
			printf("������Ʈ �Ϸ�.\n");
			Sleep(1000);
			printf("���� â���� �ǵ��ư��ϴ�.\n");
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
		cout << "��ø� ��ٷ��ּ���...";
		download();
		FileReader();

		sort(p, p + cnt, cmp);

		system("cls");
		for (int i = 0; i < cnt; i++)
		{
			cout << i + 1 << "�� " << p[i].name << " " << p[i].high_score << "��" << endl;
		}
	}
	void ShowHowtoPlay() {
		printf("****************************���� ���****************************\n\n");
		printf("1. 4��4 �迭�ǿ��� �Ȱ��� ī�带 ���ߴ� �����Դϴ�.\n");
		printf("2. ���ĺ� a~z �� ������ ���ڰ� �� ������ ���ϴ�.\n");
		printf("3. ī�带 ������ Ƚ�� �������� ������ �����˴ϴ�.\n");
		printf("4. ������ claer�ؾ߸� ������ ��ϵ˴ϴ�.\n");
		printf("5. ī�带 ������ Ƚ���� ������ ���, Ǯ�� �ð��� �������� ����� �ö󰩴ϴ�.\n\n");
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
		cout << "ī�带 ������ Ƚ�� : " << Count;
		GotoXY(14, 2);
		cout << "ī�带 ���� ¦�� �� : " << MatchCount;
		isVisit = false;
	}
	void CheckCard() {
		if (FlipCount == 2)
		{
			char c = '?';
			if ((OriginalMap[FlipPosition[0].y][FlipPosition[0].x] == OriginalMap[FlipPosition[1].y][FlipPosition[1].x]) &&
				((FlipPosition[0].y != FlipPosition[1].y) || (FlipPosition[0].x != FlipPosition[1].x))) //������ ��ġ�� ���ڰ� ������
			{
				if (visited[FlipPosition[0].y][FlipPosition[0].x] == 0 &&
					visited[FlipPosition[1].y][FlipPosition[1].x] == 0) {
					c = ' '; //�ٲٰ� 
					++MatchCount; //�ö�
					visited[FlipPosition[0].y][FlipPosition[0].x] = 1;
					visited[FlipPosition[1].y][FlipPosition[1].x] = 1;
				}
				else { Sleep(200); }
			}
			else
			{
				Sleep(200); //¦�� �ȸ��� ��� Sleep
			}
			QuestionMap[FlipPosition[0].y][FlipPosition[0].x] = c; //���忡 ������Ʈ ����
			QuestionMap[FlipPosition[1].y][FlipPosition[1].x] = c;
			FlipCount = 0;
			++Count;
			if (Count >= 100) {
				system("cls");
				GameOver();
			}
			if (MatchCount >= 8) //8�̻��̸� �� ������̹Ƿ�
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
		cout << "��ø� ��ٷ��ּ���...\n\n";
		score = 108 - count;
		
		download();
		FileReader();

		bool isNew = true;
		for (int i = 0; i < cnt; i++) { // ���� �����
			if (p[i].name == name) { 
				cout << "���� ������̼̱���!\n";
				if (score >= p[i].high_score) {
					p[i].high_score = score;
					p[i].playing_time = 0.001 * (double(end) - double(start));
				}
				isNew = false;
				break;
			}
		}

		if (isNew == true) { // �ű� �����
			cout << "�ű� ������̽ñ���!\n";
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
		cout << name << "�� ������ " << score << "�Դϴ�!\n";
		Sleep(5000);
		system("cls");

		TextColor(WHITE);
		OneMoreTime();
	}
	void OneMoreTime() {
		char input;
		cout << "�޴��� ���ư��ðڽ��ϱ�? Y/N\n";
		while (1) {
			cout << "INPUT : ";
			cin >> input;
			if (input == 'Y' || input == 'N' || input == 'y' || input == 'n') {
				break;
			}
			else {
				cout << "Y�� N �߿� �ٽ� �Է��ϼ���.\n";
			}
		}
		if (input == 'Y' || input == 'y') {
			system("cls");
			Screen();
		}
		else {
			cout << "������ �ٽ� �����մϴ�.\n";
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
		for (int i = 0; i < 16; i += 2) { //����
			for (int j = 0; j < 2; j++) {
				TempOriginalMap[i + j] = temp;
			}
			temp++;
		}
		for (int i = 0; i < 4; i++) { //? ä���ֱ�
			for (int j = 0; j < 4; j++) {
				QuestionMap[i][j] = '?';
			}
		}
		srand((unsigned int)time(NULL)); //����
		for (int i = 0; i < 100; i++) { //����ȭ ����ֱ�
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
	char QuestionMap[4][4] = {};  // ���ӿ� �������� ����
	int FlipCount = 0; //������ Ƚ��( �ι� ���������� Ȯ�ο�)
	int Count = 0; //������ Ƚ��
	int MatchCount = 0; //¦ ���� Ƚ�� 
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
		cout << ".aws ���� Ȯ�� �Ϸ�.\n\n";
		Sleep(1000);
	}
	else {
		cout << ".aws ������ �����ϴ�.\n\nInstaller�� �����մϴ�.\n\n��ø� ��ٷ��ּ���.\n\n";
		WinExec(".\\install.exe", SW_HIDE);
		Sleep(5000);
	}

	connectInternet();
	caution_download();
	CardGameManager game;

	return 0;
}