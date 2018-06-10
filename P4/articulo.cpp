#include "articulo.hpp"
const Cadena& Articulo::referencia() const{return refe;}

const Cadena& Articulo::titulo() const {return tit;}

const Fecha& Articulo::f_publi() const{return f_pub;}

double& Articulo::precio()
{
  return pre;
}

double Articulo::precio() const
{
  return pre;
}


const Articulo::Autores& Articulo::autores() const
{
  return Au;
}

std::ostream& operator << (std::ostream& os,const Articulo& A)
{
  os<<"["<<A.referencia()<<"] \""<<A.titulo()<<"\", "<<"de ";
  auto autor = A.autores().begin();
  os<<(*autor)->apellidos();
  for(++autor;autor!=A.autores().end();++autor)
    os<<", "<<(*autor)->apellidos();
  os<<". "<<A.f_publi().anno()<<". "
  <<std::fixed<<std::setprecision(2)<<A.precio()<<" €"<<std::endl<<"\t";
  A.impresion_especifica(os);
  return os;
}
