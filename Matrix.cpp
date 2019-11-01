#include "matrix.h"

//Tác dụng của hàm: Tạo ma trận mặc định
Matrix::Matrix()
{
	arr = NULL;
	rows = 0;
	columns = 0;
}

//Tác dụng của hàm: Tạo ma trận với 2 tham số truyền vào
//Input: m_row: số dòng
//		 m_col: số cột
Matrix::Matrix(int m_row, int m_col)
{
	rows = m_row;
	columns = m_col;
	arr = new float* [rows];
	for (int i = 0; i < rows; i++)
		arr[i] = new float[columns];
}

//Tác dụng của hàm: Tạo ma trận bằng cách sao chép
//Input: other: ma trận để sao chép
Matrix::Matrix(const Matrix& other)
{
	//Gán giá trị cho rows và columns
	rows = other.rows;
	columns = other.columns;

	//Cấp phát bộ nhớ cho arr
	arr = new float* [rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new float[columns];
	}

	//Copy dữ liệu từ other.arr sang arr
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			arr[i][j] = other.arr[i][j];
}

//Tác dụng của hàm: Hủy ma trận
Matrix::~Matrix()
{
	if (arr != NULL) //Kiểm tra arr có tồn tại hay không
	{
		for (int i = 0; i < rows; i++) {
			delete[] arr[i]; //Xóa bộ nhớ đã cấp phát cho từng hàng
		}
		delete[] arr; //Xóa bộ nhớ đã cấp phát cho arr
		rows = 0;
		columns = 0;
		arr = NULL;
	}
}

//Tác dụng hàm: lấy số dòng
//Output: số dòng
int Matrix::getRows()
{
	return rows;
}

//Tác dụng hàm: lấy số cột
//Output: số cột
int Matrix::getColumns()
{
	return columns;
}

//Tác dụng của hàm: Nhập ma trận
void Matrix::input()
{
	//Nhập số dòng
	cout << "Nhap so dong ma tran: ";
	cin >> rows;
	//Nhập số cột
	cout << "Nhap so cot ma tran: ";
	cin >> columns;

	//Cấp phát bộ nhớ cho ma trận có "rows" dòng, "columns" cột
	arr = new float* [rows];
	for (int i = 0; i < rows; i++) {
		arr[i] = new float[columns];
	}

	cout << "\tNhap cac phan tu cho ma tran: \n";
	//Nhập dữ liệu từng vị trí của ma trận
	for (int i = 0; i < rows; i++) {
		cout << "Nhap cac phan tu cho dong " << i << " (moi phan tu cach nhau bang ki tu khoang trang) " << endl;
		for (int j = 0; j < columns; j++) {
			cin >> arr[i][j];
		}
	}
}

//Tác dụng của hàm : Xuất ma trận
void Matrix::output()
{
	//Xuất dữ liệu từng vị trí của ma trận
	cout << "\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (arr[i][j] == -0) //Tránh việc xuất ra -0 làm xấu chương trình
				arr[i][j] = 0;
			cout << arr[i][j] << "\t";
		}
		cout << "\n";
	}
}

//Tác dụng của hàm: Kiểm tra ma trận nhập vào có phải ma trận vuông hay không?
//Output: true nếu ma trận vuông, ngược lại false
bool Matrix::isSquareMatrix()
{
	//Kiểm tra số dòng có = số cột không?
	if (rows == columns) {
		return true;
	}
	return false;
}

//Tác dụng của hàm: Thu nhỏ ma trận (xóa 1 dòng và 1 cột)
//Input: m_row: dòng muốn xóa
//		 m_column: cột muốn xóa
//Output: Ma trận sau khi đã xóa cột row và dòng column
Matrix Matrix::smallerMatrix(int m_row, int m_column)
{
	//Tạo 1 ma trận ít hơn 1 dòng và 1 cột so với ma trận gọi hàm
	Matrix smaller((rows - 1), (columns - 1));

	//Copy các phần tử của ma trận gọi hàm vào ma trận smaller (bỏ các phần tử ở cột i và dòng j)
	for (int i = 0; i < rows - 1; i++) {
		for (int j = 0; j < columns - 1; j++) {
			if (i < m_row) {
				if (j < m_column)
					smaller.arr[i][j] = arr[i][j]; //Copy như bth
				else //j >= m_column
					smaller.arr[i][j] = arr[i][j + 1]; //Bỏ các phần tử của cột j nên dời các phần tử ở cột sau lên
			}
			else { //i >= m_row
				if (j < m_column)
					smaller.arr[i][j] = arr[i + 1][j]; //Bỏ các phần tử của dòng i nên dời các phần tử ở dòng dưới lên
				else //j >= m_column
					smaller.arr[i][j] = arr[i + 1][j + 1]; //Bỏ các phần tử của dòng i cột j nên dời chéo các phần tử ở sau lên
			}

		}
	}
	return smaller;
}

//Tác dụng của hàm: Tính định thức ma trận
//Output: Kết quả 
float Matrix::det()
{
	return det(*this); //Gọi hàm tính định thức với 1 tham số truyền vào (mục đích là để có thể đệ quy được)
}

//Tác dụng của hàm: Tính định thức ma trận
//Input: Ma trận
//Output: Kết quả
float Matrix::det(Matrix m_matrix)
{
	float sum = 0; //kết  quả trả về

	//Ma trận vuông cấp 1: det = arr[0][0]
	if (m_matrix.rows == 1)  return m_matrix.arr[0][0];

	//Ma trận vuông cấp 2: det = arr[1][1]*arr[0][0] - arr[0][1]*arr[1][0]
	if (m_matrix.rows == 2) return (m_matrix.arr[1][1] * m_matrix.arr[0][0] - m_matrix.arr[0][1] * m_matrix.arr[1][0]);

	for (int k = 0; k < m_matrix.rows; k++) {
		//Tạo một ma trận nhỏ hơn 1 cấp để lưu giữ ma trận con sau khi đã bỏ dòng k và cột 0 của ma trận truyền vào

		//Thu nhỏ ma trận sau khi bỏ dòng k, cột 0
		Matrix temp = m_matrix.smallerMatrix(k, 0);

		//Gọi đệ quy cho ma trận bậc n-1 sau khi bỏ dòng k và cột đầu tiên
		//Phần tử 0 của dòng k * (-1)^(k+0) * det(ma trận con sau khi bỏ  dòng k cột 0)
		sum += m_matrix.arr[k][0] * pow(-1, k) * det(temp);
	}
	return sum;
}

//Tác dụng của hàm: Kiểm tra ma trận có khả nghịch hay không (có ma trận nghịch đảo hay không)
//Output: true nếu ma trận khả nghịch, ngược lại false
bool Matrix::checkInvertible()
{
	//Kiểm tra det có khác 0 hay không, nêu det khác 0 trả về true, ngược lại trả về false
	if (det() != 0)
		return true;
	return false;
}

//Tác dụng của hàm: Tìm ma trận nghịch đảo (sau khi đã kiểm tra tính khả nghịch trong hàm menu)
//Output: Ma trận nghịch đảo
Matrix Matrix::inverseMatrix()
{
	float deter = det(); //Kết quả định thức của ma trận ban đầu
	Matrix inverse(rows, columns); //Khởi tạo ma trận nghịch đảo 

	//Truyền các phần tử vào ma trận nghịch đảo
	//Với inverse.arr[i][j] = (-1)^(i+j) * det(ma trận con sau khi bỏ dòng i cột j)
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			inverse.arr[i][j] = pow(-1, i + j) * (smallerMatrix(i, j).det());
		}
	}

	//Chuyển vị của ma trận vừa tính (cột i thành dòng j và ngược lại)
	//Ma trận sau khi chuyển vị là ma trận phụ hợp (adj(matrix))
	for (int i = 0; i < inverse.rows; i++) {
		//Vì các phần tử trên đường chéo giữ nguyên và tránh việc đổi 2 lần ở cùng 1 vị trí => j chạy từ i + 1
		for (int j = i + 1; j < inverse.columns; j++) {
			float temp = inverse.arr[i][j];
			inverse.arr[i][j] = inverse.arr[j][i];
			inverse.arr[j][i] = temp;
		}
	}

	//Nhân ma trận phụ hợp với 1/det để ra ma trận nghịch đảo
	inverse = inverse * (1 / deter);
	return inverse;
}

//Tác dụng của hàm: Tìm hạng của ma trận
//Output: hạng của ma trận
int Matrix::rank()
{
	//Gán ma trận cho 1 ma trận temp để tránh việc thay đổi ma trận
	Matrix temp = *this;
	int max = (temp.rows < temp.columns) ? temp.rows : temp.columns; //Hạng của ma trận không thể lớn hớn rows hoặc columns
	int result = 0; //Hạng ma trận

	for (int i = 0; i < temp.rows; i++) {
		bool flag = false; //Biến kiểm tra dòng có khác 0 hay không
		int j;
		for (j = i; j < temp.columns; j++) {
			//Kiểm tra xem phần tử [i][j] có khác 0 hay không, nếu có thì phần tử đó có tính bán chuẩn hóa trên cột j
			//Nếu = 0, xét phần tử ở cột tiếp theo
			if (temp.arr[i][j] != 0) {
				flag = true; //Cờ bật lên khi dòng i khác 0
				break;
			}
		}

		if (flag == true) { //Nếu dòng i khác 0
			//Đưa phần tử [i][j] về 1
			temp.divrow(i, temp.arr[i][j]);
			//Xét các phần tử bên dưới cột j, biến đổi các phần tử đó = 0
			for (int k = i + 1; k < temp.rows; k++) {
				if (temp.arr[k][j] != 0)
				{
					//Biến đổi sơ cấp trên dòng để đưa phần tử [k][j] = 0
					temp.changerow(k, i, -temp.arr[k][j] / temp.arr[i][j]);
				}
			}
			result++; //Hạng ma trận cộng thêm 1
		}
		//Kiểm tra kết quả có bằng hạng tối đa chưa?
		if (result == max)
			break; //Thoát khỏi vòng lặp để không phải chạy thêm trong trường hợp hạng ma trận đã đạt tối đa
				   //Trường hợp này chỉ xảy ra khi rows > columns 
	}
	return result;
}

//Tác dụng của hàm: Cộng dòng 1 với một số nhân dòng 2
//Input: row1: Dòng 1
//		 row2: Dòng 2
//		 value: số để nhân với dòng 2
void Matrix::changerow(int row1, int row2, float value)
{
	//Cộng từng phần tử của dòng row1 với value*phần tử của dòng row2
	for (int j = 0; j < columns; j++) {
		arr[row1][j] = arr[row1][j] + value * arr[row2][j];
	}
}

//Tác dụng của hàm: Đổi chỗ 2 dòng
//Input: row1: Dòng 1
//		 row2: Dòng 2
void Matrix::swaprow(int row1, int row2)
{
	//Đổi chỗ lần lượt từng vị trí của row1 cho row2 và ngược lại
	for (int j = 0; j < columns; j++) {
		float temp = arr[row1][j];
		arr[row1][j] = arr[row2][j];
		arr[row2][j] = temp;
	}
}

//Tác dụng của hàm: Chia dòng cho 1 số thực
//Input: m_row: Dòng muốn chia
//		 value: số thực để chia
void Matrix::divrow(int m_row, float value)
{
	//Chia lần lượt từng vị trí của m_row cho value
	for (int j = 0; j < columns; j++) {
		arr[m_row][j] = arr[m_row][j] / value;
	}
}

//Tác dụng của hàm: Kiểm tra cột có = 0 hay không?
//Input: m_col: Cột muốn kiểm tra
//Output: True nếu cột = 0, ngược lại false
bool Matrix::isColumn0(int m_col)
{
	//Kiểm tra từng phần tử của m_col có khác 0 hay không
	for (int i = 0; i < rows; i++) {
		if (arr[i][m_col] != 0)
			return false;
	}
	return true;
}

//Tác dụng của hàm: Biến đổi ma trận thành ma trận bậc thang rút gọn
void Matrix::abridgeMatrix()
{
	int k = 0;
	for (int j = 0; j < columns - 1; j++) {//j chỉ chạy tới columns -2 do không chạy vào cột mở rộng của ma trận
		bool flag = false; //Cờ hiệu kiểm tra cột j từ vị trí k xuống vị trí rows -1 có phần tử nào khác 0 hay không
		if (!isColumn0(j)) {//Kiểm tra cột j có khác 0 hay không? Nếu = 0 thì xét cột tiếp theo
			for (; k < rows; k++) {
				if (arr[k][j] != 0) {
					//Nếu cột j từ vị trí k trở xuông có 1 vị trí khác 0
					flag = true;//Cờ hiệu bật
					break;//Thoát khỏi vòng lặp
				}
			}
			if (flag == true) { //Kiểm tra cờ hiệu đã được bật chưa
				if (k != j)//Nếu arr[k][j] # arr[j][j] thì đổi vị trí 2 dòng
					swaprow(k, j);

				//Chuẩn hóa cột j, các vị trí khác a[j][j] biến đổi thành 0
				for (int i = 0; i < rows; i++) {
					if (i == k)
						divrow(k, arr[k][j]);
					else
						changerow(i, j, -arr[i][j] / arr[j][j]); //Biến đổi sơ cấp trên dòng
				}
				k++; //Tăng giá trị cho k
				//Giải thích cho việc k++ mà không gán k = j: 
				// vd. 1 4 5
				//     0 0 2
				//Khi j = 1, k = 1 thì lúc này ma trận vẫn chưa là ma trận bậc thang rút gọn
				//Khi j = 2, k = 2 thì cờ hiệu sẽ không được bật do lúc này k = rows
				//Vì vậy khi nào cờ hiệu được bật thì lúc đó k mới được tăng để tránh trường hợp tương tự
			}
		}
	}
}

//Tác dụng của hàm: Giải hệ phương trình tuyến tính
//Ma trận truyền vào sẽ là ma trận mở rộng của hệ
//5x - 2y + 5z = 3 thì người dùng sẽ nhập là 5 -2 5 3
void Matrix::linearEquation()
{
	Matrix normal(rows, columns - 1); //Khởi tạo ma trận ban đầu (không có cột mở rộng)
									  //5x - 2y + 5z = 3 thì ma trận normal sẽ là 5 -2 5
	//Gán giá trị từ ma trận mở rộng qua ma trận normal (bỏ hàng mở rộng)
	for (int i = 0; i < normal.rows; i++)
		for (int j = 0; j < normal.columns; j++)
			normal.arr[i][j] = arr[i][j];

	int n = 0; //Số ẩn của hệ phương trình
	//Số cột khác 0 của ma trận là số ẩn của hệ phương trình
	for (int j = 0; j < normal.columns; j++) {
		if (!isColumn0(j)) //Kiểm tra cột j có khác 0 hay không? Nếu có thì số ẩn +1
			n++;
	}

	//Hạng của ma trận normal khác hạng của ma trận mở rộng thì phương trình vô nghiệm
	if (rank() != normal.rank()) {
		cout << "He phuong trinh vo nghiem.";
		return;
	}
	else if (rank() == n) {//rank(normal) = rank (mở rộng) = n: hệ có nghiệm duy nhất
		cout << "\nMa tran bac thang rut gon:";
		abridgeMatrix(); //Biến đổi ma trận thành ma trận bậc thang rút gọn
		output();
		cout << "\nHe phuong trinh co he nghiem duy nhat: {";
		for (int i = 0; i < rows; i++) {
			//Mỗi vị trí cuối cùng của dòng của ma trận sau khi biến đổi là 1 nghiệm của hệ nghiệm
			cout << "[" << arr[i][columns - 1] << "] ";
		}
		cout << "}";
	}
	else {//Hệ có vô số nghiệm phụ thuộc n - rank() tham số
		cout << "\nHe phuong trinh co vo so nghiem phu thuoc " << n - rank() << " tham so.";
	}
}

//Tác dụng của hàm: Gán ma trận 1 = ma trận 2
//Input: Ma trận 2
//Output: Ma trận 1 sau khi đã gán bằng ma trận 2
Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other) {// Tránh trường hợp gán bằng chính nó
		for (int i = 0; i < rows; i++) {
			delete[] arr[i]; //Xóa bộ nhớ đã cấp phát cho từng hàng
		}
		delete[] arr; //Xóa bộ nhớ đã cấp phát cho arr

		//Cấp phát lại cho ma trận this
		rows = other.rows;
		columns = other.columns;
		arr = new float* [rows];
		for (int i = 0; i < rows; i++)
			arr[i] = new float[columns];

		//Copy giá trị của ma trận other vào ma trận this
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				arr[i][j] = other.arr[i][j];
	}
	return (*this);
}

//Tác dụng của hàm: Nhân ma trận với 1 số thực
//Input: số thực muốn nhân
//Output: Ma trận sau khi đã nhân với số thực
Matrix& Matrix::operator*(const float num)
{
	//Nhân từng phần tử của ma trận với số num
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			arr[i][j] = arr[i][j] * num;
	return (*this);
}

//Tác dụng của hàm: Nhân 2 ma trận (đã kiểm tra điều kiện số dòng của ma trận 1 = số cột của ma trận 2)
//Input: ma trận 2
//Output: ma trận sau khi đã nhân 2 ma trận với nhau
const Matrix Matrix::operator*(const Matrix& other) const
{
	Matrix temp(rows, other.columns);
	//Phần tử ở vị trí (i,j) của ma trận AB là tích vô hướng của vectơ dòng i của A và vetơ cột j của B
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < other.columns; j++) {
			float rel = 0;
			for (int k = 0; k < columns; k++) {
				rel += arr[i][k] * other.arr[k][j];
			}
			temp.arr[i][j] = rel;
		}
	}

	return temp;
}