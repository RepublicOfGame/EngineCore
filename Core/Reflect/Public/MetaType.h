#pragma once

struct FField {
  const char* Name;
  const size_t Offset;
  FField* Next;
};

struct NClass {
  FField* Field;
};

struct Function : NClass{

};