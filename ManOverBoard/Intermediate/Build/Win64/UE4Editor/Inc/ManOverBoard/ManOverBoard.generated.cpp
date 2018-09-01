// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Boilerplate C++ definitions for a single module.
	This is automatically generated by UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "ManOverBoard.h"
#include "ManOverBoard.generated.dep.h"
PRAGMA_DISABLE_OPTIMIZATION
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1ManOverBoard() {}
	void AManOverBoardGameModeBase::StaticRegisterNativesAManOverBoardGameModeBase()
	{
	}
	IMPLEMENT_CLASS(AManOverBoardGameModeBase, 4197082574);
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ENGINE_API class UClass* Z_Construct_UClass_AGameModeBase();

	MANOVERBOARD_API class UClass* Z_Construct_UClass_AManOverBoardGameModeBase_NoRegister();
	MANOVERBOARD_API class UClass* Z_Construct_UClass_AManOverBoardGameModeBase();
	MANOVERBOARD_API class UPackage* Z_Construct_UPackage__Script_ManOverBoard();
	UClass* Z_Construct_UClass_AManOverBoardGameModeBase_NoRegister()
	{
		return AManOverBoardGameModeBase::StaticClass();
	}
	UClass* Z_Construct_UClass_AManOverBoardGameModeBase()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AGameModeBase();
			Z_Construct_UPackage__Script_ManOverBoard();
			OuterClass = AManOverBoardGameModeBase::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900288;


				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("HideCategories"), TEXT("Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("ManOverBoardGameModeBase.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("ManOverBoardGameModeBase.h"));
				MetaData->SetValue(OuterClass, TEXT("ShowCategories"), TEXT("Input|MouseInput Input|TouchInput"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AManOverBoardGameModeBase(Z_Construct_UClass_AManOverBoardGameModeBase, &AManOverBoardGameModeBase::StaticClass, TEXT("AManOverBoardGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AManOverBoardGameModeBase);
	UPackage* Z_Construct_UPackage__Script_ManOverBoard()
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/ManOverBoard")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0x774288A2;
			Guid.B = 0x0616BEE0;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif

PRAGMA_ENABLE_DEPRECATION_WARNINGS
