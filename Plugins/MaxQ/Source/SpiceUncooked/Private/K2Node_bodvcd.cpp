// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Node_bodvcd.h"
#include "K2Node_OutWithSelectorOp.h"
#include "K2Utilities.h"
#include "SpiceK2.h"

#include "EdGraphSchema_K2.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"


using namespace ENodeTitleType;


#define LOCTEXT_NAMESPACE "K2Node_bodvcd"


UK2Node_bodvcd::UK2Node_bodvcd()
{
    OperationsMap = TMap<FName, FK2SingleOutputOpWithComponentFilter>();

    auto op = DoubleOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = RealOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = ArrayDoubleOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = ArrayRealOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDimensionlessVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SMassConstantOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDegreesOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SVelocityVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceX(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceY(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceZ(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = WildcardOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);

    CurrentOperation = op;

#if WITH_EDITOR
    // Ensure the specified actions actually exist!
    for (const auto& [shortname, _op] : OperationsMap)
    {
        if (!_op.K2NodeName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(_op.K2NodeName));
        }
        if (!_op.Conversion.ConversionName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(_op.Conversion.ConversionName));
        }
    }
#endif
}


FText UK2Node_bodvcd::GetNodeTitle(Type TitleType) const
{
    switch (TitleType)
    {
    case FullTitle:
        /** The full title, may be multiple lines. */
        return FText::FromString(CurrentOperation.FullName);
    case ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "bodvcd - fetch value from kernel pool");
    case MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "bodvcd");
    }

    return LOCTEXT("ShortTitle", "bodvcd");
}


FText UK2Node_bodvcd::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Kernel");
}


FText UK2Node_bodvcd::GetKeywords() const
{
    return LOCTEXT("Keywords", "CONSTANTS");
}


FText UK2Node_bodvcd::GetTooltipText() const
{
    return LOCTEXT("Tooltip", "Fetch from the kernel pool the double precision values of an item associated with a body");
}



void UK2Node_bodvcd::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

void UK2Node_bodvcd::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);

    if (Pin->LinkedTo.Num() != 1)
    {
        CurrentOperation = WildcardOp();
        const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
        K2Schema->ForceVisualizationCacheClear();
    }
}



void UK2Node_bodvcd::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    // Inputs - Body/Item
    UEdGraphPin* bodyPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, body_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(bodyPin, body_Value);
    bodyPin->PinToolTip = TEXT("Body name");
    bodyPin->DefaultValue = FString::FromInt(body_DefaultValue);

    UEdGraphPin* itemPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, item_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(itemPin, item_Value);
    itemPin->PinToolTip = TEXT("Item for which values are desired. (\"RADII\", \"NUT_PREC_ANGLES\", etc.)");
    itemPin->DefaultValue = item_DefaultValue.ToString();
}


void UK2Node_bodvcd::ReconstructNode()
{
    Super::ReconstructNode();

    if (returnValuePin()->LinkedTo.Num() != 1)
    {
        CurrentOperation = WildcardOp();
    }
}

void UK2Node_bodvcd::ExpandOperationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* operationNode)
{
    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    // Now the body and item pins...
    auto thisBody = bodyPin();   auto thatBody = operationNode->FindPinChecked(body_Field);
    auto thisItem = itemPin();   auto thatItem = operationNode->FindPinChecked(item_Field);

    MovePinLinksOrCopyDefaults(CompilerContext, thisBody, thatBody);
    MovePinLinksOrCopyDefaults(CompilerContext, thisItem, thatItem);
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::WildcardOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd"), USpiceK2::bodvcd_double, FK2Type::Wildcard()) };
    v.FullName = v.ShortName.ToString() + "\nReturn value from the kernel pool";
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::DoubleOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd Double"), USpiceK2::bodvcd_double, FK2Type::Double()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::RealOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd Real"), USpiceK2::bodvcd_double, FK2Type::Real()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::ArrayDoubleOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd Array(Double)"), USpiceK2::bodvcd_array, FK2Type::DoubleArray()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::ArrayRealOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd Array(Real)"), USpiceK2::bodvcd_array, FK2Type::RealArray()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SDimensionlessVectorOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SDimensionlessVector"), USpiceK2::bodvcd_vector, FK2Type::SDimensionlessVector()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SMassConstantOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SMassConstant"), USpiceK2::bodvcd_double, FK2Conversion::DoubleToSMassConstant()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SDistanceOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SDistance"), USpiceK2::bodvcd_double, FK2Conversion::DoubleToSDistance()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SDegreesOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SAngle(Degrees)"), USpiceK2::bodvcd_double, FK2Conversion::DegreesToSAngle()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SDistanceVectorOp()
{

    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SDistanceVector"), USpiceK2::bodvcd_vector, FK2Conversion::SDimensionlessVectorToSDistanceVector()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SVelocityVectorOp()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SVelocityVector"), USpiceK2::bodvcd_vector, FK2Conversion::SDimensionlessVectorToSVelocityVector()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SDistanceX()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SDistanceVector.X"), USpiceK2::bodvcd_vector, FK2Conversion::SDimensionlessVectorXToSDistance()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SDistanceY()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SDistanceVector.Y"), USpiceK2::bodvcd_vector, FK2Conversion::SDimensionlessVectorYToSDistance()) };
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_bodvcd::SDistanceZ()
{
    static auto v{ FK2SingleOutputOpWithComponentFilter(FName("bodvcd SDistanceVector.Z"), USpiceK2::bodvcd_vector, FK2Conversion::SDimensionlessVectorZToSDistance()) };
    return v;
}


#undef LOCTEXT_NAMESPACE