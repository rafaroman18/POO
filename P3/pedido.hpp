#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include "tarjeta.hpp"
#include "../P1/fecha.cpp"
#include <map>
#include <set>
class Usuario_Pedido;
class Pedido_Articulo;
class Pedido
{
public:
  Pedido(Usuario_Pedido& usuario_pedidos,Pedido_Articulo& pedido_articulo,Usuario& u, const Tarjeta& t,const Fecha& fp);
  int numero() const{return num_;}
  Tarjeta const* tarjeta() const {return tarjeta_;}
  Fecha fecha() const {return fecha_;}
  double total() const {return total_;}
  int n_total_pedidos() const {return N_pedidos;}
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

std::ostream& operator<<(std::ostream& os,Pedido P)
{
  os<<std::left<<std::setw(14)<<"Núm. pedido: "<<std::fixed<<P.numero()<<std::endl
    <<std::left<<std::setw(14)<<"Fecha: "<<P.fecha()
    <<std::left<<std::setw(14)<<"Pagado con: "<<P.tarjeta()
    <<std::left<<std::setw(14)<<"Importe: "<<P.total();
  return os;
}




#endif
