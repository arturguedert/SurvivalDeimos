// Fill out your copyright notice in the Description page of Project Settings.


#include "Arma.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/SkeletalMesh.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/SkeletalMeshActor.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"
#include "PersonagemTPS.h"
#include "BotCharacter.h"


// Sets default values
AArma::AArma()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MalhaDaArma = CreateDefaultSubobject<USkeletalMeshComponent>(FName("MalhaDaArma"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshDaArma(TEXT("/Script/Engine.SkeletalMesh'/Game/Weapons/Rifle.Rifle'"));
	if (MeshDaArma.Succeeded())
	{
		MalhaDaArma->SetSkeletalMesh(MeshDaArma.Object);
	}

	RootComponent = MalhaDaArma;

	SetaDaArma = CreateDefaultSubobject<UArrowComponent>(FName("SetaCanoDaArma"));
	SetaDaArma->SetupAttachment(MalhaDaArma, FName("MuzzleFlashSocket"));
	SetaDaArma->SetRelativeLocation(FVector(1.5f, 0.f, -1.2f));

	EfeitoMuzzle = nullptr;
	ImpactoSangue = nullptr;
	ImpactoGeral = nullptr;
	DecalImpactoGeral = nullptr;
	SomDoTiro = nullptr;
}

void AArma::Atirar()
{
	if (SetaDaArma)
	{
		FVector Inicio = SetaDaArma->GetComponentLocation();
		FVector Direcao = SetaDaArma->GetComponentRotation().Vector();
		float ComprimentoRaycast = 1000;
		FVector Fim = Inicio + (Direcao * ComprimentoRaycast);
		FHitResult InfoImpacto;
		FCollisionQueryParams Parametros;
		Parametros.AddIgnoredActor(this);
		Parametros.AddIgnoredActor(GetOwner());
		Parametros.bTraceComplex = true;

		bool AcertouEmAlgo = GetWorld()->LineTraceSingleByChannel(InfoImpacto, Inicio, Fim, ECollisionChannel::ECC_Visibility, Parametros);
		if (EfeitoMuzzle)
		{
			FVector Localizacao = SetaDaArma->GetComponentLocation();
			FRotator Rotacao = SetaDaArma->GetComponentRotation();
			FVector Escala = FVector(0.9f);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EfeitoMuzzle, Localizacao, Rotacao, Escala, true);
		}

		if (SomDoTiro)
		{
			UGameplayStatics::PlaySoundAtLocation(SetaDaArma, SomDoTiro, Inicio);
		}
		
		if (AcertouEmAlgo)
		{
			UE_LOG(LogTemp, Warning, TEXT("Acertou em algo"));

			AActor* Ator = InfoImpacto.GetActor();
			if (Ator->GetClass()->IsChildOf(ACharacter::StaticClass()) && ImpactoSangue)
			{
				APersonagemTPS* Jogador = Cast<APersonagemTPS>(Ator);
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactoSangue, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), true);
				if (Jogador != nullptr)
				{
					Jogador->SetHealth(5.f);
				}
				else
				{
					ABotCharacter* Inimigo = Cast<ABotCharacter>(Ator);
					if (Inimigo != nullptr)
					{
						Inimigo->SetHealth(10.f);
					}
				}
			}
			else if (ImpactoGeral)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactoGeral, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), true);
				FVector TamanhoVariavel = FVector(FMath::RandRange(5.f, 15.f));
				UGameplayStatics::SpawnDecalAttached(DecalImpactoGeral, TamanhoVariavel, InfoImpacto.GetComponent(), NAME_None, InfoImpacto.Location, InfoImpacto.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 60.f);
			}

		}

		DrawDebugLine(GetWorld(), Inicio, Fim, FColor::Red, false, 5.0f, (uint8)0, 1.0f);



	}
}

// Called when the game starts or when spawned
void AArma::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

