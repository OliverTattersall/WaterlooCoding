module binarynum;

// bulk
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
        std::cin >> tmp;
        // std::cout << tmp << std::endl;
        if(tmp == '1'){
            tempArr[count] = 1;
            count++;
        }else if(tmp == '0'){
            tempArr[count] = 0;
            count++;
        }else if(tmp != ' ' && tmp != '\n'){
            break;
        }
        if(count == size){
            tempArr = copyover(tempArr, size, size*2);
            size *= 2;
        }
    }
    return tempArr;
}

BinaryNum readBinaryNum(){
    BinaryNum res = {0, 2, nullptr};

    // bool * tempArr = new bool[4];

    // char tmp;
    int count = 0;
    int size = 4;
    
    bool * tempArr = readBinChars(size, count);
    res.contents = new bool[size];
    // std::cout << count << std::endl;
    for(int i = count - 1; i >= 0; --i){
        // std::cout << tempArr[i];
        res.contents[i] = tempArr[count - 1 - i];
    }
    
    delete tempArr;
    res.capacity = size;
    res.size = count;

    return res;

}

void printArray(bool * arr, int size){
    for(int i =0; i < size; i++){
        std::cout << arr[i] << std::endl;
    }
}

void binaryConcat(BinaryNum &binNum) {
    int count = 0;
    int size = 4;
    bool * tempArr = readBinChars(size, count);
    // printArray(tempArr, count);
    // std::cout << count << std::endl;
    for(int i = 0; i < count / 2; ++i){
        bool temp = tempArr[i];
        // std::cout << temp << " " << tempArr[count - 1 - i] << std::endl;
        tempArr[i] = tempArr[count - 1 - i];
        tempArr[count - 1 - i] = temp;
        
    }
    // i = 0, temp = 1, temp[2-1-0] = 0
    // printArray(tempArr, count);
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
    out << binNum.contents[binNum.size - 1];
    for(int i = binNum.size - 2; i >= 0; --i){
        out << sep << binNum.contents[i];
        // out << "test";
    }
    out <<'\n';

} 

