/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */

// FIXME: Some code was deleted here.

#pragma once

#include <bind/binder.hh>
#include "bind/renamer.hh"
namespace bind
{

  Binder bind(ast::ChunkList& the_program);
  Renamer rename(ast::ChunkList& tree);
} // namespace bind
