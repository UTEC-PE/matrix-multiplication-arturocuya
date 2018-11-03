#include <bits/stdc++.h> 
using namespace std; 

#define MAX 4 

#define MAX_THREAD 4 

int matrix1[MAX][MAX]; 
int matrix2[MAX][MAX]; 
int resultMatrix[MAX][MAX]; 
int step_i = 0; 

void* multiply(void* arg) 
{ 
	int core = step_i++; 

	for (int i = core * MAX / 4; i < (core + 1) * MAX / 4; i++) 
		for (int j = 0; j < MAX; j++) 
			for (int k = 0; k < MAX; k++) 
				resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j]; 
} 

// Driver Code 
int main() 
{ 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) { 
			matrix1[i][j] = rand() % 10; 
			matrix2[i][j] = rand() % 10; 
		} 
	} 

	cout << endl << "Matrix 1" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) cout << matrix1[i][j] << " "; 
		cout << endl; 
	} 
 
	cout << endl << "Matrix 2" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) cout << matrix2[i][j] << " ";		 
		cout << endl; 
	} 

	pthread_t threads[MAX_THREAD]; 

	for (int i = 0; i < MAX_THREAD; i++) { 
		int* p; 
		pthread_create(&threads[i], NULL, multiply, (void*)(p)); 
	} 

	for (int i = 0; i < MAX_THREAD; i++) 
		pthread_join(threads[i], NULL);	 

	cout << endl << "Product" << endl; 
	for (int i = 0; i < MAX; i++) { 
		for (int j = 0; j < MAX; j++) cout << resultMatrix[i][j] << " ";		 
		cout << endl; 
	} 
	return 0; 
} 
