// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AC_ShooterHelper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOCASE_S2_API UAC_ShooterHelper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ShooterHelper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Activate Weapon/Launch Projectile
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void ActivateWeapon (USceneComponent* Camera, float Distance, UStaticMeshComponent* Weapon, FName SpawnSocket, UClass* ProjectileType, UNiagaraSystem* MuzzleFlash);

		
};
