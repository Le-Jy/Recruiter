/**
 ** \file bind/tasks.cc
 ** \brief Bind module tasks implementation.
 */

// FIXME: Some code was deleted here.
//

#include <ast/libast.hh>
#include <ast/tasks.hh>
#include <bind/binder.hh>
#include <bind/libbind.hh>
#include <object/tasks.hh>

#include <common.hh>
#include "misc/contract.hh"
//#include "ast/chunk-list.hh"
#define DEFINE_TASKS 4
#include <bind/tasks.hh>
#undef DEFINE_TASKS

namespace bind::tasks
{
  bool bindings_compute_done = false;
  bool object_bindings_compute_done = false;
  bool combine_types_compute_done = false;

  void bindings_compute()
  {
    precondition(ast::tasks::the_program);

    bind::Binder result = ::bind::bind(*ast::tasks::the_program);

    if (result.error_get())
      {
        task_error() << result.error_get();
        task_error().exit();
      }
    bindings_compute_done = true;
  }

  void bindings_display()
  {
    precondition(ast::tasks::the_program);
    ast::bindings_display(std::cout) = true;
  }

  void rename() { bind::rename(*ast::tasks::the_program); }
} // namespace bind::tasks
