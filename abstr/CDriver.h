#pragma once

#include <string>
#include <cstddef>
#include <istream>

#include "CScanner.h"
#include "parser.tab.hh"
#include "abstr/tree/visitors/GraphVizPrinterVisitor.h"

namespace Comp{

class CDriver{
public:
   CDriver() = default;

   virtual ~CDriver() = default;
   
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

   void parse_helper( std::istream &stream );

   std::unique_ptr<Comp::CParser> parser;
   std::unique_ptr<Comp::CScanner> scanner;
   NTree::Program program;
};

} /* end namespace Comp*/

