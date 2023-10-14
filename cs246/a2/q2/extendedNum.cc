// #include <iostream>
// #include <sstream>
// #include <string>
#include "extendedNum.h"

using namespace std;

// extendedNum :: extendedNum(bool special = false, string word = "", int val = 0):
//         special {special}, word {word}, val {val} {}

extendedNum extendedNum :: operator+(const extendedNum &rhs) const {
    extendedNum res = {false, "", 0};

    if(special){
        res.special=true;
        int parity = 0;
        if(word == "+infinity"){
            parity = 1;
        }else if(word == "-infinity"){
            parity = -1;
        }

        if(parity == 0){
            res.word = "undefined";
            return res;
        }
        
        if(rhs.special){
            int parity2 = 0;
            if(rhs.word == "+infinity"){
            parity2 = 1;
            }else if(rhs.word == "-infinity"){
                parity2 = -1;
            }
            if(parity2 == 0){
                res.word = "undefined";
                return res;
            }

            int math = parity + parity2;

            if(math == 0){
                res.word = "undefined";
            }else if(math == -2){
                res.word = "-infinity";
            }else{
                res.word = "+infinity";
            }
            return res;
        }

        res.word = word;
        return res;
    }else{
        if(rhs.special){
            return rhs + *this;
        }
    }
    res.val = val + rhs.val;
    return res;

}

extendedNum extendedNum :: operator-(const extendedNum &rhs) const {
    extendedNum res = {false, "", 0};
    extendedNum res2 = *this + (-rhs);
    return res2;

}

extendedNum extendedNum :: operator*(const extendedNum &rhs) const {
    extendedNum res = {false, "", 0};

    if(special){
        res.special=true;
        int parity = 0;
        if(word == "+infinity"){
            parity = 1;
        }else if(word == "-infinity"){
            parity = -1;
        }

        if(parity == 0){
            res.word = "undefined";
            return res;
        }

        int other = 0;

        if(rhs.special){
            if(rhs.word == "+infinity"){
                other = 1;
            }else if(rhs.word == "-infinity"){
                other = -1;
            }
        }else{
            other = rhs.val;
        }

        int math = parity * other;
        if(math == 0){
            res.word = "undefined";
            return res;
        }else if(math < 0){
            res.word = "-infinity";
        }else{
            res.word = "+infinity";
        }

        return res;

    }else if(rhs.special){
        return rhs * *this;
    }

    res.val = val * rhs.val;

    return res;

}




extendedNum extendedNum :: operator/(const extendedNum &rhs) const {
    extendedNum res = {false, "", 0};

    if(special){
        res.special = true;
        if(rhs.special){
            res.word = "undefined";
            return res;
        }

        int parity = 0;
        if(word == "+infinity"){
            parity = 1;
        }else if(word == "-infinity"){
            parity = -1;
        }

        if(parity == 0){
            res.word = "undefined";
            return res;
        }


        int math = parity * rhs.val;

        if(math > 0){
            res.word = "+infinity";
        }else if(math < 0){
            res.word = "-infinity";
        }else{
            if(parity == 1){
                res.word = "+infinity";
            }else{
                res.word = "-infinity";
            }
        }

        return res;

    }else{
        if(rhs.special){
            if(rhs.word == "undefined"){
                res.special = true;
                res.word = "undefined";
                return res;
            }

            return res;
        }

        if(rhs.val == 0){
            res.special = true;
            if(val == 0){
                res.word = "undefined";
                
            }else if(val > 0){
                res.word = "+infinity";

            }else{
                res.word = "-infinity";
            }
            return res;

        }

        // res.val = val / rhs.val;
        // return res;
    }

    res.val = val / rhs.val;
    return res;

}

extendedNum extendedNum :: operator-() const {
    extendedNum tmp = {false, "", -1};
    return *this * tmp;
    // if(special){
    //     res.special = true;
    //     if(word == "undefined"){
    //         res.word = "undefined";
    //     }else if(word == "+infinity"){
    //         res.word = "-infinity";
    //     }
    // }
} 

// struct extendedNum {
//   /* Add your data fields and constructor here*/
//     bool special;
//     string word;
//     int val;

    // extendedNum(bool special = false, string word = "", int val = 0):
    //     special {special}, word {word}, val {val} {}

    // extendedNum operator+(const extendedNum &rhs) const {
    //     extendedNum res = {false, "", 0};

    //     if(special){
    //         res.special=true;
    //         int parity = 0;
    //         if(word == "+infinity"){
    //             parity = 1;
    //         }else if(word == "-infinity"){
    //             parity = -1;
    //         }

    //         if(parity == 0){
    //             res.word = "undefined";
    //             return res;
    //         }
            
    //         if(rhs.special){
    //             int parity2 = 0;
    //             if(rhs.word == "+infinity"){
    //             parity2 = 1;
    //             }else if(rhs.word == "-infinity"){
    //                 parity2 = -1;
    //             }
    //             if(parity2 == 0){
    //                 res.word = "undefined";
    //                 return res;
    //             }

    //             int math = parity + parity2;

    //             if(math == 0){
    //                 res.word = "undefined";
    //             }else if(math == -2){
    //                 res.word = "-infinity";
    //             }else{
    //                 res.word = "+infinity";
    //             }
    //             return res;
    //         }

    //         res.word = word;
    //         return res;
    //     }else{
    //         if(rhs.special){
    //             return rhs + *this;
    //         }
    //     }
    //     res.val = val + rhs.val;
    //     return res;

    // }
    // extendedNum operator-(const extendedNum &rhs) const {
    //     extendedNum res = {false, "", 0};
    //     extendedNum res2 = *this + (-rhs);
    //     return res2;
    //     // if(special){
    //     //     res.special=true;
    //     //     int parity = 0;
    //     //     if(word == "+infinity"){
    //     //         parity = 1;
    //     //     }else if(word == "-infinity"){
    //     //         parity = -1;
    //     //     }

    //     //     if(parity == 0){
    //     //         res.word = "undefined";
    //     //         return res;
    //     //     }
            
    //     //     if(rhs.special){
    //     //         int parity2 = 0;
    //     //         if(rhs.word == "+infinity"){
    //     //         parity2 = 1;
    //     //         }else if(rhs.word == "-infinity"){
    //     //             parity2 = -1;
    //     //         }
    //     //         if(parity2 == 0){
    //     //             res.word = "undefined";
    //     //             return res;
    //     //         }

    //     //         int math = parity + parity2;

    //     //         if(math != 0){
    //     //             res.word = "undefined";
    //     //         }else if(parity == -1){
    //     //             res.word = "-infinity";
    //     //         }else{
    //     //             res.word = "+infinity";
    //     //         }
    //     //         return res;
    //     //     }

    //     //     res.word = word;
    //     //     return res;
    //     // }

    //     // res.val = val - rhs.val;
    //     // return res; 

    // }
    // extendedNum operator*(const extendedNum &rhs) const {
    //     extendedNum res = {false, "", 0};

    //     if(special){
    //         res.special=true;
    //         int parity = 0;
    //         if(word == "+infinity"){
    //             parity = 1;
    //         }else if(word == "-infinity"){
    //             parity = -1;
    //         }

    //         if(parity == 0){
    //             res.word = "undefined";
    //             return res;
    //         }

    //         int other = 0;

    //         if(rhs.special){
    //             if(rhs.word == "+infinity"){
    //                 other = 1;
    //             }else if(rhs.word == "-infinity"){
    //                 other = -1;
    //             }
    //         }else{
    //             other = rhs.val;
    //         }

    //         int math = parity * other;
    //         if(math == 0){
    //             res.word = "undefined";
    //             return res;
    //         }else if(math < 0){
    //             res.word = "-infinity";
    //         }else{
    //             res.word = "+infinity";
    //         }

    //         return res;

    //     }else if(rhs.special){
    //         return rhs * *this;
    //     }

    //     res.val = val * rhs.val;

    //     return res;

    // }




    // extendedNum operator/(const extendedNum &rhs) const {
    //     extendedNum res = {false, "", 0};

    //     if(special){
    //         res.special = true;
    //         if(rhs.special){
    //             res.word = "undefined";
    //             return res;
    //         }

    //         int parity = 0;
    //         if(word == "+infinity"){
    //             parity = 1;
    //         }else if(word == "-infinity"){
    //             parity = -1;
    //         }

    //         if(parity == 0){
    //             res.word = "undefined";
    //             return res;
    //         }


    //         int math = parity * rhs.val;

    //         if(math > 0){
    //             res.word = "+infinity";
    //         }else if(math < 0){
    //             res.word = "-infinity";
    //         }else{
    //             if(parity == 1){
    //                 res.word = "+infinity";
    //             }else{
    //                 res.word = "-infinity";
    //             }
    //         }
    //     }else{
    //         if(rhs.special){
    //             if(rhs.word == "undefined"){
    //                 res.special = true;
    //                 res.word = "undefined";
    //                 return res;
    //             }

    //             return res;
    //         }

    //         if(rhs.val == 0){
    //             res.special = true;
    //             if(val == 0){
    //                 res.word = "undefined";
                    
    //             }else if(val > 0){
    //                 res.word = "+infinity";

    //             }else{
    //                 res.word = "-infinity";
    //             }
    //             return res;

    //         }

    //         res.val = val / rhs.val;
    //         return res;
    //     }

    // }

    // extendedNum operator-() const {
    //     extendedNum tmp = {false, "", -1};
    //     return *this * tmp;
    //     // if(special){
    //     //     res.special = true;
    //     //     if(word == "undefined"){
    //     //         res.word = "undefined";
    //     //     }else if(word == "+infinity"){
    //     //         res.word = "-infinity";
    //     //     }
    //     // }
    // } 
// };

std::ostream &operator<<(std::ostream &out, const extendedNum &rat) {
    if(rat.special){
        out << rat.word;
    }else{
        out << rat.val;
    }

    return out;
}

std::istream &operator>>(std::istream &in, extendedNum &rat) {
    rat.special = false;
    rat.word = "";
    rat.val = 0;
    int tmp;
    string temp2;
    in >> temp2;

    stringstream sock{temp2};
    if(sock >> tmp){
        rat.val = tmp;
    }else{
        rat.special = true;
        rat.word = temp2;
    }

    return in;
    
}
