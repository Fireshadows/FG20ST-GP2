
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueEvent);


USTRUCT(BlueprintType)
struct FNodeData
{
	GENERATED_BODY()

public:
	FNodeData()
	{
		keyWord = -1;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	int keyWord;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	int index;

};

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_BODY()
	
public:
	FDialogueData()
	{
		line = FText();
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	FText line;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	float timer;

	TArray<FNodeData> children;
};


USTRUCT(BlueprintType)
struct FBranchInput
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		int keyWord;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
		FText line;
};

UCLASS(Blueprintable, Abstract)
class FGGP2_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogueComponent();

	void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FDialogueEvent DialogueStarted;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FDialogueEvent DialogueNext;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FDialogueEvent DialogueStopped;




	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	TArray<FDialogueData> lines;

	/*** Construction methods ***/
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int InitializeText(FText dialogueInput, float timer);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int AddLine(int key, FText dialogueInput, float timer);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int AddBranch(int key, FBranchInput dialogueInput, float timer);


	/*** Flow control methods ***/
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void Start();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void Next();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void Stop();

	/*** Branch Control ***/
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool AtBranch() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool EnterKeyword(int keyword);
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	FDialogueData GetCurrentText() const;

private:

	void TestIfWaitingForKeyword();
	int currentIndex;
	uint32 bStarted : 1;
	uint32 bWaitingForKeyword : 1;
};