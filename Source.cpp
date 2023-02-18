#include <iostream>
#include <cstdlib> // for rand()
#include <ctime> // for time()
#include <string>
#include <random>
#include <chrono>
#include <map>
#include <cstdio>
const int NUM_DATA = 10000;
struct Data {
	int id;
	std::string name;
	std::string subject;
	int mark;
	float cgpa;
};
void QuickSort(Data data[], int left, int right, int& numSwaps) {
	if (left >= right) {
		return;
	}
	int pivot = data[(left + right) / 2].mark;
	int i = left;
	int j = right;
	while (i <= j) {
		while (data[i].mark < pivot) {
			i++;
		}
		while (data[j].mark > pivot) {
			j--;
		}
		if (i <= j) {
			std::swap(data[i], data[j]);
			numSwaps++; // increment the counter for each swap
			i++;
			j--;
		}
	}
	QuickSort(data, left, j, numSwaps);
	QuickSort(data, i, right, numSwaps);
}
void BubbleSort(Data data[], int n, int& numSwaps) {
	bool swapped;
	do {
		swapped = false;
		for (int i = 0; i < n - 1; i++) {
			if (data[i].mark > data[i + 1].mark) {
				std::swap(data[i], data[i + 1]);
				numSwaps++; // increment the counter for each swap
				swapped = true;
			}
		}
	} while (swapped);
}
void UnsortData(Data data[], int numData) {
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(data, data + numData, g);
}
// Binary search function to search for a student with a specific mark
bool binarySearch(const Data data[], int numElements, int targetMark) {
	int left = 0;
	int right = 99; // search only the first 100 elements of the array
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (data[mid].mark == targetMark) {
			return true; // student with the specified mark found
		}
		else if (data[mid].mark < targetMark) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return false; // student with the specified mark not found
}
//Linear search for marks
bool linearSearch(const Data data[], int numElements, int targetMark) {
	for (int i = 0; i < 100; i++) {
		if (data[i].mark == targetMark) {
			std::cout << "ID: " << data[i].id << ", Name: " << data[i].name
				<< ", Subject: " << data[i].subject << ", Mark: " << data[i].mark
				<< ", CGPA: " << data[i].cgpa << std::endl;
			return true; // student with the specified mark found
		}
	}
	return false; // student with the specified mark not found
}
void ShowSubjectReport(const Data data[], int numData) {
	std::map<std::string, int> subjectCount;
	for (int i = 0; i < numData; i++) {
		subjectCount[data[i].subject]++;
	}
	std::vector<std::string> subjects;
	for (const auto& p : subjectCount) {
		subjects.push_back(p.first);
	}
	// Sort subjects in ascending order by subject number
	std::sort(subjects.begin(), subjects.end(), [](const std::string& a, const std::string& b) {
		int aNum = std::stoi(a.substr(8));
		int bNum = std::stoi(b.substr(8));
		return aNum < bNum;
		});
	std::cout << "Subject, Number of Students Enrolled" << "\n";
	for (const std::string& subject : subjects) {
		int count = subjectCount[subject];
		std::cout << subject << ", " << count << "\n";
	}
}
void ShowSubjectAverageMarks(const Data data[], int numData) {
	std::map<std::string, int> subjectTotalMarks;
	std::map<std::string, int> subjectNumStudents;
	for (int i = 0; i < numData; i++) {
		subjectTotalMarks[data[i].subject] += data[i].mark;
		subjectNumStudents[data[i].subject]++;
	}
	std::vector<std::string> subjects;
	for (const auto& p : subjectTotalMarks) {
		subjects.push_back(p.first);
	}
	// Sort subjects in ascending order by subject number
	std::sort(subjects.begin(), subjects.end(), [](const std::string& a, const std::string& b) {
		int aNum = std::stoi(a.substr(8));
		int bNum = std::stoi(b.substr(8));
		return aNum < bNum;
		});
	std::cout << "Subject, Average Mark" << "\n";
	for (const std::string& subject : subjects) {
		int totalMarks = subjectTotalMarks[subject];
		int numStudents = subjectNumStudents[subject];
		float averageMark = static_cast<float>(totalMarks) / numStudents;
		std::cout << subject << ", " << averageMark << "\n";
	}
}
int main() {
	// Create an array of Data structures
	Data data[NUM_DATA];
	// Generate random data for each element in the array
	for (int i = 0; i < NUM_DATA; i++) {
		data[i].id = i + 1;
		data[i].name = "Student " + std::to_string(i + 1);
		data[i].subject = "Subject " + std::to_string(std::rand() % 10 + 1);
		data[i].mark = std::rand() % 101; // random mark between 0 and 100
		data[i].cgpa = static_cast<float>(std::rand()) / RAND_MAX * 4; // random float between 0 and 4
	}
	while (true) {
		system("CLS");
		int choice;
		std::cout << "Student Information System" << "\n";
		std::cout << "----------------------------" << "\n";
		std::cout << "1. Sort using Quick Sort." << "\n";
		std::cout << "2. Sort using Bubble Sort." << "\n";
		std::cout << "3. Search using Linear Search." << "\n";
		std::cout << "4. Search using Binary Search." << "\n";
		std::cout << "5. Calculate the average mark for all subjects." << "\n";
		std::cout << "6. Show a report of subjects enrolled." << "\n";
		std::cout << "7. Exit." << "\n";
		std::cout << "Please choose an option: ";
		std::cin >> choice;
		int numSwaps = 0;
		// Seed the random number generator with the current time
		std::srand(std::time(0));
		UnsortData(data, NUM_DATA);
		if (choice == 1)
		{
			std::cin.ignore();
			// Print the first 100 data
			std::cout << "Quick Sort:" << std::endl;
			auto start = std::chrono::system_clock::now();
			QuickSort(data, 0, NUM_DATA - 1, numSwaps);
			for (int i = 0; i < 100; i++) {
				std::cout << "ID: " << data[i].id << ", Name: " << data[i].name << ", Subject: "
					<< data[i].subject
					<< ", Mark: " << data[i].mark << ", CGPA: " << data[i].cgpa << std::endl;
			}
			std::cout << "Total number of swaps: " << numSwaps << std::endl;
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::cout << "Total elapsed time: " << elapsed_seconds.count() << "s\n";
			std::cout << "--------------------------------------------------------------------------------------------"
				<< std::endl;
			std::cout << "Press any key to continue...";
			getchar();
			UnsortData(data, NUM_DATA);
		}
		else if (choice == 2)
		{
			std::cin.ignore();
			std::cout << "Bubble Sort:" << std::endl;
			auto start = std::chrono::system_clock::now();
			BubbleSort(data, NUM_DATA, numSwaps);
			for (int i = 0; i < 100; i++) {
				std::cout << "ID: " << data[i].id << ", Name: " << data[i].name << ", Subject: "
					<< data[i].subject
					<< ", Mark: " << data[i].mark << ", CGPA: " << data[i].cgpa << std::endl;
			}
			std::cout << "Total number of swaps: " << numSwaps << std::endl;
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::cout << "Total elapsed time: " << elapsed_seconds.count() << "s\n";
			std::cout << "--------------------------------------------------------------------------------------------"
				<< std::endl;
			std::cout << "Press any key to continue...";
			getchar();
		}
		else if (choice == 3)
		{
			std::cin.ignore();
			// Test the linear search function
			int targetMark;
			std::cout << "Please insert the Student mark: ";
			std::cin >> targetMark;
			std::cout << "\n";
			auto start = std::chrono::system_clock::now();
			if (linearSearch(data, NUM_DATA, targetMark)) {
				std::cout << "Student with mark " << targetMark << " found." << std::endl;
				std::cin.ignore();
				auto end = std::chrono::system_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - start;
				std::cout << "Total elapsed time: " << elapsed_seconds.count() << "s\n";
				std::cout << "Press any key to continue...";
				getchar();
			}
			else {
				std::cout << "Student with mark " << targetMark << " not found." << std::endl;
				std::cin.ignore();
				auto end = std::chrono::system_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - start;
				std::cout << "Total elapsed time: " << elapsed_seconds.count() << "s\n";
				std::cout << "Press any key to continue...";
				getchar();
			}
		}
		else if (choice == 4)
		{
			std::cin.ignore();
			// Test the binary search function
			QuickSort(data, 0, NUM_DATA - 1, numSwaps);
			int targetMark;
			std::cout << "Please insert the Student Mark: ";
			std::cin >> targetMark;
			std::cout << "\n";
			auto start = std::chrono::system_clock::now();
			if (binarySearch(data, NUM_DATA, targetMark)) {
				std::cout << "Student with mark " << targetMark << " found." << std::endl;
				std::cin.ignore();
				auto end = std::chrono::system_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - start;
				std::cout << "Total elapsed time: " << elapsed_seconds.count() << "s\n";
				std::cout << "Press any key to continue...";
				getchar();
			}
			else {
				std::cout << "Student with mark " << targetMark << " not found." << std::endl;
				std::cin.ignore();
				auto end = std::chrono::system_clock::now();
				std::chrono::duration<double> elapsed_seconds = end - start;
				std::cout << "Total elapsed time: " << elapsed_seconds.count() << "s\n";
				std::cout << "Press any key to continue...";
				getchar();
			}
		}
		else if (choice == 5)
		{
			std::cin.ignore();
			ShowSubjectAverageMarks(data, NUM_DATA);
			std::cout << "Press any key to continue...";
			getchar();
		}
		else if (choice == 6)
		{
			std::cin.ignore();
			ShowSubjectReport(data, NUM_DATA);
			std::cout << "Press any key to continue...";
			getchar();
		}
		else if (choice == 7)
		{
			break;
		}
		else
		{
			std::cout << "Wrong input" << "\n";
		}
	}
	return 0;
}