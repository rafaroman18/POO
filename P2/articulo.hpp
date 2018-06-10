#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iomanip>
class Articulo
{
public:
Articulo(const Cadena& R,const Cadena& T,const Fecha F,double P,unsigned S):refe(R),tit(T),f_pub(F),pre(P),sto(S){};
//METODOS OBSERVADORES
Cadena referencia() const;
Cadena titulo() const;
Fecha f_publi() const;
double precio() const;
unsigned stock() const;
//METODOS MODIFICADORES
double& precio();
unsigned& stock();
private:
Cadena refe;
Cadena tit;
Fecha f_pub;
double pre;
unsigned sto;
};
//OPERADOR DE INSERCCION
std::ostream& operator << (std::ostream& os,Articulo& A);
#endif
