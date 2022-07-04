// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ShooterHelper.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UAC_ShooterHelper::UAC_ShooterHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_ShooterHelper::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_ShooterHelper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Activate Weapon/Launch Projectile
void UAC_ShooterHelper::ActivateWeapon(USceneComponent* Camera, float Distance, UStaticMeshComponent* Weapon,
	FName SpawnSocket, UClass* ProjectileType, UNiagaraSystem* MuzzleFlash)
{
	//Local Variables
	FHitResult HitResult;
	FCollisionQueryParams HitSetup;
	FVector Target;
	HitSetup.AddIgnoredActor(GetOwner());
	
	//Line Trace
	FVector TraceStart = Camera->GetComponentLocation();
	FVector TraceEnd = TraceStart + (Camera->GetForwardVector()*Distance);
	GetOwner()->GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECC_Camera,HitSetup); // Camera Collision Channel

	//Set Target Location Dependent On Trace Result
	bool Success = HitResult.bBlockingHit;
	Success ? Target = HitResult.Location : Target = HitResult.TraceEnd;

	// Spawn Projectile
	const FVector SpawnLocation = Weapon->GetSocketLocation(SpawnSocket);
	const FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation,Target);
	GetWorld()->SpawnActor(ProjectileType, &SpawnLocation, &SpawnRotation);

	//Play Muzzle Flash VFX
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this->GetWorld(),MuzzleFlash,SpawnLocation,SpawnRotation,FVector(2,.1,.1));
	
}

