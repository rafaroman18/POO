#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP
#include "pedido.hpp"
class LineaPedido
{
public:
  explicit LineaPedido(double precio,unsigned cantidad=1):precio_(precio),cantidad_(cantidad){}
  double precio_venta() const {return precio_;}
  unsigned cantidad() const {return cantidad_;}
private:
  double precio_;
  unsigned cantidad_;
};

std::ostream& operator<<(std::ostream& os,const LineaPedido& L);

 class OrdenaArticulos:public std::binary_function<Articulo*,Articulo*,bool>
 {
 public:
 bool operator() (const Articulo*A,const Articulo*B)const;
 };
 class OrdenaPedidos:public std::binary_function<Pedido*,Pedido*,bool>
 {
 public:
   bool operator() (const Pedido* A,const Pedido* B) const;
 };
class Pedido_Articulo
{
public:
  typedef std::map<Articulo*,LineaPedido,OrdenaArticulos> ItemsPedido;
  typedef std::map<Pedido*,LineaPedido,OrdenaPedidos> Pedidos;
  void pedir(Pedido& P,Articulo& A,double precio,unsigned cantidad=1);
  void pedir(Articulo& A,Pedido& P,double precio,unsigned cantidad=1);
  const ItemsPedido& detalle(Pedido& U);
  Pedidos ventas(Articulo& A);
  std::ostream& mostrarDetallePedidos(std::ostream& os);
  std::ostream& mostrarVentasArticulos(std::ostream& os);
private:
  std::map<Pedido*,ItemsPedido,OrdenaPedidos> pedido_articulos_;
  std::map<Articulo*,Pedidos,OrdenaArticulos> articulo_pedidos_;

};
std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::ItemsPedido& Items);
std::ostream& operator<<(std::ostream& os,const Pedido_Articulo::Pedidos& P);

#endif
