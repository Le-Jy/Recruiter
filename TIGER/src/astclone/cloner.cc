/**
 ** \file astclone/cloner.cc
 ** \brief Implementation of astclone::Cloner.
 */

#include <ast/all.hh>
#include <astclone/cloner.hh>
#include <misc/symbol.hh>

namespace astclone
{
  using namespace ast;

  Cloner::Cloner()
    : result_(nullptr)
  {}

  Ast* Cloner::result_get() { return result_; }

  void Cloner::operator()(const ast::ArrayExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    NameTy* type_name = recurse(e.type_name_get());
    Exp* size = recurse(e.size_get());
    Exp* init = recurse(e.init_get());
    result_ = new ArrayExp(location, type_name, size, init);
  }

  void Cloner::operator()(const ast::ArrayTy& e)
  {
    const Location& location = e.location_get();
    NameTy* base_type = recurse(e.base_type_get());
    result_ = new ArrayTy(location, base_type);
  }

  void Cloner::operator()(const ast::AssignExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    Var* var = recurse(e.var_get());
    Exp* exp = recurse(e.exp_get());

    result_ = new AssignExp(location, var, exp);
  }

  void Cloner::operator()(const ast::BreakExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    //Exp* def = recurse(e.def_get());
    result_ = new BreakExp(location);
    //result_->def_get(def);
  }

  void Cloner::operator()(const ast::CallExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    exps_type* args = recurse_collection(e.args_get());
    result_ = new CallExp(location, name, args);
  }

  void Cloner::operator()(const ast::CastExp& e)
  {
    const Location& location = e.location_get();
    Exp* exp = recurse(e.exp_get());
    Ty* ty = recurse(e.ty_get());
    result_ = new CastExp(location, exp, ty);
  }

  void Cloner::operator()(const ast::ChunkList& e)
  {
    const Location& location = e.location_get();
    ChunkList::list_type chunks = *recurse_collection(e.chunks_get());
    result_ = new ChunkList(location, chunks);
  }

  void Cloner::operator()(const ast::ClassTy& e)
  {
    const Location& location = e.location_get();
    NameTy* super = recurse(e.super_get());
    ChunkList* chunks = recurse(e.chunks_get());
    result_ = new ClassTy(location, super, chunks);
  }

  void Cloner::operator()(const ast::Field& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    NameTy* type_name = recurse(e.type_name_get());
    result_ = new Field(location, name, type_name);
  }

  void Cloner::operator()(const ast::FieldInit& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    Exp* init = recurse(e.init_get());
    result_ = new FieldInit(location, name, init);
  }

  void Cloner::operator()(const ast::FieldVar& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    Var* var = recurse(e.var_get());
    misc::symbol name = e.name_get();
    //int index = e.index_get();
    result_ = new FieldVar(location, var, name);
    //result_->index_set(index);
  }

  void Cloner::operator()(const ast::ForExp& e)
  {
    const Location& location = e.location_get();
    VarDec* vardec = recurse(e.vardec_get());
    Exp* hi = recurse(e.hi_get());
    Exp* body = recurse(e.body_get());
    result_ = new ForExp(location, vardec, hi, body);
  }

  void Cloner::operator()(const ast::FunctionDec& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    VarChunk* formals = recurse(e.formals_get());
    NameTy* result = recurse(e.result_get());
    Exp* body = recurse(e.body_get());
    auto fundec = new FunctionDec(location, name, formals, result, body);
    result_ = fundec;
  }

  void Cloner::operator()(const ast::IfExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    Exp* test = recurse(e.test_get());
    Exp* thenclause = recurse(e.thenclause_get());
    Exp* elseclause = recurse(e.elseclause_get());

    result_ = new IfExp(location, test, thenclause, elseclause);
  }

  void Cloner::operator()(const ast::IntExp& e)
  {
    const Location& location = e.location_get();
    int value = e.value_get();
    result_ = new IntExp(location, value);
  }

  void Cloner::operator()(const ast::LetExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    ChunkList* chunks = recurse(e.chunks_get());
    Exp* body = recurse(e.body_get());

    result_ = new LetExp(location, chunks, body);
  }

  void Cloner::operator()(const ast::MethodCallExp& e)
  {
    // COMPLETED

    const Location& location = e.location_get();
    Var* object = recurse(e.object_get());
    misc::symbol name = e.name_get();
    exps_type* args = recurse_collection(e.args_get());
    result_ = new MethodCallExp(location, name, args, object);
    //MethodDec* def_set
  }

  void Cloner::operator()(const ast::MethodDec& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    VarChunk* formals = recurse(e.formals_get());
    NameTy* result = recurse(e.result_get());
    Exp* body = recurse(e.body_get());
    result_ = new MethodDec(location, name, formals, result, body);
  }

  void Cloner::operator()(const ast::NameTy& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    result_ = new NameTy(location, name);
  }

  void Cloner::operator()(const ast::NilExp& e)
  {
    const Location& location = e.location_get();
    result_ = new NilExp(location);
  }

  void Cloner::operator()(const ast::ObjectExp& e)
  {
    // COMPLETED

    const Location& location = e.location_get();
    NameTy* type_name = recurse(e.type_name_get());
    result_ = new ObjectExp(location, type_name);
  }

  void Cloner::operator()(const ast::OpExp& e)
  {
    const Location& location = e.location_get();
    Exp* left = recurse(e.left_get());
    OpExp::Oper oper = e.oper_get();
    Exp* right = recurse(e.right_get());
    result_ = new OpExp(location, left, oper, right);
  }

  void Cloner::operator()(const ast::RecordExp& e)
  {
    // COMPLETED

    const Location& location = e.location_get();
    NameTy* type_name = recurse(e.type_name_get());
    fieldinits_type* fields = recurse_collection(e.fields_get());
    result_ = new RecordExp(location, type_name, fields);
  }

  void Cloner::operator()(const ast::RecordTy& e)
  {
    // COMPLETED

    const Location& location = e.location_get();
    fields_type* fields = recurse_collection(e.fields_get());
    result_ = new RecordTy(location, fields);
  }

  void Cloner::operator()(const ast::SeqExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    exps_type* exps = recurse_collection(e.exps_get());
    result_ = new SeqExp(location, exps);
  }

  void Cloner::operator()(const ast::SimpleVar& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    result_ = new SimpleVar(location, name);
  }

  void Cloner::operator()(const ast::StringExp& e)
  {
    // COMPLETED
    const Location& location = e.location_get();
    std::string value = e.value_get();
    result_ = new StringExp(location, value);
  }

  void Cloner::operator()(const ast::SubscriptVar& e)
  {
    const Location& location = e.location_get();
    Var* var = recurse(e.var_get());
    Exp* index = recurse(e.index_get());
    result_ = new SubscriptVar(location, var, index);
  }

  void Cloner::operator()(const ast::TypeDec& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    Ty* ty = recurse(e.ty_get());
    result_ = new TypeDec(location, name, ty);
  }

  void Cloner::operator()(const ast::VarDec& e)
  {
    const Location& location = e.location_get();
    misc::symbol name = e.name_get();
    NameTy* type_name = recurse(e.type_name_get());
    Exp* init = recurse(e.init_get());
    // COMPLETED: Some code was deleted here (Cloned node instantiation).
    result_ = new VarDec(location, name, type_name, init);
  }

  void Cloner::operator()(const ast::WhileExp& e)
  {
    const Location& location = e.location_get();
    Exp* test = recurse(e.test_get());
    Exp* body = recurse(e.body_get());
    result_ = new WhileExp(location, test, body);
  }

  void Cloner::operator()(const ast::FunctionChunk& e)
  {
    chunk_visit<ast::FunctionChunk>(e);
  }

  void Cloner::operator()(const ast::MethodChunk& e)
  {
    // COMPLETED
    chunk_visit<ast::MethodChunk>(e);
  }

  void Cloner::operator()(const ast::TypeChunk& e)
  {
    // COMPLETED
    chunk_visit<ast::TypeChunk>(e);
  }

  void Cloner::operator()(const ast::VarChunk& e)
  {
    // COMPLETED
    chunk_visit<ast::VarChunk>(e);
  }

} // namespace astclone
