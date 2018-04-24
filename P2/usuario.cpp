#include <ctime>
#include <unistd.h>
#include <ostream>
#include "usuario.hpp"


class SNA{
  public:  //Semilla de SRAND
  SNA(){  std::srand(std::time(nullptr)); }
}sna;

Usuario::Usuario(Cadena id_,Cadena nombre_,Cadena apell_,Cadena dir_,Clave contr_)
{
  auto it=Usuarios.insert(id_);
  if(!it.second) throw Id_duplicado("Id ya introducido");
  id(id_);nombre(nombre_);apell(apell_);dir(dir_);contr(contr_);
}

void Usuario::es_titular_de(Tarjeta& tarjeta)
{
  tarjetas.insert(make_pair(tarjeta.numero(),&tarjeta));
}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{
  tarjetas.erase(tarjeta.numero());
}


//CLAVE
Clave::Clave(const char* C)
{
if(std::strlen(C)<5) throw Incorrecta(CORTA);
char* RNDM=new char[2];
static const char *const cv="abcdefghijklmnopqrstuvwxyz
                    ABCDEFGHIJKLMNOPQRSTUVWXYZ
                    0123456789./";
static const std::size_t longtd = sizeof(cv) -1;
RNDM[0]=cv[rand()%(longtd)];
RNDM[1]=cv[rand()%(longtd)];
const char* const ptr=crypt(C,RNDM);
if(!ptr) throw Incorrecta(ERROR_CRYPT);
con_cif = C;
}

const char* Clave::clave() const
{
  return con_cif.c_str();
}

bool Clave::verifica(const char* V) const
{
  if(const char*const pcc=crypt(V,con_cif.c_str()))
  return con_cif==pcc;
  throw Incorrecta(ERROR_CRYPT);
}

Usuario::~Usuarios
{
  for(Tarjeta& t:tarjetas)
  {
    t.anula_titular();
  }
};
