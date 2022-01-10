// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#include "K2Node_bodvrd.h"
#include "K2Node_OperationNOutput.h"
#include "K2Utilities.h"
#include "SpiceK2.h"

#include "EdGraphSchema_K2.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"


using namespace ENodeTitleType;


#define LOCTEXT_NAMESPACE "K2Node_bodvrd"


UK2Node_bodvrd::UK2Node_bodvrd()
{
    OperationsMap = TMap<FName, FK2OperationNOutput>();

    auto op = DoubleOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = ArrayDoubleOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDimensionlessVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SMassConstantOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDegreesOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SVelocityVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = WildcardOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);

    CurrentOperation = op;
    CurrentOperation.FullName = CurrentOperation.ShortName.ToString() + "\nReturn d.p. values from the kernel pool";
}


FText UK2Node_bodvrd::GetNodeTitle(Type TitleType) const
{
    switch (TitleType)
    {
    case FullTitle:
        /** The full title, may be multiple lines. */
        return FText::FromString(CurrentOperation.FullName);
    case ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "bodvrd - fetch value from kernel pool");
    case MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "bodvrd");
    }

    return LOCTEXT("ShortTitle", "bodvrd");
}


FText UK2Node_bodvrd::GetMenuCategory() const
{
    return LOCTEXT("Category", "Spice|Api|Kernel");
}


FText UK2Node_bodvrd::GetKeywords() const
{
    return LOCTEXT("Keywords", "CONSTANTS");
}


FText UK2Node_bodvrd::GetTooltipText() const
{
    return LOCTEXT("Tooltip", "Fetch from the kernel pool the double precision values of an item associated with a body");
}



void UK2Node_bodvrd::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

void UK2Node_bodvrd::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);

    if (Pin->LinkedTo.Num() != 1)
    {
        CurrentOperation = WildcardOp();
        const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
        K2Schema->ForceVisualizationCacheClear();
    }
}



void UK2Node_bodvrd::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    // Inputs - Body/Item
    UEdGraphPin* bodyPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, bodynm_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(bodyPin, bodynm_Value);
    bodyPin->PinToolTip = TEXT("Body name");
    bodyPin->DefaultValue = bodynm_DefaultValue.ToString();

    UEdGraphPin * itemPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, item_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(itemPin, item_Value);
    itemPin->PinToolTip = TEXT("Item for which values are desired. (\"RADII\", \"NUT_PREC_ANGLES\", etc.)");
    itemPin->DefaultValue = item_DefaultValue.ToString();
}


void UK2Node_bodvrd::ReconstructNode()
{
    Super::ReconstructNode();

    if (returnValuePin()->LinkedTo.Num() != 1)
    {
        CurrentOperation = WildcardOp();
        CurrentOperation.FullName = CurrentOperation.ShortName.ToString() + "\nReturn d.p. values from the kernel pool";
    }
}

void UK2Node_bodvrd::ExpandOperationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* operationNode)
{
    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    // Now the body and item pins...
    auto thisBodynm = bodynmPin();   auto thatBodynm = operationNode->FindPinChecked(bodynm_Field);
    auto thisItem = itemPin();   auto thatItem = operationNode->FindPinChecked(item_Field);

    MovePinLinksOrCopyDefaults(CompilerContext, thisBodynm, thatBodynm);
    MovePinLinksOrCopyDefaults(CompilerContext, thisItem, thatItem);
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::WildcardOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd"), FName("bodvrd_double_K2"), FK2Type::Wildcard());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::DoubleOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd Double"), FName("bodvrd_double_K2"), FK2Type::Double());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::ArrayDoubleOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd Array(Double)"), FName("bodvrd_array_K2"), FK2Type::DoubleArray());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::SDimensionlessVectorOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd SDimensionlessVector"), FName("bodvrd_vector_K2"), FK2Type::SDimensionlessVector());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::SMassConstantOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd SMassConstant"), FName("bodvrd_double_K2"), FK2Conversion::DoubleToSMassConstant());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::SDistanceOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd SDistance"), FName("bodvrd_double_K2"), FK2Conversion::DoubleToSDistance());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::SDegreesOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd SAngle(Degrees)"), FName("bodvrd_double_K2"), FK2Conversion::DegreesToSAngle());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::SDistanceVectorOp()
{

    static auto v = FK2OperationNOutput(FName("bodvrd SDistanceVector"), FName("bodvrd_vector_K2"), FK2Conversion::SDimensionlessVectorToSDistanceVector());
    return v;
}

SPICEUNCOOKED_API FK2OperationNOutput UK2Node_bodvrd::SVelocityVectorOp()
{
    static auto v = FK2OperationNOutput(FName("bodvrd SVelocityVector"), FName("bodvrd_vector_K2"), FK2Conversion::SDimensionlessVectorToSVelocityVector());
    return v;
}



#undef LOCTEXT_NAMESPACE