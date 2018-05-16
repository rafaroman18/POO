#include "articulo.hpp"
Cadena Articulo::referencia() const{return refe;}

Cadena Articulo::titulo() const {return tit;}

Fecha Articulo::f_publi() const{return f_pub;}

double& Articulo::precio()
{
  return pre;
}

double Articulo::precio() const
{
  return pre;
}

unsigned& Articulo::stock()
{
  return sto;
}

unsigned Articulo::stock() const
{
  return sto;
}

std::ostream& operator << (std::ostream& os,Articulo& A)
{
  os<<"["<<A.referencia()<<"] \""<<A.titulo()<<"\", "<<A.f_publi().anno()<<". "
  <<std::fixed<<std::setprecision(2)<<A.precio()<<" \u20AC"<<std::endl;
  return os;
}
