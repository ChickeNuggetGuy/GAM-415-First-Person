// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "firstperson415/Portal.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePortal() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UArrowComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneCaptureComponent2D_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTextureRenderTarget2D_NoRegister();
FIRSTPERSON415_API UClass* Z_Construct_UClass_APortal();
FIRSTPERSON415_API UClass* Z_Construct_UClass_APortal_NoRegister();
UPackage* Z_Construct_UPackage__Script_firstperson415();
// End Cross Module References

// Begin Class APortal Function ClearTeleportCooldown
struct Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics
{
	struct Portal_eventClearTeleportCooldown_Parms
	{
		AActor* ActorToClear;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Portal.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorToClear;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::NewProp_ActorToClear = { "ActorToClear", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Portal_eventClearTeleportCooldown_Parms, ActorToClear), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::NewProp_ActorToClear,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APortal, nullptr, "ClearTeleportCooldown", nullptr, nullptr, Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::PropPointers), sizeof(Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::Portal_eventClearTeleportCooldown_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::Function_MetaDataParams), Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::Portal_eventClearTeleportCooldown_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APortal_ClearTeleportCooldown()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APortal_ClearTeleportCooldown_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APortal::execClearTeleportCooldown)
{
	P_GET_OBJECT(AActor,Z_Param_ActorToClear);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearTeleportCooldown(Z_Param_ActorToClear);
	P_NATIVE_END;
}
// End Class APortal Function ClearTeleportCooldown

// Begin Class APortal
void APortal::StaticRegisterNativesAPortal()
{
	UClass* Class = APortal::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ClearTeleportCooldown", &APortal::execClearTeleportCooldown },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APortal);
UClass* Z_Construct_UClass_APortal_NoRegister()
{
	return APortal::StaticClass();
}
struct Z_Construct_UClass_APortal_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * A portal actor that teleports pawns to a linked partner portal.\n * Uses a scene capture component to render a live preview of the\n * destination on its mesh surface.\n */" },
#endif
		{ "IncludePath", "Portal.h" },
		{ "ModuleRelativePath", "Portal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A portal actor that teleports pawns to a linked partner portal.\nUses a scene capture component to render a live preview of the\ndestination on its mesh surface." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mesh_MetaData[] = {
		{ "Category", "Portal" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Portal.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sceneCapture_MetaData[] = {
		{ "Category", "Portal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Captures the scene from the player's relative perspective to create\n// the \"window into the other side\" effect on this portal's surface.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Portal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Captures the scene from the player's relative perspective to create\nthe \"window into the other side\" effect on this portal's surface." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_rootArrow_MetaData[] = {
		{ "Category", "Portal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Defines the spawn point and facing direction for teleported actors.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Portal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Defines the spawn point and facing direction for teleported actors." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_renderTarget_MetaData[] = {
		{ "Category", "Portal" },
		{ "ModuleRelativePath", "Portal.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_boxComp_MetaData[] = {
		{ "Category", "Portal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Overlap volume that triggers teleportation when a pawn enters.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Portal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Overlap volume that triggers teleportation when a pawn enters." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherPortal_MetaData[] = {
		{ "Category", "Portal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The linked destination portal. Must be set in the editor.\n" },
#endif
		{ "ModuleRelativePath", "Portal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The linked destination portal. Must be set in the editor." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_mat_MetaData[] = {
		{ "Category", "Portal" },
		{ "ModuleRelativePath", "Portal.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeleportCooldown_MetaData[] = {
		{ "Category", "Portal" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Grace period after teleporting to prevent immediate re-trigger.\n" },
#endif
		{ "ModuleRelativePath", "Portal.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Grace period after teleporting to prevent immediate re-trigger." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_sceneCapture;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_rootArrow;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_renderTarget;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_boxComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherPortal;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_mat;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TeleportCooldown;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APortal_ClearTeleportCooldown, "ClearTeleportCooldown" }, // 2334240046
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APortal>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_mesh = { "mesh", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, mesh), Z_Construct_UClass_UStaticMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mesh_MetaData), NewProp_mesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_sceneCapture = { "sceneCapture", nullptr, (EPropertyFlags)0x001000000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, sceneCapture), Z_Construct_UClass_USceneCaptureComponent2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sceneCapture_MetaData), NewProp_sceneCapture_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_rootArrow = { "rootArrow", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, rootArrow), Z_Construct_UClass_UArrowComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_rootArrow_MetaData), NewProp_rootArrow_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_renderTarget = { "renderTarget", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, renderTarget), Z_Construct_UClass_UTextureRenderTarget2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_renderTarget_MetaData), NewProp_renderTarget_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_boxComp = { "boxComp", nullptr, (EPropertyFlags)0x0010000000080009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, boxComp), Z_Construct_UClass_UBoxComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_boxComp_MetaData), NewProp_boxComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_OtherPortal = { "OtherPortal", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, OtherPortal), Z_Construct_UClass_APortal_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherPortal_MetaData), NewProp_OtherPortal_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_mat = { "mat", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, mat), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_mat_MetaData), NewProp_mat_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APortal_Statics::NewProp_TeleportCooldown = { "TeleportCooldown", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APortal, TeleportCooldown), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeleportCooldown_MetaData), NewProp_TeleportCooldown_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APortal_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_sceneCapture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_rootArrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_renderTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_boxComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_OtherPortal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_mat,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APortal_Statics::NewProp_TeleportCooldown,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APortal_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APortal_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_firstperson415,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APortal_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APortal_Statics::ClassParams = {
	&APortal::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APortal_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APortal_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APortal_Statics::Class_MetaDataParams), Z_Construct_UClass_APortal_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APortal()
{
	if (!Z_Registration_Info_UClass_APortal.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APortal.OuterSingleton, Z_Construct_UClass_APortal_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APortal.OuterSingleton;
}
template<> FIRSTPERSON415_API UClass* StaticClass<APortal>()
{
	return APortal::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APortal);
APortal::~APortal() {}
// End Class APortal

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_Portal_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APortal, APortal::StaticClass, TEXT("APortal"), &Z_Registration_Info_UClass_APortal, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APortal), 3879151206U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_Portal_h_2374589907(TEXT("/Script/firstperson415"),
	Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_Portal_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_Portal_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
