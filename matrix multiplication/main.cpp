#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>

std::mutex m_lock;

int step_iter = 0;

int** matrix_create(int n, int m) {
	//создание массива 
	int** matrix = new int* [n];
	for (int row = 0; row < n; row++) {
		matrix[row] = new int[m];
	}

	//заполнение массива
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < m; col++) {
			matrix[row][col] = 1+ (rand() % 100);
		}
	}
	return matrix;
}

void matrix_mult(int** matrix_a, int** matrix_b, int** matrix_c, int n, int m, int a, int b, std::thread::id id) {

	int row = step_iter++;
	if (row < n) { 	
		for (int col = 0; col < b; col++) {
			if (id != std::this_thread::get_id()) {				
				for (int inner = 0; inner < a; inner++) {
					m_lock.lock();
					matrix_c[row][col] += matrix_a[row][inner] * matrix_b[inner][col];
					std::cout << "Processing matrix[" << row << " " << col << "] by " << std::this_thread::get_id() << " value = " << matrix_c[row][col] << std::endl;
					m_lock.unlock();
				}
			} else
				col++;				
		}		
	}
}

int** res_matrix_create(int n, int b) {
	int** matrix_c = new int* [n];


	for (int row = 0; row < n; row++) {
		matrix_c[row] = new int[b];
	}

	for (int row = 0; row < n; row++) {
		for (int col = 0; col < b; col++) {
			matrix_c[row][col] = 0;
		}
	}

	return matrix_c;
}

void output_matrix(int** matrix_c, int n, int b) {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < b; col++) {
			std::cout << matrix_c[row][col] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void destroyer(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;

}

int main() {
	//объявление переменных
	int n, m, a, b;
	//Текстовая информация и ввод размеров массива
	do {
		std::cout << "Enter matrix size for A: " << std::endl;
		std::cout << "Enter rows ";
		std::cin >> n;
		std::cout << "Enter cols ";
		std::cin >> m;
		std::cout << "Enter matrix size for B: " << std::endl;
		std::cout << "Enter rows ";
		std::cin >> a;
		std::cout << "Enter cols ";
		std::cin >> b;
		if (m != a)
			std::cout << "rows a must be equal cols!!!\n" << std::endl;
	} while (m != a);
	
	//Матрица А
	int** matrix_a = matrix_create(n, m);
	//Матрица B
	int** matrix_b =matrix_create(a, b);
	//Результирующая матрица
	int** matrix_c = res_matrix_create(n, b);


	unsigned int start_time = clock();
	int THREAD_NUM = n*b;
	std::thread *th = new std::thread[THREAD_NUM];
	
	for (int i = 0; i < THREAD_NUM; i++) {
		th[i] = std::thread(matrix_mult, matrix_a, matrix_b, matrix_c, n, m, a, b, std::this_thread::get_id());
	}
	for (int i = 0; i < THREAD_NUM; i++) {
		th[i].join();
	}

	//конец подсчёта времени
	unsigned int end_time = clock();

	//рассчёт времени работы программы
	unsigned int elapsed_time = (end_time - start_time) / (double) (CLOCKS_PER_SEC / 1000);
	std::cout << "\nMatrix: " << std::endl;
	output_matrix(matrix_c, n, b);
	std::cout << "Multithread: " << std::endl;
	std::cout << "Elapsed time = " << elapsed_time << " ms" << std::endl;
	std::cout << "Elapsed time = " << static_cast<float>(elapsed_time) / 1000 << " s" << std::endl;

	destroyer(matrix_a, n);
	destroyer(matrix_b, a);
	destroyer(matrix_c, n);

	return 0;
}

