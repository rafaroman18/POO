#include "cadena.hpp"
#include <stdexcept>
Cadena::Cadena(size_t tam,char s):s_(new char[tam+1]),tam_(tam)
{
    for (size_t i = 0; i < tam; i++)
    {
        s_[i]=s;
    }
    s_[tam_]='\0';
}

Cadena::Cadena(const char* s):s_(new char [strlen(s)+1]),tam_(strlen(s))//Constructor mediante cadena
{
strcpy(s_,s);
}

Cadena::Cadena(const Cadena& A ):s_(new char[A.tam_+1]),tam_(A.tam_)//Constructor mediante otro objeto CADENA
{
  strcpy(s_,A.s_);
}

Cadena::Cadena(const Cadena& A,size_t ind, size_t tam):s_(new char[tam+1]),tam_(tam)
{
size_t i;
for(i=0;i<tam;i++)
{
  s_[i]=A[i+ind];
}
s_[tam_]='\0';
}
/*
Cadena::Cadena(const char* cad,size_t lon):s_(new char[lon+1]),tam_(lon)
{
  size_t i;
  for(i=0;i<lon;i++)
  {
    s_[i]=cad[i];
  }
  s_[tam_]='\0';
}*/
Cadena::~Cadena()
{
  delete[] s_;
}

inline size_t Cadena::length() const noexcept  //Devuelve el tamaño de la cadena
{
  return tam_;
}
/*
inline const char* Cadena::c_str() const
{
  return s_;
}*/

inline Cadena::operator const char*()const noexcept  //Conversión a cadena de bajo nivel(puts)
{
  return s_;
}

Cadena& Cadena::operator +=(const Cadena& e)
{
  Cadena t=*this;
  tam_=t.tam_+e.tam_;
  delete [] s_;
  s_=new char[tam_+1];
  strcpy(s_,t.s_);
  strcat(s_,e.s_);
  return *this;
}


Cadena operator + (const Cadena& g, const Cadena& e)
{
  return Cadena(g)+=e;
}

Cadena& Cadena::operator = (const Cadena& A)   //Operador de asignación
{                                      //mediante el paso de otro objeto Cadena
  if(this!=&A)
  {
    delete [] s_;
    tam_=A.tam_;
    s_=new char[tam_+1];
    strcpy(s_,A.s_);
  }
  return *this;
}

Cadena& Cadena::operator =(const char* s) //Operado de asignación
{                                         //mediante el paso de una cadena de caracteres
  delete [] s_;
  tam_=strlen(s);
  s_=new char[tam_+1];
  strcpy(s_,s);
  return *this;
}

char Cadena::at(size_t n)const
{
if(n>=tam_) throw std::out_of_range("Fuera de rango");
return s_[n];
}

char& Cadena::at(size_t n)
{
  if(n>=tam_) throw std::out_of_range("Fuera de rango");
  return s_[n];
}

inline char Cadena::operator[] (size_t n)const noexcept //MIRAR ESTE MISMO OPERADOR PERO CON CADENA&
{
  return s_[n];
}

char& Cadena::operator[] (size_t n) noexcept
{
  return s_[n];
}
Cadena Cadena::substr(size_t ind,size_t tam)const
{
if(ind >= this->length() || ind+tam > this->length() || ind+tam < ind )throw std::out_of_range("Fuera de rango");
  return Cadena(*this,ind,tam);
}

bool operator < (const Cadena& a,const Cadena& b) noexcept
{
  return !(a>b) && !(a==b);
}

bool operator ==(const Cadena& a,const Cadena& b) noexcept
{
    return (strcmp(a,b)==0);
}

bool operator !=(const Cadena& a,const Cadena& b) noexcept
{
    return !(a==b);
}

bool operator <=(const Cadena& a,const Cadena& b) noexcept
{
  return (!(a>b));
}

bool operator >=(const Cadena& a,const Cadena& b) noexcept
{
  return ((a>b) || (a==b));
}

bool operator > (const Cadena& a,const Cadena& b) noexcept
{
     return (strcmp(a,b)>0);
}
