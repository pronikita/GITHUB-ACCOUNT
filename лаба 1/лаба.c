#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h> // ��� ������������� memcpy()

void menu() {
    printf("|1.��������� ������       |\n");
    printf("|2.���� ������� �������   |\n");
    printf("|3.������� ������         |\n");
    printf("---------------------------\n");
    printf("|4.���������� ���������   |\n");
    printf("|5.���������� �������     |\n");
    printf("|6.���������� ���������   |\n");
    printf("|7.���������� �����       |\n");
    printf("---------------------------\n");
    printf("|8.�����                  |\n\n");
    printf("�����: ");
}

void insertionSort(int arr[], int n, int* iterationCount) {
    *iterationCount = 0;
    for (int i = 1; i < n; i++) {
        int k = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > k) {
            arr[j + 1] = arr[j];
            j = j - 1;
            (*iterationCount)++;
        }
        arr[j + 1] = k;
        (*iterationCount)++;
    }
}

void selectionSort(int arr[], int n, int* iterationCount) {
    *iterationCount = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            (*iterationCount)++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
        (*iterationCount)++;
    }
}

void countingSort(int arr[], int size, int* iterationCount) {
    *iterationCount = 0;
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        (*iterationCount)++;
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int* count = (int*)calloc(max + 1, sizeof(int));
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
        (*iterationCount)++;
    }

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
            (*iterationCount)++;
        }
    }
    free(count);
}

void shellSort(int arr[], int size, int* iterationCount) {
    *iterationCount = 0;
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                (*iterationCount)++;
            }
            arr[j] = temp;
            (*iterationCount)++;
        }
    }
}

int isSorted(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int* globalArray = NULL;
int* originalArray = NULL;
int globalArraySize = 0;

void restoreArray() {
    if (globalArray != NULL && originalArray != NULL) {
        memcpy(globalArray, originalArray, globalArraySize * sizeof(int));
    }
}

int main() {
    int vib = 0;
    setlocale(LC_ALL, "rus");
    menu();
    while (vib != 8) {
        scanf_s("%d", &vib);
        switch (vib) {
        case 1: {
            printf("������� ������ �������: ");
            scanf_s("%d", &globalArraySize);
            globalArray = (int*)malloc(globalArraySize * sizeof(int));
            originalArray = (int*)malloc(globalArraySize * sizeof(int));
            for (int i = 0; i < globalArraySize; i++) {
                globalArray[i] = rand() % 101;
            }
            memcpy(originalArray, globalArray, globalArraySize * sizeof(int));
            printf("\n");
            for (int i = 0; i < globalArraySize; i++) {
                printf("%d ", globalArray[i]);
            }
            printf(" - ��� ��������� ������\n\n");
            menu();
            break;
        }
        case 2: {
            printf("������� ������ �������: ");
            scanf_s("%d", &globalArraySize);
            globalArray = (int*)malloc(globalArraySize * sizeof(int));
            originalArray = (int*)malloc(globalArraySize * sizeof(int));
            printf("������� ������: ");
            for (int i = 0; i < globalArraySize; i++) {
                scanf_s("%d", &globalArray[i]);
            }
            memcpy(originalArray, globalArray, globalArraySize * sizeof(int));
            printf("\n");
            for (int i = 0; i < globalArraySize; i++) {
                printf("%d ", globalArray[i]);
            }
            printf(" - ��� ��������� ������\n\n");
            menu();
            break;
        }
        case 3: {
            if (globalArray != NULL && globalArraySize > 0) {
                printf("\n������� ������: ");
                for (int i = 0; i < globalArraySize; i++) {
                    printf("%d ", globalArray[i]);
                }
                printf("\n\n");
            }
            else {
                printf("������ �� ���������������. ������� ������� ��� �������� ������.\n\n");
            }
            menu();
            break;
        }
        case 4: {
            if (globalArray != NULL && globalArraySize > 0) {
                int iterations = 0;
                clock_t start = clock();
                insertionSort(globalArray, globalArraySize, &iterations);
                clock_t end = clock();
                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

                printf("\n��������������� ������ (���������� ���������): ");
                for (int i = 0; i < globalArraySize; i++) {
                    printf("%d ", globalArray[i]);
                }
                printf("\n���������� ��������: %d\n", iterations);
                printf("����� ����������: %.6f ������\n\n", time_spent);
                if (isSorted(globalArray, globalArraySize) == 1) {
                    printf("������ ������� ������������.\n\n");
                }
                else {
                    printf("������: ������ �� ������������.\n\n");
                }
                restoreArray();
            }
            else {
                printf("������ �� ���������������. ������� ������� ��� �������� ������.\n\n");
            }
            menu();
            break;
        }
        case 5: {
            if (globalArray != NULL && globalArraySize > 0) {
                int iterations = 0;
                clock_t start = clock();
                selectionSort(globalArray, globalArraySize, &iterations);
                clock_t end = clock();
                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

                printf("\n��������������� ������ (���������� �������): ");
                for (int i = 0; i < globalArraySize; i++) {
                    printf("%d ", globalArray[i]);
                }
                printf("\n���������� ��������: %d\n", iterations);
                printf("����� ����������: %.6f ������\n\n", time_spent);
                if (isSorted(globalArray, globalArraySize) == 1) {
                    printf("������ ������� ������������.\n\n");
                }
                else {
                    printf("������: ������ �� ������������.\n\n");
                }
                restoreArray();
            }
            else {
                printf("������ �� ���������������. ������� ������� ��� �������� ������.\n\n");
            }
            menu();
            break;
        }
        case 6: {
            if (globalArray != NULL && globalArraySize > 0) {
                int iterations = 0;
                clock_t start = clock();
                countingSort(globalArray, globalArraySize, &iterations);
                clock_t end = clock();
                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

                printf("\n��������������� ������ (���������� ���������): ");
                for (int i = 0; i < globalArraySize; i++) {
                    printf("%d ", globalArray[i]);
                }
                printf("\n���������� ��������: %d\n", iterations);
                printf("����� ����������: %.6f ������\n\n", time_spent);
                if (isSorted(globalArray, globalArraySize) == 1) {
                    printf("������ ������� ������������.\n\n");
                }
                else {
                    printf("������: ������ �� ������������.\n\n");
                }
                restoreArray();
            }
            else {
                printf("������ �� ���������������. ������� ������� ��� �������� ������.\n\n");
            }
            menu();
            break;
        }
        case 7: {
            if (globalArray != NULL && globalArraySize > 0) {
                int iterations = 0;
                clock_t start = clock();
                shellSort(globalArray, globalArraySize, &iterations);
                clock_t end = clock();
                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

                printf("\n��������������� ������ (���������� �����): ");
                for (int i = 0; i < globalArraySize; i++) {
                    printf("%d ", globalArray[i]);
                }
                printf("\n���������� ��������: %d\n", iterations);
                printf("����� ����������: %.6f ������\n\n", time_spent);
                if (isSorted(globalArray, globalArraySize) == 1) {
                    printf("������ ������� ������������.\n\n");
                }
                else {
                    printf("������: ������ �� ������������.\n\n");
                }
                restoreArray();
            }
            else {
                printf("������ �� ���������������. ������� ������� ��� �������� ������.\n\n");
            }
            menu();
            break;
        }
        }
    }
    if (globalArray != NULL) {
        free(globalArray);
    }
    if (originalArray != NULL) {
        free(originalArray);
    }
}
