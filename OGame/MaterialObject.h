#pragma once
#include "VisualObject.h"
#include "PresentObject.h"

class MaterialObject :
	public VisualObject, public PresentObject
{
public:
	MaterialObject();
	virtual ~MaterialObject();

	void update();

	void setPosition(const glm::vec3 & _Position) override;

private:

};

