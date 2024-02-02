#include <ctime>
#include <fstream>

#include "exportGoods.h"
#include "sortingmethods.h"

/** \brief Устанавливает количество строк, которые будут прочитаны из файла
 */
#define N 100050
/** \brief Устанавливает, сколько измерений необходимо прозвести (число от 0 до 9)
 */
#define cycle 9

/**
 * \brief Основная функция в программе
 *
 * Здесь выполняются все необходимые по заданию операции: происходит чтение файла, состоящего из 100050 строк.
 * Затем, проводится 9 измерений времени (с разным количеством сортируемых элементов) для разных сортировок.
 * \return ноль, если программа завершилась успешно
 */
int main() {
    /**В начале программы создаётся вектор data, в который считается весь файл.
     * \code
     * std::vector<Goods> data;
     * \endcode
     */
    std::vector<Goods> data;
    std::ifstream file("data.txt", std::ios::in);
    if (file.is_open()) {
        int i = 0;
        std::string temp;
        std::getline(file, temp);
        while (i < N) {
            std::string name, country, q_temp, p_temp;
            std::getline(file, name, ';');
            std::getline(file, country, ';');
            std::getline(file, q_temp, ';');
            std::getline(file, p_temp, '\n');
            int quant = std::stoi(q_temp);
            int price = std::stoi(p_temp);
            /** Стоит обратить внимание, что данные помещаются в вектор с помощью emplace_back, дабы избежать
             * излишнего копирования \code data.emplace_back(name, country, quant, price); \endcode
             */
            data.emplace_back(name, country, quant, price);
            i++;
        }
    } else {
        std::cerr << "error";
    }
    file.close();
    std::cout << "The file has succesfully readed" << std::endl;

    /** Для проведения измерений задаётся статически массив, в котором написано количество элементов, которые
     * будут учавствовать в сортировке на каждом конкретном замере
     * \code
     * int sizes[9] = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100050};
     * \endcode
     */
    int sizes[9] = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100050};
    /** До начала замеров, открывается файл datagraph.txt на запись, в который запишутся данные для
     * дальнейшего построения графиков некоторыми средствами визуализации данных
     * \code
     * std::ofstream graph("datagraph.txt");
     * \endcode
     */
    std::ofstream graph("datagraph.txt");
    for (int size : sizes) graph << size << " ";
    double bubdata[9], shakdata[9], mergedata[9];

    for (int i = 0; i < cycle; i++) {
        // std::ofstream out;
        int n = sizes[i];
        std::cout << n << " elements\n";


        std::vector<Goods> bubble(data);
        clock_t start = clock();
        bubblesort(&bubble, n);
        clock_t end = clock();
        // out.open(std::string("bubble") + std::to_string(i+1) + std::string(".txt"));
        // for (int j = 0; j < n; j++) out << bubble[j] << '\n';
        // out.close();
        double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "BubbleSort finished at: " << seconds << " sec" << std::endl;
        bubdata[i] = seconds;


        std::vector<Goods> shaker(data);
        start = clock();
        shakersort(&shaker, n);
        end = clock();
        // out.open(std::string("shaker") + std::to_string(i+1) + std::string(".txt"));
        // for (int j = 0; j < n; j++) out << shaker[j] << '\n';
        // out.close();
        seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "ShakerSort finished at: " << seconds << " sec" << std::endl;
        shakdata[i] = seconds;


        std::vector<Goods> merge(data);
        start = clock();
        mergesort(&merge, 0, n);
        end = clock();
        // out.open(std::string("merge") + std::to_string(i+1) + std::string(".txt"));
        // for (int j = 0; j < n; j++) out << merge[j] << '\n';
        // out.close();
        seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "MergeSort finished at: " << seconds << " sec" << std::endl;
        mergedata[i] = seconds;

        std::cout << std::endl;
    }
    graph << "\n";
    for (double sec : bubdata) graph << sec << " ";
    graph << "\n";
    for (double sec : shakdata) graph << sec << " ";
    graph << "\n";
    for (double sec : mergedata) graph << sec << " ";
    graph << std::endl;
    graph.close();

    return 0;
}
