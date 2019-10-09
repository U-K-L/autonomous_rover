#pragma once
#include "Arduino.h"

template<typename T, std::size_t N, std::size_t M>
class matrix {
public:
	double mat[N][M];
	int n;
	int m;

	matrix() {};
	matrix(T(&a)[N][M]) {
		n = N;
		m = M;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				mat[i][j] = a[i][j];
			}
		}
	};
	//Sets up the matrix by inserting values given.
	void setup(T(&a)[N][M]) {
		n = N;
		m = M;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				mat[i][j] = a[i][j];
			}
		}
	}

	//Sends the values as a serialized string.
	String serialize() {
		for (int i = 0; i < N; i++) {
			Serial.printf("\n[");
			for (int j = 0; j < M; j++) {
				Serial.printf("%f ", mat[i][j]);
			}
			Serial.printf("]");
		}

	}

	matrix operator * (matrix matr) {
		double elements[N][M] = { 0 };
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				for (int k = 0; k < M; k++) {
					elements[i][j] += mat[i][k] * matr.mat[k][j];
				}
			}
		}
		matrix<double, (int)3, (int)3> newMatrix = matrix<double, (int)3, (int)3>(elements);
		return newMatrix;
	}

	/*
	*/
};
/*
class matrix3X3 : public matrix {
public:
	double matrix[3][3];
	matrix3X3(m[3][3]) {
		n = 3;
		m = 3;
		matrix = m;
	}


};

class matrix4X4 : public matrix {
public:
	double matrix[4][4];
	matrix4X4(m[4][4]) {
		n = 4;
		m = 4;
		matrix = m;
	}

};
*/