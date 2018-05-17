#include "tarjeta.hpp"
#include <cctype>
#include <iomanip>
#include <algorithm>
bool luhn(const Cadena& numero);

//NUMERO
Numero::Numero(Cadena num)
{
  Cadena tmp;
  for(Cadena::iterator i=num.begin();i!=num.end();i++)
  {
    if(!std::isspace(*i))
    {
      if(!std::isdigit(*i)) throw Incorrecto(DIGITOS);
      tmp+=Cadena(1,*i);
    }
  }
  if(tmp.length()< 13 || tmp.length() > 19) throw Incorrecto(LONGITUD);
  if(!luhn(tmp))throw Incorrecto(NO_VALIDO);
  number = tmp;
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
