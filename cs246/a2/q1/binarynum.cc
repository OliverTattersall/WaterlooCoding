export module binarynum;
import <string>;
import <iostream>;

export struct BinaryNum {
  int size = 0;         // number of elements the array currently holds
  int capacity;     // number of elements the array could hold, 
                    // given current memory allocation to contents
  bool *contents = nullptr;   // (pointer to) heap-allocated array of bools
};

export BinaryNum readBinaryNum(); 
export void binaryConcat(BinaryNum &binNum); 
export int binaryToDecimal(const BinaryNum &binNum); 
export void printBinaryNum(std::ostream &out, const BinaryNum &binNum, char sep); 

