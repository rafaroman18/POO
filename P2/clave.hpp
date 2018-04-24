#ifndef CLAVE_HPP
#define CLAVE_HPP
#include "../P1/cadena.cpp"
#include "../P1/fecha.cpp"
enum raz{CORTA,ERROR_CRYPT};

class Clave
{
public:
  class Incorrecta
  {
  public:
  Incorrecta(raz R):Razon(R){}
  raz razon() const{return Razon;}
  private:
    raz Razon;
  };

  Clave (const char* C);
  const char* clave() const;
  bool verifica(const char* V);
private:
Cadena con_cif;
};
#endif
