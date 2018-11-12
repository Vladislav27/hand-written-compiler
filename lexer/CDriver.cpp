#include <cctype>
#include <fstream>
#include <cassert>

#include "CDriver.h"

Comp::CDriver::~CDriver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void Comp::CDriver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
   return;
}

void Comp::CDriver::parse( std::istream &stream )
{
   if( ! stream.good()  && stream.eof() )
   {
       return;
   }
   //else
   parse_helper( stream ); 
   return;
}


void Comp::CDriver::parse_helper( std::istream &stream )
{
   delete(scanner);
   try
   {
      scanner = new Comp::CScanner( &stream );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   delete(parser); 
   try
   {
      parser = new Comp::CParser( (*scanner) /* scanner */,
                                  (*this) /* driver */,
                                  program);
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" << 
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   const int accept( 0 );
   if( parser->parse() != accept )
   {
      std::cerr << "Parse failed!!\n";
      throw std::exception();
   }
   return;
}

std::ostream& Comp::CDriver::print( std::ostream &stream )
{
   auto vizualizer = new NTree::GraphVizPrinterVisitor(stream);
   vizualizer->Visit(&program);
   return(stream);
}

void Comp::CDriver::token()
{
//   std::cout << "Token" << std::endl;
}