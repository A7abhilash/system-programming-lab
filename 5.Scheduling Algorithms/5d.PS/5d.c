#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
int id;
int priority;
int arrival_time;
int burst_time;
int waiting_time;
int turn_around_time;
int finished;
} process_t;

process_t processes[10];
int n;

int arrival_comparator(const process_t* a, const process_t* b) {
	return a->arrival_time > b->arrival_time;
}

int finished_comparator(const process_t* a, const process_t* b) {
	return a->finished > b->finished;
}

void schedule_priority() {
	int i, finished_jobs = 0;
	float twt = 0, ttt = 0;
	qsort(processes, n, sizeof(process_t), arrival_comparator); // Sort processes by arrival time
	int cur_time = processes[0].arrival_time;
	while (finished_jobs != n) {
		int next_job = -1, min_priority = INT_MAX;
		for (i = 0; i < n && processes[i].arrival_time <= cur_time; i++) {
			if (!processes[i].finished && processes[i].priority < min_priority) {
			next_job = i;
			min_priority = processes[i].priority;
			}
		}
		if (next_job != -1) {
			cur_time += processes[next_job].burst_time;
			processes[next_job].turn_around_time = cur_time - processes[next_job].arrival_time;
			processes[next_job].waiting_time = processes[next_job].turn_around_time - processes[next_job].burst_time;
			processes[next_job].finished = finished_jobs+1;
			finished_jobs++;
			twt += processes[next_job].waiting_time;
			ttt += processes[next_job].turn_around_time;
		} else {
			for (i = 0; i < n; i++) {
				if (!processes[i].finished) {
				cur_time = processes[i].arrival_time;
				break;
				}
			}
		}
	}
	// Sort by order of scheduling
	qsort(processes, n, sizeof(process_t), finished_comparator);
	// Print table
	printf("Id\tAT\tBT\tWT\tTT\n");
	for (i = 0; i < n; i++)
	printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrival_time,
	processes[i].burst_time, processes[i].waiting_time,
	processes[i].turn_around_time);
	printf("Average waiting time: %f\n", twt/((float)n));
	printf("Average turnaround time: %f\n", ttt/((float)n));
}

int main() {
	int i;
	
	printf("Enter number of processes: ");
	scanf("%d", &n);
	
	printf("Enter process details\nArrival time\tBurst time\tPriority\n");
	for (i = 0; i < n; i++) {
		processes[i].id = i+1;
		scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
		processes[i].finished = 0;
	}
	
	schedule_priority();
}


/*
	Enter number of processes: 5

	Enter process details
	Arrival time    Burst time      Priority
	0 11 2
	5 28 0
	12 2 3
	2 10 1
	9 16 4
	
	Id      AT      BT      WT      TT
	1       0       11      0       11
	2       5       28      6       34
	4       2       10      37      47
	3       12      2       37      39
	5       9       16      42      58
	Average waiting time: 24.400000
	Average turnaround time: 37.800000
*/