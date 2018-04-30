extern "C"{
  #include <unistd.h>
}
#include <iostream>
#include <iomanip>
#include <cstring>
#include <random>
#include "usuario.hpp"

//CLAVE
Clave::Clave(const char* contrasenna)
{
if(std::strlen(contrasenna)<5) throw Incorrecta(CORTA);
static const char *const cv="abcdefghijklmnopqrstuvwxyABCDEFGHIJKLMNOPQRSTUVWXY0123456789./";
std::random_device rng;
std::uniform_int_distribution<std::size_t> dist(0,63);
const char salt[]={cv[dist(rng)],cv[dist(rng)]};
const char* const ptr=crypt(contrasenna,salt);
if(!ptr) throw Incorrecta(ERROR_CRYPT);
password = ptr;
}

inline const Cadena& Clave::clave() const
{
  return password;
}

bool Clave::verifica(const char* ppassword) const
{
  const char*const pcc=crypt(ppassword,password.c_str());
  if(!pcc) throw Incorrecta(ERROR_CRYPT);
  return password==pcc;
}

Usuario::Usuarios Usuario::usuario_;
//USUARIO
Usuario::Usuario(const Cadena& ID,const Cadena& NOM,const Cadena& APE,const Cadena& DIR,const Clave& CON)
:id_(ID),nomb_(NOM),apell_(APE),dir_(DIR),pass_(CON)
{
  if(!usuario_.insert(ID).second) throw Id_duplicado(id_);
}

void Usuario::compra(Articulo& arti,unsigned int cantidad)
{
if(cantidad==0) articulos_.erase(&arti);
else articulos_[&arti] = cantidad;
}

void Usuario::es_titular_de(Tarjeta& tarjeta)
{ if(tarjeta.titular()==this) tarjetas_.insert(std::make_pair(tarjeta.numero(),&tarjeta));}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{ tarjeta.anula_titular(); tarjetas_.erase(tarjeta.numero());  }

std::ostream& operator<<(std::ostream& os,const Usuario& U)
{
  os<<U.id_<<" "<<"["<<U.pass_.clave()<<"]"<<" "<<U.nomb_<<" "<<U.apell_
  <<std::endl<<U.dir_
  <<std::endl<<"Tarjetas:"<<std::endl;
  for(Usuario::Tarjetas::const_iterator i=U.tarjetas_.begin();i!=U.tarjetas_.end();i++)
  {
    os<<(*i->second)<<std::endl;
  };
  return os;
}

std::ostream& mostrar_carro(std::ostream& os,const Usuario& usr)
{
os<<"Carrito de la compra de "<<usr.id()<<" "<<"["<<"Artículos: "<<usr.n_articulos()<<"]"<<std::endl;
os<<" "<<"Cant."<<" "<<"Artículo"<<std::endl;
os<<"============================================================"<<std::endl;
for(Usuario::Articulos::const_iterator i=usr.compra().begin();i!=usr.compra().end();i++)
{
os<<"  "<<(i->second)<<"  "<<(*i->first)<<std::endl;
}
return os;
}

Usuario::~Usuario()
{
  for(Usuario::Tarjetas::const_iterator i=tarjetas_.begin();
  i!=tarjetas_.end();i++)
  {
    (i->second)->anula_titular();
  };
  usuario_.erase(id_);
};
