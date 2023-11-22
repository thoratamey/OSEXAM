#include <stdio.h>

#include <string.h>
int block_size[] = {200, 400, 600, 500, 300, 250};
int process_size[] = {357, 210, 468, 491};
int m = sizeof(block_size) / sizeof(block_size[0]);
int n = sizeof(process_size) / sizeof(process_size[0]);
void first_fit(int block_size[], int m, int process_size[], int n) {
    int temp_block_size[m];
    int temp_process_size[n];
    memcpy(temp_block_size, block_size, m * sizeof(int));
    memcpy(temp_process_size, process_size, n * sizeof(int));
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (temp_block_size[j] >= temp_process_size[i]) {
                allocation[i] = j;
                temp_block_size[j] -= temp_process_size[i];
                break;
            }
        }
    }
    printf("\nFirst Fit:\n");
    printf("Process No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_size[i]);
        if (allocation[i] != -1) {
            printf("%d", allocation[i] + 1);
        } else {
            printf("Not Allocated");
        }
        printf("\n");
    }
    int external_frag = 0;
    for (int i = 0; i < m; i++) {
        if (temp_block_size[i] > 0) {
            external_frag += temp_block_size[i];
        }
    }
    printf("External Fragmentation: %d KB\n", external_frag);
}
void best_fit(int block_size[], int m, int process_size[], int n) {
    int temp_block_size[m];
    int temp_process_size[n];
    memcpy(temp_block_size, block_size, m * sizeof(int));
    memcpy(temp_process_size, process_size, n * sizeof(int));
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int best_index = -1;
        for (int j = 0; j < m; j++) {
            if (temp_block_size[j] >= temp_process_size[i]) {
                if (best_index == -1 || temp_block_size[best_index] > temp_block_size[j]) {
                    best_index = j;
                }
            }
        }
        if (best_index != -1) {
            allocation[i] = best_index;
            temp_block_size[best_index] -= temp_process_size[i];
        }
    }
    printf("\nBest Fit:\n");
    printf("Process No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_size[i]);
        if (allocation[i] != -1) {
            printf("%d", allocation[i] + 1);
        } else {
            printf("Not Allocated");
        }
        printf("\n");
    }
    int external_frag = 0;
    for (int i = 0; i < m; i++) {
        if (temp_block_size[i] > 0) {
            external_frag += temp_block_size[i];
        }
    }
    printf("External Fragmentation: %d KB\n", external_frag);
}
void worst_fit(int block_size[], int m, int process_size[], int n) {
    int temp_block_size[m];
    int temp_process_size[n];
    memcpy(temp_block_size, block_size, m * sizeof(int));
    memcpy(temp_process_size, process_size, n * sizeof(int));
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int worst_index = -1;
        for (int j = 0; j < m; j++) {
            if (temp_block_size[j] >= temp_process_size[i]) {
                if (worst_index == -1 || temp_block_size[worst_index] < temp_block_size[j]) {
                    worst_index = j;
                }
            }
        }
        if (worst_index != -1) {
            allocation[i] = worst_index;
            temp_block_size[worst_index] -= temp_process_size[i];
        }
    }
    printf("\nWorst Fit:\n");
    printf("Process No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_size[i]);
        if (allocation[i] != -1) {
            printf("%d", allocation[i] + 1);
        } else {
            printf("Not Allocated");
        }
        printf("\n");
    }
    int external_frag = 0;
    for (int i = 0; i < m; i++) {
        if (temp_block_size[i] > 0) {
            external_frag += temp_block_size[i];
        }
    }
    printf("External Fragmentation: %d KB\n", external_frag);
}

int main() {
    first_fit(block_size, m, process_size, n);
    best_fit(block_size, m, process_size, n);
    worst_fit(block_size, m, process_size, n);
    return 0;

}
