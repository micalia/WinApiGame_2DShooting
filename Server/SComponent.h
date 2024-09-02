#pragma once

class Actor;

class SComponent
{
public:
	SComponent();
	virtual ~SComponent();

	virtual void BeginPlay() {}
	virtual void TickComponent() {}
	virtual void Render(HDC hdc) { }

	void SetOwner(shared_ptr<Actor> owner) { _owner = owner; }
	shared_ptr<Actor> GetOwner() { return _owner; }

protected:
	shared_ptr<Actor> _owner;
};

