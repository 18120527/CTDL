#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

long Binary(int num); 
string Add0(string src, int quantity);
vector<vector<string>> FirstGroupping(vector<string> src, int variables);
void SecondGroupping(vector<vector<string>> src, vector<string>& result);
int checkDifPos(string s1, string s2);
bool checkSame(string s1, string s2);
vector<vector<string>> FinalStep(vector<string> src, vector<string> initStr);
void Application(vector <int> arr, int variables);
