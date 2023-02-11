
#include <cache.hpp>
#include <header.hpp>
std::vector<int> size_of_data() {
    std::vector<int> size;
    int x = 1;
    while (pow(2, x) <= 0.5 * cache_size[0]) {
        ++x;
    }
    size.push_back(cache_size[0] * 1 / 2 * 1024 / 4);
    while (pow(2, x) <= 1.5 * cache_size[2]) {
        size.push_back(pow(2, x) * 1024 / 4);
        ++x;
    }
    size.push_back(cache_size[2] * 3 / 2 * 1024 / 4);
    return size;
}

std::vector<int> random_vector(size_t size) {
    std::vector<int> all16(size);
    for (size_t u = 0; u < all16.size(); ++u) {
        all16[u] = u * step;
    }
    //перемешаем
    std::shuffle(all16.begin(), all16.end(),
                 std::mt19937(std::random_device()()));
    return all16;
}

void make_title(std::vector<std::string> travel_variant, int y) {
    std::cout << "investigation:" << std::endl;
    std::cout << "  travel_variant:" << travel_variant[y] << std::endl;
    std::cout << "experiments:" << std::endl;
}

void forward(size_t size_i, const int* arr, [[maybe_unused]] int q) {
    for (int e = 0; e < count; ++e) {
        for (size_t j = 0; j < size_i; j += step)  // чтение
            q = arr[j];
    }
}

void reverse(size_t size_i, const int* arr, [[maybe_unused]] int q) {
    for (int e = 0; e < count; ++e) {
        for (int j = size_i - 1; j >= 0; j -= step)  // чтение
            q = arr[j];
    }
}

void random(const std::vector<int>& all16, const int* arr,
            [[maybe_unused]] int q) {
    for (int e = 0; e < count; ++e) {
        for (size_t j = 0; j < all16.size(); ++j)  // чтение
            q = arr[j];
    }
}

void cache_lines(size_t size_i, size_t& y, size_t i) {
    //  1. Создание буфера
    int* arr = new int[size_i];
    for (size_t k = 0; k < size_i; k++) {
        arr[k] = rand_r(reinterpret_cast<unsigned int*>(arr));
    }

    //      2. Прогревание кэша
    [[maybe_unused]] int q = 0;
    for (size_t j = 0; j < size_i; j += step)  // прогрев
        q = arr[j];

    // 2.5 генерация случайного вектора из чисел кратных 16 - только для
    // случайного обхода
    std::vector<int> all16(size_i / step + 1);
    if (y == 2) {
        all16 = random_vector(all16.size());
    }

    // 3. Циклический проход (1000 итераций)

    auto begin = std::chrono::steady_clock::now();
    if (y == 0) {  //прямой обход -forward
        forward(size_i, arr, q);
    } else if (y == 1) {  //обратный обход -reverse
        reverse(size_i, arr, q);
    } else {
        random(all16, arr, q);
    }
    auto end = std::chrono::steady_clock::now();
    auto time =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << " - experiment:" << i + 1 << std::endl;
    std::cout << " input_data:" << std::endl;
    std::cout << "  buffer_size: " << size_i / 256 << " Кb" << std::endl;
    std::cout << "duration: " << time.count() << " milliseconds" << std::endl;

    delete[] arr;
}