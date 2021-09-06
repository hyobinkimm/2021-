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
	t = _waccess_s(dir_result, 0); // ������ ������ ���� �� 0�� ��ȯ
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
		printf("Not connected.\n���� ����.");
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
		printf("=======INCOM ���ھ߱�======\n");
		cout << "1. ���� ����" << endl;
		cout << "2. �¶��� ���� ����" << endl;
		cout << "3. ���� ��� ����" << endl;
		cout << "4. �¶��� ���� �����ϱ�" << endl;
		cout << "5. ���� ������" << endl;
		printf("===========================\n");
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
			GameStart();
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
			showHowtoplay();
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
	void showHowtoplay() {
		printf("**********************************���� ���**********************************\n\n");
		printf("1. ��ǻ�Ͱ� ������ �� �ڸ� ��(1~9)�� ������ �ϴ� �����Դϴ�.\n");
		printf("2. ������ ���ڸ� ���� ���� ��� �ٸ� ���ڷ� ����� �մϴ�.\n");
		printf("3. 9ȸ�� ���� 3 STRIKE�� �޼��ؾ��մϴ�.\n");
		printf("4. STRIKE�� ����ڰ� �Է��� �� �ڸ� �� �߿��� ��ǻ�Ϳ� ���� �ڸ��� �ִ� ���� �ִ� ����Դϴ�.\n");
		printf("5. BALL�� ����ڰ� �Է��� �� �ڸ� �� �߿��� ��ǻ�Ϳ� ���� ���� �ִ� ����Դϴ�.\n");
		printf("6. ���� ������ �����ڸ��� �ð� ������ ���۵˴ϴ�.\n\n");
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
		printf("��ǻ�Ͱ� ������ �� ������ ���� ���Ͽ����ϴ�.\n\n");
		Sleep(1000);
		printf("��ŵ� 1~9������ ������ �� ������ ���� <<����>>�� �����Ͽ� �Է��ϼ���.\n");
		printf("��! 4���� �Է��ϼ���!!\n\n");

		clock_t start = clock();
		while (1) {
			if (num == 10) {
				printf("\n*********COMPUTER WIN*********\n\n");
				break;
			}
			int strike = 0;
			int ball = 0;
			printf("\n%dȸ)\n", num);
			num++;
			
			while (1) {
				bool iscompo = false;
				printf("INPUT : ");
				for (int i = 0; i < 4; i++) usr[i] = 0;
				for (int i = 0; i < 4; i++)
				{
					cin >> usr[i];

				}

				// �ߺ� �˻�
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (i == j)continue;
						if (usr[i] == usr[j]) {
							printf("�ߺ� ���� ��� �ٸ� ���ڷ� �ؾ��մϴ�. ó������ �ٽ� �Է��ϼ���.\n");
							iscompo = true;
							break;
						}
						if (usr[i] < 1 || usr[i]>9) {
							printf("������ 1���� 9�����Դϴ�. ó������ �ٽ� �Է��ϼ���.\n");
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

			// ��Ʈ����ũ, �� �˻� 			
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
				score = 0.001 * (double(end) - double(start)); // score ����
			
				printf("�ҿ� �ð� : %fs\n\n", score);
			
				afterGame();
				break;
			}
		}
		Sleep(1000);
		char input = '0';
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
			if (rank_p[i].name == name) { // ���� �����
				if (score < rank_p[i].score) {
					rank_p[i].score = score;
					cout << "\n��ü �ű�� �޼�! ������ ����Ǿ����ϴ�.\n\n";
				}
				isnew = false;
				break;
			}
		}
		if (isnew == true) { // �ű� �����
			cout << "������ ����Ǿ����ϴ�.\n\n";
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
		cout << "��ø� ��ٷ��ּ���...";
		download();
		FileReader();

		sort(rank_p, rank_p + cnt, cmp);

		system("cls");
		for (int i = 0; i < cnt; i++)
		{
			cout << i + 1 << "�� " << rank_p[i].name << " " << rank_p[i].score << "s" << endl;
		}
	}

};


int main() {
	SetConsoleTitle(TEXT("���ھ߱�"));

	if (isFolder()) { //.aws������ ����� �̸� ������ �� ������
		cout << ".aws ���� Ȯ�� �Ϸ�.\n\n";
		Sleep(1000);
	}
	else {
		cout << ".aws ������ �����ϴ�.\n\nInstaller�� �����մϴ�.\n\n��ø� ��ٷ��ּ���.\n\n";
		WinExec(".\\installer.exe", SW_HIDE);
		Sleep(5000);
	}

	connectInternet();
	caution_download();
	Baseball Game;
}
