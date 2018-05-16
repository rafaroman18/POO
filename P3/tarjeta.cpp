#include "tarjeta.hpp"
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <functional>
bool luhn(const Cadena& numero);
#define LAMBDA [](const char X){return std::isspace(X);}
//NUMERO
Numero::Numero(Cadena num)
{
  std::remove_if(num.begin(),num.end()+1,LAMBDA); //+1!!!!!!
  if(num.length()< 13 || num.length() > 19) throw Incorrecto(LONGITUD);
  if(std::find_if(num.begin(),num.end(),std::not1(EsDigito()))) throw Incorrecto(DIGITOS);
  if(!luhn(num))throw Incorrecto(NO_VALIDO);
  number = num;
}

bool operator<(const Numero& A,const Numero& B)noexcept
{
return strcmp(A,B)<0;
};


//TARJETA
Tarjeta::Tarjeta(Tipo tipo,const Numero& numero,Usuario& titular,const Fecha& caduc):tipo_(tipo),numero_(numero),titular_(&titular),caduc_(caduc),titular_f(titular.nombre()+" "+titular.apellidos())
{
if(caduc<=Fecha()) throw Caducada(caduc);
 titular.es_titular_de(*this);
}

std::ostream& operator<<(std::ostream& os,const Tarjeta& T)
{

  os<<T.tipo()<<std::endl<<T.numero()<<std::endl<<T.titular_facial()<<std::endl<<"Caduca:"<<std::setfill('0')<<std::setw(2)<<T.caducidad().mes()<<"/"<<T.caducidad().anno()%100<<std::endl;
  return os;
}

std::ostream& operator<<(std::ostream& os,const Tarjeta::Tipo& T)
{
const char* s;
switch(T)
{
  case 0:s="VISA";break;
  case 1:s="Mastercard";break;
  case 2:s="Maestro";break;
  case 3:s="JCB";break;
  case 4:s="AmericanExpress";break;
}
os<<s;
return os;
}

bool operator<(const Tarjeta& A,const Tarjeta& B)
{
  return A.numero()<B.numero();
}

Tarjeta::~Tarjeta()
{
  if(Usuario* us=const_cast<Usuario*>(titular_))
  us->no_es_titular_de(*this);
}
