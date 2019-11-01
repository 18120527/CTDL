#include "Vector.h"
#include "Matrix.h"
#include "Bool.h"

void menu();
int main()
{
	menu();
	return 0;
}

void menu()
{
	int condBreak;
	do {
		system("cls");
		cout << "\t\t\tMENU"
			<< "\n1. Vector"
			<< "\n2. Matrix"
			<< "\n3. Bool";
		cout << "\nNhap lua chon: ";
		int selectAlgorithm;
		do {
			cin >> selectAlgorithm;
			if (selectAlgorithm < 0 || selectAlgorithm >3)
				cout << "\nLua chon sai. ";
		} while (selectAlgorithm < 0 || selectAlgorithm >3);

		system("cls");
		if (selectAlgorithm == 1) { 
			//Các thuật toán trên vector
			cout << "1. Cong 2 vector"
				<< "\n2. Nhan vector voi mot so alpha"
				<< "\nNhap lua chon: ";
			int select;
			do {
				cin >> select;
				if (select < 0 || select >2)
					cout << "\nLua chon sai. ";
			} while (select < 0 || select >2);
			system("cls");
			if (select == 1) {
				Vector v1, v2;
				cout << "Nhap vector thu nhat: \n";
				v1.Input();
				cout << "Nhap vector thu 2: \n";
				v2.Input();
				if (v1.getSize() != v2.getSize())
					cout << "\nNhap sai. 2 vector khong cung do rong. ";
				else {
					v1 = v1.Addvector(v2);
					cout << "Vector sau khi cong: \n";
					v1.Output();
				}
			}
			else { //select =2
				Vector v;
				cout << "Nhap vector: \n";
				v.Input();
				cout << "Nhap alpha: ";
				float alpha;
				cin >> alpha;
				v = v.MulAlpha(alpha);
				cout << "Vector sau khi nhan voi alpha:\n";
				v.Output();
			}
		}
		else if (selectAlgorithm == 2) {
			//Các thuật toán trên ma trận
			cout << "1. Tim dinh thuc ma tran"
				<< "\n2. Nghich dao ma tran"
				<< "\n3. Tich hai ma tran"
				<< "\n4. Tim hang cua ma tran"
				<< "\n5. He phuong trinh tuyen tinh";
			int select;
			cout << "\nNhap lua chon: ";
			do {
				cin >> select;
				if (select < 0 || select >5)
					cout << "\nLua chon sai. ";
			} while (select < 0 || select >5);
			system("cls");
			if (select == 1) {
				Matrix m;
				cout << "Nhap ma tran:\n";
				m.input();
				cout << "Ket qua tinh dinh thuc cua ma tran vua nhap: " << m.det();
			}
			else if (select == 2) {
				Matrix m;
				cout << "Nhap ma tran:\n";
				m.input();
				if (m.checkInvertible()) { //Kiểm tra tính khả nghịch
					m = m.inverseMatrix();
					cout << "\nMa tran nghich dao cua ma tran vua nhap: \n";
					m.output();
				}
				else//Không có ma trận nghịch đảo
					cout << "Ma tran khong kha nghich. ";
			}
			else if (select == 3) {
				Matrix m1, m2;
				cout << "Nhap ma tran thu nhat:\n";
				m1.input();
				cout << "\nNhap ma tran thu 2: \n";
				m2.input();
				if (m1.getColumns() == m2.getRows()) {
					Matrix result = m1 * m2;
					cout << "\nKet qua nhan 2 ma tran: \n";
					result.output();
				}
				else
					cout << "Khong thuc hien duoc. So cot cua ma tran 1 khac so dong cua ma tran 2.";
			}
			else if (select == 4) {
				Matrix m;
				cout << "Nhap ma tran:\n";
				m.input();
				cout << "Hang cua ma tran vua nhap la: " << m.rank();
			}
			else{ //select = 5
				Matrix m;
				cout << "Nhap ma tran mo rong cua he:\n";
				m.input();
				m.linearEquation();
			}
		}
		else { //selectAlgorithm = 3
			//Tìm đa thức tối tiểu của hàm bool
			vector<int> arr;
			cout << "Nhap so phan tu: ";
			int n;
			do {
				cin >> n;
				if (n <= 0)
					cout << "Nhap sai. Nhap lai: ";
			} while (n <= 0);
			arr.resize(n);
			cout << "Nhap cac phan tu: \n";
			for (int i = 0; i < arr.size(); i++)
				cin >> arr[i];

			int var;
			cout << "Nhap so bien: ";
			do {
				cin >> var;
				if (var <= 0)
					cout << "Nhap sai. Nhap lai: ";
			} while (var <= 0);
			cout << "\nCac cong thuc toi tieu la: \n";
			Application(arr, var);
		}
		cout << endl;

		system("pause");
		system("cls");
		cout << "\nBan co muon tiep tuc khong?"
			<< "\n1. Tiep tuc"
			<< "\n0. Dung"
			<< "\nNhap lua chon: ";
		do {
			cin >> condBreak;
			if (condBreak < 0 || condBreak >2)
				cout << "\nLua chon sai. ";
		} while (condBreak < 0 || condBreak >2);
	} while (condBreak == 1);
}