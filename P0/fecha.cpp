

#include "fecha.hpp"
#include <ctime>
#include <iostream>
inline int Fecha::dia() const noexcept
{return dia_;}

inline int Fecha::mes() const noexcept
{return mes_;}

inline int Fecha::anno() const noexcept
{return anno_;}

void Fecha::valida()const
{
  if(anno_<AnnoMinimo || anno_>AnnoMaximo) throw Invalida("Año Erroneo");
  if(mes_<1 || mes_>12) throw Invalida("Mes Erroneo");
  int bisiesto= static_cast<int>((anno_%4==0)&&(anno_%400==0 || anno_%100!=0));
  if (dia_>diames[mes_]+bisiesto || dia_<1) throw Invalida("Dia Erroneo");
}


Fecha::Fecha(int dia,int mes,int anno):dia_(dia),mes_(mes),anno_(anno)
{
  std::time_t tiempo_calendario=std::time(nullptr);
  std::tm* tiempo_descompuesto=std::localtime(&tiempo_calendario);
  if(dia_==0)
  {
    dia_=tiempo_descompuesto->tm_mday;
  }
  if(mes_==0)
  {
    mes_=tiempo_descompuesto->tm_mon +1;
  }
  if(anno_==0)
  {
    anno_=tiempo_descompuesto->tm_year +1900;
  }
  valida();
}

Fecha::Fecha(const char* f)
{
  if(sscanf(f,"%d/%d/%4d",&dia_,&mes_,&anno_)!= 3 ) throw Invalida("Formato Invalido");
  if(dia_==0 || mes_==0 || anno_== 0)
  {
    std::time_t tiempo_calendario=std::time(nullptr);
    std::tm* tiempo_descompuesto=std::localtime(&tiempo_calendario);
    if(dia_==0)
    {
      dia_=tiempo_descompuesto->tm_mday;
    }
    if(mes_==0)
    {
      mes_=tiempo_descompuesto->tm_mon +1;
    }
    if(anno_==0)
    {
      anno_=tiempo_descompuesto->tm_year +1900;
    }
  }
valida();
}

Fecha& Fecha::operator += (int n)
{
  std::tm tiempo_descompuesto={0};
  tiempo_descompuesto.tm_mday=this->dia_+n;
  tiempo_descompuesto.tm_mon=this->mes_-1;
  tiempo_descompuesto.tm_year=this->anno_-1900;
  mktime(&tiempo_descompuesto);
  this->dia_=tiempo_descompuesto.tm_mday;
  this->mes_=tiempo_descompuesto.tm_mon+1;
  this->anno_=tiempo_descompuesto.tm_year+1900;
  valida();
  return *this;
}

Fecha& Fecha::operator -=(int n)
{
  return *this+=(-n);
}

Fecha Fecha::operator + (int n)const
{
  Fecha t=*this;
  return t+=n;
}

Fecha Fecha::operator -(int n)const
{
  Fecha t=*this;
  t+= (-n);
  return t;
}

Fecha& Fecha::operator ++()
{
  return *this+=1;
}

Fecha Fecha::operator ++(int)
{
  Fecha t=*this;
  ++*this;
  return t;
}

Fecha& Fecha::operator --()
{
  return *this+=(-1);
}


Fecha Fecha::operator --(int )
{
  Fecha t=*this;
  --*this;
  return t;
}

Fecha::operator const char* ()const
{
char* B=new char[50];
std::tm* tiempo_descompuesto=new tm;
*tiempo_descompuesto={0};
tiempo_descompuesto->tm_mday=this->dia_;
tiempo_descompuesto->tm_mon=this->mes_-1;
tiempo_descompuesto->tm_year=this->anno_-1900;
std::setlocale(LC_TIME, "es_ES.UTF-8");
mktime(tiempo_descompuesto);
strftime(B,50,"%A %d de %B de %Y",tiempo_descompuesto);
return B;
}

bool operator ==(const Fecha& cad1, const Fecha& cad2)
{
  return (cad1.dia()==cad2.dia() && cad1.mes()==cad2.mes() && cad1.anno()==cad2.anno());
}

bool operator != (const Fecha& feh, const Fecha& fech){
    return !(feh==fech);
}

bool operator < (const Fecha& cad1, const Fecha& cad2)
{
if(cad1.anno() < cad2.anno())
{
return true;
}
else
{
  if(cad1.anno() > cad2.anno() )
  {
    return false;
  }
  else
  {
    if(cad1.mes() < cad2.mes())
    {
      return true;
    }
    else
    {
      if(cad1.mes() > cad2.mes())
      {
        return false;
      }
      else
      {
          return (cad1.dia() < cad2.dia());
    }
  }
}
}
}

bool operator > (const Fecha& fecha1, const Fecha& fecha2){
    return fecha2 < fecha1 ;
}
bool operator <= (const Fecha& fecha1, const Fecha& fecha2){
    return ((fecha1 < fecha2) || (fecha1 == fecha2 )) ;
}
bool operator >= (const Fecha& fecha1, const Fecha& fecha2 )
{
    return (fecha1 > fecha2) || (fecha1 == fecha2 );
}
