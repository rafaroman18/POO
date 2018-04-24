#ifndef CADENA_HPP
#define CADENA_HPP
#include <iostream>
#include <cstring>
#include <cctype>
class Cadena
{
public:
  explicit Cadena(size_t tam=0,char s=' ');
  Cadena(const Cadena& A); //Constructor de copia
  Cadena(const char* s);  //Constructor mediante cadena de caracteres
  Cadena(const Cadena& A,size_t ind,size_t tam);
  Cadena substr(size_t ind,size_t tam)const;
  Cadena (Cadena&& ); //Constructor de movimiento
  Cadena& operator=(Cadena&& ); //Asignación de movimiento
  size_t length() const noexcept;
  const char* c_str()const noexcept;
  Cadena &operator =(const Cadena& A);
  Cadena &operator =(const char* s);
  Cadena& operator +=(const Cadena& e);
  char operator[] (size_t n) const noexcept;
  char& operator[](size_t n) noexcept;
  char& at(size_t n);
  char at(size_t n)const;
  typedef char* iterator;
  typedef char const* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  iterator begin() noexcept { return s_; }
  iterator end() noexcept { return (s_+tam_); }
  const_iterator begin() const noexcept { return s_;}
  const_iterator end() const noexcept { return s_+tam_; }
  const_iterator cbegin() const noexcept { return s_; }
  const_iterator cend() const noexcept { return (s_+tam_);}
  reverse_iterator rbegin() noexcept { return reverse_iterator(end());}
  reverse_iterator rend() noexcept { return reverse_iterator(begin());}
  const_reverse_iterator rbegin() const noexcept {return const_reverse_iterator(end());}
  const_reverse_iterator rend() const noexcept {return const_reverse_iterator(begin());}
  const_reverse_iterator crbegin() const noexcept {return const_reverse_iterator(end());}
  const_reverse_iterator crend() const noexcept {return const_reverse_iterator(begin());}
  ~Cadena();
private:
  char* s_;
  size_t tam_;

};
//OPERADORES DE INSERCCION Y EXTRACCION
std::istream &operator>>(std::istream& input,Cadena& A);
std::ostream &operator<<(std::ostream& os,const Cadena& A);

//OPERADORES DE COMPARACION
Cadena operator +(const Cadena& g, const Cadena& e);

bool operator > (const Cadena& a,const Cadena& b) noexcept;

bool operator < (const Cadena& a,const Cadena& b) noexcept;

bool operator ==(const Cadena& a,const Cadena& b) noexcept;

bool operator !=(const Cadena& a,const Cadena& b) noexcept;

bool operator <=(const Cadena& a,const Cadena& b) noexcept;

bool operator >=(const Cadena& a,const Cadena& b) noexcept;

namespace std {
template <> struct hash<Cadena> {
size_t operator()(const Cadena& cad) const
{ // conversión const char* ->string
return hash<string>{}(cad.c_str());
}
};
}
#endif
