// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arma.generated.h"

UCLASS()
class SURVIVALDEIMOS_API AArma : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArma();

	UFUNCTION()
		void Atirar();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arma")
		class USkeletalMeshComponent* MalhaDaArma;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Arma")
		class UArrowComponent* SetaDaArma;

	UPROPERTY(EditAnywhere, Category = "Efeitos da arma")
		class UParticleSystem* EfeitoMuzzle;

	UPROPERTY(EditAnywhere, Category = "Efeitos da arma")
		class UParticleSystem* ImpactoSangue;

	UPROPERTY(EditAnywhere, Category = "Efeitos da arma")
		class UParticleSystem* ImpactoGeral;

	UPROPERTY(EditAnywhere, Category = "Efeitos da arma")
		class UMaterialInterface* DecalImpactoGeral;

	UPROPERTY(EditAnywhere, Category = "Efeitos da arma")
		class USoundBase* SomDoTiro;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
