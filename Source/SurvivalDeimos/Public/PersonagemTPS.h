// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PersonagemTPS.generated.h"

UCLASS()
class SURVIVALDEIMOS_API APersonagemTPS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APersonagemTPS();

	class AArma* ArmaPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoverParaFrente(float Valor);
	void MoverDireita(float Valor);
	void Agachar();
	void Levantar();
	void Pular();
	void PararPulo();
	void Atirar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraPersonagem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* SpringArmCamera;

	UPROPERTY(BlueprintReadWrite, Category = "Pulo")
		bool bEstaPulando;

	UPROPERTY(EditAnywhere, Category = "Arma")
		TSubclassOf<class AArma>BP_ArmaTipoRifle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
		float Health;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
		bool bEstaMorto;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void SetHealth(float Dano);

	UFUNCTION()
		float GetHealth();
	
	UFUNCTION()
		bool IsEstaMorto();
};
