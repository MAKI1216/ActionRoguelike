// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "math.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	if(RootComponent)
	{
		SpringArmComp->SetupAttachment(RootComponent);
	}
	SpringArmComp->bUsePawnControlRotation=true;
	//设置相机和控制器同向
	CameraComp=CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
 
	GetCharacterMovement()->bOrientRotationToMovement=true;
	//将正面转向运动方向
	bUseControllerRotationYaw=false;
	//yaw移动不与控制器yaw移动相同(可以看到角色的正面)
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::MoveForward(float value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch=0.0f;
	ControlRotation.Roll=0.0f;
	AddMovementInput(ControlRotation.Vector(),value);
	
}

void AMyCharacter::MoveRight(float value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch=0.0f;
	ControlRotation.Roll=0.0f;
	FVector RightVector=FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector,value);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&APawn::AddControllerPitchInput);
}

