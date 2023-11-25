#include <vector>
#include <string>
#include "Order.h"

class MinHeap {
private:
    std::vector<order> heap;

    void heapifyUp(int i) {
        while (i && heap[parent(i)] > heap[i]) {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int left = leftChild(i);
        int right = rightChild(i);

        int smallest = i;

        if (left < heap.size() && heap[left] < heap[i])
            smallest = left;

        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return (2 * i + 1); }
    int rightChild(int i) { return (2 * i + 2); }

public:
    void push(order o) {
        heap.push_back(o);
        int index = heap.size() - 1;
        heapifyUp(index);
    }

    void pop() {
        try {
            if (heap.size() == 0)
                throw std::out_of_range("Vector<X>::at() : "
                                        "index is out of range(Heap underflow)");

            heap[0] = heap.back();
            heap.pop_back();

            heapifyDown(0);
        }
        catch (const std::out_of_range& oor) {
            std::cout << "\n" << oor.what();
        }
    }

    order& top() {
        try {
            if (heap.size() == 0)
                throw std::out_of_range("Vector<X>::at() : "
                                        "index is out of range(Heap underflow)");

            return heap.front();
        }
        catch (const std::out_of_range& oor) {
            std::cout << "\n" << oor.what();
        }
    }

    bool empty() {
        return heap.size() == 0;
    }
    
    int size(){
        return heap.size();
    }

    MinHeap (){}
};

