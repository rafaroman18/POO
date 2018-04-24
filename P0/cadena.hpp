#ifndef CADENA_HPP
#define CADENA_HPP
#include <iostream>
#include <cstring>
class Cadena
{
public:
  explicit Cadena(size_t tam=0,char s=' ');
  Cadena(const Cadena& A);
  Cadena(const char* s);
  Cadena(const Cadena& A,size_t ind,size_t tam);
  Cadena substr(size_t ind,size_t tam)const;
  //Cadena (const char* cad,size_t lon);
  //const char * c_str() const;       ///AÑADIDO 1
  //Cadena(Cadena&& cad);           ///AÑADIDO 2
  size_t length() const noexcept;
  operator const char*()const noexcept;
  Cadena &operator =(const Cadena& A);
  Cadena &operator =(const char* s);
  Cadena& operator +=(const Cadena& e);
  char operator[] (size_t n) const noexcept;
  char& operator[](size_t n) noexcept;
  char& at(size_t n);
  char at(size_t n)const;
  ~Cadena();
private:
  char* s_;
  size_t tam_;
};

Cadena operator +(const Cadena& g, const Cadena& e);

bool operator > (const Cadena& a,const Cadena& b) noexcept;

bool operator < (const Cadena& a,const Cadena& b) noexcept;

bool operator ==(const Cadena& a,const Cadena& b) noexcept;

bool operator !=(const Cadena& a,const Cadena& b) noexcept;

bool operator <=(const Cadena& a,const Cadena& b) noexcept;

bool operator >=(const Cadena& a,const Cadena& b) noexcept;

#endif
