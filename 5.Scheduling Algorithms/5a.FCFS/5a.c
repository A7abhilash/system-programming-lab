#include<stdio.h>

typedef struct {
	int pid;
	int burstTime;
	int arrivalTime;
	int completionTime;
	int turnaroundTime;
	int waitingTime;
}process;

const int SIZE = 5;
typedef struct {
	process readyQueue[5];
	float avgTurnaroundTime;
	float avgWaitingTime;
}queue;

void sortAccordingToArrivalTime(process readyQueue[]){
	//Insertion sort
	int i,j;
	process key;

	for(i=0;i<SIZE;i++){
		key=readyQueue[i];
		j=i-1;
		
		while(j>=0 && readyQueue[j].arrivalTime>key.arrivalTime){
			readyQueue[j+1]=readyQueue[j];
			j=j-1;
		}
		
		readyQueue[j+1]=key;
	}
}

void find_CT_TT_WT(process readyQueue[]){
	readyQueue[0].completionTime = readyQueue[0].burstTime;
	readyQueue[0].turnaroundTime = readyQueue[0].burstTime;
	readyQueue[0].waitingTime = 0;
	int gap = 0;

	for (int i = 1; i < SIZE;i++){
		gap = readyQueue[i].arrivalTime - readyQueue[i - 1].completionTime;
		gap = gap > 0 ? gap : 0;
		readyQueue[i].completionTime = readyQueue[i - 1].completionTime + readyQueue[i].burstTime + gap;
		readyQueue[i].turnaroundTime = readyQueue[i].completionTime - readyQueue[i].arrivalTime;
		readyQueue[i].waitingTime = readyQueue[i].turnaroundTime - readyQueue[i].burstTime;
	}
}

float find_AvgTT(queue Q){
	int i, sum = 0;

	for (i = 0; i < SIZE; i++){
		sum += Q.readyQueue[i].turnaroundTime;
	}
	return (float)sum / (float)SIZE;
}

float find_AvgWT(queue Q){
	int i, sum = 0;

	for (i = 0; i < SIZE; i++){
		sum += Q.readyQueue[i].waitingTime;
	}
	return (float)sum / (float)SIZE;
}

void display(queue Q){
	printf("\nPID\tAT\tBT\tTT\tWT\n");
	printf("---\t---\t---\t---\t---\n");

	for (int i = 0; i < SIZE; i++){
		printf("%d\t%d\t%d\t%d\t%d\n",Q.readyQueue[i].pid,Q.readyQueue[i].arrivalTime,Q.readyQueue[i].burstTime,Q.readyQueue[i].turnaroundTime,Q.readyQueue[i].waitingTime);
	}
	printf("Avg TT: %f\n", Q.avgTurnaroundTime);
	printf("Avg WT: %f\n", Q.avgWaitingTime);
}

void main(){
	int i;
	queue Q;

	for (i = 0; i < SIZE;i++){
		Q.readyQueue[i].pid = i + 1;
		printf("PID: %d\n", Q.readyQueue[i].pid);
		printf("Enter the arrival time: ");
		scanf("%d", &Q.readyQueue[i].arrivalTime);
		printf("Enter the burst time: ");
		scanf("%d", &Q.readyQueue[i].burstTime);
	}

	sortAccordingToArrivalTime(Q.readyQueue);
	find_CT_TT_WT(Q.readyQueue);
	Q.avgTurnaroundTime = find_AvgTT(Q);
	Q.avgWaitingTime = find_AvgWT(Q);
	display(Q);
}

/*	OUTPUT:
	PID: 1
	Enter the arrival time: 4
	Enter the burst time: 5
	PID: 2
	Enter the arrival time: 6
	Enter the burst time: 4
	PID: 3
	Enter the arrival time: 0
	Enter the burst time: 3
	PID: 4
	Enter the arrival time: 6
	Enter the burst time: 2
	PID: 5
	Enter the arrival time: 5
	Enter the burst time: 4

	PID AT  BT  TT  WT
	--- --- --- --- ---
	3   0   3   3   0
	1   4   5   5   0
	5   5   4   8   4
	2   6   4   11  7
	4   6   2   13  11
	Avg TT: 8.000000
	Avg WT: 4.400000
*/