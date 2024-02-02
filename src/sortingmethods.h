#ifndef SORTINGMETHODS_H
#define SORTINGMETHODS_H
#include <vector>

/**
 * \brief Функция сортировка массива "Пузырьком"
 *
 * Стандартная сортировка, просматривающая массив с конца и перемещающая наименьший элемент в начало.
 *
 * \tparam T - определяет тип, сортируемых объектов
 * \param a - массив (вектор) значений
 * \param size - размер массива
 */
template <typename T>
void bubblesort(std::vector<T>* a, int const size) {
    T x;
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j > i; --j)
            if ((*a)[j] < (*a)[j - 1]) {
                x = (*a)[j - 1];
                (*a)[j - 1] = (*a)[j];
                (*a)[j] = x;
            }
    }
}

/**
 * \brief Функция сортировка массива "Шейкер"
 *
 * Улучшенная "пузырьковая" сортировка, просматривающая массив и с конца, и с начала по очереди.
 *
 * \tparam T - определяет тип, сортируемых объектов
 * \param a - массив (вектор) значений
 * \param size - размер массива
 */
template <typename T>
void shakersort(std::vector<T>* a, int const size) {
    int k = size - 1;
    int lb, rb = size - 1;
    T x;

    do {
        // from bottom to top passage
        for (int i = rb; i > 0; i--) {
            if ((*a)[i - 1] > (*a)[i]) {
                x = (*a)[i - 1];
                (*a)[i - 1] = (*a)[i];
                (*a)[i] = x;
                k = i;
            }
        }
        lb = k + 1;  // all ellements from the start sorted

        // passage from top to bottom
        for (int j = 1; j <= rb; j++) {
            if ((*a)[j - 1] > (*a)[j]) {
                x = (*a)[j - 1];
                (*a)[j - 1] = (*a)[j];
                (*a)[j] = x;
                k = j;
            }
        }
        rb = k - 1;  // all elements to the end sorted
    } while (lb < rb);
}

/**
 * \brief Функция Слияния двух массивов
 *
 * Сливает два небольших массива (в качестве параметра передаётся один массив и место разбиения его на два) в
 * один по некоторому правилу, которое делает сливаемый массив отсортированным.
 *
 * \tparam T - определяет тип объектов массива
 * \param a - массив (вектор) значений
 * \param left - левая граница масива, который нужно слить
 * \param mid - место разбиения массива (вместе с left определяют первый массив)
 * \param right - права граница массива (вместе с mid определяют второй массив)
 */
template <typename T>
void merge(std::vector<T>* a, int left, int mid, int right) {
    std::vector<T> b(right + 1 - left);
    int i = 0;
    int first = left, second = mid + 1;  // h ; j
    // Merges the two array's into b[] until the first one is finish
    while ((first <= mid) && (second <= right)) {
        if ((*a)[first] <= (*a)[second]) {
            b[i] = (*a)[first];
            first++;
        } else {
            b[i] = (*a)[second];
            second++;
        }
        i++;
    }
    // Completes the array filling in it the missing values
    if (first > mid) {
        for (int k = second; k <= right; k++) {
            b[i] = (*a)[k];
            i++;
        }
    } else {
        // if second > right
        for (int k = first; k <= mid; k++) {
            b[i] = (*a)[k];
            i++;
        }
    }
    for (int k = 0; k <= right - left; k++) {
        (*a)[k + left] = b[k];
    }
}

/**
 * \brief Функция сортировка массива "Слиянием"
 *
 * Ускоренная сортировка, делящая массива на две части много раз, которые затем сливаются в сортированные
 * массивы
 *
 * \tparam T - определяет тип, сортируемых объектов
 * \param a - массив (вектор) значений массива
 * \param begin - индекс начала массива для сортировки
 * \param end - индекс конца массива для сортировки
 */
template <typename T>
void mergesort(std::vector<T>* a, int begin, int end) {
    if (begin < end) {
        int mid = (begin + end) / 2;
        mergesort(a, begin, mid);
        mergesort(a, mid + 1, end);
        merge(a, begin, mid, end);
    }
}

#endif  // SORTINGMETHODS_H
