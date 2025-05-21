// Fill out your copyright notice in the Description page of Project Settings.


#include "LMTCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Minions/LMTMinionBase.h"


// Sets default values
ALMTCharacter::ALMTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraSpringArmComponent->SetupAttachment(RootComponent);
	CameraSpringArmComponent->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraSpringArmComponent->TargetArmLength = 800.f;
	CameraSpringArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraSpringArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraSpringArmComponent, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ALMTCharacter::OnCapsuleOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this,&ALMTCharacter::OnCapsuleHit);
}

// Called when the game starts or when spawned
void ALMTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ALMTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (CurrentTarget != nullptr)
	{
		if (CheckIsTargetInRange())
		{
			GetController()->StopMovement();
			Attack();
		}
	}

	if (bAvoiding)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s actor loc"),*GetActorLocation().ToString());
		UE_LOG(LogTemp, Warning, TEXT("avoid ediyomm avoiding target loc : %s"),*AvoidingMoveLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("distance %f"),FVector::Dist2D(GetActorLocation(),AvoidingMoveLocation));
		if (FVector::Dist2D(GetActorLocation(),AvoidingMoveLocation) <= 45.f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLocation);
			UE_LOG(LogTemp, Warning, TEXT("avoidance bitti targete gidiyom aga "));
			bAvoiding = false;
		}
	}

}

// Called to bind functionality to input
void ALMTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALMTCharacter::Attack()
{
	if (CurrentTarget == nullptr) { return; }
	
	UE_LOG(LogTemp, Warning, TEXT("menzilde perform attack"));
	CurrentTarget = nullptr;
	
}

bool ALMTCharacter::CheckIsTargetInRange()
{
	return ((GetActorLocation() - CurrentTarget->GetActorLocation()).Length() <= AttackRange);
}

// void ALMTCharacter::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	if (UCapsuleComponent* otherCharCapsule = Cast<UCapsuleComponent>(OtherComp))
// 	{
// 		if (GetVelocity() == FVector::ZeroVector)
// 		{
// 			return;
// 		}
// 		//velocity is not zero so character is moving and overlapped with other character capsule
// 		// so move to side  
// 		
// 		FVector MyLoc = GetActorLocation();
// 		FVector TargetLoc = TargetLocation;
// 		FVector MinionLoc = OtherActor->GetActorLocation();
//
// 		MyLoc.Z = 0.f;
// 		TargetLoc.Z = 0.f;
// 		MinionLoc.Z = 0.f;
//
// 		FVector2D ToTarget = FVector2D(TargetLoc - MyLoc);
// 		FVector2D ToMinion = FVector2D(MinionLoc - MyLoc);
//
// 		float cross = (ToTarget.X * ToMinion.Y) - (ToTarget.Y * ToMinion.X);
//
// 		float MyRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
// 		float OtherRadius = otherCharCapsule->GetScaledCapsuleRadius();
// 		float AvoidDistance = (MyRadius + OtherRadius) + 10.f;
// 		UE_LOG(LogTemp, Warning, TEXT("avoid distance -------------  = %f"),AvoidDistance);
//
// 		if (cross < 0 )
// 		{
// 			AvoidingMoveLocation = GetActorLocation() + GetActorRightVector() * AvoidDistance;
// 			UAIBlueprintHelperLibrary::SimpleMoveToLocation( GetController(), AvoidingMoveLocation);
// 			bAvoiding = true;
// 		}
// 		else if (cross > 0 )
// 		{
// 			AvoidingMoveLocation = GetActorLocation() + -GetActorRightVector() * AvoidDistance;
// 			UAIBlueprintHelperLibrary::SimpleMoveToLocation( GetController(), AvoidingMoveLocation);
// 			bAvoiding = true;
// 		}
// 	}
// 	
// }

void ALMTCharacter::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (UCapsuleComponent* otherCharCapsule = Cast<UCapsuleComponent>(OtherComp))
	{

		if (!bCanAvoid)
		{
			return; // cooldown aktif, avoidance yapma
		}
		
		if (GetVelocity() == FVector::ZeroVector)
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
		float AvoidDistance = (MyRadius + OtherRadius) + 10.f;
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
		GetWorld()->GetTimerManager().SetTimer(AvoidCooldownTimerHandle, this, &ALMTCharacter::ResetAvoidCooldown, 0.5f, false);
		
	}
	
}

void ALMTCharacter::ResetAvoidCooldown()
{
	bCanAvoid = true;
}


ACameraActor* ALMTCharacter::GetTargetCameraActor()
{
	return TargetCameraActor;
}

void ALMTCharacter::SetCurrentTarget(ALMTMinionBase* MinionTarget)
{
	CurrentTarget = MinionTarget;
}

class ALMTMinionBase* ALMTCharacter::GetCurrentTarget()
{
	return CurrentTarget;
}

void ALMTCharacter::SetTargetLocation(FVector InLocation)
{
	TargetLocation = InLocation;
}

