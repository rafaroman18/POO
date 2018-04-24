#include "cadena.cpp"
#include <iostream>
int main()
{
  using namespace std;
  Cadena c="jaj";
  c[10]='a';
  Cadena a=" ";
  cout<<(c>a)<<endl;
  puts(c);
  return 0;
}
