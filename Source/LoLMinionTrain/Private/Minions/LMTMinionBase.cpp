// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionBase.h"

#include "LMTAttributeComp.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/LMTWidgetBase.h"
//#include "NavModifierComponent.h"
//#include "Components/CapsuleComponent.h"


ALMTMinionBase::ALMTMinionBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// NavModifierComponent = CreateDefaultSubobject<UNavModifierComponent>("NavModifierComponent");
	// NavModifierComponent->FailsafeExtent = FVector(5.f,5.f,5.f);
	// NavModifierComponent->SetActive(false);
	// NavModifierComponent->SetComponentTickEnabled(false);

	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	AttributeComp = CreateDefaultSubobject<ULMTAttributeComp>(TEXT("AttributeComp"));
	AttributeComp->SetHealth(AttributeComp->GetMaxHealth());
	AttributeComp->OnHealthChanged.AddDynamic(this,&ALMTMinionBase::OnHealthChanged);

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetDrawSize(FVector2D(85.f,7.f));

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeSphere->SetupAttachment(RootComponent);
	
}


void ALMTMinionBase::BeginPlay()
{
	Super::BeginPlay();
	
}




void ALMTMinionBase::OnHealthChanged(float NewHealthPercent)
{
	ULMTWidgetBase* HealthWidget = Cast<ULMTWidgetBase>(HealthBarWidget->GetUserWidgetObject());
	if (HealthWidget)
	{
		HealthWidget->SetHealthBar(NewHealthPercent);
	}
	
}




void ALMTMinionBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

USphereComponent* ALMTMinionBase::GetAttackRangeSphere()
{
	return AttackRangeSphere;
}


