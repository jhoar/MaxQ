// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "K2Type.h"


SPICEUNCOOKED_API FK2Type FK2Type::Wildcard()
{
    static FK2Type Wildcard = FK2Type(FName("Wildcard"), UEdGraphSchema_K2::PC_Wildcard);
    return Wildcard;
}

SPICEUNCOOKED_API FK2Type FK2Type::Double()
{
    static FK2Type Double = FK2Type(FName("Double"), UEdGraphSchema_K2::PC_Double);
    return Double;
}

SPICEUNCOOKED_API FK2Type FK2Type::DoubleArray()
{
    static FK2Type ArrayDouble = FK2Type(FName("Array(Double)"), UEdGraphSchema_K2::PC_Double, EPinContainerType::Array);
    return ArrayDouble;
}


SPICEUNCOOKED_API FK2Type FK2Type::SDimensionlessVector()
{
    static FK2Type DimensionlessVector = FK2Type(FSDimensionlessVector::StaticStruct());
    return DimensionlessVector;
}

SPICEUNCOOKED_API FK2Type FK2Type::SMassConstant()
{
    static FK2Type MassConstant = FK2Type(FSMassConstant::StaticStruct());
    return MassConstant;
}

SPICEUNCOOKED_API FK2Type FK2Type::SDistance()
{
    static FK2Type Distance = FK2Type(FSDistance::StaticStruct());
    return Distance;
}

SPICEUNCOOKED_API FK2Type FK2Type::SAngle()
{
    static FK2Type Angle = FK2Type(FSAngle::StaticStruct());
    return Angle;
}

SPICEUNCOOKED_API FK2Type FK2Type::SDistanceVector()
{
    static FK2Type DistanceVector = FK2Type(FSDistanceVector::StaticStruct());
    return DistanceVector;
}

SPICEUNCOOKED_API FK2Type FK2Type::SVelocityVector()
{
    static FK2Type VelocityVector = FK2Type(FSVelocityVector::StaticStruct());
    return VelocityVector;
}