#include <iostream>

class Cvector{
    float real;
    float imag;
public:
    Cvector(){};
    Cvector(float x, float y) : real(x), imag(y) {};
    Cvector operator + (const Cvector&);
    Cvector operator - (const Cvector&);
    Cvector operator * (const Cvector&);
    float get_real(){ return real; };
    float get_imag(){ return imag; };
};


Cvector Cvector::operator+(const Cvector& vec){
    Cvector temp;
    temp.real = real + vec.real;
    temp.imag = imag + vec.imag;
    return temp;
}

Cvector Cvector::operator-(const Cvector& vec){
    Cvector temp;
    temp.real = real - vec.real;
    temp.imag = imag - vec.imag;
    return temp;
}

Cvector Cvector::operator* (const Cvector& vec){
    Cvector temp;
    temp.real = real*vec.real - imag*vec.imag;
    temp.imag = real*vec.imag + imag*vec.real;
    return temp;
}

int main(int argc, char const *argv[])
{
    Cvector vec1(1,2);
    Cvector vec2(3,4);
    Cvector vec3 = vec1 + vec2;
    Cvector vec4 = vec2 - vec1;
    Cvector vec5 = vec1 * vec2;
    std::cout << "The sum of two vectors: " << vec3.get_real() << " + " << vec3.get_imag() << "i\n";
    std::cout << "The minus of two vectors: " << vec4.get_real() << " + " << vec4.get_imag() << "i\n";
    std::cout << "The product of two vectors: " << vec5.get_real() << " + " << vec5.get_imag() << "i\n";
    return 0;
}
