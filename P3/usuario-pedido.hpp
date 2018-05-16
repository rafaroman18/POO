#include <set>
#include <map>
#include "pedido.hpp"
class Usuario_Pedido
{
public:
typedef std::set<Pedido*> Pedidos;
void asocia(Pedido P,Usuario U);
void asocia(Usuario U,Pedido P);
Pedidos& pedidos(Usuario& U);
Usuario& cliente(Pedido& P);
private:
  std::map<Usuario*,Pedidos> Usuario_Pedidos_;//Diccionario punteros a Usuario y Pedido
  std::map<Pedido*,Usuario*> Pedido_Usuario_;//Diccionario punteros a Pedido y Usuario
};
