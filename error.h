#include <string>
struct error {              // exception
  std::string msg;
  error( std::string msg ) : msg( msg ) {}
};