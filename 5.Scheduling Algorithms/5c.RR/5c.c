#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	int id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
	int remaining_time;
	int finished_index;
} process_t;

process_t processes[10];
int n,tq;

int arrival_comparator(const process_t* a, const process_t* b) {
	return a->arrival_time > b->arrival_time;
}

int finished_comparator(const process_t* a, const process_t* b) {
	return a->finished_index > b->finished_index;
}

void schedule_rr() {
	int i, finished_jobs = 0;
	float twt = 0, ttt = 0;
	// qsort(processes, n, sizeof(process_t), arrival_comparator);
	int cur_time = 0;

	while (finished_jobs < n) {
		for (i = 0; i < n && processes[i].arrival_time <= cur_time; i++) {
			if (processes[i].remaining_time != 0) {
				if (processes[i].remaining_time <= tq) {
					printf("Scheduling process %d and finishing\n", processes[i].id);
					cur_time += processes[i].remaining_time;
					processes[i].remaining_time = 0;
					processes[i].turn_around_time = cur_time - processes[i].arrival_time;
					processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
					processes[i].finished_index = finished_jobs++;

					twt += processes[i].waiting_time;
					ttt += processes[i].turn_around_time;
				} else {
					printf("Scheduling process %d...\n", processes[i].id);
					processes[i].remaining_time -= tq;
					cur_time += tq;
				}
			}
		}
	}
	
	qsort(processes, n, sizeof(process_t), finished_comparator);

	// Print table
	printf("\nId\tAT\tBT\tTT\tWT\n");
	for (i = 0; i < n; i++)
		printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time,
									   processes[i].burst_time, processes[i].turn_around_time,
									   processes[i].waiting_time);
	
	printf("Average waiting time: %f\n", twt/((float)n));
	printf("Average turnaround time: %f\n", ttt/((float)n));
}

int main() {
	int i;
	printf("Enter number of processes: ");
	scanf("%d", &n);

	printf("Enter process details\nAT BT\n");
	for (i = 0; i < n; i++) {
		processes[i].id = i+1;
		scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
		processes[i].remaining_time = processes[i].burst_time;
	}

	printf("Enter the time quantum: ");
	scanf("%d", &tq);

	schedule_rr();
}

/*
	Enter number of processes: 5
	Enter process details
	AT BT
	0 5
	1 3
	2 1
	3 2
	4 3
	Enter time quantum: 2

	Id      AT      BT      TT      WT
	3       2       1       3       2
	4       3       2       4       2
	2       1       3       11      8
	5       4       3       9       6
	1       0       5       14      9
	Average waiting time: 5.400000
	Average turnaround time: 8.200000
*/