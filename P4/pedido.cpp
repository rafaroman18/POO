#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
//atributo estatico
int Pedido::N_pedidos=0;  //Contador de pedidos

Pedido::Pedido(Usuario_Pedido& usuario_pedidos,
              Pedido_Articulo& pedido_articulo,
              Usuario& u, const Tarjeta& t,const Fecha& fp)
        : num_(N_pedidos+1),tarjeta_(&t), fecha_(fp),total_(0)
{
  if(u.n_articulos()==0) throw Vacio(u); //¿Carrito vacío?
  if(t.titular() != &u) throw Impostor(u);
  if(t.caducidad()<fp) throw Tarjeta::Caducada(t.caducidad()); //Tarjeta caducada
  Usuario::Articulos carro = u.compra(); //Se copia para poder realizar el bucle, ya que el erase anula los iteradores. Este solo se utiliza para leer
  bool pedido_final_vacio=true;
    for(auto c : carro)
    {
      Articulo* pa= c.first;
      unsigned int cantidad = c.second;
      if(ArticuloAlmacenable* const aa=dynamic_cast<ArticuloAlmacenable* const>(pa))
      {
        if(aa->stock()<cantidad)
          {
          const_cast<Usuario::Articulos&>(u.compra()).clear();//Como compra devuelve un metodo const, hace falta un conversor a no const
          throw SinStock(*c.first);
          }//No hay bastante en el armarsén
      double precio=pa->precio();
      aa->stock() -= cantidad;
      total_ += precio * cantidad;
      pedido_articulo.pedir(*this, *aa, precio, cantidad);
      pedido_final_vacio=false;
      }
      else
        if(LibroDigital* const ld=dynamic_cast<LibroDigital* const>(pa)){
            if(ld->f_expir() > fp) {
              total_ += ld->precio() * cantidad;
              pedido_articulo.pedir(*this,*ld,ld->precio(),cantidad);
              pedido_final_vacio=false;
            }
      }
      else throw std::logic_error("Pedido::Pedido error, tipo de Articulo desconocido");
      u.compra(*(c.first),0);
    }
    if(pedido_final_vacio){throw Vacio(u);}
    usuario_pedidos.asocia(u,*this);
    ++N_pedidos;
}

std::ostream& operator<<(std::ostream& os,const Pedido& P)
{
  os<<std::left<<std::setw(14)<<"Núm. pedido:  "<<P.numero()<<std::endl
    <<std::left<<std::setw(14)<<"Fecha: "<<P.fecha()<<std::endl
    <<std::left<<std::setw(14)<<"Pagado con: "<<P.tarjeta()->tipo()<<" n.º: "<<P.tarjeta()->numero()<<std::endl
    <<std::left<<std::setw(14)<<"Importe: "<<std::fixed<<std::setprecision(2)<<P.total()<<" €"<<std::endl;
  return os;
}
