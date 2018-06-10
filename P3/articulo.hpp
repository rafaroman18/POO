#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include <iomanip>
#include "../P1/cadena.hpp"
#include "fecha.hpp"
class Articulo
{
public:
Articulo(const Cadena& R,const Cadena& T,const Fecha F,double P,unsigned S):refe(R),tit(T),f_pub(F),pre(P),sto(S){};
Cadena referencia() const;
Cadena titulo() const;
Fecha f_publi() const;
double& precio();
double precio() const;
unsigned& stock();
unsigned stock() const;
private:
Cadena refe;
Cadena tit;
Fecha f_pub;
double pre;
unsigned sto;
};

std::ostream& operator << (std::ostream& os,Articulo& A);
#endif
