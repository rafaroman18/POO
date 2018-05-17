#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <map>
#include <set>
#include "tarjeta.hpp"
#include "fecha.hpp"
class Usuario_Pedido;
class Pedido_Articulo;
class Pedido
{
public:
  Pedido(Usuario_Pedido& usuario_pedidos,Pedido_Articulo& pedido_articulo,Usuario& u, const Tarjeta& t,const Fecha& fp=Fecha());
  int numero() const{return num_;}
  Tarjeta const* tarjeta() const {return tarjeta_;}
  Fecha fecha() const {return fecha_;}
  double total() const {return total_;}
  static int n_total_pedidos() {return N_pedidos;}
  //EXCEPCIONES
  class ExcepGener
  {
  public:
    ExcepGener(Usuario& V_):V(&V_){}
    const Usuario& usuario() const{return *V;}
  private:
    Usuario* V;
  };
  class Vacio:public ExcepGener //Hereda de una clase Base ExcepGene
  {
  public:
    Vacio(Usuario& V_):ExcepGener(V_){}
  };
  class Impostor:public ExcepGener //Hereda de una clase Base ExcepGene
  {
  public:
    Impostor(Usuario& I_):ExcepGener(I_){}
  };
  class SinStock
  {
  public:
    SinStock(Articulo& A_):A(&A_){}
    const Articulo& articulo() const{return *A;}
  private:
    Articulo* A;
  };
private:
static int N_pedidos;
  int num_;
  const Tarjeta* tarjeta_;
  Fecha fecha_;
  double total_;
};

std::ostream& operator<<(std::ostream& os,const Pedido& P);





#endif
