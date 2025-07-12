// Fill out your copyright notice in the Description page of Project Settings.


#include "LMTProjectileBase.h"

#include "LMTAttributeComp.h"
#include "LMTCharacter.h"
#include "LMTPlayerController.h"
#include "LMT_GameModeBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Minions/LMTMinionBase.h"

// Sets default values
ALMTProjectileBase::ALMTProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALMTProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALMTProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	if (TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("tick"));
		return;
	}
	
	FVector CurrentLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("cuurent loc : %s"),*GetActorLocation().ToString());
	FVector TargetLocation = TargetActor->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("target loc : %s"),*TargetActor->GetActorLocation().ToString());
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation,TargetLocation,DeltaTime,ProjectileSpeed);

	SetActorLocation(NewLocation);

	UE_LOG(LogTemp, Warning, TEXT("distamce : %f"), FVector::Dist(NewLocation,TargetLocation));
	
	FRotator LookAtRotation = (TargetLocation - CurrentLocation).Rotation();
	SetActorRotation(LookAtRotation);

	if (FVector::Dist(NewLocation,TargetLocation) < 10.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("vurdum"));
		ULMTAttributeComp* targetAttribute = TargetActor->GetComponentByClass<ULMTAttributeComp>();
		if (targetAttribute)
		{
			// Eğer hedef zaten ölmüşse işlem yapma
			if (targetAttribute->GetHealth() <= 0.f)
			{
				Destroy();
				return;
			}

			targetAttribute->TakeDamage(Damage);
			if (auto InstigatorChar =  Cast<ALMTCharacter>(GetInstigator()))
			{
				if (targetAttribute->GetHealth() <= 0 )
				{
					ALMT_GameModeBase* GameMode = Cast<ALMT_GameModeBase>(UGameplayStatics::GetGameMode(this));
					GameMode->IncrementCsScore();
					
					ALMTPlayerController* PController = Cast<ALMTPlayerController>(InstigatorChar->GetController());
					PController->UpdateCsScoreHud(GameMode->GetCsScore());
					//UE_LOG(LogTemp, Warning, TEXT("CS SCORE : %f"),GameMode->GetCsScore());
					auto TargetMinion = Cast<ALMTMinionBase>(TargetActor);
					if (TargetMinion == nullptr) return;
					
					if (TSubclassOf<UUserWidget> GoldPopupWidgetClass = TargetMinion ->GetGoldWidgetClass())
					{
						APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
						if (PC)
						{
							UUserWidget* GoldPopupWidget = CreateWidget<UUserWidget>(PC, GoldPopupWidgetClass);
							if (GoldPopupWidget)
							{
								FVector2D ScreenPosition;
								FVector MinionWorldPos = TargetActor->GetActorLocation() + FVector(0.f, 0.f, 100.f); // biraz yukarı kaydır

								PC->ProjectWorldLocationToScreen(MinionWorldPos, ScreenPosition);

								float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(PC);
								ScreenPosition /= ViewportScale;

								GoldPopupWidget->AddToViewport();
								GoldPopupWidget->SetPositionInViewport(ScreenPosition, false);
								
								if (auto Sound = TargetMinion->GetGoldCollectSound())
								{
									UGameplayStatics::PlaySound2D(this,Sound);
								}
							}
						}
					}
					
					
				}
			}
		}
		
		Destroy();
	}
	
}

void ALMTProjectileBase::SetTargetActor(AActor* InActor)
{
	if (InActor != nullptr)
	{
		TargetActor = InActor;
		UE_LOG(LogTemp, Warning, TEXT("target actor : %s"),*TargetActor->GetName());
	}
}

void ALMTProjectileBase::SetDamage(float InDamage)
{
	Damage = InDamage;
}
