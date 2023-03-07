https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#ifndef EXTRACTOR_H
#define EXTRACTOR_H

#include "z3++.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include <set>

#include "Utils.h"

using namespace llvm;

using InstMapTy = std::map<Value *, unsigned int>;
using DefMapTy = std::map<Value *, std::set<Value *>>;


class Extractor {
public:
  Extractor() {
    Solver = new z3::fixedpoint(C);
    Params = new z3::params(C);
    Params->set("engine", "datalog");
    Solver->set(*Params);
  }

  ~Extractor() {
    delete Solver;
    delete Params;
  }

  enum AnalysisMode { ReachDef, Liveness };

  void initialize(AnalysisMode);
  z3::fixedpoint *getSolver() { return Solver; }
  z3::context &getContext() { return C; }

  void addNext(const InstMapTy &InstMap, Instruction *X, Instruction *Y);
  void addKill(const InstMapTy &InstMap, Instruction *X, Value *Y);
  void addGen(const InstMapTy &InstMap, Instruction *X, Value *Y);

  void extractConstraints(const InstMapTy &InstMap, Instruction *I, AnalysisMode Mode);

  void printTuple(std::string Name, Value *V1, Value *V2) {
    std::cout << Name << "(\"" << toString(V1) << "\", \"" << toString(V2)
              << "\")" << std::endl;
  }

  // Print everything in an InstMap, verbose prints all relations, !verbose prints only In and Out.
  void print(InstMapTy &InstMap, bool verbose, std::vector<Value *> &OrderSeen) {
    for (Value *OuterI : OrderSeen) {
      unsigned OuterZ3Id = InstMap[OuterI];
      std::cout << "Instruction: " << toString(OuterI) << std::endl;
      std::cout << "In set: " << std::endl;
      std::cout << "[";
      for (Value *InnerI : OrderSeen) {
        unsigned InnerZ3Id = InstMap[InnerI];
        z3::expr Q = In(C.bv_val(OuterZ3Id, 32), C.bv_val(InnerZ3Id, 32));
        if (Solver->query(Q) == z3::sat) {
          std::cout << toString(InnerI) << "; ";
        }
      }
      std::cout << "]" << std::endl;
      std::cout << "Out set: " << std::endl;
      std::cout << "[";
      for (Value *InnerI : OrderSeen) {
        unsigned InnerZ3Id = InstMap[InnerI];
        z3::expr Q = Out(C.bv_val(OuterZ3Id, 32), C.bv_val(InnerZ3Id, 32));
        if (Solver->query(Q) == z3::sat) {
          std::cout << toString(InnerI) << "; ";
        }
      }
      std::cout << "]" << std::endl;
      std::cout << std::endl;
      if (!verbose) {
        continue;
      }
      std::cout << "Kill set: " << std::endl;
      std::cout << "[";
      for (Value *InnerI : OrderSeen) {
        unsigned InnerZ3Id = InstMap[InnerI];
        z3::expr Q = Kill(C.bv_val(OuterZ3Id, 32), C.bv_val(InnerZ3Id, 32));
        if (Solver->query(Q) == z3::sat) {
          std::cout << toString(InnerI) << "; ";
        }
      }
      std::cout << "]" << std::endl;
      std::cout << std::endl;
      std::cout << "Gen set: " << std::endl;
      std::cout << "[";
      for (Value *InnerI : OrderSeen) {
        unsigned InnerZ3Id = InstMap[InnerI];
        z3::expr Q = Gen(C.bv_val(OuterZ3Id, 32), C.bv_val(InnerZ3Id, 32));
        if (Solver->query(Q) == z3::sat) {
          std::cout << toString(InnerI) << "; ";
        }
      }
      std::cout << "]" << std::endl;
      std::cout << std::endl;
      std::cout << "Next set: " << std::endl;
      std::cout << "[";
      for (Value *InnerI : OrderSeen) {
        unsigned InnerZ3Id = InstMap[InnerI];
        z3::expr Q = Next(C.bv_val(OuterZ3Id, 32), C.bv_val(InnerZ3Id, 32));
        if (Solver->query(Q) == z3::sat) {
          std::cout << toString(InnerI) << "; ";
        }
      }
      std::cout << "]" << std::endl;
      std::cout << std::endl;
    }
  }

private:
  std::map<Value *, std::set<Value *>> DefMap;

  z3::context C;
  z3::fixedpoint *Solver;
  z3::params *Params;
  z3::check_result Result;
  z3::sort LLVMInst = C.bv_sort(32); // LLVMInst is an alias for our 32-bit instruction IDs

public:
  /* Relations for Reaching Definition */
  // This defines a Relation named Kill, with a domain (LLVMInst, LLVMInst) and range (boolean)
  z3::func_decl Kill = C.function("Kill", LLVMInst, LLVMInst, C.bool_sort());
  z3::func_decl Gen = C.function("Gen", LLVMInst, LLVMInst, C.bool_sort());
  z3::func_decl Next = C.function("Next", LLVMInst, LLVMInst, C.bool_sort());
  z3::func_decl In = C.function("In", LLVMInst, LLVMInst, C.bool_sort());
  z3::func_decl Out = C.function("Out", LLVMInst, LLVMInst, C.bool_sort());

};

#endif // EXTRACTOR_H
