#include "Vector.h"

//Tác dụng của hàm: Tạo vector mặc định
Vector::Vector()
{
	size = 0;
}

//Tác dụng của hàm: Tạo vector với tham số truyền vào là độ rộng vector
//Input: _size: độ rộng vector
Vector::Vector(int _size)
{
	v.resize(_size);
	size = _size;
}

//Tác dụng của hàm: Nhập vector
void Vector::Input()
{
	//Nhập số phần tử của vector
	cout << "Nhap so phan tu cua vector: ";
	cin >> size;
	v.resize(size);

	//Nhập giá trị cho từng vị trí của vector
	cout << "Nhap cac phan tu cua vector (moi phan tu cach nhau boi dau khoang trang) :\n";
	for (int i = 0; i < size; i++) {
		cin >> v[i];
	}
}

//Tác dụng của hàm: Xuất vector
void Vector::Output()
{
	//Xuất giá trị cho từng vị trí của vector
	for (int i = 0; i < size; i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

//Tác dụng của hàm: Cộng 2 vector với nhau (2 vector phải cùng độ rộng)
//Input: other: Vector để cộng với nhau
//Output: Vector sau khi đã cộng 2 vector với nhau
Vector Vector::Addvector(const Vector other) const
{
	Vector temp(size);
	//Cộng từng vị trí của 2 vector
	for (int i = 0; i < temp.size; i++) {
		temp.v[i] = v[i] + other.v[i];
	}
	return temp;
}

//Tác dụng của hàm: Nhân vector với 1 số
//Input: alpha: số để nhân
//Output: Vector sau khi đã nhân với alpha
Vector Vector::MulAlpha(const float alpha) const
{
	Vector temp(size);
	//Nhân từng vị trí của vector với alpha
	for (int i = 0; i < temp.size; i++) {
		temp.v[i] = v[i] * alpha;
	}
	return temp;
}

//Tác dụng của hàm: Lấy số phần tử của vector
//Output: size
int Vector::getSize()
{
	return size;
}