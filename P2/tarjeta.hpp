#ifndef TARJETA_HPP
#define  TARJETA_HPP
#include <ostream>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"
//NUMERO
class Numero
{
public:
  enum Rzn {LONGITUD,DIGITOS,NO_VALIDO};
  Numero(Cadena num_);
  operator const char*()const noexcept{return number.c_str();};
  class Incorrecto
  {
  public:
    Incorrecto(Rzn RZN):Razon(RZN){}
    Rzn razon() const {return Razon;}
  private:
    Rzn Razon;
  };
private:
  Cadena number;
};

bool operator <(const Numero& A,const Numero& B) noexcept;



class Usuario;


//TARJETA
class Tarjeta
{
public:
  enum Tipo{VISA,Mastercard,Maestro,JCB,AmericanExpress};
  Tarjeta(Tipo tipo,const Numero& numero,Usuario& titular,const Fecha& caduc);
  Tarjeta (const Tarjeta&)=delete;
  Tarjeta& operator=(const Tarjeta&)=delete;
  void anula_titular(){const_cast<Usuario*&>(titular_)=nullptr;};
  //OBSERVADORES
  Tipo tipo()const{return tipo_;}
  Numero numero() const{return numero_;}
  const Usuario* titular() const {return titular_;}
  Fecha caducidad() const {return caduc_;}
  Cadena titular_facial() const{return titular_f;}
  class Caducada
  {
  public:
    Caducada(Fecha F):Cad(F){}
    Fecha cuando() const{return Cad;}
  private:
    Fecha Cad;
  };
  ~Tarjeta();
  private:
  Tipo tipo_;
  Numero numero_;
  const Usuario* titular_;
  Fecha caduc_;
  Cadena titular_f;
};

std::ostream& operator<<(std::ostream& os,const Tarjeta& T);
std::ostream& operator<<(std::ostream& os,const Tarjeta::Tipo& T);
bool operator<(const Tarjeta& A,const Tarjeta& B);

#endif
