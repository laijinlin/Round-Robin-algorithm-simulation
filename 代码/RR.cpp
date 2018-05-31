#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
using namespace std;

//���̽ṹ��
typedef struct {
	char name;        //������
	int ArrivalTime;  //����ʱ��
	int ServiceTime;  //����ʱ��
	int FinishedTime; //���ʱ��
	int WholeTime;    //��תʱ��
	double WeightWholeTime;  //��Ȩ��תʱ��
}RR;

static queue<RR>RRqueue;  //�����ȴ�����
static queue<RR>Pqueue;  //�����ܽ��̶���
static double AverageWT = 0, AverageWWT = 0;
static int q;  //ʱ��Ƭ����
static int n;  //���̸���
static RR RRarray[100];  //��������
static char processMoment[100];  //�洢ÿ������ִ�н��̵�����
static int processMomentPoint = 0;  //������ǰִ���˶��ٸ�����
static int processSTime[50];  //�洢ÿ�����̵Ŀ�ʼʱ��
static int processFTime[50];  //�洢ÿ�����̵Ľ���ʱ��

//���뺯��_�ļ���ȡģʽ
int Input1() {
	ifstream inData;
	inData.open("./RR_data.txt");
	//����׳�Կ���
	if (!inData) {
		cout << "�ļ���ȡʧ��!" << endl;
		cout << "****************************************************************" << endl;
		return -1;
	}
	else {
		cout << "�ļ���ȡ�ɹ�!" << endl;
	}
	inData >> n;  //��RR_data.txt�ж�ȡ

	inData >> q;  //��RR_data.txt�ж�ȡʱ��Ƭ����

	//��RR_data.txt�ж�ȡ�������̵����ơ�����ʱ��ͷ���ʱ��
	for (int i = 0; i < n; i++) {
		inData >> RRarray[i].name;
	}
	for (int i = 0; i < n; i++) {
		inData >> RRarray[i].ArrivalTime;
	}
	for (int i = 0; i < n; i++) {
		inData >> RRarray[i].ServiceTime;
	}
	inData.close();
	cout << "****************************************************************" << endl;
	return 0;
}

//���뺯��_�ֶ�����ģʽ
void Input2() {
	cout << "��ӭ�����ֶ�����ģʽ!" << endl;
	cout << "��������̸��� n = ";
	cin >> n;  //������̸���
	cout << "������ʱ��Ƭ���� q = ";
	cin >> q;  //����ʱ��Ƭ����
	//����ÿ�����̵Ľ�����
	cout << "��������������ƣ�" << endl;
	for (int i = 0; i<n; i++) {
		cin >> RRarray[i].name;
	}
	//����ÿ�����̵ĵ���ʱ��
	cout << "����������̵ĵ���ʱ�䣺" << endl;
	for (int i = 0; i < n; i++) {
		cin >> RRarray[i].ArrivalTime;
	}
	//����ÿ�����̵ķ���ʱ��
	cout << "����������̵ķ���ʱ�䣺" << endl;
	for (int i = 0; i < n; i++) {
		cin >> RRarray[i].ServiceTime;
	}
	cout << "****************************************************************" << endl;
}

//��ʼ��Ϣ�������
void Output() {
	//����û����������Ϣ
	cout << "The information of processes is the following:" << endl;
	cout << setw(10) << "processName" << " ";
	cout << setw(10) << "ArrivalTime" << " ";
	cout << setw(10) << "ServiceTime" << " " << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(10) << RRarray[i].name << " ";
		cout << setw(10) << RRarray[i].ArrivalTime << " ";
		cout << setw(10) << RRarray[i].ServiceTime << " " << endl;
	}
	cout << "****************************************************************" << endl;
}

//ģ�⺯��_ģ������㷨����
void RR_Simulate() {
	int CurrentTime = 0;  //��ǰʱ��
	int tempTime;  //�����˱�������CurrentTime���ۼ�ʱ�䣬��ǰ���̵ķ���ʱ��С��ʱ��Ƭqʱ������
	int ncopy = n;  //��Ž��������Ŀ���
	int shortest = 0;  //��ŵ���ʱ������Ľ��̵��±�
	RR RRcopy[100];  //��Ž�������Ŀ���

	//������������
	for (int m = 0; m < n; m++) {
		RRcopy[m] = RRarray[m];
	}

	//�����������飬��������ʱ����������������н��̣�������˳�����ν����ܽ��̶���
	while (ncopy != 1) {
		shortest = 0;
		//�ҵ��������Ľ����±꣬����shortest
		for (int m = 0; m < ncopy - 1; m++) {
			if (RRcopy[m].ArrivalTime > RRcopy[m + 1].ArrivalTime) {
				shortest = m + 1;
			}
		}
		Pqueue.push(RRcopy[shortest]);  //���������Ľ��̽����ܶ���
		//�����ӵĽ����Ƴ���������������
		if (shortest == (ncopy - 1)) {
			ncopy--;
		}
		else {
			for (int m = shortest; m < ncopy - 1; m++) {
				RRcopy[m] = RRcopy[m + 1];
			}
			ncopy--;
		}
	}
	Pqueue.push(RRcopy[0]);  //������ʱ�����Ľ��̽����ܶ���

	//���ȴ�����Ϊ�����ܽ��̶���Ϊ��ʱ������ѭ��
	while (!RRqueue.empty() || !Pqueue.empty()) {
		//ʹ��������̵ĵ���ʱ��С�ڵ�ǰʱ��Ľ��̶��������
		while (!Pqueue.empty() && Pqueue.front().ArrivalTime <= CurrentTime) {
			RRqueue.push(Pqueue.front());
			Pqueue.pop();
		}
		//���ȴ����н�����ȫ��ִ���꣬�����н���û�е���ʱ������ǰʱ���������쵽����̵ĵ���ʱ��
		if (RRqueue.empty() && !Pqueue.empty()) {
			CurrentTime = Pqueue.front().ArrivalTime;
		}
		//ʹ��������̵ĵ���ʱ��С�ڵ�ǰʱ��Ľ��̶��������
		while (!Pqueue.empty() && Pqueue.front().ArrivalTime <= CurrentTime) {
			RRqueue.push(Pqueue.front());
			Pqueue.pop();
		}
		
		//ȷ�ϸô�ʱ��Ƭ�����ʱ��tempTime
		if (RRqueue.front().ServiceTime < q) {
			tempTime = RRqueue.front().ServiceTime;
		}
		else {
			tempTime = q;
		}

		RRqueue.front().ServiceTime -= q;  //����ÿִ��һ�Σ��ͽ������ʱ��-q
		processSTime[processMomentPoint] = CurrentTime;  //��¼ÿ�����̵Ŀ�ʼʱ��
		CurrentTime += tempTime;
		processFTime[processMomentPoint] = CurrentTime;  //��¼ÿ�����̵Ľ���ʱ��
		processMoment[processMomentPoint] = RRqueue.front().name;//��¼ÿ������ִ�еĽ�����
		processMomentPoint++;

		//ʹ��������̵ĵ���ʱ��С�ڵ�ǰʱ��Ľ��̶��������
		while (!Pqueue.empty() && Pqueue.front().ArrivalTime <= CurrentTime) {
			RRqueue.push(Pqueue.front());
			Pqueue.pop();
		}

		//��ִ����Ľ����˳�����
		if (RRqueue.front().ServiceTime <= 0) {
			RRqueue.pop();  //������̵ķ���ʱ��С�ڵ���0�����ý����Ѿ��������ˣ�������ջ
		}
		else {
			//�������Ƶ���β
			RRqueue.push(RRqueue.front());
			RRqueue.pop();
		}
	}
}

//�������_���ģ��ִ�й���
void display1() {
	int time1 = 0;  //����ȡ���ڼ��ι��̵Ŀ�ʼʱ��
	int time2 = 0;  //����ȡ���ڼ��ι��̵Ľ���ʱ��
	int count = 0;
	cout << "�����̵�ִ��ʱ����Ϣ��" << endl;
	cout << "  " << processSTime[time1] << "ʱ�� --> " << setw(2) << processFTime[time2] << "ʱ��";
	for (int i = 0; i < processMomentPoint; i++) {
		count = 0;
		cout << setw(3) << processMoment[i] << setw(3) << endl;

		while (RRarray[count].name != processMoment[i] && count < n) {
			count++;
		}
		RRarray[count].FinishedTime = processFTime[time2];

		if (i < processMomentPoint - 1) {
			time1++;
			time2++;
			cout << setw(3) << processSTime[time1] << "ʱ��" << " --> " << setw(2) << processFTime[time2] << "ʱ��" << setw(3);
		}
	}
	cout << endl;
}

//���㺯��_������������Ϣ
void RR_Calculate() {
	//��תʱ�䡢��Ȩ��תʱ�䡢ƽ����תʱ�䡢��Ȩƽ����תʱ��ļ���
	//��תʱ�� = ���ʱ�� - ����ʱ��
	//��Ȩ��תʱ�� = ��תʱ��/����ʱ��
	for (int i = 0; i < n; i++) {
		RRarray[i].WholeTime = RRarray[i].FinishedTime - RRarray[i].ArrivalTime;
		RRarray[i].WeightWholeTime = (double)RRarray[i].WholeTime / RRarray[i].ServiceTime;
	}

	double x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		x += RRarray[i].WholeTime;
		y += RRarray[i].WeightWholeTime;
	}
	AverageWT = x / n;
	AverageWWT = y / n;
}

//�������_������������Ϣ
void display2() {
	cout << "****************************************************************" << endl;
	cout << "RR�����㷨ִ�к󣺽��������Ϣ���£�" << endl;
	cout << setw(10) << "��������ID��" << " ";
	cout << setw(10) << "����ʱ��" << " ";
	cout << setw(10) << "����ʱ��" << " ";
	cout << setw(10) << "���ʱ��" << " ";
	cout << setw(10) << "��תʱ��" << " ";
	cout << setw(10) << "��Ȩ��תʱ��" << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(10) << RRarray[i].name << " ";
		cout << setw(10) << RRarray[i].ArrivalTime << " ";
		cout << setw(10) << RRarray[i].ServiceTime << " ";
		cout << setw(10) << RRarray[i].FinishedTime << " ";
		cout << setw(10) << RRarray[i].WholeTime << " ";
		cout << setw(10) << RRarray[i].WeightWholeTime << " " << endl;
	}
	cout << "���н��̵�ƽ����תʱ�� = " << AverageWT << endl;
	cout << "���н��̵�ƽ����Ȩ��תʱ�� = " << AverageWWT << endl;
	cout << "****************************************************************" << endl;
}

int main() {
	cout << "��ѡ������ģʽ��" << endl;
	cout << "1.�ļ���ȡģʽ" << endl;
	cout << "2.�û�����ģʽ" << endl;
	int i, j;
	j = 0;
	while (j==0) {
		cout << "������(1/2)��";
		cin >> i;
		cout << "****************************************************************" << endl;
		switch (i) {
		case 1:
			int a;
			a = Input1();
			if (a == -1) {
				cout << "�����ļ��Ƿ����!" << endl;
				system("pause");
				return -1;
			}
			j = 1;
			break;
		case 2:
			Input2();
			j = 1;
			break;
		default:cout << "������������������!" << endl;
		}
	}
	Output();
	RR_Simulate();
	display1();
	RR_Calculate();
	display2();
	system("pause");
	return 0;
}