#pragma onceç
#include "Juego.h"

namespace MobimientoSprites {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO; //Input/Output data

		/// <summary>
	/// Summary for FrmJuego
	/// </summary>
	public ref class FrmJuego : public System::Windows::Forms::Form {
	private:
		Bitmap^ caballero;
		Bitmap^ enemigo;
		Bitmap^ fuego;
		Bitmap^ fondo;
		Juego* juego; //gestor

		   Direccion teclaPresionada;

	public:
		FrmJuego(void) {
			InitializeComponent();
			juego = nullptr;
		}

	protected:
		~FrmJuego() {
			if (components) { delete components; }
			if (juego != nullptr) delete juego;
		}

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::FlowLayoutPanel^ pnlSprite;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:
	
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pnlSprite = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(153, 115);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 100);
			this->panel1->TabIndex = 0;
			// 
			// pnlSprite
			// 
			this->pnlSprite->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlSprite->Location = System::Drawing::Point(0, 0);
			this->pnlSprite->Name = L"pnlSprite";
			this->pnlSprite->Size = System::Drawing::Size(1044, 575);
			this->pnlSprite->TabIndex = 0;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &FrmJuego::timer1_tick);
			// 
			// FrmJuego
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1044, 575);
			this->Controls->Add(this->pnlSprite);
			this->Controls->Add(this->panel1);
			this->KeyPreview = true;
			this->Name = L"FrmJuego";
			this->Text = L"Caballero";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &FrmJuego::FrmJuego_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &FrmJuego::FrmSprite_KeyUp);
			this->ResumeLayout(false);

		}

#pragma endregion
	Bitmap^ cargarImagen(String^ nombre) {
		String^ ruta = Path::Combine(Application::StartupPath, nombre);
		if(!File::Exists(ruta)) ruta = nombre;
		return gcnew Bitmap(ruta);
	}

	System::Void FrmSprite_Load(System::Object^ sender, System::EventArgs^ e) {
		caballero = cargarImagen("cabellero_new.png");
		fuego = cargarImagen("fuego_new.png");
		//enemigo = cargarImagen("enemigo_new.png");
		//fondo = cargarImagen("fondo_paisaje_01.png");
		teclaPresionada = Ninguno;
	}

	System::Void timer1_tick(System::Object^ sender, System::EventArgs^ e) 	{
		int ancho = pnlSprite->Width;
		int alto = pnlSprite->Height;
		if (ancho <= 0 || alto <= 0) return;
		if (juego == nullptr) juego = new Juego(ancho, alto); //AL INICIAR EL PROGRAMA
		juego->mover(teclaPresionada, ancho, alto);
		Graphics^ canvas = pnlSprite->CreateGraphics();
		BufferedGraphics^ buffer = BufferedGraphicsManager::Current->Allocate(canvas, pnlSprite->ClientRectangle);
		buffer->Graphics->DrawImage(fondo, 0, 0, ancho, alto);
		juego->dibujar(buffer->Graphics, caballero, enemigo, fuego);
		buffer->Render(canvas);
		delete buffer;
		//lblEliminados->Text = Convert::ToString(juego->getEliminados());
	}
	
	private: System::Void FrmJuego_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Down || e->KeyCode == Keys::S) teclaPresionada = Abajo;
		if (e->KeyCode == Keys::Left || e->KeyCode == Keys::A) teclaPresionada = Izquierda;
		if (e->KeyCode == Keys::Right || e->KeyCode == Keys::D) teclaPresionada = Derecha;
		if (e->KeyCode == Keys::Up || e->KeyCode == Keys::W) teclaPresionada = Arriba;
		if (e->KeyCode == Keys::Space && juego != nullptr) juego->lanzarBola();
	}

	private: System::Void FrmSprite_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Down || e->KeyCode == Keys::S) { if (teclaPresionada == Abajo) teclaPresionada = Ninguno; }
		if (e->KeyCode == Keys::Left || e->KeyCode == Keys::A) { if (teclaPresionada == Izquierda) teclaPresionada = Ninguno; }
		if (e->KeyCode == Keys::Right || e->KeyCode == Keys::D) { if (teclaPresionada == Derecha) teclaPresionada = Ninguno; }
		if (e->KeyCode == Keys::Up || e->KeyCode == Keys::W) { if (teclaPresionada == Arriba) teclaPresionada = Ninguno; }
	}
};
}
