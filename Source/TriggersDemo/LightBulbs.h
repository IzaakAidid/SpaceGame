// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightBulbs.generated.h"

UCLASS()
class TRIGGERSDEMO_API ALightBulbs : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ALightBulbs();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    float SpreadCorruption(AActor* corruptedActor);

    void ApplyCorruption(AActor* corruptedActor);

    UFUNCTION()
    void CorruptionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    void BecomeCorrupt(AActor* corruptActor);
    //HitBox for corruption
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Corruption")
    class USphereComponent* CorruptionRadius;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    UStaticMeshComponent* LightBulbMesh;


protected:
    UPROPERTY(VisibleAnywhere, Category = "Corruption")
    bool m_isCorrrupted;

    UPROPERTY(VisibleAnywhere, Category = "Corruption")
    float m_corruptionAmount;

    UPROPERTY(VisibleAnywhere, Category = "Corruption")
    float m_maxCorruptionRadius;
    
    UPROPERTY(VisibleAnywhere, Category = "Corruption")
    float currentRadius;

};
