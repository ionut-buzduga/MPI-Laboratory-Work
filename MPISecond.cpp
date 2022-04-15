//Laboratory 1

//1. Write a program that prints all the prime numbers less than N using M processes.
//2. Write a program that searches an element inside an array and prints its position in case the array
//contains that element, otherwise it prints 'Not found.'
//3. Let there be n processes.Each process generates m(m >= 100) random numbers(<= 1000), prints
//them to the console, computes their sumand prints it to the console.Determine the time it takes for
//each process to complete the job.

//1.

//#include <iostream>
//#include "mpi.h"
//
//using namespace std;
//
//int main()
//{
//	int rank, size;
//	int v[100];
//	mpi_status status;
//
//	mpi_init(null, null);
//
//	mpi_comm_rank(mpi_comm_world, &rank);
//	mpi_comm_size(mpi_comm_world, &size);
//
//	if (rank == 0)                     //create the array if the proccess's rank is 0(master)
//	{
//		for (int it = 1; it <= 30; it++) v[it] = it;
//
//		int k = 1;
//
//		for (int it = 1; it < size; it++)
//		{
//			mpi_send(&v[k], 5, mpi_int, it, 1, mpi_comm_world);   //send 5 elements in each proccess and update k in v[k] in order to send the entire array
//			k = k + 5;
//		}
//	}
//
//	if (rank != 0)    //rank is slave
//	{
//		mpi_recv(&v, 5, mpi_int, 0, 1, mpi_comm_world, &status);   //receive the 5 values in v
//		int index, j, nr = 0;
//		bool flag;
//		for (index = v[0]; index <= v[4]; index++)                 //operate the searching prime numbers algorithm on it
//		{
//			flag = true;
//			for (j = 2; j < index; j++)
//			{
//				if (index % j == 0)
//				{
//					flag = false;
//				}
//			}
//			if (flag == true && index != 1)
//			{
//				cout << index << endl;
//				nr++;
//			}
//		}
//		if (nr == 0) cout << "no prime numbers!";                   //print the final results
//	}
//	mpi_finalize();
//}


//2.

//#include<iostream>
//#include<mpi.h>
//
//
//using namespace std;
//
//
//int main() {
//
//	int rank, size;
//	int v[30];
//	
//	int N = 20;
//	MPI_Status status;
//
//	MPI_Init(NULL, NULL);
//
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//
//	
//	for (int i = 0; i < 20; i++) {     //create the array
//		v[i] = i;
//	}
//
//	if (rank == 0) {
//		int array[3];
//
//		int findNumber = 12;           //element to search
//		int range = size - 1;          //variable used to compute range of each proccess
//		for (int i = 1; i < size; i++) {
//			array[0] = (i - 1) * range;    //lower bound of proccess range
//			array[1] = range * i - 1;      //upper bound of proccess range
//			array[2] = findNumber;        
//			MPI_Send(&array, 3, MPI_INT, i, 1, MPI_COMM_WORLD);   //transmit the values from above to the other proccesses
//		}
//
//		int flag;
//		bool isFound = false;
//		for (int i = 1; i < size; i++) {
//			MPI_Recv(&flag, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);     //receive the value of the flag and update isFound to get the position of the desired element
//			if (flag >= 0) {
//				isFound = true;
//				cout << "Searched number position:" << flag;
//			}
//		}
//
//		if (!isFound) {
//			cout << "Number is not in the list";
//		}
//	}
//
//	if (rank != 0) {
//		int arrayRec[3];
//		MPI_Recv(&arrayRec, 3, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);  //other proccesses receive the lower and upper bounds and also the element to search for
//		int min = arrayRec[0];
//		int max = arrayRec[1];
//		int number = arrayRec[2];
//		bool flag = false;
//
//		for (min; min <= max; min++) {   // search the element in the computed range and update flag accordingly
//			if (v[min] == number) {
//				flag = true;
//			}
//		}
//
//		int verify;      
//		if (flag) {
//			verify = min;
//		}
//		else {
//			verify = -1;
//		}
//		MPI_Send(&verify, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);  //transfer verify to the receive channel from above
//	}
//
//
//
//	MPI_Finalize();
//}


//3.

//#include<iostream>
//#include<mpi.h>
//
//using namespace std;
//
//int main() {
//
//	int rank, size;
//	MPI_Status status;
//
//	MPI_Init(NULL, NULL);
//
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//	double begin_t = MPI_Wtime();
//
//	int N = size;
//	int M = rand() % 900 + 100;  
//	
//
//	int sum = 0;
//
//	srand(time(NULL) + rank);
//
//	cout << "rank " << rank << ": ";      //create an array with random numbers and compute the sum for each proccess
//	for (int i = 1; i <= M; i++) {
//		int number = rand() % 1000 + 1;
//		
//		cout << number << " ";
//		sum += number;
//	}
//	cout << endl;
//
//	cout << "The sum for rank " << rank << " is " << sum << endl;   
//
//	double end_t = MPI_Wtime();
//	cout << "The process " << rank << " took " << end_t - begin_t << " s" << endl;  //compute the time it took to complete the proccess
//
//	MPI_Finalize();
//}


//lab 2 

//1. Write a program that searches an element inside an array.
//a.Use MPI_Broadcast for sending the array.If the element is found, print the maximum
//position index.For computing the maximum position, you need to use MPI_Reduce.
//b.Use scatter for sending the array.If the element is found many times, print all its positions.
//Use MPI_Gather for sending back the positions.


//ex a


//#include<iostream>
//#include<mpi.h>
//#include <time.h> 
//
//using namespace std;
//
//int main() {
//
//	int rank, size;
//	const int N = 30;
//	int array[N + 1];
//	const int VALUE = 7;     //value to search
//	int maxPos = -1;
//	srand(time(NULL));
//	MPI_Init(NULL, NULL);
//
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//	if (rank == 0) {                           //initiate the array
//		for (int i = 0; i < N; i++)
//			array[i] = rand() % 40 + 1;
//
//		array[3] =7;
//		array[11] = 7;
//		array[16] = 7;
//		array[23] = 7;
//
//		for (int i = 0; i < N; i++) {
//			cout <<"array["<< i <<"]="<<array[i]<<" ";
//		}
//		
//		cout << endl;
//	}
//
//	MPI_Bcast(&array, N, MPI_INT, 0, MPI_COMM_WORLD);    //broadcast array to all other proccesses
//
//	int k = N / size;      //proccess size
//
//	int low = rank * k;                    //proccess lower and upper bounds
//	int high = low + k - 1;
//
//	int currentMaxPos = -1;
//	for (int i = low; i <= high; i++) {    //search the value and update currentMaxPos with the position
//		if (array[i] == VALUE) {
//			currentMaxPos = i;
//		}
//	}
//
//	MPI_Reduce(&currentMaxPos, &maxPos, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);   //this will get us the latest position which will be found in maxPos
//
//
//	if (rank == 0) {          //print the results depending if maxPos changed its value or not
//		if (maxPos == -1) {
//			cout << "Value " << VALUE << " was not found" << endl;
//		}
//		else {
//			cout << "The maximum position where value " << VALUE << " was found is: " << maxPos << endl;
//		}
//	}
//
//	MPI_Finalize();
//
//}


//ex b

//#include<iostream>
//#include<mpi.h>
//#include <time.h>
//
//using namespace std;
//
//int main() {
//
//	int rank, size;
//	const int N = 30;
//	int array[N + 1];
//	int a[N + 1];
//	int b[N + 1];
//	int c[N + 1];
//	const int VALUE = 7;
//	
//	srand(time(NULL));
//
//	MPI_Init(NULL, NULL);
//
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//	if (rank == 0) {                                //create array 
//		for (int i = 0; i < N; i++)
//			array[i] = rand() % 40 + 1;
//
//		array[3] = 7;
//		array[11] = 7;
//		array[16] = 7;
//		array[23] = 7;
//
//		for (int i = 0; i < N; i++) {
//			cout << "array[" << i << "]=" << array[i] << " ";
//		}
//		cout << endl;
//	}
//
//	int k = N / size;             //range for each proccess
//
//	MPI_Scatter(&array, k, MPI_INT, a, k, MPI_INT, 0, MPI_COMM_WORLD);     //divide the elements of the array in multiple arrays a[] of size k
//
//	for (int i = 0; i < k; i++) {      //search the value and update results in array b[]
//		if (a[i] == VALUE) {
//			b[i] = rank * k + i;       //position of the element depending on the rank
//		}
//		else {
//			b[i] = -1;                 //we know that if b[i] is -1 the element isn't found there
//		}
//	}
//
//	MPI_Gather(&b, k, MPI_INT, &c, k, MPI_INT, 0, MPI_COMM_WORLD); //gather the constructed b[] array in c and print the found elements depending if array c[]
//                                                                 //that are different than -1
//	if (rank == 0) {
//		for (int i = 0; i < N; i++) {
//			if (c[i] != -1) {
//				cout << c[i] << " ";
//			}
//		}
//	}
//
//	MPI_Finalize();
//}



//lab MPI3   not yet commented!

//1. Define a type called Student that stores information about students.Create a list of students, and
//then using n processors, search for one specific student.


#include <iostream>
#include <stdlib.h>
#include <string>
#include <mpi.h>
#define MASTER 0
#define NOT_FOUND -1

using namespace std;

struct Student {
	int id, age, gender;
	char* name = new char[20];
};

int main(int* argc, char** argv) {

	int rank, size;
	int idToSearch, students;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Datatype MPI_StudentType;

	idToSearch = atoi(argv[1]);
	students = atoi(argv[2]);

	Student* studentsList = new Student[students];
	Student* studentsToSearch = new Student[students];

	int* receiveResult = new int[students];

	MPI_Type_contiguous(3, MPI_INT, &MPI_StudentType);
	MPI_Type_contiguous(20, MPI_SHORT, &MPI_StudentType);

	MPI_Type_commit(&MPI_StudentType);

	if (rank == MASTER) {

		for (int i = 0; i < students; i++) {
			studentsList[i].id = i;
			studentsList[i].name[0] = 'A' + i;
			studentsList[i].name[1] = '\0';
			studentsList[i].gender = 1;
			studentsList[i].age = i * 6;
		}

		for (int i = 0; i < students; i++) {
			printf("ID - %d, Name - %s, Gender - %d, Age - %d\n",
				studentsList[i].id, studentsList[i].name, studentsList[i].gender, studentsList[i].age);
		}
	}

	int count = students / size;
	MPI_Bcast(&idToSearch, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
	MPI_Scatter(studentsList, count, MPI_StudentType, studentsToSearch, count, MPI_StudentType, MASTER, MPI_COMM_WORLD);

	int* resultsOfProcess = new int[students];

	int top = -1;
	for (int i = 0; i < count; i++) {
		if (studentsToSearch[i].id == idToSearch) {
			resultsOfProcess[++top] = i + rank * count;
		}
	}

	for (int i = top + 1; i < count; i++) {
		resultsOfProcess[i] = NOT_FOUND;
	}

	MPI_Gather(resultsOfProcess, count, MPI_INT, receiveResult, count, MPI_INT, MASTER, MPI_COMM_WORLD);

	if (rank == MASTER) {
		bool found = false;
		for (int i = 0; i < students; i++) {
			if (receiveResult[i] != NOT_FOUND) {
				found = true;
			}
		}
		if (found) {
			printf("Student ID %d was found.", idToSearch);
		}
		else {
			printf("Student was not found.");
		}
	}
	MPI_Type_free(&MPI_StudentType);
	MPI_Finalize();
}


