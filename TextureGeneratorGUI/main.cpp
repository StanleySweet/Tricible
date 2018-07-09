//
// Author: Pierre COURTEILLE
//

//----------------------------------------//
// include STL
//----------------------------------------//
#include <iostream> // pour std::cout et std::endl
#include <string>

//----------------------------------------//
// include Tricible
//----------------------------------------//
#include "./UnitTesting_Tools.hpp"
#include "./Unit Testing/PerlinNoise.hpp"

	//----------------------------------------//
	// code
	//----------------------------------------//
int RunBlock_AllPerlinNoise()
{
	std::string pathDir = UnitTesting::Tools::GetCurrentDirectoryOfProcess();

	// en-t�te
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "By courte_p : Unit Testing / Perlin Noise" << std::endl;
	std::cout << "Current Directories : " << std::endl << pathDir << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	// bloc de tests
	UnitTesting::Tools::RunTest_NoParameters("PerlinNoise_1D", &UnitTesting::PerlinNoise_1D);
	UnitTesting::Tools::RunTest_NoParameters("PerlinNoise_1D_Stacked", &UnitTesting::PerlinNoise_1D_Stacked);
	UnitTesting::Tools::RunTest_NoParameters("PerlinNoise_2D", &UnitTesting::PerlinNoise_2D);
	UnitTesting::Tools::RunTest_NoParameters("PerlinNoise_2D_Stacked", &UnitTesting::PerlinNoise_2D_Stacked);
	UnitTesting::Tools::RunTest_NoParameters("PerlinNoise_2D_Stacked_With_Color", &UnitTesting::PerlinNoise_2D_Stacked_With_Color);

	// sp�ciale : afficher une image dans une fen�tre SFML
	UnitTesting::Tools::DrawInSfmlWindowFromPictureFile("Example_PerlinNoise_2D_Stacked_With_Color.png");

	// pied de page
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "Press any key to exit... (STOPPED)" << std::endl;
	getchar(); // attendre entr�e touche clavier

	// fin
	return 0;
}

int main()
{
	int result = 0;

	result += RunBlock_AllPerlinNoise();

	return (result);
}

