// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(RootComp);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName("ParticleSystemComponent"));
	ParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HitBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("HitBlast"));
	HitBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Force = CreateDefaultSubobject<URadialForceComponent>(FName("Force"));
	Force->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}


void AProjectile::Launch(float Speed)
{
	if (!ensure(ProjectileMovementComponent)) { return; }
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

