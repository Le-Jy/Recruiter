/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

// FIXME: Some code was deleted here.
#include <bind/binder.hh>
#include <bind/libbind.hh>
#include <bind/renamer.hh>
#include "ast/chunk-list.hh"

namespace bind
{

  Binder bind(ast::ChunkList& the_program)
  {
    Binder binder;
    binder(the_program);
    return binder;
  }

  Renamer rename(ast::ChunkList& tree)
  {
    Renamer renamer;
    renamer(tree);
    return renamer;
  }
} // namespace bind
