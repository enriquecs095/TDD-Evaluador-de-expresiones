#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingExpressions
{
	TEST_CLASS(TestingSyntaxPostFix)
	{

	public:
		std::string aux;
		wchar_t* errorMessage;

		void LoadMessage() {
			aux = "Error ha fallado";
			errorMessage = new wchar_t[aux.length() + 1];
			auto begin = aux.begin();//c++ 11
			auto end = aux.end();
			std::copy(begin, end, errorMessage);
			errorMessage[aux.length()] = 0;
		}

		TEST_METHOD(Prueba1)
		{
			std::string expresion = "10,40,pe,%,*,/";
			LoadMessage();
			Assert::IsTrue(ValidarSintaxisPosFija(expresion), errorMessage);
		};

		TEST_METHOD(Prueba2)
		{
			std::string expresion = "4533,10,+,20..,*,30,*";
			Assert::IsTrue(ValidarSintaxisPosFija(expresion), errorMessage);
		};

		TEST_METHOD(Prueba3)
		{
			std::string expresion = "p,33e40,+";
			Assert::IsTrue(ValidarSintaxisPosFija(expresion), errorMessage);
		};

		TEST_METHOD(Prueba4)
		{
			std::string expresion = "1010.10,,120,++";
			Assert::IsTrue(ValidarSintaxisPosFija(expresion), errorMessage);
		};


		bool ValidarSintaxisPosFija(std::string Expresion) {
			size_t expresionL = Expresion.length();
			for (size_t i = 0; i < expresionL; i++)
			{
				if (i != expresionL - 1) {
					//si despues de un operador sigue otro operador o un numero
					if (Expresion[i] == 37 || Expresion[i] == 42 || Expresion[i] == 43 ||
						Expresion[i] == 45 || Expresion[i] == 46 || Expresion[i] == 47 || Expresion[i] == 94 ||
						Expresion[i] == 101 || Expresion[i] == 112) {
						if (Expresion[i + 1] == 37 || Expresion[i + 1] == 42 || Expresion[i + 1] == 43 ||
							Expresion[i + 1] == 45 || Expresion[i + 1] == 46 || Expresion[i + 1] == 47 ||
							Expresion[i + 1] == 48 || Expresion[i + 1] == 49 || Expresion[i + 1] == 50 ||
							Expresion[i + 1] == 51 || Expresion[i + 1] == 52 || Expresion[i + 1] == 53 ||
							Expresion[i + 1] == 54 || Expresion[i + 1] == 55 || Expresion[i + 1] == 56 ||
							Expresion[i + 1] == 57 || Expresion[i + 1] == 94 || Expresion[i + 1] == 101 ||
							Expresion[i + 1] == 112) {
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
							return false;
						}
					}

					//si despues de una coma hay otra coma
					if (Expresion[i] == 44 && Expresion[i + 1] == 44) {
						return false;
					}
					//si al final hay un numero o coma y no sigue un operador
				}else if (Expresion[i] == 48 || Expresion[i] == 49 || Expresion[i] == 50 || Expresion[i] == 51 ||
						 Expresion[i] == 52 || Expresion[i] == 53 || Expresion[i] == 54 || Expresion[i] == 55 ||
						 Expresion[i] == 56 || Expresion[i] == 57 || Expresion[i] == 101 || Expresion[i] == 112 ||
						 Expresion[i] == 44) {
					return false;
				}
			}
			return true;

		}
		
	};

}