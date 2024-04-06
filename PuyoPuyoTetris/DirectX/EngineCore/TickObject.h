#pragma once

#define GENERATED_BODY(Parent) \
	typedef Parent Super;

class UEngineTickCallBack
{
public:
	float Time;
	std::function<void()> CallBack;
};

// ���� :
class ULevel;
class UTickObject
{
public:
	// constrcuter destructer
	UTickObject();
	~UTickObject();

	// delete Function
	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;


	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void DelayCallBack(float _Time, std::function<void()> _CallBack)
	{
		if (nullptr == _CallBack)
		{
			MsgBoxAssert("�ݹ����� nullptr �Դϴ�.");
		}

		for (size_t i = 0; i < CallBacks.size(); i++)
		{
			if (nullptr == CallBacks[i])
			{
				CallBacks[i] = std::make_shared<UEngineTickCallBack>(_Time, _CallBack);
				return;
			}
		}

		CallBacks.push_back(std::make_shared<UEngineTickCallBack>( _Time ,_CallBack ));
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

	virtual void LevelEnd(ULevel* _NextLevel) {};
	virtual void LevelStart(ULevel* _PrevLevel) {};

private:
	int Order = 0;

	std::vector<std::shared_ptr<UEngineTickCallBack>> CallBacks;
};
