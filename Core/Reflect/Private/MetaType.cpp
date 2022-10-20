#include "MetaType.h"

void NObject::ProcessEvent(NFunction *Function, void *Parms) {
  auto *CallStack = new Stack(Function->ChildProperties);
  if (Function->HasAnyFunctionFlags(EFunctionFlags::FUNC_HasOutParms)) {

    // 如果函数有返回值
    for (FField *Field = Function->ChildProperties;
         Field && Field->HasAnyFieldFlag(CPF_Parm); Field = Field->Next) {

      if (Field->HasAnyFieldFlag(CPF_OutParm)) {
        CallStack->OutParm = new FOutParmRec();
        CallStack->OutParm->Field = Field;
        CallStack->OutParm->FieldAddr =
            Field->ContainerPtrToValuePtr<uint8_t>(Parms);
      }
    }
  }
}
