https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Extractor.h"

#include "llvm/IR/Instruction.h"

void Extractor::initialize(AnalysisMode Mode) {
  Solver->register_relation(Kill);
  Solver->register_relation(Gen);
  Solver->register_relation(Next);
  Solver->register_relation(In);
  Solver->register_relation(Out);

  /* Variables for Rules 
   * You may reuse X, Y, Z in all your rules expressions further down
   * You can also define more variables like these if you need
   * These variables are bitvectors of length 32, matching our instruction IDs created in Constraint.cpp's main()
   */
  z3::expr X = C.bv_const("X", 32);
  z3::expr Y = C.bv_const("Y", 32);
  z3::expr Z = C.bv_const("Z", 32);

  if (Mode == ReachDef) {
    // TODO: Create z3::expr rules with z3::forall and z3::implies
    // TODO: Call Solver->add_rule for all your z3::expr rules
  }
  else if (Mode == Liveness) {
    // TODO: Create z3::expr rules with z3::forall and z3::implies
    // TODO: Call Solver->add_rule for all your z3::expr rules
  }
}

void Extractor::addGen(const InstMapTy &InstMap, Instruction *X, Value *Y) {
  unsigned int Arr[2] = {InstMap.at(X), InstMap.at(Y)};
  Solver->add_fact(Gen, Arr);
}
void Extractor::addKill(const InstMapTy &InstMap, Instruction *X, Value *Y) {
  unsigned int Arr[2] = {InstMap.at(X), InstMap.at(Y)};
  Solver->add_fact(Kill, Arr);
}
void Extractor::addNext(const InstMapTy &InstMap, Instruction *X, Instruction *Y) {
  unsigned int Arr[2] = {InstMap.at(X), InstMap.at(Y)};
  Solver->add_fact(Next, Arr);
}

void Extractor::extractConstraints(const InstMapTy &InstMap, Instruction *I, AnalysisMode Mode) {
  if (Mode == ReachDef) {
    // TODO: Call addGen, addKill, addNext as needed 
  }
  else if (Mode == Liveness) {
    // TODO: Call addGen, addKill, addNext as needed 
  }
}
