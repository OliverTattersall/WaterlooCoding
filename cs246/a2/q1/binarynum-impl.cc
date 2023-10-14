module binarynum;

struct BinaryNum {
    int size = 0;         // number of elements the array currently holds
  int capacity;     // number of elements the array could hold, 
                    // given current memory allocation to contents
  bool *contents = nullptr;  
}

using namespace std;

bool* copyover(bool* old, int oldsize, int newsize){
    bool * res = new bool[newsize];
    for(int i = 0; i < oldsize; ++i){
        res[i] = old[i];
    }
    delete old;
    return res;
}

bool * readBinChars (int &size, int &count){
    bool * tempArr = new bool[4];

    char tmp;
    // int count = 0;
    // int size = 4;
    while(true){
        cin >> tmp;
        if(cin == '1'){
            tempArr[count] = 1;
            count++;
        }else if(cin == '0'){
            tempArr[count] = 0;
            count++;
        }else if(cin != ' ' && cin != '\n'){
            break;
        }
        if(count == size){
            tempArr = copyover(tempArr, size, size*2);
            size *= 2;
        }
    }
}

BinaryNum readBinaryNum(){
    BinaryNum res = {0, 2, nullptr};

    // bool * tempArr = new bool[4];

    // char tmp;
    int count = 0;
    int size = 4;
    // while(true){
    //     cin >> tmp;
    //     if(cin == '1'){
    //         tempArr[count] = 1;
    //         count++;
    //     }else if(cin == '0'){
    //         tempArr[count] = 0;
    //         count++;
    //     }else if(cin != ' ' && cin != '\n'){
    //         break;
    //     }
    //     if(count == size){
    //         tempArr = copyover(tempArr, size);
    //         size *= 2;
    //     }
    // }
    bool * tempArr = readBinChars(count, size);
    res.contents = new bool[size];
    for(int i = count - 1; i >= 0; --i){
        res.contents[i] = tempArr[count - 1 - i];
    }
    delete tempArr;
    res.capacity = size;
    res.size = count;

    return res;

}

void binaryConcat(BinaryNum &binNum) {
    int count = 0;
    int size = 4;
    bool * tempArr = readBinChars(size, count);
    for(int i = 0; i < count; ++i){
        bool temp = tempArr[i];
        tempArr[i] = tempArr[count - 1 - i];
        tempArr[count - 1 - i] = temp;
    }
    tempArr = copyover(tempArr, size, size + binNum.capacity);
    // if(count + binNum.size >= binNum.capacity){
    //     binNum.contents = copyover(binNum.contents, binNum.size, binNum.size + count);
    //     binNum.capacity = binNum.size + count;
        
    // }
    // binNum.size = binNum.size + count;
    binNum.capacity = size + binNum.capacity;
    binNum.size = count + binNum.size;


    for(int i = count; i < binNum.size; ++i){
        tempArr[i] = binNum.contents[i - count];
    }

    delete binNum.contents;
    binNum.contents = tempArr;


}


int binaryToDecimal(const BinaryNum &binNum) {
    int res = 0;
    int twopow = 1;
    for(int i = 0; i < binNum.size; ++i){
        res += binNum.contents[i] * twopow;
        twopow *= 2;
    }

    return res;
    
}

void printBinaryNum(std::ostream &out, const BinaryNum &binNum, char sep){
    for(int i = 0; i < binNum.size - 1; ++i){
        out << binNum.contents[i] << sep;
    }
    out << binNum.contents[binNum.size - 1] << '\n';

} 

