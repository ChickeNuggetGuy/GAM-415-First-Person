// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "firstperson415/PerlinProcTerrain.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePerlinProcTerrain() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
ENGINE_API UClass* Z_Construct_UClass_AActor();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
FIRSTPERSON415_API UClass* Z_Construct_UClass_APerlinProcTerrain();
FIRSTPERSON415_API UClass* Z_Construct_UClass_APerlinProcTerrain_NoRegister();
UPackage* Z_Construct_UPackage__Script_firstperson415();
// End Cross Module References

// Begin Class APerlinProcTerrain Function AlterMesh
struct Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics
{
	struct PerlinProcTerrain_eventAlterMesh_Parms
	{
		FVector impactPoint;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_impactPoint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::NewProp_impactPoint = { "impactPoint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PerlinProcTerrain_eventAlterMesh_Parms, impactPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::NewProp_impactPoint,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_APerlinProcTerrain, nullptr, "AlterMesh", nullptr, nullptr, Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::PropPointers), sizeof(Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::PerlinProcTerrain_eventAlterMesh_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::Function_MetaDataParams), Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::PerlinProcTerrain_eventAlterMesh_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APerlinProcTerrain_AlterMesh()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APerlinProcTerrain_AlterMesh_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APerlinProcTerrain::execAlterMesh)
{
	P_GET_STRUCT(FVector,Z_Param_impactPoint);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AlterMesh(Z_Param_impactPoint);
	P_NATIVE_END;
}
// End Class APerlinProcTerrain Function AlterMesh

// Begin Class APerlinProcTerrain
void APerlinProcTerrain::StaticRegisterNativesAPerlinProcTerrain()
{
	UClass* Class = APerlinProcTerrain::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AlterMesh", &APerlinProcTerrain::execAlterMesh },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(APerlinProcTerrain);
UClass* Z_Construct_UClass_APerlinProcTerrain_NoRegister()
{
	return APerlinProcTerrain::StaticClass();
}
struct Z_Construct_UClass_APerlinProcTerrain_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "PerlinProcTerrain.h" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_XSize_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_YSize_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZMultiplier_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_noiseScale_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_scale_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UVScale_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_radius_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Depth_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mat_MetaData[] = {
		{ "Category", "PerlinProcTerrain" },
		{ "ModuleRelativePath", "PerlinProcTerrain.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_XSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_YSize;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ZMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_noiseScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_scale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_UVScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_radius;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Depth;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mat;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APerlinProcTerrain_AlterMesh, "AlterMesh" }, // 4156420800
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APerlinProcTerrain>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_XSize = { "XSize", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, XSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_XSize_MetaData), NewProp_XSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_YSize = { "YSize", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, YSize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_YSize_MetaData), NewProp_YSize_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_ZMultiplier = { "ZMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, ZMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZMultiplier_MetaData), NewProp_ZMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_noiseScale = { "noiseScale", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, noiseScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_noiseScale_MetaData), NewProp_noiseScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_scale = { "scale", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, scale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_scale_MetaData), NewProp_scale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_UVScale = { "UVScale", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, UVScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UVScale_MetaData), NewProp_UVScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_radius = { "radius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, radius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_radius_MetaData), NewProp_radius_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_Depth = { "Depth", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, Depth), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Depth_MetaData), NewProp_Depth_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_Mat = { "Mat", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APerlinProcTerrain, Mat), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mat_MetaData), NewProp_Mat_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APerlinProcTerrain_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_XSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_YSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_ZMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_noiseScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_scale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_UVScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_radius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_Depth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APerlinProcTerrain_Statics::NewProp_Mat,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APerlinProcTerrain_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APerlinProcTerrain_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_firstperson415,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APerlinProcTerrain_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APerlinProcTerrain_Statics::ClassParams = {
	&APerlinProcTerrain::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APerlinProcTerrain_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APerlinProcTerrain_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APerlinProcTerrain_Statics::Class_MetaDataParams), Z_Construct_UClass_APerlinProcTerrain_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APerlinProcTerrain()
{
	if (!Z_Registration_Info_UClass_APerlinProcTerrain.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APerlinProcTerrain.OuterSingleton, Z_Construct_UClass_APerlinProcTerrain_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APerlinProcTerrain.OuterSingleton;
}
template<> FIRSTPERSON415_API UClass* StaticClass<APerlinProcTerrain>()
{
	return APerlinProcTerrain::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APerlinProcTerrain);
APerlinProcTerrain::~APerlinProcTerrain() {}
// End Class APerlinProcTerrain

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_PerlinProcTerrain_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APerlinProcTerrain, APerlinProcTerrain::StaticClass, TEXT("APerlinProcTerrain"), &Z_Registration_Info_UClass_APerlinProcTerrain, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APerlinProcTerrain), 1815137248U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_PerlinProcTerrain_h_1391954497(TEXT("/Script/firstperson415"),
	Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_PerlinProcTerrain_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_hawki_OneDrive_Documents_Unreal_Projects_firstperson415_Source_firstperson415_PerlinProcTerrain_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
