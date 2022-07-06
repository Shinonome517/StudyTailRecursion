#include <iostream>
#include <cstdint>

using namespace std;

int64_t sigma(int64_t n, int64_t ans){
    if(n <= 0){
        return ans;
    }
    else{
        return sigma(n - 1, ans + n);
    }
}

int main(){

    cout << "sigma(10): " << sigma(10, 0) << endl;
    cout << "sigma(100): " << sigma(100, 0) << endl;
    cout << "ans = " << 50000005000000 << endl;
    cout << "sigma(10000000): " << (int64_t)sigma(10000000, 0) << endl;

    cout << "Hello World" << endl;

}