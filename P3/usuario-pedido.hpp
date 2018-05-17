#include <set>
#include <map>
#include "pedido.hpp"
class Usuario_Pedido
{
public:
typedef std::set<Pedido*> Pedidos;
void asocia(Pedido& P,Usuario& U)
{
  Usuario_Pedidos_[&U].insert(&P);
  Pedido_Usuario_[&P]=(&U);
}
void asocia(Usuario& U,Pedido& P)
{
  asocia(P,U);
}
Pedidos& pedidos(Usuario& U){return Usuario_Pedidos_[&U];};
Usuario* cliente(Pedido& P){return Pedido_Usuario_[&P];};
private:
  std::map<Usuario*,Pedidos> Usuario_Pedidos_;//Diccionario punteros a Usuario y Pedido
  std::map<Pedido*,Usuario*> Pedido_Usuario_;//Diccionario punteros a Pedido y Usuario
};
