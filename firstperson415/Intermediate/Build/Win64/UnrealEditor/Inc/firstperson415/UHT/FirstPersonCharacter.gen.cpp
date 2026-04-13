// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "firstperson415/FirstPersonCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFirstPersonCharacter() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
FIRSTPERSON415_API UClass* Z_Construct_UClass_AFirstPersonCharacter();
FIRSTPERSON415_API UClass* Z_Construct_UClass_AFirstPersonCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_firstperson415();
// End Cross Module References

// Begin Class AFirstPersonCharacter Function GetFirstPersonCameraComponent
struct Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics
{
	struct FirstPersonCharacter_eventGetFirstPersonCameraComponent_Parms
	{
		UCameraComponent* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Components" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FirstPersonCharacter_eventGetFirstPersonCameraComponent_Parms, ReturnValue), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFirstPersonCharacter, nullptr, "GetFirstPersonCameraComponent", nullptr, nullptr, Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::PropPointers), sizeof(Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::FirstPersonCharacter_eventGetFirstPersonCameraComponent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::FirstPersonCharacter_eventGetFirstPersonCameraComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AFirstPersonCharacter::execGetFirstPersonCameraComponent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UCameraComponent**)Z_Param__Result=P_THIS->GetFirstPersonCameraComponent();
	P_NATIVE_END;
}
// End Class AFirstPersonCharacter Function GetFirstPersonCameraComponent

// Begin Class AFirstPersonCharacter Function GetHasRifle
struct Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics
{
	struct FirstPersonCharacter_eventGetHasRifle_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((FirstPersonCharacter_eventGetHasRifle_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FirstPersonCharacter_eventGetHasRifle_Parms), &Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFirstPersonCharacter, nullptr, "GetHasRifle", nullptr, nullptr, Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::PropPointers), sizeof(Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::FirstPersonCharacter_eventGetHasRifle_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::Function_MetaDataParams), Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::FirstPersonCharacter_eventGetHasRifle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AFirstPersonCharacter::execGetHasRifle)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetHasRifle();
	P_NATIVE_END;
}
// End Class AFirstPersonCharacter Function GetHasRifle

// Begin Class AFirstPersonCharacter Function GetMesh1P
struct Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics
{
	struct FirstPersonCharacter_eventGetMesh1P_Parms
	{
		USkeletalMeshComponent* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Components" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FirstPersonCharacter_eventGetMesh1P_Parms, ReturnValue), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFirstPersonCharacter, nullptr, "GetMesh1P", nullptr, nullptr, Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::PropPointers), sizeof(Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::FirstPersonCharacter_eventGetMesh1P_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::Function_MetaDataParams), Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::FirstPersonCharacter_eventGetMesh1P_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AFirstPersonCharacter::execGetMesh1P)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USkeletalMeshComponent**)Z_Param__Result=P_THIS->GetMesh1P();
	P_NATIVE_END;
}
// End Class AFirstPersonCharacter Function GetMesh1P

// Begin Class AFirstPersonCharacter Function SetHasRifle
struct Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics
{
	struct FirstPersonCharacter_eventSetHasRifle_Parms
	{
		bool bNewHasRifle;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
#endif // WITH_METADATA
	static void NewProp_bNewHasRifle_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bNewHasRifle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::NewProp_bNewHasRifle_SetBit(void* Obj)
{
	((FirstPersonCharacter_eventSetHasRifle_Parms*)Obj)->bNewHasRifle = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::NewProp_bNewHasRifle = { "bNewHasRifle", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FirstPersonCharacter_eventSetHasRifle_Parms), &Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::NewProp_bNewHasRifle_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::NewProp_bNewHasRifle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AFirstPersonCharacter, nullptr, "SetHasRifle", nullptr, nullptr, Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::PropPointers), sizeof(Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::FirstPersonCharacter_eventSetHasRifle_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::Function_MetaDataParams), Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::FirstPersonCharacter_eventSetHasRifle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(AFirstPersonCharacter::execSetHasRifle)
{
	P_GET_UBOOL(Z_Param_bNewHasRifle);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetHasRifle(Z_Param_bNewHasRifle);
	P_NATIVE_END;
}
// End Class AFirstPersonCharacter Function SetHasRifle

// Begin Class AFirstPersonCharacter
void AFirstPersonCharacter::StaticRegisterNativesAFirstPersonCharacter()
{
	UClass* Class = AFirstPersonCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetFirstPersonCameraComponent", &AFirstPersonCharacter::execGetFirstPersonCameraComponent },
		{ "GetHasRifle", &AFirstPersonCharacter::execGetHasRifle },
		{ "GetMesh1P", &AFirstPersonCharacter::execGetMesh1P },
		{ "SetHasRifle", &AFirstPersonCharacter::execSetHasRifle },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AFirstPersonCharacter);
UClass* Z_Construct_UClass_AFirstPersonCharacter_NoRegister()
{
	return AFirstPersonCharacter::StaticClass();
}
struct Z_Construct_UClass_AFirstPersonCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "FirstPersonCharacter.h" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_isTeleporting_MetaData[] = {
		{ "Category", "Teleport" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FirstPersonCameraComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh1P_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Mesh" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLogInputSetup_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Debug" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasRifle_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Weapon" },
		{ "ModuleRelativePath", "FirstPersonCharacter.h" },
	};
#endif // WITH_METADATA
	static void NewProp_isTeleporting_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isTeleporting;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FirstPersonCameraComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh1P;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static void NewProp_bLogInputSetup_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLogInputSetup;
	static void NewProp_bHasRifle_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasRifle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AFirstPersonCharacter_GetFirstPersonCameraComponent, "GetFirstPersonCameraComponent" }, // 514712348
		{ &Z_Construct_UFunction_AFirstPersonCharacter_GetHasRifle, "GetHasRifle" }, // 2760274109
		{ &Z_Construct_UFunction_AFirstPersonCharacter_GetMesh1P, "GetMesh1P" }, // 71780270
		{ &Z_Construct_UFunction_AFirstPersonCharacter_SetHasRifle, "SetHasRifle" }, // 3077222202
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AFirstPersonCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
void Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_isTeleporting_SetBit(void* Obj)
{
	((AFirstPersonCharacter*)Obj)->isTeleporting = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_isTeleporting = { "isTeleporting", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AFirstPersonCharacter), &Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_isTeleporting_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_isTeleporting_MetaData), NewProp_isTeleporting_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_FirstPersonCameraComponent = { "FirstPersonCameraComponent", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFirstPersonCharacter, FirstPersonCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FirstPersonCameraComponent_MetaData), NewProp_FirstPersonCameraComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_Mesh1P = { "Mesh1P", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFirstPersonCharacter, Mesh1P), Z_Construct_UClass_USkeletalMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh1P_MetaData), NewProp_Mesh1P_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFirstPersonCharacter, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFirstPersonCharacter, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFirstPersonCharacter, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0124080000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AFirstPersonCharacter, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
void Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bLogInputSetup_SetBit(void* Obj)
{
	((AFirstPersonCharacter*)Obj)->bLogInputSetup = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bLogInputSetup = { "bLogInputSetup", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AFirstPersonCharacter), &Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bLogInputSetup_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLogInputSetup_MetaData), NewProp_bLogInputSetup_MetaData) };
void Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bHasRifle_SetBit(void* Obj)
{
	((AFirstPersonCharacter*)Obj)->bHasRifle = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bHasRifle = { "bHasRifle", nullptr, (EPropertyFlags)0x0040000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AFirstPersonCharacter), &Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bHasRifle_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasRifle_MetaData), NewProp_bHasRifle_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AFirstPersonCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_isTeleporting,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_FirstPersonCameraComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_Mesh1P,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bLogInputSetup,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AFirstPersonCharacter_Statics::NewProp_bHasRifle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFirstPersonCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AFirstPersonCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_firstperson415,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AFirstPersonCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AFirstPersonCharacter_Statics::ClassParams = {
	&AFirstPersonCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_AFirstPersonCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_AFirstPersonCharacter_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AFirstPersonCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AFirstPersonCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AFirstPersonCharacter()
{
	if (!Z_Registration_Info_UClass_AFirstPersonCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AFirstPersonCharacter.OuterSingleton, Z_Construct_UClass_AFirstPersonCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AFirstPersonCharacter.OuterSingleton;
}
template<> FIRSTPERSON415_API UClass* StaticClass<AFirstPersonCharacter>()
{
	return AFirstPersonCharacter::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AFirstPersonCharacter);
AFirstPersonCharacter::~AFirstPersonCharacter() {}
// End Class AFirstPersonCharacter

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AFirstPersonCharacter, AFirstPersonCharacter::StaticClass, TEXT("AFirstPersonCharacter"), &Z_Registration_Info_UClass_AFirstPersonCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AFirstPersonCharacter), 2032719556U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_3326816527(TEXT("/Script/firstperson415"),
	Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_FirstPersonCharacter_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
