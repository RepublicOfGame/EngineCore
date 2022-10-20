#pragma once
#define NFUNCTION(...) __attribute__((annotate("NFUNCTION(__VA_ARGS__)")))
#define NCLASS(...) __attribute__((annotate("NCLASS(__VA_ARGS__)")))
#define NPROPERTY(...) __attribute__((annotate("NPROPERTY(__VA_ARGS__)")))
#include <cstdint>

enum EFunctionFlags : uint32_t { FUNC_HasOutParms = 0x00000001 };
enum EFieldFlags : uint64_t {
  CPF_OutParm = 0x0000000000000001,
  CPF_Parm = 0x0000000000000001
};

class NFunction;

class NObject {
  void ProcessEvent(NFunction *Function, void *Parms);
};

class NField : public NObject {
public:
  NField *Next;
};

class FField {
public:
  FField *Next;
  EFieldFlags FieldFlags;
  int32_t OffsetInternal;

  explicit FField(int32_t Offset) : OffsetInternal(Offset) {}

  [[nodiscard]] bool HasAnyFieldFlag(EFieldFlags FlagToCheck) const {
    return (FieldFlags & FlagToCheck) == 1;
  }

  template <class T> T *ContainerPtrToValuePtr(void *ContainerPtr) const {
    return (static_cast<uint8_t *>(ContainerPtr) + OffsetInternal);
  }
};

class NStruct : public NField {};

class FOutParmRec {
public:
  FField *Field;
  uint8_t *FieldAddr;
};

class Stack {
public:
  FField *ChildProperties;
  FOutParmRec *OutParm;
  void *Buffer;

  explicit Stack(FField *field) : ChildProperties(field) {}
};

class NFunction : public NStruct {
public:
  EFunctionFlags FunctionFlags;
  FField *ChildProperties;

  using FNativeFuncPtr = void (*)(NObject *Object, Stack *stack);
  FNativeFuncPtr Func;

  [[nodiscard]] bool HasAnyFunctionFlags(EFunctionFlags FlagsToCheck) const {
    return (FunctionFlags & FlagsToCheck) != 0;
  }

  void Invoke(NObject *Obj, Stack *Stack) const {
    // TODO: OBJ 运行时类型检查
    Func(Obj, Stack);
  }
};
