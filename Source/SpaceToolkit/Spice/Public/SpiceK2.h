// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"
#include "SpiceK2.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICE_API USpiceK2 : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (ExpandEnumAsExecs = "ResultCode"))
    static double bodvrd_double_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSDimensionlessVector bodvrd_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (ExpandEnumAsExecs = "ResultCode"))
    static TArray<double> bodvrd_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSEphemerisTime Conv_DoubleToSEphemerisTime_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSEphemerisPeriod Conv_DoubleToSEphemerisPeriod_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSMassConstant Conv_DoubleToSMassConstant_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSDistance Conv_DoubleToSDistance_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSAngle Conv_DegreesToSAngle_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSAngle Conv_RadiansToSAngle_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSAngularRate Conv_DegreesPersecondToSAngularRate_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSAngularRate Conv_RadiansPersecondToSAngularRate_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSAngularRate Conv_MinutesPerTurnToSAngularRate_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSDistanceVector Conv_SDimensionlessVectorToSDistanceVector_K2(const FSDimensionlessVector& value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
    static FSVelocityVector Conv_SDimensionlessVectorToSVelocityVector_K2(const FSDimensionlessVector& value);
};


