#ifndef FECHA_HPP
#define FECHA_HPP
#include <cstring>
#include <iostream>
static const int diames[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
class Fecha
{
  public:
  explicit Fecha(int dia=0,int mes=0,int anno=0);    //Constructor con parámetros
  Fecha(const char* f);                     //Constructor con caracteres
  int dia() const noexcept;
  int mes() const noexcept;
  int anno() const noexcept;
  static const int AnnoMinimo = 1902;
  static const int AnnoMaximo = 2037;
  Fecha& operator += (int);
  Fecha& operator -=(int );
  Fecha operator + (int )const;
  Fecha operator -(int )const;
  Fecha& operator ++();
  Fecha operator ++(int);
  Fecha& operator --();
  Fecha operator --(int );
  operator const char* ()const;
  class Invalida
  {
  public:
    Invalida(const char* err):err_(err){};
    const char* por_que()const{return err_;};
  private:
    const char* err_;
  };
  private:
  int dia_,mes_,anno_;
  void valida() const;
};

bool operator == (const Fecha&, const Fecha&);
bool operator != (const Fecha&, const Fecha&);
bool operator < (const Fecha&, const Fecha&);
bool operator > (const Fecha&, const Fecha&);
bool operator <= (const Fecha&, const Fecha&);
bool operator >= (const Fecha&, const Fecha&);




#endif
