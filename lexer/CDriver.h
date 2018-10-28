#pragma once

#include <string>
#include <cstddef>
#include <istream>

#include "CScanner.h"
#include "parser.tab.hh"

namespace Comp{

class CDriver{
public:
   CDriver() = default;

   virtual ~CDriver();
   
   /** 
    * parse - parse from a file
    * @param filename - valid string with input file
    */
   void parse( const char * const filename );
   /** 
    * parse - parse from a c++ input stream
    * @param is - std::istream&, valid input stream
    */
   void parse( std::istream &iss );
   void token();

   std::ostream& print(std::ostream &stream);
private:

   void parse_helper( std::istream &stream );

   Comp::CParser  *parser  = nullptr;
   Comp::CScanner *scanner = nullptr;
   NTree::Program program;
};

} /* end namespace Comp*/

