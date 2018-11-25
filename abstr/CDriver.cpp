#include <memory>

#include <cctype>
#include <fstream>
#include <cassert>

#include "CDriver.h"

void Comp::CDriver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
   in_file.close();
}

void Comp::CDriver::parse( std::istream &stream )
{
   if( ! stream.good()  && stream.eof() )
   {
       return;
   }
   //else
   parse_helper( stream );
}


void Comp::CDriver::parse_helper( std::istream &stream )
{
   try
   {
       std::shared_ptr<NTree::StringInterner> interner(new NTree::StringInterner());
       scanner = std::make_unique<Comp::CScanner>(&stream, interner);
       program.interner = interner;
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }

   try
   {
      parser = std::make_unique<Comp::CParser>( (*scanner) /* scanner */,
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
}

std::ostream& Comp::CDriver::print( std::ostream &stream )
{
   auto vizualizer = std::make_unique<NTree::GraphVizPrinterVisitor>(stream);
   vizualizer->Visit(&program);
   return(stream);
}

void Comp::CDriver::token()
{
//   std::cout << "Token" << std::endl;
}