template<typename T>
class Vector {
private:
    T *arr; // Dynamic array//
    int capacity; // Current capacity of the vector//
    int size; // Current size of the vector//

public:
    // Default constructor//
    Vector() {
        capacity = 1;
        size = 0;
        arr = new T[capacity];
    }

    // Destructor//
    ~Vector() {
        delete[] arr;
    }

    // Add an element to the end of the vector//
    void push_back(T element) {
        if (size == capacity) {
            capacity *= 2;
            T *temp = new T[capacity];
            for (int i = 0; i < size; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
        arr[size++] = element;
    }

    // Retrieve an element at the specified index//
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // Get the size of the vector//
    int getSize() {
        return size;
    }

    // Erase an element at the specified index//
    void erase(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    // Get an iterator pointing to the beginning of the vector//
    T* begin() {
        return arr;
    }

    // Get an iterator pointing to the end of the vector//
    T* end() {
        return arr + size;
    }

    // Clear all elements from the vector//
    void clear() {
        size = 0;
    }
};

