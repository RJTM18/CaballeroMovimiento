#pragma once
#pragma once
#include "sprite.h"

class Caballero : public Sprite {
private:
	Direccion direccion;
	bool lanzando;
public:
	Caballero(int x, int y) : Sprite(x, y, 126, 126, 4, 5)
	{
		velocidad = 20;
		direccion = Derecha;
		lanzando = false;
	}
	Direccion getDireccion() { return direccion; }
	bool estaLanzando() { return lanzando; }
	void lanzar()
	{
		if (lanzando) return;
		lanzando = true;
		indiceX = 1;
	}
	void mover(Direccion tecla, int limiteAncho, int limiteAlto) override {
		
		if (tecla != Ninguno) {
			direccion = tecla;
			dx = 0;
			dy = 0;
			if (tecla == Arriba) dy = -1;
			if (tecla == Abajo) dy = 1;
			if (tecla == Izquierda) dx = -1;
			if (tecla == Derecha) dx = 1;
			x += dx * velocidad;
			y += dy * velocidad;
			if (x < 0) x = 0;
			if (y < 0) y = 0;
			if (x > limiteAncho - ancho) x = limiteAncho - ancho;
			if (y > limiteAlto - alto) y = limiteAlto - alto;
		}

		if (direccion == Arriba) indiceY = 0;
		if (direccion == Abajo) indiceY = 1;
		if (direccion == Izquierda) indiceY = 2;
		if (direccion == Derecha) indiceY = 3;

		if (lanzando) {
			indiceX++;
			if (indiceX > 4) {
				indiceX = 0;
				lanzando = false;
			}
		}

		else if (tecla != Ninguno)
		{
			if (indiceX == 1) indiceX = 4;
			else indiceX = 1;
		}
		
		else
		{
			indiceX = 0;
		}
	}
};