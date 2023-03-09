// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASCourseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GASCourseCharBaseAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class GASCOURSE_API UGASCourseCharBaseAttributeSet : public UGASCourseAttributeSet
{
	GENERATED_BODY()

public:

	UGASCourseCharBaseAttributeSet();

	// AttributeSet Overrides
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	
	UPROPERTY(BlueprintReadOnly, Category = "Character Base Attributes", ReplicatedUsing=OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UGASCourseCharBaseAttributeSet, MovementSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Character Base Attributes", ReplicatedUsing=OnRep_CrouchSpeed)
	FGameplayAttributeData CrouchSpeed;
	ATTRIBUTE_ACCESSORS(UGASCourseCharBaseAttributeSet, CrouchSpeed)

protected:
	
	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute,
		float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	
	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
	
	UFUNCTION()
	virtual void OnRep_CrouchSpeed(const FGameplayAttributeData& OldCrouchSpeed);
	
};
