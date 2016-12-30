// Nơi chứa các hàm hướng thủ tục.

#ifndef __UTILS_H__
#define __UTILS_H__

#include <d3dx9.h>
#include <string>
#include <vector>
#include "define.h"
using namespace std;

// Kiểm tra hai hình chữ nhật có chồng lên nhau không.
// Dùng trong hệ top left
bool isIntersectd(RECT rect1, RECT rect2);

bool isIntersectedInGame(RECT rect1, RECT rect2);

// Kiểm tra rect1 có chứa rect2 không.
bool isContains(RECT rect1, RECT rect2);


// Tính khoảng cách giữa hai điểm
float getdistance(D3DXVECTOR2 p1, D3DXVECTOR2 p2);

std::vector<std::string> splitString(const std::string& input, char seperate);

//	Kiểm tra điểm có nằm trong hcn hay ko
bool isContain(RECT rect, D3DXVECTOR2 point);

double CalculateCoefficient(int n, int k);

#endif // !__UTILS_H__
