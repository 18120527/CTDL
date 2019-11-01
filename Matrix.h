#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class Matrix
{
private:
	float** arr;
	int rows; //Số dòng
	int columns; //Số cột
public:
	Matrix(); //Hàm tạo mặc định
	Matrix(int m_row, int m_col); //Hàm tạo với 2 tham số truyền vào là dòng và cột
	Matrix(const Matrix& other); //Hàm tạo copy
	~Matrix(); //Hàm hủy
	int getRows(); //Hàm lấy số hàng
	int getColumns(); //Hàm lấy số cột
	void input(); //Hàm nhập
	void output(); //Hàm xuất
	bool isSquareMatrix(); //Hàm kiểm tra ma trận có vuông hay không?
	Matrix smallerMatrix(int m_row, int m_column); //Hàm thu nhỏ ma trận (xóa đi 1 dòng và 1 cột)
	float det();//Hàm tính định thức
	float det(Matrix m_matrix); //Hàm tính định thức ma trận với tham số truyền vào là ma trận đầu vào (giúp đệ quy được)
	bool checkInvertible();// Hàm kiểm tra ma trận có khả nghịch hay không
	Matrix inverseMatrix(); //Hàm tìm ma trận nghịch đảo
	int rank(); //Hàm tìm hạng của ma trận
	void changerow(int row1, int row2, float value); //Hàm biến đổi dòng
	void swaprow(int row1, int row2); //Hàm đổi chỗ 2 dòng 
	void divrow(int m_row, float value); //Hàm chia dòng cho 1 số thực
	bool isColumn0(int m_col); //Hàm kiểm tra cột có phần tử nào khác không hay không
	void abridgeMatrix();//Ma trận bậc thang rút gọn
	void linearEquation(); //Tìm nghiệm phương trình tuyến tính
	Matrix& operator=(const Matrix& other); //Toán tử gán bằng
	Matrix& operator*(const float num); //Toán tử nhân ma trận với một số thực
	const Matrix operator*(const Matrix& other) const; //Toán tử nhân ma trận với ma trận
};

