#ifndef USUARIO_HPP
#define  USUARIO_HPP
#include "../P1/fecha.cpp"
#include "../P1/cadena.cpp"
#include <map>
class Usuario
{
public:
  typedef std::map<Numero, Tarjeta*> Tarjetas;

  void posee(Tarjeta& tarjeta);
  const Tarjetas& posee() const;
private:
  Tarjetas tarjetas;  //Enlaces
  Cadena id,nombre,apellidos,direccion;
  Clave contr;

}
#endif
