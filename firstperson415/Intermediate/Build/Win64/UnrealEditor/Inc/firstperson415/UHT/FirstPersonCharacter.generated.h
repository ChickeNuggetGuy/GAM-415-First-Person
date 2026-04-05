// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "FirstPersonCharacter.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UCameraComponent;
class USkeletalMeshComponent;
#ifdef FIRSTPERSON415_FirstPersonCharacter_generated_h
#error "FirstPersonCharacter.generated.h already included, missing '#pragma once' in FirstPersonCharacter.h"
#endif
#define FIRSTPERSON415_FirstPersonCharacter_generated_h

#define FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetFirstPersonCameraComponent); \
	DECLARE_FUNCTION(execGetMesh1P); \
	DECLARE_FUNCTION(execGetHasRifle); \
	DECLARE_FUNCTION(execSetHasRifle);


#define FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAFirstPersonCharacter(); \
	friend struct Z_Construct_UClass_AFirstPersonCharacter_Statics; \
public: \
	DECLARE_CLASS(AFirstPersonCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/firstperson415"), NO_API) \
	DECLARE_SERIALIZER(AFirstPersonCharacter)


#define FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_18_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AFirstPersonCharacter(AFirstPersonCharacter&&); \
	AFirstPersonCharacter(const AFirstPersonCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AFirstPersonCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AFirstPersonCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AFirstPersonCharacter) \
	NO_API virtual ~AFirstPersonCharacter();


#define FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_15_PROLOG
#define FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_18_INCLASS_NO_PURE_DECLS \
	FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FIRSTPERSON415_API UClass* StaticClass<class AFirstPersonCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
