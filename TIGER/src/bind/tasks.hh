/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

#pragma once

#include <task/libtask.hh>

// FIXME: Some code was deleted here.
namespace bind::tasks
{
  TASK_GROUP("4. Binding");
  TASK_DECLARE("b|bindings-compute",
               "compute bindingsg of an ast",
               bindings_compute,
               "parse");

  TASK_DECLARE("B|bindings-display",
               "display bindings",
               bindings_display,
               "bindings-compute");

  DISJUNCTIVE_TASK_DECLARE(
    "bound",
    "ensuring that one of the binding tasks has been executed",
    "bindings-compute");

  TASK_DECLARE(
    "rename",
    "Rename identifiers uses and their definitions with a unique name",
    rename,
    "bindings-compute");
} // namespace bind::tasks
