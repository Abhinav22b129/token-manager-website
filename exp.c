#include <stdio.h>

// Define frame structures for LRU and LFU
struct frame_LRU {
    int content, count;
} frame_LRU[100];

struct frame_LFU {
    int content, freq, cnt;
} frame_LFU[100];

void FIFO(int page[], int n, int frames[], int m) {
    int i, j, fnd, k = 0, cnt = 0;

    for (i = 0; i < m; i++) {
        frames[i] = -1;
    }

    printf("\n\tREFERENCE STRING\t PAGE NUMBER\t\t  STATUS\n");
    for (i = 0; i < n; i++) {
        fnd = 0;
        printf("\t\t%d\t\t\t\t\t   ", page[i]);
        for (j = 0; j < m; j++) {
            if (frames[j] == page[i]) {
                fnd = 1;
            }
        }
        if (fnd == 0) {
            frames[k] = page[i];
            k = (k + 1) % m;
            cnt++;
        }
        for (j = 0; j < m; j++) {
            if (frames[j] != -1) {
                printf("%d   ", frames[j]);
            }
        }
        if (fnd == 1) {
            printf("\t\t\t\tHIT\n");
        } else {
            printf("\t\t\t\tMISS\n");
        }
    }
    printf("\nPAGE FAULT : %d\n", cnt);
}

void LRU(int page[], int n, int f) {
    int i, j, k, cnt = 1, pf = 0, min, id = 0;

    for (i = 0; i < f; i++) {
        frame_LRU[i].content = -1;
        frame_LRU[i].count = 0;
    }

    printf("\nREFERENCING PAGE\tSTATUS\t\tFRAME CONTENT\n\n");
    for (i = 0; i < n; i++) {
        printf("\t%d\t\t", page[i]);
        for (j = 0; j < f; j++) {
            if (frame_LRU[j].content == page[i]) {
                printf("\t\t\tHIT \t\t");
                frame_LRU[j].count = cnt++;
                break;
            }
        }
        if (j == f) {
            printf("\t\t\tMISS\t\t");
            if (id < f) {
                frame_LRU[id].content = page[i];
                frame_LRU[id].count = cnt++;
                id++;
            } else {
                min = 0;
                for (k = 0; k < f; k++) {
                    if (frame_LRU[k].count < frame_LRU[min].count)
                        min = k;
                }
                frame_LRU[min].content = page[i];
                frame_LRU[min].count = cnt++;
            }
            pf++;
        }
        for (j = 0; j < f; j++) {
            if (frame_LRU[j].content != -1)
                printf("%d\t", frame_LRU[j].content);
        }
        printf("\n");
    }
    printf("\nPAGE FAULT : %d\n", pf);
}

void LFU(int page[], int n, int f) {
    int i, j, cnt = 1, pf = 0, min, id = 0;

    for (i = 0; i < f; i++) {
        frame_LFU[i].content = -1;
        frame_LFU[i].freq = 0;
        frame_LFU[i].cnt = 0;
    }

    printf("\nREFERENCING PAGE\tSTATUS\t\tFRAME CONTENT\n\n");
    for (i = 0; i < n; i++) {
        printf("\t%d\t\t", page[i]);
        for (j = 0; j < f; j++) {
            if (frame_LFU[j].content == page[i]) {
                printf("\t\t\tHIT \t\t");
                frame_LFU[j].freq++;
                break;
            }
        }
        if (j == f) {
            printf("\t\t\tMISS\t\t");
            if (id < f) {
                frame_LFU[id].content = page[i];
                frame_LFU[id].freq++;
                frame_LFU[id].cnt = cnt++;
                id++;
            } else {
                min = 0;
                for (j = 0; j < f; j++) {
                    if (frame_LFU[min].freq > frame_LFU[j].freq) {
                        min = j;
                    } else if (frame_LFU[min].freq == frame_LFU[j].freq && frame_LFU[min].cnt > frame_LFU[j].cnt) {
                        min = j;
                    }
                }
                frame_LFU[min].content = page[i];
                frame_LFU[min].freq = 1;
                frame_LFU[min].cnt = cnt++;
            }
            pf++;
        }
        for (j = 0; j < f; j++) {
            if (frame_LFU[j].content != -1)
                printf("%d\t", frame_LFU[j].content);
        }
        printf("\n");
    }
    printf("\nTOTAL PAGE FAULT : %d\n", pf);
}

int main() {
    int choice, pg, fr, i;
    int page[100];
    int frames[100];

    printf("ENTER THE NUMBER OF PAGES : ");
    scanf("%d", &pg);

    printf("ENTER THE REFERENCING STRING : ");
    for (i = 0; i < pg; i++) {
        scanf("%d", &page[i]);
    }

    printf("ENTER THE NUMBER OF FRAMES : ");
    scanf("%d", &fr);

    do {
        printf("\nMenu:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. LFU\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FIFO(page, pg, frames, fr);
                break;
            case 2:
                LRU(page, pg, fr);
                break;
            case 3:
                LFU(page, pg, fr);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}