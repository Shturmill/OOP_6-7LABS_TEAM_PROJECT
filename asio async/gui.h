#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>
#include "dns_resolver.h"

namespace DNSResolverGUI {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class Form1 : public Form {
	private:
		TextBox^ txtHost;
		Button^ btnResolve;
		TextBox^ txtOutput;

	public:
		Form1() {
			InitializeComponent();
		}

	protected:
		~Form1() {}

	private:
		void InitializeComponent() {
			this->Text = "DNS Resolver";
			this->Size = Drawing::Size(500, 300);

			txtHost = gcnew TextBox();
			txtHost->Location = Drawing::Point(20, 20);
			txtHost->Size = Drawing::Size(300, 25);

			btnResolve = gcnew Button();
			btnResolve->Text = "Resolve";
			btnResolve->Location = Drawing::Point(330, 20);
			btnResolve->Click += gcnew EventHandler(this, &Form1::OnResolveClicked);

			txtOutput = gcnew TextBox();
			txtOutput->Location = Drawing::Point(20, 60);
			txtOutput->Size = Drawing::Size(450, 180);
			txtOutput->Multiline = true;
			txtOutput->ReadOnly = true;

			this->Controls->Add(txtHost);
			this->Controls->Add(btnResolve);
			this->Controls->Add(txtOutput);
		}

		void OnResolveClicked(Object^ sender, EventArgs^ e) {
			std::string host = msclr::interop::marshal_as<std::string>(txtHost->Text);
			std::string results = resolveDNS(host);
			txtOutput->Text = gcnew String(results.c_str());
		}
	};
}
