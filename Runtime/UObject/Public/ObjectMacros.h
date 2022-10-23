#pragma once

#define BODY_MACRO_COMBINE_INNER(A, B, C, D) A##B##C##D
#define BODY_MACRO_COMBINE(A, B, C, D) BODY_MACRO_COMBINE_INNER(A, B, C, D)

#define GENERATED_BODY(...)                                                    \
  BODY_MACRO_COMBINE(CURRENT_FILE_ID, _, __LINE__, _GENERATED_BODY);

#define UFUNCTION(...) __attribute__((annotate("UFUNCTION __VA_ARGS__ ")))
#define UCLASS(...) __attribute__((annotate("UCLASS __VA_ARGS__ ")))
#define UPROPERTY(...) __attribute__((annotate("UPROPERTY __VA_ARGS__ ")))