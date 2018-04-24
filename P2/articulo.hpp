#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include "../P1/cadena.cpp"
#include "../P1/fecha.cpp"
#include <iomanip>
class Articulo
{
public:
Articulo(const Cadena R,const Cadena T,const Fecha F,const double P,const unsigned S):
                                              ref(R),tit(T),f_pub(F),pre(P),sto(S){};
Cadena referencia() const;
Cadena titulo() const;
Fecha f_publi() const;
double& precio();
double precio() const;
unsigned& stock();
unsigned stock() const;
private:
Cadena ref;
Cadena tit;
Fecha f_pub;
double pre;
unsigned sto;
};

std::ostream& operator << (std::ostream& os,Articulo& A)
{
  os<<"[ "<<A.referencia()<<"] \""<<A.titulo()<<"\", "<<A.f_publi().anno()<<". "
  <<std::setprecision(2)<<A.precio()<< "\u20AC"<<std::endl;
  return os;
}
#endif
