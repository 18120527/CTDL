#include "Bool.h"

//Tác dụng hàm: chuyển đổi từ số thập phân về nhị phân
//Input: num: số thập phân
//Output: số nhị phân
long Binary(int num)
{
	long temp;
	if (num == 0)
		return 0;
	else
		temp = num % 2;
	return Binary(num / 2) * 10 + temp;
}

//Tác dụng hàm: thêm các số 0 vào đầu chuỗi số nhị phân cho đủ byte
//Input: src: chuỗi số nhị phân
//		 quantity: số lượng số 0 thêm vào
//Output: chuỗi số nhị phân sau khi đã thêm đủ số lượng số 0 vào đầu
string Add0(string src, int quantity)
{
	string temp;
	int pos = 0;
	//Thêm các số 0 vào chuỗi temp
	for (; pos < quantity; pos++) {
		temp.insert(pos, "0");
	}
	//Thêm chuỗi src vào cuối chuỗi temp để hoàn thành chuỗi số nhị phân
	temp.insert(pos, src);
	return temp;
}

//Tác dụng hàm: Gộp nhóm lần đầu tiên (các chuỗi nhị phân có cùng số lượng số '1' sẽ vào 1 nhóm)
//Input: src: chuỗi số nhị phân
//		 variables: số biến của hàm bool
//Output: Mảng 2 chiều chứa các nhóm
vector<vector<string>> FirstGroupping(vector<string> src, int variables)
{
	vector<vector<string>> temp;
	temp.resize(variables + 1); //Độ rộng vector tối đa bằng số lượng biến + 1
	//Gộp nhóm các chuỗi nhị phân
	for (int i = 0; i < src.size(); i++) {
		int count = 0;
		for (int j = 0; j < src[i].length(); j++) {
			if (src[i][j] == '1')
				count++;
		}
		//Thêm vào cuối vector có cùng số lượng số 1
		temp[count].push_back(src[i]);
	}

	//Loại bỏ các vị trí không có phần tử nào (vd: không có chuỗi nào chứa 0 số '1', loại bỏ vị trí 0)
	for (int i = 0; i < temp.size();) {
		if (temp[i].empty()) {
			temp.erase(temp.begin() + i);
		}
		else
			i++;
	}
	return temp;
}

//Tác dụng hàm: Gộp nhóm cho ra các mảng
//Input: src: chuỗi số nhị phân
//		 result: mảng chứa những chuỗi còn lại sau khi đã loại bỏ bớt
void SecondGroupping(vector<vector<string>> src, vector<string>& result)
{
	if (src.size() == 1) {
		//Thêm tất cả chuỗi nhị phân còn lại vào result
		for (int j = 0; j < src[0].size(); j++)
			result.push_back(src[0][j]);
		return;
	}

	vector<vector<string>> tempArr; //Mảng tạm
	tempArr.resize(src.size() - 1);
	vector<int> current; //lưu trữ những phần tử đã được đánh dấu ở mảng hiện tại
	vector<int> next; //lưu trữ những phần tử đã được đánh dấu ở mảng tiếp theo

	for (int i = 0; i < src.size() - 1; i++) {
		if (i != 0) {
			current = next; //Lưu những vị trí đã được đánh dấu của mảng tiếp theo ở vòng lặp trước
			next.clear();//Làm rỗng
		}
		//Kiểm tra các vị trí của mảng hiện tại với các vị trí của mảng tiếp theo
		for (int j = 0; j < src[i].size(); j++) {
			for (int k = 0; k < src[i + 1].size(); k++) {
				//pos lưu trữ vị trí khác nhau
				int pos = checkDifPos(src[i][j], src[i + 1][k]);
				if (pos != -1) { //Có đúng 1 vị trí khác nhau
					string temp = src[i][j];
					temp[pos] = '-'; //Vị trí khác nhau duy nhất kí hiệu dấu "-"
					tempArr[i].push_back(temp); //thêm vào mảng tạm
					current.push_back(j); //Đánh dấu những phần tử ở mảng hiện tại đã gộp nhóm được
					next.push_back(k); //Đánh dấu những phần tử ở mảng tiếp theo đã gộp nhóm được
				}
			}
		}

		if (!current.empty()) {
			//Kiểm tra các phần tử trong mảng hiện tại đã được đánh dấu hết chưa
			for (int j = 0; j < src[i].size(); j++) {
				bool check = false;
				for (int k = 0; k < current.size(); k++) {
					if (j == current[k]) { //Đã có đánh dấu
						check = true;
						break;
					}
				}
				if (check == false) {//Chưa đánh dấu
					result.push_back(src[i][j]); //thêm chuỗi nhị phân chưa đánh dấu vào mảng result
				}
			}
		}
		else {
			for (int j = 0; j < src[i].size(); j++)
				result.push_back(src[i][j]); //thêm chuỗi nhị phân chưa đánh dấu vào result
		}

	}//end for i

	if (tempArr[0].empty())
	{
		for (int i = 0; i < src.size(); i++) {
			for (int j = 0; j < src[i].size(); j++) {
				result.push_back(src[i][j]);
			}
		}
		return;
	}

	//Thêm các phần tử chưa được đánh dấu của mảng cuối cùng vào result
	if (!next.empty()) {
		for (int j = 0; j < src[src.size() - 1].size(); j++) {
			bool check = false;
			for (int k = 0; k < next.size(); k++) {
				if (j == next[k]) { //Đã có đánh dấu
					check = true;
					break;
				}
			}
			if (check == false) {//Chưa đánh dấu
				result.push_back(src[src.size() - 1][j]); //thêm chuỗi nhị phân chưa đánh dấu vào result
			}
		}
	}
	else {
		for (int j = 0; j < src[src.size() - 1].size(); j++)
			result.push_back(src[src.size() - 1][j]); //thêm chuỗi nhị phân chưa đánh dấu vào result
	}

	//Loại bỏ mảng rỗng
	for (int i = 1; i < tempArr.size();) {
		if (tempArr[i].empty()) {
			tempArr.erase(tempArr.begin() + i);
		}
		else
			i++;
	}

	//Xóa các phần tử giống nhau ra khỏi mảng
	for (int i = 0; i < tempArr.size(); i++) {
		for (int j = 0; j < tempArr[i].size() - 1; j++) {
			for (int k = j + 1; k < tempArr[i].size();) {
				if (tempArr[i][j] == tempArr[i][k]) {
					tempArr[i].erase(tempArr[i].begin() + k);
				}
				else
					k++;
			}
		}
	}
	//Đệ quy với số phần tử ít hơn
	SecondGroupping(tempArr, result);
}

//Tác dụng hàm: Kiểm tra 2 chuỗi có đúng 1 vị trí khác nhau
//Input: s1, s2: chuỗi 1 và chuỗi 2
//Output: vị trí khác nhau duy nhất của 2 chuỗi
int checkDifPos(string s1, string s2)
{
	int count = 0, pos = -1;
	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] != s2[i]) {
			if (count == 0) { //Chưa có vị trí nào trước đó khác nhau, gán pos = vị trí hiện tại, tăng biến đếm
				pos = i;
				count++;
			}
			else { //Có nhiều hơn 1 vị trí khác nhau, gán pos = -1 và thoát khỏi vòng lặp
				pos = -1;
				break;
			}
		}
	}
	return pos;
}

//Tác dụng hàm: Kiểm tra 2 chuỗi có giống nhau hay không (trừ vị trí có chứa kí tự "-")
//Input: s1, s2: chuỗi 1 và chuỗi 2
//Output: true: nếu đúng
//        false: nếu sai
bool checkSame(string s1, string s2)
{
	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] != '-' && s1[i] != s2[i])
			return false;
	}
	return true;
}

//Tác dụng hàm: Bước cuối cùng của thuật toán (tìm ra các công thức tối tiểu)
//Input: src: các chuỗi đã gộp nhóm
//		 initStr: chuỗi số ban đầu 
//Output: các công thức tối tiểu
vector<vector<string>> FinalStep(vector<string> src, vector<string> initStr)
{
	//Đếm các vị trí của chuỗi số ban đầu được bao nhiêu chuỗi trong src chứa
	vector<int> count(initStr.size(), 0);
	for (int i = 0; i < src.size(); i++) {
		for (int j = 0; j < initStr.size(); j++) {
			if (checkSame(src[i], initStr[j])) {
				count[j]++;
			}
		}
	}

	vector<string> temp0 = src;
	vector<string> permanent; //Giữ những chuỗi bắt buộc phải có
	//Xóa chuỗi chứa số được đánh dấu 1 lần ra khỏi src và thêm vào permanent
	for (int i = 0; i < count.size(); i++) {
		if (count[i] == 1) {
			for (int j = 0; j < src.size();) {
				if (checkSame(src[j], initStr[i])) {
					permanent.push_back(src[j]);
					src.erase(src.begin() + j);
					break;
				}
				else j++;
			}
		}
	}

	//Xóa những số được chứa bởi các chuỗi trong permanent ra khỏi initStr
	for (int i = 0; i < permanent.size(); i++) {
		for (int j = 0; j < initStr.size();) {
			if (checkSame(permanent[i], initStr[j]))
				initStr.erase(initStr.begin() + j);
			else j++;
		}
	}

	vector<vector<string>> result; //Mảng 2 chiều chứa các công thức tối tiểu
	for (int i = 0; i < src.size(); i++) {
		vector<string> temp; //chứa công thức tối tiểu (bao gồm các chuỗi)
		vector <string> tempInitStr = initStr; //mảng tạm chứa các số tránh thay đổi
		temp.push_back(src[i]);// thêm chuỗi đang xét vào temp

		//Xóa những số được chứa bỏi chuỗi đang xét
		for (int k = 0; k < tempInitStr.size();) {
			if (checkSame(src[i], tempInitStr[k]))
				tempInitStr.erase(tempInitStr.begin() + k);
			else k++;
		}
		if (!tempInitStr.empty()) { //Kiểm tra xem đã đánh dấu hết tất cả các số chưa
									//Nếu còn số chưa đánh dấu, ghép với các chuỗi tiếp theo đến khi hết thì dừng
			for (int j = i + 1; j < src.size(); j++) {
				if (i != j) {
					for (int k = 0; k < tempInitStr.size();) {
						if (checkSame(src[j], tempInitStr[k])) {
							tempInitStr.erase(tempInitStr.begin() + k);
							temp.push_back(src[j]);
							if (tempInitStr.empty())
								break;
						}
						else k++;
					}
				}
			}
		}
		if (tempInitStr.empty()) //Tất cả các số đã được đánh dấu
			result.push_back(temp); //Thêm công thức tối tiểu vào mảng các công thức tối tiểu
	}//end for i

	//Loại bỏ những công thức dài và thêm các chuỗi cố định vào công thức đó
	if (!result.empty()) {
		int min = result[0].size();
		for (int i = 1; i < result.size(); i++) {
			if (result[i].size() < min)
				min = result[i].size();
		}

		for (int i = 0; i < result.size();) {
			if (result[i].size() > min) {
				result.erase(result.begin() + i);
			}
			else i++;
		}

		for (int i = 0; i < result.size(); i++) {
			for (int j = 0; j < permanent.size(); j++) {
				result[i].push_back(permanent[j]);
			}
		}
	}
	else result.push_back(permanent);

	return result;
}

//Tác dụng hàm: Thực hiện tìm công thức tối tiểu hàm bool
//Input: arr: chuỗi số nhập vào
//		 variables: số biến
void Application(vector <int> arr, int variables)
{
	vector <string> arrS1;
	arrS1.resize(arr.size());

	//Chuyển đổi chuỗi số nguyên thành nhị phân
	for (int i = 0; i < arr.size(); i++) {
		arrS1[i] = to_string(Binary(arr[i]));
	};

	//Thêm số không vào chuỗi nhị phân cho đủ số byte
	for (int i = 0; i < arrS1.size(); i++) {
		if (arrS1[i].length() < variables) {
			arrS1[i] = Add0(arrS1[i], variables - arrS1[i].length());
		}
	}

	//Gộp nhóm lần đầu
	vector<vector<string>> arrS2 = FirstGroupping(arrS1, variables);
	vector<string> result;

	//Tiếp tục gộp nhóm
	SecondGroupping(arrS2, result);
	//Xóa các phần tử giống nhau ra khỏi result
	for (int i = 0; i < result.size(); i++) {
		for (int j = i + 1; j < result.size() - 1;) {
			if (result[i] == result[j]) {
				result.erase(result.begin() + j);
			}
			else
				j++;
		}
	}

	//Tìm ra các công thức tối tiểu
	vector<vector<string>> FinalResult = FinalStep(result, arrS1);
	//Xuất các công thức tối tiểu
	for (int i = 0; i < FinalResult.size(); i++) {
		for (int j = 0; j < FinalResult[i].size(); j++)
			cout << FinalResult[i][j] << " ";
		cout << endl;
	}
}