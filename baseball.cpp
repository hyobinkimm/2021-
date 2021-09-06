#define _CRT_SECURE_NO_WARNINGS	
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
#pragma comment(lib, "wininet.lib")
using namespace std;

int com[4];
int usr[4];

typedef struct pplayer {
	string name;
	double score;
}pr;


pr rank_p[200];

void download() {
	WinExec("FILE\\dist\\download_baseball\\download_baseball.exe", SW_SHOW);
}

void upload() {
	WinExec("FILE\\dist\\upload_baseball\\upload_baseball.exe", SW_SHOW);
}

void caution_download() {
	WinExec(".\\caution_download.exe", SW_HIDE);
}
bool cmp(pr a, pr b) {
	return a.score < b.score;
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


class Baseball {
private:
	string name;
	double score;
	pr rank_p[201];
	int cnt = 0;
	int player = 0;
public:
	Baseball() {
		Screen();
	}

	void Screen() {
		system("cls");
		printf("=======INCOM 숫자야구======\n");
		cout << "1. 게임 시작" << endl;
		cout << "2. 온라인 순위 보기" << endl;
		cout << "3. 게임 방법 보기" << endl;
		cout << "4. 온라인 순위 갱신하기" << endl;
		cout << "5. 게임 끝내기" << endl;
		printf("===========================\n");
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
			GameStart();
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
			showHowtoplay();
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
	void showHowtoplay() {
		printf("**********************************게임 방법**********************************\n\n");
		printf("1. 컴퓨터가 생각한 네 자리 수(1~9)를 맞혀야 하는 게임입니다.\n");
		printf("2. 임의의 숫자를 적을 때는 모두 다른 숫자로 적어야 합니다.\n");
		printf("3. 9회차 동안 3 STRIKE를 달성해야합니다.\n");
		printf("4. STRIKE는 사용자가 입력한 네 자리 수 중에서 컴퓨터와 같은 자리에 있는 수가 있는 경우입니다.\n");
		printf("5. BALL은 사용자가 입력한 네 자리 수 중에서 컴퓨터와 같은 수가 있는 경우입니다.\n");
		printf("6. 게임 시작을 누르자마자 시간 측정이 시작됩니다.\n\n");
	}

	void setComrand() {
		srand((unsigned int)time(NULL));
		for (int i = 0; i < 4; i++)
		{
			com[i] = (rand() % 9) + 1;
			for (int j = 0; j < i; j++)
			{
				if (com[i] == com[j]) i--;
			}
		}
	}

	void GameStart() {
		system("cls");
		setComrand();
		/*for (int i = 0; i < 4; i++)
		{
			cout << com[i] << " ";
		}
		cout << endl;*/
		int num = 1;
		printf("컴퓨터가 임의의 네 가지의 수를 정하였습니다.\n\n");
		Sleep(1000);
		printf("당신도 1~9까지의 임의의 네 가지의 수를 <<띄어쓰기>>로 구분하여 입력하세요.\n");
		printf("꼭! 4개만 입력하세요!!\n\n");

		clock_t start = clock();
		while (1) {
			if (num == 10) {
				printf("\n*********COMPUTER WIN*********\n\n");
				break;
			}
			int strike = 0;
			int ball = 0;
			printf("\n%d회)\n", num);
			num++;
			
			while (1) {
				bool iscompo = false;
				printf("INPUT : ");
				for (int i = 0; i < 4; i++) usr[i] = 0;
				for (int i = 0; i < 4; i++)
				{
					cin >> usr[i];

				}

				// 중복 검사
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (i == j)continue;
						if (usr[i] == usr[j]) {
							printf("중복 없이 모두 다른 숫자로 해야합니다. 처음부터 다시 입력하세요.\n");
							iscompo = true;
							break;
						}
						if (usr[i] < 1 || usr[i]>9) {
							printf("범위는 1부터 9까지입니다. 처음부터 다시 입력하세요.\n");
							iscompo = true;
							break;
						}
					}
					if (iscompo == true)break;
				}
				if (iscompo == false) {
					break;
				}
			}

			// 스트라이크, 볼 검사 			
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (com[i] == usr[j]) {
						if (i == j) {
							strike++;
						}
						else {
							ball++;
						}
					}
				}
			}
			printf("%d STRIKE %d BALL\n", strike, ball);
			if (strike == 4) {
				clock_t end = clock();
				printf("\n*********YOU WIN*********\n\n");
				score = 0.001 * (double(end) - double(start)); // score 저장
			
				printf("소요 시간 : %fs\n\n", score);
			
				afterGame();
				break;
			}
		}
		Sleep(1000);
		char input = '0';
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
			GameStart();
			return;
		}
	}

	void afterGame() {
		download();
		FileReader();
		bool isnew = true;
		for (int i = 0; i < cnt; i++)
		{
			if (rank_p[i].name == name) { // 기존 사용자
				if (score < rank_p[i].score) {
					rank_p[i].score = score;
					cout << "\n자체 신기록 달성! 점수가 저장되었습니다.\n\n";
				}
				isnew = false;
				break;
			}
		}
		if (isnew == true) { // 신규 사용자
			cout << "점수가 저장되었습니다.\n\n";
			rank_p[cnt].name = name;
			rank_p[cnt].score = score;
			cnt++;
		}
		writeFile();
		upload();
	}

	void writeFile() {
		ofstream f;
		f.open("score.dll", ios::out|ios::trunc);
		f << cnt << " ";
		for (int i = 0; i < cnt; i++)
		{
			f << rank_p[i].name << " " << rank_p[i].score << " ";
		}
		f.close();
	}

	void FileReader() {
		int x = 0;
		cnt = 0;
		ifstream f;
		f.open("score.dll", ios::in);
		f >> cnt;
		while (x < cnt) {
			f >> rank_p[x].name >> rank_p[x].score;
			x++;
		}
		f.close();
	}

	void Rank() {
		cout << "잠시만 기다려주세요...";
		download();
		FileReader();

		sort(rank_p, rank_p + cnt, cmp);

		system("cls");
		for (int i = 0; i < cnt; i++)
		{
			cout << i + 1 << "위 " << rank_p[i].name << " " << rank_p[i].score << "s" << endl;
		}
	}

};


int main() {
	SetConsoleTitle(TEXT("숫자야구"));

	if (isFolder()) { //.aws폴더가 사용자 이름 폴더에 잘 있으면
		cout << ".aws 폴더 확인 완료.\n\n";
		Sleep(1000);
	}
	else {
		cout << ".aws 폴더가 없습니다.\n\nInstaller를 실행합니다.\n\n잠시만 기다려주세요.\n\n";
		WinExec(".\\installer.exe", SW_HIDE);
		Sleep(5000);
	}

	connectInternet();
	caution_download();
	Baseball Game;
}
