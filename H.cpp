#include <iostream>
#include <vector>

void GetSiftedUp(std::vector<int>& heap, int the_index) {
  if (the_index != 1) {
    int tmp_ind = the_index / 2;
    if (heap[the_index] < heap[tmp_ind]) {
      std::swap(heap[the_index], heap[tmp_ind]);
      GetSiftedUp(heap, tmp_ind);
    }
  }
}

void GetSiftedDown(std::vector<int>& heap, int the_index) {
  if (2 * the_index < (int)heap.size()) {
    int tmp_ind = the_index * 2;
    if (tmp_ind + 1 < (int)heap.size() && heap[tmp_ind + 1] < heap[tmp_ind]) {
      ++tmp_ind;
    }
    if (heap[the_index] > heap[tmp_ind]) {
      std::swap(heap[the_index], heap[tmp_ind]);
      GetSiftedDown(heap, tmp_ind);
    }
  }
}

void GetInserted(std::vector<int>& heap, int value) {
  heap.push_back(value);
  int the_index = (int)heap.size() - 1;
  GetSiftedUp(heap, the_index);
}

void GetSilentlyExtracted(std::vector<int>& heap) {
  std::swap(heap[1], heap[heap.size() - 1]);
  heap.pop_back();
  GetSiftedDown(heap, 1);
}

void DoTheThing(std::vector<int>& heap, std::vector<int>& delete_heap) {
  while (heap.size() > 1 && delete_heap.size() > 1 &&
         heap[1] == delete_heap[1]) {
    GetSilentlyExtracted(heap);
    GetSilentlyExtracted(delete_heap);
  }
}

void PrintTheAnswer(std::vector<int>& heap) {
  if (heap.size() == 1) {
    std::cout << "error" << '\n';
  } else {
    std::cout << std::abs(heap[1]) << std::endl;
  }
}

void GetMin(std::vector<int>& heap, std::vector<int>& delete_heap) {
  DoTheThing(heap, delete_heap);
  PrintTheAnswer(heap);
}

void GetExtracted(std::vector<int>& heap, std::vector<int>& delete_heap,
                  std::vector<int>& negative_delete_heap) {
  DoTheThing(heap, delete_heap);
  PrintTheAnswer(heap);
  if (heap.size() > 1) {
    GetInserted(negative_delete_heap, (-1) * heap[1]);
    GetInserted(delete_heap, heap[1]);
  }
}
void GetCleared(std::vector<int>& heap) {
  heap.resize(0);
  heap.push_back(0);
}

void GetMaxExtracted(std::vector<int>& negative_heap,
                     std::vector<int>& negative_delete_heap,
                     std::vector<int>& delete_heap) {
  DoTheThing(negative_heap, negative_delete_heap);
  PrintTheAnswer(negative_heap);
  if (negative_heap.size() > 1) {
    GetInserted(negative_delete_heap, negative_heap[1]);
    GetInserted(delete_heap, (-1) * negative_heap[1]);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int quantity = 0;
  std::cin >> quantity;
  std::vector<int> heap(0);
  std::vector<int> negative_heap(0);
  std::vector<int> delete_heap(0);
  std::vector<int> negative_delete_heap(0);
  heap.push_back(0);
  negative_heap.push_back(0);
  delete_heap.push_back(0);
  negative_delete_heap.push_back(0);
  int value = 0;
  std::string input;
  for (int tmp = 0; tmp < quantity; ++tmp) {
    std::cin >> input;
    if (input == "insert") {
      std::cin >> value;
      std::cout << "ok" << '\n';
      GetInserted(heap, value);
      GetInserted(negative_heap, value * (-1));
    } else if (input == "clear") {
      std::cout << "ok" << '\n';
      GetCleared(heap);
      GetCleared(delete_heap);
      GetCleared(negative_delete_heap);
      GetCleared(negative_heap);
    } else if (input == "extract_min") {
      GetExtracted(heap, delete_heap, negative_delete_heap);
    } else if (input == "get_min") {
      GetMin(heap, delete_heap);
    } else if (input == "get_max") {
      GetMin(negative_heap, negative_delete_heap);
    } else if (input == "extract_max") {
      GetMaxExtracted(negative_heap, negative_delete_heap, delete_heap);
    } else if (input == "size") {
      std::cout << heap.size() - delete_heap.size() << '\n';
    }
  }
}
