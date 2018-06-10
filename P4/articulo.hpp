#ifndef ARTICULO_HPP
#define ARTICULO_HPP
#include <iomanip>
#include <set>
#include "../P1/cadena.hpp"
#include "fecha.hpp"
class Autor;

class Articulo
{
public:
typedef std::set<Autor*> Autores;
Articulo(const Autores A,const Cadena& R,const Cadena& T,const Fecha F,double P):Au(A),refe(R),tit(T),f_pub(F),pre(P){};
const Cadena& referencia() const;
const Cadena& titulo() const;
const Fecha& f_publi() const;
double& precio();
double precio() const;
unsigned& stock();
unsigned stock() const;
const Autores& autores() const;
class Autores_vacios{};
virtual void impresion_especifica(std::ostream&)const noexcept=0;
virtual ~Articulo(){};
private:
Autores Au;
Cadena refe;
Cadena tit;
Fecha f_pub;
double pre;
};

class Autor
{
public:
  Autor(const Cadena& nombre,const Cadena& apellidos,const Cadena& direccion):
                nombre_(nombre),apellidos_(apellidos),direccion_(direccion){};

  class Autores_vacios {};
  const Cadena& nombre() const noexcept{return nombre_;}
  const Cadena& apellidos() const noexcept{return apellidos_;}
  const Cadena& direccion() const noexcept{return direccion_;}
private:
  Cadena nombre_,apellidos_,direccion_;
};

class LibroDigital: public Articulo
{
public:
  LibroDigital(Autores A,const Cadena& R,const Cadena& T,const Fecha F,double P,const Fecha& expiracion)
          :Articulo(A,R,T,F,P),f_expir_(expiracion){};
  const Fecha& f_expir()const{return f_expir_;}
  virtual void impresion_especifica(std::ostream& os)const noexcept
  {
    os<<"A la venta hasta el "<<f_expir_<<".";
  }
private:
  Fecha f_expir_;
};

class ArticuloAlmacenable: public Articulo
{
public:
  ArticuloAlmacenable(Autores A,const Cadena& R,const Cadena& T,
                      const Fecha F,double P,unsigned Stock=0):Articulo(A,R,T,F,P),stock_(Stock){}
unsigned stock() const { return stock_; }
unsigned& stock() { return stock_; }
protected:
unsigned stock_;
};

class Libro: public ArticuloAlmacenable
{
public:
  Libro(Autores A,const Cadena& R,const Cadena& T,
                      const Fecha F,double P,unsigned pag,unsigned Stock=0)
                      :ArticuloAlmacenable(A,R,T,F,P,Stock),n_pag_(pag){}
unsigned n_pag() const{return n_pag_;}
virtual void impresion_especifica(std::ostream& os)const noexcept
{
  os<<n_pag_<<" págs., "<<stock_<<" unidades.";
}
private:
unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable
{
public:
  Cederron(Autores A,const Cadena& R,const Cadena& T,
                      const Fecha F,double P,unsigned espacio,unsigned Stock=0)
                      :ArticuloAlmacenable(A,R,T,F,P,Stock),tam_(espacio){}
  unsigned tam()const{return tam_;}
  virtual void impresion_especifica(std::ostream& os)const noexcept
  {
    os<<tam_<<" MB, "<<stock_<<" unidades.";
  }
private:
unsigned tam_;
};

std::ostream& operator << (std::ostream& os,const Articulo& A);
#endif
