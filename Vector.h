#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Vector
{
private:
	vector<float> v;
	int size;
public:
	Vector(); //Hàm tạo mặc định
	Vector(int _size); //Hàm tạo với tham số là độ rộng của vector
	void Input(); //Hàm nhập
	void Output(); //Hàm xuất
	Vector Addvector(const Vector other)const; //Hàm cộng 2 vector
	Vector MulAlpha(const float alpha)const; //Hàm nhân vector với 1 số
	int getSize(); //Lấy số phần tử của vector
};