#ifndef TARJETA_HPP
#define  TARJETA_HPP
#include "../P1/fecha.cpp"
#include "../P1/cadena.cpp"
#include "usuario.cpp"
#include "tarjeta.cpp"
class Numero
{

};
class Tarjeta
{
public:
  Tarjeta(const Numero&, Usuario&);
  void anula_titular(){const_cast<Usuario*&>(titular_)=nullptr;};
  ~Tarjeta();
  Numero numero() const;
  const Usuario* titular() const;
private:
  Numero numero_;
  const Usuario* titular_;
};

#endif
