
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
		index = -1;
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
		timer = 0;
		bIsBranch = false;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	FText line;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	float timer;

	TArray<FNodeData> children;

	uint32 bIsBranch : 1;
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

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FDialogueEvent DialogueAtBranch;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FDialogueEvent DialogueReset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialogue")
	TArray<FDialogueData> lines;

	/*** Construction methods ***/
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int InitializeText(FText dialogueInput, float timer);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int AddLine(int key, FText dialogueInput, float timer);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int AddBranch(int key);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	int AddLineToBranch(int key, FBranchInput dialogueInput, float timer);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool HasChild() const;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AddReturnNode(int key, int returnTo);

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

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue")
	uint32 bStarted : 1;
private:

	int currentIndex;


};