#include "bitarray.h"

BitArray::BitArray(): sie(0), bits(nullptr){}
BitArray::~BitArray(){
    delete[] bits;
}

BitArray::BitArray(int num_bits, unsigned long value){
    sie = num_bits;
    if(sie < 32){
        bits = new bool[sie];
        memset(bits, value, sizeof(bool)*sie);
    }
    else{
        bits = new bool[sie];
        memset(bits, value, sizeof(long)*sizeof(bool));
    }
}
BitArray::BitArray(const BitArray& other): sie(other.sie), bits(new bool[other.sie]){
    memcpy(bits, other.bits, sie*sizeof(bool));
}

BitArray::BitArray(BitArray&& other) noexcept : sie(other.sie), bits(other.bits){
    other.sie = 0;
    other.bits = nullptr;
}
void BitArray::swap(BitArray& other){
    std::swap(sie, other.sie);
    std::swap(bits, other.bits);
}

BitArray& BitArray::operator=(const BitArray& other){
    if(this != &other){
        delete[] bits;
        this->sie = other.sie;
        bits = new bool[sie];
        memcpy(bits, other.bits, sie*sizeof(bool));
    }
    return *this;
}

BitArray& BitArray::operator=(BitArray&& other) noexcept{
    if(this != &other){
        delete[] bits;
        sie = other.sie;
        bits = other.bits;
        other.sie = 0;
        other.bits = nullptr;
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value){
    bool* temp = new bool[num_bits];
    if (num_bits < sie){
        for(int i = 0; i < num_bits; i++){
            temp[i] = bits[i];
        }
    }
    if(num_bits > sie){
        for(int i = 0; i < sie; i++){
            temp[i] = bits[i];
        }
        for(int i = sie; i < num_bits; i++){
            temp[i] = value;
        }
    }
    delete[] bits;
    bits = temp;
    sie = num_bits;
}
void BitArray::clear(){
    delete[] bits;
    bits = nullptr;
    sie = 0;
}
void BitArray::push_back(bool bit){
    resize(sie+1, bit);
}

BitArray& BitArray::operator&=(const BitArray& b){
    for(int i = 0; i < sie; i++){
        bits[i] &= b.bits[i];
    }
    return *this;
}
BitArray& BitArray::operator|=(const BitArray& b){
    for(int i = 0; i < sie; i++){
        bits[i] |= b.bits[i];
    }
    return *this;
}
BitArray& BitArray::operator^=(const BitArray& b){
    for(int i = 0; i < sie; i++){
        bits[i] ^= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n){
    for(int i = 0; i < size() - n; i++){
        bits[i] = bits[i+n];
    }
    for(int i = size() - n; i < size(); i++){
        bits[i] = 0;
    }
    return *this;
}
BitArray& BitArray::operator>>=(int n){
    for(int i = size(); i < n; i--){
        bits[i] = bits[i-1];
    }
    for(int i = size() - n; i < n; i++){
        bits[i] = 0;
    }
    return *this;
}
BitArray BitArray::operator<<(int n) const{
    BitArray temp(size());
    for(int i = 0 ; i < size() - n; i++){
        temp.bits[i] = bits[i+n];
    }
    for(int i = size()-n; i < size(); i++){
        temp.bits[i] = 0;
    }
    return temp;
}
BitArray BitArray::operator>>(int n) const{
    BitArray temp(size());
    for(int i = size(); i < n; i--){
        temp.bits[i] = bits[i - n];
    }
    for(int i = 0; i < n; i++){
        temp.bits[i] = 0;
    }
    return temp;
}

BitArray& BitArray::set(int n, bool val){
    bits[n] = val;
    return *this;
}
BitArray& BitArray::set(){
    memset(bits, true, sie*sizeof(bool));
    return *this;
}

BitArray& BitArray::reset(int n){
    bits[n] = false;
    return *this;
}
BitArray& BitArray::reset(){
    memset(bits, false, sie*sizeof(bool));
    return *this;
}

bool BitArray::any() const{
    for(int i = 0; i < sie; i++){
        if(bits[i] == true) return true;
    }
    return false;
}
bool BitArray::none() const{
    for(int i = 0; i < sie; i++){
        if(bits[i] == true) return false;
    }
    return true;
}
BitArray BitArray::operator~() const{
    for(int i = 0; i < sie; i ++){
        bits[i] = ~bits[i];
    }
    return *this;
}
int BitArray::count() const{
    int cnt = 0;
    for(int i = 0; i < sie; i++){
        if(bits[i] == 1) cnt++;
    }
    return cnt;
}

bool BitArray::operator[](int i) const{
    return bits[i];
}

int BitArray::size() const{
    return sie;
}
bool BitArray::empty() const{
    return sie == 0;
}

std::string BitArray::to_string() const{
    std::string tmp ="";
    for(int i = 0; i < sie; i++){
        if(bits[i]==1){
            tmp.push_back('1');
        }
        else{
            tmp.push_back('0');
        }
    }
    return tmp;
}


bool operator==(const BitArray& a, const BitArray& b){
    return (a.size() == b.size() && (a.to_string() == b.to_string()));
}
bool operator!=(const BitArray& a, const BitArray& b){
    return !(a == b);
}

BitArray operator&(const BitArray & b1, const BitArray& b2){
    BitArray b(b1);
    return (b &= b2);
}
BitArray operator|(const BitArray & b1, const BitArray& b2){
    BitArray b(b1);
    return(b |= b2);
}
BitArray operator^(const BitArray & b1, const BitArray& b2){
    BitArray b(b1);
    return (b ^= b2);
}
