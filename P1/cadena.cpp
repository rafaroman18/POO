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

Cadena::Cadena(const Cadena& A ):s_(new char[A.tam_+1]),tam_(A.tam_)//Constructor de copia
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

Cadena::Cadena(Cadena&& A):s_(A.s_),tam_(A.tam_) //Constructor de movimiento
{
  A.s_=nullptr;
  A.tam_=0;
}

Cadena& Cadena::operator=(Cadena&& A)
{
    delete[] s_;
    s_=A.s_;
    tam_=A.tam_;
    A.s_=nullptr;
    A.tam_=0;
    return *this;
}
Cadena::~Cadena()
{
  delete[] s_;
}

inline size_t Cadena::length() const noexcept  //Devuelve el tamaño de la cadena
{
  return tam_;
}

inline const char* Cadena::c_str()const noexcept  //Conversión a cadena de bajo nivel(puts)
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

//OPERADORES DE EXTRACCION E INSERCCION
std::istream &operator>>(std::istream& input,Cadena& A)
{
  int i=0;char* s=new char[33]; char save;
  while(isspace(input.get())!=0 && i<32) i++;
  input.unget();
  if(i<32)
  {
  i=0;
  while(!isspace(input.peek()) && i<32 && input.good())
  {
    input>>save;
    s[i]=save;
    i++;
  }
  s[i]='\0';
  }
  A=Cadena(s);
  delete[] s;
  return input;/*
  char* s = new char[33];
  input.width(33);
  input >> s;
  A = Cadena(s);
  delete[] s;
  return input;*/

}

std::ostream &operator<<(std::ostream& os,const Cadena& A)
{

  os<<A.c_str();
  return os;
}
//OPERADORES DE COMPARACION
bool operator < (const Cadena& a,const Cadena& b) noexcept
{
  return !(a>b) && !(a==b);
}

bool operator ==(const Cadena& a,const Cadena& b) noexcept
{
    return (strcmp(a.c_str(),b.c_str())==0);
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
     return (strcmp(a.c_str(),b.c_str())>0);
}
