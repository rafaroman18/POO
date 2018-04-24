#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <cstring>
extern "C"{
#include <unistd.h>
}
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
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

class Usuario
{
public:
  typedef std::unordered_set<Cadena> Usuarios;
  typedef std::unordered_map<Articulo*,unsigned int> Articulos;
  typedef std::map<Numero, Tarjeta*> Tarjetas;
  //Constructor
  Usuario(Cadena id_,Cadena nombre_,Cadena apell_,Cadena dir_,Clave contr_);
  //Constructor Copia (PROHIBIDO)
  Usuario(const Usuario&)=delete;
  //Constructor de asignacion (PROHIBIDO)
  Usuario& operator=(const Usuario&)=delete;
  //Relacion Usuario-Tarjeta
  void es_titular_de(Tarjeta& tarjeta);
  void no_es_titular_de(Tarjeta& tarjeta);
  //Relacion Usuario-Articulo
  void compra(Articulo& articulo,unsigned int cantidad=1);
  const Articulo& compra() const;
  //Métodos observadores
  Cadena id() const{return identificador;};
  Cadena nombre() const{return nomb;};
  Cadena apell() const{return apellidos;};
  Cadena dir() const{return direccion;};
  const Tarjetas& tarjetas() const;
  //Clase Excepcion
  class Id_duplicado
  {
  public:
    Id_duplicado(Cadena A):ID(A){}
    Cadena idd() const{return ID;}
  private:
    Cadena ID;
  };
  //Destructor
  ~Usuario();
private:
  Cadena identificador,nomb,apellidos,direccion; Clave contr;
  Tarjetas tarjetas_;  //Enlaces
  Articulos articulos;
};

#endif
