// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterStrat.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	/************************************/
	/* Camera							*/
	/************************************/

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Set up camera boom
	PlayerCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCameraBoom"));
	PlayerCameraBoom->AttachTo(RootComponent);
	PlayerCameraBoom->TargetArmLength = 300.f;		// Set boom length
	PlayerCameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->AttachTo(PlayerCameraBoom, USpringArmComponent::SocketName);		// Attach camera to camera boom end
	PlayerCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	//Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);

	
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);			// Works
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);		// Can't get it working
	
	InputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);	// Not in use

}



void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}