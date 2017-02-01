#ifndef MATRIX_H
	#define MATRIX_H

enum SpecialMatrix{
	TRANSLATION,
	ROTATION,
	SCALING
};

class Matrix{
public:
	Matrix(){ data=nullptr; numOfCol=0; numOfRow=0; };
	inline Matrix(const int& _numOfRow, const int& _numOfCol): numOfRow(_numOfRow), numOfCol(_numOfCol){
			data = makeData(numOfRow, numOfCol);
	}

	Matrix(const Matrix& m);

	Matrix(const SpecialMatrix& type);
	float** makeData(const int& _numOfCol, const int& _numOfRow);

	~Matrix();

	inline int getRowNum(){ return numOfRow; };
	inline int getColNum(){ return numOfCol; };

	void makeTranslationMatrix(const float& x, const float& y);
	void makeRotationMatrix(const float& alpha, const float& x, const float& y);
	void makeScalingMatrix(const float& alpha_x, const float& alpha_y );
	
	Matrix operator*(const Matrix& rhs)const; 
	inline float* operator[](const int& index){return data[index]; }
	inline float* operator[](const int& index)const {return data[index]; }

	// for debugging
	void print()const;


	
protected:

private:
	float** data;
	int numOfRow;
	int numOfCol;

	void clearData();
	void destroyData();
	void makeIdentiy();
};



	#endif