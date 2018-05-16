#include "pedido-articulo.hpp"
void Pedido_Articulo::pedir(Pedido& P,Articulo& A,double precio,unsigned cantidad)
{
pedido_articulos_[&P].insert(std::make_pair(&A,LineaPedido(precio,cantidad)));
articulo_pedidos_[&A].insert(std::make_pair(&P,LineaPedido(precio,cantidad)));
}

void Pedido_Articulo::pedir(Articulo& A,Pedido& P,double precio,unsigned cantidad)
{
  pedir(P,A,precio,cantidad);
}

bool OrdenaArticulos::operator() (const Articulo*A,const Articulo*B) const
{
  return A->referencia()<B->referencia();
}

bool OrdenaPedidos::operator() (const Pedido* A,const Pedido* B) const
{
  return A->numero()<B->numero();
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalles(Pedido& U)
{
return pedido_articulos_[&U]; //REVISAR
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& A)
{
  return articulo_pedidos_[&A];
}

std::ostream& operator<<(std::ostream& os,Pedido_Articulo::ItemsPedido& Items)
{
  double total=0.0;
  os<<"  PVP       Cantidad        Artículo"<<std::endl
    <<"================================================="<<std::endl;
for(auto w : Items)
{
os<<w.second<<"           "<<"["<<w.first->referencia()<<"] "<<"\""<<w.first->titulo()<<"\""<<std::endl;
total=total+w.second.cantidad()*w.second.precio_venta();
}
  os<<"================================================="<<std::endl;
  os<<"    Total"<<"  "<<std::setprecision(2)<<total<<" €"<<std::endl;
  return os;
}


std::ostream& operator<<(std::ostream& os,Pedido_Articulo::Pedidos& P)
{
  double total=0.0;
  unsigned contador=0;
  os<<"[Pedidos: "<<P.size()<<"]"<<std::endl;
  os<<"================================================="<<std::endl
    <<"  PVP       Cantidad         Fecha de Venta"<<std::endl
    <<"================================================="<<std::endl;

  for(auto w : P)
    {
  os<<w.second<<"           "<<w.first->fecha()<<std::endl;
  total=total+w.second.cantidad()*w.second.precio_venta();
  contador=contador+w.second.cantidad();
    };
  os<<"================================================="<<std::endl
  <<total<<"      "<<contador;
  return os;
}

void Pedido_Articulo::mostrarDetallesPedidos()
{
  for(auto c : pedido_articulos_)
  {
    std::cout<<""
  }
}
