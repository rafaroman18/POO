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
  static const char* const letras = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
	if(strlen(contrasenna)< 5) throw Incorrecta(Clave::CORTA);
	static std::random_device rd;
	static std::uniform_int_distribution<std::size_t> dis(0,63);

	const char salt[] {letras[dis(rd)],letras[dis(rd)]};
	if(const char* const encrypt = crypt(contrasenna,salt)) password = encrypt;
  else throw Incorrecta(Razon::ERROR_CRYPT);

}

inline const Cadena& Clave::clave() const
{
  return password;
}

bool Clave::verifica(const char* ppassword) const
{

  if(const char*const pcc=crypt(ppassword,password.c_str()))
  return password==pcc;
  throw Incorrecta(ERROR_CRYPT);
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
if(cantidad==0) articulos_.erase(&arti); //Esto invalida los iteradores, hay que tener ojo
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
