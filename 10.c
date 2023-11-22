#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_FRAMES 3
#define NUM_PAGES 10

int frames[NUM_FRAMES] = {-1, -1, -1}; // Frames with -1 denote empty frames
int page_faults = 0;

void print_frames() {
    printf("Frames: ");
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frames[i]);
    }
    printf("\n");
}

void fifo_algorithm(int page_reference_string[], int num_pages) {
    int frame_index = 0;

    for (int i = 0; i < num_pages; i++) {
        int page = page_reference_string[i];

        int found = 0;
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[frame_index] = page;
            frame_index = (frame_index + 1) % NUM_FRAMES;
            page_faults++;
        }

        print_frames();
    }
}

void lru_algorithm(int page_reference_string[], int num_pages) {
    int page_used_time[NUM_FRAMES] = {0};

    for (int i = 0; i < num_pages; i++) {
        int page = page_reference_string[i];

        int found = 0;
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                page_used_time[j] = i;
                break;
            }
        }

        if (!found) {
            int min_time = page_used_time[0];
            int min_index = 0;

            for (int j = 1; j < NUM_FRAMES; j++) {
                if (page_used_time[j] < min_time) {
                    min_time = page_used_time[j];
                    min_index = j;
                }
            }

            frames[min_index] = page;
            page_used_time[min_index] = i;
            page_faults++;
        }

        print_frames();
    }
}

void *optimal_algorithm(void *args) {
    int *data = (int *)args;
    int *page_reference_string = data;
    int num_pages = data[1];
    int future_occurrence[NUM_FRAMES] = {0};

    for (int i = 0; i < num_pages; i++) {
        int page = page_reference_string[i];
        int found = 0;

        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int max_future_occurrence = -1;
            int replace_index = -1;

            for (int j = 0; j < NUM_FRAMES; j++) {
                int future_index = i + 1;
                while (future_index < num_pages) {
                    if (page_reference_string[future_index] == frames[j]) {
                        future_occurrence[j] = future_index;
                        break;
                    }
                    future_index++;
                }

                if (future_occurrence[j] == 0) {
                    replace_index = j;
                    break;
                }

                if (future_occurrence[j] > max_future_occurrence) {
                    max_future_occurrence = future_occurrence[j];
                    replace_index = j;
                }
            }

            frames[replace_index] = page;
            page_faults++;
        }

        print_frames();
    }

    pthread_exit(NULL);
}

int main() {
    int num_pages;
    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    int page_reference_string[num_pages];
    printf("Enter the page reference string (e.g., 1 2 3 4 1 2 5 1 2 3): ");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &page_reference_string[i]);
    }

    pthread_t optimal_thread;

    printf("FIFO Algorithm\n");
    page_faults = 0; // Reset page_faults for the next algorithm
    fifo_algorithm(page_reference_string, num_pages);
    printf("\nTotal Page Faults (FIFO): %d\n\n", page_faults);

    printf("LRU Algorithm\n");
    page_faults = 0; // Reset page_faults for the next algorithm
    lru_algorithm(page_reference_string, num_pages);
    printf("\nTotal Page Faults (LRU): %d\n\n", page_faults);

    int optimal_data[num_pages + 1];
    optimal_data[0] = num_pages;
    for (int i = 0; i < num_pages; i++) {
        optimal_data[i + 1] = page_reference_string[i];
    }

    printf("Optimal Algorithm\n");
    page_faults = 0; // Reset page_faults for the next algorithm
    pthread_create(&optimal_thread, NULL, optimal_algorithm, (void *)optimal_data);
    pthread_join(optimal_thread, NULL);
    printf("\nTotal Page Faults (Optimal): %d\n", page_faults);

    return 0;
}
