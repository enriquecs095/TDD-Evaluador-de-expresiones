#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <iostream>
#define E "2.71" 
//#define PI "3.14"
template<typename T> //c++14
constexpr T constantPI = T("3.14");

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingExpressions
{
	TEST_CLASS(ExpresionPrefija)
	{
	public:
		wchar_t* errorMessage;
		int pos=0;
		std::string ErrorMatematico = "";
		char* emptyError = nullptr; //c++11
		std::string BigResult;
		TEST_METHOD(Prueba1)
		{
			std::string expresion = "";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		};

		TEST_METHOD(Prueba2)
		{
			std::string expresion = "10+20*wwfee3()12";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		};

		TEST_METHOD(Prueba3)
		{
			std::string expresion = "p+15*(e)";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);

		};

		TEST_METHOD(Prueba4)
		{
			std::string expresion = "p+e*10+15[]";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		};

		TEST_METHOD(Prueba5)
		{
			std::string expresion = "3+15*(12+10)+15*20+(12+10)";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		};

		TEST_METHOD(Prueba6)
		{
			std::string expresion = "3+15*(12+10)+15*20+(12+10)";
			std::string resultado = "655.000000";
			bool valueResult = Result(expresion);     
			Assert::IsTrue(valueResult, errorMessage);
			Assert::AreEqual(this->BigResult, resultado);
		};


		TEST_METHOD(Prueba7)
		{
			std::string expresion = "20%10*15+10+(10/12^10)+e";
			std::string resultado = "32.710000";
			bool valueResult = Result(expresion);      
			Assert::IsTrue(valueResult, errorMessage);
			Assert::AreEqual(this->BigResult, resultado);
		};


		TEST_METHOD(Prueba8)
		{
			std::string expresion = "(15.20/12)+(20*10+12/9)";
			std::string resultado = "202.600000";
			bool valueResult = Result(expresion);      
			Assert::IsTrue(valueResult, errorMessage);
			Assert::AreEqual(this->BigResult, resultado);
		};


		TEST_METHOD(Prueba9)
		{
			std::string expresion = "12%30*10/20+12";
			std::string resultado = "24.000000";
			bool valueResult = Result(expresion);      
			Assert::IsTrue(valueResult, errorMessage);
			Assert::AreEqual(this->BigResult, resultado);
		};


		TEST_METHOD(Prueba10)
		{
			std::string expresion = "20+12*14^5/12";
			std::string resultado = "537844.000000";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
			Assert::AreEqual(this->BigResult, resultado);
		};

		TEST_METHOD(Prueba11)
		{
			std::string expresion = "e+p*(15)";
			std::string resultado = "49.810000";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
			Assert::AreEqual(this->BigResult, resultado);
		}

		void LoadMessageError(std::string message) {
			errorMessage = new wchar_t[message.length() + 1];
			auto begin = std::begin(message); //c++ 11  auto y begin con std::begin
			auto end = std::end(message);
			std::copy(begin, end, errorMessage);
			errorMessage[message.length()] = 0;
		}


		bool Result(std::string expresion) {
			std::string message;
			decltype(message) mensajeError; //c++14
			emptyError = new char[24];
			emptyError = "Expresion vacia, revise";
			char value = u8'e'; //c++17
			if (expresion.empty()) {
				message = emptyError;
				LoadMessageError(message);
				return false;
			}
			if (!ValidarCaracteres(expresion)) {
				mensajeError = "Error de sintaxis, caracter invalido en la posicion: " + std::to_string(pos+1);
				LoadMessageError(mensajeError);
				return false;
			}
			
			if (!ValidarOperadores(expresion)) {
				message="Error en operadores, en la posicion: "+ std::to_string(pos+1);
				LoadMessageError(message);
				return false;
			}
			
			if (!ValidarParentesis(expresion)) {
				message="Error en parentesis, en la posicion: "+ std::to_string(pos+1);
				LoadMessageError(message);
				return false;
			}
			if (!ConvertirPostFija(expresion)) {
				message = "Error en conversion posfija. "+ this->ErrorMatematico;
				LoadMessageError(message);
				return false;
			}
			//std::string eo = VerResultado();
			return true;
		}

		bool ValidarOperadores(std::string Expresion) {
			size_t expresionL = Expresion.size();
			for (size_t i = 0; i < expresionL; i++)
			{
				if (i != expresionL - 1) {
					//si despues de un operador sigue otro operador
					if (Expresion[i] == 37 || Expresion[i] == 42 || Expresion[i] == 43 || Expresion[i] == 45 ||
						Expresion[i] == 46 || Expresion[i] == 47 || Expresion[i] == 94) {
						if (Expresion[i + 1] == 37 || Expresion[i + 1] == 42 || Expresion[i + 1] == 43 ||
							Expresion[i + 1] == 45 || Expresion[i + 1] == 46 || Expresion[i + 1] == 47 ||
							Expresion[i + 1] == 94) {
							pos = i+1;
							return false;
						}
					}
					//si no se añade un operador antes del parentesis
					else if (Expresion[i] != 37 || Expresion[i] != 42 || Expresion[i] != 43 || Expresion[i] != 45 ||
						Expresion[i] != 47 || Expresion[i] != 94) {
						if (Expresion[i + 1] == 40) {
							pos = i+1;
							return false;
						}
					}
					//si no se añade un operador despues del parentesis de cierre
					else if (Expresion[i] == 41) {
						if (Expresion[i + 1] != 37 || Expresion[i + 1] != 42 || Expresion[i + 1] != 43 || Expresion[i + 1] != 45 ||
							Expresion[i + 1] != 47 || Expresion[i + 1] != 94) {
							pos = i;
							return false;
						}
					}//si despues de un operador o un punto sigue un parentesis de cierre
					if (Expresion[i] == 37 || Expresion[i] == 42 || Expresion[i] == 43 || Expresion[i] == 45 ||
						Expresion[i] == 46 || Expresion[i] == 47 || Expresion[i] == 94) {
						if (Expresion[i + 1] == 41) {
							pos = i;
							return false;
						}
					}

				}//si al final hay un operador y no sigue un numero
				else if (Expresion[i] == 37 || Expresion[i] == 42 || Expresion[i] == 43 || Expresion[i] == 45 ||
					Expresion[i] == 46 || Expresion[i] == 47 || Expresion[i] == 94) {
					pos = i;
					return false;
				}
			}
			return true;
		}

		bool ValidarParentesis(std::string Expresion) {
			size_t expresionL = Expresion.size();
			size_t cantidadParentesisA = 0;
			size_t cantidadParentesisC = 0;
			std::vector<bool> check;
			for (size_t i = 0; i < expresionL; i++)
			{
				if (Expresion[i] == 40) {
					cantidadParentesisA++;
					check.push_back(false);
				}
				else if (Expresion[i] == 41) {

					if (check.empty()) {
						pos = i;
						return false;
					}
					for (size_t i = 0; i < cantidadParentesisA; i++)
					{
						if (!check[i]) {
							check[i] = true;
							break;
						}
						else if (check[i] && i == (cantidadParentesisA - 1)) {
							pos = i;
							return false;
						}
					}
					cantidadParentesisC++;
				}

			}
			if (cantidadParentesisA != cantidadParentesisC) {
				return false;
			}
			return true;
		}

		bool ValidarCaracteres(std::string expresion) {
			for (size_t i = 0; i < expresion.length(); i++)
			{
				if (expresion[i] != 37 && expresion[i] != 40 && expresion[i] != 41 && expresion[i] != 42 &&
					expresion[i] != 43 && expresion[i] != 45 && expresion[i] != 46 && expresion[i] != 47 &&
					expresion[i] != 48 && expresion[i] != 49 && expresion[i] != 50 && expresion[i] != 51 &&
					expresion[i] != 52 && expresion[i] != 53 && expresion[i] != 54 && expresion[i] != 55 &&
					expresion[i] != 56 && expresion[i] != 57 && expresion[i] != 94 && expresion[i] != 101 &&
					expresion[i] != 112) {
					pos = i;
					return false;
				}
			}
			return true;
		}

		bool ConvertirPostFija(std::string Expresion) {
			std::vector<std::string> pilaAuxiliar;
			std::vector<std::string> pilaSalida;
			std::string auxiliar;
			size_t pos = 0;
			std::string valorEntrada;
			while (pos< Expresion.size()) {
				//Saco el valor de entrada
				if (Expresion[pos] == 37 || Expresion[pos] == 40 || Expresion[pos] == 41 ||Expresion[pos] == 42 || 
					Expresion[pos] == 43 || Expresion[pos] == 45 || Expresion[pos] == 47 || Expresion[pos] == 94 ) {
					valorEntrada = Expresion[pos];
					pos++;
				}
				else{
					valorEntrada = "";
					for (pos; pos < Expresion.length(); pos++)
					{
						if (Expresion[pos] == 46 || Expresion[pos] == 48 || Expresion[pos] == 49 || Expresion[pos] == 50 || Expresion[pos] == 51 ||
							Expresion[pos] == 52 || Expresion[pos] == 53 || Expresion[pos] == 54 || Expresion[pos] == 55 ||
							Expresion[pos] == 56 || Expresion[pos] == 57 || Expresion[pos] == 101 || Expresion[pos] == 112) {
							valorEntrada += Expresion[pos];
						}
						else {
							break;
						}
					}
				}
			//-------------------------------------------------
				if (valorEntrada != "+" && valorEntrada != "-" && valorEntrada != "/" && valorEntrada != "*" &&
					valorEntrada != "%" && valorEntrada != "^" && valorEntrada != "(" && valorEntrada != ")"){
					pilaSalida.push_back(valorEntrada);
				}
				else if (valorEntrada == "(") {
					pilaAuxiliar.push_back(valorEntrada);
				}
				else if (valorEntrada == ")") {
					while (pilaAuxiliar.back() != "(") {
						auxiliar = pilaAuxiliar.back();
						pilaAuxiliar.pop_back();
						pilaSalida.push_back(auxiliar);
					}
					pilaAuxiliar.pop_back();
				}
				else if (valorEntrada == "+" || valorEntrada == "-" || valorEntrada == "/" || valorEntrada == "*" ||
					valorEntrada == "%" || valorEntrada == "^") {
					while (!pilaAuxiliar.empty() && pilaAuxiliar.back()!="(" &&  Prioridad(pilaAuxiliar.back()) >= Prioridad(valorEntrada)) {
						auxiliar = pilaAuxiliar.back();
						pilaAuxiliar.pop_back();
						pilaSalida.push_back(auxiliar);
					}
					pilaAuxiliar.push_back(valorEntrada);
				}
			}
			while (!pilaAuxiliar.empty()) {
				auxiliar = pilaAuxiliar.back();
				pilaAuxiliar.pop_back();
				pilaSalida.push_back(auxiliar);
			}

			return ConvertirConstantes(pilaSalida);
		}

		int Prioridad(std::string operador) {
			if (operador == "+" || operador == "-") {
				return 1;
			}
			else if (operador == "%") {
				return 2;
			}
			else if (operador == "/" || operador == "*") {
				return 3;
			}
			else if (operador == "^") {
				return 4;
			}
			return 0;
		}

		bool ConvertirConstantes(std::vector<std::string> expresion) {
			for (size_t i = 0; i < expresion.size(); i++)
			{
				if (std::strcmp(expresion[i].c_str(), "p") == 0) {
					
					expresion[i] = constantPI<const char*>;
				}
				else if (std::strcmp(expresion[i].c_str(), "e") == 0) {
					expresion[i] = E;
				}			
			}
			return OperacionesMatematicas(expresion);
		}

		bool OperacionesMatematicas(std::vector<std::string> expresion) {
			std::vector<double> resultado;
			double number1 = 0;
			double number2 = 0;
			int number2Module = 0;
			int number1Module = 0;
			int contadorOperaciones = 0;
			for (size_t i = 0; i < expresion.size(); i++)
			{
				//aqui voy a llamar cuando un vector no esta vacio
				if (std::strcmp(expresion[i].c_str(), "%") == 0) {
					if (resultado.empty()) {
						return false;
					}
					else {
						number2Module = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						return false;
					}
					else {
						number1Module = resultado.back();
						resultado.pop_back();
					}
					if (!number2Module) {//modular con denominador 0
						this->ErrorMatematico = "El modular no puede ser con denominador 0 ";
						return false;
					}
					contadorOperaciones++;
					resultado.push_back(number1Module % number2Module);
				}
				else if (std::strcmp(expresion[i].c_str(), "+") == 0) {
					if (resultado.empty()) {
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						return false;
					}
					else {
						number1 = resultado.back();
						resultado.pop_back();
					}
					contadorOperaciones++;
					resultado.push_back(number1 + number2);
				}
				else if (std::strcmp(expresion[i].c_str(), "-") == 0) {
					if (resultado.empty()) {
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						return false;
					}
					else {
						number1 = resultado.back();
						resultado.pop_back();
					}
					contadorOperaciones++;
					resultado.push_back(number1 - number2);
				}
				else if (std::strcmp(expresion[i].c_str(), "*") == 0) {
					if (resultado.empty()) {
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						return false;
					}
					else {
						number1 = resultado.back();
						resultado.pop_back();
					}
					contadorOperaciones++;
					resultado.push_back(number1 * number2);
				}
				else if (std::strcmp(expresion[i].c_str(), "/") == 0) {
					if (resultado.empty()) {
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						return false;
					}
					else {
						number1 = resultado.back();
						resultado.pop_back();
					}
					if (!number2) {//divisiones con denominador 0
						this->ErrorMatematico = "La division no puede ser con denominador 0 ";
						return false;
						break;
					}
					contadorOperaciones++;
					resultado.push_back(number1 / number2);
				}
				else if (std::strcmp(expresion[i].c_str(), "^") == 0) {
					if (resultado.empty()) {
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						return false;
					}
					else {
						number1 = resultado.back();
						resultado.pop_back();
					}
					contadorOperaciones++;
					resultado.push_back(pow(number1, number2));
				}
				else {
					resultado.push_back(atof(expresion[i].c_str()));
				}
			}
			if (!contadorOperaciones) {
				this->ErrorMatematico = "No hay operaciones matematicas ";
				pos = expresion.size();
				return false;
			}
			this->BigResult = std::to_string(resultado.back());
			resultado.pop_back();
			return true;
		}

		enum class PrioridadRango { UNO, DOS, TRES, CUATRO, CERO };

		 

		auto Prioridadd(PrioridadRango p) {//c++ 14 clases auto
			 // c++ 11
			size_t number { 0 };
			switch (p) {
			case PrioridadRango::UNO:
				number=1;
				break;
			case PrioridadRango::DOS:
				number = 2;
				break;
			case PrioridadRango::TRES:
				number = 3;
				break;
			case PrioridadRango::CUATRO:
				 number = 4;
				break;

			case PrioridadRango::CERO: [[fallthrough]]//c++17 el compilador cae ahi como previsto
				number = 0;
				break;
			}
			return number;
		}


		//c++14
		[[deprecated("Funcion no necesaria en el proyecto")]] std::string VerResultado() {
			return  this->BigResult;
		}

	};
}