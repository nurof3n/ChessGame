#pragma once
#include "CustomExcept.h"
#include "Piesa.h"
#include "Graphics.h"

class Tabla : public SpriteObj {
public:
	Tabla();
	~Tabla() noexcept;

	void Setup() noexcept;
	void Draw( Graphics& );
private:
	Piesa* _tabla[9][9];
};

