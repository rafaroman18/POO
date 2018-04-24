#define _XOPEN_SOURCE
#include "clave.hpp"
#include <cstring>
#include <unistd.h>
#include <crypt.h>  //Incluido por si acaso
#include <cstdlib.h>
#include <time.h>

char* random_str()
{
  char* RNDM=new char[3];
  srand(time(NULL));      //OPCIONAL????
  static const char*="abcdefghijklmnopqrstuvwxyz
                      ABCDEFGHIJKLMNOPQRSTUVWXYZ
                      0123456789./";
  RNDM[0]=alphanum[rand()%(sizeof(alphanum)-1)];
  RNDM[1]=alphanum[rand()%(sizeof(alphanum)-1)];
  RNDM[2]='\0';       //CUIDADO CON ESTO, REVISAR
  return RNDM;
}

Clave::Clave(const char* C)
{
if(strlen(C)<5) throw Incorrecta(raz::CORTA);
char* ptr=crypt(C,random_str);
if(!ptr) throw Incorrecta(raz::ERROR_CRYPT);
con_cif(C);
}

const char* Clave::clave() const
{
  return con_cif.c_str();
}

bool Clave::verifica(const char* V) const
{
  char * cadaux=new char[2];
  cadaux[0]=con_cif[0];
  cadaux[1]=con_cif[1];
  char* ptr=crypt(V,cadaux);
  return strcmp(con_cif.c_str(),ptr);
}
