#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <cstdlib>
#include <ctime>
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
class Numero;
class Tarjeta;

//CLAVE
class Clave
{
public:
  enum Razon {CORTA,ERROR_CRYPT};
  Clave (const char* contrasenna);
  class Incorrecta
  {
  public:
  Incorrecta(Razon RZN):rzn(RZN){}
  Razon razon() const{return rzn;}
  private:
    Razon rzn;
  };
  const Cadena& clave() const;
  bool verifica(const char* ppassword) const;
private:
Cadena password;
};


//USUARIO
class Usuario
{
public:
  typedef std::unordered_map<Articulo*,unsigned int> Articulos;
  typedef std::map<Numero, Tarjeta*> Tarjetas;
  typedef std::unordered_set<Cadena> Usuarios;
  //Constructor
  class Id_duplicado
  {
  public:
    Id_duplicado(Cadena A):ID(A){}
    Cadena idd() const{return ID;}
  private:
    Cadena ID;

  };
  Usuario(const Cadena& ID,const Cadena& NOM,const Cadena& APE,const Cadena& DIR,const Clave& CON);
  //Constructor Copia (PROHIBIDO)
  Usuario(const Usuario&)=delete;
  //Constructor de asignacion (PROHIBIDO)
  Usuario& operator=(const Usuario&)=delete;
  //Relacion Usuario-Tarjeta
  void es_titular_de(Tarjeta& tarjeta);
  void no_es_titular_de(Tarjeta& tarjeta);

  //Relacion Usuario-Articulo
  void compra(Articulo& articulo,unsigned int cantidad=1);
  //Métodos observadores
  Cadena id() const{return id_;};
  Cadena nombre() const{return nomb_;};
  Cadena apellidos() const{return apell_;};
  Cadena direccion() const{return dir_;};
  const Tarjetas& tarjetas() const { return tarjetas_;}
  const Articulos& compra() const {return articulos_; }
  size_t n_articulos() const { return articulos_.size();}
  friend std::ostream& operator<<(std::ostream& os,const Usuario& U);
    //Destructor
  ~Usuario();
private:
  Cadena id_,nomb_,apell_,dir_;
  Clave pass_;
  Tarjetas tarjetas_;  //Enlaces
  Articulos articulos_;
  static Usuarios usuario_;
};

std::ostream& mostrar_carro(std::ostream& os,const Usuario& usr);
#endif
