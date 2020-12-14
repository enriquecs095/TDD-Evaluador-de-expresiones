#include "pch.h"
#include "CppUnitTest.h"
#include <vector> 
#define PI "3.14"
#define E "2.71" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingExpressions
{
	TEST_CLASS(ExpresionPosFija)
	{
	public:
		std::string ErrorMatematico="";
		wchar_t* errorMessage;
		int pos = 0;

		TEST_METHOD(Prueba1)
		{
			std::string expresion = "10,1.2,2,+,2,*,+";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		};

		TEST_METHOD(Prueba2)
		{
			std::string expresion = "2,+,2,*,+";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		};

		TEST_METHOD(Prueba3)
		{
			std::string expresion = "+,20,10,-";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);

		};

		TEST_METHOD(Prueba4)
		{
			std::string expresion = "15,0,/,0,%";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		};

		TEST_METHOD(Prueba5)
		{
			std::string expresion = "10,12,22";
			bool valueResult = Result(expresion);
			Assert::IsTrue(valueResult, errorMessage);
		}


		void LoadMessageError(std::string message) {
			errorMessage = new wchar_t[message.length() + 1];
			auto begin = message.begin(); //c++ 11
			auto end = message.end();
			std::copy(begin, end, errorMessage);
			errorMessage[message.length()] = 0;
		}


		bool Result(std::string expresion) {
			std::string message;
			if (!ValidarCaracteres(expresion)) {
				message = "Error de sintaxis, caracter invalido en la posicion: " + std::to_string(pos + 1);
				LoadMessageError(message);
				return false;
			}

			if (!ValidarOperadores(expresion)) {
				message = "Error en operadores, en la posicion: " + std::to_string(pos + 1);
				LoadMessageError(message);
				return false;
			}

			if (!ValidarOperacionMatematica(expresion)) {
				message = "Error en operacion matematica " + this->ErrorMatematico+"en la posicion: " + std::to_string(pos + 1);
				LoadMessageError(message);
				return false;
			}
			return true;
		}

		bool ValidarCaracteres(std::string Expresion) {
			for (size_t i = 0; i < Expresion.length(); i++)
			{
				if (Expresion[i] != 37 && Expresion[i] != 42 && Expresion[i] != 43 && Expresion[i] != 44 &&
					Expresion[i] != 45 && Expresion[i] != 46 && Expresion[i] != 47 && Expresion[i] != 48 &&
					Expresion[i] != 49 && Expresion[i] != 50 && Expresion[i] != 51 && Expresion[i] != 52 &&
					Expresion[i] != 53 && Expresion[i] != 54 && Expresion[i] != 55 && Expresion[i] != 56 &&
					Expresion[i] != 57 && Expresion[i] != 94 && Expresion[i] != 101 && Expresion[i] != 112) {
					pos = i;
					return false;
				}
			}
			return true;
		}

		bool ValidarOperadores(std::string Expresion) {
			size_t expresionL = Expresion.length();
			for (size_t i = 0; i < Expresion.length(); i++)
			{
				if (i != expresionL - 1) {
					//si despues de un operador sigue otro operador o un numero
					if (Expresion[i] == 37 || Expresion[i] == 42 || Expresion[i] == 43 ||
						Expresion[i] == 45 || Expresion[i] == 47 || Expresion[i] == 94 ||
						Expresion[i] == 101 || Expresion[i] == 112) {
						if (Expresion[i + 1] == 37 || Expresion[i + 1] == 42 || Expresion[i + 1] == 43 ||
							Expresion[i + 1] == 45 || Expresion[i + 1] == 46 || Expresion[i + 1] == 47 ||
							Expresion[i + 1] == 48 || Expresion[i + 1] == 49 || Expresion[i + 1] == 50 ||
							Expresion[i + 1] == 51 || Expresion[i + 1] == 52 || Expresion[i + 1] == 53 ||
							Expresion[i + 1] == 54 || Expresion[i + 1] == 55 || Expresion[i + 1] == 56 ||
							Expresion[i + 1] == 57 || Expresion[i + 1] == 94 || Expresion[i + 1] == 101 ||
							Expresion[i + 1] == 112) {
							pos = i+1;
							return false;
						}
					}
					//si despues de un numero o constante sigue un operador o constante
					if (Expresion[i] == 48 || Expresion[i] == 49 || Expresion[i] == 50 || Expresion[i] == 51 ||
						Expresion[i] == 52 || Expresion[i] == 53 || Expresion[i] == 54 || Expresion[i] == 55 ||
						Expresion[i] == 56 || Expresion[i] == 57 || Expresion[i] == 101 || Expresion[i] == 112) {
						if (Expresion[i + 1] == 37 || Expresion[i + 1] == 42 || Expresion[i + 1] == 43 ||
							Expresion[i + 1] == 45 || Expresion[i + 1] == 47 || Expresion[i + 1] == 94 ||
							Expresion[i + 1] == 94 || Expresion[i + 1] == 101 || Expresion[i + 1] == 112) {
							pos = i + 1;
							return false;
						}
					}
					//si despues de una coma hay otra coma
					if (Expresion[i] == 44 && Expresion[i + 1] == 44) {
						pos = i + 1;
						return false;
					}
					//si despues de un punto sigue un operador o constante
					if (Expresion[i] == 46 ) {
						if (Expresion[i + 1] == 37 || Expresion[i + 1] == 42 || Expresion[i + 1] == 43 ||
							Expresion[i + 1] == 45 || Expresion[i + 1] == 46 || Expresion[i + 1] == 47 ||
							Expresion[i + 1] == 94 || Expresion[i + 1] == 101 || Expresion[i + 1] == 112) {
							pos = i + 1;
							return false;
						}
					}
				}//si al final hay un numero o coma y no sigue un operador
				else if (Expresion[i] == 48 || Expresion[i] == 49 || Expresion[i] == 50 || Expresion[i] == 51 ||
					Expresion[i] == 52 || Expresion[i] == 53 || Expresion[i] == 54 || Expresion[i] == 55 ||
					Expresion[i] == 56 || Expresion[i] == 57 || Expresion[i] == 101 || Expresion[i] == 112 ||
					Expresion[i] == 44) {
					pos = i;
					return false;
				}
			}
			return true;
		}

		bool ValidarOperacionMatematica(std::string expresion) {
			char* Expresion = new char[expresion.length() + 1];
			auto begin = expresion.begin(); //c++ 11
			auto end = expresion.end();
			std::copy(begin, end, Expresion);
			Expresion[expresion.length()] = 0;
			char* pointer;
			char delim[] = ",";
			char* fixError;
			std::vector<std::string> pila;
			pointer = strtok_s(Expresion, delim, &fixError);
			while (pointer != NULL) {
				if (std::strcmp(pointer, "p") == 0) {
					pila.push_back(PI);
				}
				else if (std::strcmp(pointer, "e") == 0) {
					pila.push_back(E);
				}
				else {
					pila.push_back(pointer);
				}
				pointer = strtok_s(NULL, delim, &fixError);
			}
			return OperacionesMatematicas(pila);
		}

		bool OperacionesMatematicas(std::vector<std::string> expresion) {
			std::vector<double> resultado;
			double number1 = 0;
			double number2 = 0;
			int number2Module=0;
			int number1Module=0;
			int contadorOperaciones = 0;
			for (size_t i = 0; i < expresion.size(); i++)
			{
				//aqui voy a llamar cuando un vector no esta vacio
				if (std::strcmp(expresion[i].c_str(), "%") == 0) {
					if (resultado.empty()) {
						pos = i;
						return false;
					}
					else {
						number2Module = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						pos = i;
						return false;
					}
					else {
						number1Module = resultado.back();
						resultado.pop_back();
					}
					if (!number2Module) {//modular con denominador 0
						this->ErrorMatematico = "El modular no puede ser con denominador 0 ";
						pos = i;
						return false;
					}
					contadorOperaciones++;
					resultado.push_back(number1Module % number2Module);
				}
				else if (std::strcmp(expresion[i].c_str(), "+") == 0) {
					if (resultado.empty()) {
						pos = i;
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						pos = i;
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
						pos = i;
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						pos = i;
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
						pos = i;
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						pos = i;
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
						pos = i;
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						pos = i;
						return false;
					}
					else {
						number1 = resultado.back();
						resultado.pop_back();
					}
					if (!number2) {//divisiones con denominador 0
						this->ErrorMatematico = "La division no puede ser con denominador 0 ";
						pos = i;
						return false;
						break;
					}
					contadorOperaciones++;
					resultado.push_back(number1 / number2);
				}
				else if (std::strcmp(expresion[i].c_str(), "^") == 0) {
					if (resultado.empty()) {
						pos = i;
						return false;
					}
					else {
						number2 = resultado.back();
						resultado.pop_back();
					}
					if (resultado.empty()) {
						pos = i;
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
			return true;
		}


	};
}

