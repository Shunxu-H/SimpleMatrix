/*
TO DO:
1. disable constructor that takes a float**, handle it internally please
2. dealocate data please
*/

#include <iostream>
#include <cstring>
#include <ctgmath>
#include "Matrix.h"




Matrix::Matrix(const Matrix& m){
	numOfRow = m.numOfRow;
	numOfCol = m.numOfCol;
	data = makeData(numOfRow, numOfCol);

	for (int rowPtr = 0; rowPtr < numOfRow; rowPtr++)	
		memcpy(data[rowPtr], m.data[rowPtr], sizeof(float)*numOfCol);

}

float** Matrix::makeData(const int& _numOfRow, const int& _numOfCol){
	float** ret = new float*[numOfCol];
	for (int colCnt = 0; colCnt < numOfCol; colCnt++)
		ret[colCnt] = new float[numOfRow];

	return ret;
}


Matrix::~Matrix(){
	if (data != nullptr){
		destroyData();
	}
}

void Matrix::destroyData(){
	if (data != nullptr){
		for (int rowCnt = 0; rowCnt < numOfRow; rowCnt++){
			delete[] (data[rowCnt]);
		}
		delete[] (data);
	}
}

void Matrix::clearData(){
	if (data != nullptr)
		for (int rowCnt = 0; rowCnt < numOfRow; rowCnt++)
			for (int colCnt = 0; colCnt < numOfCol; colCnt++)
				data[rowCnt][colCnt] = 0;
}

Matrix Matrix::operator*(const Matrix& rhs)const{
	if ( numOfCol != rhs.numOfRow){
		std::cerr << "matrixes' formats do not match" << std::endl;
		return Matrix();
	}

	Matrix m(this->numOfRow, rhs.numOfCol);

	for ( int thisRowPtr = 0; thisRowPtr < numOfRow; thisRowPtr++){
		for ( int rhsColPtr = 0; rhsColPtr < rhs.numOfCol; rhsColPtr++){
			float temp = 0;
			for ( int rhsRowPtr = 0; rhsRowPtr < rhs.numOfRow; rhsRowPtr++){
				temp += (*this)[thisRowPtr][rhsRowPtr]*rhs[rhsRowPtr][rhsColPtr];
			}
			m[thisRowPtr][rhsColPtr] = temp;
		}
	}
	return m;
}

void Matrix::makeIdentiy(){
	if (numOfCol != numOfRow){
		std::cerr << "Non square matrix defined in Matrix::makeIdentiy();" << std::endl;
		return;
	}
	else if (data == nullptr){
		data = makeData(numOfCol, numOfRow);
	}

	for ( int i = 0; i < numOfCol; i++)
		data[i][i] = 1;
}

void Matrix::makeTranslationMatrix(const float& x, const float& y){
	destroyData();
	numOfCol = 3;
	numOfRow = 3;

	data = makeData(numOfCol, numOfRow);
	clearData();
	makeIdentiy();

	data[0][2] = x;
	data[1][2] = y;
}

void Matrix::makeRotationMatrix(const float& alpha, const float& x, const float& y){
	destroyData();
	numOfCol = 3;
	numOfRow = 3;

	data = makeData(numOfCol, numOfRow);
	clearData();
	//makeIdentiy();

	float cosAlpha = cos(alpha);
	float sinAlpha = sin(alpha);

	data[0][0] = cosAlpha; 
	data[0][1] = -sinAlpha;
	data[0][3] = -x*cosAlpha + y*sinAlpha + x;

	data[1][0] = sinAlpha; 
	data[1][1] = cosAlpha;
	data[1][2] = -x*sinAlpha - y*cosAlpha + y;
	
	data[2][0] = 0;
	data[2][1] = 0;
	data[2][2] = 1;
	
	// data[0][0] = cosAlpha; 
	// data[0][1] = -sinAlpha;
	// data[0][3] = 0;
	// data[1][0] = sinAlpha; 
	// data[1][1] = cosAlpha;
	// data[1][2] = 0;
	// data[2][2] = 1;


	//data[0][2] = x;
	//data[1][2] = y;


}

void Matrix::makeScalingMatrix(const float& alpha_x, const float& alpha_y ){
	destroyData();
	numOfCol = 3;
	numOfRow = 3;

	data = makeData(numOfCol, numOfRow);
	clearData();
	//makeIdentiy();

	data[0][0] = alpha_x; 
	data[1][1] = alpha_y;
	data[2][2] = 1;
}

Matrix::Matrix(const SpecialMatrix& type){
	if (type == TRANSLATION){

	}
	else if (type == SCALING){

	}
	else if (type == ROTATION){

	}
} 

void Matrix::print()const
{
	if (data != nullptr)
		for (int colCnt = 0; colCnt < numOfCol; colCnt++){
			for (int rowCnt = 0; rowCnt < numOfRow; rowCnt++){
				std::cout << data[colCnt][rowCnt] << " ";
			}
			std::cout << std::endl;
		}

	std::cout << std::endl;
}
