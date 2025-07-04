// Fill out your copyright notice in the Description page of Project Settings.


#include "Minions/LMTMinionBase.h"

#include "LMTAttributeComp.h"
#include "LMTProjectileBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/LMTWidgetBase.h"
//#include "NavModifierComponent.h"
//#include "Components/CapsuleComponent.h"



ALMTMinionBase::ALMTMinionBase()
{
	PrimaryActorTick.bCanEverTick = true;

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

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this,&ALMTMinionBase::OnCapsuleHit);


	
}


void ALMTMinionBase::BeginPlay()
{
	Super::BeginPlay();


	if (GetTeam() == ECharTeam::Red)
	{
		//for red team
		LaneStart = FVector(1555.f,-930.f,35.f);
		LaneEnd = FVector(-1688.f,1927.f,35.f);
	}
	else if (GetTeam() == ECharTeam::Blue)
	{
		//for blue team
		LaneStart = FVector(-1688.f,1927.f,35.f);
		LaneEnd = FVector(1555.f,-930.f,35.f);
	}

	UE_LOG(LogTemp, Warning, TEXT("team %s"), GetTeam() == ECharTeam::Red ? TEXT("Red") : TEXT("Blue"));
	SetActorLocation(LaneStart);
	//set rotation to face the lane end
	FRotator LookAtRotation = (LaneEnd - LaneStart).Rotation();
	SetActorRotation(LookAtRotation);
	
	
}




void ALMTMinionBase::OnHealthChanged(float NewHealthPercent)
{
	ULMTWidgetBase* HealthWidget = Cast<ULMTWidgetBase>(HealthBarWidget->GetUserWidgetObject());
	if (HealthWidget)
	{
		HealthWidget->SetHealthBar(NewHealthPercent);
	}
	
}

void ALMTMinionBase::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (UCapsuleComponent* otherCharCapsule = Cast<UCapsuleComponent>(OtherComp))
	{
		if (bIsAttacking)
		{
			return;
		}
		
		if (!bCanAvoid)
		{
			return; // cooldown aktif, avoidance yapma
		}
		
		const float MinSpeedThreshold = 5.0f;

		if (GetVelocity().SizeSquared() < MinSpeedThreshold * MinSpeedThreshold)
		{
			return;
		}
		
		//velocity is not zero so character is moving and overlapped with other character capsule
		// so move to side 

		FVector MyLoc = GetActorLocation();
		FVector TargetLoc = TargetLocation;
		FVector MinionLoc = OtherActor->GetActorLocation();

		MyLoc.Z = 0.f;
		TargetLoc.Z = 0.f;
		MinionLoc.Z = 0.f;

		FVector2D ToTarget = FVector2D(TargetLoc - MyLoc);
		FVector2D ToMinion = FVector2D(MinionLoc - MyLoc);

		float cross = (ToTarget.X * ToMinion.Y) - (ToTarget.Y * ToMinion.X);

		float MyRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
		float OtherRadius = otherCharCapsule->GetScaledCapsuleRadius();
		float AvoidDistance = (MyRadius + OtherRadius) + 60.f;
		UE_LOG(LogTemp, Warning, TEXT("avoid distance -------------  = %f"),AvoidDistance);
		

		if (cross < 0 )
		{
			UE_LOG(LogTemp, Warning, TEXT("minyon solda sağa git"));
			AvoidingMoveLocation = GetActorLocation() + GetActorRightVector() * AvoidDistance;
		}
		else if (cross > 0 )
		{
			UE_LOG(LogTemp, Warning, TEXT("Minyan sağda sola git"));
			AvoidingMoveLocation = GetActorLocation() + -GetActorRightVector() * AvoidDistance;
		}

		UAIBlueprintHelperLibrary::SimpleMoveToLocation( GetController(), AvoidingMoveLocation);
		bAvoiding = true;
		bCanAvoid = false;
		GetWorld()->GetTimerManager().SetTimer(AvoidCooldownTimerHandle, this, &ALMTMinionBase::ResetAvoidCooldown, 0.5f, false);
		GetWorld()->GetTimerManager().SetTimer(AvoidTimeoutHandle, this, &ALMTMinionBase::ForceStopAvoiding, 2.f, false);
		
		
	}
	
}

void ALMTMinionBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (bAvoiding)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s actor loc"),*GetActorLocation().ToString());
		UE_LOG(LogTemp, Warning, TEXT("ben : ' %s '  avoid ediyomm avoiding target loc : %s"),*GetActorNameOrLabel(),*AvoidingMoveLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("distance %f"),FVector::Dist2D(GetActorLocation(),AvoidingMoveLocation));
		if (FVector::Dist2D(GetActorLocation(),AvoidingMoveLocation) <= 45.f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
			UE_LOG(LogTemp, Warning, TEXT("avoidance bitti targete gidiyom aga "));
			bAvoiding = false;
			GetWorld()->GetTimerManager().ClearTimer(AvoidTimeoutHandle);
		}
	}
}


void ALMTMinionBase::ResetAvoidCooldown()
{
	bCanAvoid = true;
}


USphereComponent* ALMTMinionBase::GetAttackRangeSphere()
{
	return AttackRangeSphere;
}

void ALMTMinionBase::Attack()
{
	//bisattacking
	//bisattackoncooldown
	
	if (bIsAttacking) { return; }
	if (bIsAttackOnCooldown) { return; }
	
	
	LastTarget = CurrentTarget;
	UE_LOG(LogTemp, Warning, TEXT("%s is attacking %s"),*GetName(),*LastTarget->GetName());
	PlayAnimMontage(AttackMontage);
	bIsAttacking = true;
}


void ALMTMinionBase::SetTarget(ALMTBaseCharacter* InTarget)
{
	CurrentTarget = InTarget;
}

void ALMTMinionBase::ResetAttack()
{
	bIsAttacking = false;
	bIsAttackOnCooldown = false;
}

bool ALMTMinionBase::CheckTargetIsInRange()
{
		return ((GetActorLocation() - CurrentTarget->GetActorLocation()).Length() <= AttackRange);
}

void ALMTMinionBase::SetTargetLocation(FVector InTargetLocation)
{
	TargetLocation = InTargetLocation;
}

bool ALMTMinionBase::GetBAvoiding()
{
	return bAvoiding;
}

void ALMTMinionBase::ForceStopAvoiding()
{
	if (bAvoiding)
	{
		UE_LOG(LogTemp, Warning, TEXT("Avoidance timeout, forcing stop."));
		bAvoiding = false;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
	}
}


